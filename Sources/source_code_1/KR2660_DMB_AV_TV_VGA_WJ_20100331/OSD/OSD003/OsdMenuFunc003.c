

#define __OSDDRAW003__


#include "Core\Header\Include.h"

BYTE code tOSDMenuFunc;
void DrawMenuSelect(BYTE Item,BYTE ucState);

#if(_OSD_TYPE == _OSD003)
//---------------------------------------------------------------------------
bit CEnable(void)
{
    return 1;
}

//---------------------------------------------------------------------------
bit CDisable(void)
{
    return 0;
}

//---------------------------------------------------------------------------
bit CPanelLRUD(void)
{
    return _PANEL_LR_UD_FUNC;
}

//---------------------------------------------------------------------------


bit CVideoEnable(void)
{
    if(bSourceVideo() || _SOURCE_YPBPR == _GET_INPUT_SOURCE()||_SOURCE_YPBPR1 == _GET_INPUT_SOURCE())
        return 1;
    else return 0;
}
                                     
//---------------------------------------------------------------------------
bit CVideoNTSCEnable(void)
{
    if((bSourceVideo() && ucVideoType < ZPAL_N) || (_SOURCE_YPBPR == _GET_INPUT_SOURCE())||(_SOURCE_YPBPR1 == _GET_INPUT_SOURCE()))
        return 1;
    else return 0;
}

//---------------------------------------------------------------------------
bit CVgaEnable(void)
{
    if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
        return 1;
    else return 0;
}

//---------------------------------------------------------------------------

bit MDisplayRatioEnable(void)
{
    if(CCalcRatio() >= 75)      // 屏的比例 4:3 或 16:9
        return _FAIL;
    
    return _TRUE;
}

//---------------------------------------------------------------------------
bit CTVEnable(void)
{
    if(stSystemData.InputSource == _SOURCE_VIDEO_TV)
        return 1;
    else
		return 0;
}
//---------------------------------------------------------------------------

void OSDSlider(unsigned char row, unsigned char col, unsigned char length, unsigned char value, unsigned char range,
                unsigned char color)
{
    unsigned int bound;
    unsigned char i,c;
    OSDLine(row, col, length + 8, color, THE_BYTE2);   // Set Slider Attribute. 4 extra columns for space/numbers/space
    bound   = length * value;
    Gotoxy(col,row,THE_BYTE1);
    OutputChar(0x2d);
    OutputChar(0x21);          // Left Border
    for (i = 1; i <= length; i++)
    {
        if (bound)
        {
            if(bound >= range)
            {
                c       = 0x28;
                bound   = bound - range;
            }
            else
            {
                color   = (bound << 4) / range;
                bound   = 0;
                if (4 > color)                    c = 0x23;
                else if (7 > color)               c = 0x24;
                else if (10 > color)              c = 0x25;
                else if (13 > color)              c = 0x26;
                else                              c = 0x27;
            }
        }
        else
        {
            c = 0x22;
        }
        OutputChar(c);
    }
    OutputChar(0x29);    // Right Border
    PrintfDec(value);    //值显示在右边
    OutputChar(0x2a);
    if (value < 100)
    OutputChar(0x00);

}
//---------------------------------------------------------------------------

void DrawMainMenu(void)
{
    InitOsdFrame();

    SetOSDDouble(0);
    CCloseAllWindows();

    OSDLine(ROW(0), COL(0),	COL_WIDTH,	0xf0,	BYTE_COLOR);    
    COsdFxDrawWindow(XSTART(0), YSTART(0), _MAINMENU_WITDH, _MAINMENU_HEIGHT, tMainWindowStyle);

    OSDPosition(_MAINMENU_WITDH,_MAINMENU_HEIGHT,50,90,0x01);
    
}
//---------------------------------------------------------------------------
void DrawContrast(void)
{
    OSD_TITLE_OUT(sContrast[GET_LANGUAGE()]);
    OSD_SLIDER(stConBriData.Contrast);
}
//---------------------------------------------------------------------------
void DrawBrightness(void)
{
    OSD_TITLE_OUT(sBrightness[GET_LANGUAGE()]);
    OSD_SLIDER(stConBriData.Brightness);
}
//---------------------------------------------------------------------------
void DrawHue(void)
{
    OSD_TITLE_OUT(sHue[GET_LANGUAGE()]);
    OSD_SLIDER(GET_HUE());

}
//---------------------------------------------------------------------------
void DrawSaturation(void)
{
    OSD_TITLE_OUT(sSaturation[GET_LANGUAGE()]);
    OSD_SLIDER(GET_SATURATION());

}
//---------------------------------------------------------------------------
void DrawSystem(void)
{
    OSD_TITLE_OUT(sTvSystem[GET_LANGUAGE()]);
	CCenterTextout((BYTE*)sTVType[ucTVType], 9, 1);
}
//---------------------------------------------------------------------------
void DrawAutoSearch(void)
{
    OSD_TITLE_OUT(sAutoSearch[GET_LANGUAGE()]);

}
//---------------------------------------------------------------------------
void DrawManualSearch(void)
{
    WORD iFreq = _GET_CH_FREQ();
    OSD_TITLE_OUT(sManualSearch[GET_LANGUAGE()]);
    Gotoxy(3, 1, BYTE_DISPLAY);
    CShowNumber1(stTvInfo.CurChn, 1);
    CShowFreq(iFreq);
}
//---------------------------------------------------------------------------
void DrawTuning(void)
{
    WORD iFreq = _GET_CH_FREQ();
    OSD_TITLE_OUT(sTuning[GET_LANGUAGE()]);
    Gotoxy(3, 1, BYTE_DISPLAY);
    CShowNumber1(stTvInfo.CurChn, 1);
    CShowFreq(iFreq);
}
//---------------------------------------------------------------------------
void DrawChannel(void)
{
    OSD_TITLE_OUT(sChannel[GET_LANGUAGE()]);
	Gotoxy(8, 1, BYTE_DISPLAY);
    CShowNumber1(stTvInfo.CurChn, 1);
}
//---------------------------------------------------------------------------
void DrawVolume(void)
{
    OSD_TITLE_OUT(sVolume[GET_LANGUAGE()]);
    OSD_SLIDER(GET_VOLUME());
}
//---------------------------------------------------------------------------
void DrawLanguage(void)
{
    OSD_TITLE_OUT(sLangName[GET_LANGUAGE()]);
//	CCenterTextout(sLanguage[GET_LANGUAGE()], 14, 2);

    Gotoxy(COL(7), ROW(2), BYTE_DISPLAY);
    Textout(sLanguage[0]);

    Gotoxy(COL(17), ROW(2), BYTE_DISPLAY);
    Textout(sLanguage[1]);

   	if(GET_LANGUAGE())
	    Gotoxy(16, 2, BYTE_DISPLAY);
	else
	    Gotoxy(6, 2, BYTE_DISPLAY);
	OutputChar(_SEL_SELECT);

}
//------------------------------------------------------------------------------
void DrawAtuoAdjustMenu(void)
{

    OSD_TITLE_OUT(sAutoADJName[GET_LANGUAGE()]);
	CCenterTextout(sYes[GET_LANGUAGE()], 15, 2);

		Gotoxy(13,2,BYTE_DISPLAY);
		OutputChar(0x3B);
}

