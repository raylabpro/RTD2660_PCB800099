#define __OSD_FUNC__
#include "Core\Header\Include.h"


 

//---------------------------------------------------------------------------

void SetOsdMap(BYTE ucOsdHeight,BYTE ucOsdWdith,WORD usFontBaseAddress)
{
	g_ucRowCnt = ucOsdHeight;
	g_ucColWidth = ucOsdWdith;
	g_usFontBaseAddress = usFontBaseAddress;

	SetOSDRamAddress();
	SetRowCmds();
}
//---------------------------------------------------------------------------
void SetOSDRamAddress()
{
     unsigned int iFontSelectAddress;
     unsigned int iFntBaseAddr;

     iFontSelectAddress = GET_OSD_MAP_FONT_SELECT_ADDRESS();
     iFntBaseAddr = GET_OSD_MAP_FONTBASEADDRESS();
     //CUartPrintf("FontSelectAddress:",iFontSelectAddress);
     //CUartPrintf("FntBaseAddr:",iFntBaseAddr);

     pData[0] = 0xc0;
     pData[1] = 0x04;
     CScalerWrite(_OSD_ADDR_MSB_90, 2, pData, _AUTOINC);

     pData[0] = iFontSelectAddress & 0xff;
     pData[1] = ((iFontSelectAddress >> 4) & 0xf0) | (iFntBaseAddr & 0x0f);
     pData[2] = ((iFntBaseAddr >> 4) & 0xff);
     CScalerWrite(_OSD_DATA_PORT_92, 3, pData, _NON_AUTOINC);
}
//---------------------------------------------------------------------------
void DirectWOSDRam(WORD iAddress, WORD iLen, BYTE TheByte, BYTE Value)
{
     pData[0] = TheByte | ((iAddress >> 8) & 0x0f);
     pData[1] = (BYTE)(iAddress & 0xff);
     CScalerWrite(_OSD_ADDR_MSB_90, 2, pData, _AUTOINC);
   
     if(TheByte == ALL_BYTE)  
        iLen *= 3;

     CScalerSendAddr(_OSD_DATA_PORT_92 , _NON_AUTOINC);

     while(iLen)
     {
         *(&MCU_SCA_INF_DATA_FFF5) = Value;
         iLen--;
     }

}

//-------------------------------------------------------------
void OutputChar(BYTE C)
{
     CScalerSendAddr(_OSD_DATA_PORT_92 , _NON_AUTOINC);
     *(&MCU_SCA_INF_DATA_FFF5) = C;
}

//-------------------------------------------------------------
void COsdColorPalette(BYTE *pColorPaletteArray)
{
	CScalerSetByte(_OVERLAY_LUT_ADDR_6E, 0x80);
	CScalerWrite(_COLOR_LUT_PORT_6F, 48, pColorPaletteArray, _NON_AUTOINC);
	CScalerSetByte(_OVERLAY_LUT_ADDR_6E, 0x00);
}
//-------------------------------------------------------------
void SetRowCmds() small
{
//    unsigned char i;
    unsigned char ucRowCnt = GET_OSD_MAP_ROWCOUNT();
    // Row Command Byte 0
    // 0x80
    //   Character border/shadow      000: None
    //   Double character width         0: 0x01
    //   Double character height        0: 0x01
    DirectWOSDRam(0x00,ucRowCnt,THE_BYTE0,0x80);

    //Row End Command
    OutputChar(0x00);

    //Row Command Byte 1
    //    0x90
    //    Row height (1~32) : 18
    //    Column space      : 0
    DirectWOSDRam(0x00,ucRowCnt,THE_BYTE1,0x88);

    // Row Command Byte 2

    DirectWOSDRam(0x00,ucRowCnt,THE_BYTE2,g_ucColWidth);
    
}     
//---------------------------------------------------------------------------
void Gotoxy(unsigned char x,unsigned char y,unsigned char TheByte)
{
     unsigned int iAddress = GET_OSD_MAP_FONT_SELECT_ADDRESS();
//     unsigned char i;

     iAddress += (y * g_ucColWidth);
     iAddress += x;

     pData[0] = (unsigned char)(((iAddress >> 8 ) & 0x0f) | TheByte);
     pData[1] = (unsigned char)(iAddress & 0xff);
     CScalerWrite(_OSD_ADDR_MSB_90, 2, pData, _AUTOINC);
}
//---------------------------------------------------------------------------

