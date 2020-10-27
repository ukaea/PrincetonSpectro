//34567891123456789212345678931234567894123456789512345678961234567897123456789
// ARC_Instrument_dll.h : Includes the necessary hooks for using the 
//                        Acton Research Corp. ARC_Instrument.dll
//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <ctype.h>
//#include <assert.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <conio.h>
#include <windows.h>
// function definitions
typedef short (CALLBACK* LPFNDLL_Ver) (long &, long &, long &);
//Communications
typedef short (CALLBACK* LPFNDLL_Search_For_Inst) (long &);
typedef short (CALLBACK* LPFNDLL_get_Num_Found_Inst_Ports) ();
typedef short (CALLBACK* LPFNDLL_Open_Mono) (long,long &);
typedef short (CALLBACK* LPFNDLL_Open_Mono_Port) (long, long &);
typedef short (CALLBACK* LPFNDLL_Close_Enum) (long);
typedef short (CALLBACK* LPFNDLL_Valid_Mono_Enum) (long);
typedef short (CALLBACK* LPFNDLL_get_Mono_preOpen_Model_CString) (long, char &);

//Information
typedef short (CALLBACK* LPFNDLL_get_Mono_Model_CString) (long, char &);
typedef short (CALLBACK* LPFNDLL_get_Mono_Serial_CString) (long, char &);
typedef short (CALLBACK* LPFNDLL_get_Mono_Focallength) (long, double &);
typedef short (CALLBACK* LPFNDLL_get_Mono_HalfAngle) (long, double &);
typedef short (CALLBACK* LPFNDLL_get_Mono_DetectorAngle) (long, double &);
typedef short (CALLBACK* LPFNDLL_get_Mono_Double) (long, short &);
// Double Subtractive
typedef short (CALLBACK* LPFNDLL_get_Mono_Double_Subtractive)(long,short &);
typedef short (CALLBACK* LPFNDLL_get_Mono_Precision) (long);
typedef short (CALLBACK* LPFNDLL_get_Mono_Backlash_Steps) (long, long&);
typedef short (CALLBACK* LPFNDLL_get_Mono_Gear_Steps) (long, long &, long &);
typedef short (CALLBACK* LPFNDLL_get_Mono_nmRev_Ratio) (long, double &);

// CCD Pixel Mapping
typedef short (CALLBACK* LPFNDLL_get_Mono_Pixel_Map_nm)    (long, double, long, double, double, double, double &);
typedef short (CALLBACK* LPFNDLL_get_Mono_Pixel_Map_ang)    (long, double, long, double, double, double, double &);
typedef short (CALLBACK* LPFNDLL_get_Mono_Pixel_Map_eV)    (long, double, long, double, double, double, double &);
typedef short (CALLBACK* LPFNDLL_get_Mono_Pixel_Map_micron)    (long, double, long, double, double, double, double &);
typedef short (CALLBACK* LPFNDLL_get_Mono_Pixel_Map_absCM)    (long, double, long, double, double, double, double &);
typedef short (CALLBACK* LPFNDLL_get_Mono_Pixel_Map_relCM)    (long, double, long, double, double, double, double, double &);

// PI Calibration functions
typedef short (CALLBACK* LPFNDLL_get_PI_Calibrated)   (long,long,short &); 
typedef short (CALLBACK* LPFNDLL_get_PI_Offset)       (long,long,double &);
typedef short (CALLBACK* LPFNDLL_get_PI_GAdjust)      (long,long,double &);
typedef short (CALLBACK* LPFNDLL_get_PI_FocalLength)  (long,long,double &);
typedef short (CALLBACK* LPFNDLL_get_PI_HalfAngle)    (long,long,double &);
typedef short (CALLBACK* LPFNDLL_get_PI_DetAngle)     (long,long,double &);

typedef short (CALLBACK* LPFNDLL_set_PI_Calibrated)  (long,long,short ); 
typedef short (CALLBACK* LPFNDLL_set_PI_Offset)      (long,long,double);
typedef short (CALLBACK* LPFNDLL_set_PI_GAdjust)     (long,long,double);
typedef short (CALLBACK* LPFNDLL_set_PI_FocalLength) (long,long,double);
typedef short (CALLBACK* LPFNDLL_set_PI_HalfAngle)   (long,long,double);
typedef short (CALLBACK* LPFNDLL_set_PI_DetAngle)    (long,long,double); 

//Wavelength
typedef short (CALLBACK* LPFNDLL_get_Mono_Wavelength_nm) (long, double &);
typedef short (CALLBACK* LPFNDLL_set_Mono_Wavelength_nm) (long, double);
typedef short (CALLBACK* LPFNDLL_get_Mono_Wavelength_ang) (long, double &);
typedef short (CALLBACK* LPFNDLL_set_Mono_Wavelength_ang) (long, double);
typedef short (CALLBACK* LPFNDLL_get_Mono_Wavelength_eV) (long, double &);
typedef short (CALLBACK* LPFNDLL_set_Mono_Wavelength_eV) (long, double);
typedef short (CALLBACK* LPFNDLL_get_Mono_Wavelength_micron) (long, double &);
typedef short (CALLBACK* LPFNDLL_set_Mono_Wavelength_micron) (long, double);
typedef short (CALLBACK* LPFNDLL_get_Mono_Wavelength_absCM) (long, double &);
typedef short (CALLBACK* LPFNDLL_set_Mono_Wavelength_absCM) (long, double);
typedef short (CALLBACK* LPFNDLL_get_Mono_Wavelength_relCM) (long, double, double &);
typedef short (CALLBACK* LPFNDLL_set_Mono_Wavelength_relCM) (long, double, double);
typedef short (CALLBACK* LPFNDLL_get_Mono_Wavelength_Cutoff_nm) (long, double &);
typedef short (CALLBACK* LPFNDLL_get_Mono_Wavelength_Min_nm) (long, double &);

//Grating
typedef short (CALLBACK* LPFNDLL_get_Mono_Turret) (long, long &);
typedef short (CALLBACK* LPFNDLL_set_Mono_Turret) (long, long);
typedef short (CALLBACK* LPFNDLL_get_Mono_Turret_Gratings) (long, long &);
typedef short (CALLBACK* LPFNDLL_get_Mono_Turret_Max) (long, long &);
typedef short (CALLBACK* LPFNDLL_get_Mono_Grating) (long, long &);
typedef short (CALLBACK* LPFNDLL_set_Mono_Grating) (long, long);
typedef short (CALLBACK* LPFNDLL_get_Mono_Grating_Blaze_CString) (long, long, char &);
typedef short (CALLBACK* LPFNDLL_get_Mono_Grating_Density) (long, long, long &);
typedef short (CALLBACK* LPFNDLL_get_Mono_Grating_Installed) (long, long);
typedef short (CALLBACK* LPFNDLL_get_Mono_Grating_Max) (long, long &);

//Mirrors
typedef short (CALLBACK* LPFNDLL_get_Mono_Diverter_Valid) (long, long);
typedef short (CALLBACK* LPFNDLL_get_Mono_Diverter_Pos) (long, long, long &);
typedef short (CALLBACK* LPFNDLL_set_Mono_Diverter_Pos) (long, long, long);
typedef short (CALLBACK* LPFNDLL_get_Mono_Diverter_Pos_CString) (long, long, char &);

//Slits
typedef short (CALLBACK* LPFNDLL_get_Mono_Slit_Type) (long, long, long &);
typedef short (CALLBACK* LPFNDLL_get_Mono_Slit_Type_CString) (long, long, char &);
typedef short (CALLBACK* LPFNDLL_get_Mono_Slit_Width) (long, long, long &);
typedef short (CALLBACK* LPFNDLL_set_Mono_Slit_Width) (long, long, long);
typedef short (CALLBACK* LPFNDLL_Mono_Slit_Home) (long, long);
typedef short (CALLBACK* LPFNDLL_Mono_Slit_Name_CString) (long, char &);
// Slit Band Pass
typedef short (CALLBACK* LPFNDLL_Calc_Mono_Slit_BandPass)(long,long,double,double &);
typedef short (CALLBACK* LPFNDLL_get_Mono_Slit_BandPass)(long,long,double &);
typedef short (CALLBACK* LPFNDLL_set_Mono_Slit_BandPass)(long,long,double);
// Special Double Function
typedef short (CALLBACK* LPFNDLL_get_Mono_Double_Intermediate_Slit)(long,long &);
typedef short (CALLBACK* LPFNDLL_get_Mono_Exit_Slit)(long,long &);

//Filter
typedef short (CALLBACK* LPFNDLL_get_Mono_Filter_Present) (long);
typedef short (CALLBACK* LPFNDLL_get_Mono_Filter_Position) (long, long &);
typedef short (CALLBACK* LPFNDLL_set_Mono_Filter_Position) (long, long);
typedef short (CALLBACK* LPFNDLL_get_Mono_Filter_Min_Pos) (long, long &);
typedef short (CALLBACK* LPFNDLL_get_Mono_Filter_Max_Pos) (long, long &);
typedef short (CALLBACK* LPFNDLL_Mono_Filter_Home) (long);

// advanced functions
// Gear
typedef short (CALLBACK* LPFNDLL_get_Mono_Int_Led_On) (long);
typedef short (CALLBACK* LPFNDLL_set_Mono_Int_Led) (long, int);
typedef short (CALLBACK* LPFNDLL_get_Mono_Motor_Int) (long);
typedef short (CALLBACK* LPFNDLL_get_Mono_Wheel_Int) (long);
typedef short (CALLBACK* LPFNDLL_Mono_Move_Steps) (long, long);
typedef short (CALLBACK* LPFNDLL_get_Mono_Sine_Drive) (long);

// Grating Values
typedef short (CALLBACK* LPFNDLL_get_Mono_Init_Grating) (long, long &);
typedef short (CALLBACK* LPFNDLL_set_Mono_Init_Grating) (long, long);
typedef short (CALLBACK* LPFNDLL_get_Mono_Init_Wave_nm) (long, double &);
typedef short (CALLBACK* LPFNDLL_set_Mono_Init_Wave_nm) (long, double);
typedef short (CALLBACK* LPFNDLL_get_Mono_Init_ScanRate_nm) (long, double &);
typedef short (CALLBACK* LPFNDLL_set_Mono_Init_ScanRate_nm) (long, double);
typedef short (CALLBACK* LPFNDLL_get_Mono_Grating_Offset) (long, long, long &);
typedef short (CALLBACK* LPFNDLL_get_Mono_Grating_Gadjust) (long, long, long &);
typedef short (CALLBACK* LPFNDLL_set_Mono_Grating_Offset) (long, long, long);
typedef short (CALLBACK* LPFNDLL_set_Mono_Grating_Gadjust) (long, long, long);
typedef short (CALLBACK* LPFNDLL_Mono_Grating_Calc_Offset) (long, long, double, double, long &);
typedef short (CALLBACK* LPFNDLL_Mono_Grating_Calc_Gadjust) (long, long, double, double, long &);
typedef short (CALLBACK* LPFNDLL_Mono_Reset) (long);
typedef short (CALLBACK* LPFNDLL_Mono_Restore_Factory_Settings) (long);

