TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

LIBRARY_IOC = ARC_InstrumentDev
PROD_IOC = ARC_InstrumentApp

# IsoPlaneDev.dbd will be created and installed
DBD += ARC_Instrument.dbd

# Include dbd files from all support applications:
ARC_Instrument_DBD += ARC_InstrumentInclude.dbd

# Add all the support libraries needed by this IOC
ARC_InstrumentDev_LIBS += asyn
ARC_InstrumentApp_LIBS += asyn

# IsoPlane_registerRecordDeviceDriver.cpp derives from IsoPlaneDev.dbd
ARC_InstrumentDev_SRCS += ARC_USB.cpp
ARC_InstrumentApp_SRCS += ARC_Instrument_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
ARC_InstrumentApp_SRCS_DEFAULT += ARC_InstrumentMain.cpp
ARC_InstrumentApp_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#IsoPlane_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
ARC_InstrumentDev_LIBS += $(EPICS_BASE_IOC_LIBS)
ARC_InstrumentApp_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

