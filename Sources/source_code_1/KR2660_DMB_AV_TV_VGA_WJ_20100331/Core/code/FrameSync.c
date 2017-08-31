//----------------------------------------------------------------------------------------------------
// ID Code      : FrameSync.c No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#define __FRAMESYNC__

#include "Core\Header\Include.h"


//--------------------------------------------------
// Description  : Detect frame sync status
// Input Value  : None
// Output Value : Return _FALSE if frame sync is ok, _TRUE while PLL mislock, buffer underflow/overflow
//--------------------------------------------------

bit CFrameSyncDetect(void)
{
    if (bCNoCheckSyncMode())
        return _FALSE;

    if(GET_POWERSTATUS() && GET_MODESTABLE())
    {
        CScalerRead(_STATUS0_02, 1, pData, _NON_AUTOINC);
        if(((pData[0] & 0x83) == 0))
        {
            return _FALSE;
        }
        else
        {             
            if(_GET_INPUT_SOURCE() == _SOURCE_YPBPR||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1)
               return _FALSE;

			//if(_GET_INPUT_SOURCE() == _SOURCE_VGA)	
			if(_GET_INPUT_SOURCE() == _SOURCE_YPBPR || _GET_INPUT_SOURCE() == _SOURCE_VGA||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1 )
            {   
                //if(pData[0] & 0x80)
                if((pData[0] & 0x03) == 0x00)
                    return _FALSE;
            }   

            CLR_MODESTABLE();
            CLR_FRAMESYNCSTATUS();
            return _TRUE;
        }
    }
    return _FALSE;

}
//--------------------------------------------------
// Description  : Finetune last line problem
// Input Value  : Dclk offset
// Output Value : Return _TRUE if there is no timing change
//--------------------------------------------------
bit CFrameSyncLastLineFinetune(WORD *pDelta)
{
#if(_LAST_LINE_FINETUNE == _LAST_LINE_METHOD_NONE)
    if(CFrameSyncTestSync(*pDelta))
        return _FALSE;
    else
        return _TRUE;
#endif

#if(_LAST_LINE_FINETUNE == _LAST_LINE_METHOD_0)
    // Formula: Tne DEN End to DEN Start Length must be (1280*N)
    // Samsung's Panels.
    WORD dvtotal;
    DWORD dclktotal = 0;

//  CScalerSetDataPortByte(_DISP_ACCESS_PORT_2A, _DISP_NEW_DV_CTRL_22, 0x00);

    CScalerSetByte(_LAST_LINE_H_44, 0x00);
    if(CFrameSyncTestSync(*pDelta))     return _FALSE;

    CScalerRead(_LAST_LINE_H_44, 2, pData, _AUTOINC);
    dclktotal = ((WORD)(pData[0] & 0x0f) << 8) | pData[1];

    CScalerSetByte(_LAST_LINE_H_44, 0x80);
    CTimerDelayXms(40);
    CScalerRead(_LAST_LINE_H_44, 2, pData, _AUTOINC);
    dvtotal = ((WORD)(pData[0] & 0x0f) << 8) | pData[1];

    dclktotal = dclktotal + (DWORD)stDisplayInfo.DHTotal * (dvtotal + 1 - stDisplayInfo.DVHeight);

    //dvtotal = dclktotal / 1280;
    //dvtotal = dclktotal - ((DWORD)dvtotal * 1280);
    //*pDelta   = (dvtotal > (1280 - 128)) ? (*pDelta + 3) : ((dvtotal < 128) ? (*pDelta - 3) : *pDelta);
    dvtotal = dclktotal / Panel.DHWidth;
    dvtotal = dclktotal - ((DWORD)dvtotal * Panel.DHWidth);
    *pDelta = (dvtotal > (Panel.DHWidth - 128)) ? (*pDelta + 3) : ((dvtotal < 128) ? (*pDelta - 3) : *pDelta);

//  CScalerSetDataPortByte(_DISP_ACCESS_PORT_2A, _DISP_NEW_DV_CTRL_22, 0xa0);
    return _TRUE;
#endif

#if(_LAST_LINE_FINETUNE == _LAST_LINE_METHOD_1)
    // Formula: Tne DEN End to DEN Start Length must be (4096*N + 128)
    // CPT's Panels.
    WORD dvtotal;
    DWORD dclktotal = 0;

    CScalerSetDataPortByte(_DISP_ACCESS_PORT_2A, _DISP_NEW_DV_CTRL_22, 0x00);
    CScalerSetByte(_LAST_LINE_H_44, 0x00);
    if(CFrameSyncTestSync(*pDelta))
        return _FALSE;
    CScalerRead(_LAST_LINE_H_44, 2, pData, _AUTOINC);
    dclktotal = ((WORD)(pData[0] & 0x0f) << 8) | pData[1];
    CScalerSetByte(_LAST_LINE_H_44, 0x80);
    CTimerDelayXms(40);
    CScalerRead(_LAST_LINE_H_44, 2, pData, _AUTOINC);
    dvtotal = ((WORD)(pData[0] & 0x0f) << 8) | pData[1];
    dclktotal = dclktotal + (DWORD)stDisplayInfo.DHTotal * (dvtotal + 1 - stDisplayInfo.DVHeight) - 128;
    dvtotal = dclktotal / 4096;
    dvtotal = dclktotal - ((DWORD)dvtotal * 4096);
    *pDelta = (dvtotal > (4096 - 128)) ? (*pDelta + 3) : ((dvtotal < 128) ? (*pDelta - 3) : *pDelta);
    
#if(_NEW_DV_CTRL_ENABLE)
    CScalerSetDataPortByte(_DISP_ACCESS_PORT_2A, _DISP_NEW_DV_CTRL_22, 0xa0);
#endif

    return _TRUE;
#endif

#if(_LAST_LINE_FINETUNE == _LAST_LINE_METHOD_2)
  #if 1//eric 0706
    // Formula: Fixed to target last line pixels

    DWORD dclktotal;
    DWORD dclktarget;
    WORD dvtotal;
    WORD lastlinepixels;
    SWORD offsetnew;

    // Turn off new timing method
    CScalerSetDataPortByte(_DISP_ACCESS_PORT_2A, _DISP_NEW_DV_CTRL_22, 0x00);
    // Measure DVTotal
    CScalerSetByte(_LAST_LINE_H_44, 0x80);
    if(CFrameSyncTestSync(*pDelta))
        return _FALSE;
    CScalerRead(_LAST_LINE_H_44, 2, pData, _AUTOINC);
    dvtotal = ((WORD)(pData[0] & 0x0f) << 8) | pData[1];
    // Measure last line clock numbers
    CScalerSetByte(_LAST_LINE_H_44, 0x00);
    if(CFrameSyncTestSync(*pDelta))     return _FALSE;
    CScalerRead(_LAST_LINE_H_44, 2, pData, _AUTOINC);
    lastlinepixels = ((WORD)(pData[0] & 0x0f) << 8) | pData[1];
    // Calculate total display clock numbers in a frame
    dclktotal = (DWORD)stDisplayInfo.DHTotal * dvtotal + lastlinepixels;
    // Calculate mininum path of target clock numbers
    if(lastlinepixels > _LAST_LINE_TARGET){
        if((lastlinepixels - _LAST_LINE_TARGET) > (stDisplayInfo.DHTotal / 2))
            dclktarget = (DWORD)stDisplayInfo.DHTotal * (dvtotal + 1) + _LAST_LINE_TARGET;  // +
        else
            dclktarget = (DWORD)stDisplayInfo.DHTotal * (dvtotal) + _LAST_LINE_TARGET;  // -
    }
    else{
        if((_LAST_LINE_TARGET - lastlinepixels) > (stDisplayInfo.DHTotal / 2))
            dclktarget = (DWORD)stDisplayInfo.DHTotal * (dvtotal - 1) + _LAST_LINE_TARGET;  // -
        else
            dclktarget = (DWORD)stDisplayInfo.DHTotal * (dvtotal) + _LAST_LINE_TARGET;  // +
    }
    // Calculate and apply new offset
    offsetnew = (((SDWORD)dclktotal - (SDWORD)dclktarget) * ((SDWORD)32768 - (SDWORD)*pDelta)) * 2 / (SDWORD)dclktotal;
    offsetnew = (offsetnew / 2) + ((offsetnew > 0) ? (offsetnew & 0x01) : -(offsetnew & 0x01));
    offsetnew = offsetnew + *pDelta;
    if(CFrameSyncTestSync(offsetnew))
        return _FALSE;
    // Check underflow/overflow. If failed, try another side.
    if(pData[0]){
        if(pData[0] & 0x02)
            dclktarget = dclktarget + stDisplayInfo.DHTotal;
        else
            dclktarget = dclktarget - stDisplayInfo.DHTotal;
        offsetnew = (((SDWORD)dclktotal - (SDWORD)dclktarget) * ((SDWORD)32768 - (SDWORD)*pDelta)) * 2 / (SDWORD)dclktotal;
        offsetnew = (offsetnew / 2) + ((offsetnew > 0) ? (offsetnew & 0x01) : -(offsetnew & 0x01));
        offsetnew = offsetnew + *pDelta;
        if(CFrameSyncTestSync(offsetnew))     return _FALSE;
    }
    *pDelta = offsetnew;
    return _TRUE;
  #else
    // Formula: Last line limit.
    CScalerSetByte(_DISP_NEW_DV_CTRL_22, 0x00);
    CScalerSetByte(_LAST_LINE_H_44, 0x00);
    if(CFrameSyncTestSync(*pDelta))
        return _FALSE;
    CScalerRead(_LAST_LINE_H_44, 2, pData, _AUTOINC);
    dclktotal = ((WORD)(pData[0] & 0x0f) << 8) | pData[1];
    *pDelta = (dclktotal > 1280) ? (*pDelta + 3) : ((dclktotal > 640) ? (*pDelta - 3) : *pDelta);
    return _TRUE;
  #endif
#endif

}