// Scan Values
typedef short (CALLBACK* LPFNDLL_get_Mono_Scan_Rate_nm_min)  (long, double &);
typedef short (CALLBACK* LPFNDLL_set_Mono_Scan_Rate_nm_min)  (long, double);
typedef short (CALLBACK* LPFNDLL_Mono_Start_Scan_To_nm)  (long, double);
typedef short (CALLBACK* LPFNDLL_Mono_Scan_Done)  (long, long &, double);
typedef short (CALLBACK* LPFNDLL_Mono_Start_Jog)  (long, long, long);
typedef short (CALLBACK* LPFNDLL_Mono_Stop_Jog)  (long);

// shutter control for v6 controllers
typedef short (CALLBACK* LPFNDLL_get_Mono_Shutter_Valid)   (long);
typedef short (CALLBACK* LPFNDLL_get_Mono_Shutter_Open)    (long);
typedef short (CALLBACK* LPFNDLL_set_Mono_Shutter_Open)    (long);
typedef short (CALLBACK* LPFNDLL_set_Mono_Shutter_Closed)  (long);

// NCL / NCL Light specific functions
// NCL Communications functions
typedef short (CALLBACK* LPFNDLL_Open_ReadOut) (long, long &, long &, long &);
typedef short (CALLBACK* LPFNDLL_Open_ReadOut_Port) (long, long &, long &, long &);
typedef short (CALLBACK* LPFNDLL_Valid_Enum) (long);
typedef short (CALLBACK* LPFNDLL_Valid_ReadOut_Enum) (long);
typedef short (CALLBACK* LPFNDLL_get_ReadOut_preOpen_Model_CString) (long, char &);

//Information
typedef short (CALLBACK* LPFNDLL_get_ReadOut_Model_CString) (long, char &);
typedef short (CALLBACK* LPFNDLL_get_ReadOut_Serial_CString) (long, char &);

// Detector Functions
typedef long (CALLBACK* LPFNDLL_get_Num_Det) (long);
typedef short (CALLBACK* LPFNDLL_Valid_Det_Num) (long, long);
typedef long (CALLBACK* LPFNDLL_get_ReadOut_ITime_ms) (long);
typedef short (CALLBACK* LPFNDLL_set_ReadOut_ITime_ms) (long, long);
typedef short (CALLBACK* LPFNDLL_get_Det_Type) (long, long, long &);
typedef short (CALLBACK* LPFNDLL_get_Det_Type_CString) (long, long, char &);
typedef short (CALLBACK* LPFNDLL_set_Det_Type) (long, long, long);
typedef short (CALLBACK* LPFNDLL_set_Det_Photon) (long, long);
typedef short (CALLBACK* LPFNDLL_set_Det_Voltage) (long, long);
typedef short (CALLBACK* LPFNDLL_set_Det_Current) (long, long);
typedef short (CALLBACK* LPFNDLL_get_Det_BiPolar) (long, long);
typedef short (CALLBACK* LPFNDLL_get_Det_BiPolar_CString) (long, long, char &);
typedef short (CALLBACK* LPFNDLL_set_Det_BiPolar) (long, long);
typedef short (CALLBACK* LPFNDLL_set_Det_UniPolar) (long, long);
typedef short (CALLBACK* LPFNDLL_get_Det_Range) (long, long, long &);
typedef short (CALLBACK* LPFNDLL_get_Det_Range_Factor) (long, long, long &);
typedef short (CALLBACK* LPFNDLL_set_Det_Range) (long, long, long);
typedef short (CALLBACK* LPFNDLL_get_Det_HVon) (long, long);
typedef short (CALLBACK* LPFNDLL_set_Det_HV_on) (long, long);
typedef short (CALLBACK* LPFNDLL_set_Det_HV_off) (long, long);
typedef long (CALLBACK* LPFNDLL_get_Det_HV_Volts) (long, long);
typedef short (CALLBACK* LPFNDLL_set_Det_HV_Volts) (long, long, long);
typedef long (CALLBACK* LPFNDLL_get_Det_NumAvgRead) (long);
typedef short (CALLBACK* LPFNDLL_set_Det_NumAvgRead) (long, long);
typedef short (CALLBACK* LPFNDLL_Det_Read) (long, long, double &);
typedef short (CALLBACK* LPFNDLL_Det_ReadAll) (long, double &, double &, double &);
// NCL / SpectraHub start Read
typedef short (CALLBACK* LPFNDLL_Det_Start_NonBlock_Read) (long, long);
typedef short (CALLBACK* LPFNDLL_Det_NonBlock_Read_Done) (long, long, double &);

// NCL scanning functions

// NCL Filter Wheel
typedef short (CALLBACK* LPFNDLL_get_NCL_Filter_Present)  (long);
typedef short (CALLBACK* LPFNDLL_set_NCL_Filter_Present)  (long, long, long);
typedef short (CALLBACK* LPFNDLL_get_NCL_Filter_Position) (long, long &);
typedef short (CALLBACK* LPFNDLL_set_NCL_Filter_Position) (long, long);
typedef short (CALLBACK* LPFNDLL_get_NCL_Filter_Min_Pos)  (long, long &);
typedef short (CALLBACK* LPFNDLL_get_NCL_Filter_Max_Pos)  (long, long &);
typedef short (CALLBACK* LPFNDLL_NCL_Filter_Home)         (long);

// NCL Shutter
typedef short (CALLBACK* LPFNDLL_get_NCL_Shutter_Valid)  (long, long);
typedef short (CALLBACK* LPFNDLL_get_NCL_Shutter_Open)   (long, long);
typedef short (CALLBACK* LPFNDLL_set_NCL_Shutter_Open)   (long, long);
typedef short (CALLBACK* LPFNDLL_set_NCL_Shutter_Closed) (long, long);
// SpectraHub shutter Functions
typedef short (CALLBACK* LPFNDLL_get_SpectraHub_Shutter_Enabled)(long);
typedef short (CALLBACK* LPFNDLL_set_SpectraHub_Shutter_Enable )(long);
typedef short (CALLBACK* LPFNDLL_set_SpectraHub_Shutter_Disable)(long);
typedef short (CALLBACK* LPFNDLL_get_SpectraHub_Shutter_Open_High)(long);
typedef short (CALLBACK* LPFNDLL_set_SpectraHub_Shutter_Open_High)(long);
typedef short (CALLBACK* LPFNDLL_set_SpectraHub_Shutter_Open_Low )(long);
typedef short (CALLBACK* LPFNDLL_get_SpectraHub_Shutter_Open)(long);
typedef short (CALLBACK* LPFNDLL_set_SpectraHub_Shutter_Open)(long);
typedef short (CALLBACK* LPFNDLL_set_SpectraHub_Shutter_Closed)(long);

// NCL TTL
typedef short (CALLBACK* LPFNDLL_get_NCL_TTL_Valid)   (long, long);
typedef short (CALLBACK* LPFNDLL_get_NCL_TTL_In)      (long, long);
typedef short (CALLBACK* LPFNDLL_get_NCL_TTL_Out)     (long, long);
typedef short (CALLBACK* LPFNDLL_set_NCL_TTL_Out_On)  (long, long);
typedef short (CALLBACK* LPFNDLL_set_NCL_TTL_Out_Off) (long, long);
// SpectraHub Trigger functions
typedef short (CALLBACK* LPFNDLL_get_SpectraHub_Trig_On)(long);
typedef short (CALLBACK* LPFNDLL_set_SpectraHub_Trig_On)(long);
typedef short (CALLBACK* LPFNDLL_set_SpectraHub_Trig_Off)(long);

// Mono functions
typedef short (CALLBACK* LPFNDLL_get_NCL_Mono_Setup) (long, long);
typedef long (CALLBACK* LPFNDLL_get_NCL_Mono_Enum)  (long, long);

// FilterWheel
//Communications
typedef short (CALLBACK* LPFNDLL_Open_Filter)       (long, long &);
typedef short (CALLBACK* LPFNDLL_Open_Filter_Port)  (long, long &);
typedef short (CALLBACK* LPFNDLL_Valid_Filter_Enum) (long);
typedef short (CALLBACK* LPFNDLL_get_Filter_preOpen_Model_CString) (long, char &);

//Information
typedef short (CALLBACK* LPFNDLL_get_Filter_Model_CString)  (long, char &);
typedef short (CALLBACK* LPFNDLL_get_Filter_Serial_CString) (long, char &);

//Filter
typedef short (CALLBACK* LPFNDLL_get_Filter_Present)  (long);
typedef short (CALLBACK* LPFNDLL_get_Filter_Position) (long, long &);
typedef short (CALLBACK* LPFNDLL_set_Filter_Position) (long, long);
typedef short (CALLBACK* LPFNDLL_get_Filter_Min_Pos)  (long, long &);
typedef short (CALLBACK* LPFNDLL_get_Filter_Max_Pos)  (long, long &);
typedef short (CALLBACK* LPFNDLL_Filter_Home) (long);


// Serial Number Integers
typedef long (CALLBACK* LPFNDLL_get_Filter_Serial_int32) (long);
typedef long (CALLBACK* LPFNDLL_get_Mono_Serial_int32)   (long);
typedef long (CALLBACK* LPFNDLL_get_ReadOut_Serial_int32)(long);

// PreOpen Data as Integers
typedef short (CALLBACK* LPFNDLL_get_Filter_preOpen_Model_int32)   (long, long &);
typedef short (CALLBACK* LPFNDLL_get_Mono_preOpen_Model_int32)     (long, long &);
typedef short (CALLBACK* LPFNDLL_get_ReadOut_preOpen_Model_int32)  (long, long &);
typedef short (CALLBACK* LPFNDLL_get_Filter_preOpen_Serial_int32)  (long);
typedef short (CALLBACK* LPFNDLL_get_Mono_preOpen_Serial_int32)    (long);
typedef short (CALLBACK* LPFNDLL_get_ReadOut_preOpen_Serial_int32) (long);

// function pointers
HINSTANCE hARC_Instrument; // Handle to ARC_Instrument.dll
LPFNDLL_Ver ARC_Ver;       // function pointer to ARC_Ver
//Communications
LPFNDLL_Search_For_Inst                ARC_Search_For_Inst;
LPFNDLL_get_Num_Found_Inst_Ports       ARC_get_Num_Found_Inst_Ports;
LPFNDLL_Open_Mono                      ARC_Open_Mono;
LPFNDLL_Open_Mono_Port                 ARC_Open_Mono_Port;
LPFNDLL_Close_Enum                     ARC_Close_Enum;
LPFNDLL_Valid_Mono_Enum                ARC_Valid_Mono_Enum;
LPFNDLL_get_Mono_preOpen_Model_CString ARC_get_Mono_preOpen_Model_CString;

//Information
LPFNDLL_get_Mono_Model_CString         ARC_get_Mono_Model_CString;
LPFNDLL_get_Mono_Serial_CString        ARC_get_Mono_Serial_CString;
LPFNDLL_get_Mono_Focallength           ARC_get_Mono_Focallength;
LPFNDLL_get_Mono_HalfAngle             ARC_get_Mono_HalfAngle;
LPFNDLL_get_Mono_DetectorAngle         ARC_get_Mono_DetectorAngle;
LPFNDLL_get_Mono_Double                ARC_get_Mono_Double;
// Double Subtractive
LPFNDLL_get_Mono_Double_Subtractive    ARC_get_Mono_Double_Subtractive;
LPFNDLL_get_Mono_Precision             ARC_get_Mono_Precision;
LPFNDLL_get_Mono_Backlash_Steps        ARC_get_Mono_Backlash_Steps;
LPFNDLL_get_Mono_Gear_Steps            ARC_get_Mono_Gear_Steps;
LPFNDLL_get_Mono_nmRev_Ratio           ARC_get_Mono_nmRev_Ratio;

