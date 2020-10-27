/*
 * ARCMonochromator.h		v0.04 (2006 07 19)
 *
 * ARCMonochromator derived class
 */
#pragma once

const static int ARC_NULL_HANDLE = -1;

#include <asynPortDriver.h>

#include <string>
#include <mutex>

namespace Motors {

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
		class Drive;
		class GratingDrive;
		class ExitMirror;
		class SlitWidth;
		friend class ARC_USB::GratingDrive;
		friend class ARC_USB::ExitMirror;
		friend class ARC_USB::SlitWidth;
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

		std::string m_MonoModel;
		long m_MonoSerial;
		std::timed_mutex m_Mutex;
		static const unsigned long DefaultTimeout;
		GratingDrive* m_gratingDrive;
		ExitMirror* m_exitMirror;
		SlitWidth* m_slitWidth;
		double m_CurrentPosition;
		bool m_isMoving;
	public:
		bool isConnected() const;
		bool connect(asynUser* pasynUser, unsigned long timeOut = DefaultTimeout);
		std::string disConnect(asynUser* pasynUser);
		double startMovement(asynUser* pasynUser, double position);
		void unplanedMovementStop(asynUser* pasynUser);
		double CurrentPosition() const {
			return m_CurrentPosition;
		}
		bool   isMoving() const {
			return m_isMoving;
		}
		void setisMoving(bool isMoving);

		//exit mirror
		bool canChangeExitMirror(asynUser* pasynUser) const;

		// slit widths
		bool canChangeSlitWidth(asynUser* pasynUser) const;

	protected:
		void ThrowException(std::string const& Details, std::string const& While, long Line) const;
#ifdef _M_X64
		void ThrowException(asynUser *pasynUser, long code, std::string const& While, long Line, bool ErrorToWarning = false) const;
#endif
		virtual asynStatus readOctet(asynUser *pasynUser, char *value, size_t maxChars,
			size_t *nActual, int *eomReason);
		virtual asynStatus readFloat64(asynUser *pasynUser, epicsFloat64 *value);
		virtual asynStatus writeFloat64(asynUser *pasynUser, epicsFloat64 value);

		std::string ARC_get_Mono_Model(asynUser* pasynUser) const;
		long ARC_get_Mono_Serial_int32(asynUser* pasynUser) const;
		long ARC_get_Mono_Grating_Max(asynUser* pasynUser, std::timed_mutex& Mutex) const;
		long ARC_get_Mono_Grating_Density(asynUser* pasynUser, std::timed_mutex& Mutex, long Grating) const;
		long ARC_get_Mono_Grating(asynUser* pasynUser, std::timed_mutex& Mutex) const;
		long ARC_get_Mono_Turret_Max(asynUser* pasynUser, std::timed_mutex& Mutex) const;
		long ARC_get_Mono_Turret(asynUser* pasynUser, std::timed_mutex& Mutex) const;
		void ARC_Close_Enum(asynUser* pasynUser);
		long ARC_Search_For_Inst() const;
		bool ARC_Open_Mono(asynUser* pasynUser, long Enum_Num);
		bool ARC_Open_Mono_Port(asynUser* pasynUser, long comPort);
		void ARC_set_Mono_Wavelength_nm(asynUser* pasynUser, double Wavelength);
		void ARC_set_Mono_Init_ScanRate_nm(asynUser* pasynUser, double ScanRate);
		double ARC_get_Mono_Init_ScanRate_nm(asynUser* pasynUser);
		bool ARC_Mono_Scan_Done(asynUser* pasynUser, double& WaveLength_nm) const;
		bool ARC_get_Mono_Diverter_Valid(asynUser* pasynUser, long mirror) const;
		void ARC_set_Mono_Diverter_Pos(asynUser* pasynUser, long Diverter_Num,long  Diverter_Pos);
		long ARC_get_Mono_Diverter_Pos(asynUser* pasynUser, long Diverter_Num) const;
		void ARC_set_Mono_Grating(asynUser* pasynUser, long Grating);
		long ARC_get_Mono_Slit_Type(asynUser* pasynUser, long Slit_Pos) const;
		bool isMovableSlit(asynUser* pasynUser, long Slit_Pos) const;
		bool isMovableMirror(asynUser* pasynUser, long Mirror_Pos) const;
		void ARC_set_Mono_Slit_Width(asynUser* pasynUser, long Slit_Pos, long Slit_Width);
		long ARC_get_Mono_Slit_Width(long Slit_Pos, asynUser* pasynUser) const;
  };

}// namespace Motors

//EOF ========================================================================
