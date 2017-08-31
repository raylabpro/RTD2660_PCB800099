//----------------------------------------------------------------------------------------------------
// ID Code      : Struct.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------
#include "Core\Header\Maindef.h"

#define _SET_INPUT_SOURCE(value)        (stSystemData.InputSource = value)
#define _GET_INPUT_SOURCE()             stSystemData.InputSource

#define _GET_BLUE_BACKGROUND()          1//((stSystemData.MonitorFlag & _BIT5) >> 5)
#define _SET_BLUE_BACKGROUND(x)         stSystemData.MonitorFlag = (stSystemData.MonitorFlag & (~_BIT5)) | (x << 5)

#define _BURNIN_ON						_BIT2
#define _BURNIN_OFF						0x00	

#define GET_BURNIN_STATE()          	(stSystemData.MonitorFlag & _BIT2)
#define SET_BURNIN_STATE(x)             stSystemData.MonitorFlag = (stSystemData.MonitorFlag & (~_BIT2)) | (x << 2)

#define _DISPMODE_FULL					0
#define _DISPMODE_43					1
#define _DISPMODE_AUTO					2

#define GET_DISPLAYMODE()				(stSystemData.MonitorFlag & 0x03)
#define SET_DISPLAYMODE(x)				stSystemData.MonitorFlag = ((stSystemData.MonitorFlag & 0xFC) | x) 

#define GET_OSD_SIZE()   				(stSystemData.MonitorFlag & _BIT3)
#define SET_OSD_SIZE(x)  				stSystemData.MonitorFlag = ((stSystemData.MonitorFlag & (~_BIT3)) | (x << 3)) 

#define _GET_POWER_DOWN_TIME()          ((stTvInfo.TvSettingFlag >> 2) & 0x0F)
#define _SET_POWER_DOWN_TIME(x)         stTvInfo.TvSettingFlag = (stTvInfo.TvSettingFlag & 0xC3) | (x << 2)

#define _TV_CATV                        0
#define _TV_AIR                         1
#define _GET_TV_TYPE()                  ((stTvInfo.TvSettingFlag >> 6) & 0x01)
#define _SET_TV_TYPE(x)                 stTvInfo.TvSettingFlag = (stTvInfo.TvSettingFlag & (~_BIT6)) | (x << 6)

//--------------------------------------------------
// Macro of Color Temperature
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE()           (stSystemData.ColorTemp & (_BIT3 | _BIT2 | _BIT1 | _BIT0))
#define SET_COLOR_TEMP_TYPE(x)          (stSystemData.ColorTemp = ((stSystemData.ColorTemp & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | x))

#define _CT_9300						0
#define _CT_6500						1
#define _CT_5800						2
#define _CT_SRGB						3
#define _CT_USER						4


#define GET_LR_SWAP()					((stSystemData.ColorTemp & _BIT4) >> 4)			
#define SET_LR_SWAP(x)					stSystemData.ColorTemp = (stSystemData.ColorTemp & (~_BIT4)) | (x << 4)

#define GET_UD_SWAP()					((stSystemData.ColorTemp & _BIT5) >> 5)
#define SET_UD_SWAP(x)					stSystemData.ColorTemp = (stSystemData.ColorTemp & (~_BIT5)) | (x << 5)

