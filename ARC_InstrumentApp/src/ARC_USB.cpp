/*
 * ARCMonochromtor.cpp		v0.04 (2006 07 19)
 *
 * ARCMonochromator Control
 *
 *
 * KNOWN BUGS:
 * Turning off or physically disconnecting the monochromator while the program is
 * in connected status may cause subsequent calls to seg fault.
 */

#pragma warning(disable:4250)

#include <vector>

#ifdef _M_X64
#include "..\Acton\ARC_Instrument_x64.h"
#else
#include "..\Acton\ARC_Instrument_dll.h"
#endif

#include <iocsh.h>
#include <epicsExit.h>
#include <asynDriver.h>

#define epicsExportSharedSymbols
#include <epicsExport.h>
#include "ARC_USB.h"

const static int STD_GRATING = 1200;
static const int NM_to_Angstrom = 10;
static const int ShortTimeout = 200;

class timed_lock_guard
{
	bool m_isLocked;
	std::timed_mutex& m_mutex;

public:
	timed_lock_guard(std::timed_mutex const& mutex, unsigned long TimeOut) :
		m_mutex(const_cast<std::timed_mutex&>(mutex))
	{
		using Ms = std::chrono::milliseconds;
		m_isLocked = m_mutex.try_lock_for(Ms(TimeOut));
	}
	~timed_lock_guard() {
		if (m_isLocked)
			m_mutex.unlock();
	}
	bool isLocked() const {
		return m_isLocked;
	}
};

namespace Motors {

#ifdef _DEBUG
const unsigned long ARC_USB::DefaultTimeout = UINT_MAX;
#else
const unsigned long ARC_USB::DefaultTimeout = 30000;
#endif

class ARC_USB::Exception : public std::runtime_error
{
public:
#ifdef _M_X64
	Exception(long code, std::string const& While, long Line) :
		std::runtime_error(GetDetails(code, While, Line)) {
		}
	static std::string GetDetails(long code, std::string const& While, long Line) {
		char Error_Str[_MAX_PATH+1];
		ARC_Error_To_English(code, Error_Str, sizeof(Error_Str)-1);
		return std::string(Error_Str) + " while " + While;
	}
#endif
	Exception(std::string const& Details, std::string const& While, long Line) :
		std::runtime_error(Details + " while " + While) {
		}

};

class ARC_USB::Drive
{
public:
	Drive(ARC_USB* parent)
	{
		m_parent = parent;
	}
	ARC_USB* parent() {
		return m_parent;
	}
private:
	ARC_USB* m_parent;
};

class ARC_USB::GratingDrive : public Drive
{
private:
	// Asyn handle
	int m_GratingPV;
	int m_TurretPV;

	std::timed_mutex m_Mutex;
	std::vector<int> m_gratings;
	int m_gratingNr;
	int m_turretNr;
	int m_maxTurret;

public:
	GratingDrive(ARC_USB* parent);

	asynStatus readEnum(asynUser *pasynUser, char *strings[], int values[], int severities[],
		size_t nElements, size_t *nIn);
	asynStatus writeInt32(asynUser *pasynUser, epicsInt32 value);
	asynStatus readInt32(asynUser *pasynUser, epicsInt32 *value);

	std::vector<int> const& gratings() const {
		return m_gratings;
	}
	int grating(int gratingNo) const {
		return m_gratings[gratingNo];
	}
	double readPositionFromMotor(asynUser* pasynUser);
	double startMovement(asynUser* pasynUser, double targetPosition);
};

ARC_USB::GratingDrive::GratingDrive(ARC_USB* parent) :
	Drive(parent)
{
	parent->createParam("GRATING", asynParamInt32, &m_GratingPV);
	parent->createParam("TURRET", asynParamInt32, &m_TurretPV);
	long maxGratingNr = parent->ARC_get_Mono_Grating_Max(parent->pasynUserSelf, m_Mutex);
	m_gratings.resize(maxGratingNr);
	for (size_t i = 0; i < m_gratings.size(); i++) {
		long grating = parent->ARC_get_Mono_Grating_Density(parent->pasynUserSelf, m_Mutex, long(i + 1));
		m_gratings[i] = grating;
	}
	m_gratingNr = parent->ARC_get_Mono_Grating(parent->pasynUserSelf, m_Mutex)-1;
	parent->setIntegerParam(m_GratingPV, m_gratingNr);
	m_turretNr = parent->ARC_get_Mono_Turret(parent->pasynUserSelf, m_Mutex)-1;
	parent->setIntegerParam(m_TurretPV, m_turretNr);
	m_maxTurret = parent->ARC_get_Mono_Turret_Max(parent->pasynUserSelf, m_Mutex);
}

asynStatus ARC_USB::GratingDrive::readEnum(asynUser *pasynUser, char *strings[], int values[], int severities[],
	size_t nElements, size_t *nIn)
{
	int function = pasynUser->reason;
	char enumString[64];
	asynStatus status = asynSuccess;
	if (function == m_GratingPV)
	{
		*nIn = m_gratings.size();
		for (size_t grating = 0; grating < m_gratings.size(); grating++)
		{
			if (strings[grating])
				free(strings[grating]);
			snprintf(enumString, sizeof(enumString) - 1, "%d", m_gratings[grating]);
			strings[grating] = _strdup(enumString);
			values[grating] = m_gratings[grating];
		}
	}
	return status;
}

asynStatus ARC_USB::GratingDrive::readInt32(asynUser *pasynUser, epicsInt32 *value)
{
	int function = pasynUser->reason;
	asynStatus status = asynSuccess;
	if (function == m_GratingPV)
		*value = epicsInt32(readPositionFromMotor(pasynUser) + 0.5);
	else if (function == m_TurretPV)
		*value = m_turretNr;
	return status;
}

asynStatus ARC_USB::GratingDrive::writeInt32(asynUser *pasynUser, epicsInt32 value)
{
	int function = pasynUser->reason;
	asynStatus status = asynSuccess;
	if (function == m_GratingPV)
		startMovement(pasynUser, value);
	return status;
}

class ARC_USB::ExitMirror : public Drive
{
public:
	// Mirror Position 1 … motorized entrance diverter mirror
	// Mirror Position 2 … motorized exit diverter mirror
	// Mirror Position 3 … motorized entrance diverter on a double slave unit
	// Mirror Position 4 … motorized exit diverter on a double slave unit
	enum MirrorTypes { EntanceMirror = 1, FrontExitMirror };
	enum EMirrorPosition { mpFront = 0, mpSide = 1 };

