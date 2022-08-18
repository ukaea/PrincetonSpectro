TOP = ../..
include $(TOP)/configure/CONFIG
ifeq (windows-x64, $(findstring windows-x64, $(T_A)))
    LIB_INSTALLS_WIN32 += ../ARC_Instrument_x64.lib
    BIN_INSTALLS_WIN32 += ../ARC_Instrument_x64.dll
endif

include $(TOP)/configure/RULES