//--------------------------------------------------
// Description  : Finetune Dclk offset for spread spectrum
// Input Value  : Dclk offset
// Output Value : Return _FALSE if there is no timing change
//--------------------------------------------------
BYTE CFrameSyncSpreadSpectrumFinetune(WORD *pDelta)
{
    //Enable the spread spectrum function
    CAdjustSpreadSpectrumRange(_DCLK_SPREAD_RANGE);
        
    *pDelta = *pDelta + tDCLK_OFFSET[_DCLK_SPREAD_RANGE];
        
    if(CFrameSyncTestSync(*pDelta))     return 2;
        
    if(pData[0])
    {
        //Fine-tune DCLK offset
        if(CFrameSyncTestSync((pData[0] & 0x02) ? (*pDelta - 1) : (*pDelta + 1)))     return 2;
                
        if(pData[0] & 0x03)     return 1;   //Frame sync fail!
    }
        
    return 0;
}

//--------------------------------------------------
// Description  : Calculate the suitable framesync point
// Input Value  : None
// Output Value : Return Dclk offset
//--------------------------------------------------
WORD CFrameSyncFastDo(void)
{
    DWORD aclkcnt = 0;
    DWORD offset;
    BYTE mcode, div;

    CScalerSetBit(_SYNC_SELECT_47, ~(_BIT1 | _BIT0), 0x00); // Measure input active region by xtal clk
    
    //Enable active region measure  Ken
    CScalerSetBit(_STABLE_PERIOD_H_50, ~_BIT4, _BIT4);
    CAdjustSyncProcessorMeasureStart();
        
    if(CTimerPollingEventProc(60, CMiscModeMeasurePollingEvent))
    {
    
        CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT6, _BIT6);
        CScalerSetByte(_MEAS_ACTIVE_REGION_59, 0x00);
                
        pData[0] = 0;
                
        CScalerRead(_MEAS_ACTIVE_REGION_59, 3, &pData[1], _NON_AUTOINC);
                
        aclkcnt = ((DWORD *)pData)[0];
        

        CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~(_BIT7 | _BIT5), 0x00);
        CScalerPageSelect(_PAGE1);
        CScalerRead(_P1_DPLL_M_BF, 1, &mcode, _NON_AUTOINC);
        mcode += 2;
        CScalerRead(_P1_DPLL_N_C0, 1, &div, _NON_AUTOINC);
        
        div = 0x01 << ((div & 0x30) >> 4);  //divider value
        
        offset = (DWORD)32768 * div * 2 * _DPLL_N_CODE * stDisplayInfo.DHTotal / aclkcnt * stDisplayInfo.DVHeight / mcode;
                
        offset = 32768 - offset;
                
        //CScalerSetBit(_SYNC_SELECT_47, ~(_BIT1 | _BIT0), _BIT1);
    }
    else
    {
        offset = 0xffff;
    }
        
    CScalerSetBit(_STABLE_PERIOD_H_50, ~_BIT4, 0x00);
       
    return (WORD)offset;
}

