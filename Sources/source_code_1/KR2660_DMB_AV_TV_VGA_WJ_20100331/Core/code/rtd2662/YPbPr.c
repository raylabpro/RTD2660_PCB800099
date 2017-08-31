//----------------------------------------------------------------------------------------------------
// ID Code      : YPbPr.c No.0001
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#define __YPBPR__

#include "Core\Header\Include.h"

BYTE code g_tYpbprTemp;

#if(_YPBPR_SUPPORT == _ON)

/**
 * CYPbPrSearchMode
 * Search mode for YPbPr
 * @param <none>
 * @return {_TRUE if there is a preset mode ;_FALSE if not}
 *
*/
//--------------------------------------------------
// Description  : Search mode for YPbPr
// Input Value  : None
// Output Value : YPbPr Mode number
//--------------------------------------------------
BYTE CYPbPrSearchMode(void)
{
    BYTE cnt, modetemp = _MODE_NOSUPPORT;

    for(cnt=0;cnt<_MAX_YPBPR_MODE;cnt++)
    {
        if(CYPbPrCompareMode(cnt) == _TRUE)
        {
            modetemp = cnt;
            //DebugPrintf("\n YPbPrMode = %x\n",modetemp);          
            break;
        }
    }

    if (modetemp == 2) // 576P
    {
        if (stModeInfo.IHSyncPulseCount < 40)  // 1080I 50Hz  295M
            modetemp = 6;
    }

    return modetemp;
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
// Description  : Compare mode in YPbPr mode table
// Input Value  : Mode number
// Output Value : Return _TRUE if get an available mode
//--------------------------------------------------
bit CYPbPrCompareMode(BYTE ucModeCnt)
{                   
    if(abs(stModeInfo.IVFreq - tYPBPR_MODE_TABLE[ucModeCnt].IVFreq) > tYPBPR_MODE_TABLE[ucModeCnt].IVFreqTolerance)
    {
        return _FALSE;
    }

    if(abs(stModeInfo.IHFreq - tYPBPR_MODE_TABLE[ucModeCnt].IHFreq) > tYPBPR_MODE_TABLE[ucModeCnt].IHFreqTolerance)
    {
        return _FALSE;
    }     

    return _TRUE;
}

/**
 * CYPbPrGetModeInfo
 * Get mode information for YPbPr
 * called only by CYPbPrSetupMode
 * @param <none>
 * @return {none}
 *
*/
//--------------------------------------------------
// Description  : Get mode information for YPbPr
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CYPbPrGetModeInfo(void)
{
    stModeInfo.IHTotal = tYPBPR_MODE_TABLE[stModeInfo.ModeCurr].IHTotal;
    stModeInfo.IHStartPos = tYPBPR_MODE_TABLE[stModeInfo.ModeCurr].IHStartPos;
    stModeInfo.IHWidth = tYPBPR_MODE_TABLE[stModeInfo.ModeCurr].IHWidth;

    stModeInfo.IVStartPos = tYPBPR_MODE_TABLE[stModeInfo.ModeCurr].IVStartPos;
    stModeInfo.IVHeight = tYPBPR_MODE_TABLE[stModeInfo.ModeCurr].IVHeight;

    stModeUserData.Clock = stModeInfo.IHTotal;
    stModeUserData.Phase = 0;
    stModeUserData.HPosition = stModeInfo.IHStartPos;
    stModeUserData.VPosition = stModeInfo.IVStartPos;

    // Test
    stModeUserCenterData.CenterClock    = stModeInfo.IHTotal;
    stModeUserCenterData.CenterHPos     = stModeInfo.IHStartPos;
    stModeUserCenterData.CenterVPos     = stModeInfo.IVStartPos;
}

/**
 * CYPbPrStartUp
 * settings for YPbPr startup
 * @param <none>
 * @return {none}
 *
*/
//--------------------------------------------------
// Description  : Start up settings for YPbPr
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CYPbPrStartUp(void)
{
    CScalerCodeW(tYPBPR_TABLE_SET_SCALER);

#if(0)//_YPBPR_HW_AUTO_SOY == _ENABLE)
    CScalerPageSelect(_PAGEB);
    switch(stModeInfo.ModeCurr)
    {
    case 0:  // 576I 50Hz
    case 2:  // 576P 50Hz
    case 4:  // 720P 60Hz
    case 5:  // 1080I 50Hz 274M
    case 6:  // 1080I 50Hz 295M
    case 7:  // 1080I 60Hz
    case 8:  // 720P 50Hz 
    case 9:  // 1080P 50Hz
    case 10: // 1080P 60Hz
        break;   

    case 1:  // 480I 60Hz //for panasonic 480i
        CScalerSetByte(0xc0, 0x1d);
        CScalerSetByte(0xc2, 0x85);
        break;

    case 3:  // 480P 60Hz //for panasonic 480p
        CScalerSetByte(0xc0, 0x1d);
        break;

    }   /*
    if(stModeInfo.ModeCurr ==3)
    {       
        CScalerPageSelect(_PAGEB);
        CScalerSetByte(0xc0, 0x1d);
    }
    else if(stModeInfo.ModeCurr ==1)
    {       
        CScalerPageSelect(_PAGEB);
        CScalerSetByte(0xc0, 0x1d);
        CScalerSetByte(0xc2, 0x85);
    } */
    
#endif  

}

#if defined(CONFIG_VBI_ENABLE)
UINT8 code Y_CC_Init[] =
{
    4, 0xe9, 0x00, 0x00,        // Y from AI01
    9, 0xb0, 0x40, 0xd4, 0x00, 0x00, 0x00, 0xff, 0xff,
    0
};
#endif

   /*
void YPbPrADCDefault(void)
{
    BYTE i;
        static UINT8 code YPBPR_ADC_DEFAULT[10][6] =    
        {           
        149,203,151,126,122,135,//576i
        149,203,151,126,122,135,//480i
        149,203,152,126,122,134,//576P
        149,203,151,126,122,135,//480P
        151,203,151,124,121,132,//720P60
        150,194,150,123,122,131,//1080i50
        149,199,151,124,121,131,//1080i60
        151,203,151,124,121,132,//720P50
        149,195,149,124,122,132,//1080P50
        147,199,147,124,121,133,//1080P60       
        };  

        for(i=0;i<6;i++)
        pData[i]=YPBPR_ADC_DEFAULT[stModeInfo.ModeCurr][i];
    CScalerPageSelect(_PAGE0);
    CScalerWrite(_P0_RED_GAIN_C0, 6, pData, _AUTOINC);      

}*/
/**
 * CYPbPrSetupMode
 * set YPbPr for display
 * @param <none>
 * @return {none}
 *
*/
//--------------------------------------------------
// Description  : Setup YPbPr mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit CYPbPrSetupMode(void)
{
    BYTE option = 0;

#if(_YPBPR_NEW_SYNC_DETECT == _ON)
//Ypbpr issue
/*
    static UINT8 code SOY_CLAMP[10][3] =    
    {   //Clamp Start,  Clamp End,  Compare Level
        0x10,0x18,0x1c,//0x20,      //MODE_576i   (OK )    
        0x08,0x18,0x1c,//0x28,      //MODE_480i   (OK) D1   
        0x10,0x18,0x1c,//0x20,      //MODE_576p   (OK )   
        0x08,0x16,0x1c,//0x25,      //MODE_480p   (OK) D2  
        0x22,0x3A,0x1c,//0x20,      //MODE_720p60 (OK )    
        //0x22,0x3A,0x2a,       //MODE_1080i25(OK )         
        //0x22,0x3A,0x2a,       //MODE_1080i30(OK )   
        0x22,0x3A,0x1c,//0x23,      //MODE_1080i25(OK )         
        0x22,0x3A,0x1c,//0x25,      //MODE_1080i30(OK )   

        0x22,0x3A,0x1c,//0x20,      //MODE_720p50 (OK )    
        0x22,0x3A,0x1c,//0x20,      //MODE_1080p50(OK )
        0x22,0x3A,0x1c,//0x20,      //MODE_1080p60(OK )
    };
*/
    UINT8 code SOY_CLAMP[11][3] =   
    {   //Clamp Start,  Clamp End,  Compare Level
        0x10,0x25,0x20,//0x20,      //MODE_576i   (OK )    
        0x10,0x25,0x20,//0x28,      //MODE_480i   (OK) D1   
        0x10,0x25,0x20,//0x20,      //MODE_576p   (OK )   
        0x10,0x25,0x20,//0x25,      //MODE_480p   (OK) D2  
        0x70,0xA0,0x20,//0x20,      //MODE_720p60 (OK )    
        //0x22,0x3A,0x2a,           //MODE_1080i25(OK )         
        //0x22,0x3A,0x2a,           //MODE_1080i30(OK )   
        0x60,0x85,0x20,//0x23,      //MODE_1080i25(OK ) (274M)          
        0x60,0x85,0x20,//0x23,      //MODE_1080i25(OK ) (295M)          
        //0x40,0x50,0x20,//0x25,    //MODE_1080i30(OK )   
        //0x60,0x85,0x27,//0x25,        //MODE_1080i30(OK ) 
        0x60,0x85,0x20,//0x25,  //MODE_1080i30(OK ) 
        0x70,0xA0,0x20,//0x20,      //MODE_720p50 (OK )    
        0x50,0x65,0x20,//0x20,      //MODE_1080p50(OK )
        0x50,0x65,0x20,//0x20,      //MODE_1080p60(OK )
    };

    //back up table from hill
    /*
    { //Clamp Start, Clamp End, Compare Level
        //Clamp Start, Clamp End,  Compare Level
        0x00,   0x1B,   0x20,       //MODE_576i 
        0x00,   0x17,   0x20,       //MODE_480i
        0x00,   0x17,   0x20,       //MODE_576p
        0x00,   0x13,   0x20,       //MODE_480p
        0x14,   0x67,   0x20,       //MODE_720p60
        0x16,   0x4c,   0x20,       //MODE_1080i25
        0x16,   0x4c,   0x20,       //MODE_1080i30
        0x14,   0x67,   0x20,       //MODE_720p50 
        0x16,   0x44,   0x20,       //MODE_1080p50
        0x16,   0x44,   0x20,       //MODE_1080p60
    };  
    */
#endif

    // Get information from mode table, such as IHTotal, IHStartPos, IHWidth, IVStartPos, IVHeight.
    CYPbPrGetModeInfo();

    // Start up settings of VGA mode.
    CModeStartUpVGA();

    // Start up settings of YPbPR mode.
    CYPbPrStartUp();    
    
    // Get scaling option, Capture window setup, Scaling setup, Display setup
    CModeSetupDisplay();

    // Setup color conversion
    CModeSetupColorConversion();//jerry20070605

	CEepromLoadBriConData();
    CEepromLoadColorTempData();
    CEepromLoadHueSatData();
    CLoadColorModeData();
    CAdjustYpbprSaturation(GET_SATURATION());
    CAdjustYpbprhue(50);//GET_HUE());
    CAdjustBacklight();
    CAdjustBrightness();
    CAdjustContrast();
    CAdjustAdcGainOffset(); //V304 modify
    //080324
///    CAdjustAdcClock(stModeUserData.Clock);
    CAdjustAdcClock(stModeUserData.Clock, 0);
    // Eric 0617
    //CAdjustAdcClockYPbPr(stModeUserData.Clock);
    CAdjustPhase(stModeUserData.Phase);
    CAdjustHPosition();
    CAdjustVPosition();
    CAdjustPeakingFilter(GET_PEAKING_CORING());
    CScalerSetByte(_P1_I_CODE_M_A1,0x00);//eric 20070613 for DVD player     
    CScalerSetByte(_P1_I_CODE_L_A2,0x05);    


#if(_YPBPR_NEW_SYNC_DETECT == _ON)
    //forster modified 061102
    CScalerSetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_G_CLAMP_START_00, SOY_CLAMP[stModeInfo.ModeCurr][0]);
    CScalerSetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_G_CLAMP_END_01, SOY_CLAMP[stModeInfo.ModeCurr][1]);
    CScalerSetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_BR_CLAMP_START_02, SOY_CLAMP[stModeInfo.ModeCurr][0]);
    CScalerSetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_BR_CLAMP_END_03, SOY_CLAMP[stModeInfo.ModeCurr][1]);
    CScalerPageSelect(_PAGE0); //_P0_SOG0_CTRL_AB
