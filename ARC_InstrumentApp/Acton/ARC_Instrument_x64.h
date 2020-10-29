// ARC_Instrument_x64.h 
// ARC_Instrument_x64.dll function list and hooks to the communications objects
//
// Created 2-24-2006
// By Kevin Flanagan
// Status : Development 2-24-2006
//
// hgrannis - Added ARC_IsInited() to determine if the library has been initialized.
// Status : Alpha 7-7-2006

// David Union: 3-2008: Features for progress estimates. WIP

// Exports for the functions
extern "C" _declspec(dllexport) bool ARC_Init();
extern "C" _declspec(dllexport) bool ARC_IsInited(); // hgrannis - added 7-7-2006
extern "C" _declspec(dllexport) bool ARC_Ver(long * Major, long * Minor, long * Build);
extern "C" _declspec(dllexport) void ARC_Error_To_English(long Error_Code,char * Error_Str,long Error_Str_sz);

//
// We need variants that do not go out of memory when working with them ...
//

//Communications
extern "C" _declspec(dllexport) bool ARC_Search_For_Inst(long * Num_Found);
extern "C" _declspec(dllexport) long ARC_get_Num_Found_Inst_Ports();
// Simplified looking at Acton Instruments before we open them, type generic
extern "C" _declspec(dllexport) bool ARC_get_Enum_preOpen_Model(long Enum,char *Model_Str, long Model_Str_sz,long *Error_Code);
extern "C" _declspec(dllexport) bool ARC_get_Enum_preOpen_Model_int32(long Enum,long *Model_int32,long *Error_Code);
extern "C" _declspec(dllexport) bool ARC_get_Enum_preOpen_Serial_int32(long Enum,long *Serial_int32,long *Error_Code);
extern "C" _declspec(dllexport) bool ARC_get_Enum_preOpen_COM(long Enum, long *COMx,long *Error_Code);

