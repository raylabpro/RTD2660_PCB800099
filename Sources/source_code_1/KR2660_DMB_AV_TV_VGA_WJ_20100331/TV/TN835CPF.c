#include "Core\Header\Include.h"
//----------------------------------------------------
//HSL add for TNJ835C PF 20080415
//----------------------------------------------------
#if(_TV_CHIP == _TN835CPF)

BYTE gucTuner_PB  = 0x00; // Ports byte(PB)
#define SetTunerBand(ucBand)    gucTuner_PB = (gucTuner_PB&0x0c)|(ucBand&0x03)
#define SetTunerSound(ucSound)  gucTuner_PB = (gucTuner_PB&0x03)|(ucSound&0x0c)
WORD CLockChannel1(WORD iStartFreq, const bit bCLockMode) small;


//==========================================================================
//                            kx_CI2CWriteIfPllDM
//==========================================================================
void kx_CI2CWriteIfPllDM(BYTE ucTvType, const bit bTunerMute, const BYTE ucAFTMode)
{
    if (bTunerMute)  CMuteOn();
    switch(ucTvType)
    {
       case _TV_PAL_M:     	  SetTunerSound(_TUNER_MN);       break;
       case _TV_PAL_BG:       SetTunerSound(_TUNER_BG);       break;
       case _TV_PAL_I:        SetTunerSound(_TUNER_I );       break;
       case _TV_PAL_DK:       SetTunerSound(_TUNER_DK);       break;
       case _TV_PAL_N:        SetTunerSound(_TUNER_MN);       break;
       case _TV_SECAM_BG:     SetTunerSound(_TUNER_BG);       break;
       case _TV_SECAM_DK:     SetTunerSound(_TUNER_DK);       break;
       case _TV_NTSC_M:		  SetTunerSound(_TUNER_MN);       break;
       default:               SetTunerSound(_TUNER_I );	      break;
    }	
    if(ucAFTMode==0xff)
    {// no use function
        CDetectTVSignalType();
    }
}
//==========================================================================
//                         kx_CSetTuner
//==========================================================================
void kx_CSetTuner(BYTE ucTunerAddress, WORD Freq)
{
    pData[0] = 6;
    pData[1] = ucTunerAddress;
    ((WORD *)pData)[1] = Freq;

    pData[4] = _TUNER_CONTROL_BYTE1; 

     if(Freq < _VHF_LOW_BAND)  
         SetTunerBand(_TUNER_LOW_BAND);
     else if(Freq < _VHF_HIGH_BAND)
         SetTunerBand(_TUNER_MID_BAND);
     else 
         SetTunerBand(_TUNER_HIGH_BAND);
    pData[5] = gucTuner_PB;
              
    kx_CWriteTuner(pData);
}

//==========================================================================
//                         CTvAutoSearch
//==========================================================================
#if(_NTSC_SEARCH_TABLE)

void CTvAutoSearch(void) small
{
    BYTE ucSound = 0;
    WORD iFreq   = 0;
    bit bTVType  = _GET_TV_TYPE();
         
    ucTVType = _TV_NTSC_M;
    CMuteOn();

    // Reset search max tv channel number
    _SET_MAX_CHANNEL(1);
    stTvInfo.CurChn = (_GET_TV_TYPE() == _TV_CATV) ? 1 : 2;
	ucPrevChannel   = stTvInfo.CurChn;
    // Save current channel
    CEepromSaveTvData();

    kx_CI2CWriteIfPllDM(ucTVType, _TUNER_MUTE_ON, _TUNNING_MODE);
    CTimerDelayXms(8);
    CShowAutoSerachTotal(0);   // Show search tv channel number
                    
#if(_AUTO_SERACH_METHOD == _AUTO_SEARCH_METHOD_1)
    CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, 0x00); 
#endif
	CScalerPageSelect(_PAGE9);		
    CScalerSetByte(_P9_C_LOCK_CONF_B6, 0x6B); 
    CTimerDelayXms(200);
    
    while(1)
    {
        iFreq = CLockChannel(stTvInfo.CurChn, 1);

        if(iFreq == 0xFFFF)
        {
            break;
        }
    }  // End while


    // Save search channel number
    pData[0] = (_GET_TV_TYPE() == _TV_CATV) ? _CATV_MAX_CHANNEL : _AIR_MAX_CHANNEL;
    _SET_MAX_CHANNEL(pData[0]);
    CEepromSaveTvData();
    CSetTVChannel(stTvInfo.CurChn);

    ucCurrState = _SEARCH_STATE;
}