#if(_YPBPR_HW_AUTO_SOY != _ENABLE)
    #if(_YPBPR_SYNC_SOURCE == _SOG0)
    CScalerSetByte(_P0_ADC_SOG0_CTRL_D2,SOY_CLAMP[stModeInfo.ModeCurr][2]); 
    #else
    CScalerPageSelect(_PAGEB);
    CScalerSetByte(_PB_SOYCH0_CFG3_C3,SOY_CLAMP[stModeInfo.ModeCurr][2]);//20071122 
    #endif  
#endif       

    CScalerSetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_CLAMP_CTRL0_04, 0x02);
    CScalerSetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_CLAMP_CTRL1_05, 0x83);
         
    CScalerSetBit(_SYNC_INVERT_48, ~_BIT2, _BIT2|_BIT0);    //clamp output & HSFB                       //Modify:2006.4.11A end Jerry
#endif

    CScalerPageSelect(_PAGE0);
    if(CGetSourcePortType(_GET_INPUT_SOURCE()) == _YPBPR_A0_PORT)
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

    CScalerSetByte(_COLOR_CTRL_62, 0x03);
    //YPbPrADCDefault();
    
#ifdef _SRGB_ENLARGE_RANGE
	CScalerSetBit(_COLOR_CTRL_62,~(_BIT6|_BIT2),(_BIT6|_BIT2));   	//  Enable SRGB
