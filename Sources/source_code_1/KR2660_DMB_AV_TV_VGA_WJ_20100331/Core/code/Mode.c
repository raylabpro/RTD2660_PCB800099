//----------------------------------------------------------------------------------------------------
// ID Code      : Mode.c No.0002
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#define __MODE__

#include "Core\Header\Include.h"




unsigned char code HDMI_ModeMap[] =
{
    0,  1,  2,  2,  3,  4,  
    1,  1,  1,  1,  1,  1,  
    1,  1,  2,  2,  5,  2,  
    2,  3,  4,  1,  1,  1,  
    1,  1,  1,  1,  1,  2,   
    2,  5,  5,  5,  5
};

//--------------------------------------------------
// Description  : Mode handler, the main control flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeHandler(void)
{
    if (CPowerHandler()) 
    {
        ucCurrState = GET_POWERSTATUS() ? _INITIAL_STATE : _PWOFF_STATE;
    }
	
    switch (ucCurrState)
    {
        case _PWOFF_STATE:
            ucCurrState = GET_POWERSTATUS() ? _INITIAL_STATE : _PWOFF_STATE;
            break;

        case _INITIAL_STATE:
            if (bSourceVideo())
            {
               CVideoInitial();
            }

            SET_FIRST_SHOW_NOTE();
            ucCurrState = _SEARCH_STATE;


#if(_LOGO_ENABLE)
            CModeSetFreeRun();
            CDrawLogo();
#endif

            if(1)//GET_FIRST_LOADFONT() == _TRUE)
            {
                CLR_FIRST_LOADFONT();
                COsdDispFirstTimeLoadFont();
            }

            if (_GET_INPUT_SOURCE() == _SOURCE_DVI || _GET_INPUT_SOURCE() == _SOURCE_HDMI || _GET_INPUT_SOURCE() == _SOURCE_YPBPR||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1)
            {
                CShowNote();//ucOsdEventMsg = _DO_SHOW_NOTE;
                CPowerPanelOn();
                if (GET_LIGHTPOWERSTATUS() == _OFF) 
                {
                    CPowerLightPowerOn();
                }
            }

            break;
                    
        case _SEARCH_STATE:
   #if(AUDIO_TYPE == _AUDIO_SC7313 || AUDIO_TYPE == _AUDIO_PWM)
            CInitSoundChannel(_GET_INPUT_SOURCE());
   #endif
        case _ACTIVE_STATE:
        case _NOSIGNAL_STATE:
        case _NOSUPPORT_STATE:
        case _SLEEP_STATE:
            switch (_GET_INPUT_SOURCE()) 
            {
                case _SOURCE_YPBPR:
                case _SOURCE_YPBPR1:
                case _SOURCE_VGA:
                case _SOURCE_DVI:
                case _SOURCE_HDMI:
                    CSyncProcess();
                break;
            #if(_VIDEO_SUPPORT == _ON)
                case _SOURCE_VIDEO_AV:
                case _SOURCE_VIDEO_SV:
                case _SOURCE_VIDEO_TV:
                    CVideoProcess();
                break;
            #endif
                case _SOURCE_NONE:   // Don't need to do anything
                break;
                
            default:
                break;
            }
            break;
                    
        default:
            while(_TRUE);
    }
}
//--------------------------------------------------
// Description  : Check measure ready process
// Input Value  : None
// Output Value : Return _TRUE if measure finished, _FALSE if timeout
//--------------------------------------------------
bit CModeMeasureReady(void)
{
    CScalerSetBit(_SYNC_SELECT_47, ~_BIT0, 0x00);
    CAdjustSyncProcessorMeasureStart();
    if (CTimerPollingEventProc(60, CMiscModeMeasurePollingEvent)) 
    {
        return _TRUE;
    } 
    else
    {
        CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT5, 0x00);
        return _FALSE;
    }
}

/**
* CSyncMeasureSyncType
* Get measure data and convert into system information
* @param <none>
* @return {_TRUE if success, _FALSE if the measurement result is out of range}
*
*/
bit CModeMeasureData(void)
{

    if(_GET_INPUT_SOURCE() == _SOURCE_DVI || _GET_INPUT_SOURCE() == _SOURCE_HDMI)
    {
        CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, _BIT6);  
        CScalerSetBit(_SYNC_CTRL_49, ~_BIT2, _BIT2);
    }
    
    // Read measurement status bit
    CScalerRead(_MEAS_HS_PERIOD_H_52, 3, &pData[8], _AUTOINC);// 
    if((bit)(pData[8] & _BIT4) || (bit)(pData[10] & _BIT4) || (bit)(pData[10] & _BIT5))
    {
        return _FALSE;
    }           
    
    // Pop up measurement result
    CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT6, _BIT6);
    if(CTimerPollingEventProc(60, CMiscMeasureResultPOPPollingEvent))
    {   
        CScalerSetBit(_MEAS_HS_VS_HI_SEL_58, ~_BIT0, 0x00);
        CScalerRead(_MEAS_HS_PERIOD_H_52, 6, &pData[8], _AUTOINC);

        // Calculate measurement result
        ((WORD *)pData)[0] = ((pData[8] & 0x1f) << 8) | pData[9];
        ((WORD *)pData)[1] = ((pData[10] & 0x1f) << 8) | pData[11];
        ((WORD *)pData)[2] = ((pData[12] & 0xf0) << 4) | pData[13];
            
        if((((WORD *)pData)[0] >=  0x07ff) || (((WORD *)pData)[1] >= 0x07ff) || (((WORD *)pData)[0] == 0) || (((WORD *)pData)[1] == 0))
        {
            // The measurement result is out of range
            return _FALSE;
        }
        else
        {        
            // Store measurement results in global system variable
            stModeInfo.Polarity = (pData[10] & 0xc0) >> 6;
            stModeInfo.IHCount = ((WORD *) pData)[0];
            stModeInfo.IHFreq = (WORD) ((DWORD) _RTD_XTAL * 10 * 2 / stModeInfo.IHCount);
            stModeInfo.IHFreq = (stModeInfo.IHFreq >> 1) + (stModeInfo.IHFreq & 0x01);
            stModeInfo.IVTotal = ((WORD *) pData)[1];
            stModeInfo.IVFreq = (WORD)((DWORD) (stModeInfo.IHFreq) * 1000 * 2 / stModeInfo.IVTotal);
            stModeInfo.IVFreq = (stModeInfo.IVFreq >> 1) + (stModeInfo.IVFreq & 0x01);
            stModeInfo.IHSyncPulseCount = ((WORD *) pData)[2];
                   
            if((_GET_INPUT_SOURCE()==_SOURCE_DVI || _GET_INPUT_SOURCE() == _SOURCE_HDMI) && (ucCurrState==_SEARCH_STATE))   //for philips dvd player(dvp5965k) hdmi timing
                CTimerDelayXms(40);

            return _TRUE;
        }
    }
    else
        return _FALSE;      

}

//----------------------------------------------------------------------------------------------------
// Mode Detect Functions
//----------------------------------------------------------------------------------------------------
/**
* CModeDetect
* mode detect according to the input port
* @param <none>
* @return {TRUE if sync type is identified;FALSE if no sync}
*
*/
//--------------------------------------------------
// Description  : Mode detect process
// Input Value  : None
// Output Value : Return _TRUE if we get a stable mode
//--------------------------------------------------
bit CModeDetect(void)
{
    switch (_GET_INPUT_SOURCE()) 
    {
    case _SOURCE_VGA:
#if(_TMDS_SUPPORT == _ON)
    case _SOURCE_DVI:
#endif
#if(_YPBPR_SUPPORT == _ON)
    case _SOURCE_YPBPR:
#endif
#if(_YPBPR1_SUPPORT == _ON)
    case _SOURCE_YPBPR1:
#endif

    case _SOURCE_HDMI:
        if (CModeDetectCommon())
            return _TRUE;
        break;
    }
    return _FALSE;
}

/**
* CModeDetect
* Mode detect process for VGA and DVI
* first decide if mode is exist,then decide if the signal is stable
* if there is nosignal but it is stable,also return TRUE
* @param <none>
* @return {_TRUE if there is a stable mode;_FALSE if not}
*
*/
//--------------------------------------------------
// Description  : Mode detect process for VGA and DVI
// Input Value  : None
// Output Value : Return _TRUE if we get a stable mode
//--------------------------------------------------
bit CModeDetectCommon(void)
{
    BYTE modetemp = _MODE_NOSIGNAL;
    BYTE polaritytemp;
    WORD hcount, vtotal;
    
    if (CModeMeasureReady()) 
    {
        polaritytemp = stModeInfo.Polarity;
        hcount = stModeInfo.IHCount;
        vtotal = stModeInfo.IVTotal;
        
        // Get measure results and decide " modetemp = _MODE_NOSIGNAL/_MODE_NOSUPPORT/_MODE_EXIST " 
        if (CModeMeasureData()) 
        {
            CSyncModifyPolarityVGA();
            stModeInfo.ModeCurr = _MODE_NOSIGNAL;
            
            if (abs(stModeInfo.IHCount - hcount) <= 1)
                stModeInfo.IHCount = hcount;
            
            if (abs(stModeInfo.IVTotal - vtotal) <= 2)
                stModeInfo.IVTotal = vtotal;
            
            if ((stModeInfo.IHCount != hcount) ||(stModeInfo.IVTotal != vtotal) ||  (stModeInfo.Polarity != polaritytemp))
            {
                modetemp = _MODE_NOSIGNAL;
            }
            else 
            {
                if ((stModeInfo.IHFreq < Panel.HSyncMinFreq) ||(stModeInfo.IHFreq > Panel.HSyncMaxFreq) ||
                    (stModeInfo.IVFreq < Panel.VSyncMinFreq) ||(stModeInfo.IVFreq > Panel.VSyncMaxFreq))
                {
                    modetemp = _MODE_NOSUPPORT;
                }
                else 
                {
                    modetemp = _MODE_EXIST;
                }
            }
        }
        else 
        {
            modetemp = _MODE_NOSIGNAL;
        }
        // Wait mode stable and decide the mode type for current source
        if (modetemp != ucModeFound) 
        {
            ucModeFound = modetemp;
            ucEvent1 = _INACTIVE_COUNTDOWN_EVENT;
            CLR_MODESTABLE();
            CTimerCountDownEventProc(&ucEvent1, 3, CModeStableCountDownEvent);
            return _FALSE;
        }
        else 
        {
            CTimerCountDownEventProc(&ucEvent1, 3, CModeStableCountDownEvent);
            if (GET_MODESTABLE()) 
            {
                if (ucModeFound == _MODE_EXIST)
                {
                    CModeInterlaceCheck();//v003_interlace_check
                    stModeInfo.ModeCurr = CModeSearchDisplayMode();
                }
                else 
                {
                    stModeInfo.ModeCurr = ucModeFound;
                }
                ModeLimit(); 
                return _TRUE;
            }
            else 
            {
                return _FALSE;
            }
        }
    }
    else 
    {
        return _FALSE;
    }
}

/**
* CModeIsChange
* Check if mode is changed
* check the current mode compare with the previous mode
* @param <none>
* @return {_TRUE if mode is changed;_FALSE if not}
*
*/
bit CModeIsChange(void)
{
    BYTE polaritytemp;
    WORD hcount, vtotal;
    
    polaritytemp = stModeInfo.Polarity;
    hcount = stModeInfo.IHCount;
    vtotal = stModeInfo.IVTotal;
    
    if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
    {
        if(CScalerGetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, _BIT6 | _BIT5))
            return _TRUE;
    }
    //DebugPrintf("\nMMD.1.%c",0x20);   
    if(CModeMeasureData())
    {
        if(abs(stModeInfo.IHCount - hcount) <= 1)
            stModeInfo.IHCount = hcount;
        if(abs(stModeInfo.IVTotal - vtotal) <= 2)
            stModeInfo.IVTotal = vtotal;
        
        if((stModeInfo.IHCount != hcount) || (stModeInfo.IVTotal != vtotal) || (stModeInfo.Polarity != polaritytemp))
            return _TRUE;
        else
            return _FALSE;
    }
    else
        return _TRUE;
}

/**
* CModeSearchDisplayMode
* Search display mode according to the input source
* called only by CModeDetectCommon
* @param <none>
* @return {_TRUE if there is a stable mode;_FALSE if not}
*
*/
//--------------------------------------------------
// Description  : Search display mode process
// Input Value  : None
// Output Value : Mode number
//--------------------------------------------------
BYTE CModeSearchDisplayMode(void)
{
    BYTE modetemp;

    switch (_GET_INPUT_SOURCE())
    {
    case _SOURCE_VGA:
        modetemp = CModeSearchModeVGA();
        break;
        
#if(_YPBPR_SUPPORT == _ON)
    case _SOURCE_YPBPR:
        modetemp = CYPbPrSearchMode();
        break;
#endif
#if(_YPBPR1_SUPPORT == _ON)
    case _SOURCE_YPBPR1:
        modetemp = CYPbPrSearchMode();
        break;
#endif
        
#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
    case _SOURCE_DVI:
    case _SOURCE_HDMI:
        modetemp = CModeSearchModeDVI();
        break;
#endif
    }
    return modetemp;
}