void PrintfDec(unsigned char Value)				  //hb
{
     unsigned char a[3];
     if(Value / 100 > 0)
     {
         a[0] = (Value / 100) + '0';
         a[1] = ((Value / 10) % 10) + '0';
         a[2] = (Value % 10)  + '0';
     }
     else if(Value / 10 > 0)
     {
         a[0] = 0;
         a[1] = (Value / 10) + '0';
         a[2] = (Value % 10) + '0';
     }
     else
     {
         a[0] = 0;
         a[1] = 0;
         a[2] = Value + '0';
     }

     CScalerWrite(_OSD_DATA_PORT_92, 3, a, _NON_AUTOINC);
}
/*      
//-------------------------------------------------------------

void PrintfInt(unsigned int Value)
{
     unsigned char i,a[5];
     bit fBegin = 0;

     a[0] = (Value / 10000);
     a[1] = ((Value / 1000) % 10);
     a[2] = ((Value / 100) % 10);
     a[3] = ((Value / 10) % 10);
     a[4] = (Value % 10) + '0';

     for(i=0;i<4;i++)
     {
         if(fBegin)
         {
              a[i] += '0';
         }
         else
         {
              if(a[i] != 0)
                 fBegin = 1;
         }
     }

     CScalerWrite(_OSD_DATA_PORT_92, 5, a, _NON_AUTOINC);
}
//---------------------------------------------------------------------------
void PrintfHex(unsigned char Value)
{
     unsigned char h,l,t;
     t = (Value & 0x0f);
     if(t < 10)    l = t + '0';
     else          l = (t - 10) + 'A';

     t = (Value >> 4) & 0x0f;
     if(t < 10)    h = t + '0';
     else          h = (t - 10) + 'A';

     pData[0]    = h;
     pData[1]    = l;
     CScalerWrite(_OSD_DATA_PORT_92, 2, pData, _AUTOINC);   
}
//---------------------------------------------------------------------------
*/
void COsdFxCloseWindow(BYTE ucWinID)
{

    pData[0]    = 0x81;
    pData[1]    = ucWinID * 4 + 3;
    pData[2]    = 0x00;
    CScalerWrite(_OSD_ADDR_MSB_90, 3, pData, _AUTOINC);
}

//-------------------------------------------------------------
WORD ValueInRangeChange(WORD ucMin, WORD ucMax, WORD ucCur, BYTE ucOption)//BYTE ucOption, BYTE ucLoop)
{
    WORD R;

    if((ucOption & _INC) == _INC)
    {
        if(ucCur >= ucMax)
        {
            if((ucOption & _LOOP) == _LOOP)   	
				return ucMin;
            else               					
				return ucMax;
        }
        R = ucCur + 1;
    }
    else
    {
        if(ucCur <= ucMin)
        {
            if((ucOption & _LOOP) == _LOOP)  	
				return ucMax;
            else               			 		
				return ucMin;
        }
        R = ucCur - 1;
    }
    return R;
}

//-------------------------------------------------------------
void SetOSDDouble(BYTE ucAttr)
{
    pData[0]    = 0x40;
    pData[1]    = 0x03;
    pData[2]    = ucAttr & (~_BIT1);
    CScalerWrite(_OSD_ADDR_MSB_90, 3, pData, _AUTOINC); 

	if(ucAttr & _BIT1)
	{
		CScalerSetBit(_OVERLAY_CTRL_6C, ~_BIT1, _BIT1);
	}
	else
	{
		CScalerSetBit(_OVERLAY_CTRL_6C, ~_BIT1, 0x00);
	}   
    
}
//-------------------------------------------------------------
void Textout(BYTE *Text)
{
     CScalerSendAddr(_OSD_DATA_PORT_92,  _NON_AUTOINC);
     while(*Text != 0)
     {
          *(&MCU_SCA_INF_DATA_FFF5) =  *Text++;
     }
}
         
//---------------------------------------------------------------------------
void CCenterTextout(BYTE *str,BYTE ucCenterX,BYTE y)
{
	BYTE len = StrLen(str);

	len /= 2;
	if(ucCenterX > len)
		ucCenterX -= len;
	else 
		ucCenterX = 0;

	Gotoxy(ucCenterX, y, BYTE_DISPLAY);
	Textout(str);
}