// CCD Pixel Mapping
LPFNDLL_get_Mono_Pixel_Map_nm          ARC_get_Mono_Pixel_Map_nm;  
LPFNDLL_get_Mono_Pixel_Map_ang         ARC_get_Mono_Pixel_Map_ang;
LPFNDLL_get_Mono_Pixel_Map_eV          ARC_get_Mono_Pixel_Map_eV;     
LPFNDLL_get_Mono_Pixel_Map_micron      ARC_get_Mono_Pixel_Map_micron;
LPFNDLL_get_Mono_Pixel_Map_absCM       ARC_get_Mono_Pixel_Map_absCM;
LPFNDLL_get_Mono_Pixel_Map_relCM       ARC_get_Mono_Pixel_Map_relCM;

// PI Calibration functions
LPFNDLL_get_PI_Calibrated              ARC_get_PI_Calibrated;
LPFNDLL_get_PI_Offset                  ARC_get_PI_Offset;
LPFNDLL_get_PI_GAdjust                 ARC_get_PI_GAdjust;
LPFNDLL_get_PI_FocalLength             ARC_get_PI_FocalLength;
LPFNDLL_get_PI_HalfAngle               ARC_get_PI_HalfAngle;
LPFNDLL_get_PI_DetAngle                ARC_get_PI_DetAngle;

LPFNDLL_set_PI_Calibrated              ARC_set_PI_Calibrated;
LPFNDLL_set_PI_Offset                  ARC_set_PI_Offset;
LPFNDLL_set_PI_GAdjust                 ARC_set_PI_GAdjust;
LPFNDLL_set_PI_FocalLength             ARC_set_PI_FocalLength;
LPFNDLL_set_PI_HalfAngle               ARC_set_PI_HalfAngle;
LPFNDLL_set_PI_DetAngle                ARC_set_PI_DetAngle; 

//Wavelength
LPFNDLL_get_Mono_Wavelength_nm         ARC_get_Mono_Wavelength_nm;
LPFNDLL_set_Mono_Wavelength_nm         ARC_set_Mono_Wavelength_nm;
LPFNDLL_get_Mono_Wavelength_ang        ARC_get_Mono_Wavelength_ang;
LPFNDLL_set_Mono_Wavelength_ang        ARC_set_Mono_Wavelength_ang;
LPFNDLL_get_Mono_Wavelength_eV         ARC_get_Mono_Wavelength_eV;
LPFNDLL_set_Mono_Wavelength_eV         ARC_set_Mono_Wavelength_eV;
LPFNDLL_get_Mono_Wavelength_micron     ARC_get_Mono_Wavelength_micron;
LPFNDLL_set_Mono_Wavelength_micron     ARC_set_Mono_Wavelength_micron;
LPFNDLL_get_Mono_Wavelength_absCM      ARC_get_Mono_Wavelength_absCM;
LPFNDLL_set_Mono_Wavelength_absCM      ARC_set_Mono_Wavelength_absCM;
LPFNDLL_get_Mono_Wavelength_relCM      ARC_get_Mono_Wavelength_relCM;
LPFNDLL_set_Mono_Wavelength_relCM      ARC_set_Mono_Wavelength_relCM;
LPFNDLL_get_Mono_Wavelength_Cutoff_nm  ARC_get_Mono_Wavelength_Cutoff_nm;
LPFNDLL_get_Mono_Wavelength_Min_nm     ARC_get_Mono_Wavelength_Min_nm;

//Grating
LPFNDLL_get_Mono_Turret                ARC_get_Mono_Turret;
LPFNDLL_set_Mono_Turret                ARC_set_Mono_Turret;
LPFNDLL_get_Mono_Turret_Gratings       ARC_get_Mono_Turret_Gratings;
LPFNDLL_get_Mono_Turret_Max            ARC_get_Mono_Turret_Max;  
LPFNDLL_get_Mono_Grating               ARC_get_Mono_Grating;
LPFNDLL_set_Mono_Grating               ARC_set_Mono_Grating;
LPFNDLL_get_Mono_Grating_Blaze_CString ARC_get_Mono_Grating_Blaze_CString;
LPFNDLL_get_Mono_Grating_Density       ARC_get_Mono_Grating_Density;
LPFNDLL_get_Mono_Grating_Installed     ARC_get_Mono_Grating_Installed;
LPFNDLL_get_Mono_Grating_Max           ARC_get_Mono_Grating_Max;

//Mirrors
LPFNDLL_get_Mono_Diverter_Valid        ARC_get_Mono_Diverter_Valid;
LPFNDLL_get_Mono_Diverter_Pos          ARC_get_Mono_Diverter_Pos;
LPFNDLL_set_Mono_Diverter_Pos          ARC_set_Mono_Diverter_Pos;
LPFNDLL_get_Mono_Diverter_Pos_CString  ARC_get_Mono_Diverter_Pos_CString;

//Slits
LPFNDLL_get_Mono_Slit_Type             ARC_get_Mono_Slit_Type;
LPFNDLL_get_Mono_Slit_Type_CString     ARC_get_Mono_Slit_Type_CString;
LPFNDLL_get_Mono_Slit_Width            ARC_get_Mono_Slit_Width;
LPFNDLL_set_Mono_Slit_Width            ARC_set_Mono_Slit_Width;
LPFNDLL_Mono_Slit_Home                 ARC_Mono_Slit_Home;
LPFNDLL_Mono_Slit_Name_CString         ARC_Mono_Slit_Name_CString;
// Slit Band Pass
LPFNDLL_Calc_Mono_Slit_BandPass        ARC_Calc_Mono_Slit_BandPass;
LPFNDLL_get_Mono_Slit_BandPass         ARC_get_Mono_Slit_BandPass;
LPFNDLL_set_Mono_Slit_BandPass         ARC_set_Mono_Slit_BandPass;
// Special Double Function
LPFNDLL_get_Mono_Double_Intermediate_Slit ARC_get_Mono_Double_Intermediate_Slit;
LPFNDLL_get_Mono_Exit_Slit             ARC_get_Mono_Exit_Slit;

//Filter
LPFNDLL_get_Mono_Filter_Present        ARC_get_Mono_Filter_Present;
LPFNDLL_get_Mono_Filter_Position       ARC_get_Mono_Filter_Position;
LPFNDLL_set_Mono_Filter_Position       ARC_set_Mono_Filter_Position;
LPFNDLL_get_Mono_Filter_Min_Pos        ARC_get_Mono_Filter_Min_Pos;
LPFNDLL_get_Mono_Filter_Max_Pos        ARC_get_Mono_Filter_Max_Pos;
LPFNDLL_Mono_Filter_Home               ARC_Mono_Filter_Home;

// advanced functions
// Gear
LPFNDLL_get_Mono_Int_Led_On            ARC_get_Mono_Int_Led_On;
LPFNDLL_set_Mono_Int_Led               ARC_set_Mono_Int_Led;
LPFNDLL_get_Mono_Motor_Int             ARC_get_Mono_Motor_Int;
LPFNDLL_get_Mono_Wheel_Int             ARC_get_Mono_Wheel_Int;
LPFNDLL_Mono_Move_Steps                ARC_Mono_Move_Steps;
LPFNDLL_get_Mono_Sine_Drive            ARC_get_Mono_Sine_Drive;

// Grating Values
LPFNDLL_get_Mono_Init_Grating          ARC_get_Mono_Init_Grating;
LPFNDLL_set_Mono_Init_Grating          ARC_set_Mono_Init_Grating;
LPFNDLL_get_Mono_Init_Wave_nm          ARC_get_Mono_Init_Wave_nm;
LPFNDLL_set_Mono_Init_Wave_nm          ARC_set_Mono_Init_Wave_nm;
LPFNDLL_get_Mono_Init_ScanRate_nm      ARC_get_Mono_Init_ScanRate_nm;
LPFNDLL_set_Mono_Init_ScanRate_nm      ARC_set_Mono_Init_ScanRate_nm;
LPFNDLL_get_Mono_Grating_Offset        ARC_get_Mono_Grating_Offset;
LPFNDLL_get_Mono_Grating_Gadjust       ARC_get_Mono_Grating_Gadjust;
LPFNDLL_set_Mono_Grating_Offset        ARC_set_Mono_Grating_Offset;
LPFNDLL_set_Mono_Grating_Gadjust       ARC_set_Mono_Grating_Gadjust;
LPFNDLL_Mono_Grating_Calc_Offset       ARC_Mono_Grating_Calc_Offset;
LPFNDLL_Mono_Grating_Calc_Gadjust      ARC_Mono_Grating_Calc_Gadjust;
LPFNDLL_Mono_Reset                     ARC_Mono_Reset;
LPFNDLL_Mono_Restore_Factory_Settings  ARC_Mono_Restore_Factory_Settings;

// Scan Values
LPFNDLL_get_Mono_Scan_Rate_nm_min      ARC_get_Mono_Scan_Rate_nm_min; 
LPFNDLL_set_Mono_Scan_Rate_nm_min      ARC_set_Mono_Scan_Rate_nm_min; 
LPFNDLL_Mono_Start_Scan_To_nm          ARC_Mono_Start_Scan_To_nm;
LPFNDLL_Mono_Scan_Done                 ARC_Mono_Scan_Done; 
LPFNDLL_Mono_Start_Jog                 ARC_Mono_Start_Jog; 
LPFNDLL_Mono_Stop_Jog                  ARC_Mono_Stop_Jog; 

// shutter control for v6 controllers
LPFNDLL_get_Mono_Shutter_Valid         ARC_get_Mono_Shutter_Valid; 
LPFNDLL_get_Mono_Shutter_Open          ARC_get_Mono_Shutter_Open; 
LPFNDLL_set_Mono_Shutter_Open          ARC_set_Mono_Shutter_Open; 
LPFNDLL_set_Mono_Shutter_Closed        ARC_set_Mono_Shutter_Closed;
// NCL / NCL Light specific functions
// NCL Communications functions
LPFNDLL_Open_ReadOut                   ARC_Open_ReadOut;
LPFNDLL_Open_ReadOut_Port              ARC_Open_ReadOut_Port;
LPFNDLL_Valid_Enum                     ARC_Valid_Enum;
LPFNDLL_Valid_ReadOut_Enum             ARC_Valid_ReadOut_Enum;
LPFNDLL_get_ReadOut_preOpen_Model_CString 
                                       ARC_get_ReadOut_preOpen_Model_CString;

//Information
LPFNDLL_get_ReadOut_Model_CString      ARC_get_ReadOut_Model_CString;
LPFNDLL_get_ReadOut_Serial_CString     ARC_get_ReadOut_Serial_CString;

