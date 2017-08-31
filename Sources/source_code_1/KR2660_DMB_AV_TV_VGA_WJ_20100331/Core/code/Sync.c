//----------------------------------------------------------------------------------------------------
// ID Code      : Sync.c No.0003
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#define __SYNC__

#include "Core\Header\Include.h"


/**
* CSyncProcess
* For VGA, DVI or YPbPr input source's state machine process.
* first system initial, then main loop
* @param <none>
* @return {none}
*
*/
//--------------------------------------------------
// Description  : For VGA, DVI or YPbPr input source's state machine process.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CSyncProcess(void)
{         
// Eric 0618
#if (_HDMI_SUPPORT == _ON && _HDMI_HOT_PLUG_OPTION)
    if (GET_POWERSTATUS())
    {
        /*
        if (bHDMICONNECT)
		{
            bHot_Plug = _HOT_PLUG_HI;
            bHot_Plug2 = _HOT_PLUG_HI;   
		}         
        else
		{
            bHot_Plug = _HOT_PLUG_LOW;
            bHot_Plug2 = _HOT_PLUG_LOW;            
		}*/
		
        bHot_Plug = _HOT_PLUG_HI;
        bHot_Plug2 = _HOT_PLUG_HI;   
		
    }
#endif

    switch (ucCurrState) 
    {   
    case _SEARCH_STATE:
        if (CSyncHandler())
        {
            // Source and sync OK
            if (CModeDetect()) 
            {
                if (stModeInfo.ModeCurr == _MODE_NOSIGNAL)
                {
#if(_HDMI_HOT_PLUG_OPTION)
                    bDVIDetect = 0;
#endif
                    ucCurrState = _NOSIGNAL_STATE;
                #if (_HDMI_SUPPORT == _ON)
                    if(CHdmiFormatDetect() && 
                       (_GET_INPUT_SOURCE() == _SOURCE_DVI || _GET_INPUT_SOURCE() == _SOURCE_HDMI) && 
                       ( ucHdmiTimerEvent ==0 || ucHdmiTimerEvent == _INACTIVE_COUNTDOWN_EVENT))//741001
                    {
                        ucHdmiTimerEvent = _HDMI_NO_SIGNAL_CHECK_CNT;//741001
                    }
                #endif
                //  SET_READYFORDISPLAY();
                }
                else if (stModeInfo.ModeCurr == _MODE_NOSUPPORT)
                {
#if(_HDMI_HOT_PLUG_OPTION)
                    bDVIDetect = 0;
#endif
                    CModeAutoMeasureOn();
                    ucCurrState = _NOSUPPORT_STATE;
                }
                else        //make sure input soure OK and display mode
                {
            #if(_HDMI_SUPPORT == _ON && _HDMI_HOT_PLUG_OPTION == _ENABLE)
                    //if(!CHdmiFormatDetect() && (_GET_INPUT_SOURCE() == _SOURCE_HDMI) && bDVIDetect == 0)
                    if(!CHdmiFormatDetect() && bDVIDetect == 0)
                    {              
                        bDVIDetect = 1;
                        bHot_Plug = _HOT_PLUG_LOW;
			            bHot_Plug2 = _HOT_PLUG_LOW;
                        CTimerDelayXms(300);
                        bHot_Plug = _HOT_PLUG_HI;
                        bHot_Plug2 = _HOT_PLUG_HI;                        
                        CModeResetMode();
                        return;
                    }
            #endif

                    CPowerLightPowerOff();

                    bShowOSDCurr = (bit)(CScalerGetBit(_OVERLAY_CTRL_6C, _BIT0));
                    CScalerSetBit(_OVERLAY_CTRL_6C, ~_BIT0, 0x00);
                    if(!CModeDisplayActiveMode())
                    {
                        CModeResetMode();
                        break;
                    }
                    CScalerSetBit(_OVERLAY_CTRL_6C, ~_BIT0, bShowOSDCurr);
                    
                    CModeAutoMeasureOn();
            #if(_HDMI_SUPPORT == _ON)
                    if(CHdmiFormatDetect() && (_GET_INPUT_SOURCE() == _SOURCE_DVI || _GET_INPUT_SOURCE() == _SOURCE_HDMI))      //Input source is the HDMI format.
                    {
                        CLR_LIGHTPOWERSTATUS();
                        CHdmiAudioFirstTracking();
                        CTimerReactiveTimerEvent(SEC(0.1), CHdmiAudioWaitingFlagReadyEven);
                        ucHdmiTimerEvent = _HDMI_CHECK_CNT;
                    }
                    else
                    {                           
                    //  SET_READYFORDISPLAY();
                    }

            #else
                //  SET_READYFORDISPLAY();
            #endif
                    SET_READYFORDISPLAY();
                    CTimerCancelTimerEvent(CModeNoSignalEvent);
                    CTimerCancelTimerEvent(CModeNoCableEvent);
                    CTimerCancelTimerEvent(CModeNoSupportEvent);
                    CTimerCancelTimerEvent(CModePowerSavingEvent);

                    ucCurrState = _ACTIVE_STATE;                
                }

                SET_READYFORDISPLAY();
            }
            else
            {
            #if(_HDMI_SUPPORT == _ON)
                if (CHdmiFormatDetect() && (_GET_INPUT_SOURCE() == _SOURCE_DVI || _GET_INPUT_SOURCE() == _SOURCE_HDMI))//for Philips DVD
                    CTimerDelayXms(50);//for Philips DVD
            #endif
            }                                             
            ucTimerEvent = _INACTIVE_COUNTDOWN_EVENT;
        }
        else 
        {
        #if(_HDMI_SUPPORT == _ON)
            if(_GET_INPUT_SOURCE() == _SOURCE_DVI || _GET_INPUT_SOURCE() == _SOURCE_HDMI)
                CTimerCountDownEventProc(&ucTimerEvent, 40, CModeSyncTimeoutCountDownEvent);    
            else
                CTimerCountDownEventProc(&ucTimerEvent, 5,  CModeSyncTimeoutCountDownEvent);
        #else
                CTimerCountDownEventProc(&ucTimerEvent, 5,  CModeSyncTimeoutCountDownEvent);                    
        #endif
        }
        break;

    case _ACTIVE_STATE:
        // For VGA, DVI, input*/
        if (CFrameSyncDetect())
        {
           	CMuteOn();

#if(_HDMI_SUPPORT && _HDMI_HOT_PLUG_OPTION)
            bDVIDetect = 0;
#endif
            //fram sync unstable
            CModeResetMode();
            break;
        }
        else
        {      
            #if (_HDMI_SUPPORT && _HDMI_HOT_PLUG_OPTION == _ENABLE)  
                //eric 20070326 philips DVD player
                //CHDMIStableConfirm();
            #endif  
            if(CModeIsChange())
            {       
#if(_HDMI_SUPPORT && _HDMI_HOT_PLUG_OPTION)
                bDVIDetect = 0;
#endif
                //if((_GET_INPUT_SOURCE() == _SOURCE_YPBPR)||(_GET_INPUT_SOURCE() == _SOURCE_YPBPR1))
                   CMuteOn();
            
            #if (_HDMI_SUPPORT && _HDMI_HOT_PLUG_OPTION == _ENABLE)
                    //CModeHDMIChageDelay();
            #endif      
                CModeResetMode();
                break;
            }
            else
            {
#if(_HDMI_SUPPORT == _ON)
                if(_GET_INPUT_SOURCE() == _SOURCE_DVI || _GET_INPUT_SOURCE() == _SOURCE_HDMI)
                {
                    if(CHdmiFormatDetect())     //Input source is the HDMI format.
                    {
                        if(!GET_HDMIINPUT()) 
                        {   
                            CModeResetMode();   
                            break;
                        }
                        else
                        {
                            //if(GET_AUDIOWAITINGTIMEOUT())  // Eric Lee mark for hdmi audio delay output
                                CHdmiEnableAudioOutput();
                        }
                    }
                    else
                    {
                        if(GET_HDMIINPUT())
                        {
                		    CMuteOn();
                            CModeResetMode();           
                            break;
                        }
                    }
                }
#endif
					
                CSetModeReady();
            }
        }

        break;
        
    case _NOSUPPORT_STATE:
		CMuteOn();
        if (GET_READYFORDISPLAY() == _TRUE) 
        {
            CLR_READYFORDISPLAY();
            SET_OSD_READYFORDISPLAY(); 
            CModeSetFreeRun();
        //  CAdjustBackgroundColor(0xff, 0x00, 0x00);
        }
        if (CModeConnectIsChange() || CModeIsChange())
            CModeResetMode();
        break;
        
    case _NOSIGNAL_STATE: 
    #if (_HDMI_HOT_PLUG_OPTION == _ENABLE)  
        if(GET_READYFORDISPLAY())
            if (_GET_INPUT_SOURCE() == _SOURCE_HDMI || _GET_INPUT_SOURCE() == _SOURCE_DVI) 
            {
                CLR_READYFORDISPLAY();
                CModeHdmiHP();
            }
    #endif
        if (!GET_SHOW_NO_SIGNAL()) 
        {
            SET_SHOW_NO_SIGNAL();
            CModeSetFreeRun();
            SET_OSD_READYFORDISPLAY();

        }   
                                           
        ucInputSyncType = _NO_SYNC_STATE;
        CLR_MODESTABLE();
    //  ucCurrState = _SEARCH_STATE;    
        if ((CModeConnectIsChange() || CSourceHandler()) && !bSourceVideo())
        {
            CPowerLedOn();
            CModeResetMode();
        }
        break;

    case _SLEEP_STATE:
        if ((CModeConnectIsChange() || CSourceHandler()) && !bSourceVideo())
        {
            CPowerLedOn();
            CModeResetMode();
        }
        break;

    default:
        break;
    }
}

