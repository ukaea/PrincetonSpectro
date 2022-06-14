TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

LIBRARY_IOC = IsoPlaneDev
PROD_IOC = IsoPlaneApp

# IsoPlaneDev.dbd will be created and installed
DBD += IsoPlane.dbd

# IsoPlaneDev.dbd will be made up from these files:
IsoPlane_DBD += base.dbd

# Include dbd files from all support applications:
IsoPlane_DBD += asyn.dbd
IsoPlane_DBD += drvAsynSerialPort.dbd
IsoPlane_DBD += calc.dbd
IsoPlane_DBD += $(STREAM)/dbd/stream.dbd

# Add all the support libraries needed by this IOC
# IsoPlaneDev_LIBS += stream asyn
IsoPlaneApp_LIBS += stream asyn calc

# IsoPlane_registerRecordDeviceDriver.cpp derives from IsoPlaneDev.dbd
IsoPlaneApp_SRCS += IsoPlane_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
IsoPlaneApp_SRCS_DEFAULT += IsoPlaneMain.cpp
IsoPlaneApp_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#IsoPlane_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
IsoPlaneDev_LIBS += $(EPICS_BASE_IOC_LIBS)
IsoPlaneApp_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