#else //#ifdef _SRGB_ENLARGE_RANGE
    CScalerSetBit(_COLOR_CTRL_62,~_BIT2,_BIT2);   	//  Enable SRGB
#endif //#ifdef _SRGB_ENLARGE_RANGE
    CAccAdjust(GET_DCC_MODE());  // set DCC mode

    CAdjustPeakingCoding();

#if(_AdjustCustomerColorMode == _ENABLE)
    CAdjustCustomerColorMode();
#endif

    CScalerPageSelect(_PAGE0);
    CScalerSetBit(_P0_ADC_RBG_CTRL_CE, 0x0F, (1 << 4) & 0xF0);
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    CScalerPageSelect(_PAGE6);
    CScalerSetBit(_P6_ENABLE_BIST_CTRL_A0, ~_BIT3, 0x00);       //Disable De-interlace Mode     

#if(_DE_INTERLACE_SUPPORT == _ON)
    if(stModeInfo.ModeCurr <= 1)    // Only for 480i/576i
        CModeDeInterlaceSetting();
#endif

    //forster modified 061123
    CAdjustInterlaceIVS2DVSDelay();

    pData[0] = CFrameSyncDo();
    if(pData[0] == 2)
    {
        return _FALSE;
    }
        

    if(ucCurrState == _SEARCH_STATE)
        CYPbPrPorch_LevelCheck();
    CAdjustInterlaceIVS2DVSProtection();
    CTimerDelayXms(30);
    CModeSetupEtcs(_FUNCTION_ENABLE);

    return _TRUE;   
}

#if(_YPBPR_HW_AUTO_SOY == _ENABLE)
void CYPbPrHWAutoSOY(void)
{
    CScalerPageSelect(_PAGEB);
    CScalerSetByte(0xc0, 0x41);
    CScalerSetByte(0xc2, 0x89);
    CScalerSetByte(0xc5, 0x07);
    CScalerSetByte(0xc6, 0x40);
    CScalerSetByte(0xc7, 0x00);
    CScalerSetByte(0xc8, 0x20);
    CScalerSetByte(0xc9, 0x00);
    CScalerSetByte(0xc3, 0x9E);
    CScalerSetByte(0xc4, 0x08);
}
#endif

#endif  // End of #if(_YPBPR_SUPPORT == _ON)