//==========================================================================
//bSearchAction:   0 --> Search down
//                 1 --> Search up
//==========================================================================
void CManualSearch(const bit bSearchAction, const BYTE ucCurrentChannel) small
{
    BYTE ucSound           = 0;
    WORD iFreq             = 0;
   
    CMuteOn();
	CScalerPageSelect(_PAGE9);		
    CScalerSetByte(_P9_C_LOCK_CONF_B6, 0x6B);


    if (bSearchAction)
    {
       if (ucCurrentChannel < _GET_MAX_CHANNEL())
	       iFreq = CLockChannel(ucCurrentChannel+1, 1);
       else
           iFreq = 0xFFFF;
    }
	else 
    {
        if (ucCurrentChannel == 0)  
           iFreq = 0xFFFF;
       else
    	   iFreq = CLockChannel(ucCurrentChannel-1, 0);
    }

    if (iFreq == 0xFFFF)
        CSetTVChannel(ucCurrentChannel);

    CShowAutoSearchSliderInOSD(_GET_CH_FREQ());                         

    CTimerDelayXms(50);
    if (kx_CVideoModeLocked())
        CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, 0x00); 

    ucCurrState = _SEARCH_STATE;
}

//==========================================================================
//  bCLockMode --> 1: lock up         0 : lock down
//==========================================================================
WORD CLockChannel(WORD iStartFreq, const bit bCLockMode) small
{
    BYTE ucPRG          = 0;
    BYTE count          = 0;
    BYTE rData          = 0;
    WORD iStartFreqBase = iStartFreq;
    WORD iMaxChannel    = 0;
    BYTE ucPattCount    = 0;
    bit bTVMode         = _GET_TV_TYPE();

    iMaxChannel = ((bTVMode == _TV_CATV) ? _CATV_MAX_CHANNEL : _AIR_MAX_CHANNEL) - 1;

    while(1)                   
    {
        kx_CSetTuner(_ADDR_TUNER, (bTVMode == _TV_CATV) ? tNTSC_CATV[iStartFreq] : tNTSC_AIR[iStartFreq]);
      
        if(CKeyStopAutoSearch())
           return 0xFFFF;
                          
        // Show search channel state 
        CShowAutoSearchSliderInOSD(((bTVMode == _TV_CATV) ? tNTSC_CATV[iStartFreq] : tNTSC_AIR[iStartFreq])); 

        while(1)//(count = 0; count < 5; count++)
        {
            CTimerDelayXms(100);

            if (CDetectTVSignalType())
            {
                WORD iFreqTemp = (bTVMode == _TV_CATV) ? tNTSC_CATV[iStartFreq] : tNTSC_AIR[iStartFreq];

                _SET_CH_FREQ(iFreqTemp);
                _SET_CH_SKIP(0);
                CSaveTVModeData(iStartFreq);
                if (ucPRG == 0)
                    stTvInfo.CurChn = iStartFreq;

                ucPRG++;

                CShowAutoSerachTotal(ucPRG);  // Show search tv channel number
                break;
            }
            
            count++;
            if (count >= 5) 
            {
                WORD iFreqTemp = (bTVMode == _TV_CATV) ? tNTSC_CATV[iStartFreq] : tNTSC_AIR[iStartFreq];

                _SET_CH_FREQ(iFreqTemp);
                _SET_CH_SKIP(1);
                CSaveTVModeData(iStartFreq);
                break;
            }
        }
  
        if (bCLockMode) // Search up
        {
            iStartFreq++;
            if (iStartFreq > iMaxChannel)
                return 0xFFFF;
        }
        else            // Search down
        {
            if (iStartFreq == 0) 
                return 0xFFFF;

            iStartFreq--;
        }
    }
    return 0xFFFF;  //Not Find Channel
}                

#else

