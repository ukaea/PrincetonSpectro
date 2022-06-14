//////////////////////////////////////////////////////////////////////////////////////////////////////
//																									//
//	Module:																							//
//		ARC_USB.cpp																					//
//																									//
//	Description:																					//
//		Implements the ARC_USB class.																//
//		This uses AsynPortDriver and asynOctetSyncIO to control an Acton spectrometer.				//
// 		See, for example, https://www.princetoninstruments.com/products/acton-ls-family/acton-ls	//
//																									//
//	Author:  Peter Heesterman (Tessella plc). Date: 26 Aug 2021.									//
//																									//
//	ARC_InstrumentApp is distributed subject to a Software License Agreement						//
//	found in file LICENSE that is included with this distribution.									//
//																									//
//////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER
#pragma warning(disable:4250)
#pragma warning(disable:4996)
#endif

#include <vector>
#include <string.h>

#ifdef _M_X64
#include "../Acton/ARC_Instrument_x64.h"
#else
#include "../Acton/ARC_Instrument_dll.h"
#endif

#include <iocsh.h>
#include <epicsExit.h>
#include <asynDriver.h>

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
        char Error_Str[_MAX_PATH + 1];
        ARC_Error_To_English(code, Error_Str, sizeof(Error_Str) - 1);
        return std::string(Error_Str) + " while " + While;
    }
#endif
    Exception(std::string const& Details, std::string const& While, long Line) :
        std::runtime_error(Details + " while " + While) {
    }

};

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
    asynPortDriver(portName, 1, Mask(), Mask(),
        ASYN_CANBLOCK, 1, 0, 0)
{
    asynStatus status = createParam("WAVELENGTH", asynParamFloat64, &m_WavelengthPV);
    if (status == asynSuccess)
        status = createParam("SCANRATE", asynParamFloat64, &m_ScanRatePV);
    if (status == asynSuccess)
        status = createParam("MODEL", asynParamOctet, &m_ModelPV);
    if (status == asynSuccess)
        status = createParam("SERIAL", asynParamOctet, &m_SerialPV);
    if (status == asynSuccess)
        status = createParam("MOVING", asynParamInt32, &m_MovingPV);
    if (status == asynSuccess)
        status = createParam("GRATING", asynParamInt32, &m_GratingPV);
    if (status == asynSuccess)
        status = createParam("TURRET", asynParamInt32, &m_TurretPV);
    if (status == asynSuccess)
        status = createParam("MIRROR", asynParamInt32, &m_MirrorPV);
    if (status == asynSuccess)
        status = createParam("EXITSLITWIDTH", asynParamInt32, &m_ExitSlitWidthPV);
    if (status == asynSuccess)
        status = createParam("ENTRYSLITWIDTH", asynParamInt32, &m_EntrySlitWidthPV);
    if (status != asynSuccess)
        ThrowException(pasynUserSelf, "Could not create PVs", __FUNCTION__, __LINE__);

    // Initialize Handle to "not connected" value
    m_Handle = ARC_NULL_HANDLE;
#ifndef _M_X64
    if (m_LibraryNotLoaded) {
        char CurrentDirectory[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, CurrentDirectory);
        if (Setup_ARC_Instrument_dll() == false) {
            ThrowException(pasynUserSelf, "unable to load 'Acton\\ARC_Instrument.dll'", __FUNCTION__, __LINE__);
        }
        else {
            m_LibraryNotLoaded = false;
        }
    }
#endif

    m_MonoSerial = MonoSerial;

    timed_lock_guard ML(m_Mutex, DefaultTimeout);
    if (!ML.isLocked())
        asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, "Unable to acquire mutex\n");
    else if (connect(pasynUserSelf) != asynSuccess)
        asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, "can't connect\n");
}

ARC_USB::~ARC_USB() {
    ARC_USB::disConnect(pasynUserSelf);
}

int ARC_USB::Mask()
{
    return asynDrvUserMask | asynInt32Mask | asynFloat64Mask | asynOctetMask | asynEnumMask;
}