	explicit ExitMirror(ARC_USB* parent) :
		Drive(parent) {
		parent->createParam("MIRROR", asynParamInt32, &m_MirrorPV);
	}
	asynStatus writeInt32(asynUser *pasynUser, epicsInt32 value);
	asynStatus readInt32(asynUser *pasynUser, epicsInt32 *value);
private:
	int m_MirrorPV;
};

class ARC_USB::SlitWidth : public Drive
{
public:
	// Slit Port 1 … Side entrance slit
	// Slit Port 2 … Front entrance slit
	// Slit Port 3 … Front exit slit
	// Slit Port 4 … Side exit slit
	// Slit Port 5 … Side entrance slit on a double slave unit
	// Slit Port 6 … Front entrance slit on a double slave unit
	// Slit Port 7 … Front exit slit on a double slave unit
	// Slit Port 8 … Side exit slit on a double slave unit
	enum SlitTypes { SideEntanceSlit = 1, FrontEntranceSlit, FrontExitSlit, SideExitSlit };
	SlitWidth(ARC_USB* parent) :
		Drive(parent) {
		parent->createParam("EXITSLITWIDTH", asynParamFloat64, &m_ExitSlitWidth);
		parent->createParam("ENTRYSLITWIDTH", asynParamFloat64, &m_EntrySlitWidth);
	}
	asynStatus writeInt32(asynUser *pasynUser, epicsInt32 value);
	asynStatus readInt32(asynUser *pasynUser, epicsInt32 *value);
private:
	int m_ExitSlitWidth;
	int m_EntrySlitWidth;
};

asynStatus ARC_USB::SlitWidth::writeInt32(asynUser *pasynUser, epicsInt32 value)
{
	int function = pasynUser->reason;
	asynStatus status = asynSuccess;
	if (function == m_ExitSlitWidth)
	{
		if (parent()->isMovableSlit(pasynUser, FrontExitSlit))
			parent()->ARC_set_Mono_Slit_Width(pasynUser, FrontExitSlit, value);
		else
			parent()->ARC_set_Mono_Slit_Width(pasynUser, SideExitSlit, value);
	}
	else if (function == m_EntrySlitWidth)
	{
		if (parent()->isMovableSlit(pasynUser, SideEntanceSlit))
			parent()->ARC_set_Mono_Slit_Width(pasynUser, SideEntanceSlit, value);
		else
			parent()->ARC_set_Mono_Slit_Width(pasynUser, FrontEntranceSlit, value);
	}
	return status;
}

asynStatus ARC_USB::SlitWidth::readInt32(asynUser *pasynUser, epicsInt32 *value)
{
	int function = pasynUser->reason;
	asynStatus status = asynSuccess;
	if (function == m_ExitSlitWidth)
	{
		if (parent()->isMovableSlit(pasynUser, FrontExitSlit))
			*value = parent()->ARC_get_Mono_Slit_Width(FrontExitSlit, pasynUser);
		else
			*value = parent()->ARC_get_Mono_Slit_Width(SideExitSlit, pasynUser);
	}
	else if (function == m_EntrySlitWidth)
	{
		if (parent()->isMovableSlit(pasynUser, SideEntanceSlit))
			*value = parent()->ARC_get_Mono_Slit_Width(SideEntanceSlit, pasynUser);
		else
			*value = parent()->ARC_get_Mono_Slit_Width(FrontEntranceSlit, pasynUser);
	}
	return status;
}

#ifndef _M_X64
/* LibraryNotLoaded is used to ensure that the DLL file is loaded only
 * the first time that the constructor is called.
 */
bool ARC_USB::m_LibraryNotLoaded = true;
#endif

/* Constructr
 * . loads DLL library file if required.
 * . initializes MotorSpecs
 */

//////////////////////////////////////////////////////////////////////////////////////
//																			        //
//	Construction/Destruction														//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
ARC_USB::ARC_USB(const char* portName, int MonoSerial) :
	asynPortDriver(portName, maxAddr, 1, 
		asynDrvUserMask | asynInt32Mask | asynFloat64Mask,
		ASYN_MULTIDEVICE | ASYN_CANBLOCK, 1, 0, 0)
{
	createParam("WAVELENGTH", asynParamFloat64, &m_WavelengthPV);
	createParam("SCANRATE", asynParamFloat64, &m_ScanRatePV);
	createParam("MODEL", asynParamOctet, &m_ModelPV);
	createParam("SERIAL", asynParamOctet, &m_SerialPV);
	createParam("MOVING", asynParamInt32, &m_MovingPV);

#ifndef _M_X64
	if (m_LibraryNotLoaded) {
		if (Setup_ARC_Instrument_dll() == false) {
			ThrowException("unable to load 'Acton\\ARC_Instrument.dll'", __FUNCTION__, __LINE__);
		}
		else {
			m_LibraryNotLoaded = false;
		}
	}
#endif

	// Initialize Handle to "not connected" value
	m_Handle = ARC_NULL_HANDLE;
	m_MonoSerial = MonoSerial;
	m_gratingDrive = NULL;
	m_exitMirror = NULL;
	m_slitWidth = NULL;

	if (!ARC_USB::connect(pasynUserSelf, MonoSerial))
		ThrowException("can't connect", __FUNCTION__, __LINE__);
}

ARC_USB::~ARC_USB(){
	delete m_gratingDrive;
	delete m_exitMirror;
	delete m_slitWidth;
	ARC_USB::disConnect(pasynUserSelf);
}

//////////////////////////////////////////////////////////////////////////////////////
//																			        //
// void ARC_USB::ThrowException(long code, std::string const& Details,			//
//		std::string const& While, long Line, bool ErrorToWarning = false) const		//
//																			        //
//////////////////////////////////////////////////////////////////////////////////////
void ARC_USB::ThrowException(std::string const& Details, std::string const& While, long Line) const
{
	throw Exception(Details, While, Line);
}

#ifdef _M_X64
void ARC_USB::ThrowException(asynUser *pasynUser, long code, std::string const& While, long Line, bool ErrorToWarning /*=false*/) const
{
	if (ErrorToWarning)
	{
		asynPrint(pasynUser, ASYN_TRACE_ERROR, "%s\n", Exception::GetDetails(code, While, Line).c_str());
	}
	else
	{
		const_cast<ARC_USB*>(this)->disConnect(pasynUser);
		throw Exception(code, While, Line);
	}
}
#endif

//////////////////////////////////////////////////////////////////////////////////////
//																			        //
//	bool ARC_USB::isConnected() const												//
//																					//
//	Description:																	//
//		Overridden IConnectable method												//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
bool ARC_USB::isConnected() const{
	return m_Handle != ARC_NULL_HANDLE;
}

//////////////////////////////////////////////////////////////////////////////////////
//																			        //
//	void ARC_USB::disConnect()														//
//																					//
//	Description:																	//
//		Overridden IConnectable method												//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
std::string ARC_USB::disConnect(asynUser* pasynUser)
{
	if (isConnected())
	{
		delete m_gratingDrive;
		delete m_exitMirror;
		delete m_slitWidth;
		ARC_Close_Enum(pasynUser);
	}
	return "";
}

//////////////////////////////////////////////////////////////////////////////////////
//																			        //
//	bool ARC_USB::connect(unsigned long timeOut = DefaultTimeout)					//
//																					//
//	Description:																	//
//		Overridden IConnectable method												//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
bool ARC_USB::connect(asynUser* pasynUser, unsigned long timeOut)
{
	timed_lock_guard ML(m_Mutex, timeOut);
	if (!ML.isLocked())
	{
		asynPrint(pasynUser, ASYN_TRACE_WARNING, "Unable to acquire mutex\n");
		return false;
	}

	bool OK = false;
	// Search devices
	long Total=ARC_Search_For_Inst();
	if(Total == 0)
		ThrowException("no devices found", __FUNCTION__, __LINE__);
	asynPrint(pasynUser, ASYN_TRACEIO_DEVICE, "%d devices found\n", Total);
	if (m_MonoSerial == 0)
	{
		if (Total > 1)
			ThrowException("More than one device found", __FUNCTION__, __LINE__);
		// Assuming only one device attached, so we directly open the first
		// one, that has therefore code ID 0.
		OK = ARC_Open_Mono(pasynUser, 0);
	}
	else if (m_MonoSerial <= 9)
	{
		OK = ARC_Open_Mono_Port(pasynUser, m_MonoSerial);
	}
	else for (long Enum_Num = 0; (Enum_Num < Total) && (!OK); Enum_Num++)
	{
		if (ARC_Open_Mono(pasynUser, Enum_Num))
		{
			if (ARC_get_Mono_Serial_int32(pasynUser) != m_MonoSerial)
				ARC_Close_Enum(pasynUser);
			else
				OK = true;
		}
	}
	//grating
	m_gratingDrive = new GratingDrive(this);
	bool canChangeGrating = (m_gratingDrive->gratings().size() > 1);

	//exit mirror
	m_exitMirror = NULL;
	if (canChangeExitMirror(pasynUserSelf)) {
		m_exitMirror = new ExitMirror(this);
	}

	// slit width
	m_slitWidth = NULL;
	if (canChangeSlitWidth(pasynUserSelf)) {
		m_slitWidth = new SlitWidth(this);
	}

	return OK;
}

//////////////////////////////////////////////////////////////////////////////////////
//																			        //
//	double ARC_USB::startMovement(double position, float speed)					//
//																					//
//	Description:																	//
//		overriden AbstractMotorControl method										//
//		The required feature is a simple Goto(position) command which is performed  //
//		by the monochromator always at maximum speed.								//		
//		As consequence, the movement ignores speed.									//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
double ARC_USB::startMovement(asynUser* pasynUser, double position)
{
	setisMoving(true);
	ARC_set_Mono_Wavelength_nm(pasynUser, position);
	return position;
}

//////////////////////////////////////////////////////////////////////////////////////
//																			        //
//	void ARC_USB::unplanedMovementStop()											//
//																					//
//	Description:																	//
//		overriden AbstractMotorControl method										//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
void ARC_USB::unplanedMovementStop(asynUser* pasynUser)
{
	double Wavelength_nm;
	ARC_Mono_Scan_Done(pasynUser, Wavelength_nm);
	ARC_set_Mono_Wavelength_nm(pasynUser, Wavelength_nm);
}

asynStatus ARC_USB::readOctet(asynUser *pasynUser, char *value, size_t maxChars,
	size_t *nActual, int *eomReason)
{
	int function = pasynUser->reason;
	asynStatus status = asynSuccess;
	if (function == m_ModelPV)
	{
		strncpy(value, m_MonoModel.c_str(), maxChars-1);
	}
	else if (function == m_SerialPV)
	{
		snprintf(value, maxChars - 1, "%d", m_MonoSerial);
	}
	else
		status = asynPortDriver::readOctet(pasynUser, value, maxChars, nActual, eomReason);
	return status;
}

//////////////////////////////////////////////////////////////////////////////////////
//																			        //
//	double ARC_USB::getPosition()													//
//																					//
//	Description:																	//
//		overriden AbstractMotorControl method										//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
asynStatus ARC_USB::readFloat64(asynUser *pasynUser, epicsFloat64 *value)
{
	int function = pasynUser->reason;
	asynStatus status = asynSuccess;
	if (function == m_WavelengthPV)
	{
		double Wavelength_nm = 0;
		bool done = ARC_Mono_Scan_Done(pasynUser, Wavelength_nm);
		if (done)
			setisMoving(false);
		*value = Wavelength_nm;
	}
	else if (function == m_ScanRatePV)
	{
		*value = ARC_get_Mono_Init_ScanRate_nm(pasynUser);
	}
	else
		status = asynPortDriver::readFloat64(pasynUser, value);
	return status;
}

asynStatus ARC_USB::readInt32(asynUser *pasynUser, epicsInt32 *value)
{
	asynStatus status = asynSuccess;
	if (m_gratingDrive)
		status = m_gratingDrive->readInt32(pasynUser, value);
	if ((status != asynSuccess) && (m_exitMirror))
		status = m_exitMirror->readInt32(pasynUser, value);
	if ((status != asynSuccess) && (m_slitWidth))
		m_slitWidth->readInt32(pasynUser, value);
	if (status != asynSuccess)
		status = asynPortDriver::readInt32(pasynUser, value);
	return status;
}

asynStatus ARC_USB::writeInt32(asynUser *pasynUser, epicsInt32 value)
{
	asynStatus status = asynSuccess;
	if (m_gratingDrive)
		status = m_gratingDrive->writeInt32(pasynUser, value);
	if ((status != asynSuccess) && (m_exitMirror))
		status = m_exitMirror->writeInt32(pasynUser, value);
	if ((status != asynSuccess) && (m_slitWidth))
		m_slitWidth->writeInt32(pasynUser, value);
	if (status != asynSuccess)
		status = asynPortDriver::writeInt32(pasynUser, value);
	return status;
}

asynStatus ARC_USB::writeFloat64(asynUser *pasynUser, epicsFloat64 value)
{
	int function = pasynUser->reason;
	asynStatus status = asynSuccess;
	if (function == m_WavelengthPV)
	{
		startMovement(pasynUser, value);
	}
	else if (function == m_ScanRatePV)
	{
		ARC_set_Mono_Init_ScanRate_nm(pasynUser, value);
	}
	else
		status = asynPortDriver::writeFloat64(pasynUser, value);
	return status;
}

asynStatus ARC_USB::readEnum(asynUser *pasynUser, char *strings[], int values[], int severities[],
	size_t nElements, size_t *nIn)
{
	asynStatus status = asynSuccess;
	if (m_gratingDrive)
		status = m_gratingDrive->readEnum(pasynUser, strings, values, severities, nElements, nIn);
	if (status != asynSuccess)
		status = asynPortDriver::readEnum(pasynUser, strings, values, severities, nElements, nIn);
	return status;
}

void ARC_USB::setisMoving(bool isMoving)
{
	m_isMoving = isMoving;
	setIntegerParam(m_MovingPV, isMoving ? 1 : 0);
	callParamCallbacks();
}

//////////////////////////////////////////////////////////////////////////////////////
//																			        //
//	void ARC_USB::canChangeExitMirror(EMirrorPosition newPos)						//
//																					//
//	Description:																	//
//		overriden CSpectrometerImpl method											//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
bool ARC_USB::canChangeExitMirror(asynUser* pasynUser) const
{
	bool canChangeExitMirror = false;
	for (long Mirror_Pos = 1; Mirror_Pos <= 4; Mirror_Pos += 1)
		canChangeExitMirror |= isMovableMirror(pasynUser, Mirror_Pos);
	return canChangeExitMirror;
}

//////////////////////////////////////////////////////////////////////////////////////
//																			        //
//	void ARC_USB::setExitMirrorPos(EMirrorPosition newPos)							//
//																					//
//	Description:																	//
//		overriden CSpectrometerImpl method											//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
asynStatus ARC_USB::ExitMirror::writeInt32(asynUser* pasynUser, epicsInt32 value) {
	int function = pasynUser->reason;
	asynStatus status = asynSuccess;

	if (function == m_MirrorPV)
	{
		long mirror = 2;	// 2 means "exit mirror
		long position;
		switch (value) {
		case mpFront: position = 3; break;
		case mpSide: position = 4; break;
		default: _ASSERT(false);
		}
		parent()->ARC_set_Mono_Diverter_Pos(pasynUser, mirror, value);
	}
	return status;
}

//////////////////////////////////////////////////////////////////////////////////////
//																			        //
//	EMirrorPosition ARC_USB::getExitMirrorPos()										//
//																					//
//	Description:																	//
//		overriden CSpectrometerImpl method										//													//										//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
asynStatus ARC_USB::ExitMirror::readInt32(asynUser* pasynUser, epicsInt32* value) {
	int function = pasynUser->reason;
	asynStatus status = asynSuccess;

	long mirror = 2;	// 2 means "exit mirror"
	long position = parent()->ARC_get_Mono_Diverter_Pos(pasynUser, mirror);	// 3 means "front exit slit"

	EMirrorPosition MirrorPosition;

	if (function == m_MirrorPV) {
		switch (position) {
		case 3: MirrorPosition = mpFront; break;
		case 4: MirrorPosition = mpSide; break;
		default: _ASSERT(false);
			throw new ARC_USB::Exception("unable to read mirrorPos", __FUNCTION__, __LINE__);
		}
	}
	return status;
}


//////////////////////////////////////////////////////////////////////////////////////
//																			        //
//	int ARC_USB::getGrating() const												//
//																					//
//	Description:																	//
//		getting current grating value.												//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
double ARC_USB::GratingDrive::readPositionFromMotor(asynUser* pasynUser)
{
	int Grating = __max(0, parent()->ARC_get_Mono_Grating(pasynUser, m_Mutex)-1);
	int gratingLines = grating(Grating);
	return gratingLines;
};


//////////////////////////////////////////////////////////////////////////////////////
//																			        //
//	int ARC_USB::setGrating()														//
//																					//
//	Description:																	//
//		setting current grating value.												//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
double ARC_USB::GratingDrive::startMovement(asynUser* pasynUser, double targetPosition)
{
	int index = m_turretNr *3;
	int newGrating = int(0.5+targetPosition);
	for (int i = 0; i<3; i++)
	{
		if (grating(index+i) == newGrating)
		{
			m_gratingNr = index+i;
			parent()->ARC_set_Mono_Grating(pasynUser, m_gratingNr+1);
			double gratingFactor = ((1.0* newGrating)/(1.0* STD_GRATING)); // NB, not m_gratingFactor in the parent class.
			return targetPosition;
		}
	}
	//setting not possible due to lack of availability
	throw std::runtime_error("can't set the grating");
	return 0;
}

// slit widths
bool ARC_USB::canChangeSlitWidth(asynUser* pasynUser) const
{
	bool canChangeSlitWidth = false;
	for (long Slit_Pos = SlitWidth::SideEntanceSlit; Slit_Pos <= SlitWidth::SideExitSlit; Slit_Pos++)
		canChangeSlitWidth |= isMovableSlit(pasynUser, Slit_Pos);
	return canChangeSlitWidth;
}

bool ARC_USB::isMovableSlit(asynUser* pasynUser, long Slit_Pos) const
{
	bool isMovableSlit = false;
	enum ArcSlitTypes {
		NoSlit, ManualSlit, FixedSlitWidth, FocalPlaneAdapter, ContinuousMotor, FiberOptic, IndexableSlit, SpecialContinuousMotor = 9
	};
	ArcSlitTypes ArcSlitType = static_cast<ArcSlitTypes>(ARC_get_Mono_Slit_Type(pasynUser, Slit_Pos));
	if ((ArcSlitType == ContinuousMotor) || (ArcSlitType == IndexableSlit) || (ArcSlitType == SpecialContinuousMotor))
		isMovableSlit = true;
	return isMovableSlit;
}

bool ARC_USB::isMovableMirror(asynUser* pasynUser, long Mirror_Pos) const
{
	bool isMovableMirror = false;
	ARC_get_Mono_Diverter_Valid(pasynUser, Mirror_Pos);
	return isMovableMirror;
}

std::string ARC_USB::ARC_get_Mono_Model(asynUser* pasynUser) const
{
	char ModelStr[20];
	timed_lock_guard ML(m_Mutex, ShortTimeout);
	if (!ML.isLocked())
		asynPrint(pasynUser, ASYN_TRACE_WARNING, "Unable to obtain mutex while ARC_get_Mono_Model\n");

#ifdef _M_X64
	long Error_Code;
	if (!ARC_get_Mono_Model_CharStr(m_Handle, ModelStr, sizeof(ModelStr), &Error_Code))
		ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
	ARC_get_Mono_Model_CString(m_Handle, *ModelStr);
#endif
	return ModelStr;
}

long ARC_USB::ARC_get_Mono_Serial_int32(asynUser* pasynUser) const
{
	timed_lock_guard ML(m_Mutex, ShortTimeout); // Const access, no need to force mutex lock
	if (!ML.isLocked())
		asynPrint(pasynUser, ASYN_TRACE_WARNING, "Unable to obtain mutex while ARC_get_Mono_Serial_int32\n");
	long Mono_Serial;
#ifdef _M_X64
	long Error_Code;
	Mono_Serial = ::ARC_get_Mono_Serial_int32(m_Handle, &Error_Code);
	if (Error_Code)
		ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
	Mono_Serial = ::ARC_get_Mono_Serial_int32(m_Handle);
#endif
	return Mono_Serial;
}

long  ARC_USB::ARC_get_Mono_Grating_Max(asynUser* pasynUser, std::timed_mutex& Mutex) const
{
	long maxGratingNr = 0;
	timed_lock_guard ML(Mutex, ShortTimeout); // Const access, no need to force mutex lock
	if (!ML.isLocked())
		asynPrint(pasynUser, ASYN_TRACE_WARNING, "Unable to obtain mutex while ARC_get_Mono_Grating_Max\n");
#ifdef _M_X64
	long Error_Code;
	if (!::ARC_get_Mono_Grating_Max(m_Handle, &maxGratingNr, &Error_Code))
		ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
	if (!::ARC_get_Mono_Grating_Max(m_Handle, maxGratingNr))
		ThrowException("Could not get max grating", __FUNCTION__, __LINE__);
#endif
	return maxGratingNr;
}

long ARC_USB::ARC_get_Mono_Turret(asynUser* pasynUser, std::timed_mutex& Mutex) const
{
	long Turret;
	timed_lock_guard ML(Mutex, ShortTimeout); // Const access, no need to force mutex lock
	if (!ML.isLocked())
		asynPrint(pasynUser, ASYN_TRACE_WARNING, "Unable to obtain mutex while ARC_get_Mono_Turret\n");
#ifdef _M_X64
	long Error_Code;
	if (!::ARC_get_Mono_Turret(m_Handle, &Turret, &Error_Code))
		ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
	if (!::ARC_get_Mono_Turret(m_Handle, Turret))
		ThrowException("Could not get turret", __FUNCTION__, __LINE__);
#endif
	return Turret;
}

long ARC_USB::ARC_get_Mono_Turret_Max(asynUser* pasynUser, std::timed_mutex& Mutex) const
{
	long maxTurretNr = 0;
#ifdef _M_X64
	long Error_Code;
	if (!::ARC_get_Mono_Turret_Max(m_Handle, &maxTurretNr, &Error_Code))
		ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
	if (!::ARC_get_Mono_Turret_Max(m_Handle, maxTurretNr))
		ThrowException("Could not get max turret", __FUNCTION__, __LINE__);
#endif
	return maxTurretNr;
}

long ARC_USB::ARC_get_Mono_Grating_Density(asynUser* pasynUser, std::timed_mutex& Mutex, long Grating) const
{
	long Groove_MM = 0;
	timed_lock_guard ML(Mutex, ShortTimeout); // Const access, no need to force mutex lock
	if (!ML.isLocked())
		asynPrint(pasynUser, ASYN_TRACE_WARNING, "Unable to obtain mutex while ARC_get_Mono_Grating_Density\n");
#ifdef _M_X64
	long Error_Code;
	if (!::ARC_get_Mono_Grating_Density(m_Handle, Grating, &Groove_MM, &Error_Code))
		ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
	if (!::ARC_get_Mono_Grating_Density(m_Handle, Grating, Groove_MM))
		ThrowException("Could not get grating density", __FUNCTION__, __LINE__);
#endif
	return Groove_MM;
}

long ARC_USB::ARC_get_Mono_Grating(asynUser* pasynUser, std::timed_mutex& Mutex) const
{
	long Grating = 0;
	timed_lock_guard ML(Mutex, ShortTimeout); // Const access, no need to force mutex lock
	if (!ML.isLocked())
		asynPrint(pasynUser, ASYN_TRACE_WARNING, "Unable to obtain mutex while ARC_get_Mono_Grating\n");
#ifdef _M_X64
	long Error_Code;
	if (!::ARC_get_Mono_Grating(m_Handle, &Grating, &Error_Code))
		ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__, true);
#else
	::ARC_get_Mono_Grating(m_Handle, Grating);
#endif
	return Grating;
}