//--------------------------------------------------
// Struct Type
//--------------------------------------------------
typedef struct
{
    UINT8 PolarityFlag;              
    UINT16 IHWidth;                   // Input Horizontal Width
    UINT16 IVHeight;                  // Input Vertical Height
    UINT16 IHFreq;                    // Input Horizontal Frequency
    UINT16 IVFreq;                    // Input Vertical Frequency
    UINT8 IHFreqTolerance;            // Input Horizontal Frequency Tolerance
    UINT8 IVFreqTolerance;            // Input Vertical Frequency Tolerance
    UINT16 IHTotal;                   // Input Horizontal Total Length
    UINT16 IVTotal;                   // Input Vertical Total Length
    UINT16 IHStartPos;                // Input Horizontal Start Position
    UINT16 IVStartPos;                // Input Vertical Start Position

} ModeTableType;
//------------------------------------------------------
typedef struct
{
    UINT16 DHTotal;                   // Display Horizontal Total Length
    UINT16 DHWidth;                   // Display Horizontal Width
    UINT16 DVHeight;                  // Display Vertical Height
    UINT16 DVStartPos;                // Display Vertical Start Position

} DisplayTableType;
//------------------------------------------------------
typedef struct
{
    UINT8 ModeCurr;                   // Input Mode
    UINT8 Polarity;                   // BIT0: H Polarity, Bit1: V Polarity
    UINT16 IHFreq;                    // Input Horizontal Frequency
    UINT16 IVFreq;                    // Input Vertical Frequency
    UINT16 IHTotal;                   // Input Horizontal Total Length
    UINT16 IVTotal;                   // Input Vertical Total Length
    UINT16 IHWidth;                   // Input Horizontal Width
    UINT16 IVHeight;                  // Input Vertical Height
    UINT16 IHStartPos;                // Input Horizontal Start Position
    UINT16 IVStartPos;                // Input Vertical Start Position
    UINT16 IHCount;                   // Input Horizontal Count Numbers
    UINT16 IHSyncPulseCount;          // Input Horizontal Sync Pulse Count Numbers

} ModeInformationType;
//------------------------------------------------------
typedef struct
{
    UINT8 PanelStyle;                 // 0  Panel Style
    UINT8 PanelConfig;                // 2  Panel Configuration 

    UINT16 DHStartPos;                // 9  Display Horizontal Start Position
    UINT16 DHWidth;                   // 19 Display Horizontal Width

    UINT16 DHTotal;                   // 6  Display Horizontal Total Clock Number in One Display Line

    UINT16 DVStartPos;                // 10 Display Vertical Start Position
    UINT16 DVHeight;                  // 13 Display Vertical Height

    UINT16 DVTotal;                   // 4  Display Vertical Total Line Number in One Frame

    UINT8 DHSyncWidth;                // 1  Display H Sync Width
    UINT8 DVSyncHeight;               // 1  Display V Sync Height

    UINT16 PixelClock;                // 1  Typical Pixel Clock in MHz

    UINT16 HSyncMaxFreq;              // H Sync Max Freq Unit in 0.1 kHZ
    UINT16 HSyncMinFreq;              // H Sync Min Freq Unit in 0.1 kHZ
    UINT16 VSyncMaxFreq;              // V Sync Max Freq Unit in 0.1 HZ
    UINT16 VSyncMinFreq;              // V Sync Min Freq Unit in 0.1 HZ

    // For TV
    // PAL
    UINT16 PalDHTotal;                // Display Horizontal Total Clock Number in One Display Line for CVBS PAL

#if(_VIDEO_TV_SUPPORT)
    UINT8  PalIVDV40;                 // IVS to DVS Delay Lines
    UINT8  PalIVDV41;                 // Frame Sync Delay Fine Tuning ODD
    UINT8  PalIVDV42;                 // Frame Sync Delay Fine Tuning EVEN
    UINT8  PalIVDV43;                 // Frame Sync Delay Fine Tuning Control Register
    UINT8  PalP1C4;                   // Display Clock Fine Tune Offset MSB
    UINT8  PalP1C5;                   // Display Clock Fine Tune Offset LSB
#endif

    // NTSC
    UINT16 NtscDHTotal;               // Display Horizontal Total Clock Number in One Display Line for CVBS NTSC
#if(_VIDEO_TV_SUPPORT)
    UINT8  NtscIVDV40;                // IVS to DVS Delay Lines
    UINT8  NtscIVDV41;                // Frame Sync Delay Fine Tuning ODD
    UINT8  NtscIVDV42;                // Frame Sync Delay Fine Tuning EVEN
    UINT8  NtscIVDV43;                // Frame Sync Delay Fine Tuning Control Register
    UINT8  NtscP1C4;                  // Display Clock Fine Tune Offset MSB
    UINT8  NtscP1C5;                  // Display Clock Fine Tune Offset LSB
#endif

    UINT8 TTL20;

} PanelType;
//------------------------------------------------------

