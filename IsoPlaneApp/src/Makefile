TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = IsoPlane
# IsoPlane.dbd will be created and installed
DBD += IsoPlane.dbd

# IsoPlane.dbd will be made up from these files:
IsoPlane_DBD += base.dbd

# Include dbd files from all support applications:
IsoPlane_DBD += asyn.dbd
IsoPlane_DBD += drvAsynSerialPort.dbd
IsoPlane_DBD += $(STREAM)/dbd/stream.dbd

# Add all the support libraries needed by this IOC
IsoPlane_LIBS += stream asyn

# IsoPlane_registerRecordDeviceDriver.cpp derives from IsoPlane.dbd
IsoPlane_SRCS += IsoPlane_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
IsoPlane_SRCS_DEFAULT += IsoPlaneMain.cpp
IsoPlane_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#IsoPlane_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
IsoPlane_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

