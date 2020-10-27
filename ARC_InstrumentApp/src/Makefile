TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

LIBRARY_IOC = ARCInstrumentDev
PROD_IOC = ARCInstrumentApp

# IsoPlaneDev.dbd will be created and installed
DBD += ARCInstrument.dbd

# IsoPlaneDev.dbd will be made up from these files:
ARCInstrument_DBD += base.dbd

# Include dbd files from all support applications:
ARCInstrument_DBD += asyn.dbd
ARCInstrument_DBD += drvAsynSerialPort.dbd

# Add all the support libraries needed by this IOC
ARCInstrumentDev_LIBS += asyn
ARCInstrumentApp_LIBS += asyn

# IsoPlane_registerRecordDeviceDriver.cpp derives from IsoPlaneDev.dbd
IsoPlaneDev_SRCS += ARC_USB.cpp
IsoPlaneDev_SRCS += ARCInstrument_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
ARCInstrumentApp_SRCS_DEFAULT += ARCInstrumentMain.cpp
ARCInstrumentApp_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#IsoPlane_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
ARCInstrumentDev_LIBS += $(EPICS_BASE_IOC_LIBS)
ARCInstrumentApp_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