void ARC_USB::ARC_Close_Enum(asynUser* pasynUser)
{
	timed_lock_guard ML(m_Mutex, DefaultTimeout);
	if (!ML.isLocked())
		asynPrint(pasynUser, ASYN_TRACE_WARNING, "Unable to obtain mutex at ARC_Close_Enum()\n");
#ifdef _M_X64
	long Error_Code;
	if (!::ARC_Close_Enum(m_Handle, &Error_Code))
		asynPrint(pasynUser, ASYN_TRACE_ERROR, "%s\n", Exception::GetDetails(Error_Code, "ARC_Close_Enum", __LINE__).c_str());
#else
	if (!::ARC_Close_Enum(m_Handle))
	{
		asynPrint(pasynUser, ASYN_TRACE_ERROR, "Could not close handle\n");
	}
#endif
	m_Handle = ARC_NULL_HANDLE;
}

long ARC_USB::ARC_Search_For_Inst() const
{
	timed_lock_guard ML(m_Mutex, DefaultTimeout);
	if (!ML.isLocked())
		ThrowException("Unable to obtain mutex", __FUNCTION__, __LINE__);

	long total = 0;
#ifdef _M_X64
	if (!::ARC_Search_For_Inst(&total))
#else
	if (!::ARC_Search_For_Inst(total))
#endif
		ThrowException("failed to search for devices", __FUNCTION__, __LINE__);
	return total;
}

