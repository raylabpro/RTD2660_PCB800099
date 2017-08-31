//----------------------------------------------------------------------------------------------------
// ID Code      : Source.c No.0003
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#define __SOURCE__

#include "Core\Header\Include.h"

/**
 * CSourceHandler
 * Scan all input port and select active port
 * return TRUE if there is any active port available and selected
 * @param <none>
 * @return {TRUE/FALSE}
 *
*/
bit CSourceHandler(void)
{
  #if(_HDMI_SUPPORT == _ON)
	ucHDMIMode = _HM_OTHER;
  #endif

    if(CSourceScanInputPort(CGetSourcePortType(_GET_INPUT_SOURCE())))
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Return source input port type
// Input Value  : 
// Output Value : 
//--------------------------------------------------
BYTE CGetSourcePortType(BYTE ucSource)
{
    switch(ucSource)
    {
#if(_VGA_SUPPORT)
    case _SOURCE_VGA:         return _SOURCE_VGA_PORT_TYPE;
#endif

#if(_TMDS_SUPPORT)
    case _SOURCE_DVI:         return _SOURCE_DVI_PORT_TYPE;
#endif

#if(_HDMI_SUPPORT)
    case _SOURCE_HDMI:        return _SOURCE_HDMI_PORT_TYPE;
#endif
               
#if(_YPBPR_SUPPORT)
    case _SOURCE_YPBPR:       return _SOURCE_YPBPR_PORT_TYPE;
#endif

#if(_YPBPR1_SUPPORT)
    case _SOURCE_YPBPR1:       return _SOURCE_YPBPR1_PORT_TYPE;
#endif
    default:                  break;
    }

    return _NO_PORT;
}

//--------------------------------------------------
bit bSourceVideo(void)
{
    if(_GET_INPUT_SOURCE() == _SOURCE_VIDEO_AV
    || _GET_INPUT_SOURCE() == _SOURCE_VIDEO_SV
    || _GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
      return 1;

    return 0;
}

/**
 * CSourceScanInputPort
 * Initial input port setting when firmware startup
 * @param <none>
 * @return {none}
 *
*/  /*
void CSourceInitialInputPort(void)
{
    BYTE cnt;

    SET_INPUTSYNC_TYPE(_NO_SYNC_STATE);

    for(cnt=0;cnt<_INPUT_PORT_MAX;cnt++)
    {
        CLR_INPUTPORT_SELECT(cnt);
        switch(GET_INPUTPORT_TYPE(stSystemData.InputSource))
        {
            case _DSUB_A0_PORT:
                SET_INPUTSOURCE_TYPE(_SOURCE_VGA);
                break;

        #if (_HDMI_SUPPORT == _ON)
            case _HDMI_PORT:
        #endif
        #if(_TMDS_SUPPORT == _ON)           
            case _DVI_PORT:
        #endif  
                SET_INPUTSOURCE_TYPE(_SOURCE_DVI);
                    break;
                
            case _YPBPR_A0_PORT:
                SET_INPUTSOURCE_TYPE(_SOURCE_YPBPR);
                    break;
                
            case _VIDEO_AV_PORT:
            case _VIDEO_SV_PORT:

            case _VIDEO_TV_PORT:
            case _VIDEO_YCBCR_PORT:
            case _VIDEO_SCART_PORT:
                SET_INPUTSOURCE_TYPE(_SOURCE_VIDEO8);
                break;
                        
        }
    }
} */

/**
 * CSourceScanInputPort
 * Scan if there is an available port
 * Check connect pin and scan all input port to obtain if the signal is available
 * @param <none>
 * @return {none}
 *
*/
bit CSourceScanInputPort(BYTE ucSource)
{
    BYTE cnt = _GET_INPUT_SOURCE();
    
    switch (ucSource)
    {
#if(_YPBPR_SUPPORT == _ON)
    case _YPBPR_A0_PORT:
#endif
    case _DSUB_A0_PORT:
        if (CSourceScanInputPortVGA(_ANALOG_SOURCE_0))
        {
            if ((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4))
            {
                bHsyncSelection = 1;
            }
            else
            {
                bHsyncSelection = 0;
            }
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
        break;

#if(_YPBPR_SUPPORT == _ON)
    case _YPBPR_A1_PORT:
#endif
    case _DSUB_A1_PORT:
        if (CSourceScanInputPortVGA(_ANALOG_SOURCE_1))
        {
            if ((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4))
            {
                bHsyncSelection = 1;
            }
            else
            {
                bHsyncSelection = 0;
            }
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
        break;

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
    case _DVI_PORT:
    case _DVI_D0_PORT:
    case _DVI_D1_PORT:
    #if(_DVI_DE_ONLY_SUPPORT == _ON)
        if (CSourceScanInputPortDVI(_DE_ONLY_ON))
        {
            return _TRUE;
        }
    #endif
        if (CSourceScanInputPortDVI(_DE_ONLY_OFF))
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }

    case _HDMI_PORT:
    case _HDMI_D0_PORT:
    case _HDMI_D1_PORT:
        if (CSourceScanInputPortDVI(_DE_ONLY_OFF))
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    
    case _DVI_I_A0_PORT:
    #if(_DVI_I_SOURCE_SWITCH_SUPPORT == _ON)
        if (GET_DVI_I_SOURCE_SWITCH())
    #endif
        {
    #if(_DVI_DE_ONLY_SUPPORT == _ON)
            if (CSourceScanInputPortDVI(_DE_ONLY_ON))
            {
                return _TRUE;
            }
    #endif
            if (CSourceScanInputPortDVI(_DE_ONLY_OFF))
            {
                return _TRUE;
            }
            else if (CSourceScanInputPortVGA(_ANALOG_SOURCE_0))
            {
                if ((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4))
                {
                    bHsyncSelection = 1;
                }
                else
                {
                    bHsyncSelection = 0;
                }
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
        }
    #if(_DVI_I_SOURCE_SWITCH_SUPPORT == _ON)
        else
        {
            if (CSourceScanInputPortVGA(_ANALOG_SOURCE_0))
            {
                if ((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4))
                {
                    bHsyncSelection = 1;
                }
                else
                {
                    bHsyncSelection = 0;
                }
                return _TRUE;
            }
    #if(_DVI_DE_ONLY_SUPPORT == _ON)
            else if (CSourceScanInputPortDVI(_DE_ONLY_ON))
            {
                return _TRUE;
            }
    #endif
            else if (CSourceScanInputPortDVI(_DE_ONLY_OFF))
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
        }
    #endif
        //break;
#endif//((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
    
    default:
        break;
    }
} 


//--------------------------------------------------
// Description  : Scan VGA input port to obtain if the signal is available
// Input Value  : Select analog source 0 or 1
// Output Value : Return _TRUE if the signal is available
//--------------------------------------------------
bit CSourceScanInputPortVGA(BYTE ucAnalogSource)
{
//  BYTE    ucSearchIndex;  
    BYTE cnt, synctypetemp = _NO_SYNC_STATE;;

    if(ucAnalogSource == _ANALOG_SOURCE_0)  
        CScalerSetBit(_IPH_ACT_WID_H_16, ~(_BIT6 | _BIT5 | _BIT4), ((_ADC0_INPUT_SWAP_RG << 4) | (_ADC0_INPUT_SWAP_RB << 5)| (_ADC0_INPUT_SWAP_GB << 6)));
    else if(ucAnalogSource == _ANALOG_SOURCE_1)
        CScalerSetBit(_IPH_ACT_WID_H_16, ~(_BIT6 | _BIT5 | _BIT4), ((_ADC1_INPUT_SWAP_RG << 4) | (_ADC1_INPUT_SWAP_RB << 5)| (_ADC1_INPUT_SWAP_GB << 6)));

    CScalerPageSelect(_PAGE0);
    if(ucAnalogSource == _ANALOG_SOURCE_0 || ucAnalogSource == _DIGISTAL_SOURCE_0) 
    {
        CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), (_HSYNC_SOURCE_SWAP == _OFF ? 0x00 : _BIT3 | _BIT2));
        CScalerSetDataPortBit(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_CLAMP_CTRL2_06, ~(_BIT5 | _BIT4), _BIT5); //off-line ADC clamp Enable
        CScalerSetBit(_P0_ADC_RBG_CTRL_CE, ~_BIT3, 0x00);// ADC input0
        CScalerSetBit(_P0_ADC_I_BAIS0_C7, ~_BIT0, _BIT0);  //SOG0 input MUX
        CScalerSetBit(_P0_ADC_I_BAIS1_C8, ~(_BIT7 | _BIT6), 0x00);
        CScalerSetBit(_P0_ADC_RED_CTL_CF, ~_BIT7, 0x00);//RGB clamp voltage sel
        CScalerSetBit(_P0_ADC_GREEN_CTL_D0, ~_BIT7, 0x00);
        CScalerSetBit(_P0_ADC_BLUE_CTL_D1, ~_BIT7, 0x00);
    }
    else if(ucAnalogSource == _ANALOG_SOURCE_1 || ucAnalogSource == _DIGISTAL_SOURCE_1) 
    {
        CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), (_HSYNC_SOURCE_SWAP == _OFF ? _BIT3 | _BIT2 : 0x00));
        CScalerSetDataPortBit(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_CLAMP_CTRL2_06, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
        CScalerSetBit(_P0_ADC_RBG_CTRL_CE, ~_BIT3, _BIT3);
        CScalerSetBit(_P0_ADC_SOG_CTRL_D6, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
        CScalerSetBit(_P0_ADC_RED_CTL_CF, ~_BIT7, _BIT7);
        CScalerSetBit(_P0_ADC_GREEN_CTL_D0, ~_BIT7, _BIT7);
        CScalerSetBit(_P0_ADC_BLUE_CTL_D1, ~_BIT7, _BIT7);
    }

    CScalerSetBit(_SYNC_CTRL_49, ~(_BIT1 | _BIT0), _BIT1);// ADC_HS/ADC_VS

#if(_YPBPR_SUPPORT == _ON)
    if(_GET_INPUT_SOURCE() == _SOURCE_YPBPR||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1)
        CScalerSetBit(_SYNC_SELECT_47, ~_BIT4, _BIT4);//  SOG/SOY
    else
        CScalerSetBit(_SYNC_SELECT_47, ~_BIT4, 0x00);// HS_RAW   
#else
        CScalerSetBit(_SYNC_SELECT_47, ~_BIT4, 0x00);
#endif  // End of #if(_YPBPR_SUPPORT == _ON)


    for(cnt=0;cnt<2;cnt++)
    {
        synctypetemp = CSyncGetSyncTypeAutoRun();

        if(synctypetemp != _NO_SYNC_STATE)
        {
            return _TRUE;
        }
#if(_HSYNC_TYPE_SELECT != _HSYNC_ONLY)
        CScalerSetBit(_SYNC_SELECT_47, ~_BIT4, _BIT4);
#endif  // End of #if(_HSYNC_TYPE_SELECT != _HSYNC_ONLY)
    }
        
    CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, 0x00);// manual 
    CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, 0x00);
    return _FALSE;

        
}