typedef struct
{
    UINT8 FirstAuto;                  // First Auto
    UINT16 HPosition;                 // Horizontal Position
    UINT16 VPosition;                 // Vertical Position
    UINT16 Clock;                     // Clock Adjust
    UINT8 Phase;                      // Phase Adjust

} StructModeUserDataType;
//------------------------------------------------------
typedef struct
{
    UINT8 ModeNum;                    // Mode Number
    UINT16 IHFreq;                    // Input Horizontal Frequency
    UINT16 IVFreq;                    // Input Vertical Frequency

} StructModeUserFIFODataType;
//------------------------------------------------------
typedef struct
{
    UINT16 CenterHPos;                // Horizontal Position
    UINT16 CenterVPos;                // Vertical Position
    UINT16 CenterClock;               // Clock Adjust

} StructModeUserCenterDataType;
//------------------------------------------------------
typedef struct
{
	UINT8 MonitorFlag;	   			// Bit 7: Monitor Power Status
      	                            // Bit 6: DVI-I/VGA switch flag
      	                            // Bit 5: Blue background 0-> Disable  1->Enable
      	                            // Bit 4: Display Mode    0-> Full     1-> 4:3
      	                            // Bit 3: OSD Size        0-> Normal   1-> Double
                                    // Bit 2: Reserved
                                    // Bit 1: Reserved
                                    // Bit 0: Reserved

	UINT8 InputSource;
	UINT8 BackLight;
	UINT8 ColorTemp;
	UINT8 Sharpness;
		//bit 7~4  Peaking-Coring
		//  		[ 000b: Disable]
		//  		[ 001b: Mode 1	]
		//  		[ 010b: Mode 2	]
		//  		[ 011b: Mode 3	]
		//  		[ 100b: Mode 4	]
		//bit 3~0	[ Sharpness		]
		//  		[ 000b: Disable]
		//  		[ 001b: Mode 1	]
		//  		[ 010b: Mode 2	]
		//  		[ 011b: Mode 3	]
		//  		[ 100b: Mode 4	]
    UINT8 PeakingCoring;

	UINT8 UserFIFOMode;

	UINT8 Gamma;
		// Bit 0: NR[1: On / 0:Off]
		// Bit 1: Reserved
        //bit 3~2   [ BACK COLOR ]
        //          [ 00 : RED       ]
        //          [ 01 : GREEN      ]
        //          [ 10 : BLUE ]
		//bit 4~6	[ Gamma			]
		//  		[ 000b: Disable	]
		//  		[ 001b: Gamma 1	]
		//  		[ 010b: Gamma 2	]
		//  		[ 011b: Gamma 3	]
		//  		[ 100b: Gamma 4	]
      	// Bit 7: DOS mode select

	UINT8 ucColorSetting;
		// bit 7 [Black Level Expansion	]
		// bit 6 [Auto Image			]
		// bit 5 [Flesh Tone			]
		// bit 4 [Reserved              ][NonLinear Enable		]
		// bit 3~1[DCC Mode			]
		// 		[ 000b: Disable		]
		//  	[ 001b: Mode 1		]
		//  	[ 010b: Mode 2		]
		//  	[ 011b: Mode 3		]
		//  	[ 100b: Mode 4		]
		//      [101b~111b: Reserved  ]
		// bit 0 [ICM  0: Disable 1: Enable  ]

	UINT8 CcSystem;
		//bit 7~4 	[ Nonlinear Scaling]
        //         	[ 00b : Off        ]
        //         	[ 01 ~ 10 On       ]
		// bit 3~0
		//		0: ccmute
		// 		1: CC1, 2:CC2, 3:CC3, 4:CC4,
		//		5: TT1, 6:TT2, 7:TT3, 8:TT4
	UINT8 Mode;//use for picture mode and audio mode  
               //-------picture mode--------
		//bit 7~4	[0: standard			标准]
		//			[1: bright				亮丽]
		//			[2: MILD				柔和]
		//			[3: movie			    电影]
		//			[4: user				用户]  
		//--------audio mode---------
		//bit 0~3		[0: standard		标准]
		//			[1: THEATER			    影院]
		//			[2: music				音乐]
		//			[3: news				新闻]
		//			[3: user				用户]
		//---------------------------------------

	UINT8 FMSetting;
} StructSystemDataType;
//------------------------------------------------------
typedef struct
{
	UINT8 ICM_COLOR[10];	  //0~9 use for RGBYC

}StructICMColor;
//------------------------------------------------------

typedef struct 
{
    BYTE KeyMessage;
    BYTE OsdEvent;
}SKeyToOsdEvent;
//------------------------------------------------------
// FM
//--------------------------------------------------
#define _FM_OFF							0x01
#define _FM_A1							0x02
#define _FM_A2							0x03
#define _FM_A3							0x04
#define _FM_A4							0x05
#define _FM_A5							0x06
#define _FM_A6							0x07
#define _FM_A7							0x08
#define _FM_A8							0x09
#define _FM_B1							0x0a
#define _FM_B2							0x0b
#define _FM_B3							0x0c
#define _FM_B4							0x0d
#define _FM_B5							0x0e
#define _FM_B6							0x0f
#define _FM_B7							0x10
#define _FM_B8							0x11

#define _GET_FM_STATE()					(stSystemData.FMSetting)
#define _SET_FM_STATE(x) 				    (stSystemData.FMSetting = x)


