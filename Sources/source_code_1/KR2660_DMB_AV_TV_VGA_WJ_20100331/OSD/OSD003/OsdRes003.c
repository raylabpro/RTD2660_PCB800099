#define __OSDRES003__


#include "Core\Header\Include.h"

#if(_OSD_TYPE == _OSD003)

#define FONT_BASE_ADDRESS			0x300


BYTE code tPALETTE_0[] = 
{
	//-------------:Palette ----------
    0x00,0x00,0x00, 0x00,0x00,0xd0,     // 0000/0001
    0x00,0xc0,0x00, 0x48,0x88,0xa8,     // 0010/0011
    0xc0,0x00,0x00, 0x80,0x20,0x20,     // 0100/0101
    0xc0,0xc0,0x00, 0xd0,0xd0,0xd0,     // 0110/0111
    0x00,0x00,0x00, 0x00,0x00,0xff,     // 1000/1001
    0x00,0xff,0x00, 0x60,0xff,0xff,     // 1010/1011
    0xff,0x00,0x00, 0xff,0x00,0xff,     // 1100/1101
    0xff,0xff,0x00, 0xff,0xff,0xff,     // 1110/1111
};
//-------------------------------------------------------------------------------
BYTE code tMainWindowStyle[] =
{
    WINNO(0),

    SB_THICKNESS(7) | SB_HEIGHT(7) ,
    SHADOW_COLOR(0) | BORDER_COLOR(0),
  

    R_GRADIENT_POLARITY_DEC |
    G_GRADIENT_POLARITY_INC |
    B_GRADIENT_POLARITY_DEC |
    GRADIENT_LEVEL(0) |
    R_COLOR_GRADIENT_EN(0) |
    G_COLOR_GRADIENT_EN(0) |
    B_COLOR_GRADIENT_EN(0),

    RESERVED,
    GRADIENT_PER_LEVEL(2) | WINDOW_COLOR(3),
    GRADIENT_FUNCTION_EN(0) |
    GRADIENT_DIRECTION_HOR |
    SHADOW_BORDER_EN(0) |          
    WINDOW_TYPE(0) |
    WINDOW_ENABLE(1)
};

BYTE code tNosignalWINDOW[] =
{
    WINNO(0),
    SB_THICKNESS(7) | SB_HEIGHT(7) ,
    SHADOW_COLOR(0) | BORDER_COLOR(0),
    R_GRADIENT_POLARITY_DEC |
    G_GRADIENT_POLARITY_INC |
    B_GRADIENT_POLARITY_DEC |
    GRADIENT_LEVEL(0) |
    R_COLOR_GRADIENT_EN(0) |
    G_COLOR_GRADIENT_EN(0) |
    B_COLOR_GRADIENT_EN(0),
    RESERVED,
    GRADIENT_PER_LEVEL(2) | WINDOW_COLOR(2),
    GRADIENT_FUNCTION_EN(0) |
    GRADIENT_DIRECTION_HOR |
    SHADOW_BORDER_EN(0) |          
    WINDOW_TYPE(0) |
    WINDOW_ENABLE(1)   
};
	
BYTE code sVolume_ENG[] = "VOLUME";
BYTE code sVolume_CHI[] =  "VOLUME";
BYTE code *sVolume[]	    = 
{
     sVolume_ENG,
     sVolume_CHI,
};
BYTE code sSource[]		= "SOURCE";
BYTE code sLR[]			= "LR";
BYTE code sUD[]			= "UD";
BYTE code sDisplayRatio[]	= "DISPLAYRATIO";
BYTE code sExit[]		= "EXIT";


#if(OEM_TYPE == RTD2660_VGA_AV_MP5_DMB)
BYTE code sAV1[] = "AV1";
BYTE code sAV2[] = "MP5";
BYTE code sTV[] = "DMB";
BYTE code sVGA[] = "VGA";

#elif(OEM_TYPE == RTD2660_VGA_AV_MP5)
BYTE code sAV1[] = "AV1";
BYTE code sAV2[] = "MP5";
BYTE code sTV[] = "TV";
BYTE code sVGA[] = "VGA";

#endif


BYTE code sMute[] = "MUTE";

BYTE code s16_9[] = "16:9";
BYTE code s4_3[] = "4:3";


