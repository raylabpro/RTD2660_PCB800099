//-------------------------------------------------------------------------
// ID Code      : Power.c No.0002
// Update Note  :
//
//---------------------------------------------------------------------------

#define __POWER__

#include "Core\Header\Include.h"

//---------------------------------------------------------------------------

bit CPowerHandler(void)
{
#if(_VIDEO_TV_SUPPORT)
    if(GET_POWERSWITCH() || ucAutoPowerDownTime == 0)
#else
    if(GET_POWERSWITCH())
#endif
    {
        CPowerControl();
        CLR_POWERSWITCH();
        return _TRUE;
    }
    return _FALSE;
}
//---------------------------------------------------------------------------

//eric 20070531
void CPowerLedGreen(void)
{
    bLED2=_ON;
    bLED1 =0;
}
//---------------------------------------------------------------------------

void CPowerLedRed(void)
{
    bLED2=_OFF;
    bLED1 =1; 
}
//---------------------------------------------------------------------------

void CPowerLedOrange(void)
{
    bLED2 = _ON;
    bLED1 = 1;
}
//---------------------------------------------------------------------------

void CPowerLedOn(void)
{
    CPowerLedGreen();
}
//---------------------------------------------------------------------------

void CPowerLedOff(void)
{
    // EricLee modify for power off LED off
    bLED2 =_OFF;
    bLED1 = 1;
}

void CPowerLedSleep(void)
{
    CPowerLedOrange();
}

//--------------------------------------------------
// Description  : Execute power up/down process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerControl(void)
{  
#if(_VIDEO_TV_SUPPORT && _SLEEP_FUNC)
    if(GET_POWERSTATUS() || ucAutoPowerDownTime == 0)// Power Down Process
#else
    if(GET_POWERSTATUS())// Power Down Process
#endif
	{ 

        CMuteOn();


#if(AUDIO_TYPE == _AUDIO_SC7313)
        CSc7313MuteOn();
#endif
 
        CTimerDelayXms(200);	


        TUNER_PWR_OFF();  
        CPowerDownCustomerControl();
// Eric 0618
#if(_HDMI_SUPPORT && _HDMI_HOT_PLUG_OPTION)
        bHot_Plug = _HOT_PLUG_LOW;
        bHot_Plug2 = _HOT_PLUG_LOW;        
#endif
        CPowerLedOff();//eric 20070531
    }
    else
    {                        // Power Up Process        

        CPowerLedOn();
        SET_POWERSTATUS();
        CScalerReset();//Alanli 20070801
        CPowerUpCustomerControl();
        ucTVSyncFailCount = 250;
        CModeResetMode();
        CEepromSaveSystemData();    

#if(_VIDEO_SUPPORT == _ON)
 #if(_VIDEO_TV_SUPPORT)
        if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
            CInitTV();
 #endif
        CVideoInitial();
        CTimerDelayXms(10); 
        kx_CVDCOutputDisable();
#endif  // End of #if(_VIDEO_SUPPORT == _ON)
        SET_FIRST_LOADFONT();
// Eric 0618
#if(_HDMI_SUPPORT && _HDMI_HOT_PLUG_OPTION)
        //CScalerSetDataPortByte(_P2_HDCP_ADDR_PORT_C3, 0x40, 0x93);//Change to HDCP1.1 for HDMI
        bHot_Plug = _HOT_PLUG_HI;
        bHot_Plug2 = _HOT_PLUG_HI;        
#endif
    }
}

//--------------------------------------------------
// Description  : Set panel on process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerPanelOn(void)
{
	if (GET_PANELPOWERSTATUS() == _OFF)
	{
		CPowerPanelPowerOn();
		CTimerDelayXms(40);
		CPowerDisplayPortOn();
		CScalerEnableDisplayOutput();		            
        CTimerDelayXms(500);                
    }
    //CPowerLightPowerOn();
    CMiscClearStatusRegister();
}

//--------------------------------------------------
// Description  : Set panel off process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerPanelOff(void)
{
    CPowerLightPowerOff();
    CTimerDelayXms(120);
    CScalerDisableDisplayOutput();
    CPowerDisplayPortOff();
    CTimerDelayXms(40);
    CPowerPanelPowerOff();
    // The delay below is to prevent from short period between panel OFF and next ON
    CTimerDelayXms(250);
    //ALPU_Reset_on();
}

//--------------------------------------------------
// Description  : Set panel power on
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerPanelPowerOn(void)
{
    PANELPOWER_UP();
    SET_PANELPOWERSTATUS();
}

//--------------------------------------------------
// Description  : Set panel power off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerPanelPowerOff(void)
{
    PANELPOWER_DOWN();
    CLR_PANELPOWERSTATUS();
}

//--------------------------------------------------
// Description  : Set backlight power on
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerLightPowerOn(void)
{
    CFMControl();
    LIGHTPOWER_UP();
    SET_LIGHTPOWERSTATUS();
}

//--------------------------------------------------
// Description  : Set backlight power off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerLightPowerOff(void)
{
    LIGHTPOWER_DOWN();
    CLR_LIGHTPOWERSTATUS();
}

//--------------------------------------------------
// Description  : Power on display port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerDisplayPortOn(void)
{
#if(_OUTPUT_BUS == _PANEL_TTL)
    CPowerLVDSOn();
    CScalerSetByte(_DISP_ACCESS_PORT_2A, 0x20);     
    CScalerSetByte(_DISP_DATA_PORT_2B, Panel.TTL20);
#endif

#if(_OUTPUT_BUS == _PANEL_LVDS)
    CPowerLVDSOn();
#endif

#if(_OUTPUT_BUS == _PANEL_RSDS)
    CPowerRSDSOn();
#endif
}

