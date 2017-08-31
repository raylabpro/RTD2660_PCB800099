/*===========================================================
 * Copyright (c)      Realtek Semiconductor Corporation, 2005
 * All rights reserved.
 * ========================================================== */

/*==================== File Description ===================== */
/**
 * @file
 *  This file is osd control declaration related functions.
 *
 * @author  $Author: hillwang $
 * @date    $Date: 2006-09-07 19:38:12 +0800 (?Ÿæ??? 07 ä¹æ? 2006) $
 * @version     $Revision: 1187 $
 * @ingroup Auto
 */

/**
 * @addtogroup Auto
 * @{
 */

#define _ADJUST_C
/*===================== Module dependency  ================== */
#include "Core\Header\Include.h"

/*======================= Private Types ===================== */

/*======================== Definitions ====================== */

/*========================== Variables ====================== */
//BYTE idata ucAdjustCtrl = 0;

/*=================== Local Functions Phototype ==============*/
static void CAdjustSetSharpnessTable(bit scaling,BYTE code *pArray0, BYTE code *pArray1);
void CAdjustPeakingCoring(void);
void CAdjustPeakingFilter(SBYTE ucPeaking);

/*=========================== Functions ===================== */
//--------------------------------------------------
// Description  : Adjust IHS delay
// Input Value  : IHS delay
// Output Value : None
//--------------------------------------------------
void CAdjustIHSDelay(WORD usIHSDelay)
{
    CScalerSetBit(_VGIP_HV_DELAY_1E, ~_BIT0, HIBYTE(usIHSDelay) & _BIT0);
    CScalerSetByte(_IHS_DELAY_1D, LOBYTE(usIHSDelay));
}

//--------------------------------------------------
// Description  : Adjust IVS delay
// Input Value  : IVS delay
// Output Value : None
//--------------------------------------------------
void CAdjustIVSDelay(WORD usIVSDelay)
{
    CScalerSetBit(_VGIP_HV_DELAY_1E, ~_BIT1, (usIVSDelay >> 7) & _BIT1);
    CScalerSetByte(_IVS_DELAY_1C, LOBYTE(usIVSDelay));
}

//--------------------------------------------------
// Description  : Adjust Dclk offset
// Input Value  : Dclk offset
// Output Value : None
//--------------------------------------------------
void CAdjustDclkOffset(WORD usDclkOffset)
{                      
    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_DCLK_FINE_TUNE_OFFSET_MSB_C4, 0xf0, HIBYTE(usDclkOffset) & 0x0f);
    CScalerSetByte(_P1_DCLK_FINE_TUNE_OFFSET_LSB_C5, LOBYTE(usDclkOffset));
    CScalerSetBit(_P1_DCLK_SPREAD_SPECTRUM_C6, ~_BIT2, _BIT2);
}

//--------------------------------------------------
// Description  : Adjust spread spectrum range
// Input Value  : Spread spectrum range
// Output Value : None
//--------------------------------------------------
void CAdjustSpreadSpectrumRange(BYTE ucSpreadRange)
{
    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_DCLK_SPREAD_SPECTRUM_C6, 0x0f, (ucSpreadRange << 4) & 0xf0);
    CScalerSetBit(_P1_DCLK_SPREAD_SPECTRUM_C6, ~_BIT2, _BIT2);
}

//--------------------------------------------------
// Description  : Sync processor measure start
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustSyncProcessorMeasureStart(void)
{
    CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT5, _BIT5);
}

//--------------------------------------------------
// Description  : Turn on the error correction function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustTMDSErrorCorrectionOn(void)
{
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_UP_DOWN_CTRL2_B7, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);
}

#if(((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON)) && (_DVI_LONG_CABLE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Measure TMDS transition result
// Input Value  : ucType    --> _TMDS_MEASURE_AVE, _TMDS_MEASURE_MAX, _TMDS_MEASURE_MIN
//                ucSelect  --> _TMDS_MEASURE_HSYNC_BE, _TMDS_MEASURE_HSYNC_AF, _TMDS_MEASURE_DE_BE, _TMDS_MEASURE_DE_AF
// Output Value : Transition result
//--------------------------------------------------
BYTE CAdjustTMDSMeasure(BYTE ucType, BYTE ucSelect)
{
    BYTE result;

    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_TMDS_MEAS_RESULT0_A2, ~(_BIT6 | _BIT5), (ucType << 5));
    CScalerSetBit(_P2_TMDS_MEAS_RESULT0_A2, ~(_BIT7 | _BIT4 | _BIT3), (_BIT7 | (ucSelect << 3)));

    if(CTimerPollingEventProc(60, CMiscTMDSMeasureEvent) == _FALSE)
    {
        CScalerSetBit(_P2_TMDS_MEAS_RESULT0_A2, ~_BIT7, 0x00);
        return 0xff;
    }

    CScalerRead(_P2_TMDS_MEAS_RESULT1_A3, 1, &result, _NON_AUTOINC);

    return (result & 0x7f);
}

//--------------------------------------------------
// Description  : TMDS CRC check process before displaying
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustTMDSCRCCheck(void)
{
    BYTE temp0, temp1;
    DWORD dsod0, dsod1;

    if(GET_FRAMESYNCSTATUS())
    {
        CTimerDelayXms(20);

        temp0 = 0;
        temp0 += CAdjustTMDSCRC(&pData[8]);
        temp0 += CAdjustTMDSCRC(&pData[12]);
        dsod0 = abs(((DWORD *)pData)[2] - ((DWORD *)pData)[3]);

        if(temp0 < 2)
        {
            CScalerPageSelect(_PAGE2);
            CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT5 | _BIT6), CScalerGetBit(_P2_ANALOG_COMMON_CTRL2_AB, (_BIT6 | _BIT5)) ^ (_BIT5 | _BIT6));

            temp1 = 0;
                temp1 += CAdjustTMDSCRC(&pData[8]);
                temp1 += CAdjustTMDSCRC(&pData[12]);
                dsod1 = abs(((DWORD *)pData)[2] - ((DWORD *)pData)[3]);

                if(temp1 < 2)
                {
                    if(GET_USE_TRANSITION_RESULT())
                    {
                    CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT5 | _BIT6), CScalerGetBit(_P2_ANALOG_COMMON_CTRL2_AB, (_BIT6 | _BIT5)) ^ (_BIT5 | _BIT6));
                        }
                    else
                {
                            if(dsod0 <= dsod1)
                        CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT5 | _BIT6), CScalerGetBit(_P2_ANALOG_COMMON_CTRL2_AB, (_BIT6 | _BIT5)) ^ (_BIT5 | _BIT6));
                }
            }
            else
            {
                        //CModeSetDigitalCapture();
            }
        }
        else
        {
                //CModeSetDigitalCapture();
        }
    }
}

//--------------------------------------------------
// Description  : Get TMDS transition difference
// Input Value  : ucPar     --> _MEASURE_HSYNC or _MEASURE_DE
// Output Value : Transition difference result
//--------------------------------------------------
BYTE CAdjustTMDSEqualizerCheck(BYTE ucPar)
{
    BYTE result0, result1;

    if(ucPar == _MEASURE_HSYNC)
    {
        result0 = CAdjustTMDSMeasure(_TMDS_MEASURE_MAX, _TMDS_MEASURE_HSYNC_BE);
        if(result0 == 0xff)     return 0xff;
        else if(result0 < 6)    return 0xfe;

        result1 = CAdjustTMDSMeasure(_TMDS_MEASURE_MIN, _TMDS_MEASURE_HSYNC_AF);
        if(result1 == 0xff)     return 0xff;
        else if(result1 < 6)    return 0xfe;
    }
    else if(ucPar == _MEASURE_DE)
    {
        result0 = CAdjustTMDSMeasure(_TMDS_MEASURE_MAX, _TMDS_MEASURE_DE_BE);
        if(result0 == 0xff)     return 0xff;
        else if(result0 < 6)    return 0xfe;

        result1 = CAdjustTMDSMeasure(_TMDS_MEASURE_MAX, _TMDS_MEASURE_DE_AF);
        if(result1 == 0xff)     return 0xff;
        else if(result1 < 6)    return 0xfe;
    }

    result0 = abs(result0 - result1);

    if(result0 <= 2)
        result0 = 0;

    return result0;
}

//--------------------------------------------------
// Description  : Adjust TMDS equalizer setting
// Input Value  : None
// Output Value : return _TRUE if success
//--------------------------------------------------
bit CAdjustTMDSEqualizer(void)
{
    BYTE cnt, result0, result1;

    CLR_USE_TRANSITION_RESULT();
    CScalerPageSelect(_PAGE2);
    CScalerSetByte(_P2_TMDS_MEAS_SELECT_A1, 0x21);
    CScalerSetBit(_P2_TMDS_MEAS_RESULT0_A2, ~(_BIT6 | _BIT5), _BIT5);

    cnt = 1;
    do
    {
        CScalerSetBit(_P2_TMDS_MEAS_SELECT_A1, 0xf0, (cnt%16));

        result0 = CAdjustTMDSMeasure(_TMDS_MEASURE_MAX, _TMDS_MEASURE_DE_BE);
        if(result0 == 0xff)
            return _FALSE;

        if(result0 > 80)
            break;

        cnt++;
    }
    while(cnt <= 16);

    cnt = 0;

    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
    result0 = CAdjustTMDSEqualizerCheck(_MEASURE_HSYNC);
    if(result0 == 0xff)     return _FALSE;
    if(result0 == 0xfe)     cnt += 1;

    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);
    result1 = CAdjustTMDSEqualizerCheck(_MEASURE_HSYNC);
    if(result1 == 0xff)     return _FALSE;
    if(result1 == 0xfe)     cnt += 2;

    if((abs(result0 - result1) <= 2) || (cnt != 0))
    {
        cnt = 0;

        CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
        result0 = CAdjustTMDSEqualizerCheck(_MEASURE_DE);
        if(result0 == 0xff)     return _FALSE;
        if(result0 == 0xfe)     cnt += 1;

        CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);
        result1 = CAdjustTMDSEqualizerCheck(_MEASURE_DE);
        if(result1 == 0xff)     return _FALSE;
        if(result1 == 0xfe)     cnt += 2;
    }

    if((result0 <= result1) || (cnt >= 2))
        CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

    if(abs(result0 - result1) > 2)
        SET_USE_TRANSITION_RESULT();

    return _TRUE;
}
#endif  // End of #if(((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON)) && (_DVI_LONG_CABLE_SUPPORT == _ON))

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set digital mode capture
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustSetDigitalCapture(void)
{
    CScalerSetBit(_VGIP_CTRL_10, ~_BIT1, _BIT1);
    CScalerSetBit(_IPH_ACT_STA_H_14, 0xf8, 0x00);
    CScalerSetByte(_IPH_ACT_STA_L_15, 0x00);
    CScalerSetBit(_IPV_ACT_STA_H_18, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT1 | _BIT0);
    CScalerSetByte(_IPV_ACT_STA_L_19, 0x00);
}

#if(_DVI_LONG_CABLE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Measure TMDS CRC value
// Input Value  : None
// Output Value : CRC value, DWORD data type
//--------------------------------------------------
DWORD CAdjustTMDSCRCMeasure(void)
{
    BYTE result[4];

    result[0] = 0;
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_TMDS_CTRL_A4, ~_BIT0, 0x00);
    CScalerSetBit(_P2_TMDS_CTRL_A4, ~_BIT0, _BIT0);

    if(CTimerPollingEventProc(60, CMiscTMDSCRCEvent) == _FALSE)
    {
        CScalerSetBit(_P2_TMDS_CTRL_A4, ~_BIT0, 0x00);
        return 0xffffffffl;
    }

    CTimerDelayXms(20);

    CScalerRead(_P2_CRC_OUTPUT_BYTE_2_A5, 3, &result[1], _NON_AUTOINC);

    return ((DWORD *)result)[0];
}

