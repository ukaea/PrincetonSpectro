#ARC_Instrument Start-Up Script

## Set environment variables
< envPaths
epicsEnvSet "STREAM_PROTOCOL_PATH" "$(TOP)/db"

## Change to IOC application's <top> directory
cd "${TOP}"

## Register all support components
dbLoadDatabase "dbd/ARC_InstrumentDev.dbd"
ARC_Instrument_registerRecordDeviceDriver pdbbase

##Configure communications
drvAsynSerialPortConfigure("ARC_Instrument","COM3")
asynSetOption("ARC_Instrument", 0, "baud", "115200")
asynSetOption("ARC_Instrument", 0, "bits", "8")
asynSetOption("ARC_Instrument", 0, "parity", "none")
asynSetOption("ARC_Instrument", 0, "stop", "1")
asynSetOption("ARC_Instrument", 0, "clocal", "Y")
asynSetOption("ARC_Instrument", 0, "crtscts", "N")

## Load record instances
dbLoadTemplate("db/ARC_Instrument.substitutions")

## Initialise IOC instance
cd "${TOP}/iocBoot/${IOC}"
dbDumpRecord
iocInit