//--------------------------------------------------
void CSetModeReady(void)
{
#if (_HDMI_SUPPORT == _ON)
    if((_GET_INPUT_SOURCE()==_SOURCE_DVI || _GET_INPUT_SOURCE() == _SOURCE_HDMI) && CHdmiFormatDetect())
    {           
        if (GET_READYFORDISPLAY() == _TRUE) 
        {
            CPowerPanelOn();
            if (GET_LIGHTPOWERSTATUS() == _OFF) 
            {
                CPowerLightPowerOn();
                SET_OSD_READYFORDISPLAY(); 
            }
            if(ucHdmiTimerEvent == _HDMI_CHECK_CNT)
            {
                //CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5), (0x00));
                //CLR_READYFORDISPLAY();
                CLR_SOURCE_AUTOCHANGE();
                CScalerPageSelect(_PAGE2);
                CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_VWDSR_41, ~_BIT0, _BIT0);//Enable packet variation Watch Dog
                CAdjustEnableWatchDog(_WD_DV_TIMEOUT|_WD_FRAMESYNC);            
                if (GET_CLEAR_OSD_EN())
                    ucHdmiTimerEvent--;
                else
                    ucHdmiTimerEvent = 0;

                if (GET_FIRST_SHOW_NOTE())
                   ucOsdEventMsg = _DO_SHOW_NOTE;         
            }
            else if(ucHdmiTimerEvent == 0)
            {
                CModeHDMITimeoutCountDownEvent();
                ucHdmiTimerEvent =_INACTIVE_COUNTDOWN_EVENT;
            }
            else if(ucHdmiTimerEvent ==_INACTIVE_COUNTDOWN_EVENT)
            {
                return;
            }                   
            else
            {
                ucHdmiTimerEvent--;
                if (!GET_CLEAR_OSD_EN())
                    CTimerDelayXms(50);
            }
        }
    }           
    else
    {
        if (GET_READYFORDISPLAY() == _TRUE) 
        {
            //CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5), 0x00);    
            CLR_READYFORDISPLAY();
            CLR_SOURCE_AUTOCHANGE();
 
            //080324
            if((_GET_INPUT_SOURCE() == _SOURCE_VGA) || (_GET_INPUT_SOURCE() == _SOURCE_YPBPR)||(_GET_INPUT_SOURCE() == _SOURCE_YPBPR1))
            {
                CAdjustAdcClock(stModeUserData.Clock, 1);
                CAdjustAdcClock(stModeUserData.Clock, 2);
            }           
            CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5), _BIT3);  
            CPowerPanelOn();
            if (GET_LIGHTPOWERSTATUS() == _OFF) 
            {
                CPowerLightPowerOn();
            }
        
        #if (_YPBPR_NONE_CHECK_APLL)
            if((_GET_INPUT_SOURCE() == _SOURCE_YPBPR)||(_GET_INPUT_SOURCE() == _SOURCE_YPBPR1))
            {
                CAdjustDisableWatchDog(_WD_ALL);            // Disable watch dog
                CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5), _BIT3);  
            }
            else
        #endif      
            {
                if (bCNoCheckSyncMode())
                    CAdjustDisableWatchDog(_WD_ALL);            // Disable watch dog
                else if (_GET_INPUT_SOURCE()==_SOURCE_VGA)
                    CAdjustEnableWatchDog(_WD_DV_TIMEOUT | _WD_FRAMESYNC);  // not to watch APLL mis-Lock,hill 20070417
                else
                    CAdjustEnableWatchDog(_WD_ALL);
            }
 
            SET_OSD_READYFORDISPLAY(); 
            if (GET_FIRST_SHOW_NOTE())
               ucOsdEventMsg = _DO_SHOW_NOTE;
 
            if (stModeUserData.FirstAuto == 0) 
            {
                stModeUserData.FirstAuto = 1;
                ucOsdEventMsg = _DO_AUTO_CONFIG;
            }
        }
    }