#define GET_DCC_MODE()					    ((stSystemData.ucColorSetting & (_BIT3 | _BIT2 | _BIT1)) >> 1)
#define SET_DCC_MODE(x) 				    (stSystemData.ucColorSetting = (stSystemData.ucColorSetting & ~(_BIT3 | _BIT2 | _BIT1)) | (x<<1))


#define GET_ICM_on_off()				    ((stSystemData.ucColorSetting & _BIT0))
#define SET_ICM_on_off() 				    (stSystemData.ucColorSetting |=( _BIT0))
#define CLR_ICM_on_off() 				    (stSystemData.ucColorSetting &= (~_BIT0))
//Video / TV
#define GET_ICM_HUE_R()				        (stICMColor.ICM_COLOR[0])
#define GET_ICM_HUE_G()				        (stICMColor.ICM_COLOR[1])
#define GET_ICM_HUE_B()				        (stICMColor.ICM_COLOR[2])
#define GET_ICM_HUE_Y()				        (stICMColor.ICM_COLOR[3])
#define GET_ICM_HUE_C()				        (stICMColor.ICM_COLOR[4])
#define GET_ICM_SAT_R()                     (stICMColor.ICM_COLOR[5])
#define GET_ICM_SAT_G()                     (stICMColor.ICM_COLOR[6])
#define GET_ICM_SAT_B()                     (stICMColor.ICM_COLOR[7])
#define GET_ICM_SAT_Y()                     (stICMColor.ICM_COLOR[8])
#define GET_ICM_SAT_C()                     (stICMColor.ICM_COLOR[9])

#define SET_NONLINEAR_VALUE(x)              (stSystemData.CcSystem = stSystemData.CcSystem & 0x0f | ((x & 0x0f) << 4))
#define GET_NONLINEAR_VALUE()               ((stSystemData.CcSystem & 0xf0) >> 4)
#define CLR_NONLINEAR_VALUE()               (stSystemData.CcSystem & 0x0f)

#define GET_GAMMA()                         ((stSystemData.Gamma & (_BIT4 | _BIT5 | _BIT6)) >> 4)
#define SET_GAMMA(x)                        (stSystemData.Gamma = (stSystemData.Gamma & ~(_BIT4 | _BIT5 | _BIT6)) | ((x & (_BIT0 | _BIT1 | _BIT2)) << 4))

#define GET_BACKGROUNDCOLOE()               ((stSystemData.Gamma & (_BIT2 | _BIT3)) >> 2)
#define SET_BACKGROUNDCOLOE(x)              (stSystemData.Gamma = (stSystemData.Gamma & ~(_BIT2 | _BIT3)) | ((x & (_BIT0 | _BIT1)) << 2))

#define GET_NOISEREDUTION()                 (stSystemData.Gamma & (_BIT0))
#define SET_NOISEREDUTION(x)                (stSystemData.Gamma = (stSystemData.Gamma & ~(_BIT0)) | x)

#define GET_PEAKING_CORING()                (stSystemData.PeakingCoring)
#define SET_PEAKING_CORING(x)               (stSystemData.PeakingCoring = x)

#define GET_SHARPNESS()                     (stSystemData.Sharpness & (_BIT0 | _BIT1 | _BIT2 | _BIT3))
#define SET_SHARPNESS(x)                    (stSystemData.Sharpness = (stSystemData.Sharpness & ~(_BIT0 | _BIT1 | _BIT2 | _BIT3)) | x)

#define GET_HUE()                           (stHueSatData.Hue)
#define SET_HUE(x)                          (stHueSatData.Hue = x);
#define GET_SATURATION()                    (stHueSatData.Saturation)
#define SET_SATURATION(x)                   (stHueSatData.Saturation = x)
#define GET_CONTRAST()                      (stConBriData.Contrast)
#define SET_CONTRAST(x)                     (stConBriData.Contrast = x)

#define GET_MODESELECT_TYPE()	            (BIT)(stSystemData.Gamma & _BIT7)
#define SET_MODESELECT_TYPE(x) 	            (stSystemData.Gamma =  (stSystemData.Gamma & ~_BIT7) | (x<<7))


#define GET_AFC_MODE()                      (stTvInfo.TvSettingFlag >> 7)
#define SET_AFC_MODE(x)                     (stTvInfo.TvSettingFlag = (stTvInfo.TvSettingFlag & 0x7F) | (x << 7))

