
#define _OSD_HPOSITION_OFFSET           4
#define _OSD_VPOSITION_OFFSET           2


#define OSD_ENABLE                      0x01



//--------------------------------------------------
// Macro of OSD
//--------------------------------------------------

#define FONTBYTE0(x)                    HIBYTE(0x1000|x),LOBYTE(0x1000|x)

#define FONTBYTE1(x)                    HIBYTE(0x5000|x),LOBYTE(0x5000|x)

#define FONTBYTE2(x)                    HIBYTE(0x9000|x),LOBYTE(0x9000|x)

#define FONTALLBYTE(x)                  HIBYTE(0xD000|x),LOBYTE(0xD000|x)

#define WINDOWBYTE0(x)                  HIBYTE(0x1000|x),LOBYTE(0x1000|x)

#define WINDOWBYTE1(x)                  HIBYTE(0x4000|x),LOBYTE(0x4000|x)

#define WINDOWBYTE2(x)                  HIBYTE(0x8000|x),LOBYTE(0x8000|x)

#define WINDOWALLBYTE(x)                HIBYTE(0xC000|x),LOBYTE(0xC000|x)

#define FRAMEBYTE0(x)                   WINDOWBYTE0(x)

#define FRAMEBYTE1(x)                   WINDOWBYTE1(x)

#define FRAMEBYTE2(x)                   WINDOWBYTE2(x)

#define FRAMEALLBYTE(x)                 WINDOWALLBYTE(x)

#define WINNO(x)                        x

#define ROW(x)                          x

#define COL(x)                          x

#define WIDTH(x)                        x

#define HEIGHT(x)                       x

#define LENGTH(x)                       x

#define FGCOLOR(x)                      x

#define BGCOLOR(x)                      x

#define COLOR00(x)                      x

#define COLOR01(x)                      x

#define COLOR10(x)                      x

#define COLOR11(x)                      x

#define XSTART(x)                       x

#define YSTART(x)                       x

#define XEND(x)                         x

#define YEND(x)                         x


//--------------------------------------------------
// Definitions of Color Palette
//--------------------------------------------------
#define _CP_BLACK                       0
#define _CP_WHITE                       1
#define _CP_RED                         2
#define _CP_GREEN                       3
#define _CP_BLUE                        4
#define _CP_YELLOW                      5
#define _CP_GRAY                        6
#define _CP_DARKBLUE                    7
#define _CP_LIGHTBLUE                   8
#define _CP_COLOR9                      9
#define _CP_COLOR10                     10
#define _CP_COLOR11                     11
#define _CP_COLOR12                     12
#define _CP_COLOR13                     13
#define _CP_COLOR14                     14
#define _CP_COLOR15                     15


#define _EXT_                              0xfc
#define _REPEAT_                        0xfd
#define _NEXT_                            0xfe
#define _END_                              0xff

#define Y_INC                           _AUTOINC
#define N_INC                           _NON_AUTOINC
#define BURST                           _BURST
#define OSD_ADDR_MSB_90                 _OSD_ADDR_MSB_90
#define OSD_DATA_92                     _OSD_DATA_PORT_92
#define _bb_                            _REPEAT_
#define _nn_                            _NEXT_
#define _end_                           _END_

#define RESERVED                        0x00

//Define Byte option
#define THE_BYTE0                       0x10
#define BYTE_ATTRIB                     0x10
#define THE_BYTE1                       0x50
#define BYTE_DISPLAY                    0x50
#define THE_BYTE2                       0x90
#define BYTE_COLOR                      0X90
#define ALL_BYTE                        0xd0


//Widnow Attrib Define
//Shadow/Border/Gradient
//BASE ADDRESS + 000
//BYTE 0
//[5:3]
#define SB_THICKNESS(x)                (x << 3)
//[2:0]
#define SB_HEIGHT(x)                   (x)

//BYTE 1
//[7:4]
#define SHADOW_COLOR(color)            (color << 4)
//[3:0]
#define BORDER_COLOR(color)            color

