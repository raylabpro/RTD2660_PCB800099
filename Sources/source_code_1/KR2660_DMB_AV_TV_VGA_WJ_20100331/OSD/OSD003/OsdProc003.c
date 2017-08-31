

#define __OSDPROC003__

#include "Core\Header\Include.h"

//wtao add 100429
#define TIMER_STEP    30
#define TIMER_OFF      0
#define TIMER_30m     1
#define TIMER_60m     2
#define TIMER_90m     3
#define TIMER_120m   4

#if(_OSD_TYPE == _OSD003)

void SInceptNumber(const WORD ucNumber);
void GotoResetMenu(void);

//--------------------------------------------------
void COsdHandler(void)
{
    bit fTest = 0;

    bOSDTimeOut = 1;

    COsdSystemFlowProc();
    
    COsdEventMsgProc();

    if (_PWOFF_STATE == ucCurrState)
        return;

    CKeyOSDMsgCover();

    // 执行当前菜单的私有处理函数
    if(CURRENT_MENU_ITEM.Proc != NULL)
    {
        CURRENT_MENU_ITEM.Proc();
    }

    COsdEventMsgProc();


    if ((ucKeyMessage != _NONE_KEY_MESSAGE) && bOSDTimeOut)
    {            
        if (GET_OSDTIMEOUT() < 5)
        	CTimerCancelTimerEvent(COsdTimeOut);
        else
            CTimerReactiveTimerEvent(SEC(GET_OSDTIMEOUT()), COsdTimeOut);
    }

	DbgShowOSDState();

    if (!ucOsdState && !bOSDOnScreen)
    {
        if((0xff != ucAutoPowerDownTime) && (0 != _GET_POWER_DOWN_TIME()))
           CShowTimer();
    }


	if(fTest)
	{
 		CNotUse();
	}
    if (bDrawMute)
    {
        bDrawMute = 0;
        if (GET_AUDIO_MUTE()) // Mute on 
           CDrawMuteState();
    }

}

//--------------------------------------------------
void CKeyOSDMsgCover(void)
{
    // Key Message -> Osd Message
    if(ucCurrState == _ACTIVE_STATE || ucOsdState != _MI_MENU_NONE)
    {
        CCoverKeyMsgToOsdEvent(CURRENT_MENU_ITEM.KeyMsgToOsdEvnet,CURRENT_MENU_ITEM.Option & _EN_PUB_KEYEVENT);
    }
    
    else
    {	
    	if(CURRENT_MENU_ITEM.Option & _KEYMAP_EN_IN_NOSIGNAL)
		{
        	CCoverKeyMsgToOsdEvent(CURRENT_MENU_ITEM.KeyMsgToOsdEvnet,CURRENT_MENU_ITEM.Option & _EN_PUB_KEYEVENT);
		}
		else
		{
    	    CCoverKeyMsgToOsdEvent(tKONoSignal, 0x00);
    	}
	}

}
//--------------------------------------------------