void CTvAutoSearch(void) small
{
    BYTE ucSound      = 0;
    BYTE ucPRG        = 1;
    BYTE ucmaxchannel = _GET_MAX_CHANNEL();
    WORD iFreq        = _MIN_FREQ;
         
    // Read color and sound type
    if (0 == ucmaxchannel)
    {
        ucSound  = 0;
        CLoadTVModeData(1);
    }
    else
    {
        ucSound  = 0;
        CLoadTVModeData(stTvInfo.CurChn);
    }

    // Reset search max tv channel number
    _SET_MAX_CHANNEL(1);
    stTvInfo.CurChn = 1;
	ucPrevChannel   = 1;
    // Save current channel
    CEepromSaveTvData();

    kx_CI2CWriteIfPllDM(ucTVType, _TUNER_MUTE_ON, _TUNNING_MODE);
    CTimerDelayXms(8);
    CShowAutoSerachTotal(ucPRG - 1);   // Show search tv channel number
                    
#if(_AUTO_SERACH_METHOD == _AUTO_SEARCH_METHOD_1)
    CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, 0x00); 
#endif

	CScalerPageSelect(_PAGE9);		
    CScalerSetByte(_P9_C_LOCK_CONF_B6, 0x6B);
    CTimerDelayXms(200);

    while(1)
    {
        iFreq = CLockChannel(iFreq+40, 1);

        if(iFreq < 2)
        {
            break;
        }
        
        _SET_CH_FREQ(iFreq);
        _SET_CH_SKIP(0);
        CSaveTVModeData(ucPRG);
        
        ucPRG++;
        if(ucPRG > _MAX_CHANNEL_COUNT)
        {
           ucPRG -= 1;
           break;
        }

        CShowAutoSerachTotal(ucPRG - 1);  // Show search tv channel number

    }  // End while

    {
    #if(_CHANGE_CHANNEL_MTD == _CHANGE_CHANNEL_M2)
        {
            BYTE ucChannelCount = ucPRG;
       
            for(; ucChannelCount < _MAX_CHANNEL_COUNT; ucChannelCount++)
            {
                _SET_CH_COLOR_TYPE(ucTVType);
                _SET_CH_FREQ((WORD)_MIN_FREQ);
                _SET_CH_SKIP(1);
                CSaveTVModeData(ucChannelCount);
            }
    
        }
    #endif
    
        // Save search channel number
        pData[0] = ucPRG;

        _SET_MAX_CHANNEL(pData[0]);
        CEepromSaveTvData();
    }

    CTimerDelayXms(10);
    CSetTVChannel(1);

    ucCurrState = _SEARCH_STATE;
}

//==========================================================================
//bSearchAction:   0 --> Search down
//                 1 --> Search up
//==========================================================================
void CManualSearch(const bit bSearchAction, const BYTE ucCurrentChannel) small
{
    BYTE ucSound           = 0;
    WORD iFreq             = 0;
    WORD ucSatrtSearchFreq = 0;  
   
    CMuteOn();
	CScalerPageSelect(_PAGE9);		
    CScalerSetByte(_P9_C_LOCK_CONF_B6, 0x6B);
    ucSatrtSearchFreq = _GET_CH_FREQ();

    kx_CI2CWriteIfPllDM(ucTVType, _TUNER_MUTE_ON, _TUNNING_MODE);
    CTimerDelayXms(100);

    if (ucSatrtSearchFreq > _MAX_FREQ)
        ucSatrtSearchFreq = _MAX_FREQ;
    else if(ucSatrtSearchFreq < _MIN_FREQ)
        ucSatrtSearchFreq = _MIN_FREQ;


    if (bSearchAction)
        iFreq = CLockChannel1(ucSatrtSearchFreq + 40, 1);
    else
        iFreq = CLockChannel1(ucSatrtSearchFreq - 40, 0);

    if (iFreq > 100)
    {
        _SET_CH_FREQ(iFreq);
        _SET_CH_SKIP(0);
        CSaveTVModeData(ucCurrentChannel);
    }
    CSetTVChannel(ucCurrentChannel);

    CShowAutoSearchSliderInOSD(_GET_CH_FREQ());                         

    CTimerDelayXms(50);
    if (kx_CVideoModeLocked())
        CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, 0x00); 

//	CTimerReactiveTimerEvent(SEC(GET_OSDTIMEOUT()), COsdFxExitEvent);

    ucCurrState = _SEARCH_STATE;
}

