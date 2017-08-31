//----------------------------------------------------------------------------------------------------
// ID Code      : Auto.c No.0002
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#define __AUTO__

#include "Core\Header\Include.h"

//--------------------------------------------------
// Description  : Auto clock, phase and H,V position
// Input Value  : None
// Output Value : _ERROR_SUCCESS if succeed
//--------------------------------------------------
BYTE CAutoDoAutoConfig(void)
{
    BYTE result, phasetemp, watchdogtemp;

    bDoAutoConfigFlag = _TRUE;
    CScalerRead(_WATCH_DOG_CTRL0_0C, 1, &watchdogtemp, _NON_AUTOINC);
    CScalerSetByte(_WATCH_DOG_CTRL0_0C, 0x00);

    // Save current phase
    phasetemp = stModeUserData.Phase;

    // Clear the HW auto status to prevent some un-expected event happened
    CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);
    CMiscClearStatusRegister();
    result  = CAutoDoAutoPosition();

    if(result == _ERROR_SUCCESS)
    {
        result  = CAutoDoAutoClock();
        if(result == _ERROR_SUCCESS)
        {
            result  = CAutoDoAutoPhase();
            if((result == _ERROR_SUCCESS) || (result == _ERROR_PHASE))
            {
                if(result == _ERROR_PHASE)
                {
                    stModeUserData.Phase = phasetemp;
                    CAdjustPhase(stModeUserData.Phase);
                }
                result  = CAutoDoAutoPosition();
                if(result != _ERROR_SUCCESS)
                {
                    stModeUserData.HPosition = stModeInfo.IHStartPos;
                    stModeUserData.VPosition = stModeInfo.IVStartPos;
                    CAdjustHPosition();
                    CAdjustVPosition();
                }
            }
            else
            {
                // If auto phase is failed, load phase setting before auto config
                stModeUserData.Phase = phasetemp;
                CAdjustPhase(stModeUserData.Phase);
            }
        }
        else
        {
            // If auto clock is failed, load default clock setting
            stModeUserData.Clock = stModeInfo.IHTotal;
            stModeUserData.HPosition = stModeInfo.IHStartPos;
            stModeUserData.VPosition = stModeInfo.IVStartPos;
            //080324
            ///CAdjustAdcClock(stModeUserData.Clock);
            CAdjustAdcClock(stModeUserData.Clock, 2);
            CAdjustHPosition();
            CAdjustVPosition();
        }
    }
    else
    {
        stModeUserData.HPosition = stModeInfo.IHStartPos;
        stModeUserData.VPosition = stModeInfo.IVStartPos;
        CAdjustHPosition();
        CAdjustVPosition();
    }

    if((result == _ERROR_SUCCESS) || (result == _ERROR_ABORT))
    {

        // Save auto result
        CEepromSaveModeData(stModeInfo.ModeCurr);
        CAdjustUpdateCenterData();
        CEepromSaveCenterModeData(stModeInfo.ModeCurr);
    }       
    bDoAutoConfigFlag = _FALSE;
    CScalerSetByte(_WATCH_DOG_CTRL0_0C, watchdogtemp);
    CMiscClearStatusRegister();

    return result;
}

//--------------------------------------------------
// Description  : Auto color ( white balance )
// Input Value  : None
// Output Value : _ERROR_SUCCESS if succeed
//--------------------------------------------------
BYTE CAutoDoWhiteBalance(void)
{
    BYTE result;
#if(_YPBPR_AUTO_TYPE == _NEW_TYPE)
  #if(_YPBPR_SUPPORT)
    if(_GET_INPUT_SOURCE() == _SOURCE_YPBPR||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1)    
        result = CAutoTuneBalanceNew(); 
    else
  #endif
        result = CAutoTuneBalance();
#else//_YPBPR_AUTO_TYPE==_ORIGINAL_TYPE
    result = CAutoTuneBalance();
#endif
    if(result == _ERROR_SUCCESS)
        CEepromSaveAdcData();
    else
    {
        if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
            CEepromLoadAdcDataDefault();
        else
            CEepromLoadYPbPrDataDefault();
    }
    if(bSourceVideo())
        CEepromSaveSystemData();
    return result;
}