/**
* CModeSearchModeVGA
* Search mode for VGA from preset mode to user mode
* called only by CModeSearchDisplayMode
* @param <none>
* @return {_TRUE if there is a stable mode;_FALSE if not}
*
*/
//--------------------------------------------------
// Description  : Search mode for VGA
// Input Value  : None
// Output Value : Mode number
//--------------------------------------------------
BYTE CModeSearchModeVGA(void)
{
    BYTE modecnt;
    
    SET_MODE_SEARCH_TYPE(_PRESET_MODE_TYPE);    ///!set preset mode type
    
    for (modecnt = 0; modecnt < _MAX_PRESET_MODE; modecnt++) 
    {
        if (CModeComparePresetModeVGA(modecnt))
        {

			//_MODE_1024x768_60HZ IHSyncPulseCount : 59
			//_MODE_1280x768_60HZ IHSyncPulseCount : 46
			//_MODE_1360x768_60HZ IHSyncPulseCount : 38
			
			if(modecnt == _MODE_1024x768_60HZ)
			{
			 	if(_ABS(stModeInfo.IHSyncPulseCount,46) < 3)
			 	{
					modecnt = _MODE_1280x768_60HZ;
			 	}
				
			 	if(_ABS(stModeInfo.IHSyncPulseCount,39) < 3)
			 	{
					modecnt = _MODE_1360x768_60HZ;
			 	}
			}
			//_MODE_1280x768_60HZ IHSyncPulseCount : 46
			//_MODE_1360x768_60HZ IHSyncPulseCount : 44

			  
			if(modecnt == _MODE_1280x768_60HZ)
			{
			 	if(_ABS(stModeInfo.IHSyncPulseCount,38) < 3)
			 	{
					modecnt = _MODE_1360x768_60HZ;
			 	}
                else if((_ABS(stModeInfo.IHSyncPulseCount,58) < 5) && (_ABS(stModeInfo.IVFreq,600) < 10))
			 	{
					modecnt = _MODE_1366x768_60HZ;
			 	}
			}
			//_MODE_1280x768_75Z IHSyncPulseCount : 36
			//_MODE_1360x768_75HZ IHSyncPulseCount : 38
						  
			if(modecnt == _MODE_1280x768_75HZ)
			{
			 	if(_ABS(stModeInfo.IHSyncPulseCount,40) < 3)
			 	{
					modecnt = _MODE_1360x768_60HZ;
			 	}
			 }
			//_MODE_1280x768_70HZ IHSyncPulseCount : 42
			//_MODE_1360x768_70HZ IHSyncPulseCount : 41
		 if(modecnt == _MODE_1280x768_70HZ)
			{

			 	if(_ABS(stModeInfo.IHSyncPulseCount,39) < 3)
			 	{
					modecnt = _MODE_1360x768_70HZ;
			 	}

			 }

		 

     		//_MODE_1600x1200_60HZ IHSyncPulseCount : 35
			//_MODE_1920x1200_60HZ IHSyncPulseCount : 31


			if(modecnt ==_MODE_1600x1200_60HZ)
			{	
				if(_ABS(stModeInfo.IHSyncPulseCount,26) < 3)
                    modecnt = _MODE_1920x1200_60HZ;
			}

			if(modecnt ==_MODE_1600x1200_60HZ)
			{
				if(_ABS(stModeInfo.IHSyncPulseCount,8) < 3)
                    modecnt = _MODE_1920x1200_60HZ_RB;	
			}
	
			if(modecnt ==_MODE_1920x1200_60HZ)
			{
				if(_ABS(stModeInfo.IHSyncPulseCount,8) < 3)
                    modecnt = _MODE_1920x1200_60HZ_RB;	
			}
			return modecnt;
		}
	}	
	modecnt = CModeSearchAcceptiveModeVGA();
	
    if ((modecnt == _MODE_NOSIGNAL) || (modecnt == _MODE_NOSUPPORT))
        return modecnt;                         ///!the returned number is the index in the preset mode

    SET_MODE_SEARCH_TYPE(_USER_MODE_TYPE);  ///!set user mode type
    modecnt = CModeCheckFIFOModeVGA(modecnt);   ///!the returned number is the index in the FIFO mode

    return modecnt;
}

/**
* CModeComparePresetModeVGA
* Compare the identified mode with preset VGA mode in preset table
* called only by CModeSearchDisplayMode
* @param <BYTE ucModeCnt> {mode number of preset mode in table}
* @return {_TRUE if the input mode number is correspondence to the input mode,_FALSE if not}
*
*/
//--------------------------------------------------
// Description  : Compare preset VGA mode
// Input Value  : Mode number
// Output Value : Return _TRUE if the input mode number is correspondence
//--------------------------------------------------
bit CModeComparePresetModeVGA(BYTE ucModeCnt)
{
    BYTE polarity, polaritytemp;
    
    polarity = (stModeInfo.Polarity & ~_BIT0) | ((bit)CScalerGetBit(_STABLE_PERIOD_H_50, _BIT6) ? 0x00 : _BIT0);
    
    if(abs(stModeInfo.IVFreq - tINPUTMODE_PRESET_TABLE[ucModeCnt].IVFreq) > tINPUTMODE_PRESET_TABLE[ucModeCnt].IVFreqTolerance)
        return _FALSE;
    
    if(abs(stModeInfo.IHFreq - tINPUTMODE_PRESET_TABLE[ucModeCnt].IHFreq) > tINPUTMODE_PRESET_TABLE[ucModeCnt].IHFreqTolerance)
        return _FALSE;
    
    if(abs(stModeInfo.IVTotal - tINPUTMODE_PRESET_TABLE[ucModeCnt].IVTotal) > 4)//v003
        return _FALSE;

    if ((bit) (polarity & _BIT0)) 
    {
        if ((bit) (polarity & _BIT1))
            polaritytemp = _SYNC_HP_VP;
        else
            polaritytemp = _SYNC_HP_VN;
    }
    else
    {
        if ((bit) (polarity & _BIT1))
            polaritytemp = _SYNC_HN_VP;
        else
            polaritytemp = _SYNC_HN_VN;
    }

    if ((polaritytemp & tINPUTMODE_PRESET_TABLE[ucModeCnt].PolarityFlag) ==0x00)
        return _FALSE;
    return _TRUE;
	
}

/**
* CModeSearchAcceptiveModeVGA
* decide an acceptive mode by comparing the identified mode with preset VGA mode in preset table
* do this when the input mode is not the very same preset mode in the table
* @param <none>
* @return {mode number of an acceptive mode in the table}
*
*/
//--------------------------------------------------
// Description  : Search an acceptive mode
// Input Value  : None
// Output Value : Mode number
//--------------------------------------------------
BYTE CModeSearchAcceptiveModeVGA(void)
{
    BYTE acceptivemode = _MODE_NOSUPPORT;
    
    //DebugPrintf("\n stModeInfo.IHFreq_H %x",(stModeInfo.IHFreq & 0xff00 )>>8);
    //DebugPrintf("\n stModeInfo.IHFreq_L %x",stModeInfo.IHFreq);       
    if (stModeInfo.IVTotal < 420) 
    {
    }
    else if (stModeInfo.IVTotal < 488)                 // 720x400 Mode : Vertical Line < 488
    {
        if (stModeInfo.IVFreq < 740)
            acceptivemode = _MODE_720x400_70HZ;
        else if (stModeInfo.IVFreq < 790)
        {
            if((BYTE)(GET_MODESELECT_TYPE())==0)
                acceptivemode = _MODE_640x400_70HZ;
            else
                acceptivemode = _MODE_720x400_70HZ;
        }
    }
    else if (stModeInfo.IVTotal < 610)            // 640x480 Mode : 488 <= Vertical Line < 610
    {
        if (stModeInfo.IVFreq < 640)
            acceptivemode = _MODE_640x480_60HZ;
        else if (stModeInfo.IVFreq < 690)
            acceptivemode = _MODE_640x480_66HZ;
        else if (stModeInfo.IVFreq < 740)
            acceptivemode = _MODE_640x480_72HZ;
        else if (stModeInfo.IVFreq < 790)
            acceptivemode = _MODE_640x480_75HZ;
    }
    else if (stModeInfo.IVTotal < 660)            // 800x600 Mode : 610 <= Vertical Line < 660
    {
        if (stModeInfo.IVFreq < 580)
            acceptivemode = _MODE_800x600_56HZ;
        else if (stModeInfo.IVFreq < 660)
            acceptivemode = _MODE_800x600_60HZ;
        else if (stModeInfo.IVFreq < 740)
            acceptivemode = _MODE_800x600_72HZ;
        else if (stModeInfo.IVFreq < 790)
            acceptivemode = _MODE_800x600_75HZ;
    }
    else if (stModeInfo.IVTotal < 732)            // 832x624 Mode : 660 <= Vertical Line < 732
    {
        if (stModeInfo.IVFreq < 740)
            acceptivemode = _MODE_800x600_72HZ;
        else
			acceptivemode = _MODE_832x624_75HZ;
    }
    else if (stModeInfo.IVTotal < 780)            // 1280x720 Mode : 732 <= Vertical Line < 780
    {
        if (stModeInfo.IVFreq < 740)
            acceptivemode = _MODE_1280x720_60HZ;
        else
            acceptivemode = _MODE_1280x720_75HZ;
    }
    else if (stModeInfo.IVTotal < 881)            // 1024x768 Mode : 780 <= Vertical Line < 881
    {
        if (stModeInfo.IVFreq < 650)
            //acceptivemode = _MODE_1024x768_60HZ;
            acceptivemode = _MODE_1280x768_60HZ;
        else if (stModeInfo.IVFreq < 730)
            acceptivemode = _MODE_1024x768_70HZ;
        else if (stModeInfo.IVFreq < 790)
            acceptivemode = _MODE_1024x768_75HZ;
    }
    else if (stModeInfo.IVTotal < 932)            // 1152x864/870 Mode : 881 <= Vertical Line < 932
    {
        if ((stModeInfo.IHFreq > 679) && (stModeInfo.IHFreq < 697))
            acceptivemode = _MODE_1152x870_75HZ;
        else 
        {
            if (stModeInfo.IVFreq < 650)
                acceptivemode = _MODE_1152x864_60HZ;
            else if (stModeInfo.IVFreq < 740)
                acceptivemode = _MODE_1152x864_70HZ;
            else if (stModeInfo.IVFreq < 790)
                acceptivemode = _MODE_1152x864_75HZ;
        }
    }
    else if (stModeInfo.IVTotal < 975)
    {
        if(stModeInfo.IVFreq < 660)
            acceptivemode = _MODE_1440x900_60HZ;
        else if(stModeInfo.IVFreq < 700)
			acceptivemode = _MODE_1152x900_66HZ;
        else if(stModeInfo.IVFreq < 760)
            acceptivemode = _MODE_1440x900_75HZ;
        else if(stModeInfo.IVFreq < 790)
            acceptivemode = _MODE_1152x900_76HZ;
    }
    else if (stModeInfo.IVTotal < 1040)
    {
        if (stModeInfo.IVFreq < 650)
            acceptivemode = _MODE_1280x960_60HZ;
        else
            acceptivemode = _MODE_1280x960_75HZ;
    }
    else if(stModeInfo.IVTotal < 1087)             // 1280x1024 Mode : 1040 <= Vertical Line < 1087
    {
        if (stModeInfo.IVFreq < 680)
        {           
            acceptivemode = _MODE_1280x1024_60HZ;//Confuse mode between 1280x1024_60HZ and 1680x1050_60HZ_BR
            
            //eric 20070626 mark by constomer       
            //if((stModeInfo.IHFreq > 630) &&(stModeInfo.IHFreq < 638)) // chroma #3603 RB1280x1024
            //  acceptivemode =_MODE_NOSUPPORT;     
            
            //acceptivemode = _MODE_1680x1050_60HZ_BR;
        } 
        else if (stModeInfo.IVFreq < 720)
            acceptivemode = _MODE_1280x1024_70HZ;
        else if (stModeInfo.IVFreq < 780)
            acceptivemode = _MODE_1280x1024_75HZ;
	}
    else if(stModeInfo.IVTotal < 1110)             // 1680x1050 Mode : 1087 <= Vertical Line < 1110
    {
        if(stModeInfo.IVFreq < 640)
            acceptivemode = _MODE_1680x1050_60HZ;
        else
            acceptivemode = _MODE_1680x1050_75HZ;
        
        //eric 20070626 mark by constomer
        //if((stModeInfo.IHFreq > 940) &&(stModeInfo.IHFreq < 948)) // chroma #3584,3558 
        //      acceptivemode = _MODE_NOSUPPORT;
    }
    else if(stModeInfo.IVTotal < 1200)             // 1920x1080 Mode : 1110 <= Vertical Line < 1200
    {
        acceptivemode = _MODE_1920x1080_60HZ;
        
        //eric 20070626 mark by constomer           
        //if((stModeInfo.IHFreq > 554) &&(stModeInfo.IHFreq < 562)) // chroma #3559,3585
        //  acceptivemode = _MODE_NOSUPPORT;
    }
    else if(stModeInfo.IVTotal < 1300)             // 1600x1200 Mode : 1200 <= Vertical Line < 1300
    {
        if(stModeInfo.IVFreq < 630)
            acceptivemode = _MODE_1600x1200_60HZ;//Confuse mode between 1600x1200 and 1920x1200
        else if(stModeInfo.IVFreq < 680)
            acceptivemode = _MODE_1600x1200_65HZ;
        else if(stModeInfo.IVFreq < 720)
            acceptivemode = _MODE_1600x1200_70HZ;
        else if(stModeInfo.IVFreq < 780)
            acceptivemode = _MODE_1600x1200_75HZ;
    }
    return acceptivemode;
}

/**
* CModeCheckFIFOModeVGA
* Check FIFO mode data if there is the same mode already in eeprom
* if not, then save the mode data to the eeprom and return the index of the FIFO data
* @param <BYTE ucModeCnt> {index returned from acceptive mode}
* @return {mode number of an acceptive mode in the table}
*
*/
//--------------------------------------------------
// Description  : Check FIFO mode for VGA
// Input Value  : Mode number
// Output Value : FIFO mode number
//--------------------------------------------------
BYTE CModeCheckFIFOModeVGA(BYTE ucModeCnt)
{
    BYTE cnt0, cnt1;
    StructModeUserFIFODataType stFIFOModeTemp;
    
    for (cnt0 = 0; cnt0 < 4; cnt0++) 
    {
        CEepromLoadUserFIFOModeData(cnt0, pData);
        
        for (cnt1 = 0; cnt1 < 4; cnt1++) 
        {
            if (CModeCompareFIFOModeVGA(cnt1, ucModeCnt) == _TRUE)
            {
                return (cnt0 * 4 + cnt1);
            }
        }
    }
    if (stSystemData.UserFIFOMode >= 15)
        stSystemData.UserFIFOMode = 0;
    else
        stSystemData.UserFIFOMode++;
        
    stFIFOModeTemp.ModeNum = ucModeCnt;
    stFIFOModeTemp.IHFreq = stModeInfo.IHFreq;
    stFIFOModeTemp.IVFreq = stModeInfo.IVFreq;
    CEepromSaveUserFIFOModeData(stFIFOModeTemp);
    
    stModeUserData.FirstAuto = 0;
    stModeUserData.HPosition = tINPUTMODE_PRESET_TABLE[ucModeCnt].IHStartPos;
    stModeUserData.VPosition = tINPUTMODE_PRESET_TABLE[ucModeCnt].IVStartPos;
    stModeUserData.Clock = tINPUTMODE_PRESET_TABLE[ucModeCnt].IHTotal;
    stModeUserData.Phase = 0;
    CEepromSaveModeData(stSystemData.UserFIFOMode);
    CEepromSaveSystemData();
    return stSystemData.UserFIFOMode;
}