#else
    if (GET_READYFORDISPLAY() == _TRUE) 
    {
        //CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5), 0x00);
        CLR_READYFORDISPLAY();
        CLR_SOURCE_AUTOCHANGE();
    #if(_OD_SUPPORT == _ON)
        CMemorySetODCompress();
        CMemorySetODFIFO();
        CMemorySetODOnOff(_ON);
    #endif
        //080324
        if((_GET_INPUT_SOURCE() == _SOURCE_VGA) || (_GET_INPUT_SOURCE() == _SOURCE_YPBPR)||(_GET_INPUT_SOURCE() == _SOURCE_YPBPR1))
        {
            CAdjustAdcClock(stModeUserData.Clock, 1);
            CAdjustAdcClock(stModeUserData.Clock, 2);
        }           
        CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5), _BIT3);
        CPowerPanelOn();
        if (GET_LIGHTPOWERSTATUS() == _OFF) 
        {
            CPowerLightPowerOn();
        }
 
    #if (_YPBPR_NONE_CHECK_APLL)
        if((_GET_INPUT_SOURCE() == _SOURCE_YPBPR)||(_GET_INPUT_SOURCE() == _SOURCE_YPBPR1))
        {
            CAdjustDisableWatchDog(_WD_ALL);            // Disable watch dog
            CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5), _BIT3);
        }
        else
    #endif      
        {
            if (bCNoCheckSyncMode())
                CAdjustDisableWatchDog(_WD_ALL);            // Disable watch dog
            else if (_GET_INPUT_SOURCE()==_SOURCE_VGA)
                CAdjustEnableWatchDog(_WD_DV_TIMEOUT | _WD_FRAMESYNC);  // not to watch APLL mis-Lock,hill 20070417
            else
                CAdjustEnableWatchDog(_WD_ALL);
        }
        SET_OSD_READYFORDISPLAY(); 
        if (GET_FIRST_SHOW_NOTE())
           ucOsdEventMsg = _DO_SHOW_NOTE;   
          
        if (stModeUserData.FirstAuto == 0) 
        {
            stModeUserData.FirstAuto = 1;
            ucOsdEventMsg = _DO_AUTO_CONFIG;
        }
    }
