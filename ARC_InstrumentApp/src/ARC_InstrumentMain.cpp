//////////////////////////////////////////////////////////////////////////////////////////////////////
//																									//
//	Module:																							//
//		ARC_InstrumentMain.cpp																		//
//																									//
//	Description:																					//
//		IOC Application startup.																	//
//																									//
//	Author:  Peter Heesterman (Tessella plc). Date: 26 Aug 2021.									//
//																									//
//	ARC_InstrumentApp is distributed subject to a Software License Agreement						//
//	found in file LICENSE that is included with this distribution.									//
//																									//
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stddef.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "epicsExit.h"
#include "epicsThread.h"
#include "iocsh.h"

int main(int argc,char *argv[])
{
    if(argc>=2) {    
        iocsh(argv[1]);
        epicsThreadSleep(.2);
    }
    iocsh(NULL);
    epicsExit(0);
    return(0);
}