/**
 * CSourceScanInputPortDVI
 * Scan DVI input port to obtain if the signal is available
 * @param <BYTE ucPar> {_DE_ONLY_OFF or _DE_ONLY_ON}
 * @return {_TRUE if the signal is valid and in freq range,_FALSE if not}
 *
*/
#if(_TMDS_SUPPORT == _ON || _HDMI_SUPPORT == _ON)
bit CSourceScanInputPortDVI(BYTE ucPar)
{
    BYTE cnt0, cnt1;
             
    CScalerPageSelect(_PAGE2);
    CScalerRead(_P2_HDMI_SR_CB, 1, &pData[0], _NON_AUTOINC);
    CScalerRead(_P2_TMDS_CTRL_A4, 1, &pData[1], _NON_AUTOINC);

#if(_HDMI_SUPPORT == _ON)
    if((pData[0]&0x40)&& (pData[1]&0xF8))
    {
        ucHdmiAVMuteCnt++;
        if(ucHdmiAVMuteCnt == 20)
        {
            CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_SCR_00, ~(_BIT3 | _BIT2), _BIT3);//Set HDMI/DVI switch mode(manual,DVI)//Alanli20070801
            CTimerDelayXms(200);
            CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_SCR_00, ~(_BIT3 | _BIT2), 0x00);//Set HDMI/DVI switch mode(auto)
            ucHdmiAVMuteCnt = 0;
        }
        return _FALSE;  
    }          