#endif
}



//--------------------------------------------------
// Description  : Measure sync type
// Input Value  : None
// Output Value : Return _TRUE if succeed
//--------------------------------------------------
bit CSyncHandler(void)
{
    if (ucInputSyncType == _NO_SYNC_STATE)
    {
        if (!CSourceHandler())   //input Source not exist
        {
            ucInputSyncType = _NO_SYNC_STATE;
            return _FALSE;
        }
        
        if (_SOURCE_DVI == _GET_INPUT_SOURCE() || _SOURCE_HDMI == _GET_INPUT_SOURCE())
           CTimerDelayXms(5);
       // else
        CTimerDelayXms(4);
        
        ucInputSyncType = CSyncMeasureSyncType();
        switch (ucInputSyncType)
        {
        case _NO_SYNC_STATE:
            return _FALSE;
            
        case _SS_STATE:
        case _CS_STATE:
        case _SOG_STATE:
            return _TRUE;
            
#if(_YPBPR_SUPPORT == _ON)
        case _SOY_STATE:
#if(_YPBPR_NEW_SYNC_DETECT == _ON)
            CScalerSetBit(_SYNC_INVERT_48, ~_BIT2,0x00);
#endif
            return _TRUE;
#endif
            
#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
        case _DSS_STATE:
  #if (_HDMI_SUPPORT == _ON)
            if(CHdmiFormatDetect())//Input source is the HDMI format.
            {
                if(CHdmiFormatDetect())     //Input source is the HDMI format.
                {
                    if (!GET_HDMIINPUT())//_GET_INPUT_SOURCE() != _SOURCE_HDMI)
                    {
                       // _SET_INPUT_SOURCE(_SOURCE_HDMI);
                        CModeResetMode();
                    }
                }
                else
                    CLR_HDMIINPUT();
                //  _SET_INPUT_SOURCE(_SOURCE_DVI);
             }
  #endif
             return _TRUE;
#endif
                
        default:
            ucInputSyncType = _NO_SYNC_STATE;
            return _FALSE;
        }
    }
    else
    {
        switch (_GET_INPUT_SOURCE())
        {
#if(_YPBPR_SUPPORT == _ON)
        case _SOURCE_YPBPR:
        case _SOURCE_YPBPR1:
#endif
        case _SOURCE_VGA:
            CScalerSetBit(_SYNC_CTRL_49, ~(_BIT1 | _BIT0), _BIT1);
            break;
            
#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
        case _SOURCE_DVI:
        case _SOURCE_HDMI:
            CScalerSetBit(_SYNC_CTRL_49, ~(_BIT1 | _BIT0), 0x00);
            break;
#endif
        }
        return _TRUE;
    }
}

/**
* CSyncMeasureSyncType
* Measure sync type
* called only by CSyncHandler
* identify sync type according to the input source
* @param <none>
* @return {sync type we measured}
*
*/

BYTE CSyncMeasureSyncType(void)
{
    BYTE synctypetemp;
    
    switch (CGetSourcePortType(_GET_INPUT_SOURCE()))
    {
#if(_YPBPR_SUPPORT == _ON)
    case _YPBPR_A0_PORT:
#endif

    case _DSUB_A0_PORT:
    //  if(CGetSourcePortType(_GET_INPUT_SOURCE()) == _DSUB_A0_PORT)
            CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), 0x00);//SOY0 , 1st HS/VS                       
    //  else
    //      CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));//SOY1 ,2nd HS/VS 
        
        //HS_RAW/SOY,source selection
        CScalerSetBit(_SYNC_SELECT_47, ~_BIT4, ((BYTE)bHsyncSelection << 4));
        synctypetemp    = CSyncSearchSyncTypeVGA();
        break;
        
#if(_YPBPR_SUPPORT == _ON)
    case _YPBPR_A1_PORT:
#endif
    case _DSUB_A1_PORT:
    //  if(CGetSourcePortType(_GET_INPUT_SOURCE()) == _DSUB_A0_PORT)
    //      CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), 0x00);//SOY0 , 1st HS/VS                       
    //  else
            CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));//SOY1 ,2nd HS/VS 
        
        //HS_RAW/SOY,source selection
        CScalerSetBit(_SYNC_SELECT_47, ~_BIT4, ((BYTE)bHsyncSelection << 4));
        synctypetemp    = CSyncSearchSyncTypeVGA();
        break;
        