/**
* CModeCompareFIFOModeVGA
* Compare mode in FIFO memory
* @param <BYTE ucNum> 		{mode index of the 16 mode}
* @param <BYTE ucModeCnt> 	{mode number of an acceptive mode in the table}
* @return {_TRUE if Vfreq and Hfreq are in range,_FALSE if not}
*
*/
//--------------------------------------------------
// Description  : Compare mode in FIFO memory
// Input Value  : Mode number and FIFO mode number
// Output Value : _TRUE if both are correspondence
//--------------------------------------------------
bit CModeCompareFIFOModeVGA(BYTE ucNum, BYTE ucModeCnt)
{
    StructModeUserFIFODataType stFIFOModeTemp;
    
    stFIFOModeTemp.ModeNum = (pData[ucNum * 4]);
    stFIFOModeTemp.IHFreq = ((WORD) (pData[ucNum * 4 + 1] & 0x0f) << 8) | pData[ucNum * 4 + 2];
    stFIFOModeTemp.IVFreq = ((WORD) (pData[ucNum * 4 + 1] & 0xf0) << 4) | pData[ucNum * 4 + 3];
    
    if (stFIFOModeTemp.ModeNum != ucModeCnt)
        return _FALSE;
    if (abs(stModeInfo.IVFreq - stFIFOModeTemp.IVFreq) >
        tINPUTMODE_PRESET_TABLE[ucModeCnt].IVFreqTolerance)
        return _FALSE;
    if (abs(stModeInfo.IHFreq - stFIFOModeTemp.IHFreq) >
        tINPUTMODE_PRESET_TABLE[ucModeCnt].IHFreqTolerance)
        return _FALSE;
    return _TRUE;
}

/**
* CModeSearchModeDVI
* Search mode in the preset table for DVI
* @param <BYTE ucModeCnt>   {mode number of the preset table}
* @return {mode number}
*
*/
//--------------------------------------------------
// Description  : Search mode for DVI
// Input Value  : None
// Output Value : Mode number
//--------------------------------------------------
#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
BYTE CModeSearchModeDVI(void)
{
    BYTE modecnt = 0;
    CScalerSetBit(_SYNC_SELECT_47, ~_BIT0, _BIT0);
    
    CAdjustSyncProcessorMeasureStart();
    
    if (CTimerPollingEventProc(60, CMiscModeMeasurePollingEvent)) 
    {
        CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT6, _BIT6);
        CScalerSetBit(_MEAS_HS_VS_HI_SEL_58, ~_BIT0, 0x00);
        CScalerRead(_MEAS_HS_PERIOD_H_52, 6, &pData[8], _AUTOINC);
        
        ((WORD *) pData)[0] = ((WORD) (pData[8] & 0x1f) << 8) | pData[9];
        ((WORD *) pData)[1] = ((WORD) (pData[10] & 0x1f) << 8) | pData[11];
        ((WORD *) pData)[2] = ((WORD) (pData[12] & 0xf0) << 4) | pData[13];
        
        if ((((WORD *) pData)[0] >= 0x0fff) || (((WORD *) pData)[1] >= 0x0fff) ||
            (((WORD *) pData)[0] == 0) ||   (((WORD *) pData)[1] == 0) ||   (bit) (pData[10] & _BIT5)) 
        {
            modecnt = _MODE_NOSUPPORT;
        }
        else 
        {
            // Save IH_TOTAL
            stModeInfo.IHTotal = ((WORD *) pData)[0] + 1;
            
            // Save input data enable width and height
            stModeInfo.IVHeight = ((WORD *) pData)[1] + 1;
            stModeInfo.IHWidth = ((WORD *) pData)[2] + 1;
            //DebugPrintf("\n stModeInfo.IHWidth=%x",(BYTE)(stModeInfo.IHWidth>>8));
            //DebugPrintf(",%x",(BYTE)(stModeInfo.IHWidth));
            //DebugPrintf("\n stModeInfo.IVHeight=%x",(BYTE)(stModeInfo.IVHeight>>8));
            //DebugPrintf(",%x",(BYTE)(stModeInfo.IVHeight));
            
#if(_HDMI_SUPPORT == _ON)
            // For width = 2880
            if((stModeInfo.IHWidth > 2048))
            {
                stModeInfo.IHWidth = stModeInfo.IHWidth / 2;
                stModeInfo.IHTotal = stModeInfo.IHTotal / 2;
                CScalerPageSelect(_PAGE2);
                CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, 0x50, 0xf0, 0x09);
                CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, 0x51, 0xfb, 0x00);
            }
#endif
            for (modecnt = 0; modecnt < _MAX_PRESET_MODE; modecnt++) 
            {
                if (CModeCompareModeDVI(modecnt)) 
                {
                    break;
                }
            }
        }
    }
    else 
    {
        CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT5, 0x00);
        modecnt = _MODE_NOSUPPORT;
    }
    CScalerSetBit(_SYNC_SELECT_47, ~_BIT0, 0x00);
    
    // We don't support input image less than 240 active lines
    if(stModeInfo.IVHeight < 240)//cyc:for minimum resolution 720x480i
        modecnt = _MODE_NOSUPPORT;
    // If no mode found, set to mode 0
    else if (modecnt >= _MAX_PRESET_MODE)
        modecnt = 0;
    
    // We don't support input image large than 2048 active pixel
    if((stModeInfo.IHWidth > 2048))
        modecnt = _MODE_NOSUPPORT;
    return modecnt;
}

/**
* CModeCompareModeDVI
* Compare mode in the preset table for DVI
* @param <BYTE ucModeCnt>   {mode number of the preset table}
* @return {_TRUE if the input mode number is correspondence to the input mode,_FALSE if not}
*
*/
//--------------------------------------------------
// Description  : Compare mode for DVI
// Input Value  : Mode number
// Output Value : Retrun _TRUE if it's correspondence
//--------------------------------------------------
bit CModeCompareModeDVI(BYTE ucModeCnt)
{
    if (stModeInfo.IHWidth != tINPUTMODE_PRESET_TABLE[ucModeCnt].IHWidth)
        return _FALSE;
    
    if (stModeInfo.IVHeight != tINPUTMODE_PRESET_TABLE[ucModeCnt].IVHeight)
        return _FALSE;
    
    if (abs(stModeInfo.IVFreq - tINPUTMODE_PRESET_TABLE[ucModeCnt].IVFreq) >
        tINPUTMODE_PRESET_TABLE[ucModeCnt].IVFreqTolerance)
        return _FALSE;
    
    return _TRUE;
}
#endif  // #if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

//----------------------------------------------------------------------------------------------------
// Mode Display Functions
//----------------------------------------------------------------------------------------------------
/**
* CModeDisplayActiveMode
* mode setup according to the source
* Display active mode process
* @param <none>
* @return {none}
*
*/
bit CModeDisplayActiveMode(void)
{
    stSystemData.Sharpness = 0x00;

    // added by ghyu
    //COsdFxDisableOsd();
    //CTimerReactiveTimerEvent(SEC(1), COsdFxEnableOsd);
    switch (_GET_INPUT_SOURCE())
    {
    case _SOURCE_VGA:
        return CModeSetupModeVGA();
        
#if(_YPBPR_SUPPORT == _ON)
    case _SOURCE_YPBPR:
        return CYPbPrSetupMode();
#endif
#if(_YPBPR1_SUPPORT == _ON)
    case _SOURCE_YPBPR1:
        return CYPbPrSetupMode();
#endif
        
#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
    case _SOURCE_DVI:
    case _SOURCE_HDMI:
        return CModeSetupModeDVI();
#endif
    }
    
}