bool ARC_USB::ARC_Open_Mono(asynUser* pasynUser, long Enum_Num)
{
	timed_lock_guard ML(m_Mutex, DefaultTimeout);
	if (!ML.isLocked())
		ThrowException("Unable to obtain mutex", __FUNCTION__, __LINE__);
#ifdef _M_X64
	long Error_Code;
	bool OK = ::ARC_Open_Mono(Enum_Num, &m_Handle, &Error_Code);
	if (!OK)
		asynPrint(pasynUser, ASYN_TRACE_ERROR, "%s\n", Exception::GetDetails(Error_Code, __FUNCTION__, __LINE__).c_str());
	return OK;

#else
	return (::ARC_Open_Mono(Enum_Num, m_Handle) != 0);
#endif
}

bool  ARC_USB::ARC_Open_Mono_Port(asynUser* pasynUser, long comPort)
{
	timed_lock_guard ML(m_Mutex, DefaultTimeout);
	if (!ML.isLocked())
		ThrowException("Unable to obtain mutex", __FUNCTION__, __LINE__);
#ifdef _M_X64
	long Error_Code;
	bool OK = ::ARC_Open_Mono_Port(comPort, &m_Handle, &Error_Code);
	if (!OK)
		asynPrint(pasynUser, ASYN_TRACE_ERROR, "%s\n", Exception::GetDetails(Error_Code, __FUNCTION__, __LINE__).c_str());
	return OK;
#else
	return (::ARC_Open_Mono_Port(comPort, m_Handle) != 0);
#endif
}