//--------------------------------------------------
// Description  : Wait auto measure process completed
// Input Value  : None
// Output Value : Return result _ERROR_INPUT, _ERROR_SUCCESS
//--------------------------------------------------
BYTE CAutoWaitFinish(void)
{
    BYTE timeoutcnt, ivsevent;
    BYTE valuetemp;//tommy add 070608

    CMiscClearStatusRegister();
    // Auto timeout
#if 1
    //{ add 070608
    //tommy liao add for prevent (ADD PC_AUTOADJUST ITEM) ERROR
    //tommy add for prevent execute funtion of (COsdMenuAutoAdjust) error
    //warning!!!!!!!!!!!!,don't delete the below function
    //warning!!!!!!!!!!!!,or if you change ,can cause serious error,can cause system error 
    CScalerRead(_AUTO_ADJ_CTRL0_7A, 1, &valuetemp, _AUTOINC);
    valuetemp = (valuetemp&0x03);
    if( valuetemp == 0x03 )
        timeoutcnt = 150;
    else
        timeoutcnt = 50;
    //warning!!!!!!!!!!!!,don't delete the up function
    //} add 070608
#else
    //tommy delete
    //timeoutcnt   = (CScalerGetBit(_AUTO_ADJ_CTRL0_7A, _BIT1 | _BIT0) == 0x03) ? 150 : 50;
#endif
    // IVS timeout
    ivsevent     = 25;

    do
    {
        CTimerDelayXms(1);
        CScalerRead(_STATUS1_03, 1, pData, _NON_AUTOINC);
        if(pData[0] & _EVENT_IVS)
        {
            CScalerSetByte(_STATUS1_03, 0x00);
            ivsevent = 25;
        }
        else
        {
            ivsevent = ivsevent - 1;
        }
        if((ivsevent == 0) || (pData[0] & (_EVENT_UNDERFLOW | _EVENT_OVERFLOW)))
        {
            return _ERROR_INPUT;
        }

        // Power off while auto config--------
//        CKeyCheckPowerKey(); cancel by weihao 940926

        if(GET_POWERSWITCH())
            return _ERROR_INPUT;
        //------------------------------------
        CScalerRead(_AUTO_ADJ_CTRL1_7D, 1, pData, _NON_AUTOINC);
    }
    while((pData[0] & 0x01) && (--timeoutcnt));

    CScalerRead(_STATUS0_02, 1, pData, _NON_AUTOINC);
    CScalerSetByte(_STATUS0_02, 0x00);

    // Return non-zero value in Data[0] if :
    // 1. IVS or IHS changed
    // 2. Auto-Phase Tracking timeout
    return ((pData[0] & 0x63) || (0 == timeoutcnt)) ? _ERROR_INPUT : _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Wait for IVS process
// Input Value  : ucTimes   --> frames
// Output Value : Return underflow/overflow status
//--------------------------------------------------
BYTE CAutoWaitForIVS(BYTE ucTimes)
{
    BYTE timeoutcnt;

    timeoutcnt = 25;
    CScalerSetByte(_STATUS1_03, 0x00);
    do
    {
        CTimerDelayXms(1);
        CScalerRead(_STATUS1_03, 1, pData, _NON_AUTOINC);
        pData[0] &= (_EVENT_IVS | _EVENT_UNDERFLOW | _EVENT_OVERFLOW);
        if(((pData[0] & _EVENT_IVS) == _EVENT_IVS) && (ucTimes != 0))
        {
            CScalerSetByte(_STATUS1_03, 0x00);
            ucTimes--;
            timeoutcnt = 25;
        }
    }
    while((ucTimes != 0) && (--timeoutcnt) && ((pData[0] & (_EVENT_UNDERFLOW | _EVENT_OVERFLOW)) == 0));

    return pData[0];
}

//--------------------------------------------------
// Description  : Measure position H
// Input Value  : ucNoiseMarginH    --> Noise margin for H
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoMeasurePositionH(BYTE ucNoiseMarginH)
{
    WORD lbound, rbound;

    rbound  = stModeUserData.Clock;                                               // Totol Clock Number
    lbound  = (DWORD)rbound * stModeInfo.IHSyncPulseCount / stModeInfo.IHCount;   // Clock number in HSYNC pulse
    CScalerSetBit(_VGIP_HV_DELAY_1E, 0x0f, 0x50);
    rbound  = (rbound + _MEASURE_HDEALY) - 2;
    rbound  = rbound - 32;
    lbound  = (lbound + 20 + _MEASURE_HDEALY) < stModeInfo.IHStartPos ? (lbound + 20 + _MEASURE_HDEALY) : 0x0001;
    lbound  = (lbound > 32) ? (lbound - 32) : 0x0001;
    ucNoiseMarginH  &= 0xfc;
    pData[0]    = ((lbound >> 4) & 0x70) | (HIBYTE(rbound) & 0x0f);
    pData[1]    = (LOBYTE(lbound));
    pData[2]    = (LOBYTE(rbound));
    CScalerWrite(_H_BOUNDARY_H_70, 3, pData, _AUTOINC);
    pData[0]    = ucNoiseMarginH;
    pData[1]    = ucNoiseMarginH;
    pData[2]    = ucNoiseMarginH;
    pData[3]    = 0x00;
    pData[4]    = 0x00;
    pData[5]    = 0x00;
    pData[6]    = 0x00;
    pData[7]    = 0x01;
    CScalerWrite(_RED_NOISE_MARGIN_76, 8, pData, _AUTOINC);
    pData[0]    = CAutoWaitFinish();
    if(pData[0] != _ERROR_SUCCESS)
        return pData[0];
    CScalerRead(_H_START_END_H_81, 3, &pData[8], _AUTOINC);
    usHStartPos = (((WORD)(pData[8] & 0xf0 ) << 4) | (WORD)pData[9]) + 32;
    usHEndPos   = (((WORD)(pData[8] & 0x0f ) << 8) | (WORD)pData[10]) + 32;
    return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Measure position V
// Input Value  : ucNoiseMarginV    --> Noise margin for V
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoMeasurePositionV(BYTE ucNoiseMarginV)
{
    WORD lbound, rbound;

    rbound  = stModeUserData.Clock;                                               // Totol Clock Number
    lbound  = (DWORD)rbound * stModeInfo.IHSyncPulseCount / stModeInfo.IHCount;   // Clock number in HSYNC pulse
    CScalerSetBit(_VGIP_HV_DELAY_1E, 0x0f, 0x50);
    rbound  = (rbound + _MEASURE_HDEALY) - 2;
    rbound  = rbound - 32;
    lbound  = (lbound + 20 + _MEASURE_HDEALY) < stModeInfo.IHStartPos ? (lbound + 20 + _MEASURE_HDEALY) : 0x0001;
    lbound  = (lbound > 32) ? (lbound - 32) : 0x0001;
    ucNoiseMarginV  &= 0xfc;
    pData[0]    = ((lbound >> 4) & 0x70) | (HIBYTE(rbound) & 0x0f);
    pData[1]    = (LOBYTE(lbound));
    pData[2]    = (LOBYTE(rbound));
    pData[3]    = (HIBYTE(stModeInfo.IVTotal - 1 + 3) & 0x0f);
    pData[4]    = (0x02);
    pData[5]    = (LOBYTE(stModeInfo.IVTotal - 1 + 3));
    CScalerWrite(_H_BOUNDARY_H_70, 6, pData, _AUTOINC);
    pData[0]    = ucNoiseMarginV;
    pData[1]    = ucNoiseMarginV;
    pData[2]    = ucNoiseMarginV;
    pData[3]    = 0x00;
    pData[4]    = 0x00;
    pData[5]    = 0x00;
    pData[6]    = 0x00;
    pData[7]    = 0x01;
    CScalerWrite(_RED_NOISE_MARGIN_76, 8, pData, _AUTOINC);
    pData[0]    = CAutoWaitFinish();
    if(pData[0] != _ERROR_SUCCESS)
        return pData[0];
    CScalerRead(_V_START_END_H_7E, 3, &pData[8], _AUTOINC);
    usVStartPos = (((WORD)(pData[8] & 0xf0 ) << 4) | (WORD)pData[9]) + 3;
    usVEndPos   = (((WORD)(pData[8] & 0x0f ) << 8) | (WORD)pData[10]) + 3;
    // Check all black
    if(usVEndPos == 0x0000)
        return  _ERROR_ABORT;
    // Update auto-tracking window vertical range
    pData[0]    = (pData[8] & 0x7f);
    pData[1]    = pData[9];
    pData[2]    = pData[10];
    CScalerWrite(_V_BOUNDARY_H_73, 3, pData, _AUTOINC);
    return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Auto phase search function
// Input Value  :
// Output Value :
//--------------------------------------------------
DWORD CAutoPhaseSearch(BYTE ucSelColor, BYTE ucSelStep, BYTE ucSelStepNum, BYTE ucSelStepStart, BYTE *ucPhaseResult)
{
    DWORD maxsum;
    BYTE  count, best;

    CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);
    CScalerSetBit(_AUTO_ADJ_CTRL0_7A, ~(_BIT1 | _BIT0), ucSelColor & 0x03);
    // Issac : Because H/W auto phase search may cause underflow at start and stop,
    //         frame-sync watch-dog must be disabled.
    //CAdjustDisableWatchDog(_WD_ALL);

    if(((DWORD)stModeInfo.IHFreq * stModeInfo.IHTotal / 1000) < 530){
        ucSelStep += 1;
        ucSelStepStart *= 2;
        CScalerPageSelect(_PAGE1);
        if (ucSelStepStart >= 64)
            CScalerSetBit(_P1_MIX_B0, ~_BIT1, _BIT1);
    }
    CScalerSetByte(_HW_AUTO_PHASE_CTRL0_7B, (ucSelStep & 0x07) | (((ucSelStepNum - 1) & 0x1f) << 3));
    CScalerSetByte(_HW_AUTO_PHASE_CTRL1_7C, 0x00 | (ucSelStepStart & 0x3f));
    ucSelStep   = (0x01 << ucSelStep);
    ucSelColor  = ucSelStepStart + (ucSelStepNum) * ucSelStep;
    count       = ucSelStepStart;
    maxsum      = 0;
    best        = 0;
    // Issac : Using Wait_For_Event(EVENT_IVS) instead of Wait_For_IVS().
    //         Because H/W auto phase search may cause underflow at start and stop.
    //         Wait_For_Event() will not check underflow/overflow.
    CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x7b);
    CAutoWaitForIVS(1);
    do
    {
        if(CAutoWaitForIVS(((CScalerGetBit(_AUTO_ADJ_CTRL0_7A, _BIT1 | _BIT0) == 0x03) ? 3 : 1)) & (_EVENT_UNDERFLOW | _EVENT_OVERFLOW))
        {
            CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);
            CScalerPageSelect(_PAGE1);
            CScalerSetBit(_P1_MIX_B0, ~_BIT1, 0x00);
            return 0xffffffff;
        }
        CScalerRead(_AUTO_PHASE_3_84, 3, pData, _AUTOINC);
        pData[3]    = 0;
        if(((DWORD *)pData)[0] > maxsum)
        {
            maxsum  = ((DWORD *)pData)[0];
            best    = count;
        }
        count += ucSelStep;
    }
    while(count < ucSelColor);
    CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);
    CScalerPageSelect(_PAGE1);

    CScalerSetBit(_P1_MIX_B0, ~_BIT1, 0x00);
        
    CTimerWaitForEvent(_EVENT_IVS);
    pData[0] = CAutoWaitFinish();
    if(pData[0] != _ERROR_SUCCESS)
        return 0xffffffff;
    if(((DWORD)stModeInfo.IHFreq * stModeInfo.IHTotal / 1000) < 530)
    {
        *ucPhaseResult = best / 2;
    }
    else
    {
        *ucPhaseResult = best;
    }
    return maxsum;
}

//--------------------------------------------------
// Description  : Get phase SOD information
// Input Value  : ucColor   --> Color we measure
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoReadPhaseInfo(BYTE ucColor)
{
    CScalerSetBit(_AUTO_ADJ_CTRL0_7A, ~(_BIT1 | _BIT0), ucColor & 0x03);
    CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x3b);
    pData[0] = CAutoWaitFinish();
    if(_ERROR_SUCCESS != pData[0])
        return pData[0];
    CScalerRead(_AUTO_PHASE_3_84, 4, pData, _AUTOINC);
    return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Auto clock process
