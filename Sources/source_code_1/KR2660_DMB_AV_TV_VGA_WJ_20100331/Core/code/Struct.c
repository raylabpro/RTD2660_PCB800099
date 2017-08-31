//----------------------------------------------------------------------------------------------------
// ID Code      : Struct.c No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#include "Core\Header\Include.h"


//--------------------------------------------------
// Global Variables
//--------------------------------------------------
StructModeUserDataType          	xdata   stModeUserData;
StructModeUserCenterDataType		xdata   stModeUserCenterData;
StructSystemDataType            	xdata   stSystemData;
StructOsdUserDataType           	xdata   stOsdUserData;
StructAdcDataType               	xdata   stAdcData;
StructYPbPrDataType             	xdata   stYPbPrData;
StructColorProc0DataType        	xdata   stConBriData;
StructColorProc1DataType        	xdata   stColorTempData;
ModeInformationType             	idata   stModeInfo;
DisplayTableType                	idata   stDisplayInfo;
StructTvDataType					xdata	stTvInfo;
StructAudioDataType					xdata   stAudioData;
StructHueSaturationDataType        	xdata   stHueSatData;
StructTvInformationData             xdata   stTVChannelInfo;


code StructICMColor stICMColor =
{
    _ICM_R_HUE,
    _ICM_R_SAT,
    _ICM_G_HUE,
    _ICM_G_SAT,
    _ICM_B_HUE,
    _ICM_B_SAT,
    _ICM_Y_HUE,
    _ICM_Y_SAT,
    _ICM_C_HUE,
    _ICM_C_SAT,
};

