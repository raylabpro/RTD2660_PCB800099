
#if(_PANEL_TYPE == _PNL_AT102TN03)

#define _PANEL_LR_UD_FUNC				_ON
//--------------------------------------------------
//_PANEL_TTL / _PANEL_HZ / _PANEL_LVDS / _PANEL_RSDS
#define _OUTPUT_BUS                     _PANEL_TTL

//--------------------------------------------------
// _DISP_24_BIT / _DISP_18_BIT
#define _DISP_BIT                       _DISP_18_BIT

//--------------------------------------------------
#define _DISP_EO_SWAP                   0//(1 << 6)
#define _DISP_RB_SWAP                   0//(1 << 5)
#define _DISP_ML_SWAP                   (1 << 4)

#define _RSDS_GC_SWAP                   0//(1 << 7)
#define _RSDS_HL_SWAP                   0//(1 << 6)
#define _RSDS_PN_SWAP                   0//(1 << 5)

//--------------------------------------------------
// _DISP_SINGLE_PORT / _DISP_DOUBLE_PORT
#define _DISPLAY_PORT                   _DISP_SINGLE_PORT

//--------------------------------------------------
#define _DISP_WID                       800
#define _DISP_LEN                       480

#define _DH_ACT_STA_POS                 32
#define _DH_ACT_END_POS                 (_DISP_WID + _DH_ACT_STA_POS)

#define _DV_ACT_STA_POS                 12//16
#define _DV_ACT_END_POS                 (_DISP_LEN + _DV_ACT_STA_POS)

//--------------------------------------------------
// _LVDS_MAP1 / _LVDS_MAP2
#define _LVDS_MAP                       _LVDS_MAP2

//--------------------------------------------------
#define _STD_DH_TOTAL                   1056//940

#define _STD_DV_TOTAL                   550

#define _STD_PIXCEL_CLOCK               (((DWORD)_STD_DH_TOTAL * (DWORD)_STD_DV_TOTAL * (DWORD)60) / (DWORD)1000000)

#define _HSYNC_WIDTH                    16
#define _VSYNC_HEIGHT                   3

//--------------------------------------------------
// Definitions for Display VIDEO/TV Signal
//--------------------------------------------------
#define _VIDEO_50_DH_TOTAL              _STD_DH_TOTAL
#define _REGSISTER40_50HZ               0x00
#define _REGSISTER41_50HZ               0x36
#define _REGSISTER42_50HZ               0x1B
#define _REGSISTER43_50HZ               0x02
#define _P1_REGSISTERC4_50HZ            0x18
#define _P1_REGSISTERC5_50HZ            0x9B

#define _VIDEO_60_DH_TOTAL              _STD_DH_TOTAL
#define _REGSISTER40_60HZ               0x00
#define _REGSISTER41_60HZ               0x22
#define _REGSISTER42_60HZ               0x08
#define _REGSISTER43_60HZ               0x02
#define _P1_REGSISTERC4_60HZ            0x18
#define _P1_REGSISTERC5_60HZ            0x83
//------------------- TV END -----------------------

//--------------------------------------------------
// Definitions of DPLL N Code
//--------------------------------------------------
#define _DPLL_N_CODE                    16//8

//--------------------------------------------------
// Set Last Line Finetune Method
//--------------------------------------------------
/*
_LAST_LINE_METHOD_NONE, _LAST_LINE_METHOD_0
_LAST_LINE_METHOD_1,    _LAST_LINE_METHOD_2
*/
#define _LAST_LINE_FINETUNE             _LAST_LINE_METHOD_NONE
#define _LAST_LINE_TARGET               400 // For _LAST_LINE_METHOD_2

//--------------------------------------------------
#define _AUTOCALC_PIXCLK                (_DISABLE << 2)     

//--------------------------------------------------
// Definitions for First DHS Masking
//--------------------------------------------------
#define _DHS_MASK                       0//(1 << 7)

//--------------------------------------------------
// Definitions for Display Signal
//--------------------------------------------------
#define _DVS_INVERT                     (_DISABLE << 2)
#define _DHS_INVERT                     (_DISABLE << 1)
#define _DEN_INVERT                     (_DISABLE)

#define _DISPLAY_INVERT                 (_DVS_INVERT | _DHS_INVERT | _DEN_INVERT)

//--------------------------------------------------
// Definitions for Display Control
//--------------------------------------------------
#define _DISPLAY_CTRL                   (_DHS_MASK | _DISPLAY_INVERT)

//--------------------------------------------------
// TTL panel setting
//--------------------------------------------------
#define _TTL_DCLK_DELAY                 0 //(0~7)
#define _TTL_DCLK_OUTPUT                _ENABLE
#define _TTL_DCLK_INVERT                _ENABLE//_DISABLE

