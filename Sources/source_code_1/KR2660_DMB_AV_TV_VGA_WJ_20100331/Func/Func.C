#include "Core\Header\Include.h"

//__________________________________________________________________________
//
//                         Audio func
//__________________________________________________________________________

#if(AUDIO_TYPE == _AUDIO_PWM)
//==========================================================================
//                          CMuteOn
//==========================================================================
void CMuteOn(void)
{                                    
    // Set Mute
    if(_VOLUME_INV)        
		CSetPWM(bVOLUME_PWM,0xff);
    else                    
		CSetPWM(bVOLUME_PWM,0x00);

    bMUTE = _MUTE_ON;
 //   bAUDIO_PWR =  AUDIO_OFF;

}

//==========================================================================
//                          CMuteOff
//==========================================================================
void CMuteOff(void)
{
    bMUTE = _MUTE_OFF;
  //  bAUDIO_PWR =  AUDIO_ON;

}

//==========================================================================
//                               CSetVolume
//==========================================================================
void CSetVolume(void)
{
    WORD iVolume;
                   
    if((GET_VOLUME() == 0) || (GET_AUDIO_MUTE() || ( ucCurrState == _NOSIGNAL_STATE)))
    {
       //  if(_VOLUME_INV)         CSetPWM(bVOLUME_PWM,0xff);
         //else                    CSetPWM(bVOLUME_PWM,0x00);

         CMuteOn();
         return;
    }
                   
    CMuteOff();
                                                            
    iVolume = (WORD)(_MAX_VOLUME - _MIN_VOLUME) * GET_VOLUME() / 100;

    if(_VOLUME_INV == 0)
        iVolume = _MAX_VOLUME - iVolume;
    else
        iVolume = _MIN_VOLUME + iVolume;
      
    CSetPWM(bVOLUME_PWM,iVolume);
}
#endif    // #if(AUDIO_TYPE == _AUDIO_PWM)

#if(AUDIO_TYPE == _AUDIO_SC7313)

//==========================================================================
//                           MUTE_ON
//==========================================================================
void CMuteOn(void)
{ 

	bMUTE = _MUTE_ON;


}

//==========================================================================
//                           CMuteOff
//==========================================================================
void CMuteOff(void)
{

	bMUTE = _MUTE_OFF;
}

//==========================================================================
//                             CSetVolume
//==========================================================================
void CSetVolume(void)
{      
    if((GET_VOLUME() == 0) || (GET_AUDIO_MUTE()) || ( ucCurrState == _NOSIGNAL_STATE))
    {
         CMuteOn();
         return;
    }

#if(_VIDEO_TV_SUPPORT)
 #if(_IF_PLL_DE_CHIP == _IF_PLL_DE_1338 || _IF_PLL_DE_CHIP == _IF_PLL_DE_135X)
     if (_SOURCE_VIDEO_TV == _GET_INPUT_SOURCE() && bTVNoSignal == 1)
        return;
 #endif
#endif
     CSetSc7313Volume(GET_VOLUME());
#if (_SOUND_PROCESSOR)
     CSetAudioProcessor(stAudioData.Balance, stAudioData.Bass, stAudioData.Treble);
#else
     CSetAudioProcessor(50, 50, 50);
#endif      

     if (bMUTE)
         CMuteOff();

}

#endif          //#if(AUDIO_TYPE == _AUDIO_SC7313)