void DrawFMMenu(void)
{
    BYTE *pStr;
	OSDClear(2, 1, 4 , 20, 0x00, BYTE_DISPLAY);
	OSD_TITLE_OUT(sFm[GET_LANGUAGE()]);
	switch(_GET_FM_STATE())
	{
		case _FM_OFF:		pStr = sFM_OFF;			break;
		case _FM_A1:			pStr = sFM_A1;			break;		
		case _FM_A2:			pStr = sFM_A2;			break;
		case _FM_A3:			pStr = sFM_A3;			break;
		case _FM_A4:			pStr = sFM_A4;			break;		
		case _FM_A5:			pStr = sFM_A5;			break;		
		case _FM_A6:			pStr = sFM_A6;			break;		
		case _FM_A7:			pStr = sFM_A7;			break;		
		case _FM_A8:			pStr = sFM_A8;			break;
		case _FM_B1:			pStr = sFM_B1;			break;
		case _FM_B2:			pStr = sFM_B2;			break;
		case _FM_B3:			pStr = sFM_B3;			break;
		case _FM_B4:			pStr = sFM_B4;			break;
		case _FM_B5:			pStr = sFM_B5;			break;
		case _FM_B6:			pStr = sFM_B6;			break;
		case _FM_B7:			pStr = sFM_B7;			break;
		case _FM_B8:			pStr = sFM_B8;			break;
		default:
								pStr = sFM_OFF;			break;

	}

	//CCenterTextout(pStr,ROW(2),0,27);
	if(_GET_FM_STATE() == _FM_OFF) //wtao100413
              CCenterTextout(pStr, 13, 2);
	else
		CCenterTextout(pStr, 10, 2);
	if(_GET_FM_STATE() != _FM_OFF)
	CCenterTextout(sMhz, 17, 2);
	
	    Gotoxy(20, 2, BYTE_DISPLAY);
	    OutputChar(_SEL_SELECT);
       
}
//---------------------------------------------------------------------------
//BYTE ucState : _SEL_CLEAR,_SEL_SELECT
void DrawMenuSelect(BYTE Item,BYTE ucState)
{
	BYTE x;

	if(Item == 0)
	{
		x = 7;
	}
	else 
	{
		x = 17;
	}

	Gotoxy(x, 2, BYTE_DISPLAY);
	OutputChar(ucState);
	
}
/*/---------------------------------------------------------------------------
void MenuSourceSlect(BYTE ucState)
{
	BYTE ucSelectItem;

    if(_GET_INPUT_SOURCE() == _SOURCE_VIDEO_AV)
    {
		ucSelectItem = 0;	
    }
    else
    {
		ucSelectItem = 1;
    }

    DrawMenuSelect(ucSelectItem,ucState);
}
*///---------------------------------------------------------------------------
void DrawSource(void)
{
	
    OSD_TITLE_OUT(sSource);
	//MenuSourceSlect(_SEL_SELECT);
    ucSourceTemp = stSystemData.InputSource;
	    Gotoxy(COL(4), ROW(2), BYTE_DISPLAY);
    		Textout(sAV1);
	    Gotoxy(COL(10), ROW(2), BYTE_DISPLAY);	
    		Textout(sAV2);
	    Gotoxy(COL(16), ROW(2), BYTE_DISPLAY);	
    		Textout(sTV);
	    Gotoxy(COL(22), ROW(2), BYTE_DISPLAY);	
    		Textout(sVGA);	
    if(stSystemData.InputSource == _SOURCE_VIDEO_AV)
	{
		Gotoxy(3,2,BYTE_DISPLAY);
		OutputChar(0x3B);
	}
    else if(stSystemData.InputSource == _SOURCE_VIDEO_SV)
    {
		Gotoxy(9,2,BYTE_DISPLAY);
        OutputChar(0x3B);
    }
	else if(stSystemData.InputSource == _SOURCE_VIDEO_TV)
	{
		Gotoxy(15,2,BYTE_DISPLAY);
        OutputChar(0x3B);
	}
	else if(stSystemData.InputSource == _SOURCE_VGA)
	{
		Gotoxy(21,2,BYTE_DISPLAY);
        OutputChar(0x3B);
	}
}
//---------------------------------------------------------------------------
void MenuLRSwapSlect(BYTE ucState)
{
	BYTE ucSelectItem;

    if(GET_LR_SWAP())
    {
		ucSelectItem = 0;	
    }
    else
    {
		ucSelectItem = 1;
    }

    DrawMenuSelect(ucSelectItem,ucState);
}
//---------------------------------------------------------------------------