#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
    case _DVI_PORT:
    case _HDMI_PORT:
    case _DVI_D0_PORT:
    case _DVI_D1_PORT:
    case _HDMI_D0_PORT:
    case _HDMI_D1_PORT:
        synctypetemp = CSyncSearchSyncTypeDVI();
        break;
               /*
    case _DVI_I_A0_PORT:
        synctypetemp = CSyncSearchSyncTypeDVI();
        if (synctypetemp == _NO_SYNC_STATE)
        {
            CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), 0x00);
            CScalerSetBit(_SYNC_SELECT_47, ~_BIT4, ((BYTE)bHsyncSelection << 4));
            synctypetemp = CSyncSearchSyncTypeVGA();
        }
        break;
              */
#endif//(_TMDS_SUPPORT == _ON)
        
    default:
        break;
        
    }
    
#if(_HSYNC_TYPE_DETECTION == _AUTO_RUN)
    if (1)
#endif
        
#if(_HSYNC_TYPE_DETECTION == _NORMAL_RUN)
        if (synctypetemp != _SS_STATE)
#endif
        {
            CAdjustSyncProcessorMeasureStart();
            
            if (CTimerPollingEventProc(60, CMiscModeMeasurePollingEvent))
            {
                if (CModeMeasureData())
                    CSyncModifyPolarityVGA();
                else
                    synctypetemp = _NO_SYNC_STATE;
            }
            else
                synctypetemp = _NO_SYNC_STATE;
        }
        
        return synctypetemp;
}

/**
* CSyncSearchSyncTypeVGA
* Search VGA sync type
* if the same type is searched for 3 times return sync type
* @param <none>
* @return {sync type}
*
*/
//--------------------------------------------------
// Description  : Search VGA sync type
// Input Value  : None
// Output Value : Return sync type
//--------------------------------------------------
BYTE CSyncSearchSyncTypeVGA(void)
{
#define _SYNCTYPE_CONFIRM_TIMES   3
    
    BYTE synctypeprev, synctypecurr, cnt;
    
    cnt = _SYNCTYPE_CONFIRM_TIMES;
    
    do
    {
#if(_HSYNC_TYPE_DETECTION == _NORMAL_RUN)
        synctypecurr = CSyncGetSyncTypeStepVGA();
#elif(_HSYNC_TYPE_DETECTION == _AUTO_RUN)
        synctypecurr = CSyncGetSyncTypeAutoRun();
#endif
        
        if (cnt == _SYNCTYPE_CONFIRM_TIMES)
        {
            synctypeprev = synctypecurr;
            continue;
        }
        
        if (synctypecurr != synctypeprev)
        {
            return _NO_SYNC_STATE;
        }
        
    }
    while (--cnt);
    
    return synctypecurr;
    
#undef _SYNCTYPE_CONFIRM_TIMES
}

#if(_HSYNC_TYPE_DETECTION == _NORMAL_RUN)
/**
* CSyncGetSyncTypeStepVGA
* Get VGA sync type according to sync detection by detecting registers
* @param <none>
* @return {sync type}
*
*/
BYTE CSyncGetSyncTypeStepVGA(void)
{
    BYTE flag, cnt = 0;
    
    CScalerPageSelect(_PAGE0);
    CScalerSetByte(_P0_ADC_POWER_AD, 0x18);//DCR  enable,1M
    
    CScalerSetByte(_VGIP_ODD_CTRL_13, 0x00);
    CScalerSetByte(_YUV2RGB_CTRL_9C, 0x00);//disable YUV->RGB
    CScalerSetBit(_IPH_ACT_WID_H_16, ~(_BIT7 | _BIT3), 0x00);
    CScalerSetBit(_SCALE_CTRL_32, ~_BIT7, 0x00); //disable video compensation
    CScalerSetBit(_SYNC_CTRL_49, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT1); // SeHS/DeHS ,ADC_HS/ADC/VS
    CScalerSetBit(_SYNC_INVERT_48, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));// HS_OUT ,clamp output enable
    
    if((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4)) //V304 modify
    {
        CScalerPageSelect(_PAGE0);
        CScalerSetByte(_P0_ADC_TEST_CTRL_AF, 0x04);
    }
    
    CScalerSetBit(_SYNC_SELECT_47, ~_BIT5, _BIT5);  //Enable De-composite circuit
    
    // Vsync counter level 384 crystal clocks
    CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~(_BIT2 | _BIT1 | _BIT0), 0x03);//768Hsync
    CScalerSetByte(_VSYNC_COUNTER_LEVEL_LSB_4D, 0x00);
    
    do
    {
        CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, 0x00);
        CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, _BIT0);//Measure start
        
        
        if(!CTimerPollingEventProc(20, CMiscStableFlagPollingEvent))
        {
            if((bit)CScalerGetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, _BIT7))//HS_Overflow
                return _NO_SYNC_STATE;  //No signal
            else
                return _NO_SYNC_STATE;  //Not support
        }
        
        CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT1, _BIT1);//Pop up stable value
        
        if(!(bit)CScalerGetBit(_STABLE_MEASURE_4F, _BIT6))//Stable polarity
        {
            CScalerSetBit(_SYNC_INVERT_48, ~_BIT3, CScalerGetBit(_SYNC_INVERT_48, _BIT3) ^ _BIT3);
            cnt++;
        }
        else
            break;
        
        if(cnt >= 2)
            return _NO_SYNC_STATE;
    }
    while(_TRUE);
    
    CScalerSetByte(_HSYNC_TYPE_DETECTION_FLAG_4E, 0xff);
    CTimerDelayXms(40);
    flag = CScalerGetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, 0xff);
    
    if((bit)(flag & _BIT6) || (bit)(flag & _BIT5) || (bit)(flag & _BIT3))// 1.Stable period chang 2.Stable polarity chang 3.window unlock
        return _NO_SYNC_STATE;
    else if((bit)(flag & _BIT1))  // Composite-Sync
    {
        CScalerSetBit(_SYNC_CTRL_49, ~(_BIT6 | _BIT5 | _BIT2), (_BIT6 | _BIT5 | _BIT2));// 1.DeHS 2.DeVS3..
        if((bit)(flag & _BIT0))   // Not SOY signal
        {
            CScalerSetBit(_SYNC_INVERT_48, ~(_BIT6 | _BIT1), (_BIT6 | _BIT1));
            if((bit)(flag & _BIT2))
                return _CS_STATE;  //CS with Equalizer
            else
                return _CS_STATE;  //OR-Type & XOR-Type CS
        }
        else
        {
            CScalerSetBit(_SYNC_INVERT_48, ~(_BIT6 | _BIT1), 0x00);
            if((bit)(flag & _BIT2))
                return _SOY_STATE;  //YPbPr
            else
#if(_YPBPR_SUPPORT == _ON)
                if((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4))
                    return _SOY_STATE;
                else
                    return _CS_STATE;
#else
                return _CS_STATE;
#endif
        }
    }
    else            // Check if Hsync only
    {
        CScalerSetBit(_SYNC_CTRL_49, ~(_BIT6 | _BIT5 | _BIT2), _BIT2);
        CScalerSetBit(_SYNC_SELECT_47, ~_BIT5, 0x00);  //Disable De-composite circuit
        CAdjustSyncProcessorMeasureStart();
        if(CTimerPollingEventProc(60, CMiscModeMeasurePollingEvent))
        {
            if(CModeMeasureData())
            {
                CSyncModifyPolarityVGA();
                return _SS_STATE;
            }
            else
                return _NO_SYNC_STATE;
        }
        else
            return _NO_SYNC_STATE;
    }
}
#endif  // End of #if(_HSYNC_TYPE_DETECTION == _NORMAL_RUN)

