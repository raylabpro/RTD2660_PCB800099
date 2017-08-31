#include "Core\Header\Include.h"

#if(_TV_CHIP == _TNJ7359_MF)


          /*

#if(JS6AM_TYPE == JS6AM_KOR_FRQ)
 
unsigned int code iAIR_Freq[JS6AM_AIR_CHANNEL_COUNT] =
{         
119	*_TUNER_BP,	//001
101	*_TUNER_BP,	//002
107	*_TUNER_BP,	//003
113	*_TUNER_BP,	//004
123	*_TUNER_BP,	//005
129	*_TUNER_BP,	//006
221	*_TUNER_BP,	//007
227	*_TUNER_BP,	//008
233	*_TUNER_BP,	//009
239	*_TUNER_BP,	//010
245	*_TUNER_BP,	//011
251	*_TUNER_BP,	//012
257	*_TUNER_BP,	//013
517	*_TUNER_BP,	//014
523	*_TUNER_BP,	//015
529	*_TUNER_BP,	//016
535	*_TUNER_BP,	//017
541	*_TUNER_BP,	//018
547	*_TUNER_BP,	//019
553	*_TUNER_BP,	//020
559	*_TUNER_BP,	//021
565	*_TUNER_BP,	//022
571	*_TUNER_BP,	//023
577	*_TUNER_BP,	//024
583	*_TUNER_BP,	//025
589	*_TUNER_BP,	//026
595	*_TUNER_BP,	//027
601	*_TUNER_BP,	//028
607	*_TUNER_BP,	//029
613	*_TUNER_BP,	//030
619	*_TUNER_BP,	//031
625	*_TUNER_BP,	//032
631	*_TUNER_BP,	//033
637	*_TUNER_BP,	//034
643	*_TUNER_BP,	//035
649	*_TUNER_BP,	//036
655	*_TUNER_BP,	//037
661	*_TUNER_BP,	//038
667	*_TUNER_BP,	//039
673	*_TUNER_BP,	//040
679	*_TUNER_BP,	//041
685	*_TUNER_BP,	//042
691	*_TUNER_BP,	//043
697	*_TUNER_BP,	//044
703	*_TUNER_BP,	//045
709	*_TUNER_BP,	//046
715	*_TUNER_BP,	//047
721	*_TUNER_BP,	//048
727	*_TUNER_BP,	//049
733	*_TUNER_BP,	//050
739	*_TUNER_BP,	//051
745	*_TUNER_BP,	//052
751	*_TUNER_BP,	//053
757	*_TUNER_BP,	//054
763	*_TUNER_BP,	//055
769	*_TUNER_BP,	//056
775	*_TUNER_BP,	//057
781	*_TUNER_BP,	//058
787	*_TUNER_BP,	//059
793	*_TUNER_BP,	//060
799	*_TUNER_BP,	//061
805	*_TUNER_BP,	//062
811	*_TUNER_BP,	//063
817	*_TUNER_BP,	//064
823	*_TUNER_BP,	//065
829	*_TUNER_BP,	//066
835	*_TUNER_BP,	//067
841	*_TUNER_BP,	//068
847	*_TUNER_BP,	//069
853	*_TUNER_BP,	//070
859	*_TUNER_BP,	//071
865	*_TUNER_BP,	//072
871	*_TUNER_BP,	//073
877	*_TUNER_BP,	//074
883	*_TUNER_BP,	//075
889	*_TUNER_BP,	//076
895	*_TUNER_BP,	//077
 
}; 
 
unsigned int code iCATV_Freq[JS6AM_CATV_CHANNEL_COUNT + 1] =
{ 
119	*_TUNER_BP,	//001
101	*_TUNER_BP,	//002
107	*_TUNER_BP,	//003
113	*_TUNER_BP,	//004
123	*_TUNER_BP,	//005
129	*_TUNER_BP,	//006
221	*_TUNER_BP,	//007
227	*_TUNER_BP,	//008
233	*_TUNER_BP,	//009
239	*_TUNER_BP,	//010
245	*_TUNER_BP,	//011
251	*_TUNER_BP,	//012
257	*_TUNER_BP,	//013
167	*_TUNER_BP,	//014
173	*_TUNER_BP,	//015
179	*_TUNER_BP,	//016
185	*_TUNER_BP,	//017
191	*_TUNER_BP,	//018
197	*_TUNER_BP,	//019
203	*_TUNER_BP,	//020
209	*_TUNER_BP,	//021
215	*_TUNER_BP,	//022
263	*_TUNER_BP,	//023
269	*_TUNER_BP,	//024
275	*_TUNER_BP,	//025
281	*_TUNER_BP,	//026
287	*_TUNER_BP,	//027
293	*_TUNER_BP,	//028
299	*_TUNER_BP,	//029
305	*_TUNER_BP,	//030
311	*_TUNER_BP,	//031
317	*_TUNER_BP,	//032
323	*_TUNER_BP,	//033
329	*_TUNER_BP,	//034
335	*_TUNER_BP,	//035
341	*_TUNER_BP,	//036
347	*_TUNER_BP,	//037
353	*_TUNER_BP,	//038
359	*_TUNER_BP,	//039
365	*_TUNER_BP,	//040
371	*_TUNER_BP,	//041
377	*_TUNER_BP,	//042
383	*_TUNER_BP,	//043
389	*_TUNER_BP,	//044
395	*_TUNER_BP,	//045
401	*_TUNER_BP,	//046
407	*_TUNER_BP,	//047
413	*_TUNER_BP,	//048
419	*_TUNER_BP,	//049
425	*_TUNER_BP,	//050
431	*_TUNER_BP,	//051
437	*_TUNER_BP,	//052
443	*_TUNER_BP,	//053
449	*_TUNER_BP,	//054
455	*_TUNER_BP,	//055
461	*_TUNER_BP,	//056
467	*_TUNER_BP,	//057
473	*_TUNER_BP,	//058
479	*_TUNER_BP,	//059
485	*_TUNER_BP,	//060
491	*_TUNER_BP,	//061
497	*_TUNER_BP,	//062
503	*_TUNER_BP,	//063
509	*_TUNER_BP,	//064
515	*_TUNER_BP,	//065
521	*_TUNER_BP,	//066
527	*_TUNER_BP,	//067
533	*_TUNER_BP,	//068
539	*_TUNER_BP,	//069
545	*_TUNER_BP,	//070
551	*_TUNER_BP,	//071
557	*_TUNER_BP,	//072
563	*_TUNER_BP,	//073
569	*_TUNER_BP,	//074
575	*_TUNER_BP,	//075
581	*_TUNER_BP,	//076
587	*_TUNER_BP,	//077
593	*_TUNER_BP,	//078
599	*_TUNER_BP,	//079
605	*_TUNER_BP,	//080
611	*_TUNER_BP,	//081
617	*_TUNER_BP,	//082
623	*_TUNER_BP,	//083
629	*_TUNER_BP,	//084
635	*_TUNER_BP,	//085
641	*_TUNER_BP,	//086
647	*_TUNER_BP,	//087
653	*_TUNER_BP,	//088
659	*_TUNER_BP,	//089
665	*_TUNER_BP,	//090
671	*_TUNER_BP,	//091
677	*_TUNER_BP,	//092
683	*_TUNER_BP,	//093
689	*_TUNER_BP,	//094
137	*_TUNER_BP,	//095
143	*_TUNER_BP,	//096
149	*_TUNER_BP,	//097
155	*_TUNER_BP,	//098
161	*_TUNER_BP,	//099
695	*_TUNER_BP,	//0100
701	*_TUNER_BP,	//101
707	*_TUNER_BP,	//102
713	*_TUNER_BP,	//103
719	*_TUNER_BP,	//104
725	*_TUNER_BP,	//105
731	*_TUNER_BP,	//106
737	*_TUNER_BP,	//107
743	*_TUNER_BP,	//108
749	*_TUNER_BP,	//109
755	*_TUNER_BP,	//110
761	*_TUNER_BP,	//111
767	*_TUNER_BP,	//112
773	*_TUNER_BP,	//113
779	*_TUNER_BP,	//114
785	*_TUNER_BP,	//115
791	*_TUNER_BP,	//116
797	*_TUNER_BP,	//117
803	*_TUNER_BP,	//118
809	*_TUNER_BP,	//119
815	*_TUNER_BP,	//120
821	*_TUNER_BP,	//121
827	*_TUNER_BP,	//122
833	*_TUNER_BP,	//123
839	*_TUNER_BP,	//124
845	*_TUNER_BP,	//125
851	*_TUNER_BP,	//126
857	*_TUNER_BP,	//127
863	*_TUNER_BP,	//128
869	*_TUNER_BP,	//129
875	*_TUNER_BP,	//130
881	*_TUNER_BP,	//131
887	*_TUNER_BP,	//132
893	*_TUNER_BP,	//133
899	*_TUNER_BP,	//134
}; 
#endif 
     */