/**
* CModeSetupModeVGA
* Setup VGA display
* Display active mode process
* @param <none>
* @return {none}
*
*/
//--------------------------------------------------
// Description  : Setup VGA mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit CModeSetupModeVGA(void)
{
    BYTE option = 0;
    
    //DebugPrintf("\n CModeSetupModeVGA %c",0x20);
    
    // Get information from mode table, such as IHTotal, IHStartPos, IHWidth, IVStartPos, IVHeight.
    CModeGetModeTableInfo();
    
    // Start up settings of VGA mode.
    CModeStartUpVGA();
    
    // Get scaling option, Capture window setup, Scaling setup, Display setup
    CModeSetupDisplay();
    
    // Load mode user data from eeprom
    CEepromLoadModeData(stModeInfo.ModeCurr);
    
    // Setup color processing
    CModeSetupColorProcess();
    
    // Setup color conversion
    CModeSetupColorConversion();//jerry20070605
    
    CAdjustBacklight();
    CAdjustAdcGainOffset();
    //080324
    //CAdjustAdcClock(stModeUserData.Clock);
    CAdjustAdcClock(stModeUserData.Clock, 0);
    //CAdjustPhase(stModeUserData.Phase);
    CAdjustHPosition();
    CModeModifyVTotal();
    CAdjustVPosition();
    CAdjustPeakingCoding();
    

    CScalerPageSelect(_PAGE0); 
    if(CGetSourcePortType(_GET_INPUT_SOURCE()) == _YPBPR_A0_PORT || CGetSourcePortType(_GET_INPUT_SOURCE()) == _DSUB_A0_PORT)
    {
        CScalerSetBit(_P0_ADC_CLAMP_CTRL0_D4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
        CTimerDelayXms(10);
        CScalerSetBit(_P0_ADC_DCR_CTRL_D3, ~_BIT4, 0x00);
    }
    else
    {
        CScalerSetBit(_P0_ADC_CLAMP_CTRL0_D4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
        CTimerDelayXms(10);
        CScalerSetBit(_P0_ADC_DCR_CTRL_D3, ~_BIT0, 0x00);
    }

    if ((_GET_INPUT_SOURCE() != _SOURCE_YPBPR)&&(_GET_INPUT_SOURCE() != _SOURCE_YPBPR1))
    {
        CScalerSetBit(_P0_ADC_RBG_CTRL_CE, 0x0F, (1 << 4) & 0xF0);
    }

    CScalerPageSelect(_PAGE1);
    CScalerSetByte(_P1_I_CODE_M_A1,0);
    CScalerSetByte(_P1_I_CODE_L_A2, 1);
    
    pData[0] = CFrameSyncDo();
    
    if (pData[0] == 2) 
    {
        return _FALSE;
    }
	
    CModeSetupEtcs(_FUNCTION_ENABLE);

    return _TRUE;
}

/**
* CModeSetupModeDVI
* Setup DVI display
* Display active mode process
* @param <none>
* @return {none}
*
*/
//--------------------------------------------------
// Description  : Setup mode DVI
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
bit CModeSetupModeDVI(void)
{
    BYTE option = 0;
    
    // Do initial settings of DVI mode.
    CModeStartUpDVI();

    //if(CHdmiFormatDetect())
    //  COsdFxDisableOsd();
    
    // Get scaling option, Capture window setup, Scaling setup, Display setup
    CModeSetupDisplay();    
    
    // Setup color processing
    CModeSetupColorProcess();
    
    // Setup color conversion
    CModeSetupColorConversion();//jerry20070605
    
    CAdjustBacklight();
    CAdjustPeakingCoding();
    CAdjustYpbprSaturation(GET_SATURATION());
    CAdjustYpbprhue(50);//GET_HUE());   
    
#ifdef _SRGB_ENLARGE_RANGE
	CScalerSetBit(_COLOR_CTRL_62,~(_BIT6|_BIT2),(_BIT6|_BIT2));   	//  Enable SRGB
#else //#ifdef _SRGB_ENLARGE_RANGE
	CScalerSetBit(_COLOR_CTRL_62,~_BIT2,_BIT2);   		//  Enable SRGB	
#endif //#ifdef _SRGB_ENLARGE_RANGE	
    CAccAdjust(_DISABLE);  // disable DCC mode
    
    //For Digital Interlace Mode Compensation
    CScalerPageSelect(_PAGE2);
    CScalerGetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_VCR_50, 1, pData, _NON_AUTOINC);
    
    if((pData[0] & 0x40) == 0x40)
    {
        CScalerSetBit(_SCALE_CTRL_32, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }
    
    
#if(_DE_INTERLACE_SUPPORT == _ON)   //v003_interlace_check
    //if(GET_INTERLACE_MODE(stSystemData.InputSource)){
    if(GET_INTERLACE_MODE())
    {
        if(stModeInfo.IHWidth <= 720)
        {   //for 480i & 576i
            //CScalerCodeW(tTMDS_RGB_TO_YUV);//eric 20070607
            CModeDeInterlaceSetting();
            CScalerPageSelect(_PAGE6);
            CScalerSetBit(_P6_PEAKING_ENABLE_C1, ~_BIT0, _BIT0);
        }
    }
#endif
    
    //forster modified 061123
    CAdjustInterlaceIVS2DVSDelay();
    
    pData[0] = CFrameSyncDo();
    //DebugPrintf("\n CFrameSyncDo=%x", pData[0]);
    
    if (pData[0] == 2) 
    {
        // ??? if(CHdmiFormatDetect())//741002 
        // ???  COsdFxEnableOsd();//741002
        return _FALSE;
    }
    
    CAdjustInterlaceIVS2DVSProtection();
    
#if(((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON)) && (_DVI_LONG_CABLE_SUPPORT == _ON))
    CAdjustTMDSCRCCheck();
#endif
    CAdjustTMDSCaptureCheck();
 #if(_HDMI_SUPPORT == _ON)
    CAdjustHdmiCbCr422(); //730702
    CModeSetupEtcs(_FUNCTION_DISABLE);
 #endif

#if  (_HDMI_HOT_PLUG_OPTION == _ENABLE)
    if(!CHdmiFormatDetect())//741002
    {
          //DebugPrintf("zhyftest plug\n",1);
          CAdjustBackgroundColor(0x00, 0x00, 0xff);     // set background blue screen   
          // force to background
          CScalerSetBit(_VDISP_CTRL_28, 0xff, _BIT5);   // Display output is forced to the background color
         // CModeHdmiHP();
         CModeHDMIChageDelay();
    
    }
#endif  

    return _TRUE;

}
#endif  // #if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

/**
* CModeSetupDisplay
* Setup capture window,scaling and display
* @param <BYTE ucPar> {enable/disable some bit of register}
* @return {none}
*
*/
//--------------------------------------------------
// Description  : Setup display
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSetupDisplay(void)
{
    BYTE option = 0;
    
    // Get scaling option
    option = CModeGetScaleSetting();    ///!decide capture size and display size
    
    // Capture window setup
    CModeSetCaptureWindow(option);      ///!set captur size
    
    // Scaling setup
    CModeSetScaling(option);            ///!set scaling factor
    
    // Display setup
    CModeSetDisplay(option);            ///!set display size
    
}

/**
* CModeSetupColorProcess
* Setup contrast and brightness
* @param <BYTE ucPar> {enable/disable some bit of register}
* @return {none}
*
*/
//--------------------------------------------------
// Description  : Setup contrast and brightness
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSetupColorProcess(void)
{
    CEepromLoadBriConData();
    CEepromLoadColorTempData();
    CAdjustBrightness();
    CAdjustContrast();
    CScalerSetByte(_COLOR_CTRL_62, 0x03);
    CScalerPageSelect(_PAGE7);
    CScalerSetByte(0xD8, 0x00);
}

/**
* CModeSetupColorConversion
* Setup color conversion(RGB->YUV & YUV->RGB)
* @param <BYTE ucPar> {enable/disable some bit of register}
* @return {none}
*
*/
//--------------------------------------------------
// Description  : Setup color conversion(RGB->YUV & YUV->RGB)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSetupColorConversion(void)//jerry20070605
{
    if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
    {
        //CScalerCodeW(tRGB2YUV601_TABLE_FOR_RGB_SOURCE);
        //CScalerCodeW(tYUV2RGB601_TABLE_FOR_RGB_SOURCE);
    }
    else if(bSourceVideo())
    {//AV/SV/TV
        CScalerCodeW(tRGB2YUV601_TABLE_FOR_NON_RGB_SOURCE);
        CScalerCodeW(tYUV2RGB601_TABLE_FOR_NON_RGB_SOURCE);
    }
    else if(_GET_INPUT_SOURCE() == _SOURCE_YPBPR||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1)
    {
        if(stModeInfo.ModeCurr < 4)
        {   //SD 720p below
            CScalerCodeW(tRGB2YUV601_TABLE_FOR_NON_RGB_SOURCE);
            CScalerCodeW(tYUV2RGB601_TABLE_FOR_NON_RGB_SOURCE);
        }
        else
        {                                       //HD 720p above
            CScalerCodeW(tRGB2YUV709_TABLE_FOR_NON_RGB_SOURCE);
            CScalerCodeW(tYUV2RGB709_TABLE_FOR_NON_RGB_SOURCE);
        }       
    }
#if(_HDMI_SUPPORT == _ON)
    else if(_GET_INPUT_SOURCE() == _SOURCE_DVI || _GET_INPUT_SOURCE() == _SOURCE_HDMI)
    {
        if(CHdmiFormatDetect())
        {   //HDMI timing
            CScalerPageSelect(_PAGE2);
            CScalerGetDataPortByte(_P2_HDMI_PSAP_CD, 0x07, 1, pData, _NON_AUTOINC);
            if(HDMI_ModeMap[pData[0]]<3)
            {   //SD 720p below
                CScalerGetDataPortByte(_P2_HDMI_PSAP_CD, 0x04, 1, pData, _NON_AUTOINC);
                if((pData[0] & 0x60) == 0x00)
                {//RGB          
                    CScalerCodeW(tRGB2YUV601_TABLE_FOR_RGB_SOURCE);
                    CScalerCodeW(tYUV2RGB601_TABLE_FOR_NON_RGB_SOURCE);
                }
                else
                {//YUV422 & YUV444
                    CScalerCodeW(tRGB2YUV601_TABLE_FOR_NON_RGB_SOURCE);
                    CScalerCodeW(tYUV2RGB601_TABLE_FOR_NON_RGB_SOURCE);
                }
            }
            else
            {//HD 720p above
                CScalerGetDataPortByte(_P2_HDMI_PSAP_CD, 0x04, 1, pData, _NON_AUTOINC);
                if((pData[0] & 0x60) == 0x00)
                {//RGB
                    CScalerCodeW(tRGB2YUV601_TABLE_FOR_RGB_SOURCE);
                    CScalerCodeW(tYUV2RGB601_TABLE_FOR_NON_RGB_SOURCE);     
                }
                else
                {//YUV422 & YUV444
                    CScalerCodeW(tRGB2YUV709_TABLE_FOR_NON_RGB_SOURCE);
                    CScalerCodeW(tYUV2RGB709_TABLE_FOR_NON_RGB_SOURCE);
                }
            }
        }
        else
        {   //DVI timing
            //CScalerCodeW(tRGB2YUV601_TABLE_FOR_RGB_SOURCE);
            //CScalerCodeW(tYUV2RGB601_TABLE_FOR_DVI_SOURCE);
        }       
    }
#endif  
}

/**
* CModeSetupEtcs
* Setup other setings for display
* @param <BYTE ucPar> {enable/disable some bit of register}
* @return {none}
*
*/
//--------------------------------------------------
// Description  : Setup other setings for display
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSetupEtcs(BYTE ucPar)
{

    CAdjustBackgroundColor(0x00,0x00,0x00);     //avoid 4:3 or letter aspect_ratio blue_background
    
    CMiscEnableDoubleBuffer();

    CAdjustDigitalFilter(_PHASE_ACCESS_PORT, _PHASE_THD_6, _DIV_VALUE_3, ucPar);
    CAdjustDigitalFilter(_YPBPR_ACCESS_PORT, _YPBPR_ENABLE, _DIV_VALUE_0, ucPar);
    CAdjustDigitalFilter(_NEG_SMEAR_ACCESS_PORT, _SMEAR_RING_THD_4, _DIV_VALUE_1, ucPar); //KEN 2005/09/23
    CAdjustDigitalFilter(_MISMATCH_ACCESS_PORT, _MISMATCH_THD_0, _DIV_VALUE_0, ucPar);
    CMiscClearStatusRegister();
}

/**
* CModeGetModeTableInfo
* Get mode information from mode table
* Display active mode process
* @param <none>
* @return {none}
*
*/
//--------------------------------------------------
// Description  : Get mode information from mode table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeGetModeTableInfo(void)
{
    BYTE modetemp;
    
#if 0//eric 0706
    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        modetemp = stModeInfo.ModeCurr;
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        CEepromLoadUserFIFOModeData((stModeInfo.ModeCurr / 4), pData);
        
        modetemp = pData[(stModeInfo.ModeCurr % 4) * 4];
    }
#else

		if (GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE) 
		{
			modetemp = stModeInfo.ModeCurr;
		}
		else if (GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE) 
		{
			CEepromLoadUserFIFOModeData((stModeInfo.ModeCurr / 4), pData);	///!decide current mode in which block of FIFO mode
			modetemp = pData[(stModeInfo.ModeCurr % 4) * 4];					///!decide the mode number of the mode we want
		}

#endif
    stModeInfo.IHTotal = tINPUTMODE_PRESET_TABLE[modetemp].IHTotal;
    stModeInfo.IHStartPos = tINPUTMODE_PRESET_TABLE[modetemp].IHStartPos;
    stModeInfo.IHWidth = tINPUTMODE_PRESET_TABLE[modetemp].IHWidth;
    stModeInfo.IVStartPos = tINPUTMODE_PRESET_TABLE[modetemp].IVStartPos;
    stModeInfo.IVHeight = tINPUTMODE_PRESET_TABLE[modetemp].IVHeight;
    CEepromLoadCenterModeData(stModeInfo.ModeCurr);
    // Test
    //stModeUserCenterData.CenterClock = stModeInfo.IHTotal;
    //stModeUserCenterData.CenterHPos = stModeInfo.IHStartPos;
    //stModeUserCenterData.CenterVPos = stModeInfo.IVStartPos;
}

/**
* CModeStartUpVGA
* Startup settings for VGA
* calculate pixelclock and set the ADC port
* called by CModeSetupModeVGA and CYPbPrSetupMode
* @param <none>
* @return {none}
*
*/
//--------------------------------------------------
// Description  : Startup settings for VGA
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeStartUpVGA(void)
{
    WORD pixelclock;
    
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    CScalerSetBit(_P2_TMDS_OUTPUT_CTRL_A6, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);
    CScalerSetBit(_P2_Z0_CALIBRATION_CTRL_AC, ~_BIT6, 0x00);
    
    // To imporve the FIFO efficiency only when input data rate is slow, and display data rate is high.
    CScalerSetBit(_VGIP_CTRL_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    
    // Calculate pixel clock rate (round to MHz)
    pixelclock  = (((DWORD)stModeInfo.IHFreq * (DWORD)stModeInfo.IHTotal) * 2 / (1000 * 10));
    pixelclock  = (pixelclock >> 1) + (pixelclock & 0x01);
    
    //cyc_delete    // To imporve the FIFO efficiency only when input data rate is slow, and display data rate is high.
    //cyc_delete    CScalerSetBit(_VGIP_CTRL_10, ~(_BIT3 | _BIT2 | _BIT1), 0x00);
    
    // ADC differential mode and Set ADC bandwidth to reduce high frequency noise
    CScalerPageSelect(_PAGE0);
    if(pixelclock < 38)
        CScalerSetBit(_P0_ADC_RBG_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);                    //75MHz
    else if(pixelclock < 68)
        CScalerSetBit(_P0_ADC_RBG_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));          //150MHz
    else if(pixelclock < 160)
        CScalerSetBit(_P0_ADC_RBG_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));          //300MHz
    else
        CScalerSetBit(_P0_ADC_RBG_CTRL_CE, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));  //500MHz
    
    CScalerPageSelect(_PAGE1);
    // Phase interpolation control load modified.   Marvin 0812
    if(pixelclock < 50)
        CScalerSetBit(_P1_PLL_PHASE_INTERPOLATION_B5, ~(_BIT7 | _BIT6), 0x00);
    else
        CScalerSetBit(_P1_PLL_PHASE_INTERPOLATION_B5, ~(_BIT7 | _BIT6), _BIT6);
    
    // Fine-tune R/G/B delay and enable the ADC frame-modulation
    CScalerPageSelect(_PAGE0);
    CScalerSetBit(_P0_ADC_RED_CTL_CF, ~(_BIT2 | _BIT1 | _BIT0), (_ADC_FINE_TUNE_DELAY_RED & 0x07));
    CScalerSetBit(_P0_ADC_GREEN_CTL_D0, ~(_BIT2 | _BIT1 | _BIT0), (_ADC_FINE_TUNE_DELAY_GREEN & 0x07));
    CScalerSetBit(_P0_ADC_BLUE_CTL_D1, ~(_BIT2 | _BIT1 | _BIT0), (_ADC_FINE_TUNE_DELAY_BLUE & 0x07));
    
    if(_GET_INPUT_SOURCE() == _SOURCE_YPBPR||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1)
        CScalerSetBit(_P0_ADC_CLAMP_CTRL1_D5,~(_BIT0 | _BIT1 | _BIT2 |_BIT3 | _BIT4 |_BIT5 ),
        ((_ADC1_INPUT_SWAP_RG << 2) | _ADC1_INPUT_SWAP_RG |(_ADC1_INPUT_SWAP_GB <<4)| (_ADC1_INPUT_SWAP_GB<<2)));   
    else //VGA  
        CScalerSetByte(_P0_ADC_CLAMP_CTRL1_D5, 0x00);
    //CScalerSetByte(_P0_ADC_CLAMP_CTRL1_D5, 0x00);
    CScalerSetByte(_YUV2RGB_CTRL_9C, 0x00);
    
    // HSYNC positive/negtive tracking
    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_PLL_DIV_CTRL_A0, ~_BIT7, 0x00);

}

/**
* CModeStartUpDVI
* Startup settings for DVI
* @param <none>
* @return {none}
*
*/
//--------------------------------------------------
// Description  : Startup settings for DVI
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
void CModeStartUpDVI(void)
{
    CScalerSetBit(_VGIP_HV_DELAY_1E, 0x0f, 0x00);
    
    CScalerSetBit(_VGIP_CTRL_10, ~(_BIT3 | _BIT2 | _BIT0), (_BIT2 | _BIT0));
    
    CTimerWaitForEvent(_EVENT_IVS);
    
    pData[0] = HIBYTE(stModeInfo.IHTotal - 2);
    pData[1] = 0x02;
    pData[2] = LOBYTE(stModeInfo.IHTotal - 2);
    pData[3] = HIBYTE(stModeInfo.IVTotal - 2);
    pData[4] = 0x02;
    pData[5] = LOBYTE(stModeInfo.IVTotal - 2);
    pData[6] = 0x00;
    pData[7] = 0x00;
    pData[8] = 0x00;
    pData[9] = 0x00;
    pData[10] = 0x03;
    pData[11] = 0x00;
    pData[12] = 0x00;
    pData[13] = 0x81;
    CScalerWrite(_H_BOUNDARY_H_70, 14, pData, _AUTOINC);
    
    if (CTimerPollingEventProc(255, CMiscAutoMeasurePollingEvent)) 
    {
        CScalerRead(_V_START_END_H_7E, 6, pData, _AUTOINC);
        
        // IDEN horizontal Start
        CScalerPageSelect(_PAGE2);
        //stModeInfo.IHStartPos = ((((WORD) pData[3] & 0xf0) << 4) | (WORD) pData[4]) - ((CScalerGetBit(_P2_POWER_ON_OFF_CTRL_A7, _BIT7) == _BIT7) ? 16 - 14 : 18 - 14);
        stModeInfo.IHStartPos = ((((WORD) pData[3] & 0xf0) << 4) | (WORD) pData[4]) - 4;
        
        // IDEN vertical Start
        stModeInfo.IVStartPos = (((WORD) pData[0] & 0xf0) << 4) | (WORD) pData[1];
    }
    else 
    {
        CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);
        CModeResetMode();
    }
}
#endif  // End of #if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))



//--------------------------------------------------
#if(_HDMI_SUPPORT == _ON)
void CCheckHDMIMode(void)
{
    ucHDMIMode = _HM_OTHER;


    // Decide V overscan
    if (stModeInfo.IVHeight == (480/2))
    {            
        ucHDMIMode = _HM_480I;
    }
    else if (stModeInfo.IVHeight == (576/2))
    {            
        ucHDMIMode = _HM_576I;
    }
    else if (stModeInfo.IVHeight == (480))
    {
        if(stModeInfo.IHWidth == 640)
        {
            ucHDMIMode = _HM_OTHER;
        }
        else
        {               
            ucHDMIMode = _HM_480P;
        }
    }
    else if (stModeInfo.IVHeight == (576))
    {            
        ucHDMIMode = _HM_576P;
    }
    else if (stModeInfo.IVHeight == (720))
    {            
        ucHDMIMode = _HM_720P;
    }
    else if (stModeInfo.IVHeight == (1080/2))
    {
        ucHDMIMode = _HM_1080I;
    }
    else if (stModeInfo.IVHeight == (1080))
    {            
        ucHDMIMode = _HM_1080P;
    }
    else
    {
        ucHDMIMode = _HM_OTHER;
    }

    // Decide H overscan
    if (stModeInfo.IHWidth == (960))
    {
        ucHDMIMode = _HM_1080P;
    }
    else if (stModeInfo.IHWidth == (1280))
    {
        if(stModeInfo.IVHeight == 1024 || stModeInfo.IVHeight == 768)
        {
            ucHDMIMode = _HM_OTHER;
        }

    }
    else if (stModeInfo.IHWidth == (1440))
    {

        if(stModeInfo.IVHeight == 900 || stModeInfo.IVHeight == 1050)
        {
            ucHDMIMode = _HM_OTHER;
        }
    }
    else if (stModeInfo.IHWidth == (1920))
    {
        if(stModeInfo.IVHeight == 1200)
        {
            ucHDMIMode = _HM_OTHER;
        }
    }
}
#endif // #if(_HDMI_SUPPORT == _ON)   