/*
//---------------------------------------------------------------------------
void CTextOutRightAlign(BYTE *str,BYTE x,BYTE y)
{
    BYTE ucWidth;
    BYTE ucStrLen = StrLen(str);

    if(ucStrLen > x - 1)
    {
    	x = 1;
    }
    else 
    {
    	x = x - ucStrLen;
    }

    ucWidth = CTextOutBase(str,x,y);
    ucWidth = 12 - (ucWidth % 12);
	if(ucWidth < 4)
    	ucWidth += 12;
 
    CSetBlankWidth(x - 1,y,ucWidth);    
} */
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// OSD_Position : Restore OSD position according to global settings
// para : OSD font parameter
// OSD_GLOBAL_BLINK    : 0x10
// OSD_DISP_ZONE_LEFT  : 0x04
// OSD_DISP_ZONE_RIGHT : 0x08
// OSD_ROTATE          : 0x02
// OSD_ENABLE          : 0x01
//---------------------------------------------------------------------------
void OSDPosition(WORD usOsdActWidth, WORD usOsdActHeight, BYTE ucHPos, BYTE ucVPos, BYTE ucPar)
{
	WORD usBegin = Panel.DHStartPos;//CCalcPanelDHSta();
	WORD usWidth = Panel.DHWidth;//CCalcPanelWdith();
	BYTE ucTemp = 4;

    if(ucHPos > 100)
        ucHPos = 50;

    if(ucVPos > 100)
        ucVPos = 50;
 /*
    usOsdActWidth  = _OSD_HPOSITION_OFFSET + 4 +
                    (DWORD)(usBegin / 8) + 
                    (DWORD)(ucHPos * (usWidth / 4 - usOsdActWidth/4 - 4)) / 100;
   */
    if (GET_OSD_SIZE())
        ucTemp = 8;

    usOsdActWidth  = _OSD_HPOSITION_OFFSET / ucTemp + 
                    (DWORD)(usBegin / ucTemp) + 
                    (DWORD)(ucHPos * (usWidth / 4 - usOsdActWidth/4)) / 100;

    usOsdActHeight = _OSD_VPOSITION_OFFSET + 
                    (DWORD)(Panel.DVStartPos / 4) + 
                    (DWORD)(ucVPos * (Panel.DVHeight / 4 - usOsdActHeight/4 - 6)) / 100;


    CScalerSetBit(_OSD_SCRAMBLE_93, 0xf8, 0x02);

    pData[0] = CScalerGetBit(_OVERLAY_CTRL_6C, _BIT0);

    pData[0] = (pData[0] == 0x00) ? 0xc0 : 0xe0;
    pData[1] = 0x00;
    CScalerWrite(_OSD_ADDR_MSB_90, 2, pData, _AUTOINC);

	pData[0] = usOsdActHeight >> 1;
	pData[1] = (UINT8) (usOsdActWidth >> 2);
	pData[2] = ((UINT8) (usOsdActWidth & 0x0003) << 6) |	((usOsdActHeight & 0x01) << 5) | ucPar;
	CScalerWrite(_OSD_DATA_PORT_92, 3, pData, _NON_AUTOINC);
 
    CTimerWaitForEvent(_EVENT_DEN_STOP);
    CTimerWaitForEvent(_EVENT_DEN_STOP);
    CScalerSetBit(_OSD_SCRAMBLE_93, 0xf8, 0x05);
}

/*****************************************************************************
VALUE:
    0xF0: White
    0xE0: Orange
    0xD0: Pink
    0xC0: Red
    0xB0: Light Bule
    0xA0: Green

wtao100415
******************************************************************************/    
//---------------------------------------------------------------------------
void OSDLine(BYTE row, BYTE col, BYTE length, BYTE value, BYTE TheByte)
{
    BYTE ucRowCharLength = g_ucColWidth;

    //if(ucRowCharLength < col)    return;

    if(ucRowCharLength < (col + length))    
    {
         length = ucRowCharLength - col;
    }

    Gotoxy(col,row,TheByte);

    if(TheByte == ALL_BYTE)    
       length *= 3;

    CScalerSendAddr(_OSD_DATA_PORT_92,  _NON_AUTOINC);
    while(length)
    {
         *(&MCU_SCA_INF_DATA_FFF5) =  value;
         length--;
    }
}

//---------------------------------------------------------------------------
void OSDClear(BYTE row_start, BYTE height,
              BYTE col_start, BYTE width,
              BYTE Value, BYTE indicate)
{          
    if (height)
    {
        do
        {
            OSDLine(row_start, col_start, width, Value, indicate);
            row_start++;
        }
        while (--height);
    }
}

