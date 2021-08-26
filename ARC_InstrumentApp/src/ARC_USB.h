//////////////////////////////////////////////////////////////////////////////////////////////////////
//																									//
//	Module:																							//
//		ARC_USB.h																					//
//																									//
//	Description:																					//
//		Declares the ARC_USB class.																	//
//		This uses AsynPortDriver and asynOctetSyncIO to control an Acton spectrometer.				//
// 		See, for example, https://www.princetoninstruments.com/products/acton-ls-family/acton-ls	//
//																									//
//	Author:  Peter Heesterman (Tessella plc). Date: 26 Aug 2021.									//
//																									//
//	ARC_InstrumentApp is distributed subject to a Software License Agreement						//
//	found in file LICENSE that is included with this distribution.									//
//																									//
//////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

const static int ARC_NULL_HANDLE = -1;

#include <asynPortDriver.h>

#include <string>
#include <mutex>

////////////////////////////////////////////////////////////
//
// Class declaration : ARC_USB
//
// Date : 2006
// Author: Klaus Kneupner 
//
// Description : Drive an ARC through USB.
//				 Original implementation by Francesco Orsegana (?)
//				
//				For drivers look at \\catsserver\downloads\acton
//
// 2006: created 
//
////////////////////////////////////////////////////////////
class epicsShareClass ARC_USB : public asynPortDriver {
public:
    enum MirrorTypes { EntanceMirror = 1, FrontExitMirror };
    enum EMirrorPosition { mpFront = 0, mpSide = 1 };
    enum SlitTypes { SideEntanceSlit = 1, FrontEntranceSlit, FrontExitSlit, SideExitSlit };

    explicit ARC_USB(const char* portName, int MonoSerial);
    ~ARC_USB();
private:
#ifndef _M_X64
    static bool  m_LibraryNotLoaded;
#endif
    class Exception;
    long m_Handle;

    // Asyn parameter handles
    int m_WavelengthPV;
    int m_ScanRatePV;
    int m_ModelPV;
    int m_SerialPV;
    int m_MovingPV;
    int m_GratingPV;
    int m_TurretPV;
    int m_MirrorPV;
    int m_ExitSlitWidthPV;
    int m_EntrySlitWidthPV;

    std::string m_MonoModel;
    long m_MonoSerial;
    std::timed_mutex m_Mutex;
    static const unsigned long DefaultTimeout;
    std::vector<int> m_gratings;
    int m_gratingNr;
    int m_turretNr;
    int m_maxTurret;
public:
    bool isConnected() const;
    static void ARC_InstrumentPortDriverConfigure(const iocshArgBuf *args);
    static void ARC_InstrumentExitFunc(void * param);

    asynStatus connect(asynUser* pasynUser);
    std::string disConnect(asynUser* pasynUser);

protected:
    static int Mask();
    void ThrowException(asynUser *pasynUser, std::string const& Details, std::string const& While, long Line) const;
#ifdef _M_X64
    void ThrowException(asynUser *pasynUser, long code, std::string const& While, long Line) const;
#endif
    virtual asynStatus readOctet(asynUser *pasynUser, char *value, size_t maxChars,
        size_t *nActual, int *eomReason);
    virtual asynStatus readInt32(asynUser *pasynUser, epicsInt32 *value);
    virtual asynStatus writeInt32(asynUser *pasynUser, epicsInt32 value);
    virtual asynStatus readFloat64(asynUser *pasynUser, epicsFloat64 *value);
    virtual asynStatus writeFloat64(asynUser *pasynUser, epicsFloat64 value);
    virtual asynStatus readEnum(asynUser *pasynUser, char *strings[], int values[], int severities[],
        size_t nElements, size_t *nIn);

    epicsInt32 getgratingLines(asynUser* pasynUser);
    EMirrorPosition getMirrorPosition(asynUser* pasynUser);
    asynStatus getExitSlitPosition(asynUser* pasynUser, epicsInt32 *value);
    asynStatus getEntrySlitPosition(asynUser* pasynUser, epicsInt32 *value);

    std::string ARC_get_Mono_Model(asynUser* pasynUser) const;
    long ARC_get_Mono_Serial_int32(asynUser* pasynUser) const;
    long ARC_get_Mono_Grating_Max(asynUser* pasynUser) const;
    long ARC_get_Mono_Grating_Density(asynUser* pasynUser, long Grating) const;
    long ARC_get_Mono_Grating(asynUser* pasynUser) const;
    long ARC_get_Mono_Turret_Max(asynUser* pasynUser) const;
    long ARC_get_Mono_Turret(asynUser* pasynUser) const;
    void ARC_Close_Enum(asynUser* pasynUser);
    long ARC_Search_For_Inst(asynUser* pasynUser) const;
    bool ARC_Open_Mono(asynUser* pasynUser, long Enum_Num);
    bool ARC_Open_Mono_Port(asynUser* pasynUser, long comPort);
    void ARC_set_Mono_Wavelength_nm(asynUser* pasynUser, double Wavelength);
    void ARC_set_Mono_Init_ScanRate_nm(asynUser* pasynUser, double ScanRate);
    double ARC_get_Mono_Init_ScanRate_nm(asynUser* pasynUser);
    bool ARC_Mono_Scan_Done(asynUser* pasynUser, double& WaveLength_nm) const;
    bool ARC_get_Mono_Diverter_Valid(asynUser* pasynUser, long mirror) const;
    std::string ARC_get_Mono_Diverter_Pos_CharStr(asynUser* pasynUser, long mirror) const;

    void ARC_set_Mono_Diverter_Pos(asynUser* pasynUser, long Diverter_Num, long  Diverter_Pos);
    long ARC_get_Mono_Diverter_Pos(asynUser* pasynUser, long Diverter_Num) const;
    void ARC_set_Mono_Grating(asynUser* pasynUser, long Grating);
    long ARC_get_Mono_Slit_Type(asynUser* pasynUser, long Slit_Pos) const;
    bool isMovableSlit(asynUser* pasynUser, long Slit_Pos) const;
    bool isMovableMirror(asynUser* pasynUser, long Mirror_Pos) const;
    void ARC_set_Mono_Slit_Width(asynUser* pasynUser, long Slit_Pos, long Slit_Width);
    long ARC_get_Mono_Slit_Width(long Slit_Pos, asynUser* pasynUser) const;
};
