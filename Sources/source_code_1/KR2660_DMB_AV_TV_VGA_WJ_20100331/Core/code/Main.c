//----------------------------------------------------------------------------------------------------
// Copyright of Realtek SemiConductor Corp.
// Version : V1.00c (09.15.2009)
//
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
// ID Code      : Main.c No.0002
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#define __MAIN__

#include "Core\Header\Include.h"


/**
 * CMainUserInitial
 * Setting some flags for user when initial
 * @param <none>
 * @return {none}
 *
 */
void CMainUserInitial(void)
{
    // User can make some initial settings at firmware startup
    CLR_PANELPOWERSTATUS();
    CLR_LIGHTPOWERSTATUS();
    CLR_FRAMESYNCSTATUS();
    CLR_POWERSWITCH();
    CLR_FIRST_ADCCLOCK();
    CLR_OSD_READYFORDISPLAY();
#if(_HDMI_SUPPORT == _ON)
       CLR_HDMIINPUT();
#endif
    SET_FIRST_LOADFONT();
#if defined(CONFIG_VBI_ENABLE)
    CLR_OSDVBI_INITIAL();
#endif
    //SET_SOURCE_AUTOCHANGE();
    CLR_SOURCE_AUTOCHANGE();
    SET_PRE_VGA_CONNECT(bVGACONNECT);
#if(_TMDS_SUPPORT == _ON)
#if (_HDMI_SUPPORT == _ON)
    SET_PRE_HDMI_CONNECT(bHDMICONNECT);
#else
    SET_PRE_DVI_CONNECT(bDVICONNECT);
#endif
#endif
    CLR_USE_TRANSITION_RESULT();
    CheckLanguage();
}
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------

/**
 * CMainSystemInitial
 * Initial the system for once when power up
 * @param <none>
 * @return {none}
 *
 */
void CMainSystemInitial(void)
{          
#if(_VIDEO_TV_SUPPORT)
 #if(_IF_PLL_DE_CHIP == _IF_PLL_DE_1338 || _IF_PLL_DE_CHIP == _IF_PLL_DE_135X)
    ucAddrIfPllDM = _ADDR_IfPllDM;
 #endif
#endif

    // Initial MCU
    CMcuInitial();

    CMuteOn();


#if(_HDCP_SUPPORT == _ON && _HDMI_HOT_PLUG_OPTION)
    bHot_Plug = _HOT_PLUG_LOW;
    bHot_Plug2 = _HOT_PLUG_LOW;    
#endif

	CUartSendString("Init timer\n");

    // Initial timer events
    CTimerInitialTimerEvent();
    //CMuteOn();

    CPowerLightPowerOff();
    CPowerPanelPowerOff();

    CUartSendString("Init flash\n");

    #if(_MEMORY_LOCATION == _FLASH)
         InitFlash();
    #endif    

	CUartSendString("eeprom check\n");
    // Check eeprom and load eeprom settings
	CEepromStartupCheck();

    //_SET_INPUT_SOURCE(_SOURCE_VIDEO_AV);
    if(GET_POWERSTATUS())  // Power up
       CPowerLedRed();
    else
    {
       CPowerLedOff();
    }

	CUartSendString("scaer init\n");
    
    // Initial scaler settings
	CScalerInitial();


	CUartSendString("key init\n");
    // Initial key scan status
    CKeyInitial();

	CUartSendString("user init\n");
    // Initial user settings
    CMainUserInitial();

	CUartSendString("DDC init\n");

    CDDCCIInitial();
#if(_RS232_EN)
    CUartInit();
#endif

	CUartSendString("IR init\n");    
    CIrdaInitial();

	CUartSendString("Get Extend \n");    
	GetExtendEnable();

	SetPanelLR();
	SetPanelUD();

	SetFM();
	//CUartSendString("init over \n");    
}

/**
 * main
 * main process
 * first system initial, then main loop
 * @param <none>
 * @return {none}
 *
*/
void main(void)
{
    CMainSystemInitial();
    CUartSendString("Begin...\n");
    do
    {
        CMiscIspDebugProc();                                         
        CTimerHandler();
        CKeyHandler();
        CModeHandler();
        COsdHandler(); 
    }while(_TRUE);
}

/*
void DbgLed(unsigned char ucCount)
{
	unsigned char i;	     
	for(i=0; i<ucCount; i++)
	{
		CPowerLedOrange();
		CTimerDelayXms(100);
		CPowerLedRed();
		CTimerDelayXms(100);
	}
	CPowerLedGreen();
}
  */