//---------------------------------------------------------------------------
/*
void OutputDisplaySize()
{
     //unsigned int  usHwid;
     //Data[0] 长度不定所以在后面才能得到
     //pData[1] = N_INC;
     //pData[2] = _OSD_DATA_PORT_92;
     if(stModeInfo.IHWidth / 1000)    pData[0] = '1';
     else                             pData[0] = 0;
     pData[1] = (unsigned char)((stModeInfo.IHWidth / 100) % 10) + '0';
     pData[2] = (unsigned char)((stModeInfo.IHWidth / 10) % 10) + '0';
     pData[3] = (unsigned char)(stModeInfo.IHWidth % 10) + '0';

     Gotoxy(2,11,BYTE_DISPLAY);
     CScalerWrite(_OSD_DATA_PORT_92, 4, pData, _NON_AUTOINC);



     if(stModeInfo.IVHeight / 1000)
         pData[0] = '1';
     else
         pData[0] = 0;

     pData[1] = (unsigned char)((stModeInfo.IVHeight / 100) % 10) + '0';
     pData[2] = (unsigned char)((stModeInfo.IVHeight / 10) % 10) + '0';
     pData[3] = (unsigned char)(stModeInfo.IVHeight % 10) + '0';

     Gotoxy(10,11,BYTE_DISPLAY);
     CScalerWrite(_OSD_DATA_PORT_92,4,pData,_NON_AUTOINC);
}

//---------------------------------------------------------------------------------------------------------------------
void OutputRefrushRate()
{                      
     BYTE ucIVFreq = stModeInfo.IVFreq/10;
     pData[0] = (unsigned char)((ucIVFreq / 10) % 10) + '0';
     pData[1] = (unsigned char)(ucIVFreq % 10) + '0';
    
     Gotoxy(20,11,BYTE_DISPLAY);
     CScalerWrite(_OSD_DATA_PORT_92,2,pData,_NON_AUTOINC);
}

//---------------------------------------------------------------------------------------------------------------------
void OutputHFreqRate()
{
     BYTE ucFreq = stModeInfo.IHFreq/10;
     pData[0] = (unsigned char)((ucFreq / 10) % 10) + '0';
     pData[1] = (unsigned char)(ucFreq % 10) + '0';
    
     Gotoxy(20,11,BYTE_DISPLAY);
     CScalerWrite(_OSD_DATA_PORT_92,2,pData,_NON_AUTOINC);
}
*/
//---------------------------------------------------------------------------------------------------------------------
void COsdFxEnableOsd(void)
{
    CTimerWaitForEvent(_EVENT_DEN_STOP);
    CScalerSetBit(_OVERLAY_CTRL_6C, ~_BIT0, _BIT0);   
}

//--------------------------------------------------
void COsdFxDisableOsd(void)
{       
    CTimerWaitForEvent(_EVENT_DEN_STOP);
    CScalerSetBit(_OVERLAY_CTRL_6C, ~_BIT0, 0x00);
    CLR_KEYREPEATENABLE();

    bTimerOnScreen = 0;
}