//==========================================================================
//                            kx_CI2CWriteIfPllDM
//==========================================================================
void kx_CI2CWriteIfPllDM(BYTE ucTvType, const bit bTunerMute, const BYTE ucAFTMode)
{
    ucTvType = ucTvType;

    if (ucAFTMode);
	if (bTunerMute);
/*
    // Set TDA9886 B,C data
    switch(ucTvType)
    {
    default:                // Normal sound
    case _TV_PAL_BG    :    // 50Hz PAL B/G
    case _TV_PAL_I     :    // 50Hz PAL I
    case _TV_PAL_DK    :    // 50Hz PAL D/K
        pData[0] = _TDA9886_B_DATA_PAL;
        pData[1] = _TDA9886_C_DATA_PAL;
        break;

    case _TV_SECAM_L   :    // 50Hz SECAM L
        pData[0] = _TDA9886_B_DATA_SECAML;
        pData[1] = _TDA9886_C_DATA_SECAML;
        break;

    case _TV_SECAM_LL  :    // 50Hz SECAM L'
        pData[0] = _TDA9886_B_DATA_SECAMLL;
        pData[1] = _TDA9886_C_DATA_SECAMLL;
        break;

    } // end switch

    if (bTunerMute)
        CMuteOn();
    
    // Set TDA9886 E data
    switch(ucTvType)
    {
    case _TV_PAL_BG    :    // Sound 5.5M  PAL B/G
        pData[2] = _TDA9886_E_DATA_PAL_BG;
        break;

    default:                // Normal sound
    case _TV_PAL_I     :    // Sound 6.0M  PAL I
        pData[2] = _TDA9886_E_DATA_PAL_I;
        break;

    case _TV_PAL_DK    :    // Sound 6.5M  PAL D/K
        pData[2] = _TDA9886_E_DATA_PAL_DK;
        break;

    case _TV_SECAM_L   :    // Sound 6.5M  SECAM L
        pData[2] = _TDA9886_E_DATA_SECAML;
        break;

    case _TV_SECAM_LL  :    // Sound 6.5M  SECAM L'
        pData[2] = _TDA9886_E_DATA_SECAMLL;
        break;

    } // end switch
      
    CI2cWrite(_ADDR_IfPllDM,0x00,3, pData);  // Set TDA9886
*/
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
      pData[5]=_TUNER_LOW_BAND;   // VHFLOW   
   else if(Freq < _VHF_HIGH_BAND)
      pData[5]=_TUNER_MID_BAND;  // VHFHIGH 
   else 
      pData[5]=_TUNER_HIGH_BAND;  //Band select//UHF 

   kx_CWriteTuner(pData);
}

