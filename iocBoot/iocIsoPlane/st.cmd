#IsoPlane Start-Up Script

## Set environment variables
< envPaths
epicsEnvSet "STREAM_PROTOCOL_PATH" "$(TOP)/db"

## Change to IOC application's <top> directory
cd "${TOP}"

## Register all support components
dbLoadDatabase "dbd/IsoPlaneDev.dbd"
IsoPlane_registerRecordDeviceDriver pdbbase

##Configure communications
drvAsynSerialPortConfigure("IsoPlane","COM3")
asynSetOption("IsoPlane", 0, "baud", "115200")
asynSetOption("IsoPlane", 0, "bits", "8")
asynSetOption("IsoPlane", 0, "parity", "none")
asynSetOption("IsoPlane", 0, "stop", "1")
asynSetOption("IsoPlane", 0, "clocal", "Y")
asynSetOption("IsoPlane", 0, "crtscts", "N")

## Load record instances
dbLoadTemplate("db/IsoPlane.substitutions")

## Initialise IOC instance
cd "${TOP}/iocBoot/${IOC}"
dbDumpRecord
iocInit