//BYTE 2
//[7]
#define R_GRADIENT_POLARITY_DEC        0
#define R_GRADIENT_POLARITY_INC        0x80
//[6]
#define G_GRADIENT_POLARITY_DEC        0
#define G_GRADIENT_POLARITY_INC        0x40
//[5]
#define B_GRADIENT_POLARITY_DEC        0
#define B_GRADIENT_POLARITY_INC        0x20
//[4:3]
#define GRADIENT_LEVEL(level)          (level << 3)
//[2]
#define R_COLOR_GRADIENT_EN(en)        (en << 2)
//[1]
#define G_COLOR_GRADIENT_EN(en)        (en << 1)
//[0]
#define B_COLOR_GRADIENT_EN(en)        en

//START POSITION
//BASE ADDRESS + 001
#define W_START_POS(H_STA,V_STA)       ((H_STA & 0x1f) << 2),((V_STA & 0x07) << 5) | ((H_STA >> 6) & 0x1f),(V_STA >> 3)

//END POSITION
//BASE ADDRESS + 002
#define W_END_POS(H_END,V_END)         ((H_END & 0x1f) << 2),((V_END & 0x07) << 5) | ((H_END >> 6) & 0x1f),(V_END >> 3)

//Control
//BASE ADDRESS + 003
//BYTE 1
//[6:4]
#define GRADIENT_PER_LEVEL(level)      (level << 4)
//[3:0]
#define WINDOW_COLOR(color)            color //0:Black  1:Blue   2:Green  3:Light Blue 4:Red //wtao100415

//BYTE 2
//[6]
#define GRADIENT_FUNCTION_EN(en)        (en << 6)
//[5]
#define GRADIENT_DIRECTION_HOR          0
#define GRADIENT_DIRECTION_VER          0x20
//[4]
#define SHADOW_BORDER_EN(en)            (en << 4)
//[3:1]
#define WINDOW_TYPE(type)               (type << 1)
//[0]
#define WINDOW_ENABLE(en)               en

//Window Type Define
#define WT_SHADOW_TYPE1                 0
#define WT_SHADOW_TYPE2                 1
#define WT_SHADOW_TYPE3                 2
#define WT_SHADOW_TYPE4                 3
#define WT_3DBUTTON_TYPE1               4
#define WT_3DBUTTON_TYPE2               5
#define WT_RESERVED                     6
#define WT_BORDER                       7


// PWM ADDRESS003 BYTE 1 DEFINE
#define OSD_DOUBLE_HEIGHT_ENABLE        0x01
#define OSD_DOUBLE_WIDTH_ENABLE         0x02
#define OSD_WINDOW_BLENDING             0x04
#define OSD_ALL_BLENDING                0x08
#define OSD_WINDOWCHAR_BLENDING         0x0C
#define SHOW_COLOR(color)               (color << 4)




//--------------------------------------------------
// Definitions of Clock Settings Used by COsdFxGetAdcClockRange()
//--------------------------------------------------
#define _CLOCK_BIAS                     50
#define _GET_CLOCKRANGE_MAX             0
#define _GET_CLOCKRANGE_MIN             1


//--------------------------------------------------
// Definitions of Hor. Position Settings Used by COsdFxGetHPositionRange()
//--------------------------------------------------
#define _HPOSITION_BIAS                 (ucHStartBias  - abs(stModeInfo.IHStartPos - stModeUserCenterData.CenterHPos))
#define _GET_HPOSITIONRANGE_MAX         0
#define _GET_HPOSITIONRANGE_MIN         1


#define GET_LANGUAGE()        			stOsdUserData.Language
#define SET_LANGUAGE(value)    			stOsdUserData.Language = value 

//--------------------------------------------------
// Definitions of Ver. Position Settings Used by COsdFxGetVPositionRange()
//--------------------------------------------------
#define _VPOSITION_BIAS                 		(ucVStartBias - abs(stModeInfo.IVStartPos - stModeUserCenterData.CenterVPos))
#define _GET_VPOSITIONRANGE_MAX         		0
#define _GET_VPOSITIONRANGE_MIN         		1