//==========================================================================
//                         CInitSoundChannel 
//==========================================================================
void CInitSoundChannel(BYTE ucChannel)
{
     CMuteOn();
       
     switch(ucChannel)
     {
#if(_VGA_SUPPORT)
         case _SOURCE_VGA:
   #if(AUDIO_TYPE == _AUDIO_SC7313)
             CSelect7313SoundChannel(_7313_VGA_CHENNEL);
   #elif(AUDIO_TYPE == _AUDIO_PWM)  
             _AUDIO_A = 1;
             _AUDIO_B = 0;                     
   #endif
             break;
                              
         case _SOURCE_DVI:              
   #if(AUDIO_TYPE == _AUDIO_SC7313)
             CSelect7313SoundChannel(_7313_DVI_CHENNEL);
   #elif(AUDIO_TYPE == _AUDIO_PWM) 
             _AUDIO_A = 1;
             _AUDIO_B = 0; 
   #endif
             break;
#endif
		case _SOURCE_YPBPR:     
		 #if(AUDIO_TYPE == _AUDIO_SC7313)
            CSelect7313SoundChannel(_7313_YPBPR_CHENNEL);
         #elif(AUDIO_TYPE == _AUDIO_PWM) 
            _AUDIO_A = 0;
            _AUDIO_B = 0;
         #endif

             break;

             
		case _SOURCE_YPBPR1:     
		 #if(AUDIO_TYPE == _AUDIO_SC7313)
            CSelect7313SoundChannel(_7313_YPBPR_CHENNEL);
         #elif(AUDIO_TYPE == _AUDIO_PWM) 
            _AUDIO_A = 0;
            _AUDIO_B = 0;
         #endif

             break;

#if(_VIDEO_SUPPORT)
         case _SOURCE_VIDEO_AV:
   #if(AUDIO_TYPE == _AUDIO_SC7313)
             CSelect7313SoundChannel(_7313_AV_CHENNEL);
   #elif(AUDIO_TYPE == _AUDIO_PWM) 

             _AUDIO_A = 0;
             _AUDIO_B = 1;    
   #endif
             break;

	  case _SOURCE_VIDEO_SV:
#if(AUDIO_TYPE == _AUDIO_SC7313)
		  CSelect7313SoundChannel(_7313_AV_CHENNEL);
#elif(AUDIO_TYPE == _AUDIO_PWM) 

		  _AUDIO_A = 0;
		  _AUDIO_B = 0;    
#endif
          break;


#endif
  		 case _SOURCE_HDMI:
         case _SOURCE_VIDEO_YUV:
   #if(AUDIO_TYPE == _AUDIO_SC7313)
             CSelect7313SoundChannel(_7313_HDMI_CHENNEL);  // Only for PT2314
   #elif(AUDIO_TYPE == _AUDIO_PWM)  
             _AUDIO_A = 0;
             _AUDIO_B = 0;                      
   #endif
        break;

#if(_VIDEO_TV_SUPPORT)
         case _SOURCE_VIDEO_TV:        
   #if(AUDIO_TYPE == _AUDIO_SC7313)
             CSelect7313SoundChannel(_7313_TV_CHENNEL);
   #elif(AUDIO_TYPE == _AUDIO_PWM)  
             _AUDIO_A = 1;
             _AUDIO_B = 1;                      
   #endif
             break;
#endif

     }
}


//==========================================================================
//                          CGetCurrSourcePos
//==========================================================================
BYTE CGetCurrSourcePos(void)
{
    if     (_GET_INPUT_SOURCE() == _SOURCE_0_TYPE)   return 0;
    else if(_GET_INPUT_SOURCE() == _SOURCE_1_TYPE)   return 1;
    else if(_GET_INPUT_SOURCE() == _SOURCE_2_TYPE)   return 2;
    else if(_GET_INPUT_SOURCE() == _SOURCE_3_TYPE)   return 3;
    else if(_GET_INPUT_SOURCE() == _SOURCE_4_TYPE)   return 4;
    else if(_GET_INPUT_SOURCE() == _SOURCE_5_TYPE)   return 5;
    else if(_GET_INPUT_SOURCE() == _SOURCE_6_TYPE)   return 6;
    else if(_GET_INPUT_SOURCE() == _SOURCE_7_TYPE)   return 7;
    else if(_GET_INPUT_SOURCE() == _SOURCE_8_TYPE)   return 8;
    else if(_GET_INPUT_SOURCE() == _SOURCE_9_TYPE)   return 9;
    else if(_GET_INPUT_SOURCE() == _SOURCE_10_TYPE)  return 10;

    return _NORMAL_SOURCE;
}

