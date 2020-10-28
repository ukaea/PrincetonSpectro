#ARC_Instrument Start-Up Script

## Set environment variables
< envPaths

## Change to IOC application's <top> directory
cd "${TOP}"

epicsEnvSet("ASYNPORT", "MAST")

## Register all support components
dbLoadDatabase "dbd/ARC_Instrument.dbd"
ARC_Instrument_registerRecordDeviceDriver pdbbase
ARC_InstrumentPortDriverConfigure($(ASYNPORT), 0)

## Load record instances
dbLoadTemplate("db/ARC_Instrument.substitutions", "PORT=$(ASYNPORT),ADDR=0")

## Initialise IOC instance
cd "${TOP}/iocBoot/${IOC}"
dbDumpRecord
iocInit