void ARC_USB::ARC_set_Mono_Wavelength_nm(asynUser* pasynUser, double Wavelength)
{
	timed_lock_guard ML(m_Mutex, DefaultTimeout);
	if (!ML.isLocked())
		ThrowException("Unable to obtain mutex", __FUNCTION__, __LINE__);
#ifdef _M_X64
	long Error_Code;
	if (!::ARC_set_Mono_Wavelength_nm(m_Handle, Wavelength, &Error_Code))
		ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
	if (!::ARC_set_Mono_Wavelength_nm(m_Handle, Wavelength))
		ThrowException("Could not set wavelength", __FUNCTION__, __LINE__);
#endif
}

double ARC_USB::ARC_get_Mono_Init_ScanRate_nm(asynUser* pasynUser)
{
	timed_lock_guard ML(m_Mutex, DefaultTimeout);
	double ScanRate;
	if (!ML.isLocked())
		ThrowException("Unable to obtain mutex", __FUNCTION__, __LINE__);
#ifdef _M_X64
	long Error_Code;
	if (!::ARC_get_Mono_Init_ScanRate_nm(m_Handle, &ScanRate, &Error_Code))
		ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
	if (!::ARC_get_Mono_Init_ScanRate_nm(m_Handle, ScanRate))
		ThrowException("Could not get scan rate", __FUNCTION__, __LINE__);
#endif
	return ScanRate;
}