//--------------------------------------------------
// Description  : Get scaling information
// Input Value  : None
// Output Value : Scaling information
//--------------------------------------------------
BYTE CModeGetScaleSetting(void)
{
    BYTE    option = 0;
#if(_HDMI_SUPPORT == _ON)
    BYTE    OverScan_HWidth,OverScan_VHeight;
#endif
    
#if(_DISP_INFO_BY_MODE == _ON)
    
    BYTE modetemp;
    
    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        modetemp = stModeInfo.ModeCurr;
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        CEepromLoadUserFIFOModeData((stModeInfo.ModeCurr / 4), pData);
        
        modetemp = pData[(stModeInfo.ModeCurr % 4) * 4];
    }
    stDisplayInfo.DHTotal = tDHTOTAL_PRESET_TABLE[modetemp];
    stDisplayInfo.DHWidth = Panel.DHWidth;
    stDisplayInfo.DVHeight= Panel.DVHeight;
        
    stDisplayInfo.DVStartPos = Panel.DVStartPos; 
    if (stDisplayInfo.DVStartPos < 6)
        stDisplayInfo.DVStartPos = 6;
    
#else//(_DISP_INFO_BY_MODE == _ON)
    stDisplayInfo.DHWidth   = CCalcPanelWdith();//Panel.DHWidth;
    //stDisplayInfo.DHWidth = Panel.DHWidth;
    stDisplayInfo.DVHeight = Panel.DVHeight;
    stDisplayInfo.DHTotal = Panel.DHTotal;
    
    // Modify Display Vertical Start Position   //CFrameSyncModifyDVStartPos
    
    stDisplayInfo.DVStartPos = (DWORD)35 * 2 * stDisplayInfo.DVHeight / stModeInfo.IVHeight / 10;
    stDisplayInfo.DVStartPos = ((stDisplayInfo.DVStartPos >> 1) + (stDisplayInfo.DVStartPos & 0x01));
    if (_GET_INPUT_SOURCE() !=_SOURCE_DVI && _GET_INPUT_SOURCE() !=_SOURCE_HDMI)
        stDisplayInfo.DVStartPos = Panel.DVStartPos;   //Ming-Yen
    
    if (stDisplayInfo.DVStartPos < 6)
        stDisplayInfo.DVStartPos = 6;
    
    
#endif
    
    
    
#if(_HDMI_SUPPORT == _ON)
	if((_GET_INPUT_SOURCE() ==_SOURCE_DVI || 
	    _GET_INPUT_SOURCE() ==_SOURCE_HDMI) && 
	   CHdmiFormatDetect())//HDMI only	
    {
        //Overscan Area refer by Polaroid.
        HDMI_H_Width = stModeInfo.IHWidth;
        HDMI_V_Height = stModeInfo.IVHeight;

        CCheckHDMIMode();
        
#if(_HDMI_OVERSCAN_PERCENT==_OVERSCAN_PERCENT_93_75)
        
        CScalerPageSelect(_PAGE2);
        CScalerGetDataPortByte(_P2_HDMI_PSAP_CD, 0x07, 1, pData, _NON_AUTOINC);
        if(0)//pData[0] == 20) // EricLee for GIEC DVD HDMI full display
        {//1920x1080ix50Hz
            OverScan_HWidth = (BYTE)(stModeInfo.IHWidth/32);    //Horizontal: 96.87%
            OverScan_VHeight= (BYTE)(stModeInfo.IVHeight/32);   //Vertical: 96.87%   
        }   
        else
        {
            OverScan_HWidth = (BYTE)(stModeInfo.IHWidth/16);    //Horizontal: 93.75%
            OverScan_VHeight= (BYTE)(stModeInfo.IVHeight/16);   //Vertical: 93.75%   //forster modified 061102 for HDMI 576P @ 1280x1024 panel frame sync problem
        }           
#elif(_HDMI_OVERSCAN_PERCENT==_OVERSCAN_PERCENT_95_00)
        OverScan_HWidth = (BYTE)(stModeInfo.IHWidth/20);        //Horizontal: 95.00%
        OverScan_VHeight= (BYTE)(stModeInfo.IVHeight/20);       //Vertical: 95.00%
#else
        OverScan_HWidth = 0;                                                            //Horizontal: 100.00%
        OverScan_VHeight= 0;                                                            //Vertical: 100.00%
#endif
        stModeInfo.IHWidth = stModeInfo.IHWidth - OverScan_HWidth; 
        if(stModeInfo.IHWidth % 8)
            stModeInfo.IHWidth = ((stModeInfo.IHWidth + 4) >> 3) << 3;
        stModeInfo.IHStartPos = stModeInfo.IHStartPos + OverScan_HWidth/2;
        stModeInfo.IVHeight = stModeInfo.IVHeight - OverScan_VHeight;
        stModeInfo.IVStartPos = stModeInfo.IVStartPos + OverScan_VHeight/2;
    }
#endif
    
    if (stModeInfo.IVHeight < stDisplayInfo.DVHeight)
        option |= _BIT0;    // bit 0 : V scale-up
    if (stModeInfo.IVHeight > stDisplayInfo.DVHeight)
        option |= _BIT1;    // bit 1 : V scale-down
    if (stModeInfo.IHWidth < stDisplayInfo.DHWidth)
        option |= _BIT2;    // bit 2 : H scale-up
    if (stModeInfo.IHWidth > stDisplayInfo.DHWidth)
        option |= _BIT3;    // bit 3 : H scale-down
    
    return option;
}

//--------------------------------------------------
// Description  : Set capture window
// Input Value  : Scaling information
// Output Value : None
//--------------------------------------------------
void CModeSetCaptureWindow(BYTE ucOption)
{
    WORD ustemp;
    if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
        ucHStartBias = 100;
    else if((_GET_INPUT_SOURCE() == _SOURCE_DVI) || (_GET_INPUT_SOURCE() == _SOURCE_HDMI))
        ucHStartBias = 50;
    else
        ucHStartBias = 100;
    
    ucVStartBias = 0;
    ucVStartBias = CAdjustIVS2DVSDelay(ucOption);
    
    if (ucVStartBias > stModeInfo.IVStartPos)
        ucVStartBias = stModeInfo.IVStartPos;
    
    // Set capture window
    ustemp = stModeInfo.IHStartPos + _CAPTURE_HDELAY - (ucHStartBias + _PROGRAM_HDELAY);
    
    CScalerSetBit(_IPH_ACT_STA_H_14, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(ustemp) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPH_ACT_STA_L_15, LOBYTE(ustemp));
    CScalerSetBit(_IPH_ACT_WID_H_16, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(stModeInfo.IHWidth) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPH_ACT_WID_L_17, LOBYTE(stModeInfo.IHWidth));
    
    ustemp = stModeInfo.IVStartPos - (ucVStartBias + _PROGRAM_VDELAY);
    
    CScalerSetBit(_IPV_ACT_STA_H_18, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(ustemp) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPV_ACT_STA_L_19, LOBYTE(ustemp));
    CScalerSetBit(_IPV_ACT_LEN_H_1A, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(stModeInfo.IVHeight) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPV_ACT_LEN_L_1B, LOBYTE(stModeInfo.IVHeight));
    
    // Set internal input H sync delay
    CAdjustIHSDelay(ucHStartBias + _PROGRAM_HDELAY);
    
    // Set internal input V sync delay
    CAdjustIVSDelay(ucVStartBias + _PROGRAM_VDELAY);
}

//--------------------------------------------------
// Description  : Set scaling factor settings
// Input Value  : Scaling information
// Output Value : None
//--------------------------------------------------
void CModeSetScaling(BYTE ucOption)
{
    BYTE Hini = 0;
    BYTE Vini = 0;
                      
    CScalerSetBit(_P6_UZD_CTRL0_E3, ~_BIT4, 0x00); //Disable 2-tap   EricLee add for VGA change to AV/YPbPr position issue

    // Set window size before scale up
    if(ucOption & _BIT3)
    {
        // H scale-down
        pData[0] = (BYTE)((stDisplayInfo.DHWidth >> 4) & 0x70);
        pData[1] = LOBYTE(stDisplayInfo.DHWidth);
    }
    else
    {
        // No H scale-down
        pData[0] = (BYTE)((stModeInfo.IHWidth >> 4) & 0x70);
        pData[1] = LOBYTE(stModeInfo.IHWidth);
    }
    
    if(ucOption & _BIT1)
    {
        // V scale-down
        pData[0] = pData[0] | (HIBYTE(stDisplayInfo.DVHeight) & 0x07);
        pData[2] = LOBYTE(stDisplayInfo.DVHeight);
    }
    else
    {
        // No V scale-down
        pData[0] = pData[0] | (HIBYTE(stModeInfo.IVHeight) & 0x07);
        pData[2] = LOBYTE(stModeInfo.IVHeight);
    }
    
    CScalerSetByte(_FIFO_ACCESS_PORT_30, _FIFO_DWRWL_H_BSU_00);
    CScalerWrite(_FIFO_DATA_PORT_31, 3, pData, _NON_AUTOINC);
    
    // Write coefficient for sharpness for scale-up 
    CAdjustSharpnessForScaleUp();
    // Write sharpness coefficient for scale-down 
    CAdjustSharpnessForScaleDown();
    // Config scaling
    CScalerPageSelect(_PAGE6); 
    if(ucOption & _BIT1)
        CScalerSetBit(_P6_UZD_CTRL0_E3, ~_BIT1, _BIT1);          // Turn on V scale-down
    else
        CScalerSetBit(_P6_UZD_CTRL0_E3, ~_BIT1, 0x00);           // Turn off V scale-down
    
    if(ucOption & _BIT3)
        CScalerSetBit(_P6_UZD_CTRL0_E3, ~_BIT0, _BIT0);          // Turn on H scale-down
    else
        CScalerSetBit(_P6_UZD_CTRL0_E3, ~_BIT0, 0x00);           // Turn off H scale-down
    
    if(ucOption & _BIT0)
        CScalerSetBit(_SCALE_CTRL_32, ~_BIT1, _BIT1);               // Turn on V scale-up
    else
        CScalerSetBit(_SCALE_CTRL_32, ~_BIT1, 0x00);                // Turn off V scale-up
    
    if(ucOption & _BIT2)
        CScalerSetBit(_SCALE_CTRL_32, ~_BIT0, _BIT0);               // Turn on H scale-up
    else
        CScalerSetBit(_SCALE_CTRL_32, ~_BIT0, 0x00);                // Turn off H scale-up
    
    // Set scale-down coefficient
    if(ucOption & _BIT3)    // H scale-down
    {
        // Data[12~15]
        ((DWORD *)pData)[3] = (DWORD)1 * 1048576 * stModeInfo.IHWidth;
        ((DWORD *)pData)[3] = (((DWORD *)pData)[3] % stDisplayInfo.DHWidth) ? ((((DWORD *)pData)[3] / stDisplayInfo.DHWidth) + 1) : (((DWORD *)pData)[3] / stDisplayInfo.DHWidth);
        Hini = 255 - ((stModeInfo.IHWidth *255)/stDisplayInfo.DHWidth);

        // H scale-down factor
        pData[0] = ((((DWORD *)pData)[3] >> 16) & 0xff);
        pData[1] = ((((DWORD *)pData)[3] >> 8) & 0xff);
        pData[2] = ((((DWORD *)pData)[3]) & 0xff);
        ///CScalerSetBit(_IPH_PORCH_NUM_H_1F, ~_BIT3, _BIT3); //Ming-Yen
        CScalerSetBit(_P6_UZD_CTRL1_E4, ~(_BIT3 | _BIT2), _BIT3); //For vertical UZD, H->V
        
        if(stModeInfo.IHWidth >= stDisplayInfo.DHWidth)
        {
            if(stDisplayInfo.DHWidth > 960)
                CScalerSetBit(_P6_UZD_CTRL0_E3, ~_BIT4, _BIT4); //Enable 2-tap
        }
        else
        {
            if(stModeInfo.IHWidth > 960)
                CScalerSetBit(_P6_UZD_CTRL0_E3, ~_BIT4, _BIT4); //Enable 2-tap
        }
    }
    else
    {
        pData[0] = 0x00;
        pData[1] = 0x00;
        pData[2] = 0x00;
    }
    
    if(ucOption & _BIT1)    // V scale-down
    {
        ((DWORD *)pData)[3] = (DWORD)1048576 * stModeInfo.IVHeight / stDisplayInfo.DVHeight;
        Vini = 255 - ((stModeInfo.IVHeight *255)/stDisplayInfo.DVHeight);

        // V scale-down factor
        pData[3] = ((((DWORD *)pData)[3] >> 16) & 0xff);
        pData[4] = ((((DWORD *)pData)[3] >> 8) & 0xff);
        pData[5] = ((((DWORD *)pData)[3]) & 0xff);
        CScalerSetBit(_P6_UZD_CTRL0_E3, ~_BIT7, 0x00);    // Diable Video scale-down compensation
        
        if(stModeInfo.IHWidth >= stDisplayInfo.DHWidth)
        {
            if(stDisplayInfo.DHWidth > 960)
                CScalerSetBit(_P6_UZD_CTRL0_E3, ~_BIT4, _BIT4); //Enable 2-tap
        }
        else
        {
            if(stModeInfo.IHWidth > 960)
                CScalerSetBit(_P6_UZD_CTRL0_E3, ~_BIT4, _BIT4); //Enable 2-tap
        } 
        CScalerSetBit(_P6_UZD_CTRL1_E4, ~(_BIT3 | _BIT2), _BIT3); //For vertical UZD, H->V
    }
    else 
    {
        pData[3] = 0x00;
        pData[4] = 0x00;
        pData[5] = 0x00;
        CScalerSetBit(_P6_UZD_CTRL0_E3, ~_BIT7, 0x00);    // Disable Video scale-down compensation
    }
    
    CTimerWaitForEvent(_EVENT_IEN_STOP);
    
    CScalerWrite(_P6_UZD_SCALE_HOR_FACTOR_H_E5, 6, pData, _AUTOINC);
    
    pData[0] = 0x00;
    pData[1] = 0x00;
    pData[2] = 0x00;
    pData[3] = 0x00;
    pData[4] = (BYTE)(stDisplayInfo.DHWidth >> 8);
    pData[5] = (BYTE)stDisplayInfo.DHWidth;
    pData[6] = Hini;//0x00; 
    pData[7] = Vini;//0x00;
    
    CScalerWrite(_P6_UZD_HOR_DELTA1_H_EB, 8, pData, _AUTOINC);
    
#if(_NONLINEAR_SCALING)
    CScalerDisableNonlinearScaleDown();
#endif
    
    // Set scale-up coefficient
    if(ucOption & _BIT2)    // H scale-up
    {
        // Data[12~15]
        ((DWORD *)pData)[3] = (DWORD)2 * 1048576 * stModeInfo.IHWidth / stDisplayInfo.DHWidth;
        ((DWORD *)pData)[3] = (((DWORD *)pData)[3] >> 1) + (((DWORD *)pData)[3] & 0x01);
        
        pData[0] = ((((DWORD *)pData)[3] >> 16) & 0x0f);
        pData[1] = ((((DWORD *)pData)[3] >> 8) & 0xff);
        pData[2] = ((((DWORD *)pData)[3]) & 0xff);
    }
    else {
        pData[0] = 0x0f;
        pData[1] = 0xff;
        pData[2] = 0xff;
    }
    
    if(ucOption & _BIT0)    // V scale-up
    {
        // Data[12~15]
        ((DWORD *)pData)[3] = (DWORD)2 * 1048576 * stModeInfo.IVHeight / stDisplayInfo.DVHeight;
        ((DWORD *)pData)[3] = (((DWORD *)pData)[3] >> 1) + (((DWORD *)pData)[3] & 0x01);
        
        pData[3] = ((((DWORD *)pData)[3] >> 16) & 0x0f);
        pData[4] = ((((DWORD *)pData)[3] >> 8) & 0xff);
        pData[5] = ((((DWORD *)pData)[3]) & 0xff);
    }
    else
    {
        pData[3] = 0x0f;
        pData[4] = 0xff;
        pData[5] = 0xff;
    }
    
    CScalerSetByte(_SU_ACCESS_PORT_33, 0x80);
    CScalerWrite(_SU_DATA_PORT_34, 6, pData, _NON_AUTOINC);
    CScalerSetByte(_SU_ACCESS_PORT_33, 0x00);
    CScalerPageSelect(_PAGE0);
    
#if(_NONLINEAR_SCALING)
    CScalerDisableNonlinearScaleUp();
    CScalerNonlinearScaleUp(ucOption);
    CScalerNonlinearScaleDown(ucOption);
#endif
}

