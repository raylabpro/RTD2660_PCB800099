//----------------------------------------------------------------------------------------------------
// ID Code      : EepromDefault.h No.0001
// Update Note  :
//
//----------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------
// System Data Default Value
// They are used by tEEPROM_SYSTEM_DATA & tEEPROM_ICM_COLOR in the EepromDefault.h
//---------------------------------------------------------------------------------
#define _MONITORFLAG            	(0xc0|_DISPMODE_FULL)
#define _INPUTSOURCE            	_NORMAL_SOURCE
#define _BACKLIGHT              	80
#define _COLORTEMP              	_CT_6500//0x04

#define _SHARPNESS              	0x02
#define _USERFIFOMODE           	0x0f
#define _PEAKING_CORING             50
#define _YPbPrHue               	60
#define _YPbPrSaturation        	80
#define _CONTRAST					50
#define _BRIGHTNESS					50
#define _GAMMA						(0x03|0x80)//0x00 Set VGA mode to 720x400x70hz
#define _COLORSETTING				0x0C    // set default DCC mode = 3
#define _CCSYSTEM					0x00
#define _MODE                       0x00
#define _FM_SETTING					0x01

#define _ICM_R_HUE					0x08
#define _ICM_R_SAT					0x08
#define _ICM_G_HUE					0x08
#define _ICM_G_SAT					0x08
#define _ICM_B_HUE					0x08
#define _ICM_B_SAT					0x08
#define _ICM_Y_HUE					0x08
#define _ICM_Y_SAT					0x08
#define _ICM_C_HUE					0x08
#define _ICM_C_SAT					0x08

//--------------------------------------------------
// OSD User Data Default Value
// They are used by tEEPROM_OSDUSER_DATA
//--------------------------------------------------

#define _OSD_H_POSITION             0x32
#define _OSD_V_POSITION             0x32


#define _LANGUAGE                   0x00
#define _OSD_TIMEOUT                0x0a
#define _VOLUME                     0x20
#define _FILTER                     0x00
#define _OSD_BLEND					0x00


//--------------------------------------------------
// VGA ADC Gain/Offset Default Value
// They are used by tEEPROM_ADC_DATA
//--------------------------------------------------
#define _ADC_GAIN_RED               0x80
#define _ADC_GAIN_GREEN             0x80
#define _ADC_GAIN_BLUE              0x80
#define _ADC_OFFSET_RED             0x80
#define _ADC_OFFSET_GREEN           0x80
#define _ADC_OFFSET_BLUE            0x80

//--------------------------------------------------
// YPbPr ADC Gain/Offset Default Value
// They are used by tEEPROM_YPbPr_DATA
//--------------------------------------------------
#define _YPbPr_GAIN_RED               	0x80
#define _YPbPr_GAIN_GREEN             	0x80
#define _YPbPr_GAIN_BLUE              	0x80
#define _YPbPr_OFFSET_RED             	0x7C
#define _YPbPr_OFFSET_GREEN           	0xA7
#define _YPbPr_OFFSET_BLUE            	0x84
#define _VDC_GAIN						0x80// VDC Contrast
#define _VDC_OFFSET						0x80// VDC Brightness
#define _VDC_CHOMA						0xA0// VDC Saturation

//--------------------------------------------------
// Brightness/Contrast Default Value
// They are used by tEEPROM_COLOR_PROC0_DATA
//--------------------------------------------------
#define _BRIGHTNESS_DEF                 0x32
#define _CONTRAST_DEF                   0x32

//--------------------------------------------------
// Color Temperature Default Value
// They are used by tEEPROM_COLORTEMP_DATA
//--------------------------------------------------
// VGA
// weixg mod 20070515 
#define _CT9300_RED_VGA             	108
#define _CT9300_GREEN_VGA           	113
#define _CT9300_BLUE_VGA            	121
#define _CT6500_RED_VGA             	121
#define _CT6500_GREEN_VGA           	128
#define _CT6500_BLUE_VGA            	115
#define _CT5800_RED_VGA             	121
#define _CT5800_GREEN_VGA           	128
#define _CT5800_BLUE_VGA            	105
#define _CTSRGB_RED_VGA             	0x75
#define _CTSRGB_GREEN_VGA           	0x80
#define _CTSRGB_BLUE_VGA            	0x73
#define _CTUSER_RED_VGA             	0x80
#define _CTUSER_GREEN_VGA           	0x80
#define _CTUSER_BLUE_VGA            	0x80