void ARC_USB::ARC_set_Mono_Init_ScanRate_nm(asynUser* pasynUser, double ScanRate)
{
	timed_lock_guard ML(m_Mutex, DefaultTimeout);
	if (!ML.isLocked())
		ThrowException("Unable to obtain mutex", __FUNCTION__, __LINE__);
#ifdef _M_X64
	long Error_Code;
	if (!::ARC_set_Mono_Init_ScanRate_nm(m_Handle, ScanRate, &Error_Code))
		ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
	if (!::ARC_set_Mono_Init_ScanRate_nm(m_Handle, ScanRate))
		ThrowException("Could not set scan rate", __FUNCTION__, __LINE__);
#endif
}

bool ARC_USB::ARC_Mono_Scan_Done(asynUser* pasynUser, double& WaveLength_nm) const
{
	timed_lock_guard ML(m_Mutex, ShortTimeout);
	if (!ML.isLocked())
	{
		WaveLength_nm = CurrentPosition();
		return isMoving();
	}

	bool Done_Moving = false;
#ifdef _M_X64
	long Error_Code;
	if (!::ARC_Mono_Scan_Done(m_Handle, &Done_Moving, &WaveLength_nm, &Error_Code))
	{
		asynPrint(pasynUser, ASYN_TRACE_ERROR, "%s\n", Exception::GetDetails(Error_Code, __FUNCTION__, __LINE__).c_str());
		return isMoving();
	}
#else
	long Done_MovingL;
	if (!::ARC_Mono_Scan_Done(m_Handle, Done_MovingL, WaveLength_nm))
	{
		asynPrint(pasynUser, ASYN_TRACE_WARNING, "Could not get wavelength\n");
		WaveLength_nm = CurrentPosition();
		return isMoving();
	}
	Done_Moving = (Done_MovingL != 0);
#endif
	if (m_MonoModel == "VM-748")
		// Hack workaround: this elderly model inorrectly reports the position in Angstroms.
		WaveLength_nm /= NM_to_Angstrom;
	return Done_Moving;
}