// Input Value  : None
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoDoAutoClock(void)
{
    BYTE    result, phase;
    WORD    count, delta, stop;
    DWORD   maxval;

    stModeUserData.Clock = stModeInfo.IHTotal;
    stModeUserData.Clock &= 0xfffc;
    //080324
///    CAdjustAdcClock(stModeUserData.Clock);
    CAdjustAdcClock(stModeUserData.Clock, 2);
    result  = CAutoMeasurePositionV(_MIN_NOISE_MARGIN);
    if(result != _ERROR_SUCCESS)
        return result;
    delta   = (stModeInfo.IHTotal - stModeInfo.IHWidth * 8 / 10) / 2;
    stop    = 0;
    count   = 10;
    do
    {
        // Measure Horizontal Start/End
        //result      = CAutoMeasurePositionH(_MIN_NOISE_MARGIN + 0x10);
        result      = CAutoMeasurePositionH(_MIN_NOISE_MARGIN + 0x30);
        if(result != _ERROR_SUCCESS)
            return result;
        usHEndPos   = usHEndPos + 1 - usHStartPos;
        if(usHEndPos < stModeInfo.IHWidth)
        {
            if((stModeInfo.IHWidth - usHEndPos) >= (2 * delta))
            {
                stop    = 1;
            }
            else
            {
                usHStartPos = (DWORD)(stModeInfo.IHWidth - usHEndPos) * (stModeUserData.Clock)
                            / (DWORD)stModeInfo.IHWidth;

                if(usHStartPos <= 2)    break;
                usHStartPos = (usHStartPos + 2) & 0xfffc;
                //if((usHStartPos + stModeUserData.Clock - stModeInfo.IHTotal) > usDelta)
                if((usHStartPos + stModeUserData.Clock) > (delta + stModeInfo.IHTotal))
                {
                    stop    = 1;
                }
                else
                {
                    stModeUserData.Clock += usHStartPos;
                }
            }
        }
        else
        {
            if((usHEndPos - stModeInfo.IHWidth) >= (2 * delta))
            {
                stop    = 1;
            }
            else
            {
                usHStartPos = (DWORD)(usHEndPos - stModeInfo.IHWidth) * (stModeUserData.Clock)
                            / (DWORD)stModeInfo.IHWidth;

                if(usHStartPos <= 2)    break;
                usHStartPos = (usHStartPos + 2) & 0xfffc;

                //if((stModeInfo.IHTotal - (stModeUserData.Clock - usHStartPos)) > usDelta)
                if((usHStartPos + stModeInfo.IHTotal) > (delta + stModeUserData.Clock))
                {
                    stop    = 1;
                }
                else
                {
                    stModeUserData.Clock -= usHStartPos;
                }
            }
        }
        if(stop)   break;
        //080324
        ///CAdjustAdcClock(stModeUserData.Clock);
        CAdjustAdcClock(stModeUserData.Clock, 2);
    }
    while(--count);
    if((count == 0) || (stop == 1))
        return _ERROR_ABORT;
    // Prevent from 1/2-line moire and smear effect.
    if((usHEndPos >= stModeInfo.IHWidth && (stModeUserData.Clock - stModeInfo.IHTotal) == 4)
       || (usHEndPos < stModeInfo.IHWidth && (stModeInfo.IHTotal - stModeUserData.Clock) == 4))
    {
        stModeUserData.Clock = stModeInfo.IHTotal;
        //080324
        ///CAdjustAdcClock(stModeUserData.Clock);
        CAdjustAdcClock(stModeUserData.Clock, 2);
        result    = CAutoMeasurePositionH(_MIN_NOISE_MARGIN + 0x10);
        if(result != _ERROR_SUCCESS)
            return result;
        usHEndPos   = usHEndPos + 1 - usHStartPos;
    }

#if(_AUTO_CLOCK_PRECISION < 4)
    // Save 4N clock
    stop    = stModeUserData.Clock;
    stModeUserData.Clock += (stModeInfo.IHWidth >= usHEndPos) ? 4 : 2;
    //080324
    ///CAdjustAdcClock(stModeUserData.Clock);
    CAdjustAdcClock(stModeUserData.Clock, 2);
    // Set threshold for Clock Search
    CScalerSetByte(_DIFF_THRESHOLD_79, 0x18);
    count   = stop;
    maxval  = 0;
    delta   = 6;    // Initial value must be (N * AUTO_CLOCK_STEP)
    do
    {
        result    = CAutoMeasurePositionH(_MIN_NOISE_MARGIN + 0x10);
        if(result != _ERROR_SUCCESS)
            return result;
        usHEndPos   = usHEndPos + 1 - usHStartPos;
        if(usHEndPos > (stModeInfo.IHWidth + 2))
        {
            ((DWORD *)pData)[0]   = 0;
        }
        else
        {
            ((DWORD *)pData)[0]   = CAutoPhaseSearch(_COLOR_SELECT, _HWAUTO_STEP_8, HWAUTOSTEPNUM(8), HWAUTOSTEPSTART(0), &phase);
            if (0xffffffffL == ((DWORD *)pData)[0])   return _ERROR_INPUT;
        }
        if(maxval < ((DWORD *)pData)[0])
        {
            maxval    = ((DWORD *)pData)[0];
            count     = stModeUserData.Clock;
        }
        if(delta == 0x00)
        {
            // Check if default clock is the best when clock searching range is larger than default.
            if(stModeUserData.Clock > stModeInfo.IHTotal)
            {
                stModeUserData.Clock = stModeInfo.IHTotal;
                //080324
                ///CAdjustAdcClock(stModeUserData.Clock);
                CAdjustAdcClock(stModeUserData.Clock, 2);
                continue;
            }
            break;
        }
        delta                   -= _AUTO_CLOCK_PRECISION;
        stModeUserData.Clock    -= _AUTO_CLOCK_PRECISION;
        //080324
        ///CAdjustAdcClock(stModeUserData.Clock);
        CAdjustAdcClock(stModeUserData.Clock, 2);
    }
    while(_TRUE);
    maxval = maxval / 3;
    stModeUserData.Clock    = (maxval > ((DWORD)stModeInfo.IHWidth << 10)) ? count : stop;
//  if (stModeUserData.Clock > 100)
//      stModeUserData.Clock = 100; // within range
//080324
    ///CAdjustAdcClock(stModeUserData.Clock);
    CAdjustAdcClock(stModeUserData.Clock, 2);
#endif
    return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Auto phase process
// Input Value  : None
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoDoAutoPhase(void)
{
    BYTE  result, phase, best;
    DWORD maxsum, temp0, temp1, temp2;

    result = CAutoMeasurePositionH(_MIN_NOISE_MARGIN);
    if(_ERROR_SUCCESS != result)
        return result;
    // Set threshold 0x80 for Phase Search
    CScalerSetByte(_DIFF_THRESHOLD_79, 0x80);
    maxsum  = CAutoPhaseSearch(_COLOR_SELECT, _HWAUTO_STEP_8, HWAUTOSTEPNUM(8), HWAUTOSTEPSTART(0), &result);
    if(maxsum == 0xffffffffL)
        return _ERROR_INPUT;
    if(maxsum == 0)
        return _ERROR_ABORT;
    if(maxsum < ((DWORD)stModeInfo.IVHeight * 1024 * 3 / 2))
    {
        // Decrease threshold to 0x40 for Phase Search
        CScalerSetByte(_DIFF_THRESHOLD_79, 0x40);
        maxsum  = CAutoPhaseSearch(_COLOR_SELECT, _HWAUTO_STEP_8, HWAUTOSTEPNUM(8), HWAUTOSTEPSTART(0), &result);
        if(maxsum == 0xffffffffL)
            return _ERROR_INPUT;
        if(maxsum == 0)
            return _ERROR_ABORT;
        if(maxsum < ((DWORD)stModeInfo.IVHeight * 1024 * 3 / 2))
            return _ERROR_PHASE;
    }

    // Issac:
    // Please do not delete these backup code below.
    /*if(((DWORD)stModeInfo.IHFreq * stModeInfo.IHTotal / 1000) < 530)
    {
        BYTE  count, ucSelStep, ucSelColor;

        CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);

        ucSelStep   = (0x01 << _HWAUTO_STEP_2);
        count       = ((result - 8) & 0x3f);
        ucSelColor  = count + (8 * ucSelStep);
        maxsum      = 0;
        best        = 0;

        do
        {
            CAdjustPhase(count);

            if(_ERROR_SUCCESS != CAutoReadPhaseInfo(_COLOR_SELECT))   return _ERROR_INPUT;

            if(((DWORD *)pData)[0] > maxsum)
            {
                maxsum  = ((DWORD *)pData)[0];
                best    = count;
            }

            count += ucSelStep;
        }
        while(count < ucSelColor);

        CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);

        result = best & 0x3f;
    }
    else
    */   
    {
    maxsum  = CAutoPhaseSearch(_COLOR_SELECT, _HWAUTO_STEP_2, HWAUTOSTEPNUM(8), HWAUTOSTEPSTART((result - 8) & 0x3f), &result);
    if(maxsum == 0xffffffffL)
        return _ERROR_INPUT;
    if(maxsum == 0)
        return _ERROR_ABORT;
    } 
    // Search phase by weighting SOD
    phase   = (result - 3) & 0x3f;
    CAdjustPhase(phase);

    if(_ERROR_SUCCESS != CAutoReadPhaseInfo(_COLOR_SELECT))
        return _ERROR_INPUT;
    temp0   = ((DWORD *)pData)[0];

    phase   = (phase + 1) & 0x3f;
    CAdjustPhase(phase);

    if(_ERROR_SUCCESS != CAutoReadPhaseInfo(_COLOR_SELECT))
        return _ERROR_INPUT;
    temp1   = ((DWORD *)pData)[0];

    result  = (result + 3) & 0x3f;
    maxsum  = 0;
    do
    {
        phase   = (phase + 1) & 0x3f;
        CAdjustPhase(phase);
        if(_ERROR_SUCCESS != CAutoReadPhaseInfo(_COLOR_SELECT))
            return _ERROR_INPUT;
        temp2   = ((DWORD *)pData)[0];

        ((DWORD *)pData)[0] = temp2 + temp1 + temp0
                              - ((temp1 > temp0 ? temp1 - temp0 : temp0 - temp1) / 2)
                              - ((temp1 > temp2 ? temp1 - temp2 : temp2 - temp1) / 2);

        if(((DWORD *)pData)[0] > maxsum)
        {
            maxsum  = ((DWORD *)pData)[0];
            best    = (phase - 1) & 0x3f;
        }
        temp0   = temp1;
        temp1   = temp2;
    }
    while(phase != result);
    stModeUserData.Phase    = best;
    CAdjustPhase(stModeUserData.Phase);
    CScalerSetByte(_DIFF_THRESHOLD_79, 0x40);
    return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Auto position process
// Input Value  : None
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoDoAutoPosition(void)
{
    BYTE result;
    SWORD dtemp, ctemp, atemp;

    result  = CAutoMeasurePositionV(_MIN_NOISE_MARGIN);
    if(_ERROR_SUCCESS != result)
        return result;

    result  = CAutoMeasurePositionH(_MIN_NOISE_MARGIN);
    if(_ERROR_SUCCESS != result)
        return result;

    /////////////////////////////////
    // Calculate Vertical Position //
    /////////////////////////////////
    CScalerRead(_IPV_ACT_STA_H_18, 2, pData, _AUTOINC);
    ctemp = (((WORD)(pData[0] & 0x07)) << 8) | pData[1];

    CScalerRead(_IVS_DELAY_1C, 1, pData, _AUTOINC);
    CScalerRead(_VGIP_HV_DELAY_1E, 1, &pData[1], _AUTOINC);
    dtemp = (((WORD)(pData[1] & _BIT1)) << 8) | pData[0];
    dtemp = usVStartPos - dtemp;
    atemp = (stModeInfo.IVHeight - (usVEndPos - usVStartPos + 1));
    if(atemp > 3)
    atemp = abs(usVEndPos - usVStartPos + 1 - stModeInfo.IVHeight) / 2;
    else
        atemp = 0;
    while(_TRUE)
    {
        if(abs(stModeUserData.VPosition + (ctemp - dtemp) - stModeInfo.IVStartPos + atemp) <= ucVStartBias)
        {
#if(_V_POSITION_DIRECTION == _V_POSITION_METHOD_0)
            stModeUserData.VPosition += ctemp - dtemp + atemp;
#endif

#if(_V_POSITION_DIRECTION == _V_POSITION_METHOD_1)
            stModeUserData.VPosition -= ctemp - dtemp + atemp;
#endif
            break;
        }
        else
        {
            stModeUserData.VPosition = stModeInfo.IVStartPos;
            break;
        }
    }
    CAdjustVPosition();
    ///////////////////////////////////
    // Calculate Horizontal Position //
    ///////////////////////////////////
    CScalerRead(_IPH_ACT_STA_H_14, 2, pData, _AUTOINC);
    ctemp = (((WORD)(pData[0] & 0x07)) << 8) | pData[1];
    CScalerRead(_IHS_DELAY_1D, 2, pData, _AUTOINC);
    dtemp = (((WORD)(pData[1] & _BIT0)) << 8) | pData[0];
    dtemp = usHStartPos - dtemp - 2;
    while(_TRUE)
    {
        if(abs(stModeUserData.HPosition + (ctemp - dtemp) - stModeInfo.IHStartPos) <= ucHStartBias)
        {
            stModeUserData.HPosition += ctemp - dtemp;
            break;
        }
        else
        {
            stModeUserData.HPosition = stModeInfo.IHStartPos;
            break;
        }
    }
    CAdjustHPosition();
    return _ERROR_SUCCESS;
}

#define _AUTO_VGA_MAX_LEVEL                          242
#define _AUTO_VGA_MIN_LEVEL                           2
#define _AUTO_COMPONENT_Y_MAX_LEVEL         250
#define _AUTO_COMPONENT_Y_MIN_LEVEL         12
#define _AUTO_COMPONENT_PB_MAX_LEVEL       240
#define _AUTO_COMPONENT_PR_MAX_LEVEL       240
#define _AUTO_VIDEO8_Y_MAX_LEVEL                 248 
#define _AUTO_VIDEO8_Y_MIN_LEVEL                 2//12
#define _AUTO_VIDEO8_C_MAX_LEVEL                 236 //this value can't over 240 


#define _CHROMA_BLACK_LEVEL             0x80

void CGetTargetValue(UINT8* max_value, UINT8* min_value, UINT8 color)
{
        switch(_GET_INPUT_SOURCE())
        {
               case _SOURCE_VGA:
              *max_value = _AUTO_VGA_MAX_LEVEL;
              *min_value = _AUTO_VGA_MIN_LEVEL;           
              break;
         case _SOURCE_YPBPR:case _SOURCE_YPBPR1:
              if(color == _GREEN)
              {
                  *max_value = _AUTO_COMPONENT_Y_MAX_LEVEL;
                *min_value = _AUTO_COMPONENT_Y_MIN_LEVEL;
              }
              else
              {
                  *max_value = (color == _RED) ? _AUTO_COMPONENT_PR_MAX_LEVEL : _AUTO_COMPONENT_PB_MAX_LEVEL;                 
                  *min_value = _CHROMA_BLACK_LEVEL;
              }
              break;
         
#if(_VIDEO_AUTO_WHITE_BLANCE == _ENABLE)              
            case _SOURCE_VIDEO_AV: //VIDEO8
            case _SOURCE_VIDEO_SV: //VIDEO8
            case _SOURCE_VIDEO_TV: //VIDEO8
                    if(color == _GREEN)
                    {
                       *max_value = _AUTO_VIDEO8_Y_MAX_LEVEL;
                 *min_value = _AUTO_VIDEO8_Y_MIN_LEVEL;
                    }
              else
              {
                 *max_value = _AUTO_VIDEO8_C_MAX_LEVEL;
                 *min_value = _CHROMA_BLACK_LEVEL;
              }
                 break;
#endif               
                
        }
}
/*
#define VIDEO8_Y_MAX_LEVEL          250 
#define VIDEO8_Y_MIN_LEVEL           6
#define VIDEO8_C_MAX_LEVEL          240
*/

//--------------------------------------------------
// Description  : Tune ADC gain and offset
// Input Value  : None
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoTuneBalance(void)
{
    BYTE rev, result0, result1, color, count;
    BYTE xdata ucMax_Value, ucMin_Value;

    if(_GET_INPUT_SOURCE() == _SOURCE_VGA)// VGA
    {       
        for(count=0;count<3;count++)
        {
            stAdcData.AdcGain[count] = 0x80;
            stAdcData.AdcOffset[count] = 0x80;
        }
        CAdjustAdcGainOffset();//jerry0921
    }
    else if(_GET_INPUT_SOURCE() == _SOURCE_YPBPR ||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1)// YPBPR
    {   
        for(count=0;count<3;count++)
            {
            stYPbPrData.YPbPrGain[count] = 0x80;
            stYPbPrData.YPbPrOffset[count] = 0x80;
            }
        CAdjustAdcGainOffset();//jerry0921
    }
#if(_VIDEO_AUTO_WHITE_BLANCE == _ENABLE)
    else if(bSourceVideo())// AV / SV / TV
    {   
        SET_CONTRAST(50);               // set OSD default value  to 50
        SET_SATURATION(50);             // set OSD default value to 50
        SET_VDC_GAIN(0x80);
        SET_VDC_OFFSET(0x80);
        SET_VDC_CHROMA(0x80);
        CVideoSetVDCContrast(0x80);
        CVideoSetVDCBrightness(0x80);
        CVideoSetVDCSaturation(0x80);
    #if(sRGB_Color_Enhance == _ENABLE)
        CAdjustSaturationHue(50, _TRUE);// set to OSD default value is 50
    #endif
    }
#endif


        rev = CAutoMeasurePositionV(_MIN_NOISE_MARGIN);
        if(rev != _ERROR_SUCCESS)    return rev;

        rev = CAutoMeasurePositionH(_MIN_NOISE_MARGIN);
        if(rev != _ERROR_SUCCESS)    return rev;

        if(CAutoMeasureColor(_BLUE, _MEASURE_COLORS_MAX, &rev) != _ERROR_SUCCESS)       return _ERROR_ABORT;
        if(rev < 0x60)              return _ERROR_ABORT;

        if(CAutoMeasureColor(_GREEN, _MEASURE_COLORS_MAX, &rev) != _ERROR_SUCCESS)      return _ERROR_ABORT;
        if(rev < 0x60)              return _ERROR_ABORT;

        if(CAutoMeasureColor(_RED, _MEASURE_COLORS_MAX, &rev) != _ERROR_SUCCESS)        return _ERROR_ABORT;
        if(rev < 0x60)              return _ERROR_ABORT;

    if(bSourceVideo())
        color = _GREEN;           //we don't measure the blue color in VIDEO8 auto color
    else
               color = _BLUE;
    
        while(_TRUE)
        {
            count = 0x30;

        CGetTargetValue(&ucMax_Value, &ucMin_Value, color);

            do
            {
        
            rev = CAutoTuneDeviceGain(color, &result0, ucMax_Value);

                    if(rev == _ERROR_ABORT)     return rev;
                    if(rev == _ERROR_FINISH)    break;
            rev = CAutoTuneDeviceOffset(color, &result1, ucMin_Value);
        #if(_VIDEO_AUTO_WHITE_BLANCE == _ENABLE)
            if(bSourceVideo())
            {
                        //Chroma doesn't need to adjust the offset
                if(color != _GREEN)
                result1 = ucMin_Value;
            }       
        #endif
                    if(rev == _ERROR_ABORT)     
                return rev;

                    if((result0 == ucMax_Value) && (result1 == ucMin_Value))
                        break;

                    if((count > 8) && (result0 <= (ucMax_Value + 1)) && (result0 >= (ucMax_Value - 1))
                        && (result1 <= (ucMin_Value + 1)) && (result1 >= (ucMin_Value - 1)))
                    {
                        count = 8;
                    }
        }
        while(--count);

        if(color == _BLUE)              // 2 : Blue or PB
                    color = _GREEN;
        else if(color == _GREEN)        // 1: Green or Y
                    color = _RED;
        else                        // 0: Red or PR
                    break;
    }

    if((stAdcData.AdcGain[_RED] == 0x00) || (stAdcData.AdcGain[_GREEN] == 0x00) || (stAdcData.AdcGain[_BLUE] == 0x00))
        return _ERROR_ABORT;
    else
        return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Get max or min color value
// Input Value  : Measure information
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoMeasureColor(BYTE ucColor, BYTE ucPar, BYTE *pMargin)
{
    CScalerSetBit(_AUTO_ADJ_CTRL0_7A, ~(_BIT2 | _BIT1 | _BIT0) , (ucColor == 3) ? ucColor : ( 2 - ucColor));

    if(bSourceVideo())
    {
        CScalerSetBit(_VGIP_HV_DELAY_1E, 0x0f, 0x00);
        
        pData[0] = ((HIBYTE(stModeInfo.IHStartPos) << 2) & 0x0C) |(HIBYTE(stModeInfo.IHStartPos + stModeInfo.IHWidth )  & 0x03);   
        pData[1] = LOBYTE(stModeInfo.IHStartPos);
        pData[2] = LOBYTE(stModeInfo.IHStartPos + stModeInfo.IHWidth);
        pData[3] = ((HIBYTE(stModeInfo.IVStartPos) << 2) & 0x0C) |(HIBYTE(stModeInfo.IVStartPos + stModeInfo.IVHeight )  & 0x03);   
        pData[4] = LOBYTE(stModeInfo.IVStartPos);
        pData[5] = LOBYTE(stModeInfo.IVStartPos + stModeInfo.IVHeight);

    }
    else
    {   // VGA or YPBPR
    if(ucPar == _MEASURE_COLORS_MIN)
    {
        pData[0] = 0x12;
        pData[1] = 0x80;
        pData[2] = 0x00;
        pData[3] = 0x00;
        pData[4] = (usVStartPos > 9) ? 9 : (usVStartPos - 1);
        pData[5] = pData[4] + 1;
    }
    else
    {
        pData[0] = ((usHStartPos >> 4) & 0x70) | (HIBYTE(usHEndPos) & 0x0f);
        pData[1] = (LOBYTE(usHStartPos));
        pData[2] = (LOBYTE(usHEndPos));
        pData[3] = ((usVStartPos >> 4) & 0x70) | (HIBYTE(usVEndPos) & 0x0f);
        pData[4] = (LOBYTE(usVStartPos));
        pData[5] = (LOBYTE(usVEndPos));
    }
    }   
    CScalerWrite(_H_BOUNDARY_H_70, 6, pData, _AUTOINC);

    CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x01 | ((ucPar & 0x01) << 5));

    pData[0] = CAutoWaitFinish();

    if(pData[0] != _ERROR_SUCCESS)       return pData[0];

    CScalerRead(_AUTO_PHASE_0_87, 1, pMargin, _AUTOINC);

    if(ucPar == _MEASURE_COLORS_MIN)
        *pMargin ^= 0xff;       // measure color min need 1's complement

    return _ERROR_SUCCESS;
}


UINT8 Change_Device_Gain(UINT8 color, UINT8 delta, UINT8 inc)
{
       
#if(_VIDEO_AUTO_WHITE_BLANCE == _ENABLE)
       if(bSourceVideo())
            return(Change_VDC_Gain(color, delta, inc));
       else   
#endif
              return(CAutoChangeAdcGain(color, delta, inc));                
          
       
}

UINT8 Change_Device_Offset(UINT8 color, UINT8 delta, UINT8 inc)
{
#if(_VIDEO_AUTO_WHITE_BLANCE == _ENABLE)
       if(bSourceVideo())
           return(Change_VDC_Offset(color, delta, inc));
       else   
#endif
                 return(CAutoChangeAdcOffset(color, delta, inc));       
}

//--------------------------------------------------
// Description  : Adjust ADC gain
// Input Value  : Adjusting setting
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoTuneDeviceGain(BYTE ucColor, BYTE *pMargin, BYTE ucMax_Target)
{
    BYTE temp;

    if(CAutoMeasureColor(ucColor, _MEASURE_COLORS_MAX, pMargin) != _ERROR_SUCCESS)
        return _ERROR_ABORT;

    if(*pMargin > ucMax_Target)
    {
        temp  = *pMargin - ucMax_Target;
        // Non-zero return value of Change_ADC_Gain() means ADC gain reaches maximum.
    if(Change_Device_Gain(ucColor, temp, 0))                  // Decrease Gain; Decrease Contrast
            {
               if(bSourceVideo())
               {
               if(Change_Device_Offset(ucColor, 2, 0))               // Increase Offset; Decrease Brightness               
                    return _ERROR_FINISH;

               }
               else
               {
               if(Change_Device_Offset(ucColor, 4, 0))               // Increase Offset; Decrease Brightness               
                    return _ERROR_FINISH;
               }
            }
    }
    else if(*pMargin < ucMax_Target)
    {
        temp  = ucMax_Target - *pMargin;
            // Non-zero return value of Change_ADC_Gain() means ADC gain reaches minimum.
        if(Change_Device_Gain(ucColor, temp, 1))                  // Increase Gain; Increase Contrast
            {
               if(bSourceVideo())
               {
               if(Change_Device_Offset(ucColor, 2, 1))               // Increase Offset; Decrease Brightness               
                    return _ERROR_FINISH;

               }
               else
               {
               if(Change_Device_Offset(ucColor, 4, 1))               // Increase Offset; Decrease Brightness               
                    return _ERROR_FINISH;
               }
            }
        }
    return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Adjust ADC offset
// Input Value  : Adjusting setting
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoTuneDeviceOffset(BYTE ucColor, BYTE *pMargin, BYTE ucMin_Target)
{
    BYTE temp;

    if(CAutoMeasureColor(ucColor, _MEASURE_COLORS_MIN, pMargin) != _ERROR_SUCCESS)
        return _ERROR_ABORT;

     if((_GET_INPUT_SOURCE() == _SOURCE_VGA)||
        ((_GET_INPUT_SOURCE() == _SOURCE_YPBPR ||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1)&&(ucColor == _SY)) ||
        ((bSourceVideo())&&(ucColor == _GREEN)))
     {

               //forster modified 061002
         if(*pMargin > ucMin_Target)
         {
                      temp = *pMargin - ucMin_Target;
             Change_Device_Offset(ucColor, ((temp > 8) ? 8 : temp), 0);
        }
        else if(*pMargin < ucMin_Target)
        {

        temp = ucMin_Target - *pMargin;

                if(*pMargin == 0)
                          Change_Device_Offset(ucColor, temp + 4, 1);       // Increase Offset; Increase Brightness
                else
                          Change_Device_Offset(ucColor, temp, 1);           // Increase Offset; Increase Brightness
        }       
    }
    else
    {
        if(*pMargin > _CHROMA_BLACK_LEVEL)
        {
            temp = *pMargin - _CHROMA_BLACK_LEVEL;
            Change_Device_Offset(ucColor, ((temp > 8) ? 8 : temp), 0);
        }
        else if(*pMargin < _CHROMA_BLACK_LEVEL)
        {       
            temp = _CHROMA_BLACK_LEVEL - *pMargin;
                if(*pMargin == 0)
            {
                        Change_Device_Offset(ucColor, temp + 4, 1);
                }
            else
            {
                Change_Device_Offset(ucColor, temp, 1);
            }
        }
    }
    return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Change ADC gain
// Input Value  : Input information
// Output Value : Return 1 if overrange
//--------------------------------------------------
BYTE CAutoChangeAdcGain(BYTE ucColor, BYTE ucDelta, BYTE ucInc)
{
    BYTE overrange = 0;
    BYTE Gain;

    if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
        Gain =  stAdcData.AdcGain[ucColor] ;
    else if(_GET_INPUT_SOURCE() == _SOURCE_YPBPR||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1)
        Gain = stYPbPrData.YPbPrGain[ucColor];

        if(ucInc)
        {
        if(Gain >= ucDelta)
            Gain -= ucDelta;
            else
            {
            Gain = 0;
                overrange = 1;
            }
        }
        else
        {
        if ((0xff - ucDelta) >= Gain)
            Gain += ucDelta;
            else
            {
            Gain = 0xff;
                overrange = 1;
            }
        }

   if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
        stAdcData.AdcGain[ucColor] = Gain;
    else if(_GET_INPUT_SOURCE() == _SOURCE_YPBPR||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1)
        stYPbPrData.YPbPrGain[ucColor] = Gain;

        CAdjustAdcGain();
        return overrange;
}

//--------------------------------------------------
// Description  : Change ADC offset
// Input Value  : Input information
// Output Value : Return 1 if overrange
//--------------------------------------------------
BYTE CAutoChangeAdcOffset(BYTE ucColor, BYTE ucDelta, BYTE ucInc)
{
    BYTE overrange = 0;
    BYTE Offset;    

    if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
        Offset =    stAdcData.AdcOffset[ucColor];
    else if(_GET_INPUT_SOURCE() == _SOURCE_YPBPR||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1)
        Offset = stYPbPrData.YPbPrOffset[ucColor];
    if(ucInc)
        {
        if(Offset >= ucDelta)
            Offset -= ucDelta;
            else
            {
            Offset = 0;
            overrange = 1;
            }
        }
        else
        {
        if ((0xff - ucDelta) >= Offset)
            Offset += ucDelta;
        else
            {
            Offset = 0xff;
            overrange = 1;
            }
        }

    if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
        stAdcData.AdcOffset[ucColor] = Offset;
    else if(_GET_INPUT_SOURCE() == _SOURCE_YPBPR||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1)
        stYPbPrData.YPbPrOffset[ucColor] = Offset;  

        CAdjustAdcOffset();
        return overrange;
}

#if(_VIDEO_AUTO_WHITE_BLANCE == _ENABLE)
#define _CHROMA     0x00
#define _LUMA       0x01

UINT8 Change_VDC_Gain(UINT8 color, UINT8 delta,UINT8 inc)
{
    if(color == _LUMA)//VDC Y gain is more sensitive than other source
    {
        if(delta < 0x08)
           delta = delta >> 1;
    }
    
    pData[2] = 0;
    pData[0] = color == _LUMA ? GET_VDC_GAIN() : GET_VDC_CHROMA();
    pData[1] = inc ? (0xff - pData[0]) : pData[0];
    if(inc){
        if(pData[1] > delta)
            pData[0] += delta;
    else{
             pData[0] = 0xff;
             pData[2] |= color;//saturate
        }
    }
    else{
        if(pData[1] > delta)
                pData[0] -= delta;
        else{
            pData[0] = 0;
            pData[2] |= color; //saturate
        }
    }
    if(color == _LUMA){
        SET_VDC_GAIN(pData[0]);
        CVideoSetVDCContrast(pData[0]);
    }
    else{
        SET_VDC_CHROMA(pData[0]);
        CVideoSetVDCSaturation(pData[0]);
    }
    return pData[2];
}

UINT8 Change_VDC_Offset(UINT8 color, UINT8 delta,UINT8 inc)
{
    //Chroma can't adjust the offset
    if(color == _CHROMA)
        return 0;
    pData[2] = 0;
    pData[0] = GET_VDC_OFFSET();
   pData[1] = inc ? (0xff - pData[0]) : pData[0];
    if(inc){
        if(pData[1] > delta)
            pData[0] += delta;
    else{
                  pData[0] = 0xff;
            pData[2] |= color;  //saturate
        }
    }
    else{
        if(pData[1] > delta)
            pData[0] -= delta;
    else{
            pData[0] = 0;
            pData[2] |= color;  //saturate
    }
}
    SET_VDC_OFFSET(pData[0]);
    CVideoSetVDCBrightness(pData[0]);
    return pData[2];
}
#endif

#if(_YPBPR_SUPPORT)
#if(_YPBPR_AUTO_TYPE==_NEW_TYPE)
#define Channel_Y       0
#define Channel_U       1
#define Channel_V       2

BYTE YPbPr_ABS(UINT8 data_1, UINT8 data_2)
{
    UINT8 result;

    if(data_1 >= data_2)
        result = data_1 - data_2;
    else
        result = data_2 - data_1;
    return result;
}

BYTE ActiveRegion_2547D(UINT16 *Region)
{
    //CScalerPageSelect(_PAGE0);
    CScalerSetByte(_IPH_ACT_STA_H_14, 0x00);
    CScalerSetByte(_IPV_ACT_STA_H_18, 0x00);

    CScalerRead(_IPH_ACT_STA_H_14, 10, pData, _AUTOINC);            // 14(0),15(1),16(2),17(3),18(4),19(5),1A(6),1B(7),1C(8),1D(9)
    Region[0] = ((pData[0]  & (0x07)) << 8) + pData[1] + pData[9];  //Active_HStart
    Region[1] = ((pData[2]  & (0x07)) << 8) + pData[3];                     //Active_HWidth
    Region[2] = ((pData[4]  & (0x07)) << 8) + pData[5] + pData[8];  //Active_VStart
    Region[3] = ((pData[6]  & (0x07)) << 8) + pData[7];                     //Active_VLines
    
    return(1);
}

void HistPos( UINT16 Active_HStart, UINT16 Active_HWidth, UINT16 Active_VStart, UINT16 Active_VWidth, UINT16 *Offset_Pos, UINT16 *Y_Gain_Pos, UINT16 *PbPr_Gain_Pos)
{
/*
//chroma2330#36(Default)//remember to modify fractional number.!!!!!
    //OffsetYPbPr Position
    Offset_Pos[0]   = (Active_HStart+Active_HWidth) - Active_HWidth/7;
    Offset_Pos[1]   = Offset_Pos[0] + Active_HWidth/100;
    Offset_Pos[2]   = (Active_VStart+Active_VWidth) - 2*Active_VWidth/20;
    Offset_Pos[3]   = Offset_Pos[2] + Active_VWidth/20;

    //GainY Position
    Y_Gain_Pos[0]=  (Active_HStart + Active_HWidth)/2;
    Y_Gain_Pos[1]=  Y_Gain_Pos[0] + Active_HWidth/100;
    Y_Gain_Pos[2]   = (Active_VStart+Active_VWidth) - 2*Active_VWidth/20;
    Y_Gain_Pos[3]   = Y_Gain_Pos[2] + Active_VWidth/20;

    //GainPbPr Position
    PbPr_Gain_Pos[0]    = (Active_HStart+Active_HWidth) - (2.5)*Active_HWidth/7;
    PbPr_Gain_Pos[1]    = PbPr_Gain_Pos[0]+ Active_HWidth/100;
    PbPr_Gain_Pos[2]    = Active_VStart + Active_VWidth/20;
    PbPr_Gain_Pos[3]    = PbPr_Gain_Pos[2] + Active_VWidth/20;
*/

//chroma2330#27
/*
    //OffsetYPbPr(Black)
    Offset_Pos[0]   = Active_HStart + Active_HWidth*(0.03125);
    Offset_Pos[1]       = Offset_Pos[0]  + Active_HWidth*(0.03125);

    Offset_Pos[2]   = Active_VStart + Active_VWidth*(0.05);
    Offset_Pos[3]   = Offset_Pos[2]  + Active_VWidth*(0.05);

    //GainY(White)
    Y_Gain_Pos[1]   = (Active_HStart + Active_HWidth) - Active_HWidth*(0.0625);
    Y_Gain_Pos[0]   = Y_Gain_Pos[1] - Active_HWidth*(0.03125);

    Y_Gain_Pos[3]   = (Active_VStart + Active_VWidth) - Active_VWidth*(0.05);
    Y_Gain_Pos[2]   = Y_Gain_Pos[3] - Active_VWidth*(0.05);
    
    //GainPbPr(Magenta)
    PbPr_Gain_Pos[1] = Active_HStart + Active_HWidth*(0.5) - Active_HWidth*(0.0625);
    PbPr_Gain_Pos[0] = PbPr_Gain_Pos[1]  - Active_HWidth*(0.03125);

    PbPr_Gain_Pos[3] = Y_Gain_Pos[3];
    PbPr_Gain_Pos[2] = Y_Gain_Pos[2];
*/
//VideoBook-Chapter#2_colorbar
    Offset_Pos[0]   = (Active_HStart+Active_HWidth) - Active_HWidth*(0.0625);//over 16
    Offset_Pos[1]   = Offset_Pos[0] + Active_HWidth*(0.015625);//over 64

    //GainY(White)
    Y_Gain_Pos[0]   = Active_HStart + Active_HWidth*(0.03125);//over 32
    Y_Gain_Pos[1]   = Y_Gain_Pos[0] + Active_HWidth*(0.015625);//over 64
        
    //GainPbPr(Magenta)
    PbPr_Gain_Pos[0] = (Active_HStart+Active_HWidth) - (3.5)*(Active_HWidth*(0.125));//over 8
    PbPr_Gain_Pos[1] = PbPr_Gain_Pos[0] + Active_HWidth*(0.015625); //over 64
        
    Offset_Pos[2]   = Active_VStart + Active_VWidth*(0.03125);//over 32
    Offset_Pos[3]   = Offset_Pos[2] + Active_VWidth*(0.03125);//over 32
    Y_Gain_Pos[2]  = Offset_Pos[2];
    Y_Gain_Pos[3]  = Offset_Pos[3];
    PbPr_Gain_Pos[2]  = Offset_Pos[2];
    PbPr_Gain_Pos[3]  = Offset_Pos[3];

}

void HistWrite_RTD2547D_SmartFit(UINT16 *Window, UINT8 HistCh)
{
    UINT16 HStartPos_HB,HStartPos_LB;
    UINT16 HEndPos_HB,HEndPos_LB;
    UINT16 VStartPos_HB,VStartPos_LB;
    UINT16 VEndPos_HB,VEndPos_LB;

    //CScalerPageSelect(_PAGE0);
    //Image Auto Function boundary Begin
    HStartPos_HB = (Window[0] >> 8) & (0x07);
    HStartPos_LB = Window[0] & (0xff);
    HEndPos_HB = (Window[1] >> 8) & (0x0f);
    HEndPos_LB = Window[1] & (0xff);
    VStartPos_HB = (Window[2] >> 8) & (0x07);
    VStartPos_LB = Window[2] & (0xff);
    VEndPos_HB = (Window[3] >> 8) & (0x0f);
    VEndPos_LB = Window[3] & (0xff);
    CScalerSetByte( _H_BOUNDARY_H_70, ((HStartPos_HB<<4) + HEndPos_HB));
    CScalerSetByte( _H_BOUNDARY_STA_L_71, HStartPos_LB);
    CScalerSetByte( _H_BOUNDARY_END_L_72, HEndPos_LB);
    CScalerSetByte( _V_BOUNDARY_H_73, ((VStartPos_HB<<4) + VEndPos_HB));
    CScalerSetByte( _V_BOUNDARY_STA_L_74, VStartPos_LB);
    CScalerSetByte( _V_BOUNDARY_END_L_75, VEndPos_LB);
    //Image Auto Function boundary End

    //Color Source Select for Detection
    if(HistCh==0)
        CScalerSetByte( _AUTO_ADJ_CTRL0_7A, 0x01);
    else if(HistCh==1)
        CScalerSetByte( _AUTO_ADJ_CTRL0_7A, 0x00);
    else if(HistCh==2)
        CScalerSetByte( _AUTO_ADJ_CTRL0_7A, 0x02);

    //MIN color measured, Accumulation Mode, Start Auto-Function Tracking Function
    CScalerSetByte( _AUTO_ADJ_CTRL1_7D, 0x31);
}

BYTE FindDominant_RTD2547D_SmartFit( UINT16 *Window, UINT8 HistCh)
{
    UINT32 SUM=0;
    UINT32 PxlNum=0;
    UINT32 PEAK=0;
    UINT16 timeout = 2000;

    CScalerSetByte( _DIFF_THRESHOLD_79, 0);//Threshold = 0
    HistWrite_RTD2547D_SmartFit( &Window[0], HistCh);
    do{
        CScalerRead(_AUTO_ADJ_CTRL1_7D, 1, pData, _AUTOINC);
        if(pData[0]==0x30) //check "Hiswirte" finished
        {
            CScalerRead(_AUTO_PHASE_3_84, 4, pData, _AUTOINC);
            SUM = ((UINT32)(pData[0])<<24) + ((UINT32)(pData[1])<<16)   + ((UINT16)pData[2]<<8) + pData[3];
            PxlNum = (Window[1]-Window[0]+1)*(Window[3]-Window[2]+1);
            PEAK = (SUM)/PxlNum;
            break;
        }
        timeout--;
    }while(timeout);

    return(PEAK);

}

BYTE ADC_adjust_RTD2547D(UINT16 *HistWindow, UINT8 Target, UINT8 ADC_Adds, UINT8 ADC_Data, UINT8 HistCh)
{
    UINT8 counter = 0;
    UINT16 max = 0;
    UINT16 min = 255;
    UINT8 PEAK_Level = 0;
    UINT8 diff = 0;

    CScalerPageSelect(_PAGE0);  
    CScalerSetByte(ADC_Adds, ADC_Data);
    do
    {
        PEAK_Level = FindDominant_RTD2547D_SmartFit( &HistWindow[0], HistCh);
    
        diff = YPbPr_ABS(Target, PEAK_Level);

        if(diff == 0)
        {
            break;
        }
        else if(diff != 0 && counter == 9)
        {
            break;
        }
        else if (PEAK_Level >Target)
        {
            max = ADC_Data;
            ADC_Data = (max + min )*(0.5);
            //Write ADC  Reg
            CScalerPageSelect(_PAGE0);  
            CScalerSetByte( ADC_Adds, ADC_Data);
        }
        else if (PEAK_Level < Target)
        {
            min = ADC_Data;
            ADC_Data = (max + min)*(0.5);
            //Write ADC  Reg
            CScalerPageSelect(_PAGE0);  
            CScalerSetByte( ADC_Adds, ADC_Data);
        }
        //DebugPrintf("\nmax_min: ADC_Data = %x", ADC_Data);
        counter++;
    }while(1);

    return (ADC_Data);
}

 BYTE Adjust_Loop(UINT16 *OffsetPos, UINT16 *GainPos, UINT8 OffsetData, UINT8 GainData, UINT8 ADCOffsetAdds, UINT8 ADCGainAdds, UINT8 Channel, UINT8 OffsetTarget, UINT8 GainTarget)
{
    UINT8 Gain_Check;
    UINT8 Offset_Check;
    UINT8 Check_idx = 0;
    
    do{
        //Offset adjustment Begin
        OffsetData = ADC_adjust_RTD2547D( &OffsetPos[0], OffsetTarget, ADCOffsetAdds, OffsetData, Channel);

        //Gain adjustment Begin
        GainData  = ADC_adjust_RTD2547D( &GainPos[0], GainTarget, ADCGainAdds, GainData, Channel);

        Offset_Check = FindDominant_RTD2547D_SmartFit( &OffsetPos[0], Channel);
        Gain_Check   = FindDominant_RTD2547D_SmartFit( &GainPos[0], Channel);
        Check_idx++;
        if(Check_idx>9)
            break;
    }while((YPbPr_ABS(Offset_Check, OffsetTarget)>1  ||  YPbPr_ABS(Gain_Check, GainTarget)>1));
    //DebugPrintf("Offset_Check=%x\n",Offset_Check);
    //DebugPrintf("Gain_Check=%x\n",Gain_Check);
    
    if(Channel_Y == Channel){
        stYPbPrData.YPbPrGain[_GREEN] = GainData;
        stYPbPrData.YPbPrOffset[_GREEN] = OffsetData;
    }
    else if(Channel_U == Channel){
        stYPbPrData.YPbPrGain[_BLUE] = GainData;
        stYPbPrData.YPbPrOffset[_BLUE] = OffsetData;
    }
    else{// if(Channel_V == Channel)
        stYPbPrData.YPbPrGain[_RED] = GainData;
        stYPbPrData.YPbPrOffset[_RED] = OffsetData;
    }

    return(0);
}
/*
//chroma2330
#define Y_Target_Offset_SD  16
#define U_Target_Offset_SD  128
#define V_Target_Offset_SD  128
#define Y_Target_Gain_SD        235
#define U_Target_Gain_SD        202
#define V_Target_Gain_SD        222
//
#define Y_Target_Offset_HD  16
#define U_Target_Offset_HD  128
#define V_Target_Offset_HD  128
#define Y_Target_Gain_HD        235
#define U_Target_Gain_HD        214 
#define V_Target_Gain_HD        230
*/

//VideoBook-ColorBar#2
#define Y_Target_Offset_SD  16
#define U_Target_Offset_SD  128
#define V_Target_Offset_SD  128
#define Y_Target_Gain_SD        235
#define U_Target_Gain_SD        187
#define V_Target_Gain_SD        200
//
#define Y_Target_Offset_HD  16
#define U_Target_Offset_HD  128
#define V_Target_Offset_HD  128
#define Y_Target_Gain_HD        235
#define U_Target_Gain_HD        187 
#define V_Target_Gain_HD        200


BYTE CAutoTuneBalanceNew(void)
{
    UINT16 Active_Region[4],Black_Pos[4],White_Pos[4],Magenta_Pos[4];
    UINT8 Y_Target_Offset,U_Target_Offset,V_Target_Offset;
    UINT8 Y_Target_Gain,U_Target_Gain,V_Target_Gain;
    ADCRGBYUV_2547D ADC_2547D;

    if(stModeInfo.ModeCurr >=4){//HD
        Y_Target_Offset = Y_Target_Offset_HD;
        U_Target_Offset = U_Target_Offset_HD;
        V_Target_Offset = V_Target_Offset_HD;
        Y_Target_Gain = Y_Target_Gain_HD;
        U_Target_Gain = U_Target_Gain_HD;
        V_Target_Gain = V_Target_Gain_HD;
    }
    else{//SD       
        Y_Target_Offset = Y_Target_Offset_SD;
        U_Target_Offset = U_Target_Offset_SD;
        V_Target_Offset = V_Target_Offset_SD;
        Y_Target_Gain = Y_Target_Gain_SD;
        U_Target_Gain = U_Target_Gain_SD;
        V_Target_Gain = V_Target_Gain_SD;
    }
    ActiveRegion_2547D(&Active_Region[0]);
    #if 1//eric 200706011 reduce size               
        #if(_ADC1_INPUT_SWAP_RG)        
            ADC_2547D.Y_ADC_GAIN        = _P0_RED_GAIN_C0;
            ADC_2547D.Y_ADC_OFFSET  = _P0_RED_OFFSET_C3;    
            ADC_2547D.U_ADC_GAIN        = _P0_BLU_GAIN_C2; 
            ADC_2547D.U_ADC_OFFSET  = _P0_BLU_OFFSET_C5; 
            ADC_2547D.V_ADC_GAIN        = _P0_GRN_GAIN_C1; 
            ADC_2547D.V_ADC_OFFSET  = _P0_GRN_OFFSET_C4; 
        #elif(_ADC1_INPUT_SWAP_RB)      
            ADC_2547D.Y_ADC_GAIN        = _P0_GRN_GAIN_C1;
            ADC_2547D.Y_ADC_OFFSET      = _P0_GRN_OFFSET_C4;    
            ADC_2547D.U_ADC_GAIN        = _P0_RED_GAIN_C0; 
            ADC_2547D.U_ADC_OFFSET      = _P0_RED_OFFSET_C3; 
            ADC_2547D.V_ADC_GAIN        = _P0_BLU_GAIN_C2; 
            ADC_2547D.V_ADC_OFFSET      = _P0_BLU_OFFSET_C5; 
        #elif(_ADC1_INPUT_SWAP_GB)          
            ADC_2547D.Y_ADC_GAIN        = _P0_BLU_GAIN_C2;
            ADC_2547D.Y_ADC_OFFSET  = _P0_BLU_OFFSET_C5;    
            ADC_2547D.U_ADC_GAIN        = _P0_GRN_GAIN_C1; 
            ADC_2547D.U_ADC_OFFSET  = _P0_GRN_OFFSET_C4; 
            ADC_2547D.V_ADC_GAIN        = _P0_RED_GAIN_C0; 
            ADC_2547D.V_ADC_OFFSET  = _P0_RED_OFFSET_C3; 
        #else //non-swap
            ADC_2547D.Y_ADC_GAIN        =_P0_GRN_GAIN_C1;
            ADC_2547D.Y_ADC_OFFSET  = _P0_GRN_OFFSET_C4;    
            ADC_2547D.U_ADC_GAIN        = _P0_BLU_GAIN_C2; 
            ADC_2547D.U_ADC_OFFSET  = _P0_BLU_OFFSET_C5; 
            ADC_2547D.V_ADC_GAIN        = _P0_RED_GAIN_C0; 
            ADC_2547D.V_ADC_OFFSET  = _P0_RED_OFFSET_C3; 
        #endif  
    #else
    ADC_Swap_Check_2547D(&ADC_2547D);
    #endif
    //Get Black, White, Magenta Position on the screen
    HistPos( Active_Region[0], Active_Region[1], Active_Region[2], Active_Region[3], &Black_Pos[0], &White_Pos[0], &Magenta_Pos[0]);
    Adjust_Loop(&Black_Pos[0], &White_Pos[0], 128, 128, ADC_2547D.Y_ADC_OFFSET, ADC_2547D.Y_ADC_GAIN, Channel_Y, Y_Target_Offset, Y_Target_Gain);
    Adjust_Loop(&Black_Pos[0], &Magenta_Pos[0], 128, 128, ADC_2547D.U_ADC_OFFSET, ADC_2547D.U_ADC_GAIN, Channel_U, U_Target_Offset, U_Target_Gain);
    Adjust_Loop(&Black_Pos[0], &Magenta_Pos[0], 128, 128, ADC_2547D.V_ADC_OFFSET, ADC_2547D.V_ADC_GAIN, Channel_V, V_Target_Offset, V_Target_Gain);

    //Adjust_Loop(&Black_Pos[0], &White_Pos[0], 128, 128, _P0_GRN_OFFSET_C4, _P0_GRN_GAIN_C1, Channel_Y, Y_Target_Offset, Y_Target_Gain);
    //Adjust_Loop(&Black_Pos[0], &Magenta_Pos[0], 128, 128, _P0_BLU_OFFSET_C5, _P0_BLU_GAIN_C2, Channel_U, U_Target_Offset, U_Target_Gain);
    //Adjust_Loop(&Black_Pos[0], &Magenta_Pos[0], 128, 128, _P0_RED_OFFSET_C3, _P0_RED_GAIN_C0, Channel_V, V_Target_Offset, V_Target_Gain);
    return (1);
}

void CYPbPrPorch_LevelCheck(void)
{
    UINT16 Pos_Porch[4];
//  UINT8 ucTemp;

    CScalerSetByte(_VGIP_HV_DELAY_1E, 0x00);
#if 0
    UINT16 lbound, rbound;
 
    rbound  = stModeUserData.Clock;                                               // Totol Clock Number 
    lbound  = (UINT32)rbound * stModeInfo.IHSyncPulseCount / stModeInfo.IHCount;   // Clock number in HSYNC pulse
    lbound = lbound+10;
    rbound = lbound+10;
    Pos_Porch[0] = lbound;  // H Porch Start
    Pos_Porch[1] = rbound;  // H Porch End
//  pData[0]    = ((lbound >> 4) & 0x70) | (HIBYTE(rbound) & 0x0f);
//  pData[1]    = (LOBYTE(lbound)+0);
//  pData[2]    = (LOBYTE(rbound)+0);
 
    lbound = stModeInfo.IVTotal/2;
    rbound = lbound+10;
    Pos_Porch[2] = lbound;  // V
    Pos_Porch[3] = rbound;  // V
//  pData[3]    = ((lbound >> 4) & 0x70) | (HIBYTE(rbound) & 0x0f);
//  pData[4]    = (LOBYTE(lbound)+0);
//  pData[5]    = (LOBYTE(rbound )+0);
#else
    ActiveRegion_2547D(&Pos_Porch[0]);
    switch(stModeInfo.ModeCurr)
    {
        case _MODE_480I:
//          Pos_Porch[0] = Pos_Porch[0] -38;//21;
//          Pos_Porch[1] = Pos_Porch[0]  + 3;
//          Pos_Porch[2] = Pos_Porch[2] +10;
//          Pos_Porch[3] = Pos_Porch[2] +10;
//      break;
        
        case _MODE_576I:
        case _MODE_576P:
        case _MODE_480P:
            Pos_Porch[0] = 112;//92;
            Pos_Porch[1] = 115;//97;
             //Pos_Porch[0] = Pos_Porch[0] -18;
             //Pos_Porch[1] = Pos_Porch[0]  + 5;
             Pos_Porch[2] = Pos_Porch[2] +10;
             Pos_Porch[3] = Pos_Porch[2] +10;
        break;

        default: //HD(>720p)
             Pos_Porch[0] = 170;
             Pos_Porch[1] = 173;
             //Pos_Porch[0] = Pos_Porch[0] -100;
             //Pos_Porch[1] = Pos_Porch[0]  + 8;
             Pos_Porch[2] = Pos_Porch[2] +10;
             Pos_Porch[3] = Pos_Porch[2] +10;
        break;
    }        
#endif

    
    if((FindDominant_RTD2547D_SmartFit(&Pos_Porch[0],  0) -16) != 0 || (FindDominant_RTD2547D_SmartFit(&Pos_Porch[0],  1) -128) != 0 || (FindDominant_RTD2547D_SmartFit(&Pos_Porch[0],  2)-128) != 0 ){ 
/*      
        ROSPrintf("ADC_Offset=(%d,%d,%d)\n",stYPbPrData.YPbPrOffset[_RED],stYPbPrData.YPbPrOffset[_GREEN] ,stYPbPrData.YPbPrOffset[_BLUE]);
        ROSPrintf("ADC_Gain=(%d,%d,%d)\n",stYPbPrData.YPbPrGain[_RED],stYPbPrData.YPbPrGain[_GREEN] ,stYPbPrData.YPbPrGain[_BLUE]);
        ROSPrintf("Porch Level mismatch:diff_Y=%d,diff_U=%d, diff_V=%d\n",(FindDominant_RTD2547D_SmartFit(&Pos_Porch[0],  0)-16), (FindDominant_RTD2547D_SmartFit(&Pos_Porch[0],  1)-128),(FindDominant_RTD2547D_SmartFit(&Pos_Porch[0],  2)-128));     
        ROSPrintf("after adjustment -->\n");
*/
        #if(_ADC1_INPUT_SWAP_RG)
            ADC_adjust_RTD2547D(&Pos_Porch[0], 128, _P0_BLU_OFFSET_C5, stYPbPrData.YPbPrOffset[_BLUE], Channel_U);
            ADC_adjust_RTD2547D(&Pos_Porch[0], 128, _P0_GRN_OFFSET_C4, stYPbPrData.YPbPrOffset[_GREEN], Channel_V);
            ADC_adjust_RTD2547D(&Pos_Porch[0], 16, _P0_RED_OFFSET_C3, stYPbPrData.YPbPrOffset[_RED], Channel_Y);
        #elif(_ADC1_INPUT_SWAP_RB)
            ADC_adjust_RTD2547D(&Pos_Porch[0], 128, _P0_RED_OFFSET_C3, stYPbPrData.YPbPrOffset[_RED], Channel_U);
            ADC_adjust_RTD2547D(&Pos_Porch[0], 128, _P0_BLU_OFFSET_C5, stYPbPrData.YPbPrOffset[_BLUE], Channel_V);
            ADC_adjust_RTD2547D(&Pos_Porch[0], 16, _P0_GRN_OFFSET_C4, stYPbPrData.YPbPrOffset[_GREEN], Channel_Y);
        #elif(_ADC1_INPUT_SWAP_GB)
            ADC_adjust_RTD2547D(&Pos_Porch[0], 128, _P0_GRN_OFFSET_C4, stYPbPrData.YPbPrOffset[_GREEN], Channel_U);
            ADC_adjust_RTD2547D(&Pos_Porch[0], 128, _P0_RED_OFFSET_C3, stYPbPrData.YPbPrOffset[_RED], Channel_V);
            ADC_adjust_RTD2547D(&Pos_Porch[0], 16, _P0_BLU_OFFSET_C5, stYPbPrData.YPbPrOffset[_BLUE], Channel_Y);
        #else//non-swap
            ADC_adjust_RTD2547D(&Pos_Porch[0], 128, _P0_BLU_OFFSET_C5, stYPbPrData.YPbPrOffset[_BLUE], Channel_U);
            ADC_adjust_RTD2547D(&Pos_Porch[0], 128, _P0_RED_OFFSET_C3, stYPbPrData.YPbPrOffset[_RED], Channel_V);
            ADC_adjust_RTD2547D(&Pos_Porch[0], 16, _P0_GRN_OFFSET_C4, stYPbPrData.YPbPrOffset[_GREEN], Channel_Y);
        #endif
        
        //ADC_adjust_RTD2547D(&Pos_Porch[0], 128, _P0_BLU_OFFSET_AA, stYPbPrData.YPbPrOffset[_BLUE], 1);
        //ADC_adjust_RTD2547D(&Pos_Porch[0], 128, _P0_RED_OFFSET_A8, stYPbPrData.YPbPrOffset[_RED], 2);
        //ADC_adjust_RTD2547D(&Pos_Porch[0], 16, _P0_GRN_OFFSET_A9, stYPbPrData.YPbPrOffset[_GREEN], 0);
/*
        ROSPrintf("Porch_LevelCheck: Y_Level=%d\n", FindDominant_RTD2547D_SmartFit(&Pos_Porch[0],  0));
        ROSPrintf("Porch_LevelCheck: U_Level=%d\n", FindDominant_RTD2547D_SmartFit(&Pos_Porch[0],  1));
        ROSPrintf("Porch_LevelCheck: V_Level=%d\n", FindDominant_RTD2547D_SmartFit(&Pos_Porch[0],  2));
*/
    }
    //else
    //  DebugPrintf("\n Porch Level match %c",0x20);
    
}
#endif // #if(_YPBPR_SUPPORT)
#endif