//--------------------------------------------------
void COsdFxDrawWindow(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE *pStyle)
{
    BYTE cnt0, cnt1;

    cnt0    = CScalerGetBit(_OVERLAY_CTRL_6C, _BIT0);

    pData[0]    = (cnt0 == 0x00) ? 0xc1 : 0xe1;
    pData[1]    = ((*(pStyle)) * 4) + 1;
    CScalerWrite(_OSD_ADDR_MSB_90, 2, pData, _AUTOINC);

    pData[0]    = ((usXStart & 0x03F) << 2);
    pData[1]    = (((usYStart & 0x007) << 5) | ((usXStart & 0x7C0) >> 6));
    pData[2]    = (usYStart >> 3);
    pData[3]    = ((usXEnd & 0x03F) << 2);
    pData[4]    = (((usYEnd & 0x007) << 5) | ((usXEnd & 0x7C0) >> 6));
    pData[5]    = (usYEnd >> 3);
    CScalerWrite(_OSD_DATA_PORT_92, 6, pData, _NON_AUTOINC);

    CTimerDelayXms(40);

    for(cnt1=0;cnt1<2;cnt1++)
    {	
        pData[0]    = 0xc1;
        pData[1]    = ((*(pStyle)) * 4) + (cnt1 * 3);
        CScalerWrite(_OSD_ADDR_MSB_90, 2, pData, _AUTOINC);

        for(cnt0=0;cnt0<3;cnt0++)
            pData[cnt0]   = (*(pStyle + ((cnt1 * 3) + cnt0) + 1));

        CScalerWrite(_OSD_DATA_PORT_92, 3, pData, _NON_AUTOINC);
    }
}
//--------------------------------------------------
/*
void COsdFxChangeWindowColor(BYTE ucWindowColor, BYTE *pStyle)
{
    pData[0]    = 0x41;
    pData[1]    = ((*(pStyle)) * 4) + (3);
    CScalerWrite(_OSD_ADDR_MSB_90, 2, pData, _AUTOINC);

    pData[0]    = ((*(pStyle + ((3) + 1) + 1)) & 0xf0) | (ucWindowColor & 0x0f);
    CScalerWrite(_OSD_DATA_PORT_92, 1, pData, _NON_AUTOINC);
}
*/
//--------------------------------------------------
BYTE COsdCtrlGetHPosition(void)
{
	unsigned int ucMin = stModeUserCenterData.CenterHPos - _HPOSITION_BIAS;
	unsigned int iTmp = (stModeUserData.HPosition - ucMin) * 100 / (_HPOSITION_BIAS * 2);
	return (unsigned char)iTmp;
}


//---------------------------------------------------------------------------
/*
WORD COsdFxGetVPositionRange(BYTE ucPar)
{
    if(ucPar == _GET_VPOSITIONRANGE_MAX)
        return (stModeUserCenterData.CenterVPos + _VPOSITION_BIAS);
    else if(ucPar == _GET_VPOSITIONRANGE_MIN)
        return (stModeUserCenterData.CenterVPos - _VPOSITION_BIAS);
}

//---------------------------------------------------------------------------
*/
BYTE COsdCtrlGetVPosition(void)
{
//	return 100 - (stModeUserData.VPosition-COsdFxGetVPositionRange(_GET_VPOSITIONRANGE_MIN))*100/(COsdFxGetVPositionRange(_GET_VPOSITIONRANGE_MAX)-COsdFxGetVPositionRange(_GET_VPOSITIONRANGE_MIN));
	unsigned int ucMin = stModeUserCenterData.CenterVPos - _VPOSITION_BIAS;
	unsigned int iTmp = (stModeUserData.VPosition - ucMin) * 100 / (_VPOSITION_BIAS * 2);
	return (unsigned char)iTmp;
}

//---------------------------------------------------------------------------
WORD COsdFxGetAdcClockRange(BYTE ucPar)
{
    WORD delta;

    if(ucPar == _GET_CLOCKRANGE_MAX)
    {
        CAdjustCheckAdcClockRange(stModeUserCenterData.CenterClock, &delta);

        if(delta > _CLOCK_BIAS)
            return (stModeUserCenterData.CenterClock + _CLOCK_BIAS);
        else
            return (stModeUserCenterData.CenterClock + delta);
    }
    else if(ucPar == _GET_CLOCKRANGE_MIN)
    {
        CAdjustCheckAdcClockRange(stModeUserCenterData.CenterClock, &delta);

        if(delta > _CLOCK_BIAS)
            return (stModeUserCenterData.CenterClock - _CLOCK_BIAS);
        else
            return (stModeUserCenterData.CenterClock - delta);
    }
}

//---------------------------------------------------------------------------
BYTE COsdCtrlGetClock(void)
{
      WORD iMin;
      WORD  iTmp;

      iMin = COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MIN);
      iTmp = (stModeUserData.Clock - iMin) * 100 / (COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MAX) - iMin);

      return (BYTE)iTmp;
}
/*
//---------------------------------------------------------------------------
BYTE COsdCtrlGetPhase(void)
{
	return ((WORD)stModeUserData.Phase*100/63);		
}*/

//---------------------------------------------------------------------------


BYTE StrLen(BYTE  *Str)
{
    BYTE i = 0;

    while(*Str != 0)
    {
        i++;
        Str++;
    }

    return i;
}

//----------------------------------------------------------------------------------------------------
BYTE GetNextLanguage(BYTE CurrIndex)
{
     BYTE i;
     WORD iMask = usLANGUAGE_MASK;

     iMask >>= (CurrIndex+1);

     for(i=CurrIndex+1;i<16;i++)
     {
         if(iMask&0x01)
         {
             return i;
         }
         iMask >>= 1;
     }

     //???????????Next Langage
     iMask = usLANGUAGE_MASK;
     for(i=0;i<CurrIndex;i++)
     {
         if(iMask&0x01)
         {
             return i;
         }
         iMask >>= 1;
     }
     return CurrIndex;
}