//--------------------------------------------------
// Description  : Do two times CRC check and get phase SOD value
// Input Value  : pArray    --> SOD value buffer
// Output Value : Return 0 if CRCs are not the same or CRCs == 0
//--------------------------------------------------
BYTE CAdjustTMDSCRC(BYTE *pArray)
{
    BYTE temp;

    CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x3b);
    CScalerSetByte(_STATUS0_02, 0x00);

    ((DWORD *)pData)[0] = CAdjustTMDSCRCMeasure();
    ((DWORD *)pData)[1] = CAdjustTMDSCRCMeasure();

    CScalerRead(_STATUS0_02, 1, &temp, _NON_AUTOINC);
    CScalerRead(_AUTO_PHASE_3_84, 4, pArray, _AUTOINC);

    if((((DWORD *)pData)[0] != ((DWORD *)pData)[1]) || ((temp & 0x03) != 0) || (((DWORD *)pData)[0] == 0) || (((DWORD *)pData)[1] == 0))
        return 0;
    else
        return 1;
}
#endif  // End of #if(_DVI_LONG_CABLE_SUPPORT == _ON)

//--------------------------------------------------
// Description  : TMDS digital/analog capture check process before displaying
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustTMDSCaptureCheck(void)
{
    BYTE flag = 0;

    if(flag)
    {
        CAdjustSetDigitalCapture();
        CTimerDelayXms(20);
    }

}
#endif  // End of #if(_TMDS_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Enable watch dog
// Input Value  : ucPar --> Parameter for watch dog
// Output Value : None
//--------------------------------------------------
void CAdjustEnableWatchDog(BYTE ucPar)
{
    // add this line by Moya, we don't enable watch-dog at all.
    //return;
    if (bCNoCheckSyncMode())
        return;

    if(GET_FRAMESYNCSTATUS())
    {
        CScalerSetByte(_WATCH_DOG_CTRL0_0C, 0x00);
        CMiscClearStatusRegister();
        CScalerSetBit(_WATCH_DOG_CTRL0_0C, ~ucPar, 0x06 | ucPar);  //Ming-Yen
        ucPar = ucPar + 0; //Ming-Yen
    }
}

//--------------------------------------------------
// Description  : Disable watch dog
// Input Value  : ucPar --> Parameter for watch dog
// Output Value : None
//--------------------------------------------------
void CAdjustDisableWatchDog(BYTE ucPar)
{
    BYTE temp;

    CScalerSetBit(_WATCH_DOG_CTRL0_0C, ~ucPar, 0x00);
    temp = CScalerGetBit(_WATCH_DOG_CTRL0_0C, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));
    if(temp == 0x00)
        CScalerSetByte(_WATCH_DOG_CTRL0_0C, 0x00);
}

//--------------------------------------------------
// Description  : Adjust gamma
// Input Value  : Gamma table type and gamma tables
// Output Value : None
//--------------------------------------------------
void CAdjustGamma(BYTE ucGammaTableType, BYTE *pGammaTableArrayR, BYTE *pGammaTableArrayG, BYTE *pGammaTableArrayB)
{
    WORD cnt;
    BYTE i, temp;

    if((ucGammaTableType == _COMPACT_GAMMA_NORMAL_TABLE) || (ucGammaTableType == _FULL_GAMMA_NORMAL_TABLE))
    {
        CScalerSetByte(_GAMMA_CTRL_67, 0x80 | ucGammaTableType);
        CScalerWrite(_GAMMA_PORT_66, ((ucGammaTableType == _COMPACT_GAMMA_NORMAL_TABLE) ? 256 : 384), pGammaTableArrayR, _NON_AUTOINC);
        CScalerSetByte(_GAMMA_CTRL_67, 0x90 | ucGammaTableType);
        CScalerWrite(_GAMMA_PORT_66, ((ucGammaTableType == _COMPACT_GAMMA_NORMAL_TABLE) ? 256 : 384), pGammaTableArrayG, _NON_AUTOINC);
        CScalerSetByte(_GAMMA_CTRL_67, 0xa0 | ucGammaTableType);
        CScalerWrite(_GAMMA_PORT_66, ((ucGammaTableType == _COMPACT_GAMMA_NORMAL_TABLE) ? 256 : 384), pGammaTableArrayB, _NON_AUTOINC);
        CScalerSetByte(_GAMMA_CTRL_67, 0x40);
    }
#if(_GAMMA_TYPE == _FULL_GAMMA_COMPRESS_TABLE2)
    else if(ucGammaTableType == _FULL_GAMMA_COMPRESS_TABLE2)
    {
     CScalerSetByte(_GAMMA_CTRL_67, 0x81);
    CRtdWriteGamma(pGammaTableArrayR);
    CScalerSetByte(_GAMMA_CTRL_67, 0x91);
    CRtdWriteGamma(pGammaTableArrayG);
    CScalerSetByte(_GAMMA_CTRL_67, 0xa1);
    CRtdWriteGamma(pGammaTableArrayB);
    CScalerSetByte(_GAMMA_CTRL_67, 0x40);   
    }
#endif  
    else if((ucGammaTableType == _COMPACT_GAMMA_COMPRESS_TABLE) || (ucGammaTableType == _FULL_GAMMA_COMPRESS_TABLE))
    {
        for(i=0;i<3;i++)
        {
            ucVLDCnt    = 0;
            ucVLDTemp   = 0;

            if(i == 0)
            {
                CScalerSetByte(_GAMMA_CTRL_67, 0x80 | (ucGammaTableType % 2));
                pvldarray   = (pGammaTableArrayR + 16);
            }
            else if(i == 1)
            {
                CScalerSetByte(_GAMMA_CTRL_67, 0x90 | (ucGammaTableType % 2));
                pvldarray   = (pGammaTableArrayG + 16);
            }
            else
            {
                CScalerSetByte(_GAMMA_CTRL_67, 0xa0 | (ucGammaTableType % 2));
                pvldarray   = (pGammaTableArrayB + 16);
            }

            for(temp=0;temp<16;temp++)
                pData[temp] = *(pvldarray + temp - 16);

            for(cnt=0;cnt<((ucGammaTableType == _COMPACT_GAMMA_COMPRESS_TABLE) ? 256 : 384);cnt++)
            {
                temp    = CScalerGetVLD() << 4;
                temp    |= CScalerGetVLD();
                CScalerSetByte(_GAMMA_PORT_66, temp);
            }
        }
            CScalerSetByte(_GAMMA_CTRL_67, 0x40);
        }
}


#if(_GAMMA_TYPE == _FULL_GAMMA_COMPRESS_TABLE2)
void CRtdWriteGamma(UINT8  *array)
{
    int i,k=0,m=0;
    int tmp;
    int diff0;
    int d2;
    int k0;
 
    int outA;

    k0=outA=*array++; // //2x+0
    diff0=*(array++);

    for (i=0;i<256;i+=2)
    {
        tmp=*(array++);
        //---even----------------------
        d2=(tmp>>4)-8;
        if (d2==-8)
            d2=(char)*(array++);
 // dump k0
        CScalerSetByte(_GAMMA_PORT_66,(k0>>2));
        outA=outA+diff0; // 2x+1
 // dump d0,
        CScalerSetByte(_GAMMA_PORT_66,(((k0&3)<<6)|diff0));
        diff0=diff0+d2; // d[2x+1]
// dump d1
        if (i==254) 
            diff0=0; // Last item :: without d2;
        CScalerSetByte(_GAMMA_PORT_66,(diff0));
        m++; 
        k++;
        //---odd-----------------------
        d2=(tmp&0xf)-8;
        if(d2 == -8)
            d2 = (char)*array++;
        k0 = outA = outA + diff0;
        diff0 = diff0 + d2; // d[2x+1];
        m++; 
        k++;
    }
}
#endif


//--------------------------------------------------
// Description  : Set dithering
// Input Value  : Dithering tables
// Output Value : None
//--------------------------------------------------
void CAdjustDither(BYTE *pDitherSeqTable, BYTE * pDitherTable)
{
    CScalerSetBit(_DITHERING_CTRL_6A, ~(_BIT7 | _BIT6), _BIT6);
    CScalerWrite(_DITHERING_DATA_ACCESS_69, 24, pDitherSeqTable, _NON_AUTOINC);
    CScalerSetBit(_DITHERING_CTRL_6A, ~(_BIT7 | _BIT6), _BIT7);
    CScalerWrite(_DITHERING_DATA_ACCESS_69, 24, pDitherTable, _NON_AUTOINC);
    CScalerSetByte(_DITHERING_CTRL_6A, 0x38);
}
//--------------------------------------------------
// Description  : Adjust sharpness for scale up
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustSharpnessForScaleUp(void)
{
    CAdjustSetSharpnessTable(_SCALE_UP,tSU_COEF_TABLE[GET_SHARPNESS()], tSU_COEF_TABLE[GET_SHARPNESS()]);
}
//--------------------------------------------------
// Description  : Adjust sharpness for scale down
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustSharpnessForScaleDown(void)
{
    CAdjustSetSharpnessTable(_SCALE_DOWN, tSCALE_DOWN_COEF_TABLE[GET_SHARPNESS()], tSCALE_DOWN_COEF_TABLE[GET_SHARPNESS()]);
}

//--------------------------------------------------
// Description  : Set Sharpness Table
// Input Value  : 1: Scale-Up
//                0: Scale-Down  
// Output Value : None
//--------------------------------------------------
void CAdjustSetSharpnessTable(bit scaling, BYTE code *pArray0, BYTE  code *pArray1)
{
    if(scaling)
    {
        CScalerSetByte(_FILTER_CTRL_35, 0xb0);
        CScalerWrite(_FILTER_ACCESS_PORT_36, 128, pArray0, _NON_AUTOINC);
        CScalerSetByte(_FILTER_CTRL_35, 0xc0);
        CScalerWrite(_FILTER_ACCESS_PORT_36, 128, pArray1, _NON_AUTOINC);
        CScalerSetByte(_FILTER_CTRL_35, 0x00);

        CScalerSetByte(_FILTER_CTRL_35, 0x0b);
        CScalerWrite(_FILTER_ACCESS_PORT_36, 128, pArray0, _NON_AUTOINC);
        CScalerSetByte(_FILTER_CTRL_35, 0x0c);
        CScalerWrite(_FILTER_ACCESS_PORT_36, 128, pArray1, _NON_AUTOINC);
        CScalerSetByte(_FILTER_CTRL_35, 0x00);
    }
    else
    {
        CScalerPageSelect(_PAGE6);
        CScalerSetByte(_P6_UZD_FIR_COEF_INDEX_F3, 0x00);
        CScalerWrite(_P6_UZD_FIR_COEF_PORT_F4, 64, pArray0, _NON_AUTOINC);
        CScalerSetByte(_P6_UZD_FIR_COEF_INDEX_F3, 0x80);
        CScalerWrite(_P6_UZD_FIR_COEF_PORT_F4, 64, pArray1, _NON_AUTOINC);
        CScalerSetByte(_P6_UZD_FIR_COEF_INDEX_F3, 0x00);
    }
}

//--------------------------------------------------
// Description  : Adjust color precessing brightness
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustSetBrightness(void)
{
    CScalerSetByte(_CB_ACCESS_PORT_64, 0x80);
    CScalerWrite(_CB_DATA_PORT_65, 3, pData, _NON_AUTOINC);
    CScalerSetByte(_CB_ACCESS_PORT_64, 0x00);
}

//--------------------------------------------------
// Description  : Adjust color processing contrast
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustSetContrast(void)
{
    CScalerSetByte(_CB_ACCESS_PORT_64, 0x83);
    CScalerWrite(_CB_DATA_PORT_65, 3, pData, _NON_AUTOINC);
    CScalerSetByte(_CB_ACCESS_PORT_64, 0x00);
}

