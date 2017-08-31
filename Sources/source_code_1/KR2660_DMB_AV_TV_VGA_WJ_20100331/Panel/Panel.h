//----------------------------------------------------------------------------------------------------
// ID Code      : Panel.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


#define _PNL_AT102TN03				              1      	//Toshiba				// AT070TN
#define _PNL_HSD070IDW1					2
#define _PNL_TM150XG					       3
#define _PNL_C070VW01				              4
#define _PNL_LVDS_LTM12C283				5            //Toshiba
#define _PNL_LVDS_EDTCB25QAF                        6            //Panasonic
#define _PNL_LVDS_LP141X7_C1T0                     7            //Philips
#define _PNL_LVDS_A089SW01                            8           //


#define _PANEL_TYPE					_PNL_LVDS_A089SW01//_PNL_LVDS_LTM12C283// _PNL_LVDS_LP141X7_C1T0// _PNL_LVDS_LTM12C283// _PNL_LVDS_EDTCB25QAF// _PNL_LVDS_LTM12C283
//-----------------------------------------------------------

#if(_PANEL_TYPE == _PNL_AT102TN03)
#include "Panel\PNL_AT102TN03.h"
#endif

#if(_PANEL_TYPE == _PNL_HSD070IDW1)
#include "Panel\PNL_HSD070IDW1.h"
#endif

#if(_PANEL_TYPE == _PNL_TM150XG)
#include "Panel\PNL_TM150XG.h"
#endif

#if(_PANEL_TYPE == _PNL_C070VW01)
#include "Panel\PNL_C070VW01.h"
#endif

#if(_PANEL_TYPE == _PNL_LVDS_LTM12C283)
#include "Panel\PNL_LVDS_LTM12C283.h"
#endif

#if(_PANEL_TYPE == _PNL_LVDS_EDTCB25QAF)
#include "Panel\PNL_LVDS_EDTCB25QAF.h"
#endif

#if(_PANEL_TYPE == _PNL_LVDS_LP141X7_C1T0)
#include "Panel\PNL_LVDS_LP141X7_C1T0.h"
#endif

#if(_PANEL_TYPE == _PNL_LVDS_A089SW01)
#include "Panel\PNL_A089SW01.h"
#endif
//-----------------------------------------------------------