#define GET_OSD_MAP_ROWCOUNT()                  g_ucRowCnt//pOsdMap[0]
#define GET_OSD_MAP_FONT_SELECT_ADDRESS()       (g_ucRowCnt + 1)//(pOsdMap[0] + 1)
#define GET_OSD_MAP_FONTBASEADDRESS()           g_usFontBaseAddress//(((unsigned int)pOsdMap[2] << 8) | pOsdMap[1])




#ifdef __OSD_FUNC__

//  OSD Width & height Defines
BYTE idata ucOsdEventMsg = 0;
BYTE idata ucOsdState = 0;

BYTE g_ucRowCnt = 0;
BYTE g_ucColWidth = 0;
WORD g_usFontBaseAddress = 0;

bit bOSDTimeOut = 1;
bit bfBurnIn = 0;

//BYTE LogoMoveX = 0; //wtao100423
//BYTE LogoMoveY = 0;


#else

extern BYTE idata ucOsdEventMsg;
extern BYTE idata ucOsdState;

extern BYTE g_ucRowCnt;
extern BYTE g_ucColWidth;
extern WORD g_usFontBaseAddress;

extern bit bOSDTimeOut;

extern bit bfBurnIn;

//extern BYTE LogoMoveX; //wtao100423
//extern BYTE LogoMoveY;

#endif   //#ifndef OSD_FUNCH


void SetOsdMap(BYTE ucOsdHeight,BYTE ucOsdWdith,WORD usFontBaseAddress);
void SetOSDRamAddress();
void DirectWOSDRam(WORD iAddress, WORD iLen, BYTE TheByte, BYTE Value);
void SetRowCmds() small;
void Gotoxy(BYTE x, BYTE y, BYTE TheByte);
void OutputChar(BYTE C);
void PrintfDec(unsigned char Value);
void COsdFxCloseWindow(BYTE ucWinID);
WORD ValueInRangeChange(WORD ucMin, WORD ucMax, WORD ucCur, BYTE ucOption);
void SetOSDDouble(BYTE ucAttr);

void PrintfHex(unsigned char Value);
void PrintfInt(unsigned int Value);


void Textout(BYTE *Text);
void CCenterTextout(BYTE *str,BYTE ucCenterX,BYTE y);
BYTE StrLen(BYTE *Str);

void OSDPosition(WORD usOsdActWidth, WORD usOsdActHeight, BYTE ucHPos, BYTE ucVPos, BYTE ucPar);
void OSDLine(BYTE row, BYTE col, BYTE length, BYTE value, BYTE indicate);
void OSDClear(BYTE row_start, BYTE height,
               BYTE col_start, BYTE width,
               BYTE Value, BYTE indicate);
void OutputDisplaySize();       //在当前的位置输出显示尺寸
void OutputRefrushRate();       //在当前的位置输出刷新频率

void COsdFxEnableOsd(void);
void COsdFxDisableOsd(void);
void COsdFxChangeWindowColor(BYTE ucWindowColor, BYTE *pStyle);
void COsdFxDrawWindow(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE *pStyle);
void OutputDisplaySize();
void OutputRefrushRate();

BYTE COsdCtrlGetHPosition(void);
WORD COsdFxGetVPositionRange(BYTE ucPar);
BYTE COsdCtrlGetVPosition(void);
WORD COsdFxGetAdcClockRange(BYTE ucPar);
BYTE COsdCtrlGetClock(void);
BYTE COsdCtrlGetPhase(void);

void InitBurnIn();
void BurnInRun();
void OutputHFreqRate();

BYTE GetNextLanguage(BYTE CurrIndex);
BYTE GetPrevLanguage(BYTE CurrIndex);
BYTE CheckLanguage();
BYTE FirstLanguage();


void CShowNumber(BYTE x,BYTE y,BYTE Value);
void COsdColorPalette(BYTE *pColorPaletteArray);

BYTE CCalcRatio(void);
WORD CCalcPanelWdith(void);
WORD CCalcPanelDHSta(void);
WORD CCalcPanelDHEnd(void);

void CShowNumber1(const WORD ucNumber, BYTE ucUserDefLong);
void CDoReset(void);
void CCloseAllWindows(void);