/**
* CSyncModifyPolarityVGA
* Modify VGA sync polarity
* @param <none>
* @return {none}
*
*/
//--------------------------------------------------
// Description  : Modify VGA sync polarity
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CSyncModifyPolarityVGA(void)
{
    BYTE polarity;
    
    polarity = CScalerGetBit(_VGIP_SIGINV_11, 0xff);
    polarity &= ~(_BIT3 | _BIT2);
    
    if(!(bit)(stModeInfo.Polarity & _BIT0))
        polarity |= _BIT2;
    
    if(!(bit)(stModeInfo.Polarity & _BIT1))
        polarity |= _BIT3;
    
    CScalerSetByte(_VGIP_SIGINV_11, polarity);
}

/**
* CSyncSearchSyncTypeDVI
* Search DVI sync type
* called only by CSyncMeasureSyncType
* if the same type is searched for 3 times return sync type
* @param <none>
* @return {sync type}
*
*/
//--------------------------------------------------
// Description  : Search DVI sync type
// Input Value  : None
// Output Value : Return sync type
//--------------------------------------------------
#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
BYTE CSyncSearchSyncTypeDVI(void)
{
    BYTE synctypetemp = _DSS_STATE;
    //initial DVI register setting add by frank
    CScalerSetByte(_VGIP_ODD_CTRL_13, 0x00);

#if(_HDMI_SUPPORT == _ON)   
    if(!CHdmiFormatDetect())
#endif
        CScalerSetByte(_YUV2RGB_CTRL_9C, 0x00);
    
    CScalerSetBit(_IPH_ACT_WID_H_16, ~(_BIT7 | _BIT3), 0x00);
    CScalerSetBit(_SCALE_CTRL_32, ~_BIT7, 0x00);
    CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~_BIT3, 0x00);
    
    CPowerADCAPLLOff();
    
    CScalerPageSelect(_PAGE2);
    if(!CSourceScanInputPortDVI((bit)CScalerGetBit(_P2_POWER_ON_OFF_CTRL_A7, _BIT7)))
        return _NO_SYNC_STATE;
    
#if(((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON)) && (_DVI_LONG_CABLE_SUPPORT == _ON))
    if(CAdjustTMDSEqualizer() == _FALSE)
        return _NO_SYNC_STATE;
#endif
    
    CPowerTMDSOn(); // Measure HS/VS source select as TMDS
    
    return synctypetemp;
}
#endif  // End of #if(_TMDS_SUPPORT == _ON)