extern "C" _declspec(dllexport) bool ARC_get_Enum_Model(long Enum,char *Model_Str, long Model_Str_sz,long *Error_Code);
extern "C" _declspec(dllexport) long ARC_get_Enum_Model_int32(long Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool ARC_get_Enum_Serial(long Enum,char *Serial_Str, long Serial_Str_sz,long *Error_Code);
extern "C" _declspec(dllexport) long ARC_get_Enum_Serial_int32(long Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool ARC_get_Enum_COM(long Enum, long *COMx,long *Error_Code);

extern "C" _declspec(dllexport) bool  ARC_Open_Mono(long Enum_Num,long * Mono_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Open_Mono_Port(long Com_Num,long *Mono_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Open_Mono_Serial(long Serial_Num, long * Mono_Enum, long *Model, long *Error_Code);

extern "C" _declspec(dllexport) bool  ARC_Close_Enum(long Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Valid_Mono_Enum(long Mono_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Valid_v6_Mono_Enum(long Mono_Enum,long *Error_Code);// for when we need to know if it is a more modern generation controller
extern "C" _declspec(dllexport) bool  ARC_get_Mono_preOpen_Valid(long Enum_Num,long *Error_Code);
//extern "C" _declspec(dllexport) bool  ARC_get_Mono_preOpen_Model(long Enum_Num,VARIANT Model_Var,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_preOpen_Model_CharStr(long Enum_Num, char * ModelStr,long ModelStr_sz,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_preOpen_Model_int32(long Enum_Num,long * Model_int32,long *Error_Code);
// direct communications function 
//extern "C" _declspec(dllexport) bool  ARC_Send_CMD_To_Inst(long Enum, VARIANT SendCMD, VARIANT RCV_Var,long ms_TimeOut,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Send_CMD_To_Inst_CharStr(long Enum, char * SendCMD,long SendCMD_sz,char * RCV_Str,long RCV_Str_sz, long ms_TimeOut,long *Error_Code);

//Information
//extern "C" _declspec(dllexport) bool  ARC_get_Mono_Model(long Mono_Enum, VARIANT * Model_Var,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Model_CharStr(long Mono_Enum,char * ModelStr, long ModelStr_sz,long *Error_Code);
//extern "C" _declspec(dllexport) bool  ARC_get_Mono_Serial(long Mono_Enum, VARIANT Serial_Var,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Serial_CharStr(long Mono_Enum,char * SerialStr,long SerialStr_sz,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Focallength(long Mono_Enum,double * Focallength,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_HalfAngle(long Mono_Enum,double * HalfAngle,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_DetectorAngle(long Mono_Enum,double * DetectorAngle,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Double(long Mono_Enum,bool * Double_Present,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Double_Subtractive(long Mono_Enum,bool * Double_Subtractive,long *Error_Code);
extern "C" _declspec(dllexport) long  ARC_get_Mono_Precision(long Mono_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Backlash_Steps(long Mono_Enum,long * Backlash,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Gear_Steps(long Mono_Enum,long * minor_steps,long * major_steps,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_nmRev_Ratio(long Mono_Enum,double * nmRev_Ratio,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_nmRev(long Mono_Enum,double * nm,double * Rev,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_COM(long Mono_Enum,long * COMx,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_preOpen_COM(long Mono_Enum,long * COMx,long *Error_Code);

// PI Calibration functions
extern "C" _declspec(dllexport) bool  ARC_get_PI_Calibrated (long Mono_Enum,long Grat_num,  bool * Calibrated,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_PI_Offset     (long Mono_Enum,long Grat_num,double * PI_Offset,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_PI_GAdjust    (long Mono_Enum,long Grat_num,double * PI_GAdjust,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_PI_FocalLength(long Mono_Enum,long Grat_num,double * PI_FocalLength,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_PI_HalfAngle  (long Mono_Enum,long Grat_num,double * PI_HalfAngle,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_PI_DetAngle   (long Mono_Enum,long Grat_num,double * PI_DetAngle,long *Error_Code);

extern "C" _declspec(dllexport) bool  ARC_set_PI_Calibrated (long Mono_Enum,long Grat_num,bool Calibrated,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_PI_Offset     (long Mono_Enum,long Grat_num,double PI_Offset,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_PI_GAdjust    (long Mono_Enum,long Grat_num,double PI_GAdjust,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_PI_FocalLength(long Mono_Enum,long Grat_num,double PI_FocalLength,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_PI_HalfAngle  (long Mono_Enum,long Grat_num,double PI_HalfAngle,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_PI_DetAngle   (long Mono_Enum,long Grat_num,double PI_DetAngle,long *Error_Code);

// CCD Pixel Mapping
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Pixel_Map_nm    (long Mono_Enum,double Pixel_Size_um,long Number_X_Pixels,double Left_Adj_Percent,double Center_Adj_Pixels,double Right_Adj_Percent,double *Pixel_Map,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Pixel_Map_ang   (long Mono_Enum,double Pixel_Size_um,long Number_X_Pixels,double Left_Adj_Percent,double Center_Adj_Pixels,double Right_Adj_Percent,double *Pixel_Map,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Pixel_Map_eV    (long Mono_Enum,double Pixel_Size_um,long Number_X_Pixels,double Left_Adj_Percent,double Center_Adj_Pixels,double Right_Adj_Percent,double *Pixel_Map,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Pixel_Map_micron(long Mono_Enum,double Pixel_Size_um,long Number_X_Pixels,double Left_Adj_Percent,double Center_Adj_Pixels,double Right_Adj_Percent,double *Pixel_Map,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Pixel_Map_absCM (long Mono_Enum,double Pixel_Size_um,long Number_X_Pixels,double Left_Adj_Percent,double Center_Adj_Pixels,double Right_Adj_Percent,double *Pixel_Map,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Pixel_Map_relCM (long Mono_Enum,double Pixel_Size_um,long Number_X_Pixels,double Laser_Line_nm,double Left_Adj_Percent,double Center_Adj_Pixels,double Right_Adj_Percent,double *Pixel_Map,long *Error_Code);

//Wavelength
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Wavelength_nm(long Mono_Enum,double * Wavelength,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Wavelength_nm_Stored(long Mono_Enum,double * Wavelength,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Wavelength_nm(long Mono_Enum,double Wavelength,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Wavelength_ang(long Mono_Enum,double * Wavelength,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Wavelength_ang(long Mono_Enum,double Wavelength,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Wavelength_eV(long Mono_Enum,double * Wavelength,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Wavelength_eV(long Mono_Enum,double Wavelength,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Wavelength_micron(long Mono_Enum,double * Wavelength,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Wavelength_micron(long Mono_Enum,double Wavelength,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Wavelength_absCM(long Mono_Enum,double * Wavelength,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Wavelength_absCM(long Mono_Enum,double Wavelength,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Wavelength_relCM(long Mono_Enum,double Center_nm,double * Wavelength,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Wavelength_relCM(long Mono_Enum,double Center_nm,double Wavelength,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Wavelength_Cutoff_nm(long Mono_Enum,double * Wavelength,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Wavelength_Min_nm(long Mono_Enum,double * Wavelength,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Wavelength_nm_ProcessTime(long Mono_Enum, double wavelength, long *processTime, long *errorCode);

//Grating
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Turret(long Mono_Enum,long * Turret,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Turret(long Mono_Enum,long Turret,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Turret_Gratings(long Mono_Enum,long * Gratings_Per_Turret,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Turret_Max(long Mono_Enum,long * Max_Turret_Number,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Grating(long Mono_Enum,long * Grating,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Grating(long Mono_Enum,long Grating,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Grating_ProcessTime(long Mono_Enum,long Grating,long *processTime, long *Error_Code);


//extern "C" _declspec(dllexport) bool  ARC_get_Mono_Grating_Blaze(long Mono_Enum,long Grating,VARIANT *Blaze_Var,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Grating_Blaze_CharStr(long Mono_Enum,long Grating,char *BlazeStr,long BlazeStr_sz,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Grating_Density(long Mono_Enum,long Grating,long * Groove_MM,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Grating_Installed(long Mono_Enum,long Grating,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Grating_Max(long Mono_Enum,long * Max_Grating_Number,long *Error_Code);

//Mirrors
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Diverter_Valid(long Mono_Enum,long Diverter_Num,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Diverter_Pos(long Mono_Enum,long Diverter_Num,long  * Diverter_Pos,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Diverter_Pos(long Mono_Enum,long Diverter_Num,long  Diverter_Pos,long *Error_Code);
//extern "C" _declspec(dllexport) bool  ARC_get_Mono_Diverter_Pos_Var(long Mono_Enum,long Diverter_Num,VARIANT Diverter_Pos,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Diverter_Pos_CharStr(long Mono_Enum,long Diverter_Num,char *Diverter_Pos,long Diverter_Pos_sz,long *Error_Code);

//Slits
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Slit_Type(long Mono_Enum,long Slit_Pos,long * Slit_Type,long *Error_Code);
//extern "C" _declspec(dllexport) bool  ARC_get_Mono_Slit_Type_Var(long Mono_Enum,long Slit_Pos,VARIANT Slit_Type,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Slit_Type_CharStr(long Mono_Enum,long Slit_Pos,char *Slit_Type,long Slit_Type_sz,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Slit_Width(long Mono_Enum,long Slit_Pos,long * Slit_Width,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Slit_Width(long Mono_Enum,long Slit_Pos,long Slit_Width,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Slit_Width_ProcessTime(long Mono_Enum, long Slit_Pos, long Slit_Width, long *processTime, long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Slit_Max(long monoEnum, long slitPos, long *slitWith, long *errorCode);
// DMU: Might need Slit_Home_ProcessTime()

extern "C" _declspec(dllexport) bool  ARC_Mono_Slit_Home(long Mono_Enum,long Slit_Pos,long *Error_Code);
//extern "C" _declspec(dllexport) bool  ARC_Mono_Slit_Name_Var(long Slit_Num,VARIANT Slit_Name_Var,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Slit_Name_CharStr(long Slit_Num,char * Slit_NameStr,long Slit_NameStr_sz,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Calc_Mono_Slit_BandPass(long Mono_Enum,long Slit_Pos,double SlitWidth,double * BandPass,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Slit_BandPass(long Mono_Enum,long Slit_Pos,double * BandPass,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Slit_BandPass(long Mono_Enum,long Slit_Pos,double BandPass,long *Error_Code);
// Special Double function 
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Double_Intermediate_Slit(long Mono_Enum,long * Slit_Pos,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Exit_Slit(long Mono_Enum,long * Slit_Pos,long *Error_Code);

//Filter
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Filter_Present(long Mono_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Filter_Position(long Mono_Enum,long * Position,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Filter_Position(long Mono_Enum,long  Position,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Filter_Position_ProcessTime(long Mono_Enum,long  Position,long* processTime, long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Filter_Min_Pos(long Mono_Enum,long * Position,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Filter_Max_Pos(long Mono_Enum,long * Position,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Filter_Home(long Mono_Enum,long *Error_Code);
              
// XY-Sample
extern "C" _declspec(dllexport) bool  ARC_get_Mono_XYSample_Present(long Mono_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_XYSample_XPosition_Inches(long Mono_Enum,double * XPosition,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_XYSample_YPosition_Inches(long Mono_Enum,double * YPosition,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_XYSample_XPosition_Inches(long Mono_Enum,double XPosition,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_XYSample_YPosition_Inches(long Mono_Enum,double YPosition,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_XYSample_HomeX(long Mono_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_XYSample_HomeY(long Mono_Enum,long *Error_Code);

// Sample Wheel
// a wheel num of 0 is Manual sample and only used in cams software
// a wheel num of 1 is RSample
// a wheel num of 2 is TSample
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Sample_Present        (long Mono_Enum,long Wheel_Num,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Sample_Position       (long Mono_Enum,long Wheel_Num,long * Position,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Sample_Position       (long Mono_Enum,long Wheel_Num,long Position,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Sample_Home               (long Mono_Enum,long Wheel_Num,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Sample_WheelType_Index(long Mono_Enum,long Wheel_Num,long * WheelType,long *Error_Code);
//extern "C" _declspec(dllexport) bool  ARC_get_Mono_Sample_WheelType_Var  (long Mono_Enum,long Wheel_Num,VARIANT * WheelType_Var,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Sample_WheelType_CharStr  (long Mono_Enum,long Wheel_Num,char * WheelType,long WheelType_sz,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Sample_WheelType      (long Mono_Enum,long Wheel_Num,long WheelType,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Sample_Min_Pos        (long Mono_Enum,long Wheel_Num,long * Position,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Sample_Max_Pos        (long Mono_Enum,long Wheel_Num,long * Position,long *Error_Code);

// advanced functions
// Gear
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Int_Led_On(long Mono_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Int_Led(long Mono_Enum,bool Led_State,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Motor_Int(long Mono_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Wheel_Int(long Mono_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Move_Steps(long Mono_Enum,long Num_Steps,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Sine_Drive(long Mono_Enum,long *Error_Code);

// Grating Values
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Init_Grating(long Mono_Enum,long * Init_Grating,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Init_Grating(long Mono_Enum,long Init_Grating,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Init_Wave_nm(long Mono_Enum,double * Init_Wave,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Init_Wave_nm(long Mono_Enum,double Init_Wave,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Init_ScanRate_nm(long Mono_Enum,double  * Init_ScanRate,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Init_ScanRate_nm(long Mono_Enum,double   Init_ScanRate,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Grating_Offset(long Mono_Enum,long Grating,long * Offset,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Grating_Gadjust(long Mono_Enum,long Grating,long  * Gadjust,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Grating_Offset(long Mono_Enum,long Grating,long  Offset,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Grating_Gadjust(long Mono_Enum,long Grating,long Gadjust,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Grating_Calc_Offset(long Mono_Enum,long Grating,double Wave,double RefWave,long * newOffset,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Grating_Calc_Gadjust(long Mono_Enum,long Grating,double Wave,double RefWave,long * newGadjust,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Grating_UnInstall(long Mono_Enum,long Grating, bool Reboot,long *Error_Code);
//extern "C" _declspec(dllexport) bool  ARC_Mono_Grating_Install(long Mono_Enum,long Grating,long Density,VARIANT Blaze,bool NMBlaze,bool umBlaze,bool HOLBlaze,bool MIRROR,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Grating_Install_CharStr(long Mono_Enum,long Grating,long Density,char * Blaze,long Blaze_sz,bool NMBlaze,bool umBlaze,bool HOLBlaze,bool MIRROR, bool Reboot,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Reset(long Mono_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Restore_Factory_Settings(long Mono_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Save_Factory_Settings(long Mono_Enum,long password,long *Error_Code);

// Scan Values`
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Scan_Rate_nm_min (long Mono_Enum,double * Scan_Rate,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Scan_Rate_nm_min (long Mono_Enum,double Scan_Rate,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Start_Scan_To_nm (long Mono_Enum,double Wavelength_nm,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Scan_Done (long Mono_Enum,bool * Done_Moving,double * Current_Wavelength_nm,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Start_Jog (long Mono_Enum,bool Jog_MaxRate,bool JogUp,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Stop_Jog (long Mono_Enum,long *Error_Code);

// shutter control for v6 controllers
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Shutter_Valid (long Mono_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_Shutter_Open (long Mono_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Shutter_Open (long Mono_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Mono_Shutter_Closed (long Mono_Enum,long *Error_Code);

// NCL / NCL Light specific functions
// NCL Communications functions
extern "C" _declspec(dllexport) bool  ARC_Open_ReadOut_SpectraHub(long Port_Num,long * NCL_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Open_ReadOut_Port_SpectraHub(long Com_Num,long * NCL_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Open_ReadOut(long Port_Num,long * NCL_Enum,long * Mono1_Enum,long * Mono2_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Open_ReadOut_Port(long Com_Num,long * NCL_Enum,long * Mono1_Enum,long * Mono2_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Valid_Enum(long Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Valid_ReadOut_Enum(long NCL_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_ReadOut_preOpen_Valid(long NCL_Enum,long *Error_Code);
//extern "C" _declspec(dllexport) bool  ARC_get_ReadOut_preOpen_Model(long NCL_Enum,VARIANT Model_Var,long *Error_Code); 
extern "C" _declspec(dllexport) bool  ARC_get_ReadOut_preOpen_Model_int32(long NCL_Enum,long * Model_int32,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_ReadOut_preOpen_Model_CharStr(long NCL_Enum,char *ModelStr,long ModelStr_sz,long *Error_Code);

//Information
//extern "C" _declspec(dllexport) bool  ARC_get_ReadOut_Model(long NCL_Enum,VARIANT Model_Var,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_ReadOut_Model_CharStr(long NCL_Enum,char * ModelStr,long ModelStr_sz,long *Error_Code);
//extern "C" _declspec(dllexport) bool  ARC_get_ReadOut_Serial(long NCL_Enum,VARIANT  Serial_Var,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_ReadOut_Serial_CharStr(long NCL_Enum,char * SerialStr,long SerialStr_sz,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_ReadOut_COM(long Inst_Enum,long * COMx,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_ReadOut_preOpen_COM(long Inst_Enum,long * COMx,long *Error_Code);

// SpectraHub stacking functions
extern "C" _declspec(dllexport) bool  ARC_Add_Readout(long Enum, long Hub_Enum, long SpectraHub_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Readout_Device_Enum(long NCL_Enum,long * Device_Enum,long *Error_Code);

// Detector functions
extern "C" _declspec(dllexport) long  ARC_get_Num_Det(long NCL_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Valid_Det_Num(long NCL_Enum,long Det_Num,long *Error_Code);
extern "C" _declspec(dllexport) long  ARC_get_ReadOut_ITime_ms(long NCL_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_ReadOut_ITime_ms(long NCL_Enum,long ITime_ms,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Det_Type(long NCL_Enum,long Det_Num,long * DetType,long *Error_Code);
//extern "C" _declspec(dllexport) bool  ARC_get_Det_Type_Str(long NCL_Enum,long Det_Num,VARIANT * DetType,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Det_Type_CharStr(long NCL_Enum,long Det_Num,char * DetType,long DetType_sz,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Det_Type(long NCL_Enum,long Det_Num,long DetType,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Det_Photon (long NCL_Enum,long Det_Num,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Det_Voltage(long NCL_Enum,long Det_Num,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Det_Current(long NCL_Enum,long Det_Num,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Det_BiPolar(long NCL_Enum,long Det_Num,long *Error_Code);
//extern "C" _declspec(dllexport) bool  ARC_get_Det_BiPolar_Str(long NCL_Enum,long Det_Num,VARIANT BiPolarStr,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Det_BiPolar_CharStr(long NCL_Enum,long Det_Num,char * BiPolarStr,long BiPolarStr_sz,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Det_BiPolar(long NCL_Enum,long Det_Num,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Det_UniPolar(long NCL_Enum,long Det_Num,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Det_Range(long NCL_Enum,long Det_Num,long * Range,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Det_Range_Factor(long NCL_Enum,long Det_Num,long * Range_Factor,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Det_Range(long NCL_Enum,long Det_Num,long Range,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Det_HV_on(long NCL_Enum,long Det_Num,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Det_HV_on(long NCL_Enum,long Det_Num,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Det_HV_off(long NCL_Enum,long Det_Num,long *Error_Code);
extern "C" _declspec(dllexport) long  ARC_get_Det_HV_Volts(long NCL_Enum,long Det_Num,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Det_HV_Volts(long NCL_Enum,long Det_Num,long HV_Volts,long *Error_Code);
extern "C" _declspec(dllexport) long  ARC_get_Det_NumAvgRead(long NCL_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Det_NumAvgRead(long NCL_Enum,long NumReadsAvg,long *Error_Code);
extern "C" _declspec(dllexport) long  ARC_get_NCL_Det_Units(long NCL_Enum,long *Error_Code); // : ReadUnits2;
extern "C" _declspec(dllexport) long  ARC_get_NCL_Det_Units_Index(long NCL_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_NCL_Det_Units_String(long NCL_Enum,long Det_Num,char *ReadUnits_Str,long ReadUnits_Str_sz,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_NCL_Det_Units(long NCL_Enum,long ReadingUnits /* : ReadUnits2 */,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_NCL_Det_Units_Index(long NCL_Enum,long ReadingUnits,long *Error_Code);	
extern "C" _declspec(dllexport) double  ARC_get_NCL_Det_Saturation(long NCL_Enum,long Det_Num,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Det_Read(long NCL_Enum,long Det_Num,double * Read_Value,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Det_ReadAll(long NCL_Enum,double * Det1_Value,double * Det2_Value,double * Det3_Value,long *Error_Code);
// I vs T functions
extern "C" _declspec(dllexport) bool   ARC_start_TimeScan_SingleChannel (long NCL_Enum,long Det_Num,long Interval,long NumberPoints,long *Error_Code);
extern "C" _declspec(dllexport) bool   ARC_stream_TimeScan_SingleChannel(long NCL_Enum,long Det_Num,long *Error_Code);
extern "C" _declspec(dllexport) bool   ARC_start_TimeScan_AllChannels   (long NCL_Enum,long Interval,long  NumberPoints,long *Error_Code);
extern "C" _declspec(dllexport) bool   ARC_stream_TimeScan_AllChannels  (long NCL_Enum,long *Error_Code);
extern "C" _declspec(dllexport) long   ARC_get_TimeScan_CurPointNum (long NCL_Enum,long Det_Num,long *Error_Code);
extern "C" _declspec(dllexport) double ARC_get_TimeScan_PointValue  (long NCL_Enum,long Det_Num,long Point_Num,long *Error_Code);
extern "C" _declspec(dllexport) bool   ARC_stop_TimeScan (long NCL_Enum,long *Error_Code);
// NCL / SpectraHub start Read
extern "C" _declspec(dllexport) bool   ARC_Det_Start_NonBlock_Read(long NCL_Enum,long Det_Num,long *Error_Code);
extern "C" _declspec(dllexport) bool   ARC_Det_NonBlock_Read_Done (long NCL_Enum,long Det_Num,double * Read_Value,long *Error_Code);  

// NCL scanning functions

// NCL Filter Wheel
extern "C" _declspec(dllexport) bool  ARC_get_NCL_Filter_Present(long NCL_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_NCL_Filter_Present(long NCL_Enum,long Min_Filter,long Max_Filter,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_NCL_Filter_Position(long NCL_Enum,long * Position,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_NCL_Filter_Position(long NCL_Enum,long Position,long *Error_Code);

// DMU: For Progress Bars
extern "C" _declspec(dllexport) bool  ARC_get_NCL_Filter_Position_ProcessTime(long NCL_Enum,long Position,long *processTime, long *Error_Code);


extern "C" _declspec(dllexport) bool  ARC_get_NCL_Filter_Min_Pos(long NCL_Enum,long * Min_Pos,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_NCL_Filter_Max_Pos(long NCL_Enum,long * Max_Pos,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_NCL_Filter_Home(long NCL_Enum,long *Error_Code);

// NCL Shutter
extern "C" _declspec(dllexport) bool  ARC_get_NCL_Shutter_Valid(long NCL_Enum,long Shutter_Num,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_NCL_Shutter_Open(long NCL_Enum,long Shutter_Num,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_NCL_Shutter_Open(long NCL_Enum,long Shutter_Num,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_NCL_Shutter_Closed(long NCL_Enum,long Shutter_Num,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_SpectraHub_Shutter_Enabled(long Hub_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_SpectraHub_Shutter_Enable (long Hub_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_SpectraHub_Shutter_Disable(long Hub_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_SpectraHub_Shutter_Open_High(long Hub_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_SpectraHub_Shutter_Open_High(long Hub_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_SpectraHub_Shutter_Open_Low (long Hub_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_SpectraHub_Shutter_Open(long Hub_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_SpectraHub_Shutter_Open(long Hub_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_SpectraHub_Shutter_Closed(long Hub_Enum,long *Error_Code);

// NCL TTL
extern "C" _declspec(dllexport) bool  ARC_get_NCL_TTL_Valid(long NCL_Enum,long TTL_Line,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_NCL_TTL_In(long NCL_Enum,long TTL_Line,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_NCL_TTL_Out(long NCL_Enum,long TTL_Line,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_NCL_TTL_Out_On(long NCL_Enum,long TTL_Line,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_NCL_TTL_Out_Off(long NCL_Enum,long TTL_Line,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_SpectraHub_Trig_On( long Hub_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_SpectraHub_Trig_On( long Hub_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_SpectraHub_Trig_Off(long Hub_Enum,long *Error_Code);

// Mono functions
extern "C" _declspec(dllexport) bool  ARC_get_NCL_Mono_Setup(long NCL_Enum,long Mono_Num,long *Error_Code);
extern "C" _declspec(dllexport) long  ARC_get_NCL_Mono_Enum(long NCL_Enum,long Mono_Num,long *Error_Code);

// FilterWheel
//Communications
extern "C" _declspec(dllexport) bool  ARC_Open_Filter(long Enum_Num,long * Filter_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Open_Filter_Port(long Com_Num,long * Filter_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Open_Filter_Serial(long Serial_Num,long * Filter_Enum, long* Model, long *Error_Code);

extern "C" _declspec(dllexport) bool  ARC_Valid_Filter_Enum(long Filter_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Filter_preOpen_Valid(long Enum_Num,long *Error_Code);
//extern "C" _declspec(dllexport) bool  ARC_get_Filter_preOpen_Model(long Enum_Num,VARIANT Model_Var,long *Error_Code);  
extern "C" _declspec(dllexport) bool  ARC_get_Filter_preOpen_Model_int32(long Enum_Num,long * Model_int32,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Filter_preOpen_Model_CharStr(long Enum_Num,char * ModelStr,long ModelStr_sz,long *Error_Code);

//Information
//extern "C" _declspec(dllexport) bool  ARC_get_Filter_Model(long Filter_Enum,VARIANT Model_Var,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Filter_Model_CharStr(long Filter_Enum,char * ModelStr,long ModelStr_sz,long *Error_Code);
//extern "C" _declspec(dllexport) bool  ARC_get_Filter_Serial(long Filter_Enum,VARIANT * Serial_Var,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Filter_Serial_CharStr(long Filter_Enum,char * SerialStr,long SerialStr_sz,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Filter_COM(long Filter_Enum,long * COMx,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Filter_preOpen_COM(long Filter_Enum,long * COMx,long *Error_Code);

//Filter
extern "C" _declspec(dllexport) bool  ARC_get_Filter_Present(long Filter_Enum,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Filter_Position(long Filter_Enum, long * Position,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_set_Filter_Position(long Filter_Enum, long Position, long *Error_Code);

// DMU: For Progress Bar - maybe processTime -> processMilliSeconds to make it more clear?
extern "C" _declspec(dllexport) bool  ARC_get_Filter_Position_ProcessTime(long Filter_Enum, long Position , long* processTime, long *errorCode);
extern "C" _declspec(dllexport) bool  ARC_get_Filter_Min_Pos(long Filter_Enum,long * Position,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Filter_Max_Pos(long Filter_Enum,long * Position,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Filter_Home(long Filter_Enum,long *Error_Code);

// Setup Values for v6 controllers
//extern "C" _declspec(dllexport) bool  ARC_Mono_set_Model(long Mono_Enum,VARIANT Model_Var,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_set_Model_CharStr(long Mono_Enum,char * Model_Str,long Model_Str_sz,long Passwd,long *Error_Code);
//extern "C" _declspec(dllexport) bool  ARC_Mono_set_Serial(long Mono_Enum,VARIANT Serial_Var,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_set_Serial_CharStr(long Mono_Enum,char * Serial_Str,long Serial_Str_sz,long Passwd,long *Error_Code);
//extern "C" _declspec(dllexport) bool  ARC_Mono_get_Board_Serial(long Mono_Enum,VARIANT * Serial_Var,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_get_Board_Serial_CharStr(long Mono_Enum,char * Serial_Str,long Serial_Str_sz,long Passwd,long *Error_Code);
//extern "C" _declspec(dllexport) bool  ARC_Mono_set_Board_Serial(long Mono_Enum,VARIANT Serial_Var,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_set_Board_Serial_CharStr(long Mono_Enum,char * Serial_Str,long Serial_Str_sz,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_set_Drive_Linear (long Mono_Enum,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_set_nmRev(long Mono_Enum,double nm,double Rev,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_set_Drive_Sine (long Mono_Enum,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_set_Gratings_Per_Turret (long Mono_Enum,long Grating_per_Turret,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_set_Halfangle (long Mono_Enum,double HalfAngle,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_set_Gear_Ratio (long Mono_Enum,long minor,long major,double base,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_set_Backlash (long Mono_Enum,long Backlash,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Read_Motors(long Mono_Enum,long * OnBoard1,long * OnBoard2,long * OnBoard3,long * Daughter1,long * Daughter2,long * Daughter3,long * Daughter4,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_set_Use(long Mono_Enum,long Motor,long Motor_Use,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_set_Stop(long Mono_Enum,long Motor,long Motor_Stop,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_set_Speed(long Mono_Enum,long Motor,long Motor_Speed,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_set_StepRev(long Mono_Enum,long Motor,long Steps_per_Rev,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_set_eeoptions(long Mono_Enum,char *Options_Str,long Option_Str_sz,long Passwd,long *Error_Code);
//extern "C" _declspec(dllexport) bool  ARC_Mono_Grating_Install_NoHello(long Mono_Enum,long Grating,long Density,VARIANT Blaze,bool NMBlaze,bool umBlaze,bool HOLBlaze,bool MIRROR,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Grating_Install_NoHello_CharStr(long Mono_Enum,long Grating,long Density,char * Blaze,long Blaze_sz,bool NMBlaze,bool umBlaze,bool HOLBlaze,bool MIRROR,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_set_Motor_Pos_Step(long Mono_Enum,long Motor,long Motor_Pos,long Step,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_set_Motor_Min_Pos(long Mono_Enum,long Motor,long Min_Motor_Pos,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_set_Motor_Max_Pos(long Mono_Enum,long Motor,long Max_Motor_Pos,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Grating_UnInstall_NoHello(long Mono_Enum,long Grating,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_set_Focallength(long Mono_Enum,long FocalLength,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_set_DetectorAngle(long Mono_Enum,double DetAngle,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Clear_Mono_Setup(long Mono_Enum,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_set_SlitClamp(long Mono_Enum,long Motor,long Clamp_Value,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Read_Motors_SlitClamp(long Mono_Enum,long * OnBoard1,long * OnBoard2,long * OnBoard3,long * Daughter1,long * Daughter2,long * Daughter3,long * Daughter4,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Read_Motors_SFreq(long Mono_Enum,long * OnBoard1,long * OnBoard2,long * OnBoard3,long * Daughter1,long * Daughter2,long * Daughter3,long * Daughter4,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Read_Motors_Microns_to_Steps(long Mono_Enum,long * OnBoard1,long * OnBoard2,long * OnBoard3,long * Daughter1,long * Daughter2,long * Daughter3,long * Daughter4,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Read_Motors_Steps_to_Microns(long Mono_Enum,long * OnBoard1,long * OnBoard2,long * OnBoard3,long * Daughter1,long * Daughter2,long * Daughter3,long * Daughter4,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Read_Motors_SlitHome(long Mono_Enum,long * OnBoard1,long * OnBoard2,long * OnBoard3,long * Daughter1,long * Daughter2,long * Daughter3,long * Daughter4,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_set_SFreq(long Mono_Enum,long Motor,long SFreq_Value,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_set_Microns_to_Steps(long Mono_Enum,long Motor,long Microns_to_Steps,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_set_Steps_to_Microns(long Mono_Enum,long Motor,long Steps_to_Microns,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_set_SlitHome(long Mono_Enum,long Motor,long SlitHome,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_get_Slit_Hz(long Mono_Enum,long Motor,long  * Hz,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_get_Motor_Chan(long Mono_Enum,long Motor,long * Motor_Chan,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_get_Motor_StepStop(long Mono_Enum,long Motor,long * StepStop,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_get_Motor_Accel(long Mono_Enum,long Motor,long * Accel,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_get_Motor_lraf(long Mono_Enum,long Motor,long * Motor_lraf,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_get_Motor_hraf(long Mono_Enum,long Motor,long * Motor_hraf,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_get_Motor_mper(long Mono_Enum,long Motor,long * Motor_mper,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_set_Motor_mper(long Mono_Enum,long Motor,long Motor_mper,long Passwd,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_get_Motor_App(long Mono_Enum,long Motor,long * Motor_App,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_get_Motor_Index_Min_Pos(long Mono_Enum,long Motor,long * Index_Min_Pos,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_get_Motor_Index_Max_Pos(long Mono_Enum,long Motor,long * Index_Max_Pos,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_get_Motor_Speed(long Mono_Enum,long Motor,long * Speed,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_get_Motor_Step_Offset(long Mono_Enum,long Motor,long * Step_Offset,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_get_Motor_Step_Rev(long Mono_Enum,long Motor,long * Step_Rev,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_Mono_Motor_get_Motor_Step_Pos(long Mono_Enum,long Motor,long Position,long * Step_Pos,long *Error_Code);

// Serial Number Integers  
extern "C" _declspec(dllexport) bool  ARC_get_Filter_preOpen_Serial_int32(long Filter_Enum,long * Serial_int32,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_Mono_preOpen_Serial_int32(long Mono_Enum,long * Serial_int32,long *Error_Code);
extern "C" _declspec(dllexport) bool  ARC_get_ReadOut_preOpen_Serial_int32(long ReadOut_Enum,long * Serial_int32,long *Error_Code);
extern "C" _declspec(dllexport) long  ARC_get_Filter_Serial_int32(long Filter_Enum,long *Error_Code);
extern "C" _declspec(dllexport) long  ARC_get_Mono_Serial_int32(long Mono_Enum,long *Error_Code);
extern "C" _declspec(dllexport) long  ARC_get_ReadOut_Serial_int32(long Readout_Enum,long *Error_Code);

// plug and pray support
typedef void (*callbackFcn)(wchar_t*);
extern "C" _declspec(dllexport) long ARC_SubscribeForPnPNotification(callbackFcn cbf); //, wchar_t* msg);
extern "C" _declspec(dllexport) long ARC_UnSubscribeForPnPNotification(callbackFcn cbf); //, wchar_t* msg);