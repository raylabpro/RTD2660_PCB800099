#include "Core\Header\Include.h"

#if(_FAC_OSD)



#define FACTORYSUBMENU_LINECOLOR(row,color)		OSDLine(row, COL(15), LENGTH(38), color, BYTE_COLOR)
#define FACTORYSUBMENU_TEXTOUT(str,row)			TextOutCalcWidth(str,row,20,30,14 * 12)


//-----------------------------------------------------------
void EnterFacBurnin(void)
{
  	OSDClear(6, 1, 17, 5, 0x00,BYTE_DISPLAY);
	if(GET_BURNIN_STATE()==_BURNIN_ON)
    {	
    	SET_BURNIN_STATE(0);
    	TextOutCalcWidth(sFacOff,ROW(6),COL(17),5,5*12);
    }
    else
    {
    	SET_BURNIN_STATE(1);
		TextOutCalcWidth(sFacOn,ROW(6),COL(17),5,5*12);
	}
	CEepromSaveSystemData();
}

//-----------------------------------------------------------
void ShowBackColorText(void)
{
	BYTE *str;
	switch(GET_BACKGROUNDCOLOE())
	{
	 	case _RED:			str = sRed;	  			break;
		case _GREEN:		str = sGreen;			break;
		case _BLUE:			
		default:
				
							str = sBlue;			break;
	}
	OSDLine(10, 17, 16, 0x00,BYTE_DISPLAY);
	TextOutCalcWidth(str,ROW(10),COL(17),16,16 * 12);

}
//-----------------------------------------------------------

void EnterFacReset(void)
{
    BYTE ucTemp0 = GET_POWERSTATUS();
    BYTE ucTemp1 = _GET_INPUT_SOURCE();
    BYTE ucTemp3 = GET_DISPLAYMODE();
    BYTE ucGamma = stSystemData.Gamma;
	OSDLine(11, COL(1), LENGTH(11), _MENU_ADJUST_COLOR, BYTE_COLOR);
    CEepromLoadDefault(1);

    if (ucTemp0)    
       SET_POWERSTATUS();
    else
       CLR_POWERSTATUS();
	ucGamma = stSystemData.Gamma;
    _SET_INPUT_SOURCE(ucTemp1);
    SET_DISPLAYMODE(ucTemp3);
    CEepromSaveSystemData();
    CEepromSaveOsdUserData();
    if(_GET_INPUT_SOURCE() == _SOURCE_VGA || _GET_INPUT_SOURCE() == _SOURCE_YPBPR||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1)
      CAdjustAdcGainOffset();
    CAdjustBrightness();
    CAdjustBacklight();
    CAdjustContrast();
    CSetVolume();
    CAdjustPeakingCoding();
    CAdjustGammaTable(GET_GAMMA());
    if(bSourceVideo())
    {
        kx_CAdjustVDCHue(GET_HUE());
        CVideoSetSaturation(GET_SATURATION());
    }
    else
    {
    	if((_GET_INPUT_SOURCE() != _SOURCE_YPBPR)&&(_GET_INPUT_SOURCE() != _SOURCE_YPBPR1))
        	CAdjustYpbprhue(50);
        	
        if(_GET_INPUT_SOURCE() == _SOURCE_YPBPR||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1)
        {
            CAdjustYpbprhue(GET_HUE());
            CAdjustYpbprSaturation(GET_SATURATION());
        }
    }
	if(GET_NOISEREDUTION())
		CScalerSetBit(_P6_UZD_CTRL1_E4, ~(_BIT3 |_BIT2), _BIT2); 	//For 480i/576i SU case,open NR func.
	else
		CScalerSetBit(_P6_UZD_CTRL1_E4, ~(_BIT3 |_BIT2), 0x00); 	//For 480i/576i SU case,close NR func.

    CDrawFacItemValue();
	ShowBackColorText();

    SETCOLOR_FACMAINMENU_SELLINE(11, _MENU_SELECT_COLOR);
}

//-----------------------------------------------------------
void CEnterFacGamma(void)
{
    ucOsdState = _MI_FAC_GAMMA_ADJ;
    OSDLine(7, COL(1), LENGTH(11), _MENU_ADJUST_COLOR, BYTE_COLOR);
}
//-----------------------------------------------------------
void CEnterFacADJ(void)
{
    ucOsdState = _MI_FAC_BACKLIGHT_ADJ;
	OSDLine(9, COL(1), LENGTH(10), _MENU_ADJUST_COLOR, BYTE_COLOR);

}
//-----------------------------------------------------------
void CEnterFacBackColor(void)
{
	ucOsdState = _MI_FAC_BACKCOLOR_ADJ;
	OSDLine(10, COL(1), LENGTH(10), _MENU_ADJUST_COLOR, BYTE_COLOR);
}

//-----------------------------------------------------------
void CEnterFacNR(void)
{
   	OSDClear(8, 1, 17, 5, 0x00,BYTE_DISPLAY);
	if(GET_NOISEREDUTION())
    {	
    	SET_NOISEREDUTION(0);
    	TextOutCalcWidth(sFacOff,ROW(8),COL(17),5,5*12);
    }
    else
    {
    	SET_NOISEREDUTION(1);
		TextOutCalcWidth(sFacOn,ROW(8),COL(17),5,5*12);
	}

	CTimerWaitForEvent(_EVENT_DEN_STOP);
	CScalerPageSelect(_PAGE6);
	if(GET_NOISEREDUTION())
		CScalerSetBit(_P6_UZD_CTRL1_E4, ~(_BIT3 |_BIT2), _BIT2); 	//For 480i/576i SU case,open NR func.
	else
		CScalerSetBit(_P6_UZD_CTRL1_E4, ~(_BIT3 |_BIT2), 0x00); 	//For 480i/576i SU case,close NR func.
	CEepromSaveSystemData();
}

//-----------------------------------------------------------
void DrawFactoryMenu()
{
    if (_GET_INPUT_SOURCE() != _SOURCE_VGA)
        return;

    COsdFxDisableOsd();

    SetOsdMap(tFactoryMenuOsdMap);
    CCloseAllWindows();

    OSDClear(ROW(0), HEIGHT(14), COL(0), WIDTH(35), 0x8C, BYTE_ATTRIB);
    OSDClear(ROW(0), HEIGHT(14), COL(0), WIDTH(35), 0x00, BYTE_DISPLAY);
	OSDClear(ROW(0), HEIGHT(14), COL(0), WIDTH(35), _MENU_NORMAL_COLOR, BYTE_COLOR);
    SetOSDDouble(0x00);  

   	COsdLoad1BitFontWidth12(FntFacFont,0x80,0x04);	
	ucOsdState = _MI_FAC_AUTOCOLOR;
	COsdFxDrawWindow(0,0,									//WORD usXStart,WORD usYStart,  
					450,240,	//WORD usXEnd,WORD usYEnd,  
					tMainWindowStyle);						//BYTE *pStyle)

	OSDPosition(450,200,3, 3,0x03);
   
    // Auto Color
	CTextOutBase(sFacAdjustColor,COL(1),ROW(1));
    // Gain
	TextOutCalcWidth(sFacGain,ROW(2),COL(1),16,16 * 12);
    // Offset
	TextOutCalcWidth(sFacOffset,ROW(3),COL(1),16,16 * 12);
    // 9300
	TextOutCalcWidth(sFac9300,ROW(4),COL(1),16,16 * 12);
    // 6500
	TextOutCalcWidth(sFac6500,ROW(5),COL(1),16,16 * 12);
    // BurnIn
	TextOutCalcWidth(sBurnIn,ROW(6), COL(1),16,16 * 12);
    // Gain R  G  B
	Gotoxy(COL(17),ROW(2), BYTE_DISPLAY);
	Textout(sFacRGB);
    // Offset R  G  B
	Gotoxy(COL(17),ROW(3), BYTE_DISPLAY);
	Textout(sFacRGB);
    // 9300 R  G  B
	Gotoxy(COL(17),ROW(4), BYTE_DISPLAY);
	Textout(sFacRGB);
    // 6500 R  G  B
	Gotoxy(COL(17),ROW(5), BYTE_DISPLAY);
	Textout(sFacRGB);
    // Gamma
	TextOutCalcWidth(sGamma,ROW(7),COL(1),16,16 * 12);
    // N.R
	Gotoxy(COL(1),ROW(8), BYTE_DISPLAY);
	Textout(sFacNR);
    // BackLight adj
	TextOutCalcWidth(sFacLightADJ,ROW(9), COL(1),16,16 * 12);
#if(_BACKLIGHT_USE_FAC_ADJ == _DISABLE)
	OSDClear(ROW(9), HEIGHT(1), COL(1), WIDTH(35), 0x70, BYTE_COLOR);
#endif
	// BackColor
	TextOutCalcWidth(sFacBackColor,ROW(10), COL(1),16,16 * 12);
	OSDClear(ROW(10), HEIGHT(1), COL(1), WIDTH(35), 0x70, BYTE_COLOR);
	ShowBackColorText();

    // Reset
	CTextOutBase(sFacReset,COL(1), ROW(11));
	//EXIT
	CTextOutBase(sFacExit,COL(1),ROW(12));
	//Version
	OSDClear(ROW(12), HEIGHT(1), COL(13), WIDTH(35-12), 0xF0, BYTE_COLOR);  // Color RED
	CTextOutBase(sFacVer,COL(13),ROW(12));
			
	SETCOLOR_FACMAINMENU_SELLINE(1,_MENU_SELECT_COLOR);
    CDrawFacItemValue();
	COsdFxEnableOsd();
	bOSDTimeOut = 0;	
}

//---------------------------------------------------------------------------
void CDrawFacItemValue(void)
{
    // ADC GAIN
	CFacShowNumber(18,2,stAdcData.AdcGain[_RED]);
	CFacShowNumber(25,2,stAdcData.AdcGain[_GREEN]);
	CFacShowNumber(31,2,stAdcData.AdcGain[_BLUE]);

    // ADC OFFSET
	CFacShowNumber(18,3,stAdcData.AdcOffset[_RED]);
	CFacShowNumber(25,3,stAdcData.AdcOffset[_GREEN]);
	CFacShowNumber(31,3,stAdcData.AdcOffset[_BLUE]);

    // 9300
    SET_COLOR_TEMP_TYPE(_CT_9300);
	CEepromLoadColorTempData();
	CFacShowNumber(18,4,stColorTempData.ColorTemp[_RED]);
	CFacShowNumber(25,4,stColorTempData.ColorTemp[_GREEN]);
	CFacShowNumber(31,4,stColorTempData.ColorTemp[_BLUE]);

    // 6500
	SET_COLOR_TEMP_TYPE(_CT_6500);
	CEepromLoadColorTempData();
	CFacShowNumber(18,5,stColorTempData.ColorTemp[_RED]);
	CFacShowNumber(25,5,stColorTempData.ColorTemp[_GREEN]);
	CFacShowNumber(31,5,stColorTempData.ColorTemp[_BLUE]);

    // BURNIN
   	if(GET_BURNIN_STATE()==_BURNIN_ON)
    	TextOutCalcWidth(sFacOn,ROW(6),COL(17),5,5*12);
    else
		TextOutCalcWidth(sFacOff,ROW(6),COL(17),5,5*12);

    // GAMMA
  	CFacShowNumber(17, 7, GET_GAMMA());

    // N.R
   	if(GET_NOISEREDUTION())
    	TextOutCalcWidth(sFacOn,ROW(8),COL(17),5,5*12);
    else
		TextOutCalcWidth(sFacOff,ROW(8),COL(17),5,5*12);
  	
    // BackLight adj
	CFacShowNumber(17,9,stSystemData.BackLight);
}

//---------------------------------------------------------------------------
void MFactoryMenuAdj(BYTE ucMode)
{
    BYTE ucNewItem = AdjustMenuItem(_MI_FAC_AUTOCOLOR,_MI_FAC_EXIT,ucMode);

    if(ucNewItem == ucOsdState)
    	return;
    
    // 1. Clear Current Menu
    SETCOLOR_FACMAINMENU_SELLINE(ucOsdState+1-_MI_FAC_AUTOCOLOR,_MENU_NORMAL_COLOR);
    
    // 2. Change ucOsdState
    ucOsdState = ucNewItem;

	if(ucMode == 0)
	{
	    if (ucOsdState == _MI_FAC_BACKCOLOR)
	        ucOsdState = AdjustMenuItem(_MI_FAC_AUTOCOLOR,_MI_FAC_EXIT,ucMode);
	}

#if(_BACKLIGHT_USE_FAC_ADJ == _DISABLE)
    if (ucOsdState == _MI_FAC_ADJ)
        ucOsdState = AdjustMenuItem(_MI_FAC_AUTOCOLOR,_MI_FAC_EXIT,ucMode);
#endif


	if(ucMode == 1)
	{
	    if (ucOsdState == _MI_FAC_BACKCOLOR)
	        ucOsdState = AdjustMenuItem(_MI_FAC_AUTOCOLOR,_MI_FAC_EXIT,ucMode);
	}

    
    // 3. Draw New Item   
    SETCOLOR_FACMAINMENU_SELLINE(ucOsdState+1-_MI_FAC_AUTOCOLOR,_MENU_SELECT_COLOR);

   	// 4. Change RGB
   	switch(ucOsdState)
   	{
   		case _MI_FAC_9300:      
       		SET_COLOR_TEMP_TYPE(_CT_9300);
       		CEepromLoadColorTempData();
    		CAdjustContrast();
    		break;
		
   		case _MI_FAC_6500:		
       		SET_COLOR_TEMP_TYPE(_CT_6500);
       		CEepromLoadColorTempData();
    		CAdjustContrast();
    		break;
   	}
}

//-----------------------------------------------------------
void ExitFacMenu(void)
{
	COsdDispOsdTimerEvent();
	bOSDTimeOut=1;
}

//-----------------------------------------------------------
void MFactoryEnterSub(void)
{
    switch(ucOsdState)
    {
        case _MI_FAC_AUTOCOLOR:    
            CAutoDoWhiteBalance();
            CFacShowNumber(18,2,stAdcData.AdcGain[_RED]);
    		CFacShowNumber(25,2,stAdcData.AdcGain[_GREEN]);
    		CFacShowNumber(31,2,stAdcData.AdcGain[_BLUE]);
    
    		CFacShowNumber(18,3,stAdcData.AdcOffset[_RED]);
    		CFacShowNumber(25,3,stAdcData.AdcOffset[_GREEN]);
    		CFacShowNumber(31,3,stAdcData.AdcOffset[_BLUE]);
            break;

        case _MI_FAC_9300:
        	SETCOLOR_FACMAINMENU_SELLINE(ucOsdState+1-_MI_FAC_AUTOCOLOR,_MENU_NORMAL_COLOR);
        	ucOsdState=_MI_FAC_9300_R;
        	OSDLine(ROW(4), COL(16), LENGTH(5), _MENU_SELECT_COLOR, BYTE_COLOR);			
            break;

        case _MI_FAC_6500:             
            SETCOLOR_FACMAINMENU_SELLINE(ucOsdState+1-_MI_FAC_AUTOCOLOR,_MENU_NORMAL_COLOR);
            ucOsdState=_MI_FAC_6500_R;
            OSDLine(ROW(5), COL(16), LENGTH(5), _MENU_SELECT_COLOR, BYTE_COLOR);         
            break;
        	
        case _MI_FAC_GAIN:           
            SETCOLOR_FACMAINMENU_SELLINE(ucOsdState+1-_MI_FAC_AUTOCOLOR,_MENU_NORMAL_COLOR);
            ucOsdState=_MI_FAC_GAIN_R;
            OSDLine(ROW(2), COL(16), LENGTH(5), _MENU_SELECT_COLOR, BYTE_COLOR);         
            break;
			
        case _MI_FAC_OFFSET: 
			SETCOLOR_FACMAINMENU_SELLINE(ucOsdState+1-_MI_FAC_AUTOCOLOR,_MENU_NORMAL_COLOR);
            ucOsdState=_MI_FAC_OFFSET_R;
            OSDLine(ROW(3), COL(16), LENGTH(5), _MENU_SELECT_COLOR, BYTE_COLOR);         
            break;
            
        case _MI_FAC_BURNIN:	
        	EnterFacBurnin();
			break;

        case _MI_GAMMA:
            CEnterFacGamma();
            break;

        case _MI_FAC_NR:
            CEnterFacNR();
            break; 
			 
		case _MI_FAC_ADJ:
            CEnterFacADJ();
            break;   
			                   
    	case _MI_FAC_BACKCOLOR:
            CEnterFacBackColor();
            break;                      

        case _MI_FAC_RESET:
            EnterFacReset();
            break;

        case _MI_FAC_EXIT: 		
            ExitFacMenu();                      
			break;
    }
}


//---------------------------------------------------------------------------
void MFactoryProc()
{
    switch(ucOsdEventMsg)
    {
//        case _OE_ADJ_INC:           MFactoryValueAdj(_INC);              break;
//        case _OE_ADJ_DEC:           MFactoryValueAdj(_DEC);              break;
        case _OE_MENU_NEXT:         MFactoryMenuAdj(_NEXT);              break;
        case _OE_MENU_PREV:         MFactoryMenuAdj(_PREV);              break;
        case _OE_ENTER_SUBMENU:     MFactoryEnterSub();                  break;
        case _OE_RETURN_UPMENU:     						             break;
    }

    CTimerReactiveTimerEvent(SEC(GET_OSDTIMEOUT()), COsdTimeOut);
}

//-----------------------------------------------------------
void MFac9300ReturnMenu()
{
    OSDLine(ROW(4),COL(16+(ucOsdState-_MI_FAC_9300_R)*6),LENGTH(6),_MENU_NORMAL_COLOR,BYTE_COLOR);
    ucOsdState = _MI_FAC_9300;
    SETCOLOR_FACMAINMENU_SELLINE(4, _MENU_SELECT_COLOR);
}

//-----------------------------------------------------------
void MFac9300MenuAdj(BYTE ucMode)
{
    BYTE ucNewItem;

    if(ucMode==_INC)
    { 	
    	if(ucOsdState>_MI_FAC_9300_R-1 && ucOsdState<_MI_FAC_9300_B)
    		ucNewItem=ucOsdState+1;
    	else
    		ucNewItem=_MI_FAC_9300;
    }
    else
	{
	    if(ucOsdState>_MI_FAC_9300_R && ucOsdState<_MI_FAC_9300_B+1)
    		ucNewItem=ucOsdState-1;
    	else
    		ucNewItem=_MI_FAC_9300;
	}
    // 1. Clear Current Menu
	OSDLine(ROW(4),COL(16+(ucOsdState-_MI_FAC_9300_R)*6),LENGTH(6),_MENU_NORMAL_COLOR,BYTE_COLOR);


    // 2. Change ucOsdState
    ucOsdState = ucNewItem;

    // 3. Draw New Item
    if(ucOsdState>_MI_FAC_9300_R-1 && ucOsdState<_MI_FAC_9300_B+1)
    	OSDLine(ROW(4),COL(16+(ucOsdState-_MI_FAC_9300_R)*6),LENGTH(6),_MENU_SELECT_COLOR,BYTE_COLOR);
    else
    	SETCOLOR_FACMAINMENU_SELLINE(4,_MENU_SELECT_COLOR);

}

//-----------------------------------------------------------
void MFac9300ValAdj(BYTE ucMode)
{
	SET_COLOR_TEMP_TYPE(_CT_9300);
	CEepromLoadColorTempData();
    SET_KEYREPEATENABLE();
    switch(ucOsdState)
    {
    	case _MI_FAC_9300_R :
    	    stColorTempData.ColorTemp[_RED] = ValueInRangeChange(0, 255,stColorTempData.ColorTemp[_RED], _NON_LOOP | ucMode);
			CFacShowNumber(18,4,stColorTempData.ColorTemp[_RED]); 
			break;
			
		case _MI_FAC_9300_G :
    	    stColorTempData.ColorTemp[_GREEN] = ValueInRangeChange(0, 255,stColorTempData.ColorTemp[_GREEN], _NON_LOOP | ucMode);
			CFacShowNumber(25,4,stColorTempData.ColorTemp[_GREEN]); 
			break;
			
    	case _MI_FAC_9300_B:
    	    stColorTempData.ColorTemp[_BLUE] = ValueInRangeChange(0, 255,stColorTempData.ColorTemp[_BLUE], _NON_LOOP | ucMode);
			CFacShowNumber(31,4,stColorTempData.ColorTemp[_BLUE]); 
			break;
			
    }

	CAdjustContrast();
	ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}

//-----------------------------------------------------------
void MFac9300Proc(void)
{
    switch(ucOsdEventMsg)
    {
        case _OE_ADJ_INC:           MFac9300ValAdj(_INC);                        break;
        case _OE_ADJ_DEC:           MFac9300ValAdj(_DEC);                        break;
        case _OE_MENU_NEXT:         MFac9300MenuAdj(_NEXT);                      break;
        case _OE_MENU_PREV:         MFac9300MenuAdj(_PREV);             		 break;
       // case _OE_ENTER_SUBMENU:     MFactoryEnterSub();  		      			 break;
        case _OE_RETURN_UPMENU:     MFac9300ReturnMenu();          break;

    }
}

//-----------------------------------------------------------
void MFacGainReturnMenu()
{
    OSDLine(ROW(2),COL(16+(ucOsdState-_MI_FAC_GAIN_R)*6),LENGTH(6),_MENU_NORMAL_COLOR,BYTE_COLOR);
    ucOsdState=_MI_FAC_GAIN;
    SETCOLOR_FACMAINMENU_SELLINE(2, _MENU_SELECT_COLOR);
}

//-----------------------------------------------------------
void MFacGainMenuAdj(BYTE ucMode)
{
    BYTE ucNewItem;

    if(ucMode == _INC)
    { 	
    	if(ucOsdState>_MI_FAC_GAIN_R-1 && ucOsdState<_MI_FAC_GAIN_B)
    		ucNewItem=ucOsdState+1;
    	else
    		ucNewItem=_MI_FAC_GAIN;
    }
    else
	{
	    if(ucOsdState>_MI_FAC_GAIN_R && ucOsdState<_MI_FAC_GAIN_B+1)
    		ucNewItem=ucOsdState-1;
    	else
    		ucNewItem=_MI_FAC_GAIN;
	}
    // 1. Clear Current Menu
	OSDLine(ROW(2),COL(16+(ucOsdState-_MI_FAC_GAIN_R)*6),LENGTH(6),_MENU_NORMAL_COLOR,BYTE_COLOR);


    // 2. Change ucOsdState
    ucOsdState = ucNewItem;

    // 3. Draw New Item
    if(ucOsdState>_MI_FAC_GAIN_R-1 && ucOsdState<_MI_FAC_GAIN_B+1)
    	OSDLine(ROW(2),COL(16+(ucOsdState-_MI_FAC_GAIN_R)*6),LENGTH(6),_MENU_SELECT_COLOR,BYTE_COLOR);
    else
    	SETCOLOR_FACMAINMENU_SELLINE(2,_MENU_SELECT_COLOR);
}

//-----------------------------------------------------------
void MFacGainValAdj(BYTE ucMode)
{
	BYTE y;

    SET_KEYREPEATENABLE();
    switch(ucOsdState)
    {
    	case _MI_FAC_GAIN_R :
    	    y= ValueInRangeChange(0, 255,stAdcData.AdcGain[_RED], _NON_LOOP | ucMode);
    		stAdcData.AdcGain[_RED]=y;
			CFacShowNumber(18,2,y); 
			break;
			
		case _MI_FAC_GAIN_G :
    	    y= ValueInRangeChange(0, 255,stAdcData.AdcGain[_GREEN], _NON_LOOP | ucMode);
    		stAdcData.AdcGain[_GREEN]=y;
			CFacShowNumber(25,2,y); 
			break;
			
    	case _MI_FAC_GAIN_B:
    	    y= ValueInRangeChange(0, 255,stAdcData.AdcGain[_BLUE], _NON_LOOP | ucMode);
    		stAdcData.AdcGain[_BLUE]=y;
			CFacShowNumber(31,2,y); 
			break;
    }

	ucOsdEventMsg = _SAVE_EE_ADCDATA_MSG;
	CAdjustAdcGain();
}

//-----------------------------------------------------------
void MFacGainProc(void)
{
    switch(ucOsdEventMsg)
    {
        case _OE_ADJ_INC:          	MFacGainValAdj(_INC);                   break;
        case _OE_ADJ_DEC:           MFacGainValAdj(_DEC);                   break;
        case _OE_MENU_NEXT:         MFacGainMenuAdj(_NEXT);          		break;
        case _OE_MENU_PREV:         MFacGainMenuAdj(_PREV);          		break;
       // case _OE_ENTER_SUBMENU:     MFactoryEnterSub();  		      		break;
        case _OE_RETURN_UPMENU:     MFacGainReturnMenu();          			break;
    }
}

//-----------------------------------------------------------
void MFacOffsetReturnMenu()
{
    OSDLine(ROW(3),COL(16+(ucOsdState-_MI_FAC_OFFSET_R)*6),LENGTH(6),_MENU_NORMAL_COLOR,BYTE_COLOR);
    ucOsdState=_MI_FAC_OFFSET;
    SETCOLOR_FACMAINMENU_SELLINE(3, _MENU_SELECT_COLOR);
}

//-----------------------------------------------------------
void MFacOffsetMenuAdj(BYTE ucMode)
{
    BYTE ucNewItem;

    if(ucMode == _INC)
    { 	
    	if(ucOsdState>_MI_FAC_OFFSET_R-1 && ucOsdState<_MI_FAC_OFFSET_B)
    		ucNewItem=ucOsdState+1;
    	else
    		ucNewItem=_MI_FAC_OFFSET;
    }
    else
	{
	    if(ucOsdState>_MI_FAC_OFFSET_R && ucOsdState<_MI_FAC_OFFSET_B+1)
    		ucNewItem=ucOsdState-1;
    	else
    		ucNewItem=_MI_FAC_OFFSET;
	}
    // 1. Clear Current Menu
	OSDLine(ROW(3),COL(16+(ucOsdState-_MI_FAC_OFFSET_R)*6),LENGTH(6),_MENU_NORMAL_COLOR,BYTE_COLOR);


    // 2. Change ucOsdState
    ucOsdState = ucNewItem;

    // 3. Draw New Item
    if(ucOsdState>_MI_FAC_OFFSET_R-1 && ucOsdState<_MI_FAC_OFFSET_B+1)
    	OSDLine(ROW(3),COL(16+(ucOsdState-_MI_FAC_OFFSET_R)*6),LENGTH(6),_MENU_SELECT_COLOR,BYTE_COLOR);
    else
    	SETCOLOR_FACMAINMENU_SELLINE(3,_MENU_SELECT_COLOR);
}

//-----------------------------------------------------------
void MFacOffsetValAdj(BYTE ucMode)
{
	BYTE y;

    SET_KEYREPEATENABLE();
    switch(ucOsdState)
    {
    	case _MI_FAC_OFFSET_R :
    	    y= ValueInRangeChange(0, 255,stAdcData.AdcOffset[_RED], _NON_LOOP | ucMode);
    		stAdcData.AdcOffset[_RED]=y;
			CFacShowNumber(18,3,y); 
			break;
			
		case _MI_FAC_OFFSET_G :
    	    y= ValueInRangeChange(0, 255,stAdcData.AdcOffset[_GREEN], _NON_LOOP | ucMode);
    		stAdcData.AdcOffset[_GREEN]=y;
			CFacShowNumber(25,3,y); 
			break;
			
    	case _MI_FAC_OFFSET_B:
    	    y= ValueInRangeChange(0, 255,stAdcData.AdcOffset[_BLUE], _NON_LOOP | ucMode);
    		stAdcData.AdcOffset[_BLUE]=y;
			CFacShowNumber(31,3,y); 
			break;
			
    }
	ucOsdEventMsg = _SAVE_EE_ADCDATA_MSG;
	CAdjustAdcOffset();
}

//-----------------------------------------------------------
void MFacOffsetProc(void)
{
    switch(ucOsdEventMsg)
    {
        case _OE_ADJ_INC:           MFacOffsetValAdj(_INC);                    	break;
        case _OE_ADJ_DEC:           MFacOffsetValAdj(_DEC);                     break;
        case _OE_MENU_NEXT:         MFacOffsetMenuAdj(_NEXT);          			break;
        case _OE_MENU_PREV:         MFacOffsetMenuAdj(_PREV);          			break;
       // case _OE_ENTER_SUBMENU:     MFactoryEnterSub();  		       			break;
        case _OE_RETURN_UPMENU:     MFacOffsetReturnMenu();          			break;

    }
}

//-----------------------------------------------------------
void MFac6500ReturnMenu()
{
    OSDLine(ROW(5),COL(16+(ucOsdState-_MI_FAC_6500_R)*6),LENGTH(6),_MENU_NORMAL_COLOR,BYTE_COLOR);
    ucOsdState=_MI_FAC_6500;
    SETCOLOR_FACMAINMENU_SELLINE(5, _MENU_SELECT_COLOR);
}

//-----------------------------------------------------------
void MFac6500MenuAdj(BYTE ucMode)
{
    BYTE ucNewItem;

    if(ucMode==_INC)
    { 	
    	if(ucOsdState>_MI_FAC_6500_R-1 && ucOsdState<_MI_FAC_6500_B)
    		ucNewItem=ucOsdState+1;
    	else
    		ucNewItem=_MI_FAC_6500;
    }
    else
	{
	    if(ucOsdState>_MI_FAC_6500_R && ucOsdState<_MI_FAC_6500_B+1)
    		ucNewItem=ucOsdState-1;
    	else
    		ucNewItem=_MI_FAC_6500;
	}
    // 1. Clear Current Menu
	OSDLine(ROW(5),COL(16+(ucOsdState-_MI_FAC_6500_R)*6),LENGTH(6),_MENU_NORMAL_COLOR,BYTE_COLOR);


    // 2. Change ucOsdState
    ucOsdState = ucNewItem;

    // 3. Draw New Item
    if(ucOsdState>_MI_FAC_6500_R-1 && ucOsdState<_MI_FAC_6500_B+1)
    	OSDLine(ROW(5),COL(16+(ucOsdState-_MI_FAC_6500_R)*6),LENGTH(6),_MENU_SELECT_COLOR,BYTE_COLOR);
    else
    	SETCOLOR_FACMAINMENU_SELLINE(5,_MENU_SELECT_COLOR);

}

//-----------------------------------------------------------
void MFac6500ValAdj(BYTE ucMode)
{
	SET_COLOR_TEMP_TYPE(_CT_6500);
	CEepromLoadColorTempData();
    // ucMode : _INC or _DEC
    SET_KEYREPEATENABLE();
    switch(ucOsdState)
    {
    	case _MI_FAC_6500_R :
    	    stColorTempData.ColorTemp[_RED] = ValueInRangeChange(0, 255,stColorTempData.ColorTemp[_RED], _NON_LOOP | ucMode);
			CFacShowNumber(18,5,stColorTempData.ColorTemp[_RED]);
			break;
			
		case _MI_FAC_6500_G :
    	    stColorTempData.ColorTemp[_GREEN] = ValueInRangeChange(0, 255,stColorTempData.ColorTemp[_GREEN], _NON_LOOP | ucMode);    		
			CFacShowNumber(25,5,stColorTempData.ColorTemp[_GREEN]); 
			break;
			
    	case _MI_FAC_6500_B:
    	    stColorTempData.ColorTemp[_BLUE] = ValueInRangeChange(0, 255,stColorTempData.ColorTemp[_BLUE], _NON_LOOP | ucMode);
			CFacShowNumber(31,5,stColorTempData.ColorTemp[_BLUE]); 
			break;
			
    }
	ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
	CAdjustContrast();
}

//-----------------------------------------------------------
void MFac6500Proc(void)
{
    switch(ucOsdEventMsg)
    {
        case _OE_ADJ_INC:           MFac6500ValAdj(_INC);                        break;
        case _OE_ADJ_DEC:           MFac6500ValAdj(_DEC);                        break;
        case _OE_MENU_NEXT:         MFac6500MenuAdj(_NEXT);                      break;
        case _OE_MENU_PREV:         MFac6500MenuAdj(_PREV);             		 break;
       // case _OE_ENTER_SUBMENU:     MFactoryEnterSub();  		      			 break;
        case _OE_RETURN_UPMENU:     MFac6500ReturnMenu();          break;

    }
}

//-------------------------------------------------------------
void MFacGammaValAdj(BYTE ucMode)
{
    BYTE ucTemp = GET_GAMMA();

    ucTemp = ValueInRangeChange(0, 3, ucTemp, _LOOP | ucMode);

    CAdjustGammaTable(ucTemp);

	SET_GAMMA(ucTemp);
	CEepromSaveSystemData();
  	CFacShowNumber(17, 7, ucTemp);
}
//-------------------------------------------------------------
void MFacBacklightValAdj(BYTE ucMode)
{

    SET_KEYREPEATENABLE();

    stSystemData.BackLight = ValueInRangeChange(0, 100, stSystemData.BackLight, _LOOP | ucMode);

    CAdjustBacklight();
    CEepromSaveSystemData();
    CFacShowNumber(17, 9, stSystemData.BackLight);

}

//-------------------------------------------------------------

void MFacBackcolorValAdj(BYTE ucMode)
{

	// 1 获取背颜色
    BYTE ucBackcolorValue = GET_BACKGROUNDCOLOE();

	// 跟据按钮，改变背影颜色。
	ucBackcolorValue = ValueInRangeChange(_RED, _BLUE, ucBackcolorValue, _LOOP | ucMode);
	SET_BACKGROUNDCOLOE(ucBackcolorValue);

	// 保存到 24c16 中
	CEepromSaveSystemData();

	// 显示到OSD上
	ShowBackColorText();

}



//-------------------------------------------------------------
void MFacGammaReturnMenu(void)
{
    ucOsdState =_MI_GAMMA;
    SETCOLOR_FACMAINMENU_SELLINE(7, _MENU_SELECT_COLOR);
}

//-------------------------------------------------------------
void MFacBacklightReturnMenu(void)
{
    ucOsdState =_MI_FAC_ADJ;
    SETCOLOR_FACMAINMENU_SELLINE(9, _MENU_SELECT_COLOR);
}
//-------------------------------------------------------------
void MFacBackcolorReturnMenu(void)
{
    ucOsdState =_MI_FAC_BACKCOLOR;
    SETCOLOR_FACMAINMENU_SELLINE(10, _MENU_SELECT_COLOR);
}
//-------------------------------------------------------------
void MFacGammaProc(void)
{
    switch(ucOsdEventMsg)
    {
        case _OE_ADJ_INC:           MFacGammaValAdj(_INC);          break;
        case _OE_ADJ_DEC:           MFacGammaValAdj(_DEC);          break;
        case _OE_MENU_NEXT:         MFacGammaReturnMenu();          break;
    }
}
//-------------------------------------------------------------
void MFacBacklightProc(void)
{
    switch(ucOsdEventMsg)
    {
        case _OE_ADJ_INC:           MFacBacklightValAdj(_DEC);          break;
        case _OE_ADJ_DEC:           MFacBacklightValAdj(_INC);          break;
        case _OE_MENU_NEXT:         MFacBacklightReturnMenu();          break;
    }
}
//-------------------------------------------------------------
void MFacBackColorProc(void)
{
	
    switch(ucOsdEventMsg)
    {
        case _OE_ADJ_INC:           MFacBackcolorValAdj(_DEC);          break;
        case _OE_ADJ_DEC:           MFacBackcolorValAdj(_INC);          break;
        case _OE_MENU_NEXT:         MFacBackcolorReturnMenu();          break;
    }
}

#endif