void DbgShowOSDState(void)
{
/*
    static BYTE ucMenuItemIndexBak = 0;

	if(ucMenuItemIndexBak != ucOsdState)
	{
		ucMenuItemIndexBak = ucOsdState;
		CUartPrintf("Osd State:",ucOsdState);
	}

    // debug info
    if(ucKeyMessage != _NONE_KEY_MESSAGE)
		CUartPrintf("Osd Event:",ucOsdEventMsg);
*/
}
//--------------------------------------------------
void COsdSystemFlowProc(void)
{
    switch(ucCurrState)
    {         
        case _PWOFF_STATE:
            break;
            
        case _INITIAL_STATE:
            break;
            
        case _SEARCH_STATE:
            break;
            
        case _ACTIVE_STATE:
            if(GET_OSD_READYFORDISPLAY() == _TRUE)
            {
   #if(AUDIO_TYPE == _AUDIO_SC7313 || AUDIO_TYPE == _AUDIO_PWM)
            	CInitSoundChannel(_GET_INPUT_SOURCE());
   #endif
                CLR_OSD_READYFORDISPLAY();
            	CPowerLedOn();

                if (!bSourceVideo())
				{
                    if (GET_CLEAR_OSD_EN())//ucOsdEventMsg != _DO_SHOW_NOTE)
                        COsdDispOsdTimerEvent();
				}

#if(_CHANGE_CHANNEL_DISP_MTD == _CHANGE_CHANNEL_DISP_M2)
                if (_GET_INPUT_SOURCE() != _SOURCE_VIDEO_TV)
#endif            
                {
#if(_VIDEO_TV_SUPPORT)
                    if ((0 == bTVNoSignal && _GET_BLUE_BACKGROUND()) || !_GET_BLUE_BACKGROUND())
#endif            
                        CAdjustBackgroundColor(0x00, 0x00, 0x00);
                }

#if(_VIDEO_TV_SUPPORT)
                ucNoSigCount = 0;
 #if((_TV_CHIP != _TV_JS_6B1) && (_TV_CHIP != _TV_JS_6B2) && (_TV_CHIP != _TNJ_8355))  
                if (_GET_INPUT_SOURCE() != _SOURCE_VIDEO_TV)
 #endif
#endif
                CSetVolume();

            }
            
#if(_VIDEO_TV_SUPPORT)
 #if((_TV_CHIP != _TV_JS_6B1) && (_TV_CHIP != _TV_JS_6B2) && (_TV_CHIP != _TNJ_8355))  
            CAudioCtrl(); 
 #endif

 #if(_SHOW_TV_NO_SIGNAL)
            CCheckTVSignal();
 #endif
#endif
            
            break;
            
        case _NOSUPPORT_STATE:
        	CMuteOn();
            if(GET_OSD_READYFORDISPLAY() == _TRUE)
            {
                CLR_OSD_READYFORDISPLAY();
               

			switch(_GET_INPUT_SOURCE())
		        {
		        case _SOURCE_VGA:
		        case _SOURCE_DVI:
		           CAdjustBackgroundColor(0x00, 0x00, 0x00);
		           break;
		    
		        default:
					/*
				    if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
				    	CAdjustBackgroundColor(0x00, 0x00, (_GET_BLUE_BACKGROUND()) ? 0xFF : 0x00);
				    else
				       	CAdjustBackgroundColor(0x00, 0x00, 0x00);
		            */

					CAdjustBackgroundColor(0x00, 0x00, 0xff);
		            break;
		        }

			
                if (GET_FIRST_SHOW_NOTE())
                   ucOsdEventMsg = _DO_SHOW_NOTE;
                
                CTimerReactiveTimerEvent(SEC(1), CModeNoSupportEvent);
            }
            
            break;
            
        case _NOSIGNAL_STATE:
        	CMuteOn();

    		if((GET_BURNIN_STATE() == _BURNIN_ON) && (_GET_INPUT_SOURCE() == _SOURCE_VGA))
            {
    	  	    BurnInRun();
            	CTimerCancelTimerEvent(CModeNoSignalEvent);
            	CTimerCancelTimerEvent(CModePowerSavingEvent);
                return;
            }



            if(GET_OSD_READYFORDISPLAY() == _TRUE)
            {    
                CLR_OSD_READYFORDISPLAY(); 
    		   
   
		  switch(_GET_INPUT_SOURCE())
                {
	                case _SOURCE_VIDEO_TV:
	                   CAdjustBackgroundColor(0x00, 0x00, 0x00);//0xff);	 //20071127 无信号时蓝屏
	                   break;
	            
	                default:
	                   //CAdjustBackgroundColor(0x00, 0x00, 0x00);
	                   CAdjustBackgroundColor(0x00, 0x00, 0xff);
	                   break;
                }


                if (GET_FIRST_SHOW_NOTE())
                {                        
                    ucOsdEventMsg = _DO_SHOW_NOTE;
                    CPowerPanelOn();
                    CPowerLightPowerOn();
                }  
                     
    			if (_GET_INPUT_SOURCE() == _SOURCE_YPBPR||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1) 
    			{
    				CTimerReactiveTimerEvent(SEC(3), CModeNoSignalEvent);
    				//break;
    			}
    
    #if (_HDMI_SUPPORT == _ON)
    			if (_GET_INPUT_SOURCE() == _SOURCE_HDMI || _GET_INPUT_SOURCE() == _SOURCE_DVI) 
    			{
    				CTimerReactiveTimerEvent(SEC(5), CModeNoSignalEvent);
                    if (CGetSourcePortType(_GET_INPUT_SOURCE()) == _HDMI_D0_PORT || CGetSourcePortType(_GET_INPUT_SOURCE()) == _HDMI_D1_PORT)
    				    CTimerReactiveTimerEvent(SEC(15), CModePowerSavingEvent);
                    else
    				    CTimerReactiveTimerEvent(SEC(8), CModePowerSavingEvent);

    				break;
    			}		
		        
    #endif



    			if (_GET_INPUT_SOURCE() == _SOURCE_VGA) 
    			{
        			if (bVGACONNECT)
        				CTimerReactiveTimerEvent(SEC(3), CModeNoCableEvent);
        			else       
        				CTimerReactiveTimerEvent(SEC(3), CModeNoSignalEvent);
    	              }

                if(bSourceVideo())
        			CTimerReactiveTimerEvent(SEC(3), CModeNoSignalEvent);
/*
				if(stSystemData.InputSource == _SOURCE_VGA      || 
				   stSystemData.InputSource == _SOURCE_DVI      ||
                   stSystemData.InputSource == _SOURCE_VIDEO_AV || 
                   stSystemData.InputSource == _SOURCE_VIDEO_SV || 
                   stSystemData.InputSource == _SOURCE_YPBPR    || 
                   stSystemData.InputSource == _SOURCE_YPBPR1   ||
                   stSystemData.InputSource == _SOURCE_HDMI)
				{	
    				CTimerReactiveTimerEvent(SEC(15), CModePowerSavingEvent);
				}
*/
/*
				if(stSystemData.InputSource != _SOURCE_VIDEO_TV)
				{	
    				CTimerReactiveTimerEvent(SEC(15), CModePowerSavingEvent);
				}	
*/				
            }
            
            break;
            
        case _SLEEP_STATE:
            break;
            
        default:
            break;
    }

}