// DVI/HDMI
#define _CT9300_RED_DVI             	108
#define _CT9300_GREEN_DVI           	113
#define _CT9300_BLUE_DVI            	121
#define _CT6500_RED_DVI             	120
#define _CT6500_GREEN_DVI           	128
#define _CT6500_BLUE_DVI            	115
#define _CT5800_RED_DVI             	121
#define _CT5800_GREEN_DVI           	128
#define _CT5800_BLUE_DVI            	105
#define _CTSRGB_RED_DVI             	0x75
#define _CTSRGB_GREEN_DVI           	0x80
#define _CTSRGB_BLUE_DVI            	0x73
#define _CTUSER_RED_DVI             	0x80
#define _CTUSER_GREEN_DVI           	0x80
#define _CTUSER_BLUE_DVI            	0x80

// VIDEO
#define _CT9300_RED_VIDEO           	0x80
#define _CT9300_GREEN_VIDEO         	0x80
#define _CT9300_BLUE_VIDEO          	0x80
#define _CT6500_RED_VIDEO           	0x80
#define _CT6500_GREEN_VIDEO         	0x80
#define _CT6500_BLUE_VIDEO          	0x80
#define _CT5800_RED_VIDEO           	0x80
#define _CT5800_GREEN_VIDEO         	0x80
#define _CT5800_BLUE_VIDEO          	0x80
#define _CTSRGB_RED_VIDEO           	0x80
#define _CTSRGB_GREEN_VIDEO         	0x80
#define _CTSRGB_BLUE_VIDEO          	0x80
#define _CTUSER_RED_VIDEO           	0x80
#define _CTUSER_GREEN_VIDEO         	0x80
#define _CTUSER_BLUE_VIDEO          	0x80

// YPBPR
#define _CT9300_RED_YPBPR           	0x80
#define _CT9300_GREEN_YPBPR         	0x80
#define _CT9300_BLUE_YPBPR          	0x80
#define _CT6500_RED_YPBPR           	0x80
#define _CT6500_GREEN_YPBPR         	0x80
#define _CT6500_BLUE_YPBPR          	0x80
#define _CT5800_RED_YPBPR           	0x80
#define _CT5800_GREEN_YPBPR         	0x80
#define _CT5800_BLUE_YPBPR          	0x80
#define _CTSRGB_RED_YPBPR           	0x80
#define _CTSRGB_GREEN_YPBPR         	0x80
#define _CTSRGB_BLUE_YPBPR          	0x80
#define _CTUSER_RED_YPBPR           	0x80
#define _CTUSER_GREEN_YPBPR         	0x80
#define _CTUSER_BLUE_YPBPR          	0x80

//--------------------------------------------------
// TV Default Value
// They are used by tEEPROM_TV_DATA
//--------------------------------------------------
#define _TV_DEFAULT_CH_NUM     	        0x01
#define _FM_DEFAULT_CH_NUM              0x00
#define _TV_DEFAULT_SET_FLAG   	        0x80
#define _TV_DEFAULT_MAX_CHANNEL         0x01

//---------------------------------------------------
// Audio defualt value
// They are used by tEEPROM_AUDIO_DATA
//---------------------------------------------------
#define _AUDIO_Mode				        0x00
#define _AUDIO_Volume				    50
#define _AUDIO_Balance				    50
#define _AUDIO_Bass					    50
#define _AUDIO_Treble				    50
#define _AUDIO_Woofer				    0x00


//---------------------------------------------------
// Hue/Saturation defualt value
// They are used by tEEPROM_HUE_SAT_DATA
//---------------------------------------------------
#define _HUE_DEF                        50
#define _SATURATION_DEF                 50