// Detector Functions
LPFNDLL_get_Num_Det                    ARC_get_Num_Det;
LPFNDLL_Valid_Det_Num                  ARC_Valid_Det_Num;
LPFNDLL_get_ReadOut_ITime_ms           ARC_get_ReadOut_ITime_ms;
LPFNDLL_set_ReadOut_ITime_ms           ARC_set_ReadOut_ITime_ms;
LPFNDLL_get_Det_Type                   ARC_get_Det_Type;
LPFNDLL_get_Det_Type_CString           ARC_get_Det_Type_CString;
LPFNDLL_set_Det_Type                   ARC_set_Det_Type;
LPFNDLL_set_Det_Photon                 ARC_set_Det_Photon;
LPFNDLL_set_Det_Voltage                ARC_set_Det_Voltage;
LPFNDLL_set_Det_Current                ARC_set_Det_Current;
LPFNDLL_get_Det_BiPolar                ARC_get_Det_BiPolar;
LPFNDLL_get_Det_BiPolar_CString        ARC_get_Det_BiPolar_CString;
LPFNDLL_set_Det_BiPolar                ARC_set_Det_BiPolar;
LPFNDLL_set_Det_UniPolar               ARC_set_Det_UniPolar;
LPFNDLL_get_Det_Range                  ARC_get_Det_Range;
LPFNDLL_get_Det_Range_Factor           ARC_get_Det_Range_Factor;
LPFNDLL_set_Det_Range                  ARC_set_Det_Range;
LPFNDLL_get_Det_HVon                   ARC_get_Det_HVon;
LPFNDLL_set_Det_HV_on                  ARC_set_Det_HV_on;
LPFNDLL_set_Det_HV_off                 ARC_set_Det_HV_off;
LPFNDLL_get_Det_HV_Volts               ARC_get_Det_HV_Volts;
LPFNDLL_set_Det_HV_Volts               ARC_set_Det_HV_Volts;
LPFNDLL_get_Det_NumAvgRead             ARC_get_Det_NumAvgRead;
LPFNDLL_set_Det_NumAvgRead             ARC_set_Det_NumAvgRead;
LPFNDLL_Det_Read                       ARC_Det_Read;
LPFNDLL_Det_ReadAll                    ARC_Det_ReadAll;
// NCL / SpectraHub start Read
LPFNDLL_Det_Start_NonBlock_Read        ARC_Det_Start_NonBlock_Read;
LPFNDLL_Det_NonBlock_Read_Done         ARC_Det_NonBlock_Read_Done;

// NCL Filter Wheel
LPFNDLL_get_NCL_Filter_Present         ARC_get_NCL_Filter_Present; 
LPFNDLL_set_NCL_Filter_Present         ARC_set_NCL_Filter_Present;
LPFNDLL_get_NCL_Filter_Position        ARC_get_NCL_Filter_Position;
LPFNDLL_set_NCL_Filter_Position        ARC_set_NCL_Filter_Position;
LPFNDLL_get_NCL_Filter_Min_Pos         ARC_get_NCL_Filter_Min_Pos;
LPFNDLL_get_NCL_Filter_Max_Pos         ARC_get_NCL_Filter_Max_Pos; 
LPFNDLL_NCL_Filter_Home                ARC_NCL_Filter_Home;        

// NCL Shutter
LPFNDLL_get_NCL_Shutter_Valid          ARC_get_NCL_Shutter_Valid; 
LPFNDLL_get_NCL_Shutter_Open           ARC_get_NCL_Shutter_Open; 
LPFNDLL_set_NCL_Shutter_Open           ARC_set_NCL_Shutter_Open;  
LPFNDLL_set_NCL_Shutter_Closed         ARC_set_NCL_Shutter_Closed;
// SpectraHub shutter Functions
LPFNDLL_get_SpectraHub_Shutter_Enabled   ARC_get_SpectraHub_Shutter_Enabled;
LPFNDLL_set_SpectraHub_Shutter_Enable    ARC_set_SpectraHub_Shutter_Enable;
LPFNDLL_set_SpectraHub_Shutter_Disable   ARC_set_SpectraHub_Shutter_Disable;
LPFNDLL_get_SpectraHub_Shutter_Open_High ARC_get_SpectraHub_Shutter_Open_High;
LPFNDLL_set_SpectraHub_Shutter_Open_High ARC_set_SpectraHub_Shutter_Open_High;
LPFNDLL_set_SpectraHub_Shutter_Open_Low  ARC_set_SpectraHub_Shutter_Open_Low;
LPFNDLL_get_SpectraHub_Shutter_Open      ARC_get_SpectraHub_Shutter_Open;
LPFNDLL_set_SpectraHub_Shutter_Open      ARC_set_SpectraHub_Shutter_Open;
LPFNDLL_set_SpectraHub_Shutter_Closed    ARC_set_SpectraHub_Shutter_Closed;

// NCL TTL
LPFNDLL_get_NCL_TTL_Valid              ARC_get_NCL_TTL_Valid;
LPFNDLL_get_NCL_TTL_In                 ARC_get_NCL_TTL_In; 
LPFNDLL_get_NCL_TTL_Out                ARC_get_NCL_TTL_Out;
LPFNDLL_set_NCL_TTL_Out_On             ARC_set_NCL_TTL_Out_On;
LPFNDLL_set_NCL_TTL_Out_Off            ARC_set_NCL_TTL_Out_Off;
// SpectraHub Trigger functions
LPFNDLL_get_SpectraHub_Trig_On         ARC_get_SpectraHub_Trig_On;
LPFNDLL_set_SpectraHub_Trig_On         ARC_set_SpectraHub_Trig_On;
LPFNDLL_set_SpectraHub_Trig_Off        ARC_set_SpectraHub_Trig_Off;  

// Mono functions
LPFNDLL_get_NCL_Mono_Setup             ARC_get_NCL_Mono_Setup;
LPFNDLL_get_NCL_Mono_Enum              ARC_get_NCL_Mono_Enum;

// FilterWheel
//Communications
LPFNDLL_Open_Filter                    ARC_Open_Filter;
LPFNDLL_Open_Filter_Port               ARC_Open_Filter_Port;
LPFNDLL_Valid_Filter_Enum              ARC_Valid_Filter_Enum;
LPFNDLL_get_Filter_preOpen_Model_CString 
                                       ARC_get_Filter_preOpen_Model_CString;

//Information
LPFNDLL_get_Filter_Model_CString       ARC_get_Filter_Model_CString;
LPFNDLL_get_Filter_Serial_CString      ARC_get_Filter_Serial_CString;
//Filter
LPFNDLL_get_Filter_Present             ARC_get_Filter_Present;
LPFNDLL_get_Filter_Position            ARC_get_Filter_Position;
LPFNDLL_set_Filter_Position            ARC_set_Filter_Position;
LPFNDLL_get_Filter_Min_Pos             ARC_get_Filter_Min_Pos; 
LPFNDLL_get_Filter_Max_Pos             ARC_get_Filter_Max_Pos;
LPFNDLL_Filter_Home                    ARC_Filter_Home;

// Serial Number Integers  
LPFNDLL_get_Filter_Serial_int32        ARC_get_Filter_Serial_int32;
LPFNDLL_get_Mono_Serial_int32          ARC_get_Mono_Serial_int32;
LPFNDLL_get_ReadOut_Serial_int32       ARC_get_ReadOut_Serial_int32;

// PreOpen Data as Integers
LPFNDLL_get_Filter_preOpen_Model_int32   ARC_get_Filter_preOpen_Model_int32;
LPFNDLL_get_Mono_preOpen_Model_int32     ARC_get_Mono_preOpen_Model_int32;
LPFNDLL_get_ReadOut_preOpen_Model_int32  ARC_get_ReadOut_preOpen_Model_int32;
LPFNDLL_get_Filter_preOpen_Serial_int32  ARC_get_Filter_preOpen_Serial_int32;
LPFNDLL_get_Mono_preOpen_Serial_int32    ARC_get_Mono_preOpen_Serial_int32;
LPFNDLL_get_ReadOut_preOpen_Serial_int32 ARC_get_ReadOut_preOpen_Serial_int32;