//==========================================================================
//                          CSetCurrSource   
//==========================================================================
void CSetCurrSource(const BYTE ucCurrSource)
{
    switch(ucCurrSource)
    {
    case 0:    _SET_INPUT_SOURCE(_SOURCE_0_TYPE);    break;
    case 1:    _SET_INPUT_SOURCE(_SOURCE_1_TYPE);    break;
    case 2:    _SET_INPUT_SOURCE(_SOURCE_2_TYPE);    break;
    case 3:    _SET_INPUT_SOURCE(_SOURCE_3_TYPE);    break;
    case 4:    _SET_INPUT_SOURCE(_SOURCE_4_TYPE);    break;
    case 5:    _SET_INPUT_SOURCE(_SOURCE_5_TYPE);    break;
    case 6:    _SET_INPUT_SOURCE(_SOURCE_6_TYPE);    break;
    case 7:    _SET_INPUT_SOURCE(_SOURCE_7_TYPE);    break;
    case 8:    _SET_INPUT_SOURCE(_SOURCE_8_TYPE);    break;
    case 9:    _SET_INPUT_SOURCE(_SOURCE_9_TYPE);    break;
    case 10:   _SET_INPUT_SOURCE(_SOURCE_10_TYPE);   break;
    }
}

//==========================================================================
//                           bCurrSourceSupport
//==========================================================================
bit bCurrSourceSupport(const BYTE ucSource)
{
    BYTE ucSourceTemp;

    switch(ucSource)
    {
    case 0:   ucSourceTemp = _SOURCE_0_TYPE;     break;
    case 1:   ucSourceTemp = _SOURCE_1_TYPE;     break;
    case 2:   ucSourceTemp = _SOURCE_2_TYPE;     break;
    case 3:   ucSourceTemp = _SOURCE_3_TYPE;     break;
    case 4:   ucSourceTemp = _SOURCE_4_TYPE;     break;
    case 5:   ucSourceTemp = _SOURCE_5_TYPE;     break;
    case 6:   ucSourceTemp = _SOURCE_6_TYPE;     break;
    case 7:   ucSourceTemp = _SOURCE_7_TYPE;     break;
    case 8:   ucSourceTemp = _SOURCE_8_TYPE;     break;
    case 9:   ucSourceTemp = _SOURCE_9_TYPE;     break;
    case 10:  ucSourceTemp = _SOURCE_10_TYPE;    break;
    }

    switch(ucSourceTemp)
    {
#if (_VGA_SUPPORT)
    case _SOURCE_VGA:          return 1;
#endif

#if (_TMDS_SUPPORT)
    case _SOURCE_DVI:          return 1;
#endif

#if (_VIDEO_AV_SUPPORT)
    case _SOURCE_VIDEO_AV:     return 1;
#endif

#if (_VIDEO_SV_SUPPORT)
    case _SOURCE_VIDEO_SV:     return 1;
#endif

#if (_VIDEO_YUV_SUPPORT)
    case _SOURCE_VIDEO_YUV:    return 1;
#endif

#if (_VIDEO_TV_SUPPORT)
    case _SOURCE_VIDEO_TV:     return 1;
#endif

#if (_VIDEO_SCART_SUPPORT)
    case _SOURCE_VIDEO_SCART:  return 1;
#endif

#if (_HDMI_SUPPORT)
    case _SOURCE_HDMI:         return 1;
#endif

#if (_YPBPR_SUPPORT)
    case _SOURCE_YPBPR:        return 1;
#endif

#if (_YPBPR1_SUPPORT)
    case _SOURCE_YPBPR1:        return 1;
#endif
    }

    return 0;
}

//==========================================================================
//                          bChangeSource
//==========================================================================
bit bChangeSource(void)
{
    bit bSourceSelect = 0;
    BYTE i;

    for (i = (CGetCurrSourcePos() + 1); i < _INPUT_PORT_NUM; i++)
    {
         if (bCurrSourceSupport(i))
         {
             bSourceSelect = 1;
             break;
         }
    }

    if (0 == bSourceSelect)  // Source not change
    {
        for (i = 0; i < CGetCurrSourcePos(); i++)
        {
            if (bCurrSourceSupport(i))
            {
                bSourceSelect = 1;
                break;
            }
         }
    }


    if (bSourceSelect && i != CGetCurrSourcePos())
    {
        CSetCurrSource(i);
        CInitInputSource();
        return 1;
    }

    return 0;
}