//==========================================================================
//                         CTvAutoSearch
//==========================================================================
/*void CTvAutoSearch(void) small
{
    BYTE ucSound = 0;
    BYTE ucPRG        = 0;
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
//    CEepromSaveVedioColor();    

    kx_CI2CWriteIfPllDM(ucTVType, _TUNER_MUTE_ON, _NORMAL_MODE);
    CTimerDelayXms(8);
    CShowAutoSerachTotal(ucPRG);   // Show search tv channel number
                    
    CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, 0x00); 

	CScalerPageSelect(_PAGE9);		
    CScalerSetByte(_P9_C_LOCK_CONF_B6, 0x6B);

    while(1)
    {
        #if AUTOSCAN_EN
        iFreq = CLockChannel(iFreq+40, 1);

        if(iFreq < 2)
        {
            ucPRG = (ucPRG == 0) ? 0 : (ucPRG - 1);
            break;
        }
        
        CSaveChannelData(iFreq,ucSound,ucPRG);
        
        ucPRG++;
        if(ucPRG > _MAX_CHANNEL_COUNT)
        {
           ucPRG -= 1;
           break;
        }

        CShowAutoSerachTotal(ucPRG);  // Show search tv channel number
		#else
		iFreq = GETFREQVALUE(ucPRG);
		CSaveChannelData(iFreq,ucSound,(ucPRG+1));        //HSL add for channel from 1
		CShowAutoSerachTotal(ucPRG);
		if(ucPRG > JS6AM_CHANNEL_COUNT)
			break;
		ucPRG++;
		#endif

    }  // End while

#if(_CHANGE_CHANNEL_MTD == _CHANGE_CHANNEL_M2)
    {
        BYTE ucChannelCount = 0;

        ucPRG++;

        for(ucChannelCount = ucPRG; ucChannelCount < _MAX_CHANNEL_COUNT; ucChannelCount++)
        {
            CSaveChannelData((WORD)_MIN_FREQ | 0x8000, ucSound, ucChannelCount);
        }

    }
#endif

    // Save search channel number
    pData[0] = ucPRG;
    CI2cWrite(_TV_MAX_CHANNEL_EEPROM_ADDR, _MAX_CHANNEL_ADDR, 1, pData);
    CSetTVChannel(0);

//    bChangeChannel = 1;

//	CTimerReactiveTimerEvent(SEC(GET_OSDTIMEOUT()), COsdFxExitEvent);

    kx_CI2CWriteIfPllDM(ucTVType, _TUNER_MUTE_OFF, _NORMAL_MODE); // set tv system
    ucCurrState = _SEARCH_STATE;                  
//    CModeResetTVMode();   
}
*/

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
//    CEepromSaveVedioColor();    

    kx_CI2CWriteIfPllDM(ucTVType, _TUNER_MUTE_ON, _NORMAL_MODE);
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

    kx_CI2CWriteIfPllDM(ucTVType, _TUNER_MUTE_OFF, _NORMAL_MODE); // set tv system
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

    kx_CI2CWriteIfPllDM(ucTVType, _TUNER_MUTE_ON, _NORMAL_MODE);
    CTimerDelayXms(100);

    if (ucSatrtSearchFreq > _MAX_FREQ)
        ucSatrtSearchFreq = _MAX_FREQ;
    else if(ucSatrtSearchFreq < _MIN_FREQ)
        ucSatrtSearchFreq = _MIN_FREQ;


    if (bSearchAction)
        iFreq = CLockChannel(ucSatrtSearchFreq + 40, 1);
    else
        iFreq = CLockChannel(ucSatrtSearchFreq - 40, 0);

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

    kx_CI2CWriteIfPllDM(ucTVType, _TUNER_MUTE_OFF, _NORMAL_MODE);
   // CModeResetTVMode();
    ucCurrState = _SEARCH_STATE;
}