BYTE kx_GetTN835CPFData(void)
{
	BYTE ucReg, ucData;
	ucReg = CI2cRead(_ADDR_TUNER, 0, 1, &ucData);
	if(ucReg == _FAIL) ucData = _FAIL;
	return ucData;
}

//==========================================================================
//  bCLockMode --> 1: lock up         0 : lock down
//==========================================================================
WORD CLockChannel(WORD iStartFreq, const bit bCLockMode) small
{
    BYTE f              = 0;
    BYTE rData          = 0;
    BYTE LowLevel_CH    = 0;
    BYTE count          = 0;
    WORD freq           = 0;
    WORD iStartFreqBase = iStartFreq;
    BYTE ucPattCount    = 0;

    while(1)                   
    {
        kx_CSetTuner(_ADDR_TUNER, iStartFreq);
      
        if (bCLockMode) // Search up
        {
            if (iStartFreq > (iStartFreqBase + 300))
            {
                if(CKeyStopAutoSearch())
                   return 0;
            }
        }
        else
        {
            if (iStartFreq < (iStartFreqBase - 300))
            {
                if(CKeyStopAutoSearch())
                   return 0;
            }
        } 
    
      if(CKeyStopAutoSearch())
           return 0;
                          
        // Show search channel state 
        CShowAutoSearchSliderInOSD((iStartFreq)); 
        CTimerDelayXms(5);  
        rData = kx_GetTN835CPFData();
        if(bCLockMode)
		{
			if(rData & 0x40)
			{
				switch(rData&0x07)
				{
					case 0x00: // -125
				    	iStartFreq -= 2;
				        break;
				    case 0x01: // -62.5
				        iStartFreq -= 1;
				        break;
				    case 0x02: // 0
				    	if(CDetectTVSignalType())
				        	return iStartFreq; // Save
				        else
				        	iStartFreq += (4*_TUNER_BP); 
				        break;
				    case 0x03: // +62.5              
				    	iStartFreq += 1;
				        break;
				    case 0x04: // +125
				    	iStartFreq += 2;
				        break;
				    default:
				    	iStartFreq += 4;
				        break;
				}
			}
			else
				iStartFreq += 4;
		}
		else
		{
			if(rData & 0x40)
			{
				switch(rData&0x07)
				{
					case 0x00: // -125
				    	iStartFreq -= 2;
				        break;
				    case 0x01: // -62.5
				        iStartFreq -= 1;
				        break;
				    case 0x02: // 0
				    	if(CDetectTVSignalType())
				        	return iStartFreq; // Save
				        else
				        	iStartFreq -= (4*_TUNER_BP); 
				        break;
				    case 0x03: // -62.5              
				    	iStartFreq -= 1;
				        break;
				    case 0x04: // -125
				    	iStartFreq -= 2;
				        break;
				    default:
				    	iStartFreq -= 4;
				        break;
				}
			}
			else
				iStartFreq -= 4;
		}
		
		if(bCLockMode)
		{
		    if (iStartFreq > _MAX_FREQ)
		        return 1;
		}
		else
		{
			if (iStartFreq < _MIN_FREQ) 
				return 1;
		}
    }
    return 1;  //Not Find Channel
}