//--------------------------------------------------
// Support Timing
//--------------------------------------------------
#define _H_FREQ_MAX                     930//1100            // Unit in 0.1 kHZ
#define _H_FREQ_MIN                     200//100             // Unit in 0.1 kHZ
#define _V_FREQ_MAX                     780             // Unit in 0.1 HZ
#define _V_FREQ_MIN                     490//470             // Unit in 0.1 HZ

#define LVDS_CTRL_LEVEL                 4       //0~7

//--------------------------------------------------
#define _TVNUMBER_POSITION_OFFSET       64
#define _TVSIGNAL_POSITION_OFFSET       64


#ifdef __RTDACCESS__

//--------------------------------------------------
code PanelType Panel =
{
	// Panel Style
    _OUTPUT_BUS      |
    _AUTOCALC_PIXCLK |
    _LVDS_MAP        |	
    _DISP_BIT        | 
    _RSDS_GC_SWAP    |
    _RSDS_HL_SWAP    |
    _RSDS_PN_SWAP,

	// Panel Configuration
	_DISP_EO_SWAP |
	_DISP_RB_SWAP |
	_DISP_ML_SWAP |
	_DISPLAY_PORT |
	_DISPLAY_CTRL,


    _DH_ACT_STA_POS,  // Display Horizontal Start Position
    _DISP_WID,        // Display Horizontal Width

    _STD_DH_TOTAL,    // Display Horizontal Total Clock Number in One Display Line

    _DV_ACT_STA_POS,  // Display Vertical Start Position
    _DISP_LEN,        // Display Vertical Height

    _STD_DV_TOTAL,    // Display Vertical Total Line Number in One Frame

    _HSYNC_WIDTH,     // Display H Sync Width
    _VSYNC_HEIGHT,    // Display V Sync Height

    _STD_PIXCEL_CLOCK,// Typical Pixel Clock in MHz

    _H_FREQ_MAX,      // H Sync Max Freq Unit in 0.1 kHZ
    _H_FREQ_MIN,      // H Sync Min Freq Unit in 0.1 kHZ
    _V_FREQ_MAX,      // V Sync Max Freq Unit in 0.1 HZ
    _V_FREQ_MIN,      // V Sync Min Freq Unit in 0.1 HZ

    //-----------------------------------------------------------------------------------
    // For TV
    // PAL
    _VIDEO_50_DH_TOTAL,       // Display Horizontal Total Clock Number in One Display Line for CVBS PAL
#if(_VIDEO_TV_SUPPORT)
    _REGSISTER40_50HZ,        // PalIVDV40   IVS to DVS Delay Lines 
    _REGSISTER41_50HZ,        // PalIVDV41   Frame Sync Delay Fine Tuning ODD
    _REGSISTER42_50HZ,        // PalIVDV42   Frame Sync Delay Fine Tuning EVEN
    _REGSISTER43_50HZ,        // PalIVDV43   Frame Sync Delay Fine Tuning Control Register
    _P1_REGSISTERC4_50HZ,     // PalP1C4     Display Clock Fine Tune Offset MSB
    _P1_REGSISTERC5_50HZ,     // PalP1C5     Display Clock Fine Tune Offset LSB
#endif

    // For NTSC
    _VIDEO_60_DH_TOTAL,       // Display Horizontal Total Clock Number in One Display Line for CVBS NTSC
#if(_VIDEO_TV_SUPPORT)
    _REGSISTER40_60HZ,        // NtscIVDV40  IVS to DVS Delay Lines
    _REGSISTER41_60HZ,        // NtscIVDV41  Frame Sync Delay Fine Tuning ODD
    _REGSISTER42_60HZ,        // NtscIVDV42  Frame Sync Delay Fine Tuning EVEN
    _REGSISTER43_60HZ,        // NtscIVDV43  Frame Sync Delay Fine Tuning Control Register
    _P1_REGSISTERC4_60HZ,     // NtscP1C4    Display Clock Fine Tune Offset MSB
    _P1_REGSISTERC5_60HZ,     // NtscP1C5    Display Clock Fine Tune Offset LSB
#endif
    //--------------------------------TV END---------------------------------------------

    // TTL setting   
    (_TTL_DCLK_DELAY << 4)  | // Delay
    (_TTL_DCLK_OUTPUT << 1) | // DCLK output enable
    _TTL_DCLK_INVERT,         // DCLK Polarity

};


//--------------------------------------------------
WORD code tVIDEO_TABLE_INPUT_INFO[][5] =
{
	// ih_total,ih_start,iV_height,iv_start,height
    { 864,    155,    672,    31,    274 },					// pal
    { 858,    141,    696,    26,    232 },					// ntsc
};


#define _TCON(x)							(x * 8 + 0x08)