//--------------------------------------------------
// Description  : Set display
// Input Value  : Scaling information
// Output Value : None
//--------------------------------------------------
void CModeSetDisplay(BYTE ucOption)
{
    // Disable spread spectrum
    CAdjustSpreadSpectrumRange(0);
    
    // Calculate and set display clock frequency
    ((DWORD *) pData)[0] = (DWORD)(stDisplayInfo.DHTotal) * (DWORD)stModeInfo.IHFreq * (DWORD)(stDisplayInfo.DVHeight) / stModeInfo.IVHeight / 10;
    
    CAdjustDPLL(((DWORD *) pData)[0], _DPLL_N_CODE);
    
    // Set DH_TOTAL
    pData[0] = (HIBYTE(stDisplayInfo.DHTotal - 4) & 0x0f);
    pData[1] = (LOBYTE(stDisplayInfo.DHTotal - 4));
    CScalerSetByte(_DISP_ACCESS_PORT_2A, _DISP_DH_TOTAL_H_00);
    CScalerWrite(_DISP_DATA_PORT_2B, 2, pData, _NON_AUTOINC);
    
    // Calculate DV_TOTAL setting for watchdog
    ((WORD *) pData)[2] = (DWORD) stModeInfo.IVTotal * (DWORD) (stDisplayInfo.DVHeight) / stModeInfo.IVHeight + 64;
    pData[0] = (HIBYTE(((WORD *) pData)[2]) & 0x0f);
    pData[1] = (LOBYTE(((WORD *) pData)[2]));
    CScalerSetByte(_DISP_ACCESS_PORT_2A, _DISP_DV_TOTAL_H_0B);
    CScalerWrite(_DISP_DATA_PORT_2B, 2, pData, _NON_AUTOINC);
    

    // Display horizontal start/end
    ((WORD *)pData)[4] = CCalcPanelDHSta();
    ((WORD *)pData)[5] = CCalcPanelDHEnd(); 
    //((WORD *)pData)[4] = (Panel.DHWidth - stDisplayInfo.DHWidth) / 2 + Panel.DHStartPos;
    //((WORD *)pData)[5] = ((WORD *)pData)[4] + stDisplayInfo.DHWidth;
    
    pData[0] = HIBYTE(((WORD *)pData)[4]);
    pData[1] = LOBYTE(((WORD *)pData)[4]);
    pData[2] = HIBYTE(((WORD *)pData)[5]);
    pData[3] = LOBYTE(((WORD *)pData)[5]);
    
    CScalerSetByte(_DISP_ACCESS_PORT_2A, _DISP_DH_ACT_STA_H_05);
    CScalerWrite(_DISP_DATA_PORT_2B, 4, pData, _NON_AUTOINC);
    
    // Display vertical start/end
    ((WORD *)pData)[4] = stDisplayInfo.DVStartPos - ((Panel.DVHeight - stDisplayInfo.DVHeight) / 2);
    ((WORD *)pData)[5] = stDisplayInfo.DVStartPos;
    ((WORD *)pData)[6] = ((WORD *)pData)[5] + stDisplayInfo.DVHeight;
    ((WORD *)pData)[7] = ((WORD *)pData)[4] + Panel.DVHeight;
    
    pData[0] = HIBYTE(((WORD *)pData)[4]);
    pData[1] = LOBYTE(((WORD *)pData)[4]);
    pData[2] = HIBYTE(((WORD *)pData)[5]);
    pData[3] = LOBYTE(((WORD *)pData)[5]);
    pData[4] = HIBYTE(((WORD *)pData)[6]);
    pData[5] = LOBYTE(((WORD *)pData)[6]);
    pData[6] = HIBYTE(((WORD *)pData)[7]);
    pData[7] = LOBYTE(((WORD *)pData)[7]);
    CScalerSetByte(_DISP_ACCESS_PORT_2A, (0x80 | _DISP_DV_BKGD_STA_H_0E));
    CScalerWrite(_DISP_DATA_PORT_2B, 8, pData, _NON_AUTOINC);
    CScalerSetByte(_DISP_ACCESS_PORT_2A, 0x00);//cyc_test
    
    // Turn off full-line buffer
    CScalerSetBit(_SCALE_CTRL_32, ~_BIT4, 0x00);
    
    CAdjustIVS2DVSDelay(ucOption);
    
    //CTimerWaitForEvent(_EVENT_DEN_STOP);
    // Enable display timing
    
    CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5 | _BIT3 | _BIT1 | _BIT0), (_BIT5 | _BIT3 | _BIT1 | _BIT0));
    CMiscClearStatusRegister();
}

//--------------------------------------------------
// Description  : Modify IVTotal
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeModifyVTotal(void)
{
/*
BYTE ucTemp;

        // Force to stop auto-tracking function
        CScalerSetByte(_AUTO_ADJ_CTRL_7F, 0x00);
        
          CScalerSetByte(_STATUS0_01, 0x00);   // Clear Status
          
            ucTemp  = 8;             // Tracking timeout 80ms
            do
            {
            CTimerDelayXms(10);
            CScalerRead(_STATUS0_01, 1, pData, _NON_AUTOINC);  // Read Status
            
              // V101C corrected
              if(pData[0] & 0x80)
              CScalerSetByte(_STATUS0_01, 0x00);   // Clear Status
              else
              break;
              }
              while(--ucTemp);
              
                // Measure actual number of scan line in each frame
                CScalerCodeW(tMEASURE_IVS);
                
                  ucTemp  = 50;    // Tracking timeout 50ms
                  do
                  {
                  CTimerDelayXms(1);
                  CScalerRead(_AUTO_ADJ_CTRL_7F, 0x01, pData, _NON_AUTOINC);
                  }
                  while((pData[0] & 0x01) && (--ucTemp));
                  
                    CScalerSetByte(_AUTO_ADJ_CTRL_7F, 0x00);
                    
                      if(ucTemp)
                      {
                      CScalerRead(_VER_START_80, 0x04, pData, _AUTOINC);
                      pData[0]  = pData[3] & 0x0f;
                      pData[1]  = pData[2];
                      
                        stModeInfo.IVTotal   = stModeInfo.IVTotal < ((WORD *)pData)[0] ? ((WORD *)pData)[0] : stModeInfo.IVTotal;
                        }
    */
}

//----------------------------------------------------------------------------------------------------
// Other Mode Functions
//----------------------------------------------------------------------------------------------------
/**
* CModeResetMode
* Reset mode
* clear some display flags and registers and go back to  _SEARCH_STATE
* @param <none>
* @return {none}
*
*/
void CModeResetMode(void)
{   
    if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
    {
       ucTVSyncFailCount++;
       if(ucTVSyncFailCount < 100)
          return;
    }

    bfBurnIn = 0;
    ucTVSyncFailCount = 0;
    CLR_OSD_READYFORDISPLAY();

    CAdjustBackgroundColor(0x00, 0x00, 0x00);
    // force to background
    CScalerSetBit(_VDISP_CTRL_28, ~(_BIT3), _BIT5); // Display output is forced to the background color

#if (_HDMI_SUPPORT == _ON)

  #if(_OSD_TYPE == _OSD003)
    #if (_CHANGE_SOURCE_METHOD == _CHANGE_SOURCE_METHOD_0)
    if ((ucOsdState < _MI_SOURCE_VGA || ucOsdState > _MI_SOURCE_TV) && 
         ((_GET_INPUT_SOURCE() != _SOURCE_HDMI) && (_GET_INPUT_SOURCE() != _SOURCE_DVI)))
    #endif
  #else
    if(_GET_INPUT_SOURCE() != _SOURCE_HDMI && _GET_INPUT_SOURCE() != _SOURCE_DVI)
  #endif
    {
        CPowerLightPowerOff();  
    }

    if(CHdmiFormatDetect())//Input source is the HDMI format.
    {
        CScalerPageSelect(_PAGE2);
        CAdjustDisableHDMIWatchDog(_WD_AUDIO_FOR_TMDS_CLOCK | _WD_PACKET_VARIATION);//731301
        CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_VCR_50, 0xf0, 0x00);
        CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AOCR_62, 0x00);//Disable SPDIF/I2S Output
        SET_VIDEOMODECHANGE();
    } /*
    CScalerPageSelect(_PAGE2);
    CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_SCR_00, ~(_BIT3 | _BIT2), _BIT3);//Set HDMI/DVI switch mode(manual,DVI)
    */
    CLR_HDMIINPUT();
    CLR_HDMISTABLE();
    ucHdmiAVMuteCnt = 0;
    if(_GET_INPUT_SOURCE() == _SOURCE_HDMI || _GET_INPUT_SOURCE() == _SOURCE_DVI)
    {
        CPowerPanelOn();
        ucHDMIMode = _HM_OTHER;
    }

#else
    CPowerLightPowerOff();
#endif

    
#if((_YPBPR_SUPPORT||_YPBPR1_SUPPORT) && _YPBPR_NEW_SYNC_DETECT == _ON)        // Set SOG0,SOG1 sync level to default 320mv
    if (_GET_INPUT_SOURCE() == _SOURCE_YPBPR||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1)
    {
        if(CGetSourcePortType(_GET_INPUT_SOURCE()) == _YPBPR_A0_PORT)
        {
            #if(_YPBPR_HW_AUTO_SOY != _ENABLE)
            CScalerPageSelect(_PAGE0);      
            CScalerSetByte(_P0_ADC_SOG0_CTRL_D2, _SOY_LEVEL);
            #endif
        }
        else
        {
            #if(_YPBPR_HW_AUTO_SOY != _ENABLE)
            CScalerPageSelect(_PAGEB);
            CScalerSetByte(_PB_SOYCH0_CFG3_C3,_SOY_LEVEL);//20071122
            #endif
        }
    
        CScalerPageSelect(_PAGE0);
        CScalerSetByte(_P0_ADC_DCR_CTRL_D3,0x11);
        CScalerSetByte(_P0_ADC_CLAMP_CTRL0_D4,0x00);
    }
#if(_YPBPR_AUTO_SOY == _ENABLE)
    SyncLevelOffset = 0;
#endif

#if(_YPBPR_HW_AUTO_SOY == _ENABLE)
    CYPbPrHWAutoSOY();
#endif

#endif



    CAdjustDisableWatchDog(_WD_ALL);            // Disable watch dog
    CScalerSetByte(_HOST_CTRL_01, 0x40);
    CScalerSetBit(_VGIP_CTRL_10, ~(_BIT1 | _BIT0), 0x00);
    CScalerSetByte(_VGIP_SIGINV_11, 0x00);
    CScalerSetByte(_VGIP_DELAY_CTRL_12, 0x00); //731301
    
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_Z0_CALIBRATION_CTRL_AC, ~_BIT6, _BIT6); //V305 modify
    
    CScalerPageSelect(_PAGE2);
    CScalerSetByte(_P2_TMDS_OUTPUT_CTRL_A6, 0x78);      //Auto Output Disable
    CScalerSetByte(_P2_POWER_ON_OFF_CTRL_A7, 0x6F); //Input Channel ctrl by auto func(Manual)
    CScalerCodeW(tSCALER_RESET_TABLE);
    CScalerSetByte(_VDISP_SIGINV_29, Panel.PanelConfig & (~_BIT3));
    
//20080114***
    CScalerPageSelect(_PAGE6);
    CScalerSetByte(_P6_UZD_VER_INITIAL_VALUE_F2, 0x00);
    CScalerSetByte(_P6_UZD_HOR_INITIAL_VALUE_F1, 0x00); 
//20080114###

    if(bSourceVideo())
    {
        CScalerPageSelect(_PAGE9);      
        CScalerSetBit(_P9_HLOOP_MAXSTATE_C1, ~(_BIT2 | _BIT1 | _BIT0), 0x03);
    }

    CModeSetFreeRun();
    
    if (GET_PANELPOWERSTATUS() == _OFF) 
    {
        CScalerEnableDisplayOutput();
    }
    CModeAutoMeasureOff();                      // Disable auto measure
    CAdjustTMDSErrorCorrectionOn();
    CMiscClearStatusRegister();
    if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
    {
        CScalerSetDataPortBit(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_CLAMP_CTRL0_04, ~(_BIT7 | _BIT6), 0x00);
        CScalerSetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_G_CLAMP_START_00, 0x04);
        CScalerSetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_G_CLAMP_END_01, 0x10);
        CScalerSetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_BR_CLAMP_START_02, 0x04);
        CScalerSetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_BR_CLAMP_END_03, 0x10);
    }
    
#if (_YPBPR_NONE_CHECK_APLL)        
    if (_GET_INPUT_SOURCE() == _SOURCE_YPBPR||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1)       
        CScalerSetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_DETECT_TOLERANCE_SET_08, 0x14); // Set capture windows tolance is 16,hill 20070417
    else
        CScalerSetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_DETECT_TOLERANCE_SET_08, 0x04); // restore capture windows tolance,hill 20070417    