//--------------------------------------------------
// Description  : Apply Dclk frequency and get the overflow/underflow information
// Input Value  : Dclk offset
// Output Value : Return _FALSE if there is no timing change
//--------------------------------------------------
bit CFrameSyncTestSync(WORD usOffset)
{
    CScalerSetBit(_SYNC_SELECT_47, ~_BIT0, 0x00);
    CAdjustSyncProcessorMeasureStart();
    
    // Apply Dclk frequency setting
    CAdjustDclkOffset(usOffset);
    
    CScalerSetByte(_STATUS0_02, 0x00);                      // Clear Status
    
    CTimerWaitForEvent(_EVENT_DVS);                         // Wait for Frame End
    CTimerWaitForEvent(_EVENT_DVS);                         // Wait for Frame End
    //CTimerWaitForEvent(_EVENT_DVS);                         //V400 modify for Interlace mode
    //CTimerWaitForEvent(_EVENT_IVS);                         // Wait for Frame End
    
    //CTimerWaitForEvent(_EVENT_IVS);                         // Wait for Frame End
    
    //CTimerWaitForEvent(_EVENT_IVS);                         // Wait for Frame End

    CScalerRead(_STATUS0_02, 1, pData, _NON_AUTOINC);       // Read status
    
    // Input timing changed
    if (pData[0] & 0x60)
        return _TRUE;
    
    // Save underflow/overflow information into pData[0]
#if(_VIDEO_TV_SUPPORT)
    if(_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
       pData[0] = 0x00;
    else
#endif
       pData[0] &= 0x03;
    
    return _FALSE;                                          // Success
}

//--------------------------------------------------
// Description  : Adjust Dclk offset to meet frame sync
// Input Value  : None
// Output Value : Return 0 if sucess
//--------------------------------------------------
BYTE CFrameSyncDo(void)
{
    WORD buffer, delta;
    BYTE fine, result = 0;

    // Read the DCLK offset
    CScalerPageSelect(_PAGE1);

    CScalerRead(_P1_DCLK_FINE_TUNE_OFFSET_MSB_C4, 2, pData, _AUTOINC);
    buffer  = (((WORD)pData[0] & 0x0f) << 8) | pData[1];
    // Disable the Fixed DVTOTAL & Last Line Length Fucntion
    CScalerSetBit(_P1_EVEN_FIXED_LAST_LINE_CTRL_CA, ~_BIT1, 0x00);
        
    // Disable spread spectrum
    CAdjustSpreadSpectrumRange(0);

    // Fast Framesync method
    delta = CFrameSyncFastDo();
        
    if(CFrameSyncTestSync(delta))       return 2;
            
    if(pData[0] == 0)
    {
        result |= _BIT0;
                
        if(CFrameSyncTestSync(delta + _OFFSET_STEP))        return 2;
        if(pData[0] == 0)       result |= _BIT1;
                
        if(CFrameSyncTestSync(delta - _OFFSET_STEP))        return 2;
        if(pData[0] == 0)       result |= _BIT2;

            if(result == (_BIT0 | _BIT1))
                delta += _OFFSET_STEP / 2;
            else if(result == (_BIT0 | _BIT2))
                delta -= _OFFSET_STEP / 2;
    }
    //DebugPrintf("\nresult = 0x%x", result);
    
    if(result == 0)     // Fast search fail, do iteration search
    {
        // Apply Dclk frequency setting
        CAdjustDclkOffset(buffer);
        // Search first satisfied DCLK setting for frame-sync
        result  = 0x00;
        fine    = _SEARCH_TIME;
        do{
            if(CFrameSyncTestSync(buffer))      return 2;
                        
            if(pData[0] == 0)       break;
                        
            if(pData[0] & 0x02)
                buffer  -= (result & 0x01) ? (_OFFSET_STEP / 2) : _OFFSET_STEP;  // underflow
            else
                buffer  += (result & 0x02) ? (_OFFSET_STEP / 2) : _OFFSET_STEP;  // overflow
                
            result  = pData[0];  // 會儲存上一次是 over or under
        }
        while(--fine);
                
        if(fine == 0x00)    return 1;
                
        // If default offset is OK....
        if(result == 0x00)
        {
            if(CFrameSyncTestSync(buffer + _OFFSET_STEP))     return 2;
            result  = pData[0] ? pData[0] : 0x01;       //  normal result == 0 , over/under,  resuit = pdata0
        }
                
        // Search most satisfied DCLK setting for frame-sync
        delta = buffer;
        fine  = 4;
        do
        {
            WORD temp = (result & 0x01) ? delta + (_OFFSET_STEP / 2) : delta - (_OFFSET_STEP / 2);
                        
            if(CFrameSyncTestSync(temp))        return 2;
                        
            if(pData[0])        break;
                        
            delta   = temp;
        }
        while(--fine);
                
        delta   = (buffer + delta) >> 1;
    }
                                  
    if(!CFrameSyncLastLineFinetune(&delta))     return 2;
        
    result = CFrameSyncSpreadSpectrumFinetune(&delta);
    if(result != 0)     return result;
        
    SET_FRAMESYNCSTATUS();
        
    return 0;
}