//==========================================================================
//                          CInitInputSource
//==========================================================================
void CInitInputSource(void)
{
#if(_HDMI_SUPPORT && _HDCP_SUPPORT == _ON && _HDMI_HOT_PLUG_OPTION)
	bDVIDetect = 0;
	
	if(_GET_INPUT_SOURCE()==_SOURCE_HDMI || _GET_INPUT_SOURCE()==_SOURCE_DVI)
	{
		bHot_Plug = _HOT_PLUG_LOW;
		bHot_Plug2 = _HOT_PLUG_LOW;    	
		CTimerDelayXms(100);   //20070714 gary for HDMI compatibility problem
		bHot_Plug = _HOT_PLUG_HI;
		bHot_Plug2 = _HOT_PLUG_HI;    	
	}
	else
	{
		//bHot_Plug = _HOT_PLUG_HI;
		//bHot_Plug2 = _HOT_PLUG_HI;    	
		bHot_Plug = _HOT_PLUG_LOW;
		bHot_Plug2 = _HOT_PLUG_LOW;    	
		
	}
#endif

    TUNER_PWR_OFF();

#if(OEM_TYPE == RTD2660_VGA_AV_MP5_DMB) //VGA+AV1+MP5+DMB
    switch(_GET_INPUT_SOURCE()) 
    {
      //VGA    
             #if(_VGA_SUPPORT)
              case _SOURCE_VGA:
          	 bAML8613_PWR = AML8613_OFF;
          	 bDTV_PWR = DTV_OFF;
                  break;
             #endif
      //AV1
             #if(_VIDEO_AV_SUPPORT)
              case _SOURCE_VIDEO_AV:
                  kx_CSelectVideoChannel(_AV_CHANNEL, 0);
          	 bAML8613_PWR = AML8613_OFF;
          	 bDTV_PWR = DTV_OFF;
                  break;
             #endif
     //MP5
             #if(_VIDEO_SV_SUPPORT)
              case _SOURCE_VIDEO_SV:
                  kx_CSelectVideoChannel(_SV_CHANNEL, 0);
          		 bAML8613_PWR = AML8613_ON;
          		 bDTV_PWR = DTV_OFF;
                  break;
             #endif
      //DMB
             #if(_VIDEO_TV_SUPPORT)
              case _SOURCE_VIDEO_TV:
                  kx_CSelectVideoChannel(_TV_CHANNEL, 0);
          	 bAML8613_PWR = AML8613_OFF;	
          	 bDTV_PWR = DTV_ON;
                  if (ucCurrState != _SOURCE_CHANGE_STATE && ucOsdEventMsg != _CHANGE_SOURCE_MSG)
                      CInitTV();
                  break;
             #endif
			 
       //UNDER NO USE   
            #if(_VIDEO_YUV_SUPPORT)
              case _SOURCE_VIDEO_YUV:
                  break;
            #endif
          
            #if(_VIDEO_SCART_SUPPORT)
              case _SOURCE_VIDEO_SCART:break;                  
            #endif 
            #if(_HDMI_SUPPORT == _ON)
              case _SOURCE_HDMI:break;
            #endif
            #if(_YPBPR_SUPPORT)
              case _SOURCE_YPBPR: break;
             #endif
            #if(_YPBPR1_SUPPORT)
              case _SOURCE_YPBPR1: bYpbprPort = YPBPR2_ON; break;
            #endif

    }  
	
#elif(OEM_TYPE == RTD2660_VGA_AV_MP5)//VGA+AV1+MP5
    switch(_GET_INPUT_SOURCE()) 
    {
      //VGA    
             #if(_VGA_SUPPORT)
              case _SOURCE_VGA:
                  break;
             #endif
      //AV1
             #if(_VIDEO_AV_SUPPORT)
              case _SOURCE_VIDEO_AV:
                  kx_CSelectVideoChannel(_AV_CHANNEL, 0);
                  break;
             #endif
     //MP5
             #if(_VIDEO_SV_SUPPORT)
              case _SOURCE_VIDEO_SV:
                  kx_CSelectVideoChannel(_SV_CHANNEL, 0);
                  break;
             #endif
      //TV
             #if(_VIDEO_TV_SUPPORT)
              case _SOURCE_VIDEO_TV:
                  kx_CSelectVideoChannel(_TV_CHANNEL, 0);
                  if (ucCurrState != _SOURCE_CHANGE_STATE && ucOsdEventMsg != _CHANGE_SOURCE_MSG)
                      CInitTV();
                  break;
             #endif
			 
       //UNDER NO USE   
            #if(_VIDEO_YUV_SUPPORT)
              case _SOURCE_VIDEO_YUV:
                  break;
            #endif
          
            #if(_VIDEO_SCART_SUPPORT)
              case _SOURCE_VIDEO_SCART:break;                  
            #endif 
            #if(_HDMI_SUPPORT == _ON)
              case _SOURCE_HDMI:break;
            #endif
            #if(_YPBPR_SUPPORT)
              case _SOURCE_YPBPR: break;
             #endif
            #if(_YPBPR1_SUPPORT)
              case _SOURCE_YPBPR1: bYpbprPort = YPBPR2_ON; break;
            #endif

    }
#endif
    CInitSoundChannel(_GET_INPUT_SOURCE());

#if(_VIDEO_TV_SUPPORT)
 #if(_SLEEP_FUNC)
    _SET_POWER_DOWN_TIME(0);
    ucAutoPowerDownTime = 0xff;
    CEepromSaveTvData();
 #endif
#endif

#if(_DE_INTERLACE_SUPPORT == _ON && _DE_INTERLACE_TEST_OPTION==_ENABLE)
    if (bSourceVideo())
        bDIstatus = 1;
    else
        bDIstatus = 0; 
#endif
}
//==========================================================================
void DoSetBackColor(void)
{
	BYTE r = 0;
	BYTE g = 0;
	BYTE b = 0;

	switch(GET_BACKGROUNDCOLOE())
	{
	 	case _RED:			r = 0xFF;					break;
		case _GREEN:		g = 0xFF;					break;
		case _BLUE:			
		default:
							b = 0xFF;					break;
	}

	CAdjustBackgroundColor(r, g, b);
}