#endif 
    CLR_SHOW_NO_SIGNAL();
    CTimerCancelTimerEvent(CModeNoSignalEvent);
    CTimerCancelTimerEvent(CModeNoCableEvent);
    CTimerCancelTimerEvent(CModeNoSupportEvent);
    CTimerCancelTimerEvent(CModePowerSavingEvent);

    if (GET_CLEAR_OSD_EN())
    {
        CTimerCancelTimerEvent(COsdTimeOut);
        COsdDispOsdTimerEvent();
    }

    CLR_FIRST_ADCCLOCK();
    CLR_USE_TRANSITION_RESULT();
    CLR_FRAMESYNCSTATUS();
#if (_HDMI_SUPPORT == _ON)//temp
    if(CHdmiFormatDetect())//Input source is the HDMI format.
    {
        CLR_HDMIINPUT();
        CLR_AVRESUME();
    }
#endif
    ucInputSyncType = _NO_SYNC_STATE;
    
#if(_TMDS_SUPPORT == _ON)
    SET_PRE_VGA_CONNECT(bVGACONNECT);
#if (_HDMI_SUPPORT == _ON)
    SET_PRE_HDMI_CONNECT(bHDMICONNECT);
#else
    SET_PRE_DVI_CONNECT(bDVICONNECT);
#endif//(_HDMI_SUPPORT == _ON)

#else
    SET_PRE_VGA_CONNECT(bVGACONNECT);
#endif//(_TMDS_SUPPORT == _ON)

    stModeInfo.ModeCurr = _MODE_NOSIGNAL;
    ucModeFound         = _MODE_FIRST;
    ucTimerEvent        = _INACTIVE_COUNTDOWN_EVENT;
    ucEvent1            = _INACTIVE_COUNTDOWN_EVENT;
    
    stModeInfo.Polarity = 0;
    stModeInfo.IHCount = 0;
    stModeInfo.IHFreq = 0;
    stModeInfo.IVTotal = 0;
    stModeInfo.IVFreq = 0;
    stModeInfo.IHWidth = 0;
    stModeInfo.IVHeight = 0;
    stModeInfo.IHSyncPulseCount = 0;
    
    if(ucCurrState != _PWOFF_STATE)         
        ucCurrState = _SEARCH_STATE;
    
    SET_CLEAR_OSD_EN();
    ucVideoType = 0;
#if (_OSD_TYPE == _OSD003)
    bDrawMute   = 0;
#endif
    CIrdaInitial();
}

//--------------------------------------------------
// Description  : Free run mode setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSetFreeRun(void)
{
    WORD usDEndPos;
    CMiscDisableDoubleBuffer();         // Disable video graphic input(VGIP) double buffer mode
    
    
    CAdjustDPLL((DWORD) (Panel.PixelClock) * 1000, _DPLL_N_CODE);
    
    
    CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5 | _BIT3 | _BIT1 | _BIT0),     // Display output normal operation and enable display timing generator
        (_BIT5 | _BIT1 | _BIT0));
    
    pData[0] = (HIBYTE(Panel.DHTotal - 4) & 0x0f);
    pData[1] = (LOBYTE(Panel.DHTotal - 4));
    pData[2] = (Panel.DHSyncWidth);
    pData[3] = (HIBYTE(Panel.DHStartPos) & 0x0f);
    pData[4] = (LOBYTE(Panel.DHStartPos));
    pData[5] = (HIBYTE(Panel.DHStartPos) & 0x0f);
    pData[6] = (LOBYTE(Panel.DHStartPos));
    
    usDEndPos = Panel.DHStartPos + Panel.DHWidth;
    pData[7] = (HIBYTE(usDEndPos) & 0x0f);
    pData[8] = (LOBYTE(usDEndPos));
    pData[9] = (HIBYTE(usDEndPos) & 0x0f);
    pData[10] = (LOBYTE(usDEndPos));
    
    CScalerSetByte(_DISP_ACCESS_PORT_2A, _DISP_DH_TOTAL_H_00);
    CScalerWrite(_DISP_DATA_PORT_2B, 11, pData, _NON_AUTOINC);
    
    pData[0] = (HIBYTE(Panel.DVTotal) & 0x0f);
    pData[1] = (LOBYTE(Panel.DVTotal));
    pData[2] = (Panel.DVSyncHeight);
    pData[3] = (HIBYTE(Panel.DVStartPos) & 0x0f);
    pData[4] = (LOBYTE(Panel.DVStartPos));
    pData[5] = (HIBYTE(Panel.DVStartPos) & 0x0f);
    pData[6] = (LOBYTE(Panel.DVStartPos));
    
    usDEndPos = Panel.DVStartPos+ Panel.DVHeight;
    pData[7] = (HIBYTE(usDEndPos) & 0x0f);
    pData[8] = (LOBYTE(usDEndPos));
    pData[9] = (HIBYTE(usDEndPos) & 0x0f);
    pData[10] = (LOBYTE(usDEndPos));
    
    CScalerSetByte(_DISP_ACCESS_PORT_2A, _DISP_DV_TOTAL_H_0B);
    CScalerWrite(_DISP_DATA_PORT_2B, 11, pData, _NON_AUTOINC);
    
    pData[0] = ((Panel.DHTotal >> 4) & 0xf0) | (HIBYTE(Panel.DVTotal) & 0x0f);
    pData[1] = LOBYTE(Panel.DVTotal);
    pData[2] = LOBYTE(Panel.DHTotal);
    
    CScalerPageSelect(_PAGE1);
    CScalerWrite(_P1_EVEN_FIX_LASTLINE_M_C7, 3, pData, _AUTOINC);
    
    // Modify OSD Reference Position
    CScalerSetDataPortByte(_DISP_ACCESS_PORT_2A, _DISP_OSD_REFERENCE_DEN_21, 0x02);//stDisplayInfo.DVStartPos);
}
//-------------------------------------------------------------------------
bit CModeConnectIsChange(void)
{
#if(_TMDS_SUPPORT == _ON)
#if (_HDMI_SUPPORT == _ON)
    if((bVGACONNECT != GET_PRE_VGA_CONNECT()) || (bHDMICONNECT != GET_PRE_HDMI_CONNECT()))
    {
        SET_PRE_VGA_CONNECT(bVGACONNECT);
        SET_PRE_HDMI_CONNECT(bHDMICONNECT);
        return _TRUE;
    }
    SET_PRE_VGA_CONNECT(bVGACONNECT);
    SET_PRE_HDMI_CONNECT(bHDMICONNECT);
#else
    if ((bVGACONNECT != GET_PRE_VGA_CONNECT()) || (bDVICONNECT != GET_PRE_DVI_CONNECT())) {
        SET_PRE_VGA_CONNECT(bVGACONNECT);//MCU VGA detect pin
        SET_PRE_DVI_CONNECT(bDVICONNECT);//MCU DVI detect pin
        return _TRUE;
    }
    SET_PRE_VGA_CONNECT(bVGACONNECT);
    SET_PRE_DVI_CONNECT(bDVICONNECT);
#endif//(_TMDS_SUPPORT == _ON)
#else//(_TMDS_SUPPORT == _ON)
    if ((bVGACONNECT != GET_PRE_VGA_CONNECT())) {
        SET_PRE_VGA_CONNECT(bVGACONNECT);
        return _TRUE;
    }
    SET_PRE_VGA_CONNECT(bVGACONNECT);
#endif//(_TMDS_SUPPORT == _ON)
    return _FALSE;
}

/**
* CModeAutoMeasureOn
* online auto measure enable
* first system initial, then main loop
* @param <none>
* @return {none}
*
*/
void CModeAutoMeasureOn(void)
{
    CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT7, _BIT7);
    CTimerDelayXms(40); //V304 modify
}

/**
* CModeAutoMeasureOff
* online auto measure disable
* first system initial, then main loop
* @param <none>
* @return {none}
*
*/
void CModeAutoMeasureOff(void)
{
    CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT7, 0x00);
}

//----------------------------------------------------------------------------------------------------
// Mode Events
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : No signal timeout count down event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSyncTimeoutCountDownEvent(void)
{
    //  ucCurrState = _NOSIGNAL_STATE;
    ucCurrState = _NOSIGNAL_STATE;
    stModeInfo.ModeCurr = _MODE_NOSIGNAL;
    //DebugPrintf("\n\n *****_NOSIGNAL_STATE2*****",0);
    //741001***
#if(_HDMI_SUPPORT == _ON)
    if((_GET_INPUT_SOURCE() == _SOURCE_DVI || _GET_INPUT_SOURCE() == _SOURCE_HDMI) && ( ucHdmiTimerEvent ==0 || ucHdmiTimerEvent ==_INACTIVE_COUNTDOWN_EVENT))
        ucHdmiTimerEvent = _HDMI_NO_SIGNAL_CHECK_CNT;
#endif
    //741001###
    SET_READYFORDISPLAY();
}

//--------------------------------------------------
// Description  : Mode stable count down event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeStableCountDownEvent(void)
{
    SET_MODESTABLE();
}


//-----------------------------------------
// CModePowerSavingEvent
// Power saving event
// first system initial, then main loop
// @param <none>
// @return {none}
//
//----------------------------------------------
void CModePowerSavingEvent(void)
{
    CPowerPanelOff();
    // if OSD is still on scree, don't enter sleep state,
    // check again 2 seconds later.
    CScalerSetBit(_OVERLAY_CTRL_6C, ~_BIT0, 0x00);//tommy add for disable osd
    CScalerSetBit(_VDISP_CTRL_28, ~(_BIT3 | _BIT0), 0x00);
    CPowerADCAPLLOff();
    CPowerLVDSOff();
    CPowerDPLLOff();
    CSetPWM(_BACKLIGHT_PWM, 0xff);
    CScalerDisableDisplayOutput();
    
#if(_VGA_DVI_AUTO_SWITCH_SUPPORT == _ON)
    SET_SOURCE_AUTOCHANGE();
#endif
    CPowerLedSleep();

    ucCurrState = _SLEEP_STATE;

#if(_VIDEO_AV_SUPPORT)
 #if(_SLEEP_FUNC)
    _SET_POWER_DOWN_TIME(0);
    ucAutoPowerDownTime = 0xff;
    CEepromSaveTvData();
 #endif
#endif
}

#if(_HDMI_SUPPORT == _ON)
void CModeHDMITimeoutCountDownEvent(void)
{
    //if(ucOsdState == 0)
    //  COsdFxDisableOsd();
    
    // EricLee mark for HDMI display faster
    //CTimerDelayXms(500);
    if ((bit) CScalerGetBit(_VDISP_CTRL_28, _BIT3))
        CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, 0x00);
    CLR_HDMISHOWSEARCH();//741002
    SET_HDMISTABLE();
    CLR_READYFORDISPLAY();
}
#endif

//--------------------------------------------------
// Description  : Check input signal for interlace mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeInterlaceCheck(void)//v003_interlace_check
{
    switch(_GET_INPUT_SOURCE())
    {
    case _SOURCE_VGA:
#if(_YPBPR_SUPPORT == _ON||_YPBPR1_SUPPORT == _ON)
    case _SOURCE_YPBPR:
    case _SOURCE_YPBPR1:
#endif
        CLR_INTERLACE_MODE();
        
        stModeInfo.IHTotal = 1000;
        //080324
        ///CAdjustAdcClock(stModeInfo.IHTotal);
        // Eric 0617 for YPbPr power ON/OFF
        if (_SOURCE_YPBPR == _GET_INPUT_SOURCE()||_SOURCE_YPBPR1 == _GET_INPUT_SOURCE())
            CAdjustAdcClockYPbPr(stModeInfo.IHTotal);
        else
            CAdjustAdcClock(stModeInfo.IHTotal, 0);
        CAdjustPhase(0);
        CScalerSetBit(_VGIP_CTRL_10, ~(_BIT3 | _BIT2 | _BIT1), 0);
        
        CScalerSetBit(_IPV_ACT_LEN_H_1A, ~_BIT5, _BIT5);
        CTimerDelayXms(80);
        CScalerRead(_IPV_ACT_LEN_H_1A, 1, pData, _NON_AUTOINC);
        if(pData[0] & 0x20)
            SET_INTERLACE_MODE();
        
        
        break;
        
#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON) || (_VIDEO_SUPPORT == _ON))
  #if(_VIDEO_SUPPORT == _ON)
        case _SOURCE_VIDEO_AV:
        case _SOURCE_VIDEO_SV:
        case _SOURCE_VIDEO_TV:
  #endif
#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
    case _SOURCE_DVI:
    case _SOURCE_HDMI:
#endif
        CScalerPageSelect(_PAGE2);
        CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_VCR_50, ~_BIT6, _BIT6);
        CTimerDelayXms(50);
        CScalerGetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_VCR_50, 1, pData, _NON_AUTOINC);
        if((pData[0] & 0x40) == 0x40)
            SET_INTERLACE_MODE();
        else
            CLR_INTERLACE_MODE();
        break;
#endif
    }
}

#if(_DE_INTERLACE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : De-Interlace Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeDeInterlaceSetting(void)
{
    UINT8 option =0;

    stModeInfo.IVHeight = stModeInfo.IVHeight * 2;
    
    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_MIX_B0, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));           //ADC input clock: dual clk mode
    CScalerPageSelect(_PAGE0);
    CScalerSetBit(_P0_ADC_V_BAIS1_CB, ~_BIT6, _BIT6);                           //ADC 2X Oversample
    CScalerSetBit(_VGIP_ODD_CTRL_13, ~(_BIT6 | _BIT2 | _BIT0), (_BIT2 | _BIT0));
    CScalerSetBit(_SCALE_CTRL_32, ~_BIT7, 0x00);                                    //Disable video compensation
    
    CScalerPageSelect(_PAGE6);
    CScalerSetBit(_P6_YUV422_TO_YUV444_D4, ~_BIT7, _BIT7);              //Enable YUV422 to YUV 444
    CScalerSetByte(_P6_HORIZONTAL_ACTIVE_SIZE_MSB_A9, (BYTE)(stModeInfo.IHWidth >> 8)); //setup NR cap-win(H)
    CScalerSetByte(_P6_HORIZONTAL_ACTIVE_SIZE_LSB_AA, (BYTE)(stModeInfo.IHWidth >> 0));
    CScalerSetByte(_P6_VERTICAL_ACTIVE_SIZE_MSB_AB, (BYTE)(stModeInfo.IVHeight >> 8));      //setup NR cap-win(V)
    CScalerSetByte(_P6_VERTICAL_ACTIVE_SIZE_LSB_AC, (BYTE)(stModeInfo.IVHeight >> 0));
    CScalerSetBit(_P6_ENABLE_BIST_CTRL_A0, ~_BIT3, _BIT3);                  //Enable De-interlace Mode      
    
    CScalerSetByte(_P6_INTERPOLATION_CTRL_A1, 0x00/*0x01*/);//eric 20070607                         //use 9 pixel interpolation range
    CScalerSetBit(_P6_SMOOTHING_ERROR_CORR_CTRL_A6,~_BIT2,_BIT2);       //enable median filter
    
    CScalerSetBit(_P6_UZD_CTRL1_E4, ~(_BIT3 |_BIT2), _BIT2);                        //For 480i/576i SU case,open NR func.
    
    if(_GET_INPUT_SOURCE() == _SOURCE_YPBPR||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1)
        CScalerSetBit(_P6_PEAKING_ENABLE_C1, ~_BIT0, _BIT0);                        //Enable 444 to 422 color conversion
    
    if(stModeInfo.IHWidth > 720)
        ((WORD *)pData)[0] = 720;
    else
        ((WORD *)pData)[0] = stModeInfo.IHWidth;
    ((WORD *)pData)[1] = stModeInfo.IHTotal - stModeInfo.IHWidth;
    //((WORD *)pData)[0] = stModeInfo.IHWidth;                          //v004 add
    
    CScalerSetByte(_P6_ACTIVE_BLANK_WINDOW_CTRL_MSB_D5, (((pData[0] & 0x07) << 4) | (pData[2] & 0x03)));
    CScalerSetByte(_P6_ACTIVE_WINDOW_CTRL_LSB_D6, pData[1]);
    CScalerSetByte(_P6_BLANK_WINDOW_CTRL_LSB_D7, pData[3]);
    
    //CScalerSetByte(_IPH_PORCH_NUM_H_1F, (pData[2] & 0x07));   //v004 cancel
    CScalerSetByte(_IPH_PORCH_NUM_H_1F, ((pData[2] | 0x10)& 0x17)); //fjyang20070712 for FV set
    CScalerSetByte(_IPH_PORCH_NUM_L_20, pData[3]);              //v004 cancel
    