//----------------------------------------------------------------------------------------------------
BYTE GetPrevLanguage(BYTE CurrIndex)
{
     char i;
     WORD iMask = usLANGUAGE_MASK;

     iMask <<= (16 - CurrIndex);

     for(i=CurrIndex - 1;i>=0;i--)
     {
         if(iMask & 0x8000)
         {
             return i;
         }
         iMask <<= 1;
     }

     //???????????Prev Langage
     iMask = usLANGUAGE_MASK;
     for(i=15;i>=CurrIndex;i--)
     {
         if(iMask & 0x8000)
         {
             return i;
         }
         iMask <<= 1;
     }
     return CurrIndex;
}

//----------------------------------------------------------------------------------------------------
BYTE CheckLanguage(void)
{
     BYTE ucLanguage = GET_LANGUAGE();
     WORD iMask      = usLANGUAGE_MASK;

     iMask >>= ucLanguage;

     if(iMask & 0x01)
     {
         return ucLanguage;
     }
     else
     {
         ucLanguage = FirstLanguage();
         SET_LANGUAGE(ucLanguage);

         return ucLanguage;
     }
}

//----------------------------------------------------------------------------------------------------
BYTE FirstLanguage(void)
{
     BYTE i;
     WORD iMask = usLANGUAGE_MASK;

     for(i=0;i<16;i++)
     {
         if(iMask&0x01)
         {
             return i;
         }
         iMask >>= 1;
     }
     return 255;
}

//---------------------------------------------
//#if(_BURNIN_EN)
void InitBurnIn()
{     
     CModeSetFreeRun();
     CTimerWaitForEvent(_EVENT_DVS);
     CAdjustBackgroundColor(0x00,0x00,0x00);
     CTimerWaitForEvent(_EVENT_DVS);
     CPowerPanelOn();
     CPowerLightPowerOn();
}
//---------------------------------------------
void BurnInRun()
{
	static BYTE ucBurnInDelay = 0;
	static BYTE ucBurnInColor = 0;
	BYTE R = 0;
	BYTE G = 0;
	BYTE B = 0;

	if(ucBurnInDelay < 100)
	{
		ucBurnInDelay++;
		//CTimerDelayXms(10);
		return;
	}

	ucBurnInDelay = 0;

	if(ucBurnInColor & 0x80)
	{
		if(ucBurnInColor & 0x01)     R = 0xff;
		if(ucBurnInColor & 0x02)     G = 0xff;
		if(ucBurnInColor & 0x04)     B = 0xff;
	}
	else
	{
		if(ucBurnInColor & 0x01)     R = 0x7f;
		if(ucBurnInColor & 0x02)     G = 0x7f;
		if(ucBurnInColor & 0x04)     B = 0x7f;
	}

    if (bfBurnIn == 0)
    {
        InitBurnIn();        
        bfBurnIn = 1;
    }

    CTimerWaitForEvent(_EVENT_DVS);
	CAdjustBackgroundColor(R,G,B);
	ucBurnInColor++;
}
//---------------------------------------------

//#endif   // if(BURNIN_EN)

//----------------------------------------------------------- 
//  ucNumber:      0~65535
//  ucUserDefLong: 0   --> 自动计算ucNumber长度，有几位输出几位
//                 1~5 --> 输出1~5位，不足用0补
//  exp:           ucNumber = 12
//                 ucUserDefLong = 0    Output:  12
//                 ucUserDefLong = 3    Output:  012
//----------------------------------------------------------- 
void CShowNumber1(const WORD ucNumber, BYTE ucUserDefLong)
{
    BYTE uctemp[5];
    
    uctemp[4] = (ucNumber / 10000) % 10;
    uctemp[3] = (ucNumber / 1000) % 10;
    uctemp[2] = (ucNumber / 100) % 10;
    uctemp[1] = (ucNumber / 10) % 10;
    uctemp[0] = ucNumber  % 10;
    
    if (ucUserDefLong)
        ucUserDefLong -= 1;     
    else    
    {
        for(pData[15] = 4; pData[15]>0;pData[15]--)
        {
            if(uctemp[pData[15]] != 0)
                break;          
        }
        
        ucUserDefLong = pData[15];
    }
    
    CScalerSendAddr(_OSD_DATA_PORT_92 , _NON_AUTOINC);
    do
    {
        *(&MCU_SCA_INF_DATA_FFF5) = (uctemp[ucUserDefLong]+'0');
    }
    while(ucUserDefLong--);
} 