WORD CLockChannel1(WORD iStartFreq, const bit bCLockMode) small
{
    BYTE f              = 0;
    BYTE rData          = 0;
    BYTE LowLevel_CH    = 0;
    BYTE count          = 0;
    WORD freq           = 0;
    WORD iStartFreqBase = iStartFreq;
    BYTE ucPattCount    = 0;
    bit bReSearch       = 0;

    while(1)                   
    {
        kx_CSetTuner(_ADDR_TUNER, iStartFreq);
      
        if (bCLockMode) // Search up
        {
            if (iStartFreq > (iStartFreqBase + 300))
            {
                if(CKeyStopAutoSearch())
                   return 0;
            }
        }
        else
        {
            if (iStartFreq < (iStartFreqBase - 300))
            {
                if(CKeyStopAutoSearch())
                   return 0;
            }
        } 
    
      if(CKeyStopAutoSearch())
           return 0;
                          
        // Show search channel state 
        CShowAutoSearchSliderInOSD((iStartFreq)); 
        CTimerDelayXms(5);  
        rData = kx_GetTN835CPFData();
        if(bCLockMode)
		{
			if(rData & 0x40)
			{
				switch(rData&0x07)
				{      /*
					case 0x00: // -125
				    	iStartFreq -= 2;
				        break;
				    case 0x01: // -62.5
				        iStartFreq -= 1;
				        break; */
				    case 0x02: // 0
				    	if(CDetectTVSignalType())
				        	return iStartFreq; // Save
				        else
				        	iStartFreq += (4*_TUNER_BP); 
				        break;
				    case 0x03: // +62.5              
				    	iStartFreq += 1;
				        break;
				    case 0x04: // +125
				    	iStartFreq += 1;
				        break;
				    default:
				    	iStartFreq += 1;
				        break;
				}
			}
			else
				iStartFreq += 2;
		}
		else
		{
			if(rData & 0x40)
			{
				switch(rData&0x07)
				{
					case 0x00: // -125
				    	iStartFreq -= 1;
				        break;
				    case 0x01: // -62.5
				        iStartFreq -= 1;
				        break;
				    case 0x02: // 0
				    	if(CDetectTVSignalType())
				        	return iStartFreq; // Save
				        else
				        	iStartFreq -= (4*_TUNER_BP); 
				        break;
				    case 0x03: // -62.5              
				    	iStartFreq -= 1;
				        break;
				    case 0x04: // -125
				    	iStartFreq -= 1;
				        break;
				    default:
				    	iStartFreq -= 2;
				        break;
				}
			}
			else
				iStartFreq -= 2;
		}
		
		if(bCLockMode)
		{
            if (bReSearch && (iStartFreq > iStartFreqBase))
                return 1; // Not find channel

		    if (iStartFreq > _MAX_FREQ)
            {
		        iStartFreq = _MIN_FREQ;
                bReSearch  = 1;
            }
		}
		else
		{
            if (bReSearch && (iStartFreq < iStartFreqBase))
                return 1; // Not find channel

			if (iStartFreq < _MIN_FREQ)
            {
				iStartFreq = _MAX_FREQ;
                bReSearch  = 1;
            }
		}
    }
    return 1;  //Not Find Channel
}

#endif

//==========================================================================
//                        CSetTVChannel
//==========================================================================
void CSetTVChannel(const BYTE ucCurrentChannel)
{  
    CLoadTVModeData(ucCurrentChannel);    
       
    kx_CI2CWriteIfPllDM(ucTVType, _TUNER_MUTE_ON, _NORMAL_MODE); // set tv system
    kx_CSetTuner(_ADDR_TUNER, _GET_CH_FREQ());
    CTimerDelayXms(20);

#if (_TV_AFC)
    CurrAFCFreq = _GET_CH_FREQ();
    AFCState    = _TV_AFC_START;
#endif

    CSetTvColor(ucTVType);
    if (bChangeChannel == 1)
    {
	    CVideoSoftReset();
	    CTimerDelayXms(600);
    }
    ucTVSyncFailCount = 251;
    ucAudioState = 1;
}

#if (_TV_AFC)
//==========================================================================
//                        CTVAFC
//==========================================================================
void CTVAFC(void)
{
    BYTE rData = 0;
              
    if (_GET_INPUT_SOURCE() != _SOURCE_VIDEO_TV ||
        ucOsdState != _MI_MENU_NONE || bTVNoSignal == 1 || !GET_AFC_MODE())
       return;
               
    if (_TV_AFC_TIMEOUT == AFCState)
    {
        CLoadTVModeData(ucCurrentChannel);    
        kx_CSetTuner(_ADDR_TUNER, _GET_CH_FREQ());
        AFCState = _TV_AFC_STOP;
    }
    else if(_TV_AFC_STOP == AFCState)
    {
        return;
    } 

    rData = kx_GetTN835CPFData();

    switch(rData & 0x07)
    {
	case 0x00: // -125
    case 0x01: // -62.5
        if (CurrAFCFreq)
            CurrAFCFreq--;
        kx_CSetTuner(_ADDR_TUNER, CurrAFCFreq);
        break;

    case 0x03: // +62.5              
    case 0x04: // +125
        CurrAFCFreq++;
        kx_CSetTuner(_ADDR_TUNER, CurrAFCFreq);
        break;

    case 0x02: // 0
        return;
    }

    AFCState++;
}
#endif //_TV_AFC
#endif // #if(_TV_CHIP == _TN835CPF)