//==========================================================================
//                          ChangeSourceState
//==========================================================================
void ChangeSourceState(void)
{
	// close OSD first to avoid dirty screen.
	COsdFxDisableOsd();
#if(_VIDEO_TV_SUPPORT)
    if(_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
       CAdjustBackgroundColor(0x00, 0x00, 0x00);//(_GET_BLUE_BACKGROUND()) ? 0xFF : 0x00);
    else
#endif
       //CAdjustBackgroundColor(0x00, 0x00, 0x00);
       CAdjustBackgroundColor(0x00, 0x00, 0xff);
	CScalerSetBit(_VDISP_CTRL_28, 0xff, 0x20);
	CScalerSetBit(_VDISP_CTRL_28, ~_BIT3, _BIT5);
    CMuteOn();
    // EricLee 081117 add for change souce have some noise
    CTimerDelayXms(50);
    TUNER_PWR_OFF();
    
    CInitInputSource();
          
#if(_VIDEO_TV_SUPPORT)
 #if(_FM_DEVICE)  
    bFM = 0; // Close FM
 #endif
#endif 

    switch(_GET_INPUT_SOURCE())
	{
		case _SOURCE_VGA:
		case _SOURCE_YPBPR:
		case _SOURCE_YPBPR1:
			CScalerSetBit(_IPH_ACT_WID_H_16, ~_BIT5, 0x00);
			kx_CVDCOutputDisable();
			break;
	#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))			
		case _SOURCE_DVI:
        case _SOURCE_HDMI:
			kx_CVDCOutputDisable();
			break;
	#endif
		    break;
#if(_VIDEO_TV_SUPPORT)
		case _SOURCE_VIDEO_TV:
            CInitTV();
#endif
		case _SOURCE_VIDEO_AV:
		case _SOURCE_VIDEO_SV:
			break;
	}  
}

//-----------------------------------------------------------
void COsdEventMsgProc(void)
{                  
    if(ucOsdEventMsg > _OE_USER_CMD)
    {    
         ucOsdEventMsg = _NONE_MSG;
         return;
    }

    switch(ucOsdEventMsg)
    {
        case _SHOW_NOSIGNAL_MSG:
        case _SHOW_NOCABLE_MSG:
        case _SHOW_NOSUPPORT_MSG:
        	ucOsdState = _MI_MENU_NONE;
#if(_LOGO_ENABLE)
			CDrawLogo();
			SET_FIRST_LOADFONT();
#else        
         #if(_LOGO_Visatech)
                    CShowVisatech();
	  #else	 
			CShowNoSignal();
	  #endif
#endif
			CTimerCancelTimerEvent(COsdTimeOut);
            break;
            
        case _SAVE_EE_MODEUSERDATA_MSG:
            CEepromSaveModeData(stModeInfo.ModeCurr);
            break;
            
        case _SAVE_EE_SYSTEMDATA_MSG:
            CEepromSaveSystemData();
            break;
            
        case _SAVE_EE_OSDUSERDATA_MSG:
            CEepromSaveOsdUserData();
            break;
            
        case _SAVE_EE_ADCDATA_MSG:
            CEepromSaveAdcData();
            break;
            
        case _SAVE_EE_COLORPROC0_MSG:
            CEepromSaveBriConData();
            break;
            
        case _SAVE_EE_COLORPROC1_MSG:
            CEepromSaveColorTempData();
            break;

        case _SAVE_EE_AUDIO_DATA_MSG:
            CEepromSaveAudioData();
            break;

        case _SAVE_EE_HUE_SAT_DATA_MSG:
            CEepromSaveHueSatData();
            break;

        case _SAVE_EE_TV_DATA_MSG:
            CEepromSaveTvData();
            break;

        case _OE_VMODE:
//			ChangeColorMode();
        	break;

        case _OE_AMODE:
//        	ChangeAudioMode();
        	break;

        case _OE_CHG_SOURCE_AV_SV:
        	CChangeSourceAvSv();
        	//break;
        case _CHANGE_SOURCE_MSG:
            ChangeSourceState();
        	CEepromSaveSystemData();
            ucTVSyncFailCount = 250;
            CLR_CLEAR_OSD_EN();
            CModeResetMode();
        	CLR_SOURCE_AUTOCHANGE();
            //CShowNote();
            CLR_CLEAR_OSD_EN();
            SET_FIRST_SHOW_NOTE();
            break;

            
        case _DO_AUTO_CONFIG:
        	if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
        	{
			//	CShowAutoAdjust();
        	}

        	break;
        	
        case _DO_SHOW_NOTE:
            CLR_FIRST_SHOW_NOTE();
            CShowNote();            
            break;

#if(_VGA_SUPPORT)
        case _OE_INPUT_VGA:
            if (_GET_INPUT_SOURCE() != _SOURCE_VGA)
            {
                _SET_INPUT_SOURCE(_SOURCE_VGA);
                ChangeSourceReset();
            } 
            break;
#endif

#if(_TMDS_SUPPORT)
        case _OE_INPUT_DVI:
            if (_GET_INPUT_SOURCE() != _SOURCE_DVI)
            {
                _SET_INPUT_SOURCE(_SOURCE_DVI);
                ChangeSourceReset();
            } 
            break;
#endif

#if(_VIDEO_SV_SUPPORT)
        case _OE_INPUT_S_VIDEO:
            if (_GET_INPUT_SOURCE() != _SOURCE_VIDEO_SV)
            {
                _SET_INPUT_SOURCE(_SOURCE_VIDEO_SV);
                ChangeSourceReset();
            } 
            break;
#endif

#if(_VIDEO_AV_SUPPORT)
        case _OE_INPUT_AV:
            if (_GET_INPUT_SOURCE() != _SOURCE_VIDEO_AV)
            {
                _SET_INPUT_SOURCE(_SOURCE_VIDEO_AV);
                ChangeSourceReset();
            } 
            break;
#endif

#if(_VIDEO_TV_SUPPORT)
        case _OE_INPUT_TV:
            if (_GET_INPUT_SOURCE() != _SOURCE_VIDEO_TV)
            {
                _SET_INPUT_SOURCE(_SOURCE_VIDEO_TV);                
                ChangeSourceReset();
            } 
            break;
#endif
                  
#if(_YPBPR_SUPPORT)
        case _OE_INPUT_YPBPR:
            if (_GET_INPUT_SOURCE() != _SOURCE_YPBPR)
            {
                _SET_INPUT_SOURCE(_SOURCE_YPBPR);
                ChangeSourceReset();
            } 
            break;
        case _OE_INPUT_YPBPR1:
            if (_GET_INPUT_SOURCE() != _SOURCE_YPBPR1)
            {
                _SET_INPUT_SOURCE(_SOURCE_YPBPR1);
                ChangeSourceReset();
            } 
            break;
#endif

		case _OE_TCON_MODE:

			   if (bPanel_LR == 0 && bPanel_UD == 0)
				   PanelLRSwap();
			   else if (bPanel_LR == 1 && bPanel_UD == 0)
				   PanelUDSwap();
                        else if (bPanel_UD == 1 && bPanel_LR == 1)
				   PanelLRSwap();
			   else if (bPanel_UD == 1 && bPanel_LR == 0)
				   PanelUDSwap();
			   else if (bPanel_LR == 0 && bPanel_UD == 0)
				   PanelLRSwap();

	                 CEepromSaveSystemData();
	                 ucOsdEventMsg = _SAVE_EE_SYSTEMDATA_MSG;
		break;

		case _OE_PANEL_LR_SWAP:
			PanelLRSwap();
			break;

		case _OE_PANEL_UD_SWAP:
			PanelUDSwap();	
			break;

		case _OE_GOTO_MENU_CONTRAST:
			GotoContrastMenu();
			break;
		case _OE_GOTO_MENU_SATURATION:
			GotoSaturationMenu();
			break;
		case _OE_GOTO_MENU_BRIGHTNESS:
			GotoBrightnessMenu();
			break;
		case _OE_SC_TIMER_CHANGE:
			SetSleepTimer();
			break;
/*
遥控的16:9/4:3按键的定义为复用:
   支持16:9用作ChangeDisplayMode
   否则用作ChangePictureMode
wtao100416 
*/                  
		//case _OE_CHG_DISPLAY_MODE:
		//	ChangeDisplayMode();
		//	break;
		case _OE_CHANGE_PICTURE_MODE:
			if(MDisplayRatioEnable())//16:9 or 4:3
			    ChangeDisplayMode();
			else//Standard Vivid Soft or Persenal
			    CChangePictureMode();
			break;			
		case _OE_GOTO_MENU_VOLUME:
			GotoVolumeMenu();
			break;
		case _OE_GOTO_MENU_RESET:
                      GotoResetMenu();
			break;
        default:
            break;
    }
    
    ucOsdEventMsg = _NONE_MSG;
}
//----------------------------------------------------------------------------------------------------
#if(_VIDEO_TV_SUPPORT)
#define _INPUT_NO_NUMBER       0
#define _INPUT_ONE_NUMBER      1
#define _INPUT_TWO_NUMBER      2
#define _INPUT_THREE_NUMBER    3
WORD iInpuNumCount = 0;
void EnterSCInputNum(void)
{
    BYTE ucInputState = GET_INPUTCH_STATE() + 1;
    
    //COsdLoad1BitFont(FntInputState,0x7A,1,tFntVolumeCharWidth);
    
    // iInputCHCount = _INPUT_CH_TIMEOUT_COUNT;
    // Reset input number and state
    ucCurrentInputNumber = 0;
    // 0: no input number   1: input one number     2: input two number    3: input three number
    ucCurrentInputState  = _INPUT_NO_NUMBER;  
    
    if (ucInputState > 3)
    {   // Input state err reset input state to input one channel -
        ucInputState = 1;
        SET_INPUTCH_STATE(0);
        CEepromSaveTvData();
    }
    
    ucOsdState = _MI_SC_INPUT_CH_NUM;
    bChangeChannel = 0;
    COsdFxDisableOsd();
    CCloseAllWindows();
    SetOSDDouble(0X03);
    
    // Init OSD Ram
    OSDClear(0, 8, 0, 20, 0x8C, BYTE_ATTRIB);
    OSDClear(0, 8, 0, 20, 0x00, BYTE_DISPLAY);
    OSDClear(0, 8, 0, 20, 0xF0, BYTE_COLOR);
    
    
    OSDPosition(3 * 12, 4 * 18,_TVNUMBER_POSITION_OFFSET,3,1);
    
    Gotoxy(1, 0, BYTE_DISPLAY);         
    for(; ucInputState > 0; ucInputState--)
        OutputChar(0x7A);  // Show "-"
    
    
    COsdFxEnableOsd();
    CTimerReactiveTimerEvent(SEC(20),COsdDispOsdTimerEvent);
    bOSDTimeOut   = 0;
    iInpuNumCount = 0;
}
//---------------------------------------------------------------------------
void MScInputChNumProc(void)
{
    BYTE idata ucInputState = GET_INPUTCH_STATE() + 1;
    
    iInpuNumCount++;

    if (iInpuNumCount > 900)
        ucOsdEventMsg = _OE_RETURN_UPMENU;

    switch(ucOsdEventMsg)
    {        
    case _OE_SC_INPUT_NUM0:
    case _OE_SC_INPUT_NUM1:
    case _OE_SC_INPUT_NUM2:
    case _OE_SC_INPUT_NUM3:
    case _OE_SC_INPUT_NUM4:
    case _OE_SC_INPUT_NUM5:
    case _OE_SC_INPUT_NUM6:
    case _OE_SC_INPUT_NUM7:
    case _OE_SC_INPUT_NUM8:
    case _OE_SC_INPUT_NUM9:
        SInceptNumber(ucOsdEventMsg - _OE_SC_INPUT_NUM0);
        iInpuNumCount = 0;
        break;
        
    case _OE_SC_INPUT_CHANGE_CH:
        //            iInputCHCount = _INPUT_CH_TIMEOUT_COUNT;
        ucInputState = ValueInRangeChange(1, 3, ucInputState, _LOOP | 0x01);
        SET_INPUTCH_STATE(ucInputState-1);
        CEepromSaveTvData();
        
        // Reset input number and state
        ucCurrentInputNumber = 0;
        // 0: no input number   1: input one number     2: input two number    3: input three number
        ucCurrentInputState  = 0;
        iInpuNumCount        = 0;
        break;
        
    case _OE_RETURN_UPMENU:
        if (_INPUT_NO_NUMBER == ucCurrentInputState)
            COsdDispOsdTimerEvent();
        else
            ucInputState = ucCurrentInputState;
        break;
    }
    
    SShowCurrentInputState(ucInputState);
    
    if (ucInputState == ucCurrentInputState)
    {
        BYTE ucMaxChannel = _GET_MAX_CHANNEL();
        
        CMuteOn();
        COsdDispOsdTimerEvent();
        CModeResetTVMode();
        CTimerDelayXms(200);
        
        if (ucCurrentInputNumber == 0)
            ucCurrentInputNumber = 1;
        bDrawMute = 0;
#if(_FM_DEVICE)
        if (1 == bFM)
        {
            ucPrevChannel =  stTvInfo.ucFMCurrCh;
            stTvInfo.ucFMCurrCh = (ucCurrentInputNumber > ucMaxChannel) ? ucMaxChannel : ucCurrentInputNumber;
            CSetTVChannel(stTvInfo.ucFMCurrCh);
            //CShowTVNumber(stTvInfo.ucFMCurrCh, _SHOW_CH_TV_NUMBER);
        }
        else
#endif   
        {
            ucPrevChannel =  stTvInfo.CurChn;
           // stTvInfo.CurChn = (ucCurrentInputNumber > ucMaxChannel) ? ucMaxChannel : ucCurrentInputNumber;	//pc 20091008 changed
			stTvInfo.CurChn = ucCurrentInputNumber;
            CSetTVChannel(stTvInfo.CurChn);
            //            CShowTVNumber(stTvInfo.CurChn,_SHOW_CH_TV_NUMBER | _SHOW_CH_TV_TYPE | _SHOW_CH_SOUND_TYPE);
            kx_CI2CWriteIfPllDM(ucTVType, _TUNER_MUTE_OFF, _NORMAL_MODE);
        }
        
        ucOsdEventMsg = _SAVE_EE_TV_DATA_MSG;
    }
    
//    CTimerReactiveTimerEvent(SEC(10), COsdDispOsdTimerEvent);
    bOSDTimeOut = 0;
}
//---------------------------------------------------------------------------
void SInceptNumber(const WORD ucNumber)
{
    switch(ucCurrentInputState)
    { 
    case _INPUT_NO_NUMBER: // not input number
        ucCurrentInputNumber = ucNumber;
        ucCurrentInputState  = _INPUT_ONE_NUMBER;
        break;
        
    case _INPUT_ONE_NUMBER: // Input on number alrady
    case _INPUT_TWO_NUMBER: // Input two number alrady
        ucCurrentInputNumber = (ucCurrentInputNumber*10) + ucNumber;
        ucCurrentInputState  = (ucCurrentInputState == _INPUT_TWO_NUMBER) ? _INPUT_THREE_NUMBER : _INPUT_TWO_NUMBER;
        break;
    }
}

//---------------------------------------------------------------------------
void SShowCurrentInputState(BYTE ucInputState)
{
    Gotoxy(1, 0, BYTE_DISPLAY); 
    
    switch(ucCurrentInputState)
    {
    case _INPUT_NO_NUMBER: // not input number
        {
            for(;ucInputState > 0;ucInputState--)
            {
                OutputChar(0x7A);  // Show "-"
            }
            OutputChar(0x01);  // Show " "
            OutputChar(0x01);  // Show " "
        }
        break;
        
    case _INPUT_ONE_NUMBER: // Input on number alrady
        CShowNumber1(ucCurrentInputNumber,1);
        break;
        
    case _INPUT_TWO_NUMBER: // Input two number alrady
        CShowNumber1(ucCurrentInputNumber,2);
        break;
        
    case _INPUT_THREE_NUMBER: // Input three number alrady
        CShowNumber1(ucCurrentInputNumber,3);
        break;
    }
}


//---------------------------------------------------------------------------
void CShowTVNumber(BYTE ucNumber, BYTE ucOption)
{ 
    ucOsdState     = _MI_MENU_NONE;
    bChangeChannel = 0;
    
    InitOsdFrame();

    SetOSDDouble(3);
    CCloseAllWindows();

    OSDPosition(_MAINMENU_WITDH,_MAINMENU_HEIGHT,0,0,0x03);
    
    if (ucOption & _SHOW_CH_TV_NUMBER)
    {
		Gotoxy(0, 0, BYTE_DISPLAY);
    	PrintfDec(ucNumber);
    }

    if (_SHOW_CH_TV_TYPE & ucOption)
    {
    	BYTE *pStr;

    	switch(ucTVType)
    	{
        default:
    	case _TV_NTSC_M:		pStr = "NTSC M";		break;
    	case _TV_NTSC_4_BG:		pStr = "NTSC M";		break;
    	case _TV_NTSC_4_DK:		pStr = "NTSC M";		break;
    	case _TV_NTSC_4_I:		pStr = "NTSC M";		break;
    	case _TV_PAL_M:		    pStr = "PAL M";			break;
    	case _TV_PAL_BG:		pStr = "PAL BG";		break;
    	case _TV_PAL_I:			pStr = "PAL I";			break;
    	case _TV_PAL_DK:		pStr = "PAL DK";		break;
    	case _TV_PAL_N:			pStr = "PAL N";			break;
    	case _TV_SECAM_BG:		pStr = "SECAM BG";		break;
    	case _TV_SECAM_DK:		pStr = "SECAM DK";		break;
    	case _TV_SECAM_L:		pStr = "SECAM L";		break;
    	case _TV_SECAM_LL:		pStr = "SECAM LL";		break;
        }
		Gotoxy(0, 1, BYTE_DISPLAY);
        Textout(pStr);  
    }

   
    COsdFxEnableOsd();
    CTimerReactiveTimerEvent(SEC(5), COsdDispOsdTimerEvent);
    bOSDTimeOut  = 0;
#if(_SLEEP_FUNC)
    bOSDOnScreen = 1;
#endif
}

#endif

//----------------------------------------------------------------------------------------------------
void COsdDispFirstTimeLoadFont(void)
{       
    COsdFxDisableOsd();
    COsdColorPalette(tPALETTE_0);
    
    SetOsdMap(ROW_COUNT,COL_WIDTH,FONT_BASE_ADDRESS);
    CScalerLoadHardwareVLCFont(FntGlobal,0x00);
}

//-----------------------------------------------------------
#define _NOTE_WIDTH						(11 * 12 + 8)	
#define _NOTE_HEIGHT					       (3 * 18)

void CShowTimerMode()
{
    InitOsdFrame();
    SetOSDDouble(0x03);
	OSDPosition(_NOTE_WIDTH, _NOTE_HEIGHT, 42, 0, 0x03);
	if(_GET_POWER_DOWN_TIME() == 0x00)
	{
		Gotoxy(0,0,BYTE_DISPLAY);
		Textout(sOff[GET_LANGUAGE()]);
	}
	CTimerReactiveTimerEvent(SEC(5), COsdTimeOut);
    COsdFxEnableOsd();
    bOSDTimeOut = 0;
}

//---------------------------------------------------------------------------

void CShowTimer(void) small
{
    BYTE ucCurrentMin;
    BYTE ucCurrentSec;

	if(bShowTimerChg == 0)
		return;

	bShowTimerChg = 0;
    ucCurrentMin = ucAutoPowerDownTime;
    ucCurrentSec = 60 - (BYTE)(ucMinuteCount/1000);
	
    if (!bTimerOnScreen)
    {              
	    ucOsdState = _MI_MENU_NONE;

	    InitOsdFrame();
	    SetOSDDouble(0x03);
		OSDPosition(_NOTE_WIDTH, _NOTE_HEIGHT, 42, 0, 0x03);
        bTimerOnScreen = 1;

        COsdFxEnableOsd();
    }
    
    Gotoxy(0, 0, BYTE_DISPLAY);	
    if(ucCurrentSec != 60)
       CShowNumber1(ucAutoPowerDownTime-1 , 0);
    else
       CShowNumber1(ucAutoPowerDownTime , 0);
    OutputChar(':');
    if(ucCurrentSec == 60)
    	CShowNumber1(0, 2);
    else
       CShowNumber1(ucCurrentSec, 2);
    //OutputChar(0x01);   
   	CTimerCancelTimerEvent(COsdTimeOut);
}
//---------------------------------------------------------------------------

void SetSleepTimer(void)
{
	COsdDispOsdTimerEvent();
	if(_GET_POWER_DOWN_TIME() == TIMER_120m)
	{
	    _SET_POWER_DOWN_TIME(TIMER_OFF);
	}
	else
	{
	    _SET_POWER_DOWN_TIME(_GET_POWER_DOWN_TIME()+1);
	}   
	CEepromSaveTvData();//ucOsdEventMsg = _SAVE_EE_TV_DATA_MSG;

	ucAutoPowerDownTime = _GET_POWER_DOWN_TIME() * TIMER_STEP;
	if(TIMER_OFF == ucAutoPowerDownTime) // Auto power down time off
	{
	    ucAutoPowerDownTime = 0xff;
	}

	CShowTimerMode();
	ucMinuteCount = 0;  // Reset count
}
//-----------------------------------------------------------

BYTE CFoundKeyMsgToOsdEvent(SKeyToOsdEvent *tMsgTable)
{
     BYTE i;

     if(ucKeyMessage == _NONE_KEY_MESSAGE)
     {
          //ucOsdEventMsg = _NONE_MSG;
          return 0;
     }
                        
     i = 0;
     while(1)
     {
         if(tMsgTable[i].KeyMessage == _NONE_KEY_MESSAGE)
         {
              //ucOsdEventMsg = _NONE_MSG;
              // End flag
              return 1;
         }
         if(ucKeyMessage == tMsgTable[i].KeyMessage)
         {
              ucOsdEventMsg = tMsgTable[i].OsdEvent;
              return 0;
         }

         i++;
     }
     return 1;
}                                        
//---------------------------------------------------------------------------

void CCoverKeyMsgToOsdEvent(SKeyToOsdEvent *tMsgTable,BYTE bUserPublicKeyEvnet)
{
     bit bFoundPublic = 1;

     if(tMsgTable != NULL)
         bFoundPublic = CFoundKeyMsgToOsdEvent(tMsgTable);

     if(bFoundPublic && bUserPublicKeyEvnet)
     {
         CFoundKeyMsgToOsdEvent(tKOPublic);
     }
}
//---------------------------------------------------------------------------
void InitOsdFrame(void)
{
    COsdFxDisableOsd();
    CCloseAllWindows();

    SetOsdMap(ROW_COUNT,COL_WIDTH,FONT_BASE_ADDRESS);

    if(GET_FIRST_LOADFONT() == _TRUE)
    {
        CLR_FIRST_LOADFONT();
        COsdDispFirstTimeLoadFont();
    }    

	//CScalerSetBit(_OVERLAY_CTRL_6C, 0x23, ((stOsdUserData.OsdBlending & 0x07) << 2));
    OSDClear(ROW(0), HEIGHT(ROW_COUNT), COL(0), WIDTH(COL_WIDTH), 0x8C, BYTE_ATTRIB);
    OSDClear(ROW(0), HEIGHT(ROW_COUNT), COL(0), WIDTH(COL_WIDTH), 0x00, BYTE_DISPLAY);
    OSDClear(ROW(0), HEIGHT(ROW_COUNT), COL(0), WIDTH(COL_WIDTH), 0x40, BYTE_COLOR);    

    CTimerCancelTimerEvent(COsdTimeOut);
}

//---------------------------------------------------------------------------
void CShowNoSignal(void)
{
    InitOsdFrame();
    SetOSDDouble(0x00);   	 
    OSDLine(1,0,COL_WIDTH,0xF0,BYTE_COLOR);
    CCenterTextout(sNoSignal, COL(14), ROW(1));
    COsdFxDrawWindow(XSTART(0), YSTART(0), _MAINMENU_WITDH, _MAINMENU_HEIGHT, tNosignalWINDOW);
    OSDPosition(_MAINMENU_WITDH, _MAINMENU_HEIGHT, 50, 50, 0x03); 
    COsdFxEnableOsd();
}
//---------------------------------------------------------------------------

void CShowVisatech(void)
{
    InitOsdFrame();
       SetOSDDouble(0x03);   
	OSDPosition(300, 30, 0, 1, 0x03);    
       OSDLine(10,20,COL_WIDTH,0xA0,BYTE_COLOR);
	Gotoxy(20,10, BYTE_DISPLAY);
	Textout(sVisatech);
	
    COsdFxEnableOsd();
 }

//---------------------------------------------------------------------------
void CShowNote(void)
{
	BYTE code *pStr; 

    ucOsdState = _MI_MENU_NONE;

    InitOsdFrame();
    SetOSDDouble(0x03);  



	switch(stSystemData.InputSource)
	{
		case _SOURCE_VIDEO_SV:		pStr = sAV2;		break;
		case _SOURCE_VIDEO_AV:		pStr = sAV1;		break;
		case _SOURCE_VIDEO_TV:		pStr = sTV;			break;
		case _SOURCE_VGA:			pStr = sVGA;			break;

	}
	
	//CCenterTextout(pStr,COL(5),ROW(0)); 
	Gotoxy(0, 0, BYTE_DISPLAY);
	Textout(pStr);
    
    OSDPosition(120, 18, 0, 1, 0x03); 
	
    COsdFxEnableOsd();
    CPowerPanelOn();  

    CTimerReactiveTimerEvent(SEC(5), COsdTimeOut);

}
//---------------------------------------------------------------------------




BYTE AdjustMenuItem(BYTE ucBeginItem,BYTE ucEndItem,BYTE ucMode)
{
     BYTE i;
     BYTE ucCount;
     BYTE ucNewItem;

     CLR_KEYREPEATENABLE();

     //如果菜单只有一项,直接返回
     ucCount = ucEndItem - ucBeginItem;
     if(ucCount < 1)
     {
          return ucOsdState;
     }

     // 计算下一项菜单，或是上一菜单
     i = 0;

     ucNewItem = ucOsdState;

     // EricLee add for menu have more item,but only show one item bug
     ucCount += 1;
     while(i < ucCount)
     {

         ucNewItem = ValueInRangeChange(ucBeginItem, ucEndItem, ucNewItem, ucMode | _LOOP);

         if(g_tMenuItem[ucNewItem].Enable())
         {
             break;
         }
         
         i++;
     }

     return ucNewItem;
}
//----------------------------------------------------------------------------------------------------
BYTE GetShowIndex(BYTE ucMenuItem,BYTE ucBeginItem,BYTE ucEndItem)
{
     BYTE Index;

     bit fEnable;
     bit fDisableNoShow;

     Index = 0;

     while(ucBeginItem <= ucEndItem)
     {
     	fEnable = g_tMenuItem[ucBeginItem].Enable();
		if((g_tMenuItem[ucBeginItem].Option & _DISABLE_NOT_SHOW) != _DISABLE_NOT_SHOW)
			fDisableNoShow = 0;
		else
			fDisableNoShow = 1;

     	if(ucBeginItem == ucMenuItem)
     	{
     		if(fEnable)		
     		{
     			return Index;
     		}
     		else
     		{
				if(fDisableNoShow)
					return _NOT_SHOW;
				else
					return Index;
     		}
     	}

     	if(ucBeginItem > ucMenuItem)
     		return _NOT_SHOW;
     		
       	if(!fDisableNoShow)
       	{	
        	Index++;
        }
        else
        {
        	if(fEnable)
        	{
            	Index++;
            }
		}
        ucBeginItem++;
     }

     return _NOT_SHOW;     
}
//----------------------------------------------------------------------------------------------------
BYTE GetShowCount(BYTE ucBeginItem,BYTE ucEndItem)
{
     BYTE ucCount;

     bit fEnable;
     bit fDisableNoShow;


     ucCount = 0;

     while(ucBeginItem <= ucEndItem)
     {
     	fEnable = g_tMenuItem[ucBeginItem].Enable();
     	
		if((g_tMenuItem[ucBeginItem].Option & _DISABLE_NOT_SHOW) != _DISABLE_NOT_SHOW)
			fDisableNoShow = 0;
		else
			fDisableNoShow = 1;
     		
       	if(!fDisableNoShow)
       	{	
        	ucCount++;
        }
        else
        {
        	if(fEnable)
        	{
            	ucCount++;
            }
		}
        ucBeginItem++;
     }

     return ucCount;     
}

//----------------------------------------------------------------------------------------------------
void CDrawMuteState(void)
{           
    ucOsdState     = _MI_MENU_NONE;
#if(_VIDEO_TV_SUPPORT)
        bChangeChannel = 0;
#endif
    InitOsdFrame();
    SetOSDDouble(0x03);     
    OSDPosition(120, 18, 0, 1, 0x03); 	
    COsdFxEnableOsd();
    if (GET_AUDIO_MUTE()) // Mute on 
	{
		if(_DISP_WID>1000)
                     Gotoxy(26,0,BYTE_DISPLAY);//wtao100427
		else
			Gotoxy(20, 0, BYTE_DISPLAY);
		
		Textout(sMute);
	}
    else
	{
	   if(_DISP_WID>1000)
               OSDClear(2, 1, 26 , 4, 0x00, BYTE_DISPLAY);	//wtao100427
	   else
		 OSDClear(2, 1, 20 , 4, 0x00, BYTE_DISPLAY);		
	}

                                              
    bOSDTimeOut  = 0;
 //   ucAudioState = 1;
    if (GET_AUDIO_MUTE()) // Mute on  
    {
       	CTimerCancelTimerEvent(COsdDispOsdTimerEvent);
    }
    else             
    {
              CTimerReactiveTimerEvent(SEC(5), COsdDispOsdTimerEvent);
	       //COsdTimeOut();		 //wtao100427 add to avoid lose "No Signal" 
    } 

    bOSDTimeOut  = 0;
    bOSDOnScreen = 1;
}

//-----------------------------------------------------------------------
void CSetMuteState(void)
{
    if (GET_AUDIO_MUTE()) // Mute on 
        CLR_AUDIO_MUTE();
    else
        SET_AUDIO_MUTE();

    CDrawMuteState();
       CSetVolume();
    ucOsdEventMsg = _SAVE_EE_AUDIO_DATA_MSG;
}

//-----------------------------------------------------------------------



void ChangeSourceReset(void)
{
    ChangeSourceState();
	CEepromSaveSystemData();
    ucTVSyncFailCount = 250;
    CLR_CLEAR_OSD_EN();
    CModeResetMode();
	CLR_SOURCE_AUTOCHANGE();
    //CShowNote();
    CLR_CLEAR_OSD_EN();
    SET_FIRST_SHOW_NOTE();
}

   
//----------------------------------------------------------------------------------------------------
void CChangeSourceAvSv(void)
{
	switch(_GET_INPUT_SOURCE())
	{
		case _SOURCE_VIDEO_AV:		_SET_INPUT_SOURCE(_SOURCE_VIDEO_SV);		break;
		case _SOURCE_VIDEO_SV:		_SET_INPUT_SOURCE(_SOURCE_VIDEO_TV);		break;
		case _SOURCE_VIDEO_TV:		_SET_INPUT_SOURCE(_SOURCE_VGA);		break;
		case _SOURCE_VGA:			_SET_INPUT_SOURCE(_SOURCE_VIDEO_AV);		break;
		default: break;

	}
	
	COsdDispOsdTimerEvent();              
    ucOsdEventMsg = _CHANGE_SOURCE_MSG;
}

//---------------------------------------------------------------------------
void ChangeDisplayMode(void)
{
	if(!MDisplayRatioEnable())
		return;
	
	if(GET_DISPLAYMODE() == _DISPMODE_FULL)
	{
		SET_DISPLAYMODE(_DISPMODE_43);
	}
	else
	{
		SET_DISPLAYMODE(_DISPMODE_FULL);
	}

	CEepromSaveSystemData();
	ucTVSyncFailCount = 250;

	ucOsdState = _MI_MENU_NONE;
	COsdFxDisableOsd();
	
	CModeResetMode();
}
//---------------------------------------------------------------------------
void PanelLRSwap(void)
{
	if(GET_LR_SWAP())
		SET_LR_SWAP(0);
	else 
		SET_LR_SWAP(1);

	CEepromSaveSystemData();

	SetPanelLR();	
}
//---------------------------------------------------------------------------

void PanelUDSwap(void)
{
	if(GET_UD_SWAP())
		SET_UD_SWAP(0);
	else 
		SET_UD_SWAP(1);

	ucOsdEventMsg = _SAVE_EE_SYSTEMDATA_MSG;

	SetPanelUD();
}
//---------------------------------------------------------------------------

void GotoBrightnessMenu(void)
{
	DrawMainMenu();    
	DrawBrightness();
	
    ucOsdState = _MI_BRIGHTNESS;
    
    COsdFxEnableOsd();
}
//---------------------------------------------------------------------------
void GotoContrastMenu(void)
{
	DrawMainMenu();    
	DrawContrast();
	
    ucOsdState = _MI_CONTRAST;
    
    COsdFxEnableOsd();
}
//---------------------------------------------------------------------------
void GotoSaturationMenu(void)
{
	DrawMainMenu();    
	DrawSaturation();
	
    ucOsdState = _MI_SATURATION;
    
    COsdFxEnableOsd();
}
//---------------------------------------------------------------------------
void GotoVolumeMenu(void)
{
	DrawMainMenu();    
	DrawVolume();
	
    ucOsdState = _MI_VOLUME;

    SET_KEYREPEATENABLE();

	CAdjustAudio();
       CSetVolume();

    ucOsdEventMsg = _SAVE_EE_AUDIO_DATA_MSG;
    OSD_SLIDER(GET_VOLUME());
    COsdFxEnableOsd();
}
//---------------------------------------------------------------------------
//wtao100413
void GotoResetMenu(void)
{
    ucOsdState = _MI_RESET;
	DrawMainMenu();    
       m_fResetMenuState = 0;
       DrawReset();
	

    SET_KEYREPEATENABLE();
	
    COsdFxEnableOsd();
	
}

//---------------------------------------------------------------------------
void CAdjustPicMode(void)
{
	switch (GET_COLOR_MODE())
	{
		case _CM_NORMAL:	
			stConBriData.Contrast = 50;
			stConBriData.Brightness= 50;
			break;
		case _CM_SOFT:
			stConBriData.Contrast = 45;
			stConBriData.Brightness= 45;
			break;
		case _CM_VIVID:
			stConBriData.Contrast = 55;
			stConBriData.Brightness= 55;
			break;
		case _CM_USER:
			stConBriData.Contrast = 60;
			stConBriData.Brightness= 60;
			break;
	}
	CAdjustBrightness();
	CAdjustContrast();
	CEepromSaveBriConData();
}
//---------------------------------------------------------------------------


void CChangePictureMode(void)
{	
	BYTE code *pStr; 

	// change picture mode
	BYTE ucMode = GET_COLOR_MODE();
	ucMode = ValueInRangeChange(_CM_NORMAL, _CM_USER, ucMode, _INC | _LOOP);
	SET_COLOR_MODE(ucMode);

	// save to eeprom
	CEepromSaveSystemData();

	// display picture mode on screen
    ucOsdState = _MI_MENU_NONE;

    InitOsdFrame();
    SetOSDDouble(0x00);//(0x03); 

	switch(GET_COLOR_MODE())
	{
		case _CM_NORMAL:	pStr = sStandard;		break;
		case _CM_SOFT:		pStr = sSoft;			       break;
		case _CM_VIVID:		pStr = sVivid;			break;
		case _CM_USER:		pStr = sPersonal;		       break;
	}
	OSDLine(2, 2, COL_WIDTH, 0xA0,BYTE_COLOR);//wtao100416
	Gotoxy(2, 2, BYTE_DISPLAY);
	Textout(pStr);
    
    OSDPosition(120, 18, 0, 1, 0x03);
	
    COsdFxEnableOsd();
    CPowerPanelOn();  

	// set osd timeout
    CTimerReactiveTimerEvent(SEC(5), COsdTimeOut);


    // change contrast brightness value
    
    CAdjustPicMode();
    
}


//FM CONTROL
//-----------------------------------------------------------------------------------
void CFMControl(void)
{
    CSetFMFreq(_GET_FM_STATE());
	CEepromSaveSystemData();
}

//----------------------------------------------------------------------------------------------------


























void CNotUse(void)
{
    BYTE ucTest = cCodeHDMITemp;

    CAdjustMZHueSat(0);

	ucTest = tLogoTemp;
	DoSetBackColor();
    ucTest = tOSDMenuFunc;

    CAdjustGammaTable(0);

    ucTest = g_tYpbprTemp;
	CDisable();

	CVideoEnable();
	CVideoNTSCEnable();
	CVgaEnable();
//	CHDMIEnable();
//	CDviEnable();
	MDisplayRatioEnable();
	
	AdjustMenuItem(0,0,0);
	GetShowIndex(0,0,0);
	GetShowCount(0,0);

	CSaveTVModeData(0);
	CIOMaskToKeyMaskExt(0);

	CShowNoSignal();

#if(AUDIO_TYPE == _AUDIO_SC7313)
	CSc7313MuteOn();
#endif
	//CEepromSaveHueSatData();
	//CKeyScanReadyTimerEvent();
	//CKeyRepeatEnableTimerEvent();
	//CAutoDoAutoConfig();

	//CAutoDoWhiteBalance();
	//CEepromSaveOsdUserData();
	//CEepromSaveBriConData();
	//CEepromSaveColorTempData();
	//CEepromSaveTvData();
	//CScalerWriteAmount(0,0,0,0);
    //SYMBOL:  _CCENTERTEXTOUT
	SetOsdMap(0,0,0);
	//SetOSDRamAddress();
	//DirectWOSDRam(0, 0, 0, 0);
	//SetRowCmds();
	//Gotoxy(0, 0, 0);
	//OutputChar(0);

	COsdFxCloseWindow(0);
	//ValueInRangeChange(0, 0, 0, 0);
	Textout(0);
	StrLen(0);
	//OSDPosition(0, 0, 0, 0, 0);
	OSDClear(0, 0, 0, 0, 0,0);
	//COsdFxCodeWrite(0);
	//COsdFxEnableOsd();
	//COsdFxDisableOsd();
	COsdFxDrawWindow(0, 0, 0, 0, 0);
	//COsdFxGetAdcClockRange(0);
	InitBurnIn();
	BurnInRun();
    //CKeyScanReady();

   // CSetPWM(0, 0);
    //CTextOutRightAlign(0,0,0);
    //OSDSlider(0, 0, 0, 0, 0,0);

#if(_VIDEO_TV_SUPPORT)
	//CSaveChannelSkip(0,0);
	//CSaveChannelColorType(0,0);
	//CChangeChannel(0);
	//CTuningCurrentChannel(0,0);
	//CTvAutoSearch();
	//CManualSearch(0,0);
//    CFMInit();
#endif
	COsdCtrlGetHPosition();
	COsdCtrlGetVPosition();
	COsdCtrlGetClock();
	//COsdCtrlGetPhase();
    //GetNextLanguage(0);
	//GetPrevLanguage(0);
    CDoReset();

    //AdjustMenuItem(0,0,0);

	CEnable();
	//CVideoEnable();
	//CVgaEnable();
	//CTVEnable();

    //Draw2bit3x2Icon(0,0,0);
    bChangeSource();
    
#if(_VIDEO_TV_SUPPORT)
    #if(_FM_DEVICE)
        CChangeFM();
    #endif
        CShowTimer();
    #if(_IF_PLL_DE_CHIP == _IF_PLL_DE_1338 || _IF_PLL_DE_CHIP == _IF_PLL_DE_135X)
	CSetPifFreq(0,0,0,0);
	CSetSoundFreq(0);
    #endif

	//CShowTVNumber(stTvInfo.ucFMCurrCh, _SHOW_CH_TV_NUMBER);
	kx_CReadIfPllDM();
#endif
    //CCenterTextout(0,ROW(1),COL(0),0);
    //COsdLoad1BitFont(0, 0x00, 123, 0);
    CShowNumber1(0, 0);

    //MColorValueAdj(_DEC);    
    //MMainMenuValueAdj(_DEC); 
    //CAdjustGammaTable(0);

    KxEFLogo1BitAddress();
    KxEFLogo2BitAddress();
    KxEFLogo4BitAddress();

}
//--------------------------------------------------

#endif			//#if(_OSD_TYPE == _OSD003)