bool ARC_USB::ARC_get_Mono_Diverter_Valid(asynUser* pasynUser, long mirror) const
{
	timed_lock_guard ML(m_Mutex, ShortTimeout); // Const access, no need to force mutex lock
	if (!ML.isLocked())
		asynPrint(pasynUser, ASYN_TRACE_WARNING, "Unable to obtain mutex while ARC_get_Mono_Diverter_Valid\n");
#ifdef _M_X64
	long Error_Code;
	return ::ARC_get_Mono_Diverter_Valid(m_Handle, mirror, &Error_Code);
#else
	return (::ARC_get_Mono_Diverter_Valid(m_Handle, mirror) != 0);
#endif
}

void  ARC_USB::ARC_set_Mono_Diverter_Pos(asynUser* pasynUser, long Diverter_Num,long  Diverter_Pos)
{
	timed_lock_guard ML(m_Mutex, DefaultTimeout);
	if (!ML.isLocked())
		ThrowException("Unable to obtain mutex", __FUNCTION__, __LINE__);
#ifdef _M_X64
	long Error_Code = 0;
	if (!::ARC_set_Mono_Diverter_Pos(m_Handle, Diverter_Num, Diverter_Pos, &Error_Code))
		ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
	if (!::ARC_set_Mono_Diverter_Pos(m_Handle, Diverter_Num, Diverter_Pos))
		ThrowException("Could not set divertor position", __FUNCTION__, __LINE__);
#endif
}

long ARC_USB::ARC_get_Mono_Diverter_Pos(asynUser* pasynUser, long Diverter_Num) const
{
	long  Diverter_Pos;
	timed_lock_guard ML(m_Mutex, ShortTimeout); // Const access, no need to force mutex lock
	if (!ML.isLocked())
		asynPrint(pasynUser, ASYN_TRACE_WARNING, "Unable to obtain mutex while ARC_get_Mono_Diverter_Pos\n");
#ifdef _M_X64
	long Error_Code = 0;
	if (!::ARC_get_Mono_Diverter_Pos(m_Handle, Diverter_Num, &Diverter_Pos, &Error_Code))
		ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
	if (!::ARC_get_Mono_Diverter_Pos(m_Handle, Diverter_Num, Diverter_Pos))
		ThrowException("Could not get divertor position", __FUNCTION__, __LINE__);
#endif
	return Diverter_Pos;
}