int Setup_ARC_Instrument_dll()
{
   hARC_Instrument = LoadLibrary("Acton\\ARC_Instrument.dll");
   if (hARC_Instrument != NULL)
   {
    // 
    ARC_Ver                             = (LPFNDLL_Ver) GetProcAddress(hARC_Instrument,"ARC_Ver");
    //Communications
    ARC_Search_For_Inst                 = (LPFNDLL_Search_For_Inst)  GetProcAddress(hARC_Instrument,"ARC_Search_For_Inst");
	ARC_get_Num_Found_Inst_Ports        = (LPFNDLL_get_Num_Found_Inst_Ports)  GetProcAddress(hARC_Instrument,"ARC_get_Num_Found_Inst_Ports"); 
    ARC_Open_Mono                       = (LPFNDLL_Open_Mono)  GetProcAddress(hARC_Instrument,"ARC_Open_Mono");
    ARC_Open_Mono_Port                  = (LPFNDLL_Open_Mono_Port)  GetProcAddress(hARC_Instrument,"ARC_Open_Mono_Port");
    ARC_Close_Enum                      = (LPFNDLL_Close_Enum)  GetProcAddress(hARC_Instrument,"ARC_Close_Enum");
    ARC_Valid_Mono_Enum                 = (LPFNDLL_Valid_Mono_Enum)  GetProcAddress(hARC_Instrument,"ARC_Valid_Mono_Enum");
    ARC_get_Mono_preOpen_Model_CString  = (LPFNDLL_get_Mono_preOpen_Model_CString)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_preOpen_Model_CString");
    //Information
    ARC_get_Mono_Model_CString          = (LPFNDLL_get_Mono_Model_CString)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Model_CString");
    ARC_get_Mono_Serial_CString         = (LPFNDLL_get_Mono_Serial_CString)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Serial_CString");
    ARC_get_Mono_Focallength            = (LPFNDLL_get_Mono_Focallength)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Focallength");
    ARC_get_Mono_HalfAngle              = (LPFNDLL_get_Mono_HalfAngle)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_HalfAngle");
    ARC_get_Mono_DetectorAngle          = (LPFNDLL_get_Mono_DetectorAngle)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_DetectorAngle");
    ARC_get_Mono_Double                 = (LPFNDLL_get_Mono_Double)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Double");
    
    // Double Subtractive
    ARC_get_Mono_Double_Subtractive     = (LPFNDLL_get_Mono_Double_Subtractive)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Double_Subtractive");
    ARC_get_Mono_Precision              = (LPFNDLL_get_Mono_Precision)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Precision");
    ARC_get_Mono_Backlash_Steps         = (LPFNDLL_get_Mono_Backlash_Steps)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Backlash_Steps");
    ARC_get_Mono_Gear_Steps             = (LPFNDLL_get_Mono_Gear_Steps)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Gear_Steps");
    ARC_get_Mono_nmRev_Ratio            = (LPFNDLL_get_Mono_nmRev_Ratio)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_nmRev_Ratio");

    // CCD Pixel Mapping
    ARC_get_Mono_Pixel_Map_nm           = (LPFNDLL_get_Mono_Pixel_Map_nm)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Pixel_Map_nm");  
    ARC_get_Mono_Pixel_Map_ang          = (LPFNDLL_get_Mono_Pixel_Map_ang)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Pixel_Map_ang");
    ARC_get_Mono_Pixel_Map_eV           = (LPFNDLL_get_Mono_Pixel_Map_eV)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Pixel_Map_eV");
    ARC_get_Mono_Pixel_Map_micron       = (LPFNDLL_get_Mono_Pixel_Map_micron)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Pixel_Map_micron");
    ARC_get_Mono_Pixel_Map_absCM        = (LPFNDLL_get_Mono_Pixel_Map_absCM)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Pixel_Map_absCM");
    ARC_get_Mono_Pixel_Map_relCM        = (LPFNDLL_get_Mono_Pixel_Map_relCM)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Pixel_Map_relCM");

    // PI Calibration functions
    ARC_get_PI_Calibrated              = (LPFNDLL_get_PI_Calibrated)  GetProcAddress(hARC_Instrument,"ARC_get_PI_Calibrated");
    ARC_get_PI_Offset                  = (LPFNDLL_get_PI_Offset)  GetProcAddress(hARC_Instrument,"ARC_get_PI_Offset");
    ARC_get_PI_GAdjust                 = (LPFNDLL_get_PI_GAdjust)  GetProcAddress(hARC_Instrument,"ARC_get_PI_GAdjust");
    ARC_get_PI_FocalLength             = (LPFNDLL_get_PI_FocalLength)  GetProcAddress(hARC_Instrument,"ARC_get_PI_FocalLength");
    ARC_get_PI_HalfAngle               = (LPFNDLL_get_PI_HalfAngle)  GetProcAddress(hARC_Instrument,"ARC_get_PI_HalfAngle");
    ARC_get_PI_DetAngle                = (LPFNDLL_get_PI_DetAngle)  GetProcAddress(hARC_Instrument,"ARC_get_PI_DetAngle");

    ARC_set_PI_Calibrated              = (LPFNDLL_set_PI_Calibrated)  GetProcAddress(hARC_Instrument,"ARC_set_PI_Calibrated");
    ARC_set_PI_Offset                  = (LPFNDLL_set_PI_Offset)  GetProcAddress(hARC_Instrument,"ARC_set_PI_Offset");
    ARC_set_PI_GAdjust                 = (LPFNDLL_set_PI_GAdjust)  GetProcAddress(hARC_Instrument,"ARC_set_PI_GAdjust");
    ARC_set_PI_FocalLength             = (LPFNDLL_set_PI_FocalLength)  GetProcAddress(hARC_Instrument,"ARC_set_PI_FocalLength");
    ARC_set_PI_HalfAngle               = (LPFNDLL_set_PI_HalfAngle)  GetProcAddress(hARC_Instrument,"ARC_set_PI_HalfAngle");
    ARC_set_PI_DetAngle                = (LPFNDLL_set_PI_DetAngle)  GetProcAddress(hARC_Instrument,"ARC_set_PI_DetAngle");

    //Wavelength
    ARC_get_Mono_Wavelength_nm          = (LPFNDLL_get_Mono_Wavelength_nm)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Wavelength_nm");
    ARC_set_Mono_Wavelength_nm          = (LPFNDLL_set_Mono_Wavelength_nm)  GetProcAddress(hARC_Instrument,"ARC_set_Mono_Wavelength_nm");
    ARC_get_Mono_Wavelength_ang         = (LPFNDLL_get_Mono_Wavelength_ang)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Wavelength_ang");
    ARC_set_Mono_Wavelength_ang         = (LPFNDLL_set_Mono_Wavelength_ang)  GetProcAddress(hARC_Instrument,"ARC_set_Mono_Wavelength_ang");
    ARC_get_Mono_Wavelength_eV          = (LPFNDLL_get_Mono_Wavelength_eV)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Wavelength_eV");
    ARC_set_Mono_Wavelength_eV          = (LPFNDLL_set_Mono_Wavelength_eV)  GetProcAddress(hARC_Instrument,"ARC_set_Mono_Wavelength_eV");
    ARC_get_Mono_Wavelength_micron      = (LPFNDLL_get_Mono_Wavelength_micron)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Wavelength_micron");
    ARC_set_Mono_Wavelength_micron      = (LPFNDLL_set_Mono_Wavelength_micron)  GetProcAddress(hARC_Instrument,"ARC_set_Mono_Wavelength_micron");
    ARC_get_Mono_Wavelength_absCM       = (LPFNDLL_get_Mono_Wavelength_absCM)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Wavelength_absCM");
    ARC_set_Mono_Wavelength_absCM       = (LPFNDLL_set_Mono_Wavelength_absCM)  GetProcAddress(hARC_Instrument,"ARC_set_Mono_Wavelength_absCM");
    ARC_get_Mono_Wavelength_relCM       = (LPFNDLL_get_Mono_Wavelength_relCM)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Wavelength_relCM");
    ARC_set_Mono_Wavelength_relCM       = (LPFNDLL_set_Mono_Wavelength_relCM)  GetProcAddress(hARC_Instrument,"ARC_set_Mono_Wavelength_relCM");
    ARC_get_Mono_Wavelength_Cutoff_nm   = (LPFNDLL_get_Mono_Wavelength_Cutoff_nm)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Wavelength_Cutoff_nm");
    ARC_get_Mono_Wavelength_Min_nm      = (LPFNDLL_get_Mono_Wavelength_Min_nm)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Wavelength_Min_nm");

    //Grating
    ARC_get_Mono_Turret                 = (LPFNDLL_get_Mono_Turret)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Turret");
    ARC_set_Mono_Turret                 = (LPFNDLL_set_Mono_Turret)  GetProcAddress(hARC_Instrument,"ARC_set_Mono_Turret");
    ARC_get_Mono_Turret_Gratings        = (LPFNDLL_get_Mono_Turret_Gratings)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Turret_Gratings");
	ARC_get_Mono_Turret_Max             = (LPFNDLL_get_Mono_Turret_Max)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Turret_Max");
    ARC_get_Mono_Grating                = (LPFNDLL_get_Mono_Grating)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Grating");
    ARC_set_Mono_Grating                = (LPFNDLL_set_Mono_Grating)  GetProcAddress(hARC_Instrument,"ARC_set_Mono_Grating");
    ARC_get_Mono_Grating_Blaze_CString  = (LPFNDLL_get_Mono_Grating_Blaze_CString)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Grating_Blaze_CString");
    ARC_get_Mono_Grating_Density        = (LPFNDLL_get_Mono_Grating_Density)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Grating_Density");
    ARC_get_Mono_Grating_Installed      = (LPFNDLL_get_Mono_Grating_Installed)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Grating_Installed");
	ARC_get_Mono_Grating_Max            = (LPFNDLL_get_Mono_Grating_Max)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Grating_Max");

    //Mirrors
    ARC_get_Mono_Diverter_Valid         = (LPFNDLL_get_Mono_Diverter_Valid)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Diverter_Valid");
    ARC_get_Mono_Diverter_Pos           = (LPFNDLL_get_Mono_Diverter_Pos)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Diverter_Pos");
    ARC_set_Mono_Diverter_Pos           = (LPFNDLL_set_Mono_Diverter_Pos)  GetProcAddress(hARC_Instrument,"ARC_set_Mono_Diverter_Pos");
    ARC_get_Mono_Diverter_Pos_CString   = (LPFNDLL_get_Mono_Diverter_Pos_CString)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Diverter_Pos_CString");

    //Slits
    ARC_get_Mono_Slit_Type              = (LPFNDLL_get_Mono_Slit_Type)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Slit_Type");
    ARC_get_Mono_Slit_Type_CString      = (LPFNDLL_get_Mono_Slit_Type_CString)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Slit_Type_CString");
    ARC_get_Mono_Slit_Width             = (LPFNDLL_get_Mono_Slit_Width)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Slit_Width");
    ARC_set_Mono_Slit_Width             = (LPFNDLL_set_Mono_Slit_Width)  GetProcAddress(hARC_Instrument,"ARC_set_Mono_Slit_Width");
    ARC_Mono_Slit_Home                  = (LPFNDLL_Mono_Slit_Home)  GetProcAddress(hARC_Instrument,"ARC_Mono_Slit_Home");
    ARC_Mono_Slit_Name_CString          = (LPFNDLL_Mono_Slit_Name_CString)  GetProcAddress(hARC_Instrument,"ARC_Mono_Slit_Name_CString");
    // Slit Band Pass
    ARC_Calc_Mono_Slit_BandPass         = (LPFNDLL_Calc_Mono_Slit_BandPass)  GetProcAddress(hARC_Instrument,"ARC_Calc_Mono_Slit_BandPass");
    ARC_get_Mono_Slit_BandPass          = (LPFNDLL_get_Mono_Slit_BandPass)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Slit_BandPass");
    ARC_set_Mono_Slit_BandPass          = (LPFNDLL_set_Mono_Slit_BandPass)  GetProcAddress(hARC_Instrument,"ARC_set_Mono_Slit_BandPass");
    // Special Double Function
    ARC_get_Mono_Double_Intermediate_Slit = (LPFNDLL_get_Mono_Double_Intermediate_Slit)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Double_Intermediate_Slit");
    ARC_get_Mono_Exit_Slit                = (LPFNDLL_get_Mono_Exit_Slit)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Exit_Slit");

    //Filter
    ARC_get_Mono_Filter_Present         = (LPFNDLL_get_Mono_Filter_Present)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Filter_Present");
    ARC_get_Mono_Filter_Position        = (LPFNDLL_get_Mono_Filter_Position)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Filter_Position");
    ARC_set_Mono_Filter_Position        = (LPFNDLL_set_Mono_Filter_Position)  GetProcAddress(hARC_Instrument,"ARC_set_Mono_Filter_Position");
    ARC_get_Mono_Filter_Min_Pos         = (LPFNDLL_get_Mono_Filter_Min_Pos)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Filter_Min_Pos");
    ARC_get_Mono_Filter_Max_Pos         = (LPFNDLL_get_Mono_Filter_Max_Pos)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Filter_Max_Pos");
    ARC_Mono_Filter_Home                = (LPFNDLL_Mono_Filter_Home)  GetProcAddress(hARC_Instrument,"ARC_Mono_Filter_Home");

    // advanced functions
    // Gear
    ARC_get_Mono_Int_Led_On             = (LPFNDLL_get_Mono_Int_Led_On)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Int_Led_On");
    ARC_set_Mono_Int_Led                = (LPFNDLL_set_Mono_Int_Led)  GetProcAddress(hARC_Instrument,"ARC_set_Mono_Int_Led");
    ARC_get_Mono_Motor_Int              = (LPFNDLL_get_Mono_Motor_Int)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Motor_Int");
    ARC_get_Mono_Wheel_Int              = (LPFNDLL_get_Mono_Wheel_Int)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Wheel_Int");
    ARC_Mono_Move_Steps                 = (LPFNDLL_Mono_Move_Steps)  GetProcAddress(hARC_Instrument,"ARC_Mono_Move_Steps");
    ARC_get_Mono_Sine_Drive             = (LPFNDLL_get_Mono_Sine_Drive)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Sine_Drive");

    // Grating Values
    ARC_get_Mono_Init_Grating           = (LPFNDLL_get_Mono_Init_Grating)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Init_Grating");
    ARC_set_Mono_Init_Grating           = (LPFNDLL_set_Mono_Init_Grating)  GetProcAddress(hARC_Instrument,"ARC_set_Mono_Init_Grating");
    ARC_get_Mono_Init_Wave_nm           = (LPFNDLL_get_Mono_Init_Wave_nm)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Init_Wave_nm");
    ARC_set_Mono_Init_Wave_nm           = (LPFNDLL_set_Mono_Init_Wave_nm)  GetProcAddress(hARC_Instrument,"ARC_set_Mono_Init_Wave_nm");
    ARC_get_Mono_Init_ScanRate_nm       = (LPFNDLL_get_Mono_Init_ScanRate_nm)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Init_ScanRate_nm");
    ARC_set_Mono_Init_ScanRate_nm       = (LPFNDLL_set_Mono_Init_ScanRate_nm)  GetProcAddress(hARC_Instrument,"ARC_set_Mono_Init_ScanRate_nm");
    ARC_get_Mono_Grating_Offset         = (LPFNDLL_get_Mono_Grating_Offset)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Grating_Offset");
    ARC_get_Mono_Grating_Gadjust        = (LPFNDLL_get_Mono_Grating_Gadjust)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Grating_Gadjust");
    ARC_set_Mono_Grating_Offset         = (LPFNDLL_set_Mono_Grating_Offset)  GetProcAddress(hARC_Instrument,"ARC_set_Mono_Grating_Offset");
    ARC_set_Mono_Grating_Gadjust        = (LPFNDLL_set_Mono_Grating_Gadjust)  GetProcAddress(hARC_Instrument,"ARC_set_Mono_Grating_Gadjust");
    ARC_Mono_Grating_Calc_Offset        = (LPFNDLL_Mono_Grating_Calc_Offset)  GetProcAddress(hARC_Instrument,"ARC_Mono_Grating_Calc_Offset");
    ARC_Mono_Grating_Calc_Gadjust       = (LPFNDLL_Mono_Grating_Calc_Gadjust)  GetProcAddress(hARC_Instrument,"ARC_Mono_Grating_Calc_Gadjust");
    ARC_Mono_Reset                      = (LPFNDLL_Mono_Reset)  GetProcAddress(hARC_Instrument,"ARC_Mono_Reset");
    ARC_Mono_Restore_Factory_Settings   = (LPFNDLL_Mono_Restore_Factory_Settings)  GetProcAddress(hARC_Instrument,"ARC_Mono_Restore_Factory_Settings");

    // Scan Values
    ARC_get_Mono_Scan_Rate_nm_min       = (LPFNDLL_get_Mono_Scan_Rate_nm_min)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Scan_Rate_nm_min"); 
    ARC_set_Mono_Scan_Rate_nm_min       = (LPFNDLL_set_Mono_Scan_Rate_nm_min)  GetProcAddress(hARC_Instrument,"ARC_set_Mono_Scan_Rate_nm_min"); 
    ARC_Mono_Start_Scan_To_nm           = (LPFNDLL_Mono_Start_Scan_To_nm)  GetProcAddress(hARC_Instrument,"ARC_Mono_Start_Scan_To_nm");
    ARC_Mono_Scan_Done                  = (LPFNDLL_Mono_Scan_Done)  GetProcAddress(hARC_Instrument,"ARC_Mono_Scan_Done"); 
    ARC_Mono_Start_Jog                  = (LPFNDLL_Mono_Start_Jog)  GetProcAddress(hARC_Instrument,"ARC_Mono_Start_Jog"); 
    ARC_Mono_Stop_Jog                   = (LPFNDLL_Mono_Stop_Jog)  GetProcAddress(hARC_Instrument,"ARC_Mono_Stop_Jog"); 

    // shutter control for v6 controllers
    ARC_get_Mono_Shutter_Valid          = (LPFNDLL_get_Mono_Shutter_Valid)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Shutter_Valid"); 
    ARC_get_Mono_Shutter_Open           = (LPFNDLL_get_Mono_Shutter_Open)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Shutter_Open"); 
    ARC_set_Mono_Shutter_Open           = (LPFNDLL_set_Mono_Shutter_Open)  GetProcAddress(hARC_Instrument,"ARC_set_Mono_Shutter_Open"); 
    ARC_set_Mono_Shutter_Closed         = (LPFNDLL_set_Mono_Shutter_Closed)  GetProcAddress(hARC_Instrument,"ARC_set_Mono_Shutter_Closed");
    // NCL / NCL Light specific functions
    // NCL Communications functions
    ARC_Open_ReadOut                    = (LPFNDLL_Open_ReadOut)  GetProcAddress(hARC_Instrument,"ARC_Open_ReadOut");
    ARC_Open_ReadOut_Port               = (LPFNDLL_Open_ReadOut_Port)  GetProcAddress(hARC_Instrument,"ARC_Open_ReadOut_Port");
    ARC_Valid_Enum                      = (LPFNDLL_Valid_Enum)  GetProcAddress(hARC_Instrument,"ARC_Valid_Enum");
    ARC_Valid_ReadOut_Enum              = (LPFNDLL_Valid_ReadOut_Enum)  GetProcAddress(hARC_Instrument,"ARC_Valid_ReadOut_Enum");
    ARC_get_ReadOut_preOpen_Model_CString 
                                        = (LPFNDLL_get_ReadOut_preOpen_Model_CString)  GetProcAddress(hARC_Instrument,"ARC_get_ReadOut_preOpen_Model_CString");

    //Information
    ARC_get_ReadOut_Model_CString       = (LPFNDLL_get_ReadOut_Model_CString)  GetProcAddress(hARC_Instrument,"ARC_get_ReadOut_Model_CString");
    ARC_get_ReadOut_Serial_CString      = (LPFNDLL_get_ReadOut_Serial_CString)  GetProcAddress(hARC_Instrument,"ARC_get_ReadOut_Serial_CString");

    // Detector Functions
    ARC_get_Num_Det                     = (LPFNDLL_get_Num_Det)  GetProcAddress(hARC_Instrument,"ARC_get_Num_Det");
    ARC_Valid_Det_Num                   = (LPFNDLL_Valid_Det_Num)  GetProcAddress(hARC_Instrument,"ARC_Valid_Det_Num");
    ARC_get_ReadOut_ITime_ms            = (LPFNDLL_get_ReadOut_ITime_ms)  GetProcAddress(hARC_Instrument,"ARC_get_ReadOut_ITime_ms");
    ARC_set_ReadOut_ITime_ms            = (LPFNDLL_set_ReadOut_ITime_ms)  GetProcAddress(hARC_Instrument,"ARC_set_ReadOut_ITime_ms");
    ARC_get_Det_Type                    = (LPFNDLL_get_Det_Type)  GetProcAddress(hARC_Instrument,"ARC_get_Det_Type");
    ARC_get_Det_Type_CString            = (LPFNDLL_get_Det_Type_CString )  GetProcAddress(hARC_Instrument,"ARC_get_Det_Type_CString");
    ARC_set_Det_Type                    = (LPFNDLL_set_Det_Type)  GetProcAddress(hARC_Instrument,"ARC_set_Det_Type");
    ARC_set_Det_Photon                  = (LPFNDLL_set_Det_Photon)  GetProcAddress(hARC_Instrument,"ARC_set_Det_Photon");
    ARC_set_Det_Voltage                 = (LPFNDLL_set_Det_Voltage)  GetProcAddress(hARC_Instrument,"ARC_set_Det_Voltage");
    ARC_set_Det_Current                 = (LPFNDLL_set_Det_Current)  GetProcAddress(hARC_Instrument,"ARC_set_Det_Current");
    ARC_get_Det_BiPolar                 = (LPFNDLL_get_Det_BiPolar)  GetProcAddress(hARC_Instrument,"ARC_get_Det_BiPolar");
    ARC_get_Det_BiPolar_CString         = (LPFNDLL_get_Det_BiPolar_CString)  GetProcAddress(hARC_Instrument,"ARC_get_Det_BiPolar_CString");
    ARC_set_Det_BiPolar                 = (LPFNDLL_set_Det_BiPolar)  GetProcAddress(hARC_Instrument,"ARC_set_Det_BiPolar");
    ARC_set_Det_UniPolar                = (LPFNDLL_set_Det_UniPolar)  GetProcAddress(hARC_Instrument,"ARC_set_Det_UniPolar");
    ARC_get_Det_Range                   = (LPFNDLL_get_Det_Range)  GetProcAddress(hARC_Instrument,"ARC_get_Det_Range");
    ARC_get_Det_Range_Factor            = (LPFNDLL_get_Det_Range_Factor)  GetProcAddress(hARC_Instrument,"ARC_get_Det_Range_Factor");
    ARC_set_Det_Range                   = (LPFNDLL_set_Det_Range)  GetProcAddress(hARC_Instrument,"ARC_set_Det_Range");
    ARC_get_Det_HVon                    = (LPFNDLL_get_Det_HVon)  GetProcAddress(hARC_Instrument,"ARC_get_Det_HVon");
    ARC_set_Det_HV_on                   = (LPFNDLL_set_Det_HV_on)  GetProcAddress(hARC_Instrument,"ARC_set_Det_HV_on");
    ARC_set_Det_HV_off                  = (LPFNDLL_set_Det_HV_off)  GetProcAddress(hARC_Instrument,"ARC_set_Det_HV_off");
    ARC_get_Det_HV_Volts                = (LPFNDLL_get_Det_HV_Volts)  GetProcAddress(hARC_Instrument,"ARC_get_Det_HV_Volts");
    ARC_set_Det_HV_Volts                = (LPFNDLL_set_Det_HV_Volts)  GetProcAddress(hARC_Instrument,"ARC_set_Det_HV_Volts");
    ARC_get_Det_NumAvgRead              = (LPFNDLL_get_Det_NumAvgRead)  GetProcAddress(hARC_Instrument,"ARC_get_Det_NumAvgRead");
    ARC_set_Det_NumAvgRead              = (LPFNDLL_set_Det_NumAvgRead)  GetProcAddress(hARC_Instrument,"ARC_set_Det_NumAvgRead");
    ARC_Det_Read                        = (LPFNDLL_Det_Read)  GetProcAddress(hARC_Instrument,"ARC_Det_Read");
    ARC_Det_ReadAll                     = (LPFNDLL_Det_ReadAll)  GetProcAddress(hARC_Instrument,"ARC_Det_ReadAll");
    // NCL / SpectraHub start Read
    ARC_Det_Start_NonBlock_Read         = (LPFNDLL_Det_Start_NonBlock_Read)  GetProcAddress(hARC_Instrument,"ARC_Det_Start_NonBlock_Read");
    ARC_Det_NonBlock_Read_Done          = (LPFNDLL_Det_NonBlock_Read_Done)  GetProcAddress(hARC_Instrument,"ARC_Det_NonBlock_Read_Done");

    // NCL Filter Wheel
    ARC_get_NCL_Filter_Present          = (LPFNDLL_get_NCL_Filter_Present)  GetProcAddress(hARC_Instrument,"ARC_get_NCL_Filter_Present"); 
    ARC_set_NCL_Filter_Present          = (LPFNDLL_set_NCL_Filter_Present)  GetProcAddress(hARC_Instrument,"ARC_set_NCL_Filter_Present");
    ARC_get_NCL_Filter_Position         = (LPFNDLL_get_NCL_Filter_Position)  GetProcAddress(hARC_Instrument,"ARC_get_NCL_Filter_Position");
    ARC_set_NCL_Filter_Position         = (LPFNDLL_set_NCL_Filter_Position)  GetProcAddress(hARC_Instrument,"ARC_set_NCL_Filter_Position");
    ARC_get_NCL_Filter_Min_Pos          = (LPFNDLL_get_NCL_Filter_Min_Pos)  GetProcAddress(hARC_Instrument,"ARC_get_NCL_Filter_Min_Pos");
    ARC_get_NCL_Filter_Max_Pos          = (LPFNDLL_get_NCL_Filter_Max_Pos)  GetProcAddress(hARC_Instrument,"ARC_get_NCL_Filter_Max_Pos"); 
    ARC_NCL_Filter_Home                 = (LPFNDLL_NCL_Filter_Home)  GetProcAddress(hARC_Instrument,"ARC_NCL_Filter_Home");        

    // NCL Shutter
    ARC_get_NCL_Shutter_Valid           = (LPFNDLL_get_NCL_Shutter_Valid)  GetProcAddress(hARC_Instrument,"ARC_get_NCL_Shutter_Valid"); 
    ARC_get_NCL_Shutter_Open            = (LPFNDLL_get_NCL_Shutter_Open)  GetProcAddress(hARC_Instrument,"ARC_get_NCL_Shutter_Open"); 
    ARC_set_NCL_Shutter_Open            = (LPFNDLL_set_NCL_Shutter_Open)  GetProcAddress(hARC_Instrument,"ARC_set_NCL_Shutter_Open");  
    ARC_set_NCL_Shutter_Closed          = (LPFNDLL_set_NCL_Shutter_Closed)  GetProcAddress(hARC_Instrument,"ARC_set_NCL_Shutter_Closed");
	// SpectraHub shutter Functions
    ARC_get_SpectraHub_Shutter_Enabled  = (LPFNDLL_get_SpectraHub_Shutter_Enabled)  GetProcAddress(hARC_Instrument,"ARC_get_SpectraHub_Shutter_Enabled");
    ARC_set_SpectraHub_Shutter_Enable   = (LPFNDLL_set_SpectraHub_Shutter_Enable)  GetProcAddress(hARC_Instrument,"ARC_set_SpectraHub_Shutter_Enable");
    ARC_set_SpectraHub_Shutter_Disable  = (LPFNDLL_set_SpectraHub_Shutter_Disable)  GetProcAddress(hARC_Instrument,"ARC_set_SpectraHub_Shutter_Disable");
    ARC_get_SpectraHub_Shutter_Open_High= (LPFNDLL_get_SpectraHub_Shutter_Open_High)  GetProcAddress(hARC_Instrument,"ARC_get_SpectraHub_Shutter_Open_High");
    ARC_set_SpectraHub_Shutter_Open_High= (LPFNDLL_set_SpectraHub_Shutter_Open_High)  GetProcAddress(hARC_Instrument,"ARC_set_SpectraHub_Shutter_Open_High");
    ARC_set_SpectraHub_Shutter_Open_Low = (LPFNDLL_set_SpectraHub_Shutter_Open_Low)  GetProcAddress(hARC_Instrument,"ARC_set_SpectraHub_Shutter_Open_Low");
    ARC_get_SpectraHub_Shutter_Open     = (LPFNDLL_get_SpectraHub_Shutter_Open)  GetProcAddress(hARC_Instrument,"ARC_get_SpectraHub_Shutter_Open");
    ARC_set_SpectraHub_Shutter_Open     = (LPFNDLL_set_SpectraHub_Shutter_Open)  GetProcAddress(hARC_Instrument,"ARC_set_SpectraHub_Shutter_Open");
    ARC_set_SpectraHub_Shutter_Closed   = (LPFNDLL_set_SpectraHub_Shutter_Closed)  GetProcAddress(hARC_Instrument,"ARC_set_SpectraHub_Shutter_Closed");

    // NCL TTL
    ARC_get_NCL_TTL_Valid               = (LPFNDLL_get_NCL_TTL_Valid)  GetProcAddress(hARC_Instrument,"ARC_get_NCL_TTL_Valid");
    ARC_get_NCL_TTL_In                  = (LPFNDLL_get_NCL_TTL_In)  GetProcAddress(hARC_Instrument,"ARC_get_NCL_TTL_In"); 
    ARC_get_NCL_TTL_Out                 = (LPFNDLL_get_NCL_TTL_Out)  GetProcAddress(hARC_Instrument,"ARC_get_NCL_TTL_Out");
    ARC_set_NCL_TTL_Out_On              = (LPFNDLL_set_NCL_TTL_Out_On)  GetProcAddress(hARC_Instrument,"ARC_set_NCL_TTL_Out_On");
    ARC_set_NCL_TTL_Out_Off             = (LPFNDLL_set_NCL_TTL_Out_Off)  GetProcAddress(hARC_Instrument,"ARC_set_NCL_TTL_Out_Off");
	// SpectraHub Trigger functions
    ARC_get_SpectraHub_Trig_On          = (LPFNDLL_get_SpectraHub_Trig_On)  GetProcAddress(hARC_Instrument,"ARC_get_SpectraHub_Trig_On");
    ARC_set_SpectraHub_Trig_On          = (LPFNDLL_set_SpectraHub_Trig_On)  GetProcAddress(hARC_Instrument,"ARC_set_SpectraHub_Trig_On");
    ARC_set_SpectraHub_Trig_Off         = (LPFNDLL_set_SpectraHub_Trig_Off)  GetProcAddress(hARC_Instrument,"ARC_set_SpectraHub_Trig_Off");

    // Mono functions
    ARC_get_NCL_Mono_Setup              = (LPFNDLL_get_NCL_Mono_Setup)  GetProcAddress(hARC_Instrument,"ARC_get_NCL_Mono_Setup");
    ARC_get_NCL_Mono_Enum               = (LPFNDLL_get_NCL_Mono_Enum)  GetProcAddress(hARC_Instrument,"ARC_get_NCL_Mono_Enum");

    // FilterWheel
    //Communications
    ARC_Open_Filter                     = (LPFNDLL_Open_Filter)  GetProcAddress(hARC_Instrument,"ARC_Open_Filter");
    ARC_Open_Filter_Port                = (LPFNDLL_Open_Filter_Port)  GetProcAddress(hARC_Instrument,"ARC_Open_Filter_Port");
    ARC_Valid_Filter_Enum               = (LPFNDLL_Valid_Filter_Enum)  GetProcAddress(hARC_Instrument,"ARC_Valid_Filter_Enum");
    ARC_get_Filter_preOpen_Model_CString 
                                        = (LPFNDLL_get_Filter_preOpen_Model_CString)  GetProcAddress(hARC_Instrument,"ARC_get_Filter_preOpen_Model_CString");

    //Information
    ARC_get_Filter_Model_CString        = (LPFNDLL_get_Filter_Model_CString)  GetProcAddress(hARC_Instrument,"ARC_get_Filter_Model_CString");
    ARC_get_Filter_Serial_CString       = (LPFNDLL_get_Filter_Serial_CString)  GetProcAddress(hARC_Instrument,"ARC_get_Filter_Serial_CString");
    //Filter
    ARC_get_Filter_Present              = (LPFNDLL_get_Filter_Present)  GetProcAddress(hARC_Instrument,"ARC_get_Filter_Present");
    ARC_get_Filter_Position             = (LPFNDLL_get_Filter_Position)  GetProcAddress(hARC_Instrument,"ARC_get_Filter_Position");
    ARC_set_Filter_Position             = (LPFNDLL_set_Filter_Position)  GetProcAddress(hARC_Instrument,"ARC_set_Filter_Position");
    ARC_get_Filter_Min_Pos              = (LPFNDLL_get_Filter_Min_Pos)  GetProcAddress(hARC_Instrument,"ARC_get_Filter_Min_Pos"); 
    ARC_get_Filter_Max_Pos              = (LPFNDLL_get_Filter_Max_Pos)  GetProcAddress(hARC_Instrument,"ARC_get_Filter_Max_Pos");
    ARC_Filter_Home                     = (LPFNDLL_Filter_Home)  GetProcAddress(hARC_Instrument,"ARC_Filter_Home");

	// Serial Number Integers
    ARC_get_Filter_Serial_int32         = (LPFNDLL_get_Filter_Serial_int32)  GetProcAddress(hARC_Instrument,"ARC_get_Filter_Serial_int32");
    ARC_get_Mono_Serial_int32           = (LPFNDLL_get_Mono_Serial_int32)  GetProcAddress(hARC_Instrument,"ARC_get_Mono_Serial_int32");
    ARC_get_ReadOut_Serial_int32        = (LPFNDLL_get_ReadOut_Serial_int32)  GetProcAddress(hARC_Instrument,"ARC_get_ReadOut_Serial_int32");
	
    // PreOpen Data as Integers
    ARC_get_Filter_preOpen_Model_int32   = (LPFNDLL_get_Filter_preOpen_Model_int32)    GetProcAddress(hARC_Instrument,"ARC_get_Filter_preOpen_Model_int32");
    ARC_get_Mono_preOpen_Model_int32     = (LPFNDLL_get_Mono_preOpen_Model_int32)      GetProcAddress(hARC_Instrument,"ARC_get_Mono_preOpen_Model_int32");
    ARC_get_ReadOut_preOpen_Model_int32  = (LPFNDLL_get_ReadOut_preOpen_Model_int32)   GetProcAddress(hARC_Instrument,"ARC_get_ReadOut_preOpen_Model_int32");
    ARC_get_Filter_preOpen_Serial_int32  = (LPFNDLL_get_Filter_preOpen_Serial_int32)   GetProcAddress(hARC_Instrument,"ARC_get_Filter_preOpen_Serial_int32");
    ARC_get_Mono_preOpen_Serial_int32    = (LPFNDLL_get_Mono_preOpen_Serial_int32)     GetProcAddress(hARC_Instrument,"ARC_get_Mono_preOpen_Serial_int32");
    ARC_get_ReadOut_preOpen_Serial_int32 = (LPFNDLL_get_ReadOut_preOpen_Serial_int32)  GetProcAddress(hARC_Instrument,"ARC_get_ReadOut_preOpen_Serial_int32");

	if (ARC_Ver != NULL &&
       //Communications
	   ARC_Search_For_Inst                != NULL && 
       ARC_Open_Mono                      != NULL && 
       ARC_Open_Mono_Port                 != NULL && 
       ARC_Close_Enum                     != NULL && 
       ARC_Valid_Mono_Enum                != NULL && 
       ARC_get_Mono_preOpen_Model_CString != NULL && 
       //Information
       ARC_get_Mono_Model_CString         != NULL && 
       ARC_get_Mono_Serial_CString        != NULL && 
       ARC_get_Mono_Focallength           != NULL && 
       ARC_get_Mono_HalfAngle             != NULL && 
       ARC_get_Mono_DetectorAngle         != NULL && 
       ARC_get_Mono_Double                != NULL && 
       ARC_get_Mono_Precision             != NULL && 
       ARC_get_Mono_Backlash_Steps        != NULL && 
       ARC_get_Mono_Gear_Steps            != NULL && 
       ARC_get_Mono_nmRev_Ratio           != NULL && 

       // CCD Pixel Mapping
       ARC_get_Mono_Pixel_Map_nm          != NULL && 
       ARC_get_Mono_Pixel_Map_ang         != NULL && 
       ARC_get_Mono_Pixel_Map_eV          != NULL && 
       ARC_get_Mono_Pixel_Map_micron      != NULL && 
       ARC_get_Mono_Pixel_Map_absCM       != NULL && 
       ARC_get_Mono_Pixel_Map_relCM       != NULL && 

       // PI Calibration functions
       ARC_get_PI_Calibrated              != NULL && 
       ARC_get_PI_Offset                  != NULL && 
       ARC_get_PI_GAdjust                 != NULL && 
       ARC_get_PI_FocalLength             != NULL && 
       ARC_get_PI_HalfAngle               != NULL && 
       ARC_get_PI_DetAngle                != NULL && 

       ARC_set_PI_Calibrated              != NULL && 
       ARC_set_PI_Offset                  != NULL && 
       ARC_set_PI_GAdjust                 != NULL && 
       ARC_set_PI_FocalLength             != NULL && 
       ARC_set_PI_HalfAngle               != NULL && 
       ARC_set_PI_DetAngle                != NULL && 

       //Wavelength
       ARC_get_Mono_Wavelength_nm         != NULL && 
       ARC_set_Mono_Wavelength_nm         != NULL && 
       ARC_get_Mono_Wavelength_ang        != NULL && 
       ARC_set_Mono_Wavelength_ang        != NULL && 
       ARC_get_Mono_Wavelength_eV         != NULL && 
       ARC_set_Mono_Wavelength_eV         != NULL && 
       ARC_get_Mono_Wavelength_micron     != NULL && 
       ARC_set_Mono_Wavelength_micron     != NULL && 
       ARC_get_Mono_Wavelength_absCM      != NULL && 
       ARC_set_Mono_Wavelength_absCM      != NULL && 
       ARC_get_Mono_Wavelength_relCM      != NULL && 
       ARC_set_Mono_Wavelength_relCM      != NULL && 
       ARC_get_Mono_Wavelength_Cutoff_nm  != NULL && 
       ARC_get_Mono_Wavelength_Min_nm     != NULL && 

       //Grating
       ARC_get_Mono_Turret                != NULL && 
       ARC_set_Mono_Turret                != NULL && 
       ARC_get_Mono_Turret_Gratings       != NULL &&
       ARC_get_Mono_Turret_Max            != NULL && 
       ARC_get_Mono_Grating               != NULL && 
       ARC_set_Mono_Grating               != NULL && 
       ARC_get_Mono_Grating_Blaze_CString != NULL && 
       ARC_get_Mono_Grating_Density       != NULL && 
       ARC_get_Mono_Grating_Installed     != NULL && 
       ARC_get_Mono_Grating_Max           != NULL &&

       //Mirrors
       ARC_get_Mono_Diverter_Valid        != NULL && 
       ARC_get_Mono_Diverter_Pos          != NULL && 
       ARC_set_Mono_Diverter_Pos          != NULL && 
       ARC_get_Mono_Diverter_Pos_CString  != NULL && 

       //Slits
       ARC_get_Mono_Slit_Type             != NULL && 
       ARC_get_Mono_Slit_Type_CString     != NULL && 
       ARC_get_Mono_Slit_Width            != NULL && 
       ARC_set_Mono_Slit_Width            != NULL && 
       ARC_Mono_Slit_Home                 != NULL && 
       ARC_Mono_Slit_Name_CString         != NULL &&  

       //Filter
       ARC_get_Mono_Filter_Present        != NULL && 
       ARC_get_Mono_Filter_Position       != NULL && 
       ARC_set_Mono_Filter_Position       != NULL && 
       ARC_get_Mono_Filter_Min_Pos        != NULL && 
       ARC_get_Mono_Filter_Max_Pos        != NULL && 
       ARC_Mono_Filter_Home               != NULL && 

       // advanced functions
       // Gear
       ARC_get_Mono_Int_Led_On            != NULL &&
       ARC_set_Mono_Int_Led               != NULL &&
       ARC_get_Mono_Motor_Int             != NULL &&
       ARC_get_Mono_Wheel_Int             != NULL &&
       ARC_Mono_Move_Steps                != NULL &&
       ARC_get_Mono_Sine_Drive            != NULL &&

       // Grating Values
       ARC_get_Mono_Init_Grating          != NULL && 
       ARC_set_Mono_Init_Grating          != NULL &&
       ARC_get_Mono_Init_Wave_nm          != NULL &&
       ARC_set_Mono_Init_Wave_nm          != NULL &&
       ARC_get_Mono_Init_ScanRate_nm      != NULL &&
       ARC_set_Mono_Init_ScanRate_nm      != NULL &&
       ARC_get_Mono_Grating_Offset        != NULL &&
       ARC_get_Mono_Grating_Gadjust       != NULL &&
       ARC_set_Mono_Grating_Offset        != NULL &&
       ARC_set_Mono_Grating_Gadjust       != NULL &&
       ARC_Mono_Grating_Calc_Offset       != NULL &&
       ARC_Mono_Grating_Calc_Gadjust      != NULL &&
       ARC_Mono_Reset                     != NULL &&
       ARC_Mono_Restore_Factory_Settings  != NULL &&

       // Scan Values
       ARC_get_Mono_Scan_Rate_nm_min      != NULL &&
       ARC_set_Mono_Scan_Rate_nm_min      != NULL && 
       ARC_Mono_Start_Scan_To_nm          != NULL && 
       ARC_Mono_Scan_Done                 != NULL && 
       ARC_Mono_Start_Jog                 != NULL && 
       ARC_Mono_Stop_Jog                  != NULL && 

       // shutter control for v6 controllers
       ARC_get_Mono_Shutter_Valid         != NULL && 
       ARC_get_Mono_Shutter_Open          != NULL && 
       ARC_set_Mono_Shutter_Open          != NULL && 
       ARC_set_Mono_Shutter_Closed        != NULL && 
       // NCL / NCL Light specific functions
       // NCL Communications functions
       ARC_Open_ReadOut                   != NULL && 
       ARC_Open_ReadOut_Port              != NULL && 
       ARC_Valid_Enum                     != NULL && 
       ARC_Valid_ReadOut_Enum             != NULL && 
       ARC_get_ReadOut_preOpen_Model_CString 
                                       != NULL && 

       //Information
       ARC_get_ReadOut_Model_CString      != NULL && 
       ARC_get_ReadOut_Serial_CString     != NULL && 

       // Detector Functions
       ARC_get_Num_Det                    != NULL &&  
       ARC_Valid_Det_Num                  != NULL && 
       ARC_get_ReadOut_ITime_ms           != NULL && 
       ARC_set_ReadOut_ITime_ms           != NULL &&
       ARC_get_Det_Type                   != NULL && 
       ARC_get_Det_Type_CString           != NULL && 
       ARC_set_Det_Type                   != NULL && 
       ARC_set_Det_Photon                 != NULL && 
       ARC_set_Det_Voltage                != NULL && 
       ARC_set_Det_Current                != NULL && 
       ARC_get_Det_BiPolar                != NULL && 
       ARC_get_Det_BiPolar_CString        != NULL && 
       ARC_set_Det_BiPolar                != NULL &&
       ARC_set_Det_UniPolar               != NULL &&
       ARC_get_Det_Range                  != NULL && 
       ARC_get_Det_Range_Factor           != NULL && 
       ARC_set_Det_Range                  != NULL &&
       ARC_get_Det_HVon                   != NULL && 
       ARC_set_Det_HV_on                  != NULL &&
       ARC_set_Det_HV_off                 != NULL &&
       ARC_get_Det_HV_Volts               != NULL &&
       ARC_set_Det_HV_Volts               != NULL &&
       ARC_get_Det_NumAvgRead             != NULL &&
       ARC_set_Det_NumAvgRead             != NULL &&
       ARC_Det_Read                       != NULL &&
       ARC_Det_ReadAll                    != NULL && 
       // NCL / SpectraHub start Read
       ARC_Det_Start_NonBlock_Read        != NULL &&
       ARC_Det_NonBlock_Read_Done         != NULL && 

       // NCL Filter Wheel
       ARC_get_NCL_Filter_Present         != NULL && 
       ARC_set_NCL_Filter_Present         != NULL && 
       ARC_get_NCL_Filter_Position        != NULL && 
       ARC_set_NCL_Filter_Position        != NULL && 
       ARC_get_NCL_Filter_Min_Pos         != NULL && 
       ARC_get_NCL_Filter_Max_Pos         != NULL &&  
       ARC_NCL_Filter_Home                != NULL &&     

       // NCL Shutter
       ARC_get_NCL_Shutter_Valid          != NULL && 
       ARC_get_NCL_Shutter_Open           != NULL &&  
       ARC_set_NCL_Shutter_Open           != NULL && 
       ARC_set_NCL_Shutter_Closed         != NULL && 

       // NCL TTL
       ARC_get_NCL_TTL_Valid              != NULL &&  
       ARC_get_NCL_TTL_In                 != NULL && 
       ARC_get_NCL_TTL_Out                != NULL && 
       ARC_set_NCL_TTL_Out_On             != NULL && 
       ARC_set_NCL_TTL_Out_Off            != NULL && 

       // Mono functions
       ARC_get_NCL_Mono_Setup             != NULL && 
       ARC_get_NCL_Mono_Enum              != NULL && 

       // FilterWheel
       //Communications
       ARC_Open_Filter                    != NULL && 
       ARC_Open_Filter_Port               != NULL && 
       ARC_Valid_Filter_Enum              != NULL && 
       ARC_get_Filter_preOpen_Model_CString 
                                       != NULL &&
       //Information
       ARC_get_Filter_Model_CString       != NULL && 
       ARC_get_Filter_Serial_CString      != NULL && 
       //Filter
       ARC_get_Filter_Present             != NULL && 
       ARC_get_Filter_Position            != NULL && 
       ARC_set_Filter_Position            != NULL && 
       ARC_get_Filter_Min_Pos             != NULL && 
       ARC_get_Filter_Max_Pos             != NULL && 
       ARC_Filter_Home                    != NULL &&
	   
       // PreOpen Data as Integers
 //      ARC_get_Filter_preOpen_Model_int32   != NULL &&
 //      ARC_get_Mono_preOpen_Model_int32     != NULL &&
       ARC_get_ReadOut_preOpen_Model_int32  != NULL &&
       ARC_get_Filter_preOpen_Serial_int32  != NULL &&
       ARC_get_Mono_preOpen_Serial_int32    != NULL &&
       ARC_get_ReadOut_preOpen_Serial_int32 != NULL ) 

    {
	return TRUE;
	}
	else
    {
	return FALSE;
	}
   }
   else
   {
    // Failed to load the DLL 
    return FALSE;	   
   }
}

void UnLoad_ARC_Instrument_dll()
{
long Close_Loop;

// code here to unload any open ports
for (Close_Loop = 0; Close_Loop < 15; Close_Loop++)
 ARC_Close_Enum(Close_Loop);  

// UnLoad the library that we had loaded
FreeLibrary(hARC_Instrument);

}