void DrawLRSwap(void)
{	
    OSD_TITLE_OUT(sLR);

    Gotoxy(COL(6), ROW(2), BYTE_DISPLAY);
    OutputChar('L');

    Gotoxy(COL(16), ROW(2), BYTE_DISPLAY);
    OutputChar('R');

    MenuLRSwapSlect(_SEL_SELECT);
}
//---------------------------------------------------------------------------
void MenuUDSwapSlect(BYTE ucState)
{
	BYTE ucSelectItem;

    if(GET_UD_SWAP())
    {
		ucSelectItem = 0;	
    }
    else
    {
		ucSelectItem = 1;
    }

    DrawMenuSelect(ucSelectItem,ucState);
}
//---------------------------------------------------------------------------

void DrawUDSwap(void)
{	
    OSD_TITLE_OUT(sUD);

    Gotoxy(COL(6), ROW(2), BYTE_DISPLAY);
    OutputChar('U');

    Gotoxy(COL(16), ROW(2), BYTE_DISPLAY);
    OutputChar('D');

    MenuUDSwapSlect(_SEL_SELECT);
}
//---------------------------------------------------------------------------
void MenuDisaplayRatioSlect(BYTE ucState)
{
	BYTE ucSelectItem;

    if(GET_DISPLAYMODE() == _DISPMODE_FULL)
    {
		ucSelectItem = 0;	
    }
    else
    {
		ucSelectItem = 1;
    }

    DrawMenuSelect(ucSelectItem,ucState);
}
//---------------------------------------------------------------------------
void DrawDisplayRatio(void)
{
    OSD_TITLE_OUT(sDisplayRatio);

    Gotoxy(COL(8), ROW(2), BYTE_DISPLAY);
    Textout(s16_9);

    Gotoxy(COL(18), ROW(2), BYTE_DISPLAY);
    Textout(s4_3);

    MenuDisaplayRatioSlect(_SEL_SELECT);
}
//---------------------------------------------------------------------------

void DrawReset(void)
{
    OSD_TITLE_OUT(sReset[GET_LANGUAGE()]);

    Gotoxy(COL(8), ROW(2), BYTE_DISPLAY);
    Textout(sNo[GET_LANGUAGE()]);

    Gotoxy(COL(18), ROW(2), BYTE_DISPLAY);
    Textout(sYes[GET_LANGUAGE()]);

   	DrawMenuSelect(0,_SEL_SELECT);
}
//---------------------------------------------------------------------------
/*
void DrawExit(void)
{
	OSD_TITLE_OUT(sExit);
}
*/
//---------------------------------------------------------------------------

void MAdjustContrast(BYTE ucMode)
{
    // ucMode : _INC or _DEC
    SET_KEYREPEATENABLE();
    stConBriData.Contrast = ValueInRangeChange(0, 100, stConBriData.Contrast, _NON_LOOP | ucMode);
    CAdjustContrast();
    ucOsdEventMsg = _SAVE_EE_COLORPROC0_MSG;
	OSD_SLIDER(stConBriData.Contrast);	
}
//---------------------------------------------------------------------------
void MAdjustBrightness(BYTE ucMode)
{
    // ucMode : _INC or _DEC
    SET_KEYREPEATENABLE();
    stConBriData.Brightness = ValueInRangeChange(0, 100, stConBriData.Brightness, _NON_LOOP | ucMode);
    CAdjustBrightness();
    ucOsdEventMsg = _SAVE_EE_COLORPROC0_MSG;
    OSD_SLIDER(stConBriData.Brightness);
}
//---------------------------------------------------------------------------
void MAdjustHue(BYTE ucMode)
{
    SET_KEYREPEATENABLE();
    stHueSatData.Hue = ValueInRangeChange(0, 100, stHueSatData.Hue, _NON_LOOP | ucMode);

    if(bSourceVideo())
    {
        kx_CAdjustVDCHue(GET_HUE());
    }
    else
    {
        CAdjustYpbprhue(GET_HUE());
    }
    ucOsdEventMsg = _SAVE_EE_HUE_SAT_DATA_MSG;   

    OSD_SLIDER(GET_HUE());

}
//---------------------------------------------------------------------------
void MAdjustSaturation(BYTE ucMode)
{
    // ucMode : _INC or _DEC
    SET_KEYREPEATENABLE();
    stHueSatData.Saturation = ValueInRangeChange(0, 100, stHueSatData.Saturation, _NON_LOOP | ucMode);

    if(bSourceVideo())
    {
        CVideoSetSaturation(GET_SATURATION());
    }
    else
    {
        CAdjustYpbprSaturation(GET_SATURATION());
    }

    ucOsdEventMsg = _SAVE_EE_HUE_SAT_DATA_MSG;
    OSD_SLIDER(GET_SATURATION());
}

//---------------------------------------------------------------------------
unsigned char NextTVSystem(unsigned char LR)
{
	if(ucTVType == 0)
		return _NORMAL_TV_TYPE;
	if(LR)
	{
		switch(ucTVType)
		{
			case _TV_PAL_I:			ucTVType = _TV_PAL_DK;			break;
			case _TV_PAL_DK:        ucTVType = _TV_PAL_BG;			break;
			case _TV_PAL_BG:        ucTVType = _TV_SECAM_DK;		break;
			case _TV_SECAM_DK:      ucTVType = _TV_SECAM_BG;		break;
			case _TV_SECAM_BG:      ucTVType = _TV_NTSC_M;			break;
			case _TV_NTSC_M:        ucTVType = _TV_PAL_N;			break;
			case _TV_PAL_N:         ucTVType = _TV_PAL_M;			break;
			case _TV_PAL_M:         ucTVType = _TV_PAL_I;			break;
		}
	}
	else
	{
		switch(ucTVType)
		{				
			case _TV_PAL_I:			ucTVType = _TV_PAL_M;			break;
			case _TV_PAL_DK:        ucTVType = _TV_PAL_I;			break;
			case _TV_PAL_BG:        ucTVType = _TV_PAL_DK;			break;
			case _TV_SECAM_DK:      ucTVType = _TV_PAL_BG;			break;
			case _TV_SECAM_BG:      ucTVType = _TV_SECAM_DK;		break;
			case _TV_NTSC_M:        ucTVType = _TV_SECAM_BG;		break;
			case _TV_PAL_N:         ucTVType = _TV_NTSC_M;			break;
			case _TV_PAL_M:         ucTVType = _TV_PAL_N;			break;
		}
	}
	return ucTVType;
}

//---------------------------------------------------------------------------
void MAdjustSystem(BYTE LR)
{
    ucTVType = NextTVSystem(LR);
    kx_CI2CWriteIfPllDM(ucTVType,_TUNER_MUTE_ON,_NORMAL_MODE);
	OSDClear(1, 1, 1, 20, 0x00, BYTE_DISPLAY);
	DrawSystem();
    CSetTvColor(ucTVType);

    _SET_CH_COLOR_TYPE(ucTVType);
    CSaveTVModeData(stTvInfo.CurChn);
    ucTVSyncFailCount = 251;

}
//---------------------------------------------------------------------------
void MAdjustAutoSearch(BYTE ucMode)
{
	ucMode = ucMode;
	CTvAutoSearch();
}
//---------------------------------------------------------------------------
void MAdjustManualSearch(BYTE ucMode)
{
    CManualSearch(ucMode, stTvInfo.CurChn);
}
//---------------------------------------------------------------------------
void MAdjustTuning(BYTE ucMode)
{
	WORD iFreq;
    SET_KEYREPEATENABLE();
	CTuningCurrentChannel(ucMode, stTvInfo.CurChn);
	iFreq = _GET_CH_FREQ();
    CShowFreq(iFreq);
}
//---------------------------------------------------------------------------
void MAdjustChannel(BYTE ucMode)
{
    stTvInfo.CurChn = ValueInRangeChange(0, stTvInfo.ucMaxChannel, stTvInfo.CurChn, _LOOP | ucMode);
    CSetTVChannel(stTvInfo.CurChn);
    ucPrevChannel =  stTvInfo.CurChn;
    Gotoxy(8, 1, BYTE_DISPLAY);
    CShowNumber1(stTvInfo.CurChn, 1);
    CMuteOn();
    CModeResetTVMode();

    ucOsdEventMsg  = _SAVE_EE_TV_DATA_MSG;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void MAdjustVolume(BYTE ucMode)
{
    SET_KEYREPEATENABLE();
    stAudioData.Volume = ValueInRangeChange(0, 100, stAudioData.Volume, _NON_LOOP | ucMode);
    CLR_AUDIO_MUTE();
    CAdjustAudio();
    CSetVolume();

    ucOsdEventMsg = _SAVE_EE_AUDIO_DATA_MSG;
    OSD_SLIDER(GET_VOLUME());
}
//---------------------------------------------------------------------------
void AutoAdjustLeftRight(BYTE LR)
{
     LR = LR;
	 			if(stSystemData.InputSource == _SOURCE_VGA)
			{
				CAutoDoAutoConfig();
				CAutoDoWhiteBalance();
			}
}
///////--------------------------------------------------
void MAdjustLanguage(BYTE ucMode)
{
    BYTE ucLang = GET_LANGUAGE();

    OSDClear(0,2,0,20,0x00,BYTE_DISPLAY);
	
    if (!ucMode) //中文-> English
    	{
          ucLang = 0;//GetNextLanguage(ucLang);
	    Gotoxy(16, 2, BYTE_DISPLAY);
	    OutputChar(_SEL_CLEAR);
	    Gotoxy(6, 2, BYTE_DISPLAY);
	    OutputChar(_SEL_SELECT);
	   SET_LANGUAGE(0);
	   CCenterTextout(sLangName[0],  COL(14), ROW(0));//9, 0);//wtao100413
    	}
    else   //English ->中文
    	{
          ucLang = 1;//GetPrevLanguage(ucLang);
	    Gotoxy(6, 2, BYTE_DISPLAY);
	    OutputChar(_SEL_CLEAR);
	    Gotoxy(16, 2, BYTE_DISPLAY);
	    OutputChar(_SEL_SELECT);
	   SET_LANGUAGE(1);
	   CCenterTextout(sLangName[1],  COL(14), ROW(0));//9, 0);//wtao100413
    	}
	
    
	//OSDClear(0, 2, 1, 30, 0x00, BYTE_DISPLAY);
	//OSD_CLEAR_MENU();

    //
   // CCenterTextout(sLanguage[GET_LANGUAGE()], 14, 2);
		
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void MAdjustSource(BYTE ucMode)
{
    if(ucSourceTemp == _SOURCE_VIDEO_AV)
	{
        OSDClear(2, 1, 3 , 1, 0x00, BYTE_DISPLAY);
	}
	    else if(ucSourceTemp == _SOURCE_VIDEO_SV)
    {
        OSDClear(2, 1, 9 , 1, 0x00, BYTE_DISPLAY);
    }
	else if(ucSourceTemp == _SOURCE_VIDEO_TV)
	{
        OSDClear(2, 1, 15 , 1, 0x00, BYTE_DISPLAY);
	}
	else if(ucSourceTemp == _SOURCE_VGA)
	{
        OSDClear(2, 1, 21 , 1, 0x00, BYTE_DISPLAY);
	}
	
    if (ucMode)
    {
    	if(ucSourceTemp == _SOURCE_VIDEO_AV)
			ucSourceTemp = _SOURCE_VIDEO_SV;					
	else if(ucSourceTemp == _SOURCE_VIDEO_SV)			
    		ucSourceTemp = _SOURCE_VIDEO_TV;
    else if(ucSourceTemp == _SOURCE_VIDEO_TV)
    		ucSourceTemp = _SOURCE_VGA;	
	else if(ucSourceTemp == _SOURCE_VGA)
    		ucSourceTemp = _SOURCE_VIDEO_AV;
    	else
    		return;
    }
    else
    {
    	if(ucSourceTemp == _SOURCE_VIDEO_AV)
			ucSourceTemp = _SOURCE_VGA;  
	else if(ucSourceTemp == _SOURCE_VGA)	
    		ucSourceTemp = _SOURCE_VIDEO_TV;
    else if(ucSourceTemp == _SOURCE_VIDEO_TV)		
			ucSourceTemp = _SOURCE_VIDEO_SV;   
	else if(ucSourceTemp == _SOURCE_VIDEO_SV)		
    		ucSourceTemp = _SOURCE_VIDEO_AV;
    	else
    		return;
    }

    if(ucSourceTemp == _SOURCE_VIDEO_AV)
	{
		Gotoxy(3,2,BYTE_DISPLAY);
		OutputChar(0x3B);
	}
	else if(ucSourceTemp == _SOURCE_VIDEO_SV)  //mp5 cvbs
    {
		Gotoxy(9,2,BYTE_DISPLAY);
        OutputChar(0x3B);
    }
	else if(ucSourceTemp == _SOURCE_VIDEO_TV)
	{
		Gotoxy(15,2,BYTE_DISPLAY);
        OutputChar(0x3B);
	}
	else if(ucSourceTemp == _SOURCE_VGA)
	{
		Gotoxy(21,2,BYTE_DISPLAY);
        OutputChar(0x3B);
	}
}
//---------------------------------------------------------------------------
void MAdjustFM(BYTE LR)
{
	BYTE item ;
	item = _GET_FM_STATE();
	item = ValueInRangeChange(_FM_OFF,_FM_B8,item,_LOOP | LR);//SHANG//FM OFF//NON
	//item = ValueInRangeChange(_FM_OFF,_FM_B8,item,_NON_LOOP | LR);
	_SET_FM_STATE(item);
	CFMControl();
	DrawFMMenu();
}

//------------------------------------------------------------------------------

void MAdjustLRSwap(BYTE ucMode)
{
	ucMode = ucMode;

	MenuLRSwapSlect(_SEL_CLEAR);

	PanelLRSwap();
	
	MenuLRSwapSlect(_SEL_SELECT);
}
//---------------------------------------------------------------------------


void MAdjustUDSwap(BYTE ucMode)
{
	ucMode = ucMode;
	MenuUDSwapSlect(_SEL_CLEAR);
	PanelUDSwap();
	MenuUDSwapSlect(_SEL_SELECT);
}
//---------------------------------------------------------------------------
void MAdjustDisplayRatio(BYTE ucMode)
{
	ucMode = ucMode;
	MenuDisaplayRatioSlect(_SEL_CLEAR);
	
	ChangeDisplayMode();	
}
//---------------------------------------------------------------------------
void MAdjustReset(BYTE ucMode)
{
	ucMode = ucMode;
	
	DrawMenuSelect(m_fResetMenuState,_SEL_CLEAR);

	m_fResetMenuState = ~m_fResetMenuState;
	
	DrawMenuSelect(m_fResetMenuState,_SEL_SELECT);

}
//---------------------------------------------------------------------------

void MReset(void)
{
	OSDLine(ROW(2), COL(0), COL_WIDTH, 0x00, BYTE_DISPLAY);
	CCenterTextout(sReseting, COL(14), ROW(2));
	CDoReset();
    CLR_KEYREPEATENABLE();
    COsdFxDisableOsd();
    ucOsdState = _MI_MENU_NONE;
}
//---------------------------------------------------------------------------





// Func
//---------------------------------------------------------------------------
void MMenuNoneProc(void)
{
    switch(ucOsdEventMsg)
    {
    case _OE_ENTER_SUBMENU:     
		MMenuNoneEnterSubMenu();        
		ucSourceTemp = stSystemData.InputSource;
		break;
    
    case _OE_SC_CH_INC:
    case _OE_SC_CH_DEC:
    	if (_GET_INPUT_SOURCE() != _SOURCE_VIDEO_TV)
            return;
        CChangeChannel((ucOsdEventMsg == _OE_SC_CH_DEC) ? 0 : 1);
        COsdDispOsdTimerEvent();
        bDrawMute = 0;
        break;

#if(_VGA_SUPPORT)
    case _OE_INPUT_VGA:
        if (_GET_INPUT_SOURCE() != _SOURCE_VGA)
        {
            _SET_INPUT_SOURCE(_SOURCE_VGA);
            ChangeSourceReset();
        } 
        break;
#endif

#if(_TMDS_SUPPORT)
    case _OE_INPUT_DVI:
        if (_GET_INPUT_SOURCE() != _SOURCE_DVI)
        {
            _SET_INPUT_SOURCE(_SOURCE_DVI);
            ChangeSourceReset();
        } 
        break;
#endif

#if(_VIDEO_SV_SUPPORT)
    case _OE_INPUT_S_VIDEO:
        if (_GET_INPUT_SOURCE() != _SOURCE_VIDEO_SV)
        {
            _SET_INPUT_SOURCE(_SOURCE_VIDEO_SV);
            ChangeSourceReset();
        } 
        break;
#endif

#if(_VIDEO_AV_SUPPORT)
    case _OE_INPUT_AV:
        if (_GET_INPUT_SOURCE() != _SOURCE_VIDEO_AV)
        {
            _SET_INPUT_SOURCE(_SOURCE_VIDEO_AV);
            ChangeSourceReset();
        } 
        break;
#endif

#if(_VIDEO_TV_SUPPORT)
    case _OE_INPUT_TV:
        if (_GET_INPUT_SOURCE() != _SOURCE_VIDEO_TV)
        {
            _SET_INPUT_SOURCE(_SOURCE_VIDEO_TV);
            ChangeSourceReset();
        } 
        break;
#endif

#if(_YPBPR_SUPPORT)
    case _OE_INPUT_YPBPR:
        if (_GET_INPUT_SOURCE() != _SOURCE_YPBPR)
        {
            _SET_INPUT_SOURCE(_SOURCE_YPBPR);
            ChangeSourceReset();
        } 
        break;
    case _OE_INPUT_YPBPR1:
        if (_GET_INPUT_SOURCE() != _SOURCE_YPBPR1)
        {
            _SET_INPUT_SOURCE(_SOURCE_YPBPR1);
            ChangeSourceReset();
        } 
        break;


#endif
	case _OE_CHG_DISPLAY_MODE:				ChangeDisplayMode();			break;
	case _OE_PANEL_LR_SWAP:					PanelLRSwap();					break;
	case _OE_PANEL_UD_SWAP:				PanelUDSwap();					break;
	case _OE_GOTO_MENU_CONTRAST:			GotoContrastMenu();				break;
	case _OE_GOTO_MENU_SATURATION:		GotoSaturationMenu();			break;
	case _OE_GOTO_MENU_BRIGHTNESS:		GotoBrightnessMenu();			break;
	case _OE_SC_TIMER_CHANGE:				SetSleepTimer();				       break;
       

       case _OE_SC_INPUT_NUM0:
       case _OE_SC_INPUT_NUM1:
       case _OE_SC_INPUT_NUM2:
       case _OE_SC_INPUT_NUM3:
       case _OE_SC_INPUT_NUM4:
       case _OE_SC_INPUT_NUM5:
       case _OE_SC_INPUT_NUM6:
       case _OE_SC_INPUT_NUM7:
       case _OE_SC_INPUT_NUM8:
       case _OE_SC_INPUT_NUM9:
       case _OE_SC_INPUT_CHANGE_CH:
                                                                             EnterSCInputNum();
                                                                             MScInputChNumProc();
        break;
        
       case _OE_SC_INPUT_CH:       			       EnterSCInputNum();              break;
       
       case _OE_SC_RETURN:
       	COsdDispOsdTimerEvent();
	       pData[0]        = stTvInfo.CurChn;
              stTvInfo.CurChn = ucPrevChannel;
              ucPrevChannel   = pData[0];
        
              CMuteOn();
              CModeResetTVMode();
              CTimerDelayXms(200);
              CSetTVChannel(stTvInfo.CurChn);
              ucOsdEventMsg = _SAVE_EE_TV_DATA_MSG;
        break;

      case _OE_SC_AUTO_SEARCH:
       	DrawMainMenu();
       	DrawAutoSearch();
       	COsdFxEnableOsd();	    
    	       CTvAutoSearch();
    	break;
		
	case _OE_SC_MUTE:          
		CSetMuteState();                
	break;
	
	default: break;	
    }
}
//---------------------------------------------------------------------------
#define _TEST_ADCKEY				0            

void MMenuNoneEnterSubMenu(void)
{
    // Draw osd
    // Insert code to here
	DrawMainMenu();    
	DrawContrast();
	
    ucOsdState = _MI_CONTRAST;
    
    COsdFxEnableOsd();

    #if(_TEST_ADCKEY)
	{
		BYTE ucValue;
		while(1)
		{
			ucValue = CGetADCAValue(AD_KEY);
			Gotoxy(1,1,BYTE_DISPLAY);
			PrintfDec(ucValue);
	    }
    }
    #endif

}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// MainMenu\CONTRAST,BRIGHTNESS,HUE,SATURATION,SOURCE,LR_SWAP,UD_SWAP,DISPLAY_RATIO,RESET,EXIT,
// MainMenu\_MI_CONTRAST,_MI_BRIGHTNESS,_MI_HUE,_MI_SATURATION,_MI_SOURCE,_MI_LR_SWAP,_MI_UD_SWAP,_MI_DISPLAY_RATIO,_MI_RESET,_MI_EXIT,
void MMainMenuProc(void)
{
    switch(ucOsdEventMsg)
    {
        case _OE_ADJ_INC:           
			MMainMenuValueAdj(_INC);            
			break;
        case _OE_ADJ_DEC:           
			MMainMenuValueAdj(_DEC);            
			break;
        case _OE_MENU_NEXT:         
             	       if (ucOsdState == _MI_SOURCE)
                         {
                             if (ucSourceTemp != stSystemData.InputSource)
                             {
                                 stSystemData.InputSource = ucSourceTemp;
                             
                             	COsdDispOsdTimerEvent();              
                                 ucOsdEventMsg = _CHANGE_SOURCE_MSG;
                                 COsdFxDisableOsd();
                                 return;
                             }
                         }
		       MMainMenuMenuAdj(_NEXT);           
		       break;
        case _OE_MENU_PREV:         
			MMainMenuMenuAdj(_PREV);           
			break;
        case _OE_ENTER_SUBMENU:     
			//MMainMenuEnterSubMenu();            //no process
			break;
        case _OE_RETURN_UPMENU:     
			MMainMenuReturnUpMenu();            
			break;
	default: break;		
    }
}
//---------------------------------------------------------------------------
void MMainMenuValueAdj(BYTE ucMode)
{
    // ucMode : _INC or _DEC

    switch(ucOsdState)
    {
        case _MI_CONTRAST:             MAdjustContrast(ucMode);       	    break;
        case _MI_BRIGHTNESS:          MAdjustBrightness(ucMode);         break;
        case _MI_HUE:                       MAdjustHue(ucMode);                    break;
        case _MI_SATURATION:          MAdjustSaturation(ucMode);         break;
        case _MI_SYSTEM:                  MAdjustSystem(ucMode);		    break;
        case _MI_AUTOSEARCH:         MAdjustAutoSearch(ucMode);        break;        
        case _MI_MANUALSEARCH:     MAdjustManualSearch(ucMode);    break;
        case _MI_TUNING:                  MAdjustTuning(ucMode);               break;
        case _MI_CHANNEL:                MAdjustChannel(ucMode);             break;
        case _MI_VOLUME:                  MAdjustVolume(ucMode);             break;
        case _MI_ATUOADJ:                AutoAdjustLeftRight(ucMode);      break;
        case _MI_LANGUAGE:              MAdjustLanguage(ucMode);         break;        
        case _MI_SOURCE:                 MAdjustSource(ucMode);              break;
	 case _MI_FM_SEND:	            MAdjustFM(ucMode);			   break;
        case _MI_LR_SWAP:                MAdjustLRSwap(ucMode);            break;
        case _MI_UD_SWAP:               MAdjustUDSwap(ucMode);            break;
        case _MI_DISPLAY_RATIO:      MAdjustDisplayRatio(ucMode);     break;
        case _MI_RESET:                    MAdjustReset(ucMode);                break;
	default: break;		
    }   
}
//---------------------------------------------------------------------------
void MMainMenuMenuAdj(BYTE ucMode)
{
    // ucMode : _NEXT or _Prev
    BYTE ucNewItem = AdjustMenuItem(_MI_CONTRAST,_MI_EXIT,ucMode);
    if(ucNewItem == ucOsdState)
        return;

	if(ucOsdState == _MI_RESET)
	{        
		if(m_fResetMenuState == 1)
		{
			MReset();
		}
	}
    // 1. Clear Current Menu
    // Insert code to here
	OSD_CLEAR_MENU();

	
    // 2. Change ucOsdState
    ucOsdState = ucNewItem;

    // 3. Draw New Item
    // Insert code to here
    switch(ucOsdState)
    {
        case _MI_CONTRAST:            	DrawContrast();				break;
        case _MI_BRIGHTNESS:            DrawBrightness();                 	break;
        case _MI_HUE:                         DrawHue();                         	break;
        case _MI_SATURATION:            DrawSaturation();                  	break;
        case _MI_FM_SEND:	              DrawFMMenu();                  	break;        
        case _MI_SYSTEM:         		DrawSystem();		              break;
        case _MI_AUTOSEARCH:            DrawAutoSearch();      	       break;        
        case _MI_MANUALSEARCH:          DrawManualSearch();            break;
        case _MI_TUNING:                       DrawTuning();                       break;
        case _MI_CHANNEL:                    DrawChannel();                      break;
        case _MI_VOLUME:                      DrawVolume();                  	break;
        case _MI_ATUOADJ:                    DrawAtuoAdjustMenu();        break;
        case _MI_LANGUAGE:                 DrawLanguage();                  	break;        
        case _MI_SOURCE:                     DrawSource();                      	break;
        case _MI_LR_SWAP:                   DrawLRSwap();                      	break;
        case _MI_UD_SWAP:                  DrawUDSwap();                      	break;
        case _MI_DISPLAY_RATIO:         DrawDisplayRatio();                break;
        case _MI_RESET:                 
        	m_fResetMenuState = 0;
        	DrawReset();
        	break;
        case _MI_EXIT:                  //DrawExit();                        	break;
        	ucOsdState = _MI_MENU_NONE;
        	COsdTimeOut();
        	break;
	default: break;		
    }


}

//---------------------------------------------------------------------------
void MMainMenuEnterSubMenu(void)
{
    // 1. Before Enter SubMenu
    // Insert code to here ...


    // 2. Change ucOsdState
    
    switch(ucOsdState)
    {
        case _MI_CONTRAST:                                        break;
        case _MI_BRIGHTNESS:                                     break;
        case _MI_HUE:                                                   break;
        case _MI_SATURATION:                                     break;
        case _MI_SYSTEM:         			                  break;
        case _MI_AUTOSEARCH:                               	    break;        
        case _MI_MANUALSEARCH:                                 break;
        case _MI_TUNING:                                             break;
        case _MI_CHANNEL:                                           break;
        case _MI_VOLUME:                                             break;
        case _MI_LANGUAGE:                                 	    break;  
        case _MI_SOURCE:                                            break;
        case _MI_LR_SWAP:                                           break;
        case _MI_UD_SWAP:                                          break;
        case _MI_DISPLAY_RATIO:                                 break;
        case _MI_RESET:							    break;
        case _MI_EXIT:                                                  break;
	 default:break;	
    }

    // 3. Now enter sub menu
    // Insert code to here ...


}
//---------------------------------------------------------------------------
void MMainMenuReturnUpMenu(void)
{
    // 1. Before Return UpMenu
    // Insert code to here ...

    // 2. Change ucOsdState
    ucOsdState = _MI_MENU_NONE;
    COsdFxDisableOsd();

    // 3. Now Return to upmenu
    // Insert code to here ...
}
//---------------------------------------------------------------------------
void CShowAutoSerachTotal(BYTE ucSearchTotal)
{
	ucSearchTotal = ucSearchTotal;
	Gotoxy(3, 1, BYTE_DISPLAY);
    CShowNumber1(ucSearchTotal, 1);    
}
//---------------------------------------------------------------------------
void CShowFreq(WORD iFreqN)
{
    DWORD lFreqTemp = 0;

    // Get PIF freq
    lFreqTemp = (((float)iFreqN/_TUNER_BP) - ((float)_PIF_FREQ/1000))*100;

    Gotoxy(8, 1, BYTE_DISPLAY); 
    iFreqN = lFreqTemp/100;  // MHz  
    CShowNumber1(iFreqN, 0);
    OutputChar(0x2E); // "."

    iFreqN = lFreqTemp%100;  // KHz
    CShowNumber1(iFreqN, 2);

    OutputChar('M');
    OutputChar('H');
    OutputChar('Z');
    OutputChar(0x00); // " "
}

//---------------------------------------------------------------------------
void CShowAutoSearchSliderInOSD(WORD ucCurrentValue)
{
    CShowFreq(ucCurrentValue);
}
//-----------------------------------------------------------------------
bit CKeyStopAutoSearch(void)
{
    BYTE ucIRKey = CIRKeyScan();

	if(_POWER_KEY_MESSAGE == ucIRKey)
	{
//		bPowerState = 1;
		return 1;
	}
  #if(_KEY_TYPE == _KT_PCB2660_003)
    if (_MENU_KEY_MASK == CKeyScan() || _MENU_KEY_MESSAGE == ucIRKey || _IR_MENU_KEY_MESSAGE == ucIRKey)
        return 1;
  #endif
  
  #if(_KEY_TYPE == _KT_PCB2660_003_5KEY)
      if (_MENU_KEY_MASK == CKeyScan() || _ESC_KEY_MESSAGE == ucIRKey)
        return 1;
 #endif
    return 0;
}
//-----------------------------------------------------------------------

#endif      //#if(_OSD_TYPE == _OSD003)