//--------------------------------------------------
// Display Interface Initial
//--------------------------------------------------
BYTE code tTTL_INITIAL[] =
{
    #if(_OUTPUT_BUS == _PANEL_TTL)    
    
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,     0x00,0x80,     //0x80  0xdc
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,     0x01,0x3e, 
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,     0x78,0xf0,           // POWER UP LVDS

   //TCON0  CPV
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON(0),
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0C,0x10,0xEC,0xFE,0x21,0xCC,0xC0,


    //TCON1  LD
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON(1),
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0C,0x10,0xEC,0x1B,0x00,0x20,0x80,


    //TCON9  POL
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON(9),
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0C,0x10,0xEC,0x00,0x00,0x1E,0x88,


    //TCON6  STHR
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON(6),
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0C,0x10,0xEC,0x66,0x00,0x68,0x80,


    //TCON3  STHL
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON(3),
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0C,0x10,0xEC,0x66,0x00,0x68,0x80,


    //TCON10  STV1
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON(10),
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0C,0x00,0x0E,0x01,0x20,0xF2,0x88,


    //TCON5  STV2
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON(5),
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0C,0x00,0x0E,0x01,0x20,0xF2,0x88,


    //TCON8  OE
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON(8),
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0C,0x10,0xEC,0xAA,0x22,0xEA,0x80,

    //4,  	_NON_AUTOINC,   	_DISP_ACCESS_PORT_2A,           	_DISP_TIMING_20,

    #endif

    _END
};

//--------------------------------------------------
BYTE code tLVDS_INITIAL[] =
{
    5,  	_AUTOINC,       	_TCON_ADDR_PORT_8B,             	_TCON_CTRL0_00,0x09,  
    4,  	_NON_AUTOINC,   	_TCON_ADDR_PORT_8B,             	_TCON_LVDS_CTRL0_A0,
#if( _2660_IC_VERB)
	9,  	_NON_AUTOINC,   	_TCON_DATA_PORT_8C,             	0x00,0xD7,0xc7,0x1c,0x80,0x80,
#else	 
    9,  	_NON_AUTOINC,   	_TCON_DATA_PORT_8C,             	0x00,0x17,0xc7,0x1c,0x80,0x80,
#endif    

    _END
};
//--------------------------------------------------
unsigned int  code tModeLimitTable[] =                //limit modem
{
	0,
    
};

//--------------------------------------------------
#if(_VGA_EDID)
BYTE code tVGA_EDID_DATA[] =
{
    0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x4a,0x8b,0x00,0x00,0x01,0x01,0x01,0x01,
    0x1e,0x0c,0x01,0x01,0x0e,0x24,0x1b,0x78,0xe8,0x8a,0x01,0x9a,0x58,0x52,0x8b,0x28,
    0x1e,0x50,0x54,0xff,0xff,0x80,0x61,0x40,0x61,0x4f,0x61,0x59,0x71,0x4f,0x81,0x40,
    0x81,0x59,0x81,0x99,0xa9,0x40,0x00,0x00,0x00,0xfc,0x00,0x31,0x37,0x27,0x27,0x20,
    0x4c,0x43,0x44,0x0a,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xfc,0x00,0x4d,0x6f,0x6e,
    0x69,0x74,0x6f,0x72,0x0a,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xfd,0x00,0x2b,
    0x55,0x14,0x5c,0x0e,0x00,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xff,
    0x00,0x30,0x30,0x30,0x30,0x30,0x31,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0xbd,
};
#endif

#if(_DVI_EDID)
BYTE code tDVI_EDID_DATA[] =
{
    0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x26,0xCD,0x68,0x46,0x00,0x00,0x00,0x00,
    0x23,0x0c,0x01,0x03,0x81,0x24,0x1D,0x78,0xeF,0x0D,0xC2,0xa0,0x57,0x47,0x98,0x27,
    0x12,0x48,0x4F,0xBF,0xEF,0x00,0x81,0x80,0x81,0x8F,0x61,0x40,0x61,0x59,0x45,0x40,
    0x45,0x59,0x31,0x40,0x31,0x59,0xBC,0x34,0x00,0x98,0x51,0x00,0x2A,0x40,0x10,0x90,
    0x13,0x00,0x68,0x22,0x11,0x00,0x00,0x1e,0x00,0x00,0x00,0xFF,0x00,0x30,0x0A,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,0x00,0x41,
    0x53,0x34,0x36,0x33,0x37,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFD,
    0x00,0x38,0x55,0x18,0x50,0x0E,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x06,
};
#endif

#else	// else of . #ifdef __MAIN__

extern code PanelType Panel;
extern WORD code tVIDEO_TABLE_INPUT_INFO[][5];
extern BYTE code tTTL_INITIAL[];
extern BYTE code tLVDS_INITIAL[];
extern WORD code tModeLimitTable[];

extern BYTE code tVGA_EDID_DATA[];
extern BYTE code tDVI_EDID_DATA[];

#endif	// endif of . #ifdef __MAIN__



#endif