BYTE CGetInputSourceNum(BYTE ucInputSource)
{
    switch(ucInputSource)
    {
        default:
        case _SOURCE_VGA:
            return 0;

#if(_TMDS_SUPPORT || _HDMI_SUPPORT)
        case _SOURCE_DVI:
        case _SOURCE_HDMI:
            return 1;
#endif

#if(_VIDEO_SUPPORT)
        case _SOURCE_VIDEO_AV:
        case _SOURCE_VIDEO_SV:
        case _SOURCE_VIDEO_YUV:
        case _SOURCE_VIDEO_TV:
        case _SOURCE_VIDEO_SCART:
            return 2;
#endif

        case _SOURCE_YPBPR:
        case _SOURCE_YPBPR1:
            return 3;
   }
}
//--------------------------------------------------

void MemoryCpy(BYTE *Obj,BYTE *Src,BYTE ucCnt)
{
	while(ucCnt--)
	{
		*Obj++ = *Src++;
	}
}
//------------------------------------------------------------------------


void SetPanelLR(void)
{
	if(GET_LR_SWAP())
		bPanel_LR = 0;
	else
		bPanel_LR = 1;
}
//------------------------------------------------------------------------
void SetPanelUD(void)
{
	bPanel_UD = GET_UD_SWAP();
}

//------------------------------------------------------------------------
BYTE code tFMTable[][5] = 
{
//	D0	D1	D2	D3	D4
	{0,	0,	0,	0,	0},	// 0x00
	{1,	0,	0,	0,	0},	// 0x01
	{0,	0,	0,	0,	1},	// 0x02
	{0,	1,	0,	0,	0},	// 0x03
	{1,	0,	0,	0,	1},	// 0x04
	{1,	1,	0,	0,	0},	// 0x05
	{0,	1,	0,	0,	1},	// 0x06
	{0,	0,	1,	0,	0},	// 0x07
	{1,	1,	0,	0,	1},	// 0x08
	{1,	0,	1,	0,	0},	// 0x09
	{0,	0,	1,	0,	1},	// 0x0a
	{0,	1,	1,	0,	0},	// 0x0b
	{1,	0,	1,	0,	1},	// 0x0c
	{1,	1,	1,	0,	0},	// 0x0d
	{0,	1,	1,	0,	1},	// 0x0e
	{1,	1,	1,	0,	1},	// 0x0f
	{1,	1,	1,	1,	1},	// 0x10


};
//------------------------------------------------------------------------