#endif
            /*      
    if (_SOURCE_DVI == _GET_INPUT_SOURCE())
        CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_SCR_00, ~(_BIT3 | _BIT2), _BIT3);//Set HDMI/DVI switch mode(manual,DVI)//Alanli20070801
    else
        CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_SCR_00, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));//Set HDMI/DVI switch mode(manual,DVI)//Alanli20070801
        CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, 0X51, ~(_BIT7), 0X00);//Set HDMI/DVI switch mode(manual,DVI)//Alanli20070801
               */  
 
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_SYNC_CTRL_49, ~(_BIT1 | _BIT0), 0x00);
    CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT1 | _BIT0), _BIT1 | _BIT0);
    CScalerSetBit(_P2_UP_DOWN_CTRL0_B5, ~(_BIT7), _BIT7);

    CScalerSetBit(_IPH_ACT_WID_H_16, ~_BIT3, _BIT3);                                                //TMDS/Video8:TMDS

    // Modify by Ericlee for add DVI 20070830
    switch (CGetSourcePortType(_GET_INPUT_SOURCE()))
    {
    case _DVI_PORT:
    case _HDMI_PORT:
    case _DVI_D0_PORT:
    case _HDMI_D0_PORT:  // D0
        CScalerSetBit(_P2_TMDS_MEAS_RESULT0_A2, ~_BIT1, 0x00);
        CScalerSetBit(_P2_HDCP_PORT_CTRL_C2, ~_BIT1, _DDC_CHANNEL_FOR_D0);
        // R/B swap & P/N Swap    
        CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT6 | _BIT5), _CHANNEL_D0_RG_SWAP | _CHANNEL_D0_PN_SWAP);
        break;

    case _DVI_D1_PORT:
    case _HDMI_D1_PORT:  // D1
        CScalerSetBit(_P2_TMDS_MEAS_RESULT0_A2, ~_BIT1, _BIT1);
        CScalerSetBit(_P2_HDCP_PORT_CTRL_C2, ~_BIT1, _DDC_CHANNEL_FOR_D1);
        // R/B swap & P/N Swap    
        CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT6 | _BIT5), _CHANNEL_D1_RG_SWAP | _CHANNEL_D1_PN_SWAP);
        break;
    }

    CScalerSetBit(_P2_HDCP_CTRL_C0, ~_BIT0, _BIT0);

    CScalerPageSelect(_PAGE2);

    if(ucPar == _DE_ONLY_ON)
        CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~_BIT7, _BIT7);
    else
        CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~_BIT7, 0x00);

    CScalerRead(_P2_UP_DOWN_CTRL1_B6, 1, pData, _NON_AUTOINC);
     pData[0] &= 0xf0;
    /*if(pData[0] == 0xe0) 
        CScalerSetByte(_P2_RGB_PLL_SETTING_AE, 0x20);
    else if((pData[0] == 0x80) | (pData[0] == 0x60) | (pData[0] == 0x10))
        CScalerSetByte(_P2_RGB_PLL_SETTING_AE, 0x24);
    else if((pData[0] == 0x40) | (pData[0] == 0x30))
        CScalerSetByte(_P2_RGB_PLL_SETTING_AE, 0x2b);
    else
        CScalerSetByte(_P2_RGB_PLL_SETTING_AE, 0x24);*/

    if(pData[0] == 0xe0)
        CScalerSetByte(_P2_RGB_PLL_SETTING_AE, 0x24);
    else if((pData[0] == 0x80) | (pData[0] == 0x60) | (pData[0] == 0x10))
        CScalerSetByte(_P2_RGB_PLL_SETTING_AE, 0x2c);
    else if((pData[0] == 0x40) | (pData[0] == 0x30))
        CScalerSetByte(_P2_RGB_PLL_SETTING_AE, 0x30);
    else
        return _FALSE;  

    if(pData[0] == 0xe0)
        CScalerSetByte(_P2_ADAPTIVE_EQUALIZER2_B8, 0x01);
    else
        CScalerSetByte(_P2_ADAPTIVE_EQUALIZER2_B8, 0x00);

    // EricLee for ATI9250,ATI9550
    CScalerSetBit(_P2_ANALOG_BIAS_CTRL_AA, ~(_BIT5), 0x00);
    CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT3 | _BIT2), 0x00);
    /*
    if(_GET_INPUT_SOURCE() == _SOURCE_DVI)
        CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT6 | _BIT5 | _BIT4), _BIT4); 
    else if(_GET_INPUT_SOURCE() == _SOURCE_HDMI)
    {   // eric 0617
        //CScalerSetBit(_P2_ANALOG_BIAS_CTRL_AA, ~(_BIT2), _BIT2);
        CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));   
    }*/
	if(_GET_INPUT_SOURCE() == _SOURCE_HDMI && _GET_INPUT_SOURCE() == _SOURCE_DVI)
    {   // eric 0617
        //CScalerSetBit(_P2_ANALOG_BIAS_CTRL_AA, ~(_BIT2), _BIT2);
        CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));   
    }
    
    else
    {
        CScalerSetBit(_P2_ANALOG_BIAS_CTRL_AA, ~(_BIT5), _BIT5);
        CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT3 | _BIT2), 0x00);
        CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT6 | _BIT5 | _BIT4), _BIT6 | _BIT5 | _BIT4); 
    }

    for(cnt0=0;cnt0<2;cnt0++)
    {
        for(cnt1=0;cnt1<2;cnt1++)
        {
            CScalerSetByte(_P2_TMDS_CTRL_A4, 0xf8);
            CTimerDelayXms(25);

            CScalerRead(_P2_TMDS_CTRL_A4, 1, pData, _NON_AUTOINC);

            if(ucPar == _DE_ONLY_ON)
                pData[0] = ((pData[0] & 0xe0) == 0xe0) ? _TRUE : _FALSE;
            else
                pData[0] = ((pData[0] & 0xf8) == 0xf8) ? _TRUE : _FALSE;

            if(pData[0])
            {
                CScalerRead(_P2_UP_DOWN_CTRL1_B6, 1, pData, _NON_AUTOINC);
                pData[0] &= 0xf0;

                if((pData[0] == 0xe0) || (pData[0] == 0x80) || (pData[0] == 0x60) || (pData[0] == 0x40) || (pData[0] == 0x30))
                {
            #if(_HDMI_SUPPORT == _ON)
                    if(CHdmiFormatDetect())
                    {
                         if(!CHdmiVideoSetting())
                             return _FALSE;
                    }
                    else
                    {
                        CHdmiVideoSetting();
                    }
                        /*
            #else
                     if(CHdmiFormatDetect())
                            return _FALSE;
                            */
            #endif
					
#if(_HDMI_SUPPORT == _ON)//DVI need enable compensation,otherwise color is error.
                    if(!CHdmiFormatDetect())
#endif
                    CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT3 | _BIT2), _BIT2);

                    return _TRUE;
                }
            }
#if(_HDMI_SUPPORT == _ON)
            if(!CHdmiFormatDetect())
#endif
            CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT3 | _BIT2), _BIT2);
            }

        CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);
        CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT3 | _BIT2), 0x00);
    }

    return _FALSE;
}
#endif  // End of #if(_TMDS_SUPPORT == _ON)