typedef struct
{

    UINT8 OsdHPos;
    UINT8 OsdVPos;
    UINT8 Language;
    UINT8 OsdTimeout;
    UINT8 OsdBlending;
} StructOsdUserDataType;

#define NoSignalAutoOff_Enable	1
#define NoSignalAutoOff_Disable	0

#define GET_OSDTIMEOUT() 							(stOsdUserData.OsdTimeout)
#define SET_OSDTIMEOUT(x) 							(stOsdUserData.OsdTimeout = x)
#define SET_OSDUSERHPOS(x) 							(stOsdUserData.OsdHPos= x)
#define SET_OSDUSERVPOS(x) 							(stOsdUserData.OsdVPos= x)
#define GET_OSDBLENDING() 							(stOsdUserData.OsdBlending)
#define SET_OSDBLENDING(x) 							(stOsdUserData.OsdBlending = x)

typedef struct
{
    UINT8 AdcGain[3];
    UINT8 AdcOffset[3];
} StructAdcDataType;

typedef struct
{
    UINT8 YPbPrGain[3];
    UINT8 YPbPrOffset[3];
#if(_VIDEO_AUTO_WHITE_BLANCE == _ENABLE)
    UINT8 VDCGain;
    UINT8 VDCOffset;
    UINT8 VDCChroma;
#endif
}StructYPbPrDataType;

#if(_VIDEO_AUTO_WHITE_BLANCE == _ENABLE)
#define GET_VDC_GAIN() 		                (stYPbPrData.VDCGain)
#define SET_VDC_GAIN(x) 	                (stYPbPrData.VDCGain= x)
#define GET_VDC_OFFSET() 	                (stYPbPrData.VDCOffset)
#define SET_VDC_OFFSET(x) 	                (stYPbPrData.VDCOffset= x)
#define GET_VDC_CHROMA() 	                (stYPbPrData.VDCChroma)
#define SET_VDC_CHROMA(x) 	                (stYPbPrData.VDCChroma= x)
#endif

typedef struct			// for D-sub and DVI
{
    UINT8 Brightness;
    UINT8 Contrast;

} StructColorProc0DataType;

typedef struct
{
    UINT8 ColorTemp[3];
} StructColorProc1DataType;

typedef struct
{
    UINT8 ColorTemp9300Red;
    UINT8 ColorTemp9300Green;
    UINT8 ColorTemp9300Blue;

    UINT8 ColorTemp6500Red;
    UINT8 ColorTemp6500Green;
    UINT8 ColorTemp6500Blue;

    UINT8 ColorTemp5800Red;
    UINT8 ColorTemp5800Green;
    UINT8 ColorTemp5800Blue;

    UINT8 ColorTempsRGBRed;
    UINT8 ColorTempsRGBGreen;
    UINT8 ColorTempsRGBBlue;

    UINT8 ColorTempUserRed;
    UINT8 ColorTempUserGreen;
    UINT8 ColorTempUserBlue;
} StructColorTempDataType;

//--------------------------------------------------
// TV information Struct
//--------------------------------------------------
typedef struct
{
	UINT8 CurChn;
    UINT8 ucFMCurrCh;
	UINT8 TvSettingFlag;
		// Bit 7:  AFC  0: OFF
        //              1: ON
		// Bit 6:  0: CATV
        //         1: AIR
		// Bit 5~2 Auto power down
        //        0: Auto power down off
        //        1: 15 Minute
        //        2: 30 Minute
        //        3: 45 Minute
        //        4: 60 Minute
        //        5: 75 Minute
        //        6: 90 Minute
        //        7: 105 Minute
        //        8: 120 Minute

		// Bit 1~0: Input channel state
        //        00: Input one channel   -
        //        01: Input two channel   --
        //        02: Input three channel ---  

    BYTE ucMaxChannel;

} StructTvDataType;
#define GET_INPUTCH_STATE()         (stTvInfo.TvSettingFlag & 0x03)
#define SET_INPUTCH_STATE(x)        stTvInfo.TvSettingFlag = (stTvInfo.TvSettingFlag & 0xFC) | x

#define _GET_MAX_CHANNEL()          (stTvInfo.ucMaxChannel)
#define _SET_MAX_CHANNEL(channel)   stTvInfo.ucMaxChannel = channel

typedef struct
{
	BYTE TYPE;
	// 0 ~ 3: sound type
	// 4 ~ 7: color type
	
	WORD Freq;
    // bit 0~14:    channel freq
    // bit 15: Skip    0-> no skip  1->skip
} StructTvInformationData;
#define _GET_CH_COLOR_TYPE()       (stTVChannelInfo.TYPE >> 4)
#define _SET_CH_COLOR_TYPE(color)  stTVChannelInfo.TYPE = (stTVChannelInfo.TYPE & 0x0F) | (color << 4)