void ARC_USB::ARC_set_Mono_Grating(asynUser* pasynUser, long Grating)
{
	timed_lock_guard ML(m_Mutex, DefaultTimeout);
	if (!ML.isLocked())
		ThrowException("Unable to obtain mutex", __FUNCTION__, __LINE__);
#ifdef _M_X64
	long Error_Code = 0;
	if (!::ARC_set_Mono_Grating(m_Handle, Grating, &Error_Code))
		ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
	if (!::ARC_set_Mono_Grating(m_Handle, Grating))
		ThrowException("Could not set grating", __FUNCTION__, __LINE__);
#endif
}

long ARC_USB::ARC_get_Mono_Slit_Type(asynUser* pasynUser, long Slit_Pos) const
{
	timed_lock_guard ML(m_Mutex, ShortTimeout); // Const access, no need to force mutex lock
	if (!ML.isLocked())
		asynPrint(pasynUser, ASYN_TRACE_WARNING, "Unable to obtain mutex while ARC_get_Mono_Slit_Type\n");
	long Slit_Type;
#ifdef _M_X64
	long Error_Code = 0;
	if (!::ARC_get_Mono_Slit_Type(m_Handle, Slit_Pos, &Slit_Type, &Error_Code))
		ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
	if (!::ARC_get_Mono_Slit_Type(m_Handle, Slit_Pos, Slit_Type))
		ThrowException("Could not get slit type", __FUNCTION__, __LINE__);
#endif
		return Slit_Type;
}

void  ARC_USB::ARC_set_Mono_Slit_Width(asynUser* pasynUser, long Slit_Pos, long Slit_Width)
{
	timed_lock_guard ML(m_Mutex, DefaultTimeout);
	if (!ML.isLocked())
		ThrowException("Unable to obtain mutex", __FUNCTION__, __LINE__);
#ifdef _M_X64
	long Error_Code = 0;
	if (!::ARC_set_Mono_Slit_Width(m_Handle, Slit_Pos,  Slit_Width, &Error_Code))
		ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
	if (!::ARC_set_Mono_Slit_Width(m_Handle, Slit_Pos,  Slit_Width))
		ThrowException("Could not set slit width", __FUNCTION__, __LINE__);
#endif
}

long ARC_USB::ARC_get_Mono_Slit_Width(long Slit_Pos, asynUser* pasynUser) const
{
	timed_lock_guard ML(m_Mutex, DefaultTimeout); // Const access, no need to force mutex lock
	if (!ML.isLocked())
		asynPrint(pasynUser, ASYN_TRACE_WARNING, "Unable to obtain mutex while ARC_get_Mono_Slit_Width\n");
	long Slit_Width;
#ifdef _M_X64
	long Error_Code = 0;
	if (!::ARC_get_Mono_Slit_Width(m_Handle, Slit_Pos,  &Slit_Width, &Error_Code))
		ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
	if (!::ARC_get_Mono_Slit_Width(m_Handle, Slit_Pos,  Slit_Width))
		ThrowException("Could not get slit width", __FUNCTION__, __LINE__);
#endif
	return Slit_Width;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//																								//
//	static void ARC_InstrumentPortDriverConfigure(const iocshArgBuf *args)						//
//																								//
//	Description:																				//
//		This function will be invoked when from the st.cmd starup script.						//
//		It creates the object and also schedules the exit event.								//
//																								//
//	Parameters:																					//
//		asynPortName. This is the Asyn port name (e.g. ARC_Instrument).							//
//		monoSerial. This will be the serial number of of desired instrument (0 for any).		//
//																								//
//////////////////////////////////////////////////////////////////////////////////////////////////
void ARC_USB::ARC_InstrumentPortDriverConfigure(const iocshArgBuf *args)
{
	try {
		const char* asynPortName = args[0].sval;
		int monoSerial = atoi(args[1].sval);
		Motors::ARC_USB* Instance = new Motors::ARC_USB(asynPortName, monoSerial);
		epicsAtExit(ARC_InstrumentExitFunc, Instance);
	}
	catch (Exception const& E) {
		fprintf(stderr, "%s\n", E.what());
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//																								//
//	void ARC_InstrumentExitFunc(void * param)														//
//																								//
//	Description:																				//
//		This function will be invoked when the IOC exits.										//
//		In order to not leak resources, it destroys the object that's been created.				//
//																								//
//////////////////////////////////////////////////////////////////////////////////////////////////
void ARC_USB::ARC_InstrumentExitFunc(void * param)
{
	Motors::ARC_USB* Instance = static_cast<Motors::ARC_USB*>(param);
	delete Instance;
}

} // namespace Motors

static const iocshArg initArg0 = { "asynPortName", iocshArgString };
static const iocshArg initArg1 = { "monoSerial", iocshArgString };
static const iocshArg * const initArgs[] = { &initArg0, &initArg1 };
static const iocshFuncDef initFuncDef = { "ARC_InstrumentPortDriverConfigure",2,initArgs };

//////////////////////////////////////////////////////////////////////////////////////////////////
//																								//
//	static void ARC_InstrumentRegistrar(void)														//
//																								//
//	Description:																				//
//		Registers the functions to be called within the IOC.									//
//																								//
//////////////////////////////////////////////////////////////////////////////////////////////////
static void ARC_InstrumentRegistrar(void)
{
	iocshRegister(&initFuncDef, Motors::ARC_USB::ARC_InstrumentPortDriverConfigure);
}

extern "C" {

	epicsExportRegistrar(ARC_InstrumentRegistrar);

}


//EOF ========================================================================