void SetFM(void)
{
	BYTE ucFMIndex = 0;
	bD0 = tFMTable[ucFMIndex][0];
	bD1 = tFMTable[ucFMIndex][1];
	bD2 = tFMTable[ucFMIndex][2];
	bD3 = tFMTable[ucFMIndex][3];
	bD4 = tFMTable[ucFMIndex][4];

}
//-----------------------------------------------------------------------

void CInitFM(void)
{
//	bFMPower = 0;	
	IE = 0;
	Delay5us();
	Delay5us();
	CI2cWriteFM(0,0x5e,0x00);
	CI2cWriteFM(1,0x03,0xB8);
	CI2cWriteFM(2,0x27,0xD3);
	CI2cWriteFM(3,0x01,0xC5);
	CI2cWriteFM(4,0x4E,0x03);
	CI2cWriteFM(5,0x9C,0xA0);///Adjust the Fre
	CI2cWriteFM(6,0x88,0x06);//Adjust the Fre
	CI2cWriteFM(7,0x59,0x2C);
	CI2cWriteFM(8,0x08,0x81);
	CI2cWriteFM(9,0x02,0x46);
	CI2cWriteFM(10,0x00,0x68);
	CI2cWriteFM(11,0x40,0x18);
	CI2cWriteFM(12,0x10,0x83);
	
	CI2cWriteFM(13,0x06,0x02);
	CI2cWriteFM(14,0xE6,0xDB);
	CI2cWriteFM(15,0x00,0x03);
	CI2cWriteFM(16,0x00,0x00);
	CI2cWriteFM(17,0x00,0x00);
	CI2cWriteFM(18,0x00,0x00);
	CI2cWriteFM(19,0x00,0x00);
	IE      = 0x8a;                        
}


void CSetFMFreq(BYTE ucFreq)
{
    WORD RFFreq   = 0;
	switch(ucFreq)
	{
    case 0x00: // FM off
        RFFreq   = 0;
        break;

    case 0x01: // FM off
        RFFreq   = 0;
        break;

    case 0x02: // 87.7
        RFFreq   = 877;
        break;

    case 0x03: // 87.9
        RFFreq   = 879;
        break;

    case 0x04: // 88.0
        RFFreq   = 880;
        break;

    case 0x05: // 88.1
        RFFreq   = 881;
        break;

    case 0x06: // 88.2
        RFFreq   = 882;
        break;

     case 0x07: // 88.3
        RFFreq   = 883;
        break;

    case 0x08: // 88.4
        RFFreq   = 884;
        break;

    case 0x09: // 88.5
        RFFreq   = 885;
        break;

    case 0x0A: // 88.6
        RFFreq   = 886;
        break;

    case 0x0B: // 88.7
        RFFreq   = 887;
        break;

    case 0x0C: // 88.8
        RFFreq   = 888;
        break;

    case 0x0D:  // 88.9
        RFFreq   = 889;
        break;

    case 0x0E: // 89.0
        RFFreq   = 890;
        break;

    case 0x0F: // 89.1
        RFFreq   = 891;
        break;

    case 0x10: // 89.2
        RFFreq   = 892;
        break;
		
    case 0x11: // 89.4
        RFFreq   = 894;
        break;		
	}
	CInitFM();
	IE      = 0;                        
 	AS6300_Set_Freq(RFFreq);   
	IE      = 0x8a;     
	FMAudioTran();
}
void FMAudioTran(void)
{
		if(0x01!=_GET_FM_STATE())  
		 {
			 if(_VOLUME_INV)		 
			 	CSetPWM(bVOLUME_PWM,0x00);
			 else					 
			 	CSetPWM(bVOLUME_PWM,0xFF);
		 }
	        else
		 {
		        CSetVolume();
		 }
}