//20080114***
    CScalerSetBit(_P6_DELETE_LINE_PIXEL_ENABLE_A7, ~(_BIT1), _BIT1);
    stModeInfo.IVHeight = stModeInfo.IVHeight - 4;
//20080114###

    //CModeSetScaling(0x05); // 0x05: ALL SCALE UP
    if (stModeInfo.IVHeight < stDisplayInfo.DVHeight)
        option |= _BIT0;    // bit 0 : V scale-up
    if (stModeInfo.IVHeight > stDisplayInfo.DVHeight)
        option |= _BIT1;    // bit 1 : V scale-down
    if (stModeInfo.IHWidth < stDisplayInfo.DHWidth)
        option |= _BIT2;    // bit 2 : H scale-up
    if (stModeInfo.IHWidth > stDisplayInfo.DHWidth)
        option |= _BIT3;    // bit 3 : H scale-down
    CModeSetScaling(option);
    
    stModeInfo.IVHeight = stModeInfo.IVHeight + 4;//20080114        
    stModeInfo.IVHeight = stModeInfo.IVHeight / 2;
}
#endif  // End of #if(_DE_INTERLACE_SUPPORT == _ON)

BYTE CCalcCurrentModeRatio(void)
{
    BYTE ucRatio = (DWORD)stModeInfo.IVHeight * 100 / stModeInfo.IHWidth;
    return ucRatio;
}
//---------------------------------------------

BYTE CCalcRatio(void)
{
    BYTE ucRatio = (DWORD)Panel.DVHeight * 100 / Panel.DHWidth;
    return ucRatio;
}
//---------------------------------------------
WORD CCalcPanelWdith(void)
{
     BYTE ucRatio = CCalcRatio();
     
     if(ucRatio >= 75)     // 比例比 4:3 更大
        return Panel.DHWidth;


     // if run to here Panel Ratio is 16 : 9 or 16 : 10
     if(GET_DISPLAYMODE() == _DISPMODE_FULL)
     {

#if(_PANEL_TYPE == _PNL_HSD070IDW1)		
        return Panel.DHWidth-2;
#else
		 return Panel.DHWidth;
#endif

     }     
     else if(GET_DISPLAYMODE() == _DISPMODE_43)
     {
        return Panel.DVHeight * 4 / 3;
     }
     else       // auto
     {
         BYTE ucModeRatio = CCalcCurrentModeRatio();
         
         if(ucModeRatio >= 75)
            return Panel.DVHeight * 4 / 3;
         return Panel.DHWidth;
     }

}
//---------------------------------------------
WORD CCalcPanelDHSta(void)
{

    WORD usWidth = CCalcPanelWdith();
    return Panel.DHStartPos + (Panel.DHWidth - usWidth) / 2;
}
//---------------------------------------------
WORD CCalcPanelDHEnd(void)
{
    WORD usWidth = CCalcPanelWdith();
    return Panel.DHStartPos + Panel.DHWidth - (Panel.DHWidth - usWidth) / 2;
}
//---------------------------------------------



//--------------------------------------------------
// Description  : No signal event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeNoSignalEvent(void)
{
#if(_VIDEO_AV_SUPPORT)
 #if(_SLEEP_FUNC)
    _SET_POWER_DOWN_TIME(0);
    ucAutoPowerDownTime = 0xff;
    CEepromSaveTvData();
 #endif
#endif

    CPowerPanelOn();
    CPowerLightPowerOn();
    ucOsdEventMsg = _SHOW_NOSIGNAL_MSG;
    
    
    #if (_HDMI_SUPPORT == _ON)  
    CLR_HDMISHOWSEARCH();
    #endif

}

//--------------------------------------------------
// Description  : No cable event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeNoCableEvent(void)
{
#if(_VIDEO_TV_SUPPORT)
 #if(_SLEEP_FUNC)
    _SET_POWER_DOWN_TIME(0);
    ucAutoPowerDownTime = 0xff;
    CEepromSaveTvData();
 #endif
#endif

    ucOsdEventMsg = _SHOW_NOCABLE_MSG;
    CPowerPanelOn(); // avoid power on not active panel power
    CPowerLightPowerOn();
	CMuteOn();

#if (_HDMI_SUPPORT == _ON)  
    CLR_HDMISHOWSEARCH();
#endif

    
}

//--------------------------------------------------
// Description  : No support event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeNoSupportEvent(void)
{
#if(_VIDEO_AV_SUPPORT)
 #if(_SLEEP_FUNC)
    _SET_POWER_DOWN_TIME(0);
    ucAutoPowerDownTime = 0xff;
    CEepromSaveTvData();
 #endif
#endif

    CPowerPanelOn(); 
    CPowerLightPowerOn();
	CMuteOn();
    ucOsdEventMsg = _SHOW_NOSUPPORT_MSG;

#if (_HDMI_SUPPORT == _ON)  
    CLR_HDMISHOWSEARCH();
#endif  
}

//-----------------------------------------------------------
void COsdDispOsdTimerEvent(void)
{         
    COsdFxDisableOsd();



    ucOsdState = _MI_MENU_NONE;
        
#if(_VIDEO_AV_SUPPORT)
 #if(_SLEEP_FUNC)
    bOSDOnScreen = 0;
 #endif
         
 #if(_SLEEP_FUNC)
    if(_ACTIVE_STATE == ucCurrState && (0xff == ucAutoPowerDownTime) || (0 == _GET_POWER_DOWN_TIME()))
 #endif 
#else
    if(_ACTIVE_STATE == ucCurrState)
#endif 
    {
         bDrawMute = 1;
    }
bDrawMute = 1;
#if(_KEY_TYPE == _KT_PCB2660_003_5KEY)
#if(_VIDEO_TV_SUPPORT)
	bTVChannelChange = 0;
#endif
#endif

}


//-----------------------------------------------------------
void ModeLimit()
{
	 unsigned char i,Count;
	 Count = tModeLimitTable[0];
	 for(i=0;i<Count;i++)
	 {
		 if(tModeLimitTable[i+1] == stModeInfo.ModeCurr)
         {
             stModeInfo.ModeCurr = _MODE_NOSUPPORT;
             return;
          }
	 }

}

//--------------------------------------------------
#define NOR_FACTOR_CONSTANT     0x3FC00000 
BYTE code tDCC_Control1[] =
{
    0x84,  0x66,  0xc3,
    0x7c,  0xce,  0x1e,
    0x10,  0x10,  0x14,
};

BYTE code tDCC_Control2[] =
{
    0x84,  0x66,  0xc3,
    0x5c,  0xce,  0x1e,
    0x10,  0x10,  0x14,
};

BYTE code tDCC_Control3[] =
{
    0x84,  0x66,  0xc3,
    0x7c,  0xce,  0x1e,
    0x10,  0x10,  0x14,
};

BYTE code tDCC_Control4[] =
{
    0x84,  0x66,  0xc3,
    0xb4,  0xe6,  0x1e,
    0x10,  0x00,  0xff,

};

BYTE code tDCC_Control5[] =
{
    0x84,  0x66,  0xc3,
    0xb4,  0xe6,  0x1e,
    0x10,  0x00,  0xff,

};

BYTE code tDCC_Control6[] =
{
    0x84,  0x66,  0xc3,
    0x64,  0xce,  0x1e,
    0x10,  0x10,  0x14,
};

BYTE code tDCC_UserCurve1[] =
{
    0x05,  0x10,  0x1f,  0x30,
    0x43,  0x57,  0x6d,  0x80,
    0x95,  0xa9,  0xbd,  0xce,
    0xe0,  0xed,  0xf7,  0x10,  0x00,
    0x80,  0x14,  0x34,
};

BYTE code tDCC_UserCurve2[] =
{
    0x0e,  0x1d,  0x2d,  0x3d,
    0x4d,  0x5d,  0x6d,  0x7d,
    0x8e,  0x9d,  0xad,  0xbc,
    0xca,  0xdb,  0xeb,  0x10,  0x00,
    0x41,  0x14,  0x34,
};

BYTE code tDCC_UserCurve3[] =
{
    0x0f,  0x1d,  0x2d,  0x3e,
    0x4b,  0x5c,  0x6d,  0x80,
    0x91,  0xa2,  0xb3,  0xc4,
    0xd4,  0xe3,  0xf2,  0x10,  0x00,
    0x5d,  0x14,  0x30,
};

BYTE code tDCC_UserCurve4[] =
{
    0x07,  0x11,  0x21,  0x35,
    0x50,  0x60,  0x70,  0x80,
    0x9a,  0xad,  0xbf,  0xcb,
    0xd8,  0xe3,  0xf0,  0x10,  0x00,
    0x50,  0x14,  0x34,
};

BYTE code tDCC_UserCurve5[] =
{
    0x07,  0x11,  0x21,  0x35,
    0x50,  0x69,  0x7e,  0x8f,
    0x9e,  0xad,  0xbf,  0xcb,
    0xd8,  0xe3,  0xf0,  0x10,  0x00,
    0x50,  0x14,  0x34,
};

BYTE code tDCC_UserCurve6[] =
{
    0x18,  0x2c,  0x3f,  0x50,
    0x61,  0x73,  0x85,  0x99,
    0xad,  0xc0,  0xd2,  0xe0,
    0xeb,  0xf5,  0xfc,  0x10,  0x00,
    0x64,  0x14,  0x3a,
};

code BYTE *tDCC_Control[6] =
{
    tDCC_Control2, tDCC_Control3, tDCC_Control1, tDCC_Control4, tDCC_Control5, tDCC_Control6
};

code BYTE  *tDCC_UserCurve[6] =
{
    tDCC_UserCurve2, tDCC_UserCurve3, tDCC_UserCurve1, tDCC_UserCurve4, tDCC_UserCurve5, tDCC_UserCurve6
};

void CAccAdjust (BYTE mode)
{
    BYTE *DCCContol,*DCCCurve;
    BYTE i,j;

    // Set DCC Normal_Factor
//  ((DWORD*)pData)[1] = ((DWORD)stDisplayInfo.DHWidth * stDisplayInfo.DVHeight);
    ((DWORD*)pData)[1] = ((DWORD) Panel.DHWidth * Panel.DVHeight);
    ((DWORD*)pData)[0] = (NOR_FACTOR_CONSTANT / ((DWORD*)pData)[1]);
    CScalerSetByte(_DCC_ACCESS_PORT_E6, 0x00);
    CScalerSetByte(_DCC_DATA_PORT_E7, pData[1]);
    CScalerSetByte(_DCC_DATA_PORT_E7, pData[2]);
    CScalerSetByte(_DCC_DATA_PORT_E7, pData[3]);

    if(mode == 0)
    {

#if(_DCC_FUNC==_ENABLE)//Modify:2006.4.25D jerry
        CScalerSetByte(_DCC_CTRL0_E4, 0x90);  //set manual mode
        CScalerSetByte(_DCC_CTRL1_E5, 0x80);  //DCC gain control enable 
#else   
        CScalerSetByte(_DCC_CTRL0_E4, 0x00);  //disable dcc, page0
        CScalerSetByte(_DCC_CTRL1_E5, 0x00);  //disable
#endif

        
        return;
    }
    else
    {
         DCCContol = tDCC_Control[mode - 1];
         DCCCurve = tDCC_UserCurve[mode - 1];
    }

    CScalerRead(_DCC_CTRL0_E4, 1, &i, _NON_AUTOINC);
    i = i & 0xfc;
    CScalerRead(_DCC_CTRL1_E5, 1, &j, _NON_AUTOINC);
    CScalerSetByte(_DCC_CTRL0_E4, i);
    CScalerSetByte(_DCC_CTRL1_E5, j);


    CScalerSetByte(_DCC_ACCESS_PORT_E6, 0x03);
    for (i=0; i<9; i++) 
    {
        CScalerSetByte(_DCC_DATA_PORT_E7, *DCCContol );
        DCCContol++;
    }

    CScalerRead(_DCC_CTRL0_E4, 1, &i, _NON_AUTOINC);
    i = (i & 0xfc) | 0x01;
    CScalerSetByte(_DCC_CTRL0_E4, i);

    CScalerSetByte(_DCC_ACCESS_PORT_E6, 0x00);
    for (i=0; i<20; i++) 
    {
        CScalerSetByte(_DCC_DATA_PORT_E7, *DCCCurve);
        DCCCurve++;
    }

    CTimerWaitForEvent(_EVENT_DEN_STOP);
    CScalerSetByte(_DCC_CTRL0_E4, 0xac);  //enable dcc
    CScalerSetByte(_DCC_CTRL1_E5, 0x80);

    CScalerSetByte(_HW_ACCESS_PORT_60, 0x00);         // disable Hightlight Window

}

//--------------------------------------------------
void COsdTimeOut(void)
{
	if(ucCurrState == _NOSIGNAL_STATE)
	{
		ucOsdState = _MI_MENU_NONE;	
       #if(_LOGO_ENABLE)
		SET_FIRST_LOADFONT();
		CDrawLogo();
       #else
	   #if(_LOGO_Visatech)
		CShowVisatech();
          #else
		CShowNoSignal();
          #endif		  
       #endif
	}
	else
	{
		COsdDispOsdTimerEvent();
	}	
}
//------------------------END--------------------------