#if(_HSYNC_TYPE_DETECTION == _AUTO_RUN)
/**
* CSyncGetSyncTypeAutoRun
* Get VGA sync type by Hsync Type Detection Auto Run
* @param <none>
* @return {sync type}
*
*/
BYTE CSyncGetSyncTypeAutoRun(void)
{
    BYTE synctemp;
    
    CScalerPageSelect(_PAGE0);
    CScalerSetBit(_P0_ADC_POWER_C6, ~(_BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4 | _BIT3));//ADC RGB power
    CScalerSetBit(_IPH_ACT_WID_H_16, ~_BIT7, 0x00);
    CScalerSetBit(_SCALE_CTRL_32, ~_BIT7, 0x00); //video mode compensation disable
    CScalerSetBit(_SYNC_CTRL_49, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT1);// ADC_HS/ADC_VS ,SeHS/DeHS
    CScalerSetByte(_P0_ADC_CLAMP_CTRL1_D5, 0x00);//clamp to black_Low
    if((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT3)) // SOG1/SOY1
        CScalerSetBit(_P0_ADC_SOG_CTRL_D6, ~(_BIT1 | _BIT0), _SOY_RESISTER);// R=500K,10n
    else // SOG0/SOY0
        CScalerSetBit(_P0_ADC_SOG_CTRL_D6, ~(_BIT3 | _BIT2), (_SOY_RESISTER << 2));// R=500K,10n        
    
    CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, 0x00);//Measure- Clear
    CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, _BIT0);//Measure- Start
    
    CTimerDelayXms(5);
    
    if((bit)CScalerGetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, _BIT7))
    {// Hsync overflow
        return _NO_SYNC_STATE;
    }
    //eric 20070523 VGA long time wake up 
    CTimerDelayXms(60);
    if(!((bit)CScalerGetBit(_STABLE_MEASURE_4F, _BIT7)))//both polarity and period are stable
        return _NO_SYNC_STATE;
    CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT1, _BIT1);//Pop up result
    
    // Get stable period
    CScalerRead(_STABLE_PERIOD_H_50, 2, pData, _AUTOINC);
    ((WORD *)pData)[1] = ((pData[0] & 0x07) << 8) | pData[1];
    
    if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
    {
        CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~(_BIT2 | _BIT1 | _BIT0), (BYTE)(((WORD *)pData)[1] >> 10) & 0x07);
        CScalerSetByte(_VSYNC_COUNTER_LEVEL_LSB_4D, (BYTE)(((WORD *)pData)[1] >> 2));
    }
    else
    {
        if(((WORD *)pData)[1]<=0x500)   
        {
            if((((WORD *)pData)[1]<=0x2D4)&&(((WORD *)pData)[1]>=0x2C9))
            {
                //720P50
                CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~(_BIT2 | _BIT1 | _BIT0), (BYTE)(((WORD *)pData)[1] >> 8) & 0x07);
                CScalerSetByte(_VSYNC_COUNTER_LEVEL_LSB_4D, (BYTE)(((WORD *)pData)[1] ));
            }
            else
            {
                //480p (_STABLE_PERIOD=0x6B3)
                CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~(_BIT2 | _BIT1 | _BIT0), (BYTE)(((WORD *)pData)[1] >> 10) & 0x07);
                CScalerSetByte(_VSYNC_COUNTER_LEVEL_LSB_4D, (BYTE)(((WORD *)pData)[1] >> 2));               
            }
            
            
        }
        else
        {
            //480i (_STABLE_PERIOD=0x359)
            CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~(_BIT2 | _BIT1 | _BIT0), (BYTE)(((WORD *)pData)[1] >> 9) & 0x07);
            CScalerSetByte(_VSYNC_COUNTER_LEVEL_LSB_4D, (BYTE)(((WORD *)pData)[1] >> 1));
        }       
    }   
    CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, 0x00);//stable measure stop
    
    CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, 0x00);
    CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, _BIT6);  //Enable hsync type detection auto run
    
    if(CTimerPollingEventProc(90, CMiscHsyncTypeAutoRunFlagPollingEvent)) //auto run ready
    {
        synctemp = (CScalerGetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, 0xff) & 0x70) >> 4;//Measur result
        ucStablePol = ~(CScalerGetBit(_STABLE_PERIOD_H_50, _BIT6) >> 6); //Get Hsync Polarity
#if(_YPBPR_AUTO_SOY == _ENABLE)
        if((_GET_INPUT_SOURCE() == _SOURCE_YPBPR)||(_GET_INPUT_SOURCE() == _SOURCE_YPBPR1))
        {
            if((synctemp == 0)||(synctemp == 1))
            {   // No-signal or Not-support         
                SyncLevelOffset++;
                CYPbPrAutoSOY();        // Adjust SOG sync level
            }
        }