//--------------------------------------------------
// Description  : Adjust ADC gain
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustAdcGain(void)
{
    if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
    {
#if(_ADC0_INPUT_SWAP_RG == _ON)
        pData[1] = stAdcData.AdcGain[_RED];
        pData[0] = stAdcData.AdcGain[_GREEN];
        pData[2] = stAdcData.AdcGain[_BLUE];

#elif(_ADC0_INPUT_SWAP_RB == _ON)
        pData[2] = stAdcData.AdcGain[_RED];
        pData[1] = stAdcData.AdcGain[_GREEN];
        pData[0] = stAdcData.AdcGain[_BLUE];

#elif(_ADC0_INPUT_SWAP_GB == _ON)
        pData[0] = stAdcData.AdcGain[_RED];
        pData[2] = stAdcData.AdcGain[_GREEN];
        pData[1] = stAdcData.AdcGain[_BLUE];
#else
        pData[0] = stAdcData.AdcGain[_RED];
        pData[1] = stAdcData.AdcGain[_GREEN];
        pData[2] = stAdcData.AdcGain[_BLUE];
#endif//(_ADC_INPUT_SWAP_RG == _ON)
    }
    else// if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
    {
#if(_ADC1_INPUT_SWAP_RG == _ON)
        pData[1] = stYPbPrData.YPbPrGain[_RED];
        pData[0] = stYPbPrData.YPbPrGain[_GREEN];
        pData[2] = stYPbPrData.YPbPrGain[_BLUE];
#elif(_ADC1_INPUT_SWAP_RB == _ON)
        pData[2] = stYPbPrData.YPbPrGain[_RED];
        pData[1] = stYPbPrData.YPbPrGain[_GREEN];
        pData[0] = stYPbPrData.YPbPrGain[_BLUE];
#elif(_ADC1_INPUT_SWAP_GB == _ON)
        pData[0] = stYPbPrData.YPbPrGain[_RED];
        pData[2] = stYPbPrData.YPbPrGain[_GREEN];
        pData[1] = stYPbPrData.YPbPrGain[_BLUE];
#else
        pData[0] = stYPbPrData.YPbPrGain[_RED];
        pData[1] = stYPbPrData.YPbPrGain[_GREEN];
        pData[2] = stYPbPrData.YPbPrGain[_BLUE];
#endif
    }
    {
        CScalerPageSelect(_PAGE0);      
        CScalerWrite(_P0_RED_GAIN_C0, 3, pData, _AUTOINC);

    }
}

//--------------------------------------------------
// Description  : Adjust ADC offset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustAdcOffset(void)
{
    if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
    {
#if(_ADC0_INPUT_SWAP_RG == _ON)
        pData[4] = stAdcData.AdcOffset[_RED];
        pData[3] = stAdcData.AdcOffset[_GREEN];
        pData[5] = stAdcData.AdcOffset[_BLUE];
#elif(_ADC0_INPUT_SWAP_RB == _ON)
        pData[5] = stAdcData.AdcOffset[_RED];
        pData[4] = stAdcData.AdcOffset[_GREEN];
        pData[3] = stAdcData.AdcOffset[_BLUE];
#elif(_ADC0_INPUT_SWAP_GB == _ON)
        pData[3] = stAdcData.AdcOffset[_RED];
        pData[5] = stAdcData.AdcOffset[_GREEN];
        pData[4] = stAdcData.AdcOffset[_BLUE];
#else
        pData[3] = stAdcData.AdcOffset[_RED];
        pData[4] = stAdcData.AdcOffset[_GREEN];
        pData[5] = stAdcData.AdcOffset[_BLUE];
#endif
    }
    else 
    {
#if(_ADC1_INPUT_SWAP_RG == _ON)
        pData[4] = stYPbPrData.YPbPrOffset[_RED];
        pData[3] = stYPbPrData.YPbPrOffset[_GREEN];
        pData[5] = stYPbPrData.YPbPrOffset[_BLUE];
#elif(_ADC1_INPUT_SWAP_RB == _ON)
        pData[5] = stYPbPrData.YPbPrOffset[_RED];
        pData[4] = stYPbPrData.YPbPrOffset[_GREEN];
        pData[3] = stYPbPrData.YPbPrOffset[_BLUE];
#elif(_ADC1_INPUT_SWAP_GB == _ON)
        pData[3] = stYPbPrData.YPbPrOffset[_RED];
        pData[5] = stYPbPrData.YPbPrOffset[_GREEN];
        pData[4] = stYPbPrData.YPbPrOffset[_BLUE];
#else
        pData[3] = stYPbPrData.YPbPrOffset[_RED];
        pData[4] = stYPbPrData.YPbPrOffset[_GREEN];
        pData[5] = stYPbPrData.YPbPrOffset[_BLUE];
#endif
    }
    {
        CScalerPageSelect(_PAGE0);
        //pData[3] = pData[4] = pData[5] = 0x80;    //provisional ¼È©w
        CScalerWrite(_P0_RED_OFFSET_C3, 3, &pData[3], _AUTOINC);
    }
}

//--------------------------------------------------
// Description  : Adjust ADC gain and offset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustAdcGainOffset(void)
{
    CAdjustAdcGain();
    CAdjustAdcOffset();
}

//--------------------------------------------------
// Description  : Adjust background color
// Input Value  : Red, green and blue color settings
// Output Value : None
//--------------------------------------------------
void CAdjustBackgroundColor(BYTE ucRed, BYTE ucGreen, BYTE ucBlue)
{
    CScalerSetBit(_OVERLAY_CTRL_6C, ~_BIT5, 0x00);
    CScalerSetBit(_OVERLAY_CTRL_6C, ~_BIT5, _BIT5);

    CScalerSetByte(_BGND_COLOR_CTRL_6D, ucRed);
    CScalerSetByte(_BGND_COLOR_CTRL_6D, ucGreen);
    CScalerSetByte(_BGND_COLOR_CTRL_6D, ucBlue);

    CScalerSetBit(_OVERLAY_CTRL_6C, ~_BIT5, 0x00);
}

//--------------------------------------------------
bit CheckInterLace(void)
{
    CTimerDelayXms(200);
    CScalerRead(_IPV_ACT_LEN_H_1A, 1, pData, _NON_AUTOINC);
    
    if(pData[0] & 0x20)
        return 1;
        
    return 0;
}

//--------------------------------------------------
void CAdjustInterlaceIVS2DVSDelay(void)
{
    UINT16 usTemp;
    
//    CScalerRead(_IPV_ACT_LEN_H_1A, 1, pData, _NON_AUTOINC);

    if(CTimerPollingEventProc(5, CheckInterLace))
    //if(pData[0] & 0x20)
    {
        CScalerSetBit(_SCALE_CTRL_32, ~(_BIT7 | _BIT6), _BIT7); 
        CScalerRead(_IPV_ACT_LEN_H_1A, 2, pData, _AUTOINC);
        usTemp = (((WORD) pData[0] & 0x07) << 8) | (WORD) pData[1];
        if(usTemp <= 288)   //480i 576i 
            CScalerSetBit(_VGIP_SIGINV_11, ~_BIT4, 0);
        else
            CScalerSetBit(_VGIP_SIGINV_11, ~_BIT4, _BIT4);      


        CScalerRead(_IV_DV_DELAY_CLK_ODD_41, LENGTH(1), pData, _NON_AUTOINC);
        usTemp = (WORD)pData[0] * 16 + 16;
        usTemp += stModeInfo.IHTotal/2;

        CScalerSetByte(_IV_DV_DELAY_CLK_ODD_41, ((usTemp - 16) / 16));
        usTemp -= stModeInfo.IHTotal / 2;
        //usTemp += stModeInfo.IHTotal / 2;

        CScalerSetByte(_IV_DV_DELAY_CLK_EVEN_42, ((usTemp - 16) / 16));

        CScalerSetBit(_FS_DELAY_FINE_TUNING_43, ~_BIT1, _BIT1);
        CScalerSetBit(_IPV_ACT_LEN_H_1A, 0xff, 0x20); //forster modified 061123 to fix the frame sync problem

    }
}

