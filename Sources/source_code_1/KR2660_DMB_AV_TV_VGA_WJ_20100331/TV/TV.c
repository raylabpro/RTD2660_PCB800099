#include "Core\Header\Include.h"


#if(_VIDEO_TV_SUPPORT == _OFF)
BYTE idata ucTVType             = _NORMAL_TV_TYPE;
#endif

#if(_VIDEO_TV_SUPPORT)
#if(_TV_AFC)            
BYTE AFCState                      = 0;
WORD CurrAFCFreq              = 0;
#endif
BYTE idata ucTVType             = _NORMAL_TV_TYPE;
bit bChangeChannel              = 0;
BYTE xdata ucPrevChannel        = 0;
WORD xdata ucCurrentInputNumber = 0;
BYTE xdata ucCurrentInputState  = 0;           
BYTE xdata ucAudioState         = 1;
BYTE xdata ucAddrIfPllDM        = _ADDR_IfPllDM;


#if(_IF_PLL_DE_CHIP == _IF_PLL_DE_1338 || _IF_PLL_DE_CHIP == _IF_PLL_DE_135X)
bit bFM = 0;
#endif

//WORD CLoadChannelFreq(const BYTE ucCurrentChannel);
//void CSaveChannelFreq(const WORD iFreq, const BYTE ucCurrentChannel);



//==========================================================================
//                      CDetectTVSignalType
//==========================================================================
BYTE CDetectTVSignalType(void)
{
#if(_NTSC_SEARCH_TABLE)

    CVideoSoftReset();
    CTimerDelayXms(100);

    if (kx_CVideoModeLocked())  // Horizontal Lock
         return 1;
#else

    BYTE ucTemp;
              
    for(ucTemp = 0; ucTemp < 4; ucTemp++)
    {
        if (kx_CVideoModeLocked())  // Horizontal Lock
             return 1;

        CTimerDelayXms(50);
    }

#endif

    // No video detected or h/v sync not locked
     return 0;  
}

      
//==========================================================================
//                        CModeResetTVMode
//==========================================================================
void CModeResetTVMode(void)  // eric 1130 add for change tv channel bug
{         
    TVNoSignalCount = 0;
    TVSignalCount   = 0;
    bBuleBackGround = 0;
#if(1)
   #if(0)
 //   CPowerLightPowerOff();
    CLR_LIGHTPOWERSTATUS();
	// force to background
    CAdjustBackgroundColor(0x00, 0x00, 0x00);     
	CScalerSetBit(_VDISP_CTRL_28, 0xf7, _BIT5);	// Display output is forced to the background color,and free run
	CTimerWaitForEvent(_EVENT_DEN_STOP);	          
	CAdjustDisableWatchDog(_WD_ALL);			// Disable watch dog
	CScalerSetByte(_HOST_CTRL_01, 0x40);
	CScalerSetBit(_VGIP_CTRL_10, ~(_BIT1 | _BIT0), 0x00);
	CScalerSetByte(_VGIP_SIGINV_11, 0x00);
    
    CScalerSetByte(_VGIP_DELAY_CTRL_12, 0x00); //731301	
    CScalerPageSelect(_PAGE2);
	CScalerSetBit(_P2_Z0_CALIBRATION_CTRL_AC, ~_BIT6, _BIT6); //V305 modify    
    CScalerPageSelect(_PAGE2);
	CScalerSetByte(_P2_TMDS_OUTPUT_CTRL_A6, 0x78);		//Auto Output Disable
	CScalerSetByte(_P2_POWER_ON_OFF_CTRL_A7, 0x0F);	//Input Channel ctrl by auto func(Manual)                
	CModeAutoMeasureOff();						// Disable auto measure
	CMiscClearStatusRegister();  
    ucSearchCount  = 1;
    bChangeChannel = 1;
	
    ucCurrState  = _SEARCH_STATE; 
   #else
 //   CPowerLightPowerOff();
    CLR_LIGHTPOWERSTATUS();
    SET_OSD_READYFORDISPLAY();

#if(_CHANGE_CHANNEL_DISP_MTD == _CHANGE_CHANNEL_DISP_M1)
	//CScalerSetBit(_VDISP_CTRL_28, ~(_BIT3), 0x00);	
#elif(_CHANGE_CHANNEL_DISP_MTD == _CHANGE_CHANNEL_DISP_M2)
    CAdjustBackgroundColor(0x00, 0x00, 0xff);
	CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5), _BIT5);	
#else     
    CAdjustBackgroundColor(0x00, 0x00, 0x00);
	CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5), _BIT5);	
#endif

    ucSearchCount  = 150;  // 1
    bChangeChannel = 1;
    bTVNoSignal    = 0;
   #endif
	
#else
                 
    CLR_LIGHTPOWERSTATUS();
    CAdjustBackgroundColor(0x00, 0x00, 0x00);     
	CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5|_BIT3), _BIT5);	// Display output is forced to the background color,and free run
    ucSearchCount  = 1;
    bChangeChannel = 1;

#endif
}                                                        