#endif
        switch(synctemp)
        {//eric 20070530
        case _NO_SIGNAL:        // No Signal
        case _NOT_SUPPORT:      // Not Support
        case _HSYNC_WITHOUT_VS: // Hsync only
            synctemp =_NO_SYNC_STATE;   
            break;                      
            
        case _YPBPR_SYNC:       // YPbPr-Type CS
            synctemp =_SOY_STATE;
            break;  
            
        case _SERRATION_CS:     // Serration-Type CS
#if(_YPBPR_SUPPORT == _ON)
#if(_HSYNC_TYPE_SELECT == _HSYNC_WITH_SOG_SOY)
            if((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4))
            {
                if(CModeMeasureReady())
                {
                    if(CModeMeasureData())
                    {
                        if((stModeInfo.IHFreq < Panel.HSyncMinFreq) || (stModeInfo.IHFreq > Panel.HSyncMaxFreq) || (stModeInfo.IVFreq < Panel.VSyncMinFreq) || (stModeInfo.IVFreq > Panel.VSyncMaxFreq))
                        {
                            synctemp=_NO_SYNC_STATE;
                            break;                                                  
                        }
                        else
                        {                                   
                            if(CYPbPrSearchMode() != _MODE_NOSUPPORT)
                                synctemp = _SOY_STATE;                                              
                            else
                                synctemp =_CS_STATE;                                                                
                            break;          
                        }
                    }
                }
                else
                {
                    synctemp = _NO_SYNC_STATE;
                    break;                                  
                }
            }
            else
            {
                synctemp =_CS_STATE;
                break;                              
            }            
#else
            if((_GET_INPUT_SOURCE() == _SOURCE_YPBPR)||(_GET_INPUT_SOURCE() == _SOURCE_YPBPR1))
                synctemp =_SOY_STATE;                                                       
            else
                synctemp = _CS_STATE;
            break;                      
            
#endif  //End of #if(_HSYNC_TYPE_SELECT == _HSYNC_WITH_SOG_SOY)
#else
            synctemp =_CS_STATE;
            break;          
#endif
            
        case _XOR_OR_TYPE_CS_WITH_EQR:      // CS with Equalizer
        case _XOR_OR_TYPE_CS_WITHOUT_EQR:       // OR-Type & XOR-Type CS
            synctemp =_CS_STATE;
            break;              
            
        case _SEPARATE_HSYNC:       // Separate Sync
            synctemp =_SS_STATE;
            break;              
            
        default:        // Hsync only
            synctemp =_NO_SYNC_STATE;               
        }
        
    }
    else
        synctemp =_NO_SYNC_STATE;   
    
#if(_HSYNC_TYPE_SELECT != _HSYNC_ONLY)
    if((synctemp != _NO_SYNC_STATE) && ((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4)))
    {
        CScalerRead(_STABLE_HIGH_PERIOD_H_4A, 2, pData, _AUTOINC);
        stModeInfo.IHSyncPulseCount = ((pData[0] & 0x07) << 8) | pData[1];
        
        CScalerRead(_STABLE_PERIOD_H_50, 2, pData, _AUTOINC);
        stModeInfo.IHCount = ((pData[0] & 0x07) << 8) | pData[1];
        
        if(((stModeInfo.IHSyncPulseCount * 7 / stModeInfo.IHCount) != 0) || (stModeInfo.IHSyncPulseCount < 4))
            synctemp = _NO_SYNC_STATE;
    }
#endif  // End of #if(_HSYNC_TYPE_SELECT != _HSYNC_ONLY)
    
    return synctemp;    
    
}
#endif  // End of #if(_HSYNC_TYPE_DETECTION == _AUTO_RUN)


#if(_YPBPR_AUTO_SOY == _ENABLE)
void CYPbPrAutoSOY(void)
{
    if((SOGSyncLevel - SyncLevelOffset) < MinSOGSyncLevel)
        SyncLevelOffset = 0;
    CScalerPageSelect(_PAGE0); //_P0_SOG0_CTRL_AB
    
    //eric 20070530
    if(CGetSourcePortType(_GET_INPUT_SOURCE()) == _YPBPR_A0_PORT)   
        CScalerSetByte(_P0_ADC_SOG0_CTRL_D2,SOGSyncLevel - SyncLevelOffset);
    else
    {
        CScalerPageSelect(_PAGEB);
        CScalerSetByte(_PB_SOYCH0_CFG3_C3,SOGSyncLevel - SyncLevelOffset);
    }
}
#endif

//--------------------------------------------------
bit bCNoCheckSyncMode(void)
{

    if ((_GET_INPUT_SOURCE()==_SOURCE_VGA) && 
                                            (stModeInfo.ModeCurr == (_MODE_1440x900_60HZ_RB) ||
                                             stModeInfo.ModeCurr == (_MODE_1440x900_60HZ)    ||
                                             stModeInfo.ModeCurr == (_MODE_1024x768_60HZ)    ||
                                             stModeInfo.ModeCurr == (_MODE_1024x768_70HZ)    ||
                                             stModeInfo.ModeCurr == (_MODE_1360x768_60HZ)	 ||
                                             stModeInfo.ModeCurr == (_MODE_720x400_70HZ)	 ||
											 stModeInfo.ModeCurr == (_MODE_1680x1050_60HZ)	 ||
                                             stModeInfo.ModeCurr == (_MODE_640x480_60HZ)))	
        return _TRUE;

    if ((_GET_INPUT_SOURCE()==_SOURCE_DVI) && 
                                            (stModeInfo.ModeCurr == (_MODE_1440x900_60HZ_RB) ||
                                             stModeInfo.ModeCurr == (_MODE_1440x900_60HZ)))//    ||
                                           //  stModeInfo.ModeCurr == (_MODE_1024x768_72HZ)    ||
                                             //stModeInfo.ModeCurr == (_MODE_1024x768_70HZ)))
        return _TRUE;



    return _FALSE;
}