//////////////////////////////////////////////////////////////////////////////////////
//																			        //
// void ARC_USB::ThrowException(long code, std::string const& Details,			//
//		std::string const& While, long Line, bool ErrorToWarning = false) const		//
//																			        //
//////////////////////////////////////////////////////////////////////////////////////
void ARC_USB::ThrowException(asynUser *pasynUser, std::string const& Details, std::string const& While, long Line) const
{
    const_cast<ARC_USB*>(this)->disConnect(pasynUser);
    throw Exception(Details, While, Line);
}

#ifdef _M_X64
void ARC_USB::ThrowException(asynUser *pasynUser, long code, std::string const& While, long Line) const
{
    const_cast<ARC_USB*>(this)->disConnect(pasynUser);
    throw Exception(code, While, Line);
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
bool ARC_USB::isConnected() const {
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
        ARC_Close_Enum(pasynUser);
    }
    return "";
}

//////////////////////////////////////////////////////////////////////////////////////
//																			        //
//	bool ARC_USB::connect(asynUser* pasynUser)										//
//																					//
//	Description:																	//
//		Overridden IConnectable method												//
//																					//
//////////////////////////////////////////////////////////////////////////////////////
asynStatus ARC_USB::connect(asynUser* pasynUser)
{
    asynStatus status = asynError;
    // Search devices
    long Total = ARC_Search_For_Inst(pasynUser);
    if (Total == 0)
    {
        asynPrint(pasynUser, ASYN_TRACE_ERROR, "no devices found\n");
        return asynError;
    }
    asynPrint(pasynUser, ASYN_TRACEIO_DEVICE, "%d devices found\n", Total);
    if (m_MonoSerial == 0)
    {
        if (Total > 1)
        {
            asynPrint(pasynUser, ASYN_TRACE_ERROR, "More than one device found\n");
            return asynError;
        }
        // Assuming only one device attached, so we directly open the first
        // one, that has therefore code ID 0.
        if (ARC_Open_Mono(pasynUser, 0))
            status = asynSuccess;
    }
    else for (long Enum_Num = 0; (Enum_Num < Total) && (status == asynError); Enum_Num++)
    {
        if (ARC_Open_Mono(pasynUser, Enum_Num))
        {
            if (ARC_get_Mono_Serial_int32(pasynUser) != m_MonoSerial)
                ARC_Close_Enum(pasynUser);
            else
                status = asynSuccess;
        }
    }
    //grating
    if (status == asynSuccess)
    {
        m_MonoModel = ARC_get_Mono_Model(pasynUser);
        m_MonoSerial = ARC_get_Mono_Serial_int32(pasynUser);
    }
    long maxGratingNr = ARC_get_Mono_Grating_Max(pasynUserSelf);
    m_gratings.resize(maxGratingNr);
    for (size_t i = 0; i < m_gratings.size(); i++) {
        long grating = ARC_get_Mono_Grating_Density(pasynUserSelf, long(i + 1));
        m_gratings[i] = grating;
    }
    m_gratingNr = ARC_get_Mono_Grating(pasynUserSelf) - 1;
    m_turretNr = ARC_get_Mono_Turret(pasynUserSelf) - 1;
    m_maxTurret = ARC_get_Mono_Turret_Max(pasynUserSelf);

    return status;
}