BYTE code sVisatech[] = "VISATECH";
BYTE code sNoSignal[] = "NO SIGNAL";
BYTE code sReseting[] = "PLEASE WAITING...";
BYTE code sStandard[] = "STANDARD";
BYTE code sSoft[] = "SOFT";
BYTE code sVivid[] = "VIVID";
BYTE code sPersonal[] = "PERSONAL";

//-------------------------------------------------------------------
BYTE code sBrightness_ENG[]	= "BRIGHTNESS";
BYTE code sBrightness_CHI[]	= {0x01,0x02,0x03,0x04,0x00};
BYTE code *sBrightness[] = 
{
	sBrightness_ENG,
	sBrightness_CHI,
};
//-------------------------------------------------------------------
BYTE code sContrast_ENG[]	= "CONTRAST";
BYTE code sContrast_CHI[]	= {0x05,0x06,0x07,0x08,0x03,0x04,0x00};
BYTE code *sContrast[] = 
{
	sContrast_ENG,
	sContrast_CHI,
};
//-------------------------------------------------------------------
BYTE code sHue_ENG[]		= "TINT";//"HUE";
BYTE code sHue_CHI[]		= {0x0e,0x0f,0x09,0x0a,0x00};
BYTE code *sHue[] = 
{
	sHue_ENG,
	sHue_CHI,
};
//-------------------------------------------------------------------
BYTE code sSaturation_ENG[]	= "COLOR";//"SATURATION";
BYTE code sSaturation_CHI[]	= {0x0b,0x0c,0x0e,0x0f,0x00};
BYTE code *sSaturation[] = 
{
	sSaturation_ENG,
	sSaturation_CHI,
};
//-------------------------------------------------------------------
BYTE code sAutoPowerDown_ENG[]  = "AUTO POWER DOWN";
BYTE code sAutoPowerDown_CHI[]  = {0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x00};
BYTE code *sAutoPowerDown[] = 
{
	sAutoPowerDown_ENG,
	sAutoPowerDown_CHI,
};
//-------------------------------------------------------------------
BYTE code sLanguage_ENG[]	= "ENGLISH";
BYTE code sLanguage_CHI[]	= {0x1c,0x1d,0x1e,0x1f,0x00};
BYTE code *sLanguage[] = 
{
	sLanguage_ENG,
	sLanguage_CHI,
};
//-------------------------------------------------------------------
BYTE code sLang_ENG[]	= "LANGUAGE";
BYTE code sLang_CHI[]	= {0x61,0x62,0x63,0x64,0x00};
BYTE code *sLangName[] = 
{
	sLang_ENG,
	sLang_CHI,
};
//-------------------------------------------------------------------
BYTE code sAutoADJ_ENG[]	= "AUTO ADJUST";
BYTE code sAutoADJ_CHI[]	= "AUTO ADJUST";
BYTE code *sAutoADJName[] = 
{
	sAutoADJ_ENG,
	sAutoADJ_CHI,
};
//-------------------------------------------------------------------

BYTE code sFm_ENG[]	= "FM";
BYTE code sFm_CHI[]	= "FM";
BYTE code *sFm[] = 
{
	sFm_ENG,
	sFm_CHI,
};
code BYTE sFM_OFF[] = {"OFF"}; 
code BYTE sFM_A1[] = {"87.7"};
code BYTE sFM_A2[] = {"87.9"};
code BYTE sFM_A3[] = {"88.0"};
code BYTE sFM_A4[] = {"88.1"};
code BYTE sFM_A5[] = {"88.2"};
code BYTE sFM_A6[] = {"88.3"};
code BYTE sFM_A7[] = {"88.4"};
code BYTE sFM_A8[] = {"88.5"};
code BYTE sFM_B1[] = {"88.6"};
code BYTE sFM_B2[] = {"88.7"};
code BYTE sFM_B3[] = {"88.8"};
code BYTE sFM_B4[] = {"88.9"};
code BYTE sFM_B5[] = {"89.0"};
code BYTE sFM_B6[] = {"89.1"};
code BYTE sFM_B7[] = {"89.2"};
code BYTE sFM_B8[] = {"89.4"};

code BYTE sMhz[] = {"MHZ"};

//-------------------------------------------------------------------