//--------------------------------------------------
// Description  : Calculate the suitable IVS to DVS delay
//                CR[38] : IVS to DVS delay in IHS lines
//                CR[1E] : IVS to DVS delay in ICLK * 16
// Input Value  : Scaling setting
// Output Value : IV to DV delay lines
//--------------------------------------------------
BYTE CAdjustIVS2DVSDelay(BYTE ucOption)
{
    ((DWORD *)pData)[0] = ((DWORD)stDisplayInfo.DHTotal * stDisplayInfo.DVStartPos) + Panel.DHStartPos;
//    ((DWORD *)pData)[0] = ((DWORD)stDisplayInfo.DHTotal * Panel.DVStartPos) + Panel.DHStartPos;
    ((DWORD *)pData)[0] = ((DWORD *)pData)[0] * stModeInfo.IVHeight / stDisplayInfo.DVHeight * stModeInfo.IHTotal / stDisplayInfo.DHTotal;
    ((DWORD *)pData)[1] = ((DWORD)stModeInfo.IHTotal * (stModeInfo.IVStartPos - (ucVStartBias + _PROGRAM_VDELAY))) + stModeInfo.IHStartPos - (ucHStartBias + _PROGRAM_HDELAY);

    if (_GET_INPUT_SOURCE() !=_SOURCE_DVI && _GET_INPUT_SOURCE() !=_SOURCE_HDMI)
    {
        ((DWORD *)pData)[0] = ((DWORD)stDisplayInfo.DHTotal * Panel.DVStartPos) + Panel.DHStartPos;
        ((DWORD *)pData)[0] = ((DWORD *)pData)[0] * stModeInfo.IVHeight / stDisplayInfo.DVHeight * stModeInfo.IHTotal / stDisplayInfo.DHTotal;
        ((DWORD *)pData)[1] = ((DWORD)stModeInfo.IHTotal * (stModeInfo.IVStartPos - (ucVStartBias + _PROGRAM_VDELAY))) + stModeInfo.IHStartPos - (ucHStartBias + _PROGRAM_HDELAY);
    }

    if(ucOption & _BIT0)
    {
        // V scale-up. Target 2.50 IHS delay
        // Reg[40] = 0 ==> Delay 1 line
        //((DWORD *)pData)[1] += (stModeInfo.IHTotal * 1) + 640;
        //eric 20070620
        CScalerPageSelect(_PAGE6);
        //if((CScalerGetBit(_P6_UZD_CTRL0_E3, _BIT1 | _BIT0)) && (~(bit)(CScalerGetBit(_P6_UZD_CTRL0_E3, _BIT4))))
#if(_DE_INTERLACE_SUPPORT == _ON)        
        if (bSourceVideo())
        {
            if (stDisplayInfo.DHWidth < 700)
                ((DWORD *)pData)[1] += (stModeInfo.IHTotal * 2) + 640;
            else
            {
                if((~(bit)(CScalerGetBit(_P6_UZD_CTRL0_E3, _BIT4))) &&(CScalerGetBit(_P6_UZD_CTRL0_E3, _BIT1))&&(CScalerGetBit(_P6_UZD_CTRL0_E3, _BIT0)))
                    ((DWORD *)pData)[1] += (stModeInfo.IHTotal * 2) + 640;
                else
                    ((DWORD *)pData)[1] += (stModeInfo.IHTotal *1) + 640;
            }
        }
        else
        {
            if(stModeInfo.IVHeight <= 288)
            { 
                if((~(bit)(CScalerGetBit(_P6_UZD_CTRL0_E3, _BIT4))) &&(CScalerGetBit(_P6_UZD_CTRL0_E3, _BIT1))&&
                   (CScalerGetBit(_P6_UZD_CTRL0_E3, _BIT0)) && (Panel.DHWidth > 700)) // EricLee 0402 add for YPbPr
                    ((DWORD *)pData)[1] += (stModeInfo.IHTotal * 3) + 640;
                else
                    ((DWORD *)pData)[1] += (stModeInfo.IHTotal *2) + 640;
            }
            else
            { 
                if((~(bit)(CScalerGetBit(_P6_UZD_CTRL0_E3, _BIT4))) &&(CScalerGetBit(_P6_UZD_CTRL0_E3, _BIT1))&&
                   (CScalerGetBit(_P6_UZD_CTRL0_E3, _BIT0)) && (Panel.DHWidth > 700)) // EricLee 0402 add for YPbPr
                    ((DWORD *)pData)[1] += (stModeInfo.IHTotal * 2) + 640;
                else
                    ((DWORD *)pData)[1] += (stModeInfo.IHTotal *1) + 640;
            }
        }
#else
        if (bSourceVideo() && stDisplayInfo.DHWidth < 700)
            ((DWORD *)pData)[1] += (stModeInfo.IHTotal * 2) + 640;
        else
        {
            if((~(bit)(CScalerGetBit(_P6_UZD_CTRL0_E3, _BIT4))) &&(CScalerGetBit(_P6_UZD_CTRL0_E3, _BIT1))&&(CScalerGetBit(_P6_UZD_CTRL0_E3, _BIT0)))
                ((DWORD *)pData)[1] += (stModeInfo.IHTotal * 2) + 640;
            else
                ((DWORD *)pData)[1] += (stModeInfo.IHTotal *1) + 640;
        }
#endif

    }
    else
    {
        if (ucOption & _BIT1)
        {
            // V scale-down. Target 1.75 IHS delay
            ((DWORD *)pData)[1]  += stModeInfo.IHTotal + ((DWORD)640 * stModeInfo.IVHeight / stDisplayInfo.DVHeight);
        }
        else
        {
            // V no scaling. Target 1.50 IHS delay
            ((DWORD *)pData)[1]  += stModeInfo.IHTotal + 640;
        }

        // Turn on full-line buffer
        ((DWORD *)pData)[1]  += stModeInfo.IHTotal;
        CScalerSetBit(_SCALE_CTRL_32, ~_BIT4, _BIT4);

    }

    if (((DWORD *)pData)[0] > ((DWORD *)pData)[1])
    {
        // You should never get into this code ....
    }

    ((DWORD *)pData)[0]  = ((DWORD *)pData)[1] - ((DWORD *)pData)[0];

    pData[14] = ((DWORD *)pData)[0] / stModeInfo.IHTotal;
    pData[15] = (((DWORD *)pData)[0] - ((DWORD)stModeInfo.IHTotal * pData[14])) / 16;

    CScalerSetBit(_FS_DELAY_FINE_TUNING_43, ~_BIT1, 0x00);
    CScalerSetByte(_IVS2DVS_DELAY_LINES_40, pData[14]);
    CScalerSetByte(_IV_DV_DELAY_CLK_ODD_41, pData[15]);

    return pData[14];
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void CAdjustUpdateCenterData(void)
{
    WORD delta;

    stModeUserCenterData.CenterHPos     = stModeUserData.HPosition;
    stModeUserCenterData.CenterVPos     = stModeUserData.VPosition;

    CAdjustCheckAdcClockRange(stModeUserData.Clock, &delta);

    if(delta < _CLOCK_BIAS)
    {
        stModeUserCenterData.CenterClock = stModeInfo.IHTotal;
    }
    else
    {
        if(stModeUserData.Clock < stModeInfo.IHTotal)
        {
            if((stModeUserData.Clock - stModeInfo.IHTotal + delta) < _CLOCK_BIAS)
            {
                stModeUserCenterData.CenterClock = stModeInfo.IHTotal - delta + _CLOCK_BIAS;
            }
            else
            {
                stModeUserCenterData.CenterClock = stModeUserData.Clock;
            }
        }
        else
        {
            if((stModeInfo.IHTotal + delta - stModeUserData.Clock) < _CLOCK_BIAS)
            {
                stModeUserCenterData.CenterClock = stModeInfo.IHTotal + delta - _CLOCK_BIAS;
            }
            else
            {
                stModeUserCenterData.CenterClock = stModeUserData.Clock;
            }
        }
    }
}

//--------------------------------------------------
// Description  : Check if the ADC clock (IHTotal) is out of range. Range = (BackPorch + FrontPorch) * 2 / 5 .
// Input Value  : usClock   --> ADC Clock (IHTotal)
// Output Value : Return _TRUE if not out of range
//--------------------------------------------------
bit CAdjustCheckAdcClockRange(WORD usClock, WORD *delta)
{
    *delta   = (stModeInfo.IHTotal - stModeInfo.IHWidth * 8 / 10) / 2;

    if((usClock > stModeInfo.IHTotal) && ((usClock - stModeInfo.IHTotal) > *delta))
        return _FALSE;

    if((usClock <= stModeInfo.IHTotal) && ((stModeInfo.IHTotal - usClock) > *delta))
        return _FALSE;

    // yc 060222 for usClock error no display
    if(usClock < (stModeInfo.IHStartPos + _CAPTURE_HDELAY - (ucHStartBias + _PROGRAM_HDELAY) + stModeInfo.IHWidth))
        return _FALSE;

    return _TRUE;
}

//080324
#if(1)
//--------------------------------------------------
// Description  : Set ADC clock (IHTotal)
// Input Value  : usClock   --> Target ADC clock
// Output Value : None
//--------------------------------------------------
#define _G_VALUE_DIVIDER_0  4
#define _G_VALUE_DIVIDER_1  16
#define _G_VALUE_DIVIDER_2  64
#define _G_VALUE_DIVIDER_3  128
#define _G_VALUE_DIVIDER_4  256
#define _G_VALUE_DIVIDER_5  512

//cyyeh 20080222 start
void CAdjustAdcClock(WORD usClock , BYTE ucControl)
{
    DWORD pllclock, icode;
    BYTE mcode;
    SBYTE STemp;
    WORD pcode;
    BYTE vco_divider = 2;

    if(ucControl == 1)
        CAdjustAPLLFastLock(usClock);
    else if(ucControl == 2)
        CAdjustAdcClock_OSD(usClock);
    else
    {
        CAdjustEnableWatchDog(_WD_DV_TIMEOUT);
        CScalerPageSelect(_PAGE1);
/********************************************************
Fvco : Frequency of APLL
Fxtal : Frequency of Crystal
IHF : Input Horizontal Frequency
usClock : Divider number of input clock
stModeInfo.IHFreq = 10 * IHF(in KHz)
_RTD_XTAl : Defined crystal clock unit in KHz
 
Fvco = Fxtal*(M + K/16)/N1 = IHF * usClock * vco_divider
Assum N1 = 2
(M + K/16) = IHF * usClock * N1 * vco_divider / Fxtal
stModeInfo.IHFreq UINT in 100Hz
*********************************************************/
        //ADC sampling clock, UNIT in KHz
        pllclock = (DWORD)stModeInfo.IHFreq * usClock / 10;  
        vco_divider = pllclock < 100000 ? 4 : 2;   
        //Get (M + K/16) * 1024
        pllclock  = ((pllclock * _APLL_N_CODE * vco_divider) << 10 ) / _RTD_XTAL;
        CScalerPageSelect(_PAGE1);
        CScalerSetByte(_P1_PLL_DIV_CTRL_A0, 0x08);
        CScalerSetByte(_P1_DDS_MIX_2_B9, 0xff);
        CScalerSetByte(_P1_PLL_CRNT_AE, 0x65);
        CScalerSetBit(_P1_PLLDIV_H_B1, ~(_BIT6 | _BIT5 | _BIT4), (vco_divider == 2) ? (_BIT6 | _BIT5) : (_BIT6 | _BIT5 | _BIT4));
        //Set the divide number
        CScalerSetBit(_P1_PLLDIV_H_B1, 0xf0, (BYTE)(((usClock - 1) >> 8) & 0x0f));
        CScalerSetByte(_P1_PLLDIV_L_B2, (BYTE)((usClock - 1) & 0x00ff));
        CAdjustGetAPLLSetting(usClock);
        //Set N code
        CScalerSetBit(_P1_PLL_N_AD, 0xf8, ((_APLL_N_CODE - 2) & 0x07));
        //Get M, K code, M + K/16 = pllclock / 1024
        mcode = pllclock >> 10; //M is the integer part
        //CScalerSetByte(0x04,mcode );
        //K is the fraction part quantized by 16
        STemp = ((DWORD)pllclock - ((DWORD)mcode << 10)) >> 6;
        //K is range from -8 ~ 7
        if(STemp>7)
        {
            mcode +=1;
            STemp -= 16;
        }
        else if(STemp<(-8))
        {
            mcode -=1;
            STemp += 16;
        }
        //set M, N, K code
        CScalerSetByte(_P1_PLL_M_AC, (mcode - 3)); 
        CScalerSetBit(_P1_PLL_N_AD, 0x0f, (((STemp & 0x0f) << 4) | (_APLL_N_CODE - 2)));
        CScalerSetByte(0xA4, 0x80);
        CTimerDelayXms(1);
        CScalerRead(0xA4, 2, pData, _AUTOINC);
        usPEValue =  ( ((pData[0]&0x0F)<<8) | pData[1] );
        usPEValue = 1000000/(usPEValue*(_RTD_XTAL/1000));   // unit : ps
/****************************************************************************
    Formula :

      I_gain       Ths                    PE(UNIT)                   1
    --------- x  ------- = ------------------------------------ x  -----
       2^22        Tbck        Txclk x 16N/(16M +- K) x 1/16         8

      I_gain         Ths                      PE(UNIT)                   1
    --------- x  ----------- = ------------------------------------ x  -----
       2^22       Tclk x N         Txclk x 16N/(16M +- K) x 1/16         8

               2^22 x PE_U x (16M +- K)        1
    I_gain = ----------------------------- x -----
                         Ths                   8

        2^19 x PE_U x (16M +- K)   
    = -----------------------------
                  Ths              

    = IHF x 2^19 x PE_U x (16M +- K)
****************************************************************************/
// (M + K/16) = pllclock / 1024
// 16M + K = 16 * pllclock / 1024
// 2^19 * 2^4 / 2^10 = 2^13
// _PE_VALUE UNIT is ps, so result has to multiply 10^(-12)
// stModeInfo.IHFreq/10 UNIT is KHz, so result has to multiply 10^2
    /*
        icode = (DWORD)((stModeInfo.IHFreq) * usPEValue * pllclock) / (DWORD)1220702;
        icode &= 0x00007fff;
        CScalerSetByte(_P1_I_CODE_M_A1,(BYTE)(icode >> 8));
        CScalerSetByte(_P1_I_CODE_L_A2, (BYTE)icode);
        // Set the P code
        pcode = (7 * icode * _RTD_XTAL / stModeInfo.IHFreq /_APLL_N_CODE) >> 7;
    //    pcode = 0xC0;
    //*/
    ///*    whhsiao 20080227 update-start
        icode = (DWORD)((stModeInfo.IHFreq) * usPEValue * pllclock) / (DWORD)1220703;
        //icode = icode>>2;   // n=32
        icode = icode>>6;   // n=512
        icode &= 0x00007fff;
    
        CScalerSetByte(_P1_I_CODE_M_A1,(BYTE)(icode >> 8));
        CScalerSetByte(_P1_I_CODE_L_A2, (BYTE)icode);
    
        // Set the P code
        //pcode = (5 * icode * _RTD_XTAL / (stModeInfo.IHFreq/10) / _APLL_N_CODE ) >> 7;    // Total gain=(1+5)/32
        pcode = (63 * icode * _RTD_XTAL / (stModeInfo.IHFreq/10) / _APLL_N_CODE ) >> 7;    // Total gain=(1+63)/512
    //    pcode = 0xC0;
    //*/    whhsiao 20080227 update-end
        if(pcode > 255)
        {
            for(pData[0] = 9; pData[0] < 15; pData[0]++)
            {
                if((pcode >> pData[0]) == 0)
                    break;
            }
            switch(pData[0]-9)//yc 20080225 
            {
                case 0:
                    pcode = pcode / _G_VALUE_DIVIDER_0;
                    break;
                case 1:
                    pcode = pcode / _G_VALUE_DIVIDER_1;
                    break;
                case 2:
                    pcode = pcode / _G_VALUE_DIVIDER_2;
                    break;
                case 3:
                    pcode = pcode / _G_VALUE_DIVIDER_3;
                    break;
                case 4:
                    pcode = pcode / _G_VALUE_DIVIDER_4;
                    break;
                case 5:
                    pcode = pcode / _G_VALUE_DIVIDER_5;
                    break;
                default:
                    break;
            }
            //pcode = pcode / g_value_divider[(pData[0] - 9)];
            STemp = pData[0] - 7;
        }
    
        if(pcode==0)
        pcode = 1;
    
        //g_value = 0x01;
        CScalerSetByte(_P1_P_CODE_MAPPING_METHOD_B6, STemp << 2);
    
        CScalerSetByte(_P1_DDS_MIX_2_B9, 0x05); //set the P_code_max
        CScalerSetByte(_P1_DDS_MIX_3_BA, 0x1e);
        CScalerSetByte(_P1_P_CODE_A3, (BYTE)pcode);
    
        CScalerSetByte(_P1_PLLPHASE_CTRL1_B4, 0x00);
    
        CTimerWaitForEvent(_EVENT_IEN_STOP);
        CTimerWaitForEvent(_EVENT_IEN_STOP);
    
        pData[0] = 32;
        do
        {
            CScalerSetBit(_P1_PLLDIV_H_B1, 0xf0, (BYTE)(((usClock - 1) >> 8) & 0x0f));
            CScalerSetByte(_P1_PLLDIV_L_B2, (BYTE)((usClock - 1) & 0x00ff));
            CScalerSetByte(_P1_PLLPHASE_CTRL1_B4, 0x00);
    
            CTimerWaitForEvent(_EVENT_IEN_STOP);
            CTimerWaitForEvent(_EVENT_IEN_STOP);
    
        }while(CAdjustGetAPLLSetting(usClock) && --pData[0]);
    
        CPowerADCAPLLOn();
        
    
        CTimerWaitForEvent(_EVENT_IEN_STOP);
        CTimerWaitForEvent(_EVENT_IEN_STOP);
        CTimerWaitForEvent(_EVENT_IEN_STOP);
    
        CAdjustGetAPLLSetting(usClock);
    
        CScalerSetByte(_P1_FAST_PLL_CTRL_AA, 0x00);
    
        CMiscClearStatusRegister();

    }
}

void CAdjustAPLLFastLock(WORD usClock)
{
    DWORD delta, pll_divider , pll_divider_k , pllclock , pll_divider_old ;
    BYTE mcode ;
    SBYTE kcode , delta_k , final_k , delta_m=0;
    DWORD sum_i_now;
    ///*    whhsiao 20080227 update-start
    SDWORD sum_i_now_temp[2]={0,0};
    BYTE  times;
    //*/    whhsiao 20080227 update-end

    //ADC sampling clock, UNIT in KHz
    pllclock = (DWORD)stModeInfo.IHFreq * usClock / 10;
    mcode = pllclock < 100000 ? 4 : 2;
    //Get (M + K/16) * 1024
    pll_divider_old  = (((pllclock * _APLL_N_CODE * mcode) << 10 ) / _RTD_XTAL) << 3;
    CScalerPageSelect(_PAGE1);
/*
    CScalerSetByte(_P1_FAST_PLL_CTRL_AA, 0x04);
    CTimerDelayXms(1);
    CScalerSetByte(_P1_FAST_PLL_CTRL_AA, 0x03);
    CScalerRead(_P1_FAST_PLL_ISUM_AB, 4, pData, _NON_AUTOINC);

    sum_i_now = ( (((DWORD)pData[0]<<24)&0x7000000) | (((DWORD)pData[1]<<16)&0xff0000)| (((DWORD)pData[2]<<8)&0xff00) | ((DWORD)pData[3]&0xff)) ;
*/
///*    whhsiao 20080227 update-start
    for (times=0;times<10;times++)
    {
    CScalerSetByte(_P1_FAST_PLL_CTRL_AA, 0x04);
    CTimerDelayXms(1);
    CScalerSetByte(_P1_FAST_PLL_CTRL_AA, 0x03);
    CScalerRead(_P1_FAST_PLL_ISUM_AB, 4, pData, _NON_AUTOINC);

    sum_i_now_temp[1] = ( (((DWORD)pData[0]<<24)&0x7000000) | (((DWORD)pData[1]<<16)&0xff0000)| (((DWORD)pData[2]<<8)&0xff00) | ((DWORD)pData[3]&0xff)) ;

    if ((sum_i_now_temp[1]>>26) ==1)
        sum_i_now_temp[1] = sum_i_now_temp[1] | 0xF8000000;

    sum_i_now_temp[0] += sum_i_now_temp[1];
    CTimerDelayXms(1);
    }

    if ( (sum_i_now_temp[0]>>31) == 1)
        sum_i_now = ((sum_i_now_temp[0]/(SBYTE)10)^0xFFFFFFFF)+1;
    else
        sum_i_now = sum_i_now_temp[0]/(SBYTE)10;
//*/    whhsiao 20080227 update-end


    // calculate Final K Value    
    delta_k =  sum_i_now >> 22;

    if ( (delta_k>>4) == 1 )
    {  
      delta_k |= 0xE0;
      delta_k +=1;
     }

    CScalerRead(0xAD, 1, pData, _NON_AUTOINC);
    kcode = (pData[0]>>4)&0x0f;

    if ( (kcode>>3) == 1 )
        kcode |= 0xF0;

    final_k = delta_k + kcode ;


    if (final_k < -16)
    {
        delta_m = -1;
        final_k +=16;
    }
    else if (final_k >15)
    {
        delta_m =1 ;
        final_k -=16;
    }

    
    final_k &= 0x0F;

    // calculate Sum_I
    delta = sum_i_now & 0x3fffff;   // 22bits


    // calculate Final M Value 
    CScalerRead(0xAC, 1, pData, _NON_AUTOINC);
    mcode = pData[0]+3;

    if (delta_m>0)
        mcode += 1;
    if (delta_m<0)
        mcode -= 1;

    pll_divider = (DWORD)mcode << 26;

    pll_divider_k = (DWORD)final_k << 22;


    if ( (final_k>>3) == 1 )                                 // final_k 2's 
        pll_divider_k = 0x4000000 - pll_divider_k;


    if ( (final_k>>3) == 1 )
        pll_divider =  pll_divider - pll_divider_k ;
    else
        pll_divider =  pll_divider + pll_divider_k ;


    if ((sum_i_now>>26) ==1)                        // delta 2's
        delta = 0x400000 -  delta;       
  //  else
  //      delta = delta;

        
    if ((sum_i_now>>26) ==1)
        pll_divider = pll_divider - delta ;
    else
        pll_divider = pll_divider + delta ;


    usPllDivider =  pll_divider / usClock ;
    usPllDividerRem =  ((pll_divider % usClock) <<12) / usClock ;

    usIHFreqApllFast =  ((((DWORD)stModeInfo.IHFreq * (pll_divider>>11)) / pll_divider_old) + 2) >> 2;
  
}
//--------------------------------------------------
// Description  : Set ADC clock (IHTotal)
// Input Value  : usClock   --> Target ADC clock
// Output Value : None
//--------------------------------------------------
void CAdjustAdcClock_OSD(WORD usClock)
{
    DWORD delta, pll_divider;
    BYTE mcode;
    WORD pcode;
    SBYTE STemp ;
    CScalerPageSelect(_PAGE1);
#if(_APLL_FAST_LOCK)
    //set the FAST PLL CONTROL
    CScalerSetBit(_P1_FAST_PLL_CTRL_AA, ~(_BIT5 | _BIT1), (_BIT5 | _BIT1));
#endif
    pll_divider = ((usPllDivider * usClock)) + ((usPllDividerRem * usClock)>>12);
    mcode = pll_divider >> 26;
    STemp = (pll_divider>>22) & 0x0F;
    if(STemp>7)
    {
        mcode +=1;
        STemp -= 16;
    }
    else if(STemp<(-8))  // Always False
    {
        mcode -=1;
        STemp += 16;
    }
    delta = pll_divider & 0x003FFFFF;
    CScalerSetBit(_P1_PLLDIV_H_B1, 0xf0, (BYTE)(((usClock - 1) >> 8) & 0x0f));
    CScalerSetByte(_P1_PLLDIV_L_B2, (BYTE)((usClock - 1) & 0x00ff));
    CScalerSetByte(_P1_PLL_M_AC, (mcode - 3)); 
    CScalerSetBit(_P1_PLL_N_AD, 0x0f, (((STemp & 0x0f) << 4) | (_APLL_N_CODE - 2)));
    pData[0] = 0x00;
    pData[1] = (BYTE)((delta >> 16) & 0x0000003f);
    pData[2] = (BYTE)((delta >> 8)  & 0x000000ff);
    pData[3] = (BYTE)((delta << 0)  & 0x000000ff);
    CScalerWrite(_P1_FAST_PLL_ISUM_AB, 4, pData, _NON_AUTOINC);
/****************************************************************************
    PE Calibration Function  // Added by whhsiao 20080213
****************************************************************************/
    CScalerSetByte(0xA4, 0x80);
    CTimerDelayXms(1);
    CScalerRead(0xA4, 2, pData, _AUTOINC);
    usPEValue =  ( ((pData[0]&0x0F)<<8) | pData[1] );
    usPEValue = 1000000/(usPEValue*(_RTD_XTAL/1000));   // unit : ps
/****************************************************************************

    Formula :

      I_gain       Ths                    PE(UNIT)                   1
    --------- x  ------- = ------------------------------------ x  -----
       2^22        Tbck        Txclk x 16N/(16M +- K) x 1/16         8

      I_gain         Ths                      PE(UNIT)                   1
    --------- x  ----------- = ------------------------------------ x  -----
       2^22       Tclk x N         Txclk x 16N/(16M +- K) x 1/16         8

               2^22 x PE_U x (16M +- K)        1
    I_gain = ----------------------------- x -----
                         Ths                   n

        2^22 x PE_U x (16M +- K)        1
    = ----------------------------- x -----
                  Ths                   n

    = IHF x 2^22 x PE_U x (16M +- K) x 2^(-n)

****************************************************************************/
    // (M + K/16) = pllclock / 1024
    // 16M + K = 16 * pllclock / 1024
    // 2^19 * 2^4 / 2^10 = 2^13
    // _PE_VALUE UNIT is ps, so result has to multiply 10^(-12)
    // stModeInfo.IHFreq/10 UNIT is KHz, so result has to multiply 10^2
    pll_divider = (usPEValue * (usIHFreqApllFast/10)) * (pll_divider/(DWORD)100000);  //yc 20080306 
    pll_divider = (pll_divider/10000) >> 9;    // 
    //pll_divider = (pll_divider/10000) >> 8;    // 
    pll_divider &= 0x00007fff;
    CScalerSetByte(_P1_I_CODE_M_A1,(BYTE)(pll_divider >> 8));
    CScalerSetByte(_P1_I_CODE_L_A2, (BYTE)pll_divider);
    // Set the P code
    pcode = (WORD) ((63*pll_divider * (_RTD_XTAL/_APLL_N_CODE) / (usIHFreqApllFast/10) ) >> 7); // Total Gain = 65/512
    STemp=1;
    if(pcode > 255)
    {
        for(pData[0] = 9; pData[0] < 15; pData[0]++)
        {
            if((pcode >> pData[0]) == 0)
                break;
        }
        switch(pData[0]-9)//yc 20080225 
        {
            case 0:
                pcode = pcode / _G_VALUE_DIVIDER_0;
                break;
            case 1:
                pcode = pcode / _G_VALUE_DIVIDER_1;
                break;
            case 2:
                pcode = pcode / _G_VALUE_DIVIDER_2;
                break;
            case 3:
                pcode = pcode / _G_VALUE_DIVIDER_3;
                break;
            case 4:
                pcode = pcode / _G_VALUE_DIVIDER_4;
                break;
            case 5:
                pcode = pcode / _G_VALUE_DIVIDER_5;
                break;
            default:
                break;
        }
        STemp = pData[0] - 7;
    }
    if(pcode==0x00)
        pcode = 0x01;
    CScalerSetByte(_P1_P_CODE_MAPPING_METHOD_B6, STemp << 2);
    CScalerSetByte(_P1_DDS_MIX_2_B9, 0xFF); //set the P_code_max
    CScalerSetByte(_P1_DDS_MIX_3_BA, 0xFF);
    CScalerSetByte(_P1_P_CODE_A3, (BYTE)pcode); 
#if(_APLL_FAST_LOCK) //yc 20080225
    //CScalerSetBit(_P1_FAST_PLL_CTRL_AA, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
    CAdjustDisableWatchDog(_WD_APLL_NONLOCK);
    CScalerSetBit(_P1_FAST_PLL_CTRL_AA, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
    CTimerDelayXms(100); 
    CAdjustEnableWatchDog(_WD_APLL_NONLOCK);
#else
    //Enable Double buffer write in PLL M/N K¡BPLLDIV¡BDDS SUM_I
    CScalerSetBit(_P1_FAST_PLL_CTRL_AA, ~_BIT4, _BIT4);
#endif
    CMiscClearStatusRegister();
}

// Eric 0617 add for YPbPr
void CAdjustAdcClockYPbPr(WORD usClock)
{
    //#define _PE_VALUE   175 // Unit: ps
    DWORD pllclock, icode, SUM_I;
    BYTE mcode;
    SBYTE kcode,g_value = 1;
    WORD delta, pcode;
    static BYTE vco_divider = 2;
    BYTE g_value_divider[6] = {4, 16, 64, 128, 256, 512};
#if (_APLL_FAST_LOCK)
    DWORD temp2662;
#endif


    if(bDoAspectRatioFlag == _FALSE && bDoAutoConfigFlag == _FALSE)
        CAdjustEnableWatchDog(_WD_DV_TIMEOUT);
    CScalerPageSelect(_PAGE1);

#if(_APLL_FAST_LOCK)
    //set the FAST PLL CONTROL
    CScalerSetBit(_P1_FAST_PLL_CTRL_AA, ~(_BIT5 | _BIT1), (_BIT5 | _BIT1));
#endif
    /********************************************************
    Fvco : Frequency of APLL
    Fxtal : Frequency of Crystal
    IHF : Input Horizontal Frequency
    usClock : Divider number of input clock
    stModeInfo.IHFreq = 10 * IHF(in KHz)
    _RTD_XTAl : Defined crystal clock unit in KHz

    Fvco = Fxtal*(M + K/16)/N1 = IHF * usClock * vco_divider
    Assum N1 = 2
    (M + K/16) = IHF * usClock * N1 * vco_divider / Fxtal
    stModeInfo.IHFreq UINT in 100Hz
    *********************************************************/

    //ADC sampling clock, UNIT in KHz
    pllclock = (DWORD)stModeInfo.IHFreq * usClock / 10;

    vco_divider = pllclock < 100000 ? 4 : 2;

    //Get (M + K/16) * 1024
    pllclock  = ((((pllclock * _APLL_N_CODE * vco_divider) << 4 )/(DWORD)(_RTD_XTAL)) << 6);

    CScalerPageSelect(_PAGE1);
    CScalerSetByte(_P1_PLL_DIV_CTRL_A0, 0x08);
//  CScalerSetByte(_P1_FAST_PLL_CTRL_AA, 0x24);  //Ming-Yen
//  CScalerSetByte(_P1_PE_TRACKING_METHOD_B7, 0x02); //Ming-Yen
//  CScalerSetByte(_P1_DDS_MIX_1_B8, 0x0c);   //Ming-Yen
    CScalerSetByte(_P1_DDS_MIX_2_B9, 0xff);
    CScalerSetByte(_P1_PLL_CRNT_AE, 0x63);
    
    //CScalerSetByte(_P1_PLL_WD_AF, 0x08);

    CScalerSetBit(_P1_PLLDIV_H_B1, ~(_BIT6 | _BIT5 | _BIT4), (vco_divider == 2) ? (_BIT6 | _BIT5) : (_BIT6 | _BIT5 | _BIT4));

       

    //Set the divide number
    CScalerSetBit(_P1_PLLDIV_H_B1, 0xf0, (BYTE)(((usClock - 1) >> 8) & 0x0f));
    CScalerSetByte(_P1_PLLDIV_L_B2, (BYTE)((usClock - 1) & 0x00ff));


////////////////////////////////////////
      CAdjustGetAPLLSetting(usClock);
////////////////////////////////////////


    //Set N code
    CScalerSetBit(_P1_PLL_N_AD, 0xf8, ((_APLL_N_CODE - 2) & 0x07));

    //Get M, K code, M + K/16 = pllclock / 1024
    mcode = pllclock >> 10; //M is the integer part
    delta = (DWORD)pllclock - ((DWORD)mcode << 10);

    //K is the fraction part quantized by 16
    kcode = (delta) >> 6; 

#if(_APLL_FAST_LOCK)
    //SUM_I is the truncated part by calculation quantized by 1024
    SUM_I = ((DWORD)delta << 4) - ((DWORD)kcode << 10); 
#endif  

    //K is range from -8 ~ 7
    if(kcode>7)
    {
        mcode +=1;
        kcode -= 16;
    }
    else if(kcode<(-8))
    {
        mcode -=1;
        kcode += 16;
    }

    //set M, N, K code
    CScalerSetByte(_P1_PLL_M_AC, (mcode - 3)); 
    CScalerSetBit(_P1_PLL_N_AD, 0x0f, (((kcode & 0x0f) << 4) | (_APLL_N_CODE - 2)));

#if (_APLL_FAST_LOCK)
    SUM_I = SUM_I << 12; // over flow need to modify
    //set SUM_I
    temp2662 = SUM_I & 0x07ffffff;
    pData[0] = (BYTE)((temp2662 >>24) & 0x000000ff);
    pData[1] = (BYTE)((temp2662 >>16) & 0x000000ff);
    pData[2] = (BYTE)((temp2662 >>8) & 0x000000ff);
    pData[3] = (BYTE)(temp2662 & 0x000000ff);
    CScalerWrite(_P1_FAST_PLL_ISUM_AB, 4, pData, _NON_AUTOINC);
#endif


/****************************************************************************

    Formula :

      I_gain       Ths                    PE(UNIT)                   1
    --------- x  ------- = ------------------------------------ x  -----
       2^22        Tbck        Txclk x 16N/(16M +- K) x 1/16         8

      I_gain         Ths                      PE(UNIT)                   1
    --------- x  ----------- = ------------------------------------ x  -----
       2^22       Tclk x N         Txclk x 16N/(16M +- K) x 1/16         8

               2^22 x PE_U x (16M +- K)        1
    I_gain = ----------------------------- x -----
                         Ths                   8

        2^19 x PE_U x (16M +- K)
    = -----------------------------
                  Ths

    = IHF x 2^19 x PE_U x (16M +- K)

****************************************************************************/

    // (M + K/16) = pllclock / 1024
    // 16M + K = 16 * pllclock / 1024
    // 2^19 * 2^4 / 2^10 = 2^13
    // _PE_VALUE UNIT is ps, so result has to multiply 10^(-12)
    // stModeInfo.IHFreq/10 UNIT is KHz, so result has to multiply 10^2

    icode = (DWORD)((stModeInfo.IHFreq) * 120/*usPEValue*/ * pllclock)/(DWORD)1220702;
    icode &= 0x00007fff;

    CScalerSetByte(_P1_I_CODE_M_A1,(BYTE)(icode >> 8));
    CScalerSetByte(_P1_I_CODE_L_A2, (BYTE)icode);

    // Set the P code
    pcode = (7 * icode * _RTD_XTAL / stModeInfo.IHFreq /_APLL_N_CODE) >> 7;
    
    if(pcode > 255)
    {
        for(pData[0] = 9; pData[0] < 15; pData[0]++)
        {
            if((pcode >> pData[0]) == 0)
                break;
        }
        pcode = pcode / g_value_divider[(pData[0] - 9)];
        g_value = pData[0] - 7;
    }

    CScalerSetByte(_P1_P_CODE_MAPPING_METHOD_B6, g_value << 2);
    CScalerSetByte(_P1_DDS_MIX_2_B9, 0x05); //set the P_code_max
    CScalerSetByte(_P1_DDS_MIX_3_BA, 0x1e);
    CScalerSetByte(_P1_P_CODE_A3, (BYTE)pcode);

#if (_APLL_FAST_LOCK)
    //CScalerSetByte(_P1_FAST_PLL_CTRL_AA, 0x60);
    CScalerSetBit(_P1_FAST_PLL_CTRL_AA, ~(_BIT6 | _BIT5 | _BIT3), (_BIT6 | _BIT5 | _BIT3));
#else
    //Enable Double buffer write in PLL M/N K¡BPLLDIV¡BDDS SUM_I
    CScalerSetBit(_P1_FAST_PLL_CTRL_AA, ~_BIT4, _BIT4);
#endif

    CScalerSetByte(_P1_PLLPHASE_CTRL1_B4, 0x00);

    CTimerWaitForEvent(_EVENT_IEN_STOP);
    CTimerWaitForEvent(_EVENT_IEN_STOP);

    pData[0] = 32;
    do
    {
        CScalerSetBit(_P1_PLLDIV_H_B1, 0xf0, (BYTE)(((usClock - 1) >> 8) & 0x0f));
        CScalerSetByte(_P1_PLLDIV_L_B2, (BYTE)((usClock - 1) & 0x00ff));
        CScalerSetByte(_P1_PLLPHASE_CTRL1_B4, 0x00);

     //   CTimerWaitForEvent(_EVENT_IEN_STOP);
       // CTimerWaitForEvent(_EVENT_IEN_STOP);

    }while(CAdjustGetAPLLSetting(usClock) && --pData[0]);

    CPowerADCAPLLOn();
    //DebugPrintf("\n CPowerADCAPLLOn ... ",0x20);
    
    CTimerWaitForEvent(_EVENT_IEN_STOP);
    CTimerWaitForEvent(_EVENT_IEN_STOP);
    CTimerWaitForEvent(_EVENT_IEN_STOP);
        
    CAdjustGetAPLLSetting(usClock);
        
    CScalerSetByte(_P1_FAST_PLL_CTRL_AA, 0x00);
        
    CMiscClearStatusRegister();
        
    if (bDoAspectRatioFlag == _FALSE && bDoAutoConfigFlag == _FALSE)
       CAdjustEnableWatchDog(_WD_ALL);
}

#else

//--------------------------------------------------
// Description  : Set ADC clock (IHTotal)
// Input Value  : usClock   --> Target ADC clock
// Output Value : None
//--------------------------------------------------
void CAdjustAdcClock(WORD usClock)
{
    //#define _PE_VALUE   175 // Unit: ps
    DWORD pllclock, icode, SUM_I;
    BYTE mcode;
    SBYTE kcode,g_value = 1;
    WORD delta, pcode;
    static BYTE vco_divider = 2;
    BYTE g_value_divider[6] = {4, 16, 64, 128, 256, 512};
#if (_APLL_FAST_LOCK)
    DWORD temp2662;
#endif


    if(bDoAspectRatioFlag == _FALSE && bDoAutoConfigFlag == _FALSE)
        CAdjustEnableWatchDog(_WD_DV_TIMEOUT);
    CScalerPageSelect(_PAGE1);

#if(_APLL_FAST_LOCK)
    //set the FAST PLL CONTROL
    CScalerSetBit(_P1_FAST_PLL_CTRL_AA, ~(_BIT5 | _BIT1), (_BIT5 | _BIT1));
#endif
    /********************************************************
    Fvco : Frequency of APLL
    Fxtal : Frequency of Crystal
    IHF : Input Horizontal Frequency
    usClock : Divider number of input clock
    stModeInfo.IHFreq = 10 * IHF(in KHz)
    _RTD_XTAl : Defined crystal clock unit in KHz

    Fvco = Fxtal*(M + K/16)/N1 = IHF * usClock * vco_divider
    Assum N1 = 2
    (M + K/16) = IHF * usClock * N1 * vco_divider / Fxtal
    stModeInfo.IHFreq UINT in 100Hz
    *********************************************************/

    //ADC sampling clock, UNIT in KHz
    pllclock = (DWORD)stModeInfo.IHFreq * usClock / 10;

    vco_divider = pllclock < 100000 ? 4 : 2;

    //Get (M + K/16) * 1024
    pllclock  = ((((pllclock * _APLL_N_CODE * vco_divider) << 4 )/(DWORD)(_RTD_XTAL)) << 6);

    CScalerPageSelect(_PAGE1);
    CScalerSetByte(_P1_PLL_DIV_CTRL_A0, 0x08);
//  CScalerSetByte(_P1_FAST_PLL_CTRL_AA, 0x24);  //Ming-Yen
//  CScalerSetByte(_P1_PE_TRACKING_METHOD_B7, 0x02); //Ming-Yen
//  CScalerSetByte(_P1_DDS_MIX_1_B8, 0x0c);   //Ming-Yen
    CScalerSetByte(_P1_DDS_MIX_2_B9, 0xff);
    CScalerSetByte(_P1_PLL_CRNT_AE, 0x63);
    
    //CScalerSetByte(_P1_PLL_WD_AF, 0x08);

    CScalerSetBit(_P1_PLLDIV_H_B1, ~(_BIT6 | _BIT5 | _BIT4), (vco_divider == 2) ? (_BIT6 | _BIT5) : (_BIT6 | _BIT5 | _BIT4));

       

    //Set the divide number
    CScalerSetBit(_P1_PLLDIV_H_B1, 0xf0, (BYTE)(((usClock - 1) >> 8) & 0x0f));
    CScalerSetByte(_P1_PLLDIV_L_B2, (BYTE)((usClock - 1) & 0x00ff));


////////////////////////////////////////
      CAdjustGetAPLLSetting(usClock);
////////////////////////////////////////


    //Set N code
    CScalerSetBit(_P1_PLL_N_AD, 0xf8, ((_APLL_N_CODE - 2) & 0x07));

    //Get M, K code, M + K/16 = pllclock / 1024
    mcode = pllclock >> 10; //M is the integer part
    delta = (DWORD)pllclock - ((DWORD)mcode << 10);

    //K is the fraction part quantized by 16
    kcode = (delta) >> 6; 

#if(_APLL_FAST_LOCK)
    //SUM_I is the truncated part by calculation quantized by 1024
    SUM_I = ((DWORD)delta << 4) - ((DWORD)kcode << 10); 
#endif  

    //K is range from -8 ~ 7
    if(kcode>7)
    {
        mcode +=1;
        kcode -= 16;
    }
    else if(kcode<(-8))
    {
        mcode -=1;
        kcode += 16;
    }

    //set M, N, K code
    CScalerSetByte(_P1_PLL_M_AC, (mcode - 3)); 
    CScalerSetBit(_P1_PLL_N_AD, 0x0f, (((kcode & 0x0f) << 4) | (_APLL_N_CODE - 2)));

#if (_APLL_FAST_LOCK)
    SUM_I = SUM_I << 12; // over flow need to modify
    //set SUM_I
    temp2662 = SUM_I & 0x07ffffff;
    pData[0] = (BYTE)((temp2662 >>24) & 0x000000ff);
    pData[1] = (BYTE)((temp2662 >>16) & 0x000000ff);
    pData[2] = (BYTE)((temp2662 >>8) & 0x000000ff);
    pData[3] = (BYTE)(temp2662 & 0x000000ff);
    CScalerWrite(_P1_FAST_PLL_ISUM_AB, 4, pData, _NON_AUTOINC);
#endif


/****************************************************************************

    Formula :

      I_gain       Ths                    PE(UNIT)                   1
    --------- x  ------- = ------------------------------------ x  -----
       2^22        Tbck        Txclk x 16N/(16M +- K) x 1/16         8

      I_gain         Ths                      PE(UNIT)                   1
    --------- x  ----------- = ------------------------------------ x  -----
       2^22       Tclk x N         Txclk x 16N/(16M +- K) x 1/16         8

               2^22 x PE_U x (16M +- K)        1
    I_gain = ----------------------------- x -----
                         Ths                   8

        2^19 x PE_U x (16M +- K)
    = -----------------------------
                  Ths

    = IHF x 2^19 x PE_U x (16M +- K)

****************************************************************************/

    // (M + K/16) = pllclock / 1024
    // 16M + K = 16 * pllclock / 1024
    // 2^19 * 2^4 / 2^10 = 2^13
    // _PE_VALUE UNIT is ps, so result has to multiply 10^(-12)
    // stModeInfo.IHFreq/10 UNIT is KHz, so result has to multiply 10^2

    icode = (DWORD)((stModeInfo.IHFreq) * 120/*usPEValue*/ * pllclock)/(DWORD)1220702;
    icode &= 0x00007fff;

    CScalerSetByte(_P1_I_CODE_M_A1,(BYTE)(icode >> 8));
    CScalerSetByte(_P1_I_CODE_L_A2, (BYTE)icode);

    // Set the P code
    pcode = (7 * icode * _RTD_XTAL / stModeInfo.IHFreq /_APLL_N_CODE) >> 7;
    
    if(pcode > 255)
    {
        for(pData[0] = 9; pData[0] < 15; pData[0]++)
        {
            if((pcode >> pData[0]) == 0)
                break;
        }
        pcode = pcode / g_value_divider[(pData[0] - 9)];
        g_value = pData[0] - 7;
    }

    CScalerSetByte(_P1_P_CODE_MAPPING_METHOD_B6, g_value << 2);
    CScalerSetByte(_P1_DDS_MIX_2_B9, 0x05); //set the P_code_max
    CScalerSetByte(_P1_DDS_MIX_3_BA, 0x1e);
    CScalerSetByte(_P1_P_CODE_A3, (BYTE)pcode);

#if (_APLL_FAST_LOCK)
    //CScalerSetByte(_P1_FAST_PLL_CTRL_AA, 0x60);
    CScalerSetBit(_P1_FAST_PLL_CTRL_AA, ~(_BIT6 | _BIT5 | _BIT3), (_BIT6 | _BIT5 | _BIT3));
#else
    //Enable Double buffer write in PLL M/N K¡BPLLDIV¡BDDS SUM_I
    CScalerSetBit(_P1_FAST_PLL_CTRL_AA, ~_BIT4, _BIT4);
#endif

    CScalerSetByte(_P1_PLLPHASE_CTRL1_B4, 0x00);

    CTimerWaitForEvent(_EVENT_IEN_STOP);
    CTimerWaitForEvent(_EVENT_IEN_STOP);

    pData[0] = 32;
    do
    {
        CScalerSetBit(_P1_PLLDIV_H_B1, 0xf0, (BYTE)(((usClock - 1) >> 8) & 0x0f));
        CScalerSetByte(_P1_PLLDIV_L_B2, (BYTE)((usClock - 1) & 0x00ff));
        CScalerSetByte(_P1_PLLPHASE_CTRL1_B4, 0x00);

     //   CTimerWaitForEvent(_EVENT_IEN_STOP);
       // CTimerWaitForEvent(_EVENT_IEN_STOP);

    }while(CAdjustGetAPLLSetting(usClock) && --pData[0]);

    CPowerADCAPLLOn();
    //DebugPrintf("\n CPowerADCAPLLOn ... ",0x20);
    
    CTimerWaitForEvent(_EVENT_IEN_STOP);
    CTimerWaitForEvent(_EVENT_IEN_STOP);
    CTimerWaitForEvent(_EVENT_IEN_STOP);
        
    CAdjustGetAPLLSetting(usClock);
        
    CScalerSetByte(_P1_FAST_PLL_CTRL_AA, 0x00);
        
    CMiscClearStatusRegister();
        
    if (bDoAspectRatioFlag == _FALSE && bDoAutoConfigFlag == _FALSE)
       CAdjustEnableWatchDog(_WD_ALL);
}

#endif


//--------------------------------------------------
// Description  : Get APLL Setting
// Input Value  : usClock   --> Target ADC clock
// Output Value : None
//--------------------------------------------------
BYTE CAdjustGetAPLLSetting(WORD usClock)
{
    BYTE ucTemp[2];

    usClock -= 1;
    
    CScalerPageSelect(_PAGE1);
    CScalerRead(_P1_PLLDIV_H_B1, 2, ucTemp, _AUTOINC);

    ucTemp[0] &= 0x0f;

    if((ucTemp[0] != (BYTE)(usClock >> 8)) || (ucTemp[1] != (BYTE)(usClock & 0x00ff)))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}


//--------------------------------------------------
// Description  : Set phase
// Input Value  : ucPhase   --> Target phase, ucPhase = N, N = 0 ~ 63
// Output Value : None
//--------------------------------------------------
void CAdjustPhase(BYTE ucPhase)
{
#if(1)
    BYTE ctrl, select;
    //DebugPrintf("\n CAdjustPhase %c",'!');
    
    if (bDoAspectRatioFlag == _FALSE && bDoAutoConfigFlag == _FALSE)
       CAdjustEnableWatchDog(_WD_DV_TIMEOUT_APLL_NONLOCK);

    //Ida added for change range from 0-63 to 0-100
     ucPhase = ucPhase & 0x3f;
    //ucPhase = ((WORD)(ucPhase*64)/101) & 0x3f;

    // Code below is to select stable HSYNC latch edge.
    // There is about 2.025ns delay for RTD2553V between input clock into ADC and output from ADC.
    // Calculating the corresponding phase delay for 2.025ns
    // Original Formula :
    // select = 64 * 2.025 * ulRate / 1000000;

    //select = (DWORD)_RTD_XTAL * stModeInfo.IHTotal / stModeInfo.IHCount * 130 / 1000000;
    select = (DWORD)_RTD_XTAL * stModeInfo.IHTotal / stModeInfo.IHCount * 389 / 1000000;

    select = (select <= 64) ? (64 - select) : (128 - select);

    // Calculate the absolute value from the selected phase to transition
    pData[0]    = (ucPhase >= select) ? ucPhase - select : select - ucPhase;
    ctrl        = (pData[0] > 12 && pData[0] < 52) ? 0x00 : 0x01;

    if((stModeInfo.IHStartPos < stModeUserData.HPosition) && ((stModeUserData.HPosition - stModeInfo.IHStartPos) > ucHStartBias))
        stModeUserData.HPosition = stModeInfo.IHStartPos + ucHStartBias;

    if((stModeInfo.IHStartPos > stModeUserData.HPosition) && ((stModeInfo.IHStartPos - stModeUserData.HPosition) > ucHStartBias))
        stModeUserData.HPosition = stModeInfo.IHStartPos - ucHStartBias;

//    pData[0]    = ucHStartBias + stModeInfo.IHStartPos - stModeUserData.HPosition  + _PROGRAM_HDELAY;
    ((WORD *)pData)[0]  = ucHStartBias + stModeInfo.IHStartPos - stModeUserData.HPosition  + _PROGRAM_HDELAY;


    // Compensate the H position shift due to the phase select
    if (select > 12)
        select  = ((ucPhase + 12) < select) ? (((WORD *)pData)[0] - 1) : ((WORD *)pData)[0];
    else
        select  = (ucPhase < (select + 52)) ? (((WORD *)pData)[0] - 1) : ((WORD *)pData)[0];

    CScalerPageSelect(_PAGE1);

    CScalerSetBit(_P1_PLLDIV_H_B1, ~_BIT6, _BIT6);
    if(((DWORD)stModeInfo.IHFreq * stModeInfo.IHTotal / 1000) < 530)
    {
        CScalerSetBit(_P1_PLLPHASE_CTRL1_B4, 0x80, ucPhase * 2);           // Set phase
    }
    else
    {
        CScalerSetBit(_P1_PLLPHASE_CTRL1_B4, 0x80, ucPhase);               // Set phase
    }

    CAdjustIHSDelay(select);                                        // Compensate IHS delay
    CScalerSetBit(_VGIP_DELAY_CTRL_12, ~_BIT3, (ctrl << 3));        // Select a correct edge to latch the stable data
    
    CMiscApplyDoubleBuffer();
        
    CMiscClearStatusRegister();
    if (bDoAspectRatioFlag == _FALSE && bDoAutoConfigFlag == _FALSE)
       CAdjustEnableWatchDog(_WD_ALL);
#else
    BYTE ctrl, select;
    BYTE pllclock;
    //DebugPrintf("\n CAdjustPhase %c",'!');
    
    if(bDoAspectRatioFlag == _FALSE && bDoAutoConfigFlag == _FALSE)  // for Aspect ratio,hill 20070515  
    CAdjustEnableWatchDog(_WD_DV_TIMEOUT);
    
    //Ida added for change range from 0-63 to 0-100
    ucPhase = ucPhase & 0x3f;
 
    pllclock = (DWORD)stModeInfo.IHFreq * stModeUserData.Clock / 10000;
    if(pllclock < 113)
        select = (138+pllclock)/4;
    else
        select = (pllclock-113)/3;
 
 
    // Calculate the absolute value from the selected phase to transition
    pData[0]    = (ucPhase >= select) ? ucPhase - select : select - ucPhase;
    ctrl = (pData[0] > 12 && pData[0] < 52) ? 0x00 : 0x01;
 
    if((stModeInfo.IHStartPos < stModeUserData.HPosition) && ((stModeUserData.HPosition - stModeInfo.IHStartPos) > ucHStartBias))
        stModeUserData.HPosition = stModeInfo.IHStartPos + ucHStartBias;
 
    if((stModeInfo.IHStartPos > stModeUserData.HPosition) && ((stModeInfo.IHStartPos - stModeUserData.HPosition) > ucHStartBias))
        stModeUserData.HPosition = stModeInfo.IHStartPos - ucHStartBias;
 
//    pData[0]    = ucHStartBias + stModeInfo.IHStartPos - stModeUserData.HPosition  + _PROGRAM_HDELAY;
    ((WORD *)pData)[0]  = ucHStartBias + stModeInfo.IHStartPos - stModeUserData.HPosition  + _PROGRAM_HDELAY;
 

    // Compensate the H position shift due to the phase select
    if (select > 12)
        select  = ((ucPhase + 12) < select) ? (((WORD *)pData)[0] - 1) : ((WORD *)pData)[0];
    else
        select  = (ucPhase < (select + 52)) ? (((WORD *)pData)[0] - 1) : ((WORD *)pData)[0];
    CScalerPageSelect(_PAGE1);
 
    CScalerSetBit(_P1_PLLDIV_H_B1, ~_BIT6, _BIT6);
 
    if((bit)CScalerGetBit(_P1_PLLDIV_H_B1, _BIT4))
    {
        CScalerSetBit(_P1_PLLPHASE_CTRL1_B4, 0x80, ucPhase * 2);           // Set phase
    }
    else
    {
        CScalerSetBit(_P1_PLLPHASE_CTRL1_B4, 0x80, ucPhase);               // Set phase
    }
 
    CAdjustIHSDelay(select);                                        // Compensate IHS delay
    CScalerSetBit(_VGIP_DELAY_CTRL_12, ~_BIT3, (ctrl << 3));        // Select a correct edge to latch the stable data
    
    CMiscApplyDoubleBuffer();
  
    CMiscClearStatusRegister();
  
    if(bDoAspectRatioFlag == _FALSE && bDoAutoConfigFlag == _FALSE)  // for Aspect ratio,hill 20070515  
        CAdjustEnableWatchDog(_WD_DV_TIMEOUT | _WD_FRAMESYNC);
#endif
}

//--------------------------------------------------
// Description  : Set H Position
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustHPosition(void)
{
    // Update IHS delay according to phase
    CAdjustPhase(stModeUserData.Phase);
}

//--------------------------------------------------
// Description  : Set V Position
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustVPosition(void)
{
    if (bDoAspectRatioFlag == _FALSE && bDoAutoConfigFlag == _FALSE)
       CAdjustEnableWatchDog(_WD_APLL_NONLOCK);

    if((stModeInfo.IVStartPos < stModeUserData.VPosition) && ((stModeUserData.VPosition - stModeInfo.IVStartPos) > ucVStartBias))
    {
        stModeUserData.VPosition = stModeInfo.IVStartPos + ucVStartBias;
    }

#if(_V_POSITION_DIRECTION == _V_POSITION_METHOD_0)

    CAdjustIVSDelay(ucVStartBias + stModeInfo.IVStartPos - stModeUserData.VPosition + _PROGRAM_VDELAY);

#endif

#if(_V_POSITION_DIRECTION == _V_POSITION_METHOD_1)

    CAdjustIVSDelay(ucVStartBias - (stModeInfo.IVStartPos - stModeUserData.VPosition) + _PROGRAM_VDELAY);

#endif

    CMiscApplyDoubleBuffer();

    CTimerWaitForEvent(_EVENT_DEN_STOP);
    CTimerWaitForEvent(_EVENT_DEN_START);

    CMiscClearStatusRegister();
    if (bDoAspectRatioFlag == _FALSE && bDoAutoConfigFlag == _FALSE)
       CAdjustEnableWatchDog(_WD_ALL);
}

//--------------------------------------------------
// Description  : Adjust Digital Filter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustDigitalFilter(BYTE ucAccess, BYTE ucOffset, BYTE ucDiv, BYTE ucEnable)
{
    pData[0] = ((ucAccess & 0x0f) << 4) | 0x00;

    if(ucAccess == _YPBPR_ACCESS_PORT)
    {
        pData[1] = ((ucOffset & 0x07) << 5) | 0x10;
    }
    else
    {
        pData[1] = ((ucEnable & 0x01) << 7) | ((ucOffset & 0x07) << 4) | ((ucDiv & 0x03) << 2);
    }

    CScalerWrite(_DIGITAL_FILTER_CTRL_98, 2, pData, _AUTOINC);

    CScalerSetByte(_DIGITAL_FILTER_CTRL_98, 0x00);
}

void CAdjustSetYpbprRhue(void)
{
    CScalerSetBit(_COLOR_CTRL_62,0xc7,0x08);
    CScalerWrite(_SRGB_ACCESS_PORT_63, 6, pData, _NON_AUTOINC);
}

void CAdjustSetYpbprGhue(void)
{
    CScalerSetBit(_COLOR_CTRL_62,0xc7,0x10);
    CScalerWrite(_SRGB_ACCESS_PORT_63, 6, pData, _NON_AUTOINC);
}

void CAdjustSetYpbprBhue(void)
{
    CScalerSetBit(_COLOR_CTRL_62,0xc7,0x18);
    CScalerWrite(_SRGB_ACCESS_PORT_63, 6, pData, _NON_AUTOINC);
}


#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON) || (_YPBPR_SUPPORT == _ON))
void CAdjustInterlaceIVS2DVSProtection(void)
{
    WORD ustemp;
    BYTE temp;

    CScalerRead(_IPV_ACT_LEN_H_1A, 1, pData, _NON_AUTOINC);
    if(pData[0] & 0x20)
    {
      //  CScalerSetBit(_SCALE_CTRL_32, ~(_BIT7 | _BIT6), _BIT7); //forster modified 061102 
        //CScalerSetBit(_VGIP_ODD_CTRL_13, ~_BIT0, _BIT0);

//V400 modify
        CScalerRead(_IV_DV_DELAY_CLK_ODD_41, LENGTH(1), &temp, _NON_AUTOINC);
        ustemp = (WORD)temp * 16 + 16;

        if(ustemp > (stModeInfo.IHTotal / 2))
        {
            ustemp -= stModeInfo.IHTotal / 2;
            CScalerSetByte(_IV_DV_DELAY_CLK_EVEN_42, (ustemp - 16) / 16);
        }
        else
        {
            CScalerSetByte(_IPV_ACT_STA_L_19, CScalerGetBit(_IPV_ACT_STA_L_19, 0xff) + 1);
            ustemp += stModeInfo.IHTotal;
            CScalerSetByte(_IV_DV_DELAY_CLK_ODD_41, (ustemp - 16) / 16);
            ustemp -= stModeInfo.IHTotal / 2;
            CScalerSetByte(_IV_DV_DELAY_CLK_EVEN_42, (ustemp - 16) / 16);
        } 
//V400 modify  
        CScalerSetBit(_FS_DELAY_FINE_TUNING_43, ~(_BIT1), _BIT1);       
    }
}
#endif

//------------------------------------------------------------
//                MCU DAC function
//------------------------------------------------------------
void CSetPWM(BYTE PWMId, WORD Value)
{         
    BYTE ucPWMData = 0;

/*
     switch(PWMId)
     {
         case _SCALAR_PWM0:             // Scalar PWM
         case _SCALAR_PWM1:
         case _SCALAR_PWM2:
             pData[0] = PWMId << 6;     // PWM ID
             pData[1] = 0x01;
             pData[2] = Value;
             CScalerWrite(_OSD_ADDR_MSB_90,3,pData,_AUTOINC);
             break;

#if(_MCU_TYPE == _MYSON_MTV512 || _MCU_TYPE == _RTD_2120)
         case _MCU_PWM0:
         case _MCU_PWM1:
         case _MCU_PWM2:
              CSetMCUPWM(PWMId - _MCU_PWM0,Value);
              break;

         case _MCU_PWM3:
         case _MCU_PWM4:
         case _MCU_PWM5:
              CSetMCUPWM(PWMId - _MCU_PWM3,Value);
              break;
#endif
     }  */
     switch(PWMId)
     {
     case 0:  // PWM0
/*         ucPWMData = MCU_PWM01L_DUT_FF4C;
         MCU_PWM0H_DUT_FF4A  = (Value >> 4) & 0xFF;
         MCU_PWM01L_DUT_FF4C = (ucPWMData & 0xF0) | ((BYTE)Value & 0x0F); */
         MCU_PWM0H_DUT_FF4A  = Value;
         break;

     case 1:  // PWM1
/*         ucPWMData = MCU_PWM01L_DUT_FF4C;
         MCU_PWM1H_DUT_FF4B  = (Value >> 4) & 0xFF;
         MCU_PWM01L_DUT_FF4C = (ucPWMData & 0x0F) | (((BYTE)Value & 0x0F) << 4); */
         MCU_PWM1H_DUT_FF4B  = Value;
         break;

     case 2:  // PWM2
/*         ucPWMData = MCU_PWM23L_DUT_FF4F;
         MCU_PWM2H_DUT_FF4D  = (Value >> 4) & 0xFF;
         MCU_PWM23L_DUT_FF4F = (ucPWMData & 0xF0) | ((BYTE)Value & 0x0F);*/
         MCU_PWM2H_DUT_FF4D  = Value;
         break;

     case 3:  // PWM3
/*         ucPWMData = MCU_PWM23L_DUT_FF4F;
         MCU_PWM3H_DUT_FF4E  = (Value >> 4) & 0xFF;
         MCU_PWM23L_DUT_FF4F = (ucPWMData & 0x0F) | (((BYTE)Value & 0x0F) << 4); */
         MCU_PWM3H_DUT_FF4E  = Value;
         break;

     case 4:  // PWM4
/*         ucPWMData = MCU_PWM45L_DUT_FF52;
         MCU_PWM4H_DUT_FF50  = (Value >> 4) & 0xFF;
         MCU_PWM45L_DUT_FF52 = (ucPWMData & 0xF0) | ((BYTE)Value & 0x0F); */
         MCU_PWM4H_DUT_FF50  = Value;
         break;

     case 5:  // PWM5     
/*         ucPWMData = MCU_PWM45L_DUT_FF52;
         MCU_PWM5H_DUT_FF51  = (Value >> 4) & 0xFF;
         MCU_PWM45L_DUT_FF52 = (ucPWMData & 0x0F) | (((BYTE)Value & 0x0F) << 4); */
         MCU_PWM5H_DUT_FF51  = Value;
         break;

     }
}
//-------------------------------------------------