asynStatus ARC_USB::readOctet(asynUser *pasynUser, char *value, size_t maxChars,
    size_t *nActual, int *eomReason)
{
    timed_lock_guard ML(m_Mutex, DefaultTimeout);
    if (!ML.isLocked())
    {
        asynPrint(pasynUser, ASYN_TRACE_WARNING, "Unable to acquire mutex\n");
        return asynTimeout;
    }
    asynStatus status = asynSuccess;
    if (!isConnected())
    {
        status = connect(pasynUser);
        if (status != asynSuccess)
            return status;
    }
    int function = pasynUser->reason;
    if (function == m_ModelPV)
    {
        strncpy(value, m_MonoModel.c_str(), maxChars - 1);
        *nActual = m_MonoModel.size();
    }
    else if (function == m_SerialPV)
    {
        snprintf(value, maxChars - 1, "%d", m_MonoSerial);
        *nActual = strlen(value);
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
    timed_lock_guard ML(m_Mutex, ShortTimeout);
    if (!ML.isLocked())
    {
        asynPrint(pasynUser, ASYN_TRACE_WARNING, "Unable to acquire mutex\n");
        return asynTimeout;
    }
    asynStatus status = asynSuccess;
    if (!isConnected())
    {
        status = connect(pasynUser);
        if (status != asynSuccess)
            return status;
    }
    int function = pasynUser->reason;
    if (function == m_WavelengthPV)
    {
        double Wavelength_nm = 0;
        bool done = ARC_Mono_Scan_Done(pasynUser, Wavelength_nm);
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

epicsInt32 ARC_USB::getgratingLines(asynUser* pasynUser)
{
    m_gratingNr = ARC_get_Mono_Grating(pasynUser) - 1;
    int gratingLines = m_gratings[m_gratingNr];
    return gratingLines;
}

ARC_USB::EMirrorPosition ARC_USB::getMirrorPosition(asynUser* pasynUser)
{
    EMirrorPosition MirrorPosition;
    long mirror = 2;	// 2 means "exit mirror"
    long position = ARC_get_Mono_Diverter_Pos(pasynUser, mirror);	// 3 means "front exit slit"
    switch (position) {
        case 3: MirrorPosition = mpFront; break;
        case 4: MirrorPosition = mpSide; break;
        default:
            throw new ARC_USB::Exception("unable to read mirrorPos", __FUNCTION__, __LINE__);
    }
    return MirrorPosition;
}

asynStatus ARC_USB::getExitSlitPosition(asynUser* pasynUser, epicsInt32 *value)
{
    asynStatus status = asynSuccess;
    if (isMovableSlit(pasynUser, FrontExitSlit))
        *value = ARC_get_Mono_Slit_Width(FrontExitSlit, pasynUser);
    else if (isMovableSlit(pasynUser, SideExitSlit))
        *value = ARC_get_Mono_Slit_Width(SideExitSlit, pasynUser);
    else
        status = asynDisabled;
    return status;
}

asynStatus ARC_USB::getEntrySlitPosition(asynUser* pasynUser, epicsInt32 *value)
{
    asynStatus status = asynSuccess;
    if (isMovableSlit(pasynUser, SideEntanceSlit))
        *value = ARC_get_Mono_Slit_Width(SideEntanceSlit, pasynUser);
    else if (isMovableSlit(pasynUser, SideEntanceSlit))
        *value = ARC_get_Mono_Slit_Width(FrontEntranceSlit, pasynUser);
    else
        status = asynDisabled;
    return status;
}

asynStatus ARC_USB::readInt32(asynUser *pasynUser, epicsInt32 *value)
{
    timed_lock_guard ML(m_Mutex, ShortTimeout);
    if (!ML.isLocked())
    {
        asynPrint(pasynUser, ASYN_TRACE_WARNING, "Unable to acquire mutex\n");
        return asynTimeout;
    }
    asynStatus status = asynSuccess;
    if (!isConnected())
    {
        status = connect(pasynUser);
        if (status != asynSuccess)
            return status;
    }
    int function = pasynUser->reason;
    if (function == m_GratingPV)
    {
        *value = getgratingLines(pasynUser);
    }
    else if (function == m_TurretPV)
    {
        *value = m_turretNr;
    }
    else if (function == m_MirrorPV)
    {
        *value = getMirrorPosition(pasynUser);
    }
    else if (function == m_ExitSlitWidthPV)
    {
        status = getExitSlitPosition(pasynUser, value);
    }
    else if (function == m_EntrySlitWidthPV)
    {
        status = getEntrySlitPosition(pasynUser, value);
    }
    else if (function == m_MovingPV)
    {
        double Wavelength_nm = 0;
        bool done = ARC_Mono_Scan_Done(pasynUser, Wavelength_nm);
        *value = done ? 0 : 1;
        setDoubleParam(m_WavelengthPV, Wavelength_nm);
        setDoubleParam(m_ScanRatePV, ARC_get_Mono_Init_ScanRate_nm(pasynUser));
        setIntegerParam(m_GratingPV, getgratingLines(pasynUser));
        setIntegerParam(m_MirrorPV, getMirrorPosition(pasynUser));
        epicsInt32 SlitPosition;
        if (getExitSlitPosition(pasynUser, &SlitPosition)==asynSuccess)
            setIntegerParam(m_ExitSlitWidthPV, SlitPosition);
        if (getEntrySlitPosition(pasynUser, &SlitPosition)==asynSuccess)
            setIntegerParam(m_ExitSlitWidthPV, SlitPosition);
        callParamCallbacks();
    }
    else
        status = asynPortDriver::readInt32(pasynUser, value);
    return status;
}

asynStatus ARC_USB::writeInt32(asynUser *pasynUser, epicsInt32 value)
{
    timed_lock_guard ML(m_Mutex, DefaultTimeout);
    if (!ML.isLocked())
    {
        asynPrint(pasynUser, ASYN_TRACE_WARNING, "Unable to acquire mutex\n");
        return asynTimeout;
    }
    asynStatus status = asynSuccess;
    if (!isConnected())
    {
        status = connect(pasynUser);
        if (status != asynSuccess)
            return status;
    }
    int function = pasynUser->reason;
    if (function == m_GratingPV)
    {
        int index = m_turretNr * 3;
        for (int i = 0; i < 3; i++)
        {
            if (m_gratings[index + i] == value)
            {
                m_gratingNr = index + i;
                ARC_set_Mono_Grating(pasynUser, m_gratingNr + 1);
                double gratingFactor = ((1.0* value) / (1.0* STD_GRATING)); // NB, not m_gratingFactor in the parent class.
            }
        }
    }
    else if (function == m_MirrorPV)
    {
        status = asynSuccess;
        long mirror = 2;	// 2 means "exit mirror
        long position;
        switch (value) {
        case mpFront: position = 3; break;
        case mpSide: position = 4; break;
        default: assert(false);
        }
        ARC_set_Mono_Diverter_Pos(pasynUser, mirror, value);
    }
    else if (function == m_ExitSlitWidthPV)
    {
        if (isMovableSlit(pasynUser, FrontExitSlit))
            ARC_set_Mono_Slit_Width(pasynUser, FrontExitSlit, value);
        else
            ARC_set_Mono_Slit_Width(pasynUser, SideExitSlit, value);
    }
    else if (function == m_EntrySlitWidthPV)
    {
        if (isMovableSlit(pasynUser, SideEntanceSlit))
            ARC_set_Mono_Slit_Width(pasynUser, SideEntanceSlit, value);
        else
            ARC_set_Mono_Slit_Width(pasynUser, FrontEntranceSlit, value);
    }
    else
        status = asynPortDriver::writeInt32(pasynUser, value);
    return status;
}

asynStatus ARC_USB::writeFloat64(asynUser *pasynUser, epicsFloat64 value)
{
    timed_lock_guard ML(m_Mutex, DefaultTimeout);
    if (!ML.isLocked())
    {
        asynPrint(pasynUser, ASYN_TRACE_WARNING, "Unable to acquire mutex\n");
        return asynTimeout;
    }
    asynStatus status = asynSuccess;
    if (!isConnected())
    {
        status = connect(pasynUser);
        if (status != asynSuccess)
            return status;
    }
    int function = pasynUser->reason;
    if (function == m_WavelengthPV)
    {
        ARC_set_Mono_Wavelength_nm(pasynUser, value);
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
    timed_lock_guard ML(m_Mutex, DefaultTimeout);
    if (!ML.isLocked())
    {
        asynPrint(pasynUser, ASYN_TRACE_WARNING, "Unable to acquire mutex\n");
        return asynTimeout;
    }
    asynStatus status = asynSuccess;
    if (!isConnected())
    {
        status = connect(pasynUser);
        if (status != asynSuccess)
            return status;
    }
    int function = pasynUser->reason;
    char enumString[64];
    if (function == m_GratingPV)
    {
        *nIn = m_gratings.size();
        for (size_t grating = 0; grating < m_gratings.size(); grating++)
        {
            if (strings[grating])
                free(strings[grating]);
            snprintf(enumString, sizeof(enumString) - 1, "%d", m_gratings[grating]);
            strings[grating] = strdup(enumString);
            values[grating] = m_gratings[grating];
            severities[grating] = 0;
        }
    }
    else if (function == m_MirrorPV)
    {
        *nIn = 0;
        for (long Mirror_Pos = 1; Mirror_Pos <= 4; Mirror_Pos += 1)
        {
            if (isMovableMirror(pasynUser, Mirror_Pos))
            {
                if (strings[*nIn])
                    free(strings[*nIn]);
                strings[*nIn] = strdup(ARC_get_Mono_Diverter_Pos_CharStr(pasynUser, Mirror_Pos).c_str());
                values[*nIn] = Mirror_Pos;
                severities[*nIn] = 0;
                *nIn++;
            }
        }
    }
    else if (function == m_MovingPV)
    {
        *nIn = 2;
        strings[0] = strdup("Stationary");
        values[0] = 0;
        severities[0] = 0;
        strings[1] = strdup("Moving");
        values[1] = 1;
        severities[1] = 0;
    }
    else
        status = asynPortDriver::readEnum(pasynUser, strings, values, severities, nElements, nIn);
    return status;
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
    bool isMovableMirror = ARC_get_Mono_Diverter_Valid(pasynUser, Mirror_Pos);
    return isMovableMirror;
}

std::string ARC_USB::ARC_get_Mono_Model(asynUser* pasynUser) const
{
    char ModelStr[20];

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

long  ARC_USB::ARC_get_Mono_Grating_Max(asynUser* pasynUser) const
{
    long maxGratingNr = 0;
#ifdef _M_X64
    long Error_Code;
    if (!::ARC_get_Mono_Grating_Max(m_Handle, &maxGratingNr, &Error_Code))
        ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
    if (!::ARC_get_Mono_Grating_Max(m_Handle, maxGratingNr))
        ThrowException(pasynUser, "Could not get max grating", __FUNCTION__, __LINE__);
#endif
    return maxGratingNr;
}

long ARC_USB::ARC_get_Mono_Turret(asynUser* pasynUser) const
{
    long Turret;
#ifdef _M_X64
    long Error_Code;
    if (!::ARC_get_Mono_Turret(m_Handle, &Turret, &Error_Code))
        ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
    if (!::ARC_get_Mono_Turret(m_Handle, Turret))
        ThrowException(pasynUser, "Could not get turret", __FUNCTION__, __LINE__);
#endif
    return Turret;
}

long ARC_USB::ARC_get_Mono_Turret_Max(asynUser* pasynUser) const
{
    long maxTurretNr = 0;
#ifdef _M_X64
    long Error_Code;
    if (!::ARC_get_Mono_Turret_Max(m_Handle, &maxTurretNr, &Error_Code))
        ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
    if (!::ARC_get_Mono_Turret_Max(m_Handle, maxTurretNr))
        ThrowException(pasynUser, "Could not get max turret", __FUNCTION__, __LINE__);
#endif
    return maxTurretNr;
}

long ARC_USB::ARC_get_Mono_Grating_Density(asynUser* pasynUser, long Grating) const
{
    long Groove_MM = 0;
#ifdef _M_X64
    long Error_Code;
    if (!::ARC_get_Mono_Grating_Density(m_Handle, Grating, &Groove_MM, &Error_Code))
        ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
    if (!::ARC_get_Mono_Grating_Density(m_Handle, Grating, Groove_MM))
        ThrowException(pasynUser, "Could not get grating density", __FUNCTION__, __LINE__);
#endif
    return Groove_MM;
}

long ARC_USB::ARC_get_Mono_Grating(asynUser* pasynUser) const
{
    long Grating = 0;
#ifdef _M_X64
    long Error_Code;
    if (!::ARC_get_Mono_Grating(m_Handle, &Grating, &Error_Code))
        ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
    if (!::ARC_get_Mono_Grating(m_Handle, Grating))
        ThrowException(pasynUser, "Could not get monchromator grating", __FUNCTION__, __LINE__);
#endif
    return Grating;
}

void ARC_USB::ARC_Close_Enum(asynUser* pasynUser)
{
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

long ARC_USB::ARC_Search_For_Inst(asynUser* pasynUser) const
{
    long total = 0;
#ifdef _M_X64
    if (!::ARC_Search_For_Inst(&total))
#else
    if (!::ARC_Search_For_Inst(total))
#endif
        asynPrint(pasynUser, ASYN_TRACE_ERROR, "failed to search for devices\n");
    return total;
}

bool ARC_USB::ARC_Open_Mono(asynUser* pasynUser, long Enum_Num)
{
    bool OK = false;
#ifdef _M_X64
    long Error_Code;
    OK = ::ARC_Open_Mono(Enum_Num, &m_Handle, &Error_Code);
    if (!OK)
        asynPrint(pasynUser, ASYN_TRACE_ERROR, "%s\n", Exception::GetDetails(Error_Code, __FUNCTION__, __LINE__).c_str());
#else
    OK = (::ARC_Open_Mono(Enum_Num, m_Handle) != 0);
    if (!OK)
        asynPrint(pasynUser, ASYN_TRACE_ERROR, "%s\n", "Could not open monchromator\n");
#endif
    return OK;
}

bool  ARC_USB::ARC_Open_Mono_Port(asynUser* pasynUser, long comPort)
{
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
#ifdef _M_X64
    long Error_Code;
    if (!::ARC_set_Mono_Wavelength_nm(m_Handle, Wavelength, &Error_Code))
        ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
    if (!::ARC_set_Mono_Wavelength_nm(m_Handle, Wavelength))
        ThrowException(pasynUser, "Could not set wavelength", __FUNCTION__, __LINE__);
#endif
}

double ARC_USB::ARC_get_Mono_Init_ScanRate_nm(asynUser* pasynUser)
{
    double ScanRate;
#ifdef _M_X64
    long Error_Code;
    if (!::ARC_get_Mono_Init_ScanRate_nm(m_Handle, &ScanRate, &Error_Code))
        ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
    if (!::ARC_get_Mono_Init_ScanRate_nm(m_Handle, ScanRate))
        ThrowException(pasynUser, "Could not get scan rate", __FUNCTION__, __LINE__);
#endif
    return ScanRate;
}

void ARC_USB::ARC_set_Mono_Init_ScanRate_nm(asynUser* pasynUser, double ScanRate)
{
#ifdef _M_X64
    long Error_Code;
    if (!::ARC_set_Mono_Init_ScanRate_nm(m_Handle, ScanRate, &Error_Code))
        ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
    if (!::ARC_set_Mono_Init_ScanRate_nm(m_Handle, ScanRate))
        ThrowException(pasynUser, "Could not set scan rate", __FUNCTION__, __LINE__);
#endif
}

bool ARC_USB::ARC_Mono_Scan_Done(asynUser* pasynUser, double& WaveLength_nm) const
{
    bool Done_Moving = false;
#ifdef _M_X64
    long Error_Code;
    if (!::ARC_Mono_Scan_Done(m_Handle, &Done_Moving, &WaveLength_nm, &Error_Code))
    {
        asynPrint(pasynUser, ASYN_TRACE_ERROR, "%s\n", Exception::GetDetails(Error_Code, __FUNCTION__, __LINE__).c_str());
        return true;
    }
#else
    long Done_MovingL = 1;
    if (!ARC_get_Mono_Wavelength_nm(m_Handle, WaveLength_nm))
        //    if (!::ARC_Mono_Scan_Done(m_Handle, Done_MovingL, WaveLength_nm)) *This function throws an access violation*
    {
        asynPrint(pasynUser, ASYN_TRACE_ERROR, "Could not get wavelength\n");
        return true;
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
#ifdef _M_X64
    long Error_Code;
    return ::ARC_get_Mono_Diverter_Valid(m_Handle, mirror, &Error_Code);
#else
    return (::ARC_get_Mono_Diverter_Valid(m_Handle, mirror) != 0);
#endif
}

std::string ARC_USB::ARC_get_Mono_Diverter_Pos_CharStr(asynUser* pasynUser, long mirror) const
{
    char Diverter_pos[64];
#ifdef _M_X64
    long Error_Code;
    if (!::ARC_get_Mono_Diverter_Pos_CharStr(m_Handle, mirror, Diverter_pos, sizeof(Diverter_pos) - 1, &Error_Code))
        ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
    if (!::ARC_get_Mono_Diverter_Pos_CString(m_Handle, mirror, *Diverter_pos))
        ThrowException(pasynUser, "Could not get the mirror name", __FUNCTION__, __LINE__);
#endif
    return Diverter_pos;
}

void  ARC_USB::ARC_set_Mono_Diverter_Pos(asynUser* pasynUser, long Diverter_Num, long  Diverter_Pos)
{
#ifdef _M_X64
    long Error_Code = 0;
    if (!::ARC_set_Mono_Diverter_Pos(m_Handle, Diverter_Num, Diverter_Pos, &Error_Code))
        ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
    if (!::ARC_set_Mono_Diverter_Pos(m_Handle, Diverter_Num, Diverter_Pos))
        ThrowException(pasynUser, "Could not set divertor position", __FUNCTION__, __LINE__);
#endif
}

long ARC_USB::ARC_get_Mono_Diverter_Pos(asynUser* pasynUser, long Diverter_Num) const
{
    long  Diverter_Pos;
#ifdef _M_X64
    long Error_Code = 0;
    if (!::ARC_get_Mono_Diverter_Pos(m_Handle, Diverter_Num, &Diverter_Pos, &Error_Code))
        ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
    if (!::ARC_get_Mono_Diverter_Pos(m_Handle, Diverter_Num, Diverter_Pos))
        ThrowException(pasynUser, "Could not get divertor position", __FUNCTION__, __LINE__);
#endif
    return Diverter_Pos;
}

void ARC_USB::ARC_set_Mono_Grating(asynUser* pasynUser, long Grating)
{
#ifdef _M_X64
    long Error_Code = 0;
    if (!::ARC_set_Mono_Grating(m_Handle, Grating, &Error_Code))
        ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
    if (!::ARC_set_Mono_Grating(m_Handle, Grating))
        ThrowException(pasynUser, "Could not set grating", __FUNCTION__, __LINE__);
#endif
}

long ARC_USB::ARC_get_Mono_Slit_Type(asynUser* pasynUser, long Slit_Pos) const
{
    long Slit_Type;
#ifdef _M_X64
    long Error_Code = 0;
    if (!::ARC_get_Mono_Slit_Type(m_Handle, Slit_Pos, &Slit_Type, &Error_Code))
        ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
    if (!::ARC_get_Mono_Slit_Type(m_Handle, Slit_Pos, Slit_Type))
        ThrowException(pasynUser, "Could not get slit type", __FUNCTION__, __LINE__);
#endif
    return Slit_Type;
}

void  ARC_USB::ARC_set_Mono_Slit_Width(asynUser* pasynUser, long Slit_Pos, long Slit_Width)
{
#ifdef _M_X64
    long Error_Code = 0;
    if (!::ARC_set_Mono_Slit_Width(m_Handle, Slit_Pos, Slit_Width, &Error_Code))
        ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
    if (!::ARC_set_Mono_Slit_Width(m_Handle, Slit_Pos, Slit_Width))
        ThrowException(pasynUser, "Could not set slit width", __FUNCTION__, __LINE__);
#endif
}

long ARC_USB::ARC_get_Mono_Slit_Width(long Slit_Pos, asynUser* pasynUser) const
{
    long Slit_Width;
#ifdef _M_X64
    long Error_Code = 0;
    if (!::ARC_get_Mono_Slit_Width(m_Handle, Slit_Pos, &Slit_Width, &Error_Code))
        ThrowException(pasynUser, Error_Code, __FUNCTION__, __LINE__);
#else
    if (!::ARC_get_Mono_Slit_Width(m_Handle, Slit_Pos, Slit_Width))
        ThrowException(pasynUser, "Could not get slit width", __FUNCTION__, __LINE__);
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
        ARC_USB* Instance = new ARC_USB(asynPortName, monoSerial);
        epicsAtExit(ARC_InstrumentExitFunc, Instance);
    }
    catch (Exception const& E) {
        fprintf(stderr, "%s\n", E.what());
        exit(1);
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
    ARC_USB* Instance = static_cast<ARC_USB*>(param);
    delete Instance;
}

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
    iocshRegister(&initFuncDef, ARC_USB::ARC_InstrumentPortDriverConfigure);
}

extern "C" {
    epicsExportRegistrar(ARC_InstrumentRegistrar);
}