//==========================================================================
//                            CChangeChannel
//==========================================================================
void CChangeChannel(bit bNext)
{
    BYTE ucmaxchannel = _GET_MAX_CHANNEL();

    COsdDispOsdTimerEvent();
#if (_OSD_TYPE == _OSD003)
    bDrawMute = 0;
#endif

    if (stTvInfo.CurChn > ucmaxchannel)
    {
        ucPrevChannel   = 1;
        stTvInfo.CurChn = 1;
        return;
    }
              
    CMuteOn();
#if(_FM_DEVICE)
    if (1 == bFM)
    {
        ucPrevChannel =  stTvInfo.ucFMCurrCh;
    }
    else
#endif
    {
        ucPrevChannel =  stTvInfo.CurChn;
        CModeResetTVMode();
    }

	do
	{
       if (bNext)  // Change next channel
           stTvInfo.CurChn = (stTvInfo.CurChn == ucmaxchannel) ? 1 : (stTvInfo.CurChn+1);
       else        // Change prev channel
           stTvInfo.CurChn = (stTvInfo.CurChn == 1) ? ucmaxchannel : (stTvInfo.CurChn-1);
    
       CLoadTVModeData(stTvInfo.CurChn);

	   if (!_GET_CH_SKIP() || stTvInfo.CurChn == ucPrevChannel)
	        break;
	}
	while(1);

    CTimerDelayXms(200);
    CSetTVChannel(stTvInfo.CurChn); 
    CTimerDelayXms(180);
    CEepromSaveTvData();
    // EricLee 081117 add for change channel have some noise
    //CTimerDelayXms(200);
   // CShowTVNumber(stTvInfo.CurChn, _SHOW_CH_TV_NUMBER | _SHOW_CH_TV_TYPE);
}

//==========================================================================
//bSearchAction:   0 --> Tuning down
//                 1 --> Tuning up
//==========================================================================
void CTuningCurrentChannel(const bit bSearchAction, const BYTE ucCurrentChannel) small
{
    WORD iFreq;

    CLoadTVModeData(ucCurrentChannel);
    if ((_GET_CH_FREQ() < _MIN_FREQ || _GET_CH_FREQ() > _MAX_FREQ) && 0 == _GET_MAX_CHANNEL())
        _SET_CH_FREQ((WORD)_MIN_FREQ);

    iFreq = _GET_CH_FREQ();

    if (bSearchAction) // Tuning up
    {
#if (_FM_DEVICE)
        if (((iFreq < _MAX_FREQ) && 0 == bFM) || ((iFreq < _FM_MAX_FREQ) && 1 == bFM))
#else
        if (iFreq < _MAX_FREQ)
#endif
            iFreq++;
    }
    else  // Tuning down
    {
#if (_FM_DEVICE)
        if (((iFreq > _MIN_FREQ) && 0 == bFM) || ((iFreq > _FM_MIN_FREQ) && 1 == bFM))
#else
        if (iFreq > _MIN_FREQ)
#endif
            iFreq--;
    }

    kx_CSetTuner(_ADDR_TUNER, iFreq); 
    _SET_CH_FREQ(iFreq);
    CSaveTVModeData(ucCurrentChannel);
}

//==========================================================================
//                          CInitTV
//==========================================================================
void CInitTV(void)
{
    TUNER_PWR_ON();
#if(_IF_PLL_DE_CHIP == _IF_PLL_DE_1338 || _IF_PLL_DE_CHIP == _IF_PLL_DE_135X)
    CInitialTB1338();
#endif

    CSetTVChannel(stTvInfo.CurChn);
    ucPrevChannel = stTvInfo.CurChn;
    CSetTvColor(ucTVType);
    CTimerDelayXms(100); 
}

#if((_TV_CHIP != _TV_JS_6B1) && (_TV_CHIP != _TV_JS_6B2) && (_TV_CHIP != _TNJ_8355))  
//---------------------------------------------------------------------------
#define _TV_SIGNAL_NOISE       0x90
#define _TV_AUDIO_COUNT        (_VIDEO_SEARCH_COUNT/2)
void CAudioCtrl(void)
{
    bit bSignalNoise = 0;

    if (_GET_INPUT_SOURCE() != _SOURCE_VIDEO_TV)
        return;
 
    if (ucTVNoise > _TV_SIGNAL_NOISE)
        bSignalNoise = 1;

    if ((bSignalNoise == 1) && (ucAudioState == 0))
        ucAudioState = 1;

    if (ucAudioState == 0)
    {
    	ucAudioState--;
	}
    else
    {
    	ucAudioState++;
    }
	
    if (ucAudioState < _TV_AUDIO_COUNT)  // 250                    
        return;

#if(_FM_DEVICE)
    if ((bSignalNoise == 1) && bFM == 0)  // TV no signal
#else
    if (bSignalNoise == 1)
#endif
    {
        CMuteOn();
    }
    else      
    {
    	CSetVolume();
	}
    ucAudioState = 0;
}
#endif

#if(_IF_PLL_DE_CHIP == _IF_PLL_DE_1338 || _IF_PLL_DE_CHIP == _IF_PLL_DE_135X)  
//---------------------------------------------------------------------------
#if(_FM_DEVICE)
void CChangeFM(void)
{
    CMuteOn();
    if (bFM)
    {                
        CInitialTB1338();
        CTimerDelayXms(10);
        CFMInit();
        CSetTVChannel(stTvInfo.ucFMCurrCh);
        CInitSoundChannel(_SOURCE_VIDEO_TV);
    }
    else
    {
        if (_SOURCE_VIDEO_TV == _GET_INPUT_SOURCE())
           CInitTV();

        CInitSoundChannel(_GET_INPUT_SOURCE());
    }

    CTimerDelayXms(100);
    CSetVolume();
}
#endif
#endif
    
//---------------------------------------------------------------------------

  
#endif


