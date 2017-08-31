//----------------------------------------------------------------------------------------------------
// ID Code      : Pcb.h No.0001
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// PCB Type
//--------------------------------------------------
#define _PCB_CF_TC2660							1
#define _PCB_CF_TV2661X						2
#define _PCB_CF_TC266A							3
#define _PCB_CF_V266B							4


#define _PCB_TYPE					       _PCB_CF_TC2660
#define IRSEND_ENABLE
                     
//--------------------------------------------------


#if(_PCB_TYPE == _PCB_CF_V266B)
#include "pcb\PCB_CF_V266B.h"
#endif

#if(_PCB_TYPE == _PCB_CF_TC2660)
#include "pcb\PCB_CF_TC2660.h"
#endif


#if(_PCB_TYPE == _PCB_CF_TC266A)
#include "pcb\PCB_CF_TC266A.h"
#endif

#if(_PCB_TYPE == _PCB_CF_TV2661X)
#include "pcb\PCB_CF_TV2661X.h"
#endif