BYTE code sReset_ENG[]		= "RESET";
BYTE code sReset_CHI[]		= {0x3c,0x3d,0x3e,0x3f,0x00};
BYTE code *sReset[] = 
{
	sReset_ENG,
	sReset_CHI,
};
//-------------------------------------------------------------------
BYTE code sOn_ENG[] = "ON";
BYTE code sOn_CHI[] = {0x78,0x79,0x00};
BYTE code *sOn[] = 
{
	sOn_ENG,
	sOn_CHI,
};
//-------------------------------------------------------------------
BYTE code sOff_ENG[] = "OFF";
BYTE code sOff_CHI[] = {0x14,0x15,0x00};
BYTE code *sOff[] = 
{
	sOff_ENG,
	sOff_CHI,
};
//-------------------------------------------------------------------
BYTE code sYes_ENG[] = "YES";
BYTE code sYes_CHI[] = {0x5b,0x5c,0x00};
BYTE code *sYes[] = 
{
	sYes_ENG,
	sYes_CHI,
};
//-------------------------------------------------------------------
BYTE code sNo_ENG[] = "NO";
BYTE code sNo_CHI[] = {0x5d,0x5e,0x00};
BYTE code *sNo[] = 
{
	sNo_ENG,
	sNo_CHI,
};

//-------------------------------------------------------------------
BYTE code sTvSystem_ENG[] = "TV SYSTEM";
BYTE code sTvSystem_CHI[] = {0x0b,0x0c,0x0e,0x0f,0x65,0x66,0x67,0x68,0x00};
BYTE code *sTvSystem[] = 
{
	sTvSystem_ENG,
	sTvSystem_CHI,
};
//-------------------------------------------------------------------
BYTE code sAutoSearch_ENG[] = "AUTO SEARCH";
BYTE code sAutoSearch_CHI[] = {0x10,0x11,0x12,0x13,0x69,0x6a,0x6b,0x6c,0x00};
BYTE code *sAutoSearch[] = 
{
	sAutoSearch_ENG,
	sAutoSearch_CHI,
};
//-------------------------------------------------------------------
BYTE code sManualSearch_ENG[] = "MANUAL SEARCH";
BYTE code sManualSearch_CHI[] = {0x76,0x77,0x12,0x13,0x69,0x6a,0x6b,0x6c,0x00};
BYTE code *sManualSearch[] = 
{
	sManualSearch_ENG,
	sManualSearch_CHI,
};
//-------------------------------------------------------------------
BYTE code sTuning_ENG[] = "TUNING";
BYTE code sTuning_CHI[] = {0x6d,0x6e,0x09,0x0a,0x00};
BYTE code *sTuning[] = 
{
	sTuning_ENG,
	sTuning_CHI,
};
//-------------------------------------------------------------------
BYTE code sChannel_ENG[] = "CHANNEL";
BYTE code sChannel_CHI[] = {0x6b,0x6c,0x70,0x71,0x00};
BYTE code *sChannel[] = 
{
	sChannel_ENG,
	sChannel_CHI,
};
//-------------------------------------------------------------------
BYTE code sBlue_ENG[] = "BLUE";
BYTE code sBlue_CHI[] = {0x72,0x73,0x74,0x75,0x00};
BYTE code *sBlue[] = 
{
	sBlue_ENG,
	sBlue_CHI,
};
//-------------------------------------------------------------------
BYTE code sTVNONE[] =" ";
BYTE code sTVNTSC_M[] ="NTSC M";
BYTE code sTVNTSC_4_BG[] ="NTSC M";
BYTE code sTVNTSC_4_DK[] ="NTSC M";
BYTE code sTVNTSC_4_I[] ="NTSC M";
BYTE code sTVPAL_M[]   = "PAL M";
BYTE code sTVPAL_BG[]  = "PAL BG";
BYTE code sTVPAL_I[]   = "PAL I";
BYTE code sTVPAL_DK[]  = "PAL DK";
BYTE code sTVPAL_N[]  = "PAL N";
BYTE code sTVSECAM_BG[] ="SECAM BG";
BYTE code sTVSECAM_DK[] ="SECAM DK";
BYTE code sTVSECAM_L[] ="SECAM L";
BYTE code sTVSECAM_LL[] ="SECAM LL";

WORD code  *sTVType[] =
{
	sTVNONE,
    sTVNTSC_M,
    sTVNTSC_4_BG,
    sTVNTSC_4_DK,
    sTVNTSC_4_I,
    sTVPAL_M,
    sTVPAL_BG,
    sTVPAL_I,
    sTVPAL_DK,
    sTVPAL_N,
    sTVSECAM_BG,
    sTVSECAM_DK,
    sTVSECAM_L,
    sTVSECAM_LL,
};

//-------------------------------------------------------------------
#endif			//#if(_OSD_TYPE == _OSD003)