//==========================================================================
//  bCLockMode --> 1: lock up         0 : lock down
//==========================================================================
WORD CLockChannel(WORD iStartFreq, const bit bCLockMode) small
{
    BYTE f            = 0;
    BYTE rData        = 0;
    BYTE LowLevel_CH  = 0;
    BYTE count        = 0;
    WORD freq         = 0;
    WORD iStartFreqBase = iStartFreq;
    BYTE ucPattCount  = 0;

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
        
        // Show search channel state 
        CShowAutoSearchSliderInOSD((iStartFreq));                         

        rData = kx_CReadIfPllDM();

        switch((rData >> 1) & 0x0f)
        {
        case 7:
            if (bCLockMode) // Search up
            {
                f = 1;
                iStartFreq++;
            }
            else            // Search down
            {
                count++;
                f |= 0x0a;
            }
            break;

        case 8:
            if (bCLockMode) // Search up
            {
                count++;
                f |= 0x0a;
            }
            else            // Search down
            {
                f = 1;
                iStartFreq--;
            }
            break; 

        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            f |= 0x0a;
            break; 
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            f |= 0x10;
            break; 
        case 0:
        case 15:
            f |= 0x04;
            freq = iStartFreq;
            break;
        }

		if (0x1b==f || 0x1a==f) 
		{
			LowLevel_CH++;
			freq = iStartFreq;
		}
		else
            LowLevel_CH = 0;

        if((rData & 0xc0) != 0xc0)
        {
            f     = 0;
   	        count = 0;
      	  //  i    += 4;    
        }
        else if((f==0x1f || LowLevel_CH>4) && ((count > 3 && bCLockMode) || (count > 0 && !bCLockMode)) )
        {
            kx_CSetTuner(_ADDR_TUNER, freq);
			CTimerDelayXms(200);
            CVideoSoftReset();
            CTimerDelayXms(10);

            switch(CDetectTVSignalType())
            {
            case 0:  // MODE_NOSIGNAL
                LowLevel_CH = 0;  // eric add
                f = 0;
                count = 0;
                break;

            case 1:  // 
                return freq;
            }
        }

        if (bCLockMode) // Search up
        {
            iStartFreq++;
            if (iStartFreq > _MAX_FREQ)
                return 1;
        }
        else            // Search down
        {
            iStartFreq--;
            if (iStartFreq < _MIN_FREQ)
                return 1;
        }
    }
    return 1;  //Not Find Channel
}

//==========================================================================
//                        CSetTVChannel
//==========================================================================
void CSetTVChannel(const BYTE ucCurrentChannel)
{  
    CLoadTVModeData(ucCurrentChannel);    
        
    kx_CI2CWriteIfPllDM(ucTVType, _TUNER_MUTE_ON, _NORMAL_MODE); // set tv system
    CLoadTVModeData(ucCurrentChannel);    
    kx_CSetTuner(_ADDR_TUNER, _GET_CH_FREQ());
    CTimerDelayXms(20);
    ucAudioState = 1;

    CSetTvColor(ucTVType);
    if (bChangeChannel == 1)
    {
	    CVideoSoftReset();
	    CTimerDelayXms(600);
    }
    ucTVSyncFailCount = 251;
}


#endif // #if(_TV_CHIP == _TNJ7359_MF)