//--------------------------------------------------
// Description  : Power off display port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerDisplayPortOff(void)
{
#if(_OUTPUT_BUS == _PANEL_TTL)
#endif

#if(_OUTPUT_BUS == _PANEL_LVDS)
    CPowerLVDSOff();
#endif

#if(_OUTPUT_BUS == _PANEL_RSDS)
    CPowerRSDSOff();
#endif
}

//--------------------------------------------------
// Description  : Power on LVDS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerLVDSOn(void)
{
    CScalerSetByte(_TCON_ADDR_PORT_8B, _TCON_LVDS_CTRL0_A0);
    CScalerSetByte(_TCON_DATA_PORT_8C, 0x30);
}
//--------------------------------------------------
// Description  : Power off LVDS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerLVDSOff(void)
{
    CScalerSetByte(_TCON_ADDR_PORT_8B, _TCON_LVDS_CTRL0_A0);
    CScalerSetByte(_TCON_DATA_PORT_8C, 0x00);
}

#if(_OUTPUT_BUS == _PANEL_RSDS)
//--------------------------------------------------
// Description  : Power on RSDS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerRSDSOn(void)
{
    CPowerLVDSOn();
    CScalerSetByte(_TCON_ADDR_PORT_8B, 0x00);
    CScalerSetByte(_TCON_DATA_PORT_8C, 0xc3);  //for 8-bit RSDS panel
    CTimerDelayXms(40);
    CScalerSetByte(_TCON_ADDR_PORT_8B, 0x00);
    CScalerSetByte(_TCON_DATA_PORT_8C, 0x83);
}

//--------------------------------------------------
// Description  : Power off RSDS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerRSDSOff(void)
{
    CPowerLVDSOff();

    CScalerSetBit(_VDISP_CTRL_28, ~_BIT1, _BIT1); // Force HS/VS/DEN/Data to 0
    CTimerDelayXms(40);
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_CTRL0_00, 0x48); // TTL output 0
    CTimerDelayXms(40);
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_CTRL0_00, 0x42); // Back to HZ
    CScalerSetBit(_VDISP_CTRL_28, ~_BIT1, 0); // Release force
}
#endif

//--------------------------------------------------
// Description  : Power on ADC and APLL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerADCAPLLOn(void)
{
    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_PLL_WD_AF, ~_BIT0, 0x00);     // Power up PLL

    CScalerPageSelect(_PAGE0);
    CScalerSetBit(_P0_ADC_POWER_C6, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));    // Power up ADC
}

//--------------------------------------------------
// Description  : Power off ADC and APLL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerADCAPLLOff(void)
{
    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_PLL_WD_AF, ~_BIT0, _BIT0);     // Power down PLL

    CScalerPageSelect(_PAGE0);
    CScalerSetBit(_P0_ADC_POWER_C6, ~(_BIT2 | _BIT1 | _BIT0), 0x00);    // Power down ADC
}

//--------------------------------------------------
// Description  : Power on TMDS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
void CPowerTMDSOn(void)
{
    CScalerSetBit(_SYNC_CTRL_49, ~(_BIT1 | _BIT0), 0x00);
}
#endif
/*
//--------------------------------------------------
// Description  : Power off TMDS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerTMDSOff(void)
{
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_Z0_CALIBRATION_CTRL_AC, ~_BIT6, 0x00);
    CScalerSetBit(_P2_TMDS_OUTPUT_CTRL_A6, ~_BIT7, 0x00);
}
*/

//--------------------------------------------------
// Description  : Power off ADC and APLL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerDPLLOff(void)
{
    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_DPLL_N_C0, ~_BIT7, _BIT7);// Power down DPLL
}

//--------------------------------------------------
// Description  : Execute power up/down process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerDownCustomerControl(void)
{
    CMuteOn();
    CLR_POWERSTATUS();
    CPowerPanelOff();
    CPowerADCAPLLOff();
    CPowerLVDSOff();
    CPowerDPLLOff();
    //CPowerTMDSOff();
	//CScalerSetByte(_HOST_CTRL_01, 0x02);
    SET_BURNIN_STATE(0);
    
#if(_VIDEO_TV_SUPPORT && _SLEEP_FUNC)
    if (ucAutoPowerDownTime == 0)
        SET_POWERSTATUS();

    CEepromSaveSystemData();
    if (ucAutoPowerDownTime == 0)
        CLR_POWERSTATUS();
#else
    CEepromSaveSystemData();
#endif

#if(_VIDEO_TV_SUPPORT && _SLEEP_FUNC)
    _SET_POWER_DOWN_TIME(0);
    ucAutoPowerDownTime = 0xff;
    CEepromSaveTvData();
    bOSDOnScreen = 0;
#endif

    CPowerDownScaler();
    CTimerCancelTimerEvent(CModeNoSignalEvent);
    CTimerCancelTimerEvent(CModeNoCableEvent);
    CTimerCancelTimerEvent(CModeNoSupportEvent);
    CTimerCancelTimerEvent(CModePowerSavingEvent);

}

void CPowerUpCustomerControl(void)
{
    CMuteOn();
    CPowerPanelOn();
    CPowerADCAPLLOn();
    CPowerLVDSOn();
    CPowerDPLLOff();
    
#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
    CPowerTMDSOn();
#endif

#if(_BACKLIGHT_USE_FAC_ADJ == _DISABLE)
    CAdjustBacklight();
#endif

#if( _HDMI_SUPPORT == _ON)
    if(_GET_INPUT_SOURCE() == _SOURCE_DVI || _GET_INPUT_SOURCE() == _SOURCE_HDMI)
    {
        CLR_HDMISHOWSEARCH();
    }
#endif 

}