//----------------------------------------------------------- 
void CCloseAllWindows(void)
{
	pData[0] = 0xC1;
	pData[1] = 0x00;
	CScalerWrite(_OSD_ADDR_MSB_90, 2, pData, _AUTOINC);

	CScalerWriteAmount(_OSD_DATA_PORT_92, 84, 0x00, _NON_AUTOINC);
}
//----------------------------------------------------------- 

void CDoReset(void) 
{
    BYTE ucTemp0 = GET_POWERSTATUS();
    BYTE ucTemp1 = _GET_INPUT_SOURCE();
    BYTE ucTemp2 = GET_LANGUAGE();
    BYTE ucTemp3 = GET_DISPLAYMODE();
    BYTE ucBrnin = GET_BURNIN_STATE();
    //BYTE ucGamma = stSystemData.Gamma;//GET_GAMMA();
    BYTE ucNR    = GET_NOISEREDUTION();
    BYTE fLR = GET_LR_SWAP();
    BYTE fUD = GET_UD_SWAP();


    CEepromLoadDefault(0);

    if (ucTemp0)    
       SET_POWERSTATUS();
    else
       CLR_POWERSTATUS();


    SET_BURNIN_STATE((ucBrnin ? 1 : 0));
    SET_NOISEREDUTION(ucNR);

    _SET_INPUT_SOURCE(ucTemp1);
    //SET_LANGUAGE(ucTemp2);
    SET_LANGUAGE(ENGLISH); //wtao100413
    SET_DISPLAYMODE(ucTemp3);
    SET_LR_SWAP(fLR);
    SET_UD_SWAP(fUD);
    
    CEepromSaveSystemData();
    CEepromSaveOsdUserData();

	CEepromLoadColorTempData();
    CAdjustBrightness();
    CAdjustContrast();
    CAdjustAudio();
    CSetVolume();
    ucOsdEventMsg = _SAVE_EE_SYSTEMDATA_MSG;

    CAdjustPeakingCoding();
    if(bSourceVideo())
    {
        kx_CAdjustVDCHue(GET_HUE());
        CVideoSetSaturation(GET_SATURATION());
    }
    else
    {
    	if((_GET_INPUT_SOURCE() != _SOURCE_YPBPR)&&(_GET_INPUT_SOURCE() != _SOURCE_YPBPR1))
        	CAdjustYpbprhue(50);
	
        if((_GET_INPUT_SOURCE() == _SOURCE_YPBPR)||(_GET_INPUT_SOURCE() == _SOURCE_YPBPR1))
        {
            CAdjustYpbprhue(GET_HUE());
            CAdjustYpbprSaturation(GET_SATURATION());
        }
        else if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
        {
            CAutoDoAutoConfig();
            CAutoDoWhiteBalance();
			stModeUserData.FirstAuto = 1;
            CEepromSaveModeData(stModeInfo.ModeCurr);
        }
    }
}

    
/*  OSD Window Templet
//BASE ADDRESS + 000 Shadow/Border/Gradient
SB_THICKNESS(1) | SB_HEIGHT(1) ,
SHADOW_COLOR(1) | BORDER_COLOR(2),
R_GRADIENT_POLARITY_DEC |
  G_GRADIENT_POLARITY_INC |
  B_GRADIENT_POLARITY_DEC |
  GRADIENT_LEVEL(1) |
  R_COLOR_GRADIENT_EN(1) |
  G_COLOR_GRADIENT_EN(1) |
  B_COLOR_GRADIENT_EN(1),

//BASE ADDRESS + 001 START POSITION
W_START_POS(10,300),
//BASE ADDRESS + 002 END POSITION
W_END_POS(20,350),

//BASE ADDRESS + 003  Control
RESERVED,
GRADIENT_PER_LEVEL(2) | WINDOW_COLOR(3),

GRADIENT_FUNCTION_EN(1) |
  GRADIENT_DIRECTION_HOR |
  SHADOW_BORDER_EN(1) |
  WINDOW_TYPE(WT_3DBUTTON_TYPE1) |
  WINDOW_ENABLE(1),

*/