#define _GET_CH_SOUND_TYPE()       (stTVChannelInfo.TYPE & 0x0F)
#define _SET_CH_SOUND_TYPE(sound)  stTVChannelInfo.TYPE = (stTVChannelInfo.TYPE & 0xF0) | sound

#define _GET_CH_FREQ()             (stTVChannelInfo.Freq & 0x7FFF)
#define _SET_CH_FREQ(freq)         stTVChannelInfo.Freq = (stTVChannelInfo.Freq & 0x8000) | freq

#define _GET_CH_SKIP()             ((stTVChannelInfo.Freq >> 15))
#define _SET_CH_SKIP(skip)         stTVChannelInfo.Freq = (stTVChannelInfo.Freq & 0x7FFF) | (skip << 15)


typedef struct 
{
	UINT8 Mode;	// General Audio Mode
		//bit 7~6 	 Reserved
		//bit 5~4 	 color MODE
		//bit 3~2	[ MTS				]
		//  		[ 00b: Mono		    ]
		//  		[ 01b: Stereo		]
		//  		[ 10b: SAP			]
		//  		[ 11b: Dual		    ]
		//bit 1	    [ Mute on/off ctrl	]
		//		    [ 0: Mute off		]
		//		    [ 1: Mute On		]
		//bit 0	    [ Audio Destination	]
		//  		[ 0: Loudspeaker	]
		//  		[ 1: Earphone		]
	UINT8 Volume;	// based on Audio Dst (bit 0 of Mode)
	UINT8 Balance;		// Balance value of each output channel
	UINT8 Bass;			// Bass value of each output channel
	UINT8 Treble;		// Treble value of each output channel
	UINT8 Woofer;		// Woofer value for loudspeaker
} StructAudioDataType;

#define _CM_NORMAL					0
#define _CM_SOFT					1
#define _CM_VIVID					2
#define _CM_USER					3

#define GET_COLOR_MODE()			((stSystemData.Mode & (_BIT5 | _BIT4)) >> 4)
#define SET_COLOR_MODE(x)			stSystemData.Mode = (stSystemData.Mode & (~(_BIT5 | _BIT4))) | (x << 4)

#define _AUDIO_NORMAL				0
#define _AUDIO_THEATER				1
#define _AUDIO_MUSIC				2
#define GET_AUDIO_MODE()			(stSystemData.Mode & (_BIT1 | _BIT0))
#define SET_AUDIO_MODE(x)			stSystemData.Mode = (stSystemData.Mode & (~(_BIT1 | _BIT0))) | x 

#define GET_AUDIO_MUTE()            ((stAudioData.Mode & _BIT1) >> 1)
#define SET_AUDIO_MUTE()            (stAudioData.Mode |= (_BIT1))
#define CLR_AUDIO_MUTE()            (stAudioData.Mode = stAudioData.Mode & (~_BIT1))
#define GET_VOLUME()                (stAudioData.Volume)
#define SET_VOLUME(x)               (stAudioData.Volume = x)


//--------------------------------------------------
// Timer Struct
//--------------------------------------------------
struct CTimerEventTable
{
    UINT16 Time;
    void (*Event)(void);
};

typedef struct		
{
    UINT8 Hue;
    UINT8 Saturation;
} StructHueSaturationDataType;


//--------------------------------------------------
// Extern Global Struct Variables
//--------------------------------------------------
extern StructModeUserDataType       xdata   stModeUserData;
extern StructModeUserCenterDataType xdata   stModeUserCenterData;
extern StructSystemDataType         xdata   stSystemData;
extern StructOsdUserDataType        xdata   stOsdUserData;
extern StructAdcDataType            xdata   stAdcData;
extern StructYPbPrDataType          xdata   stYPbPrData;
extern StructColorProc0DataType     xdata   stConBriData;
extern StructColorProc1DataType     xdata   stColorTempData;
extern ModeInformationType          idata   stModeInfo;
extern DisplayTableType             idata   stDisplayInfo;
extern StructTvDataType		    	xdata   stTvInfo;
extern StructAudioDataType 	    	xdata   stAudioData;
extern StructHueSaturationDataType  xdata   stHueSatData;
extern StructTvInformationData      xdata   stTVChannelInfo;
extern code StructICMColor stICMColor;
