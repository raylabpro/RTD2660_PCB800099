//----------------------------------------------------------------------------------------------------
// ID Code      : EepromDefault.h No.0001
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#ifdef __EEPROM__

//--------------------------------------------------
// System Data Default Value
//--------------------------------------------------

code StructSystemDataType tEEPROM_SYSTEM_DATA =
{
    _MONITORFLAG,
    _INPUTSOURCE,
    _BACKLIGHT,
    _COLORTEMP,
    _SHARPNESS,
    _PEAKING_CORING,
    _USERFIFOMODE,
    _GAMMA,
    _COLORSETTING,
    _CCSYSTEM,
    _MODE,
    _FM_SETTING,
};

code StructICMColor tEEPROM_ICM_COLOR =
{
    _ICM_R_HUE,
    _ICM_R_SAT,
    _ICM_G_HUE,
    _ICM_G_SAT,
    _ICM_B_HUE,
    _ICM_B_SAT,
    _ICM_Y_HUE,
    _ICM_Y_SAT,
    _ICM_C_HUE,
    _ICM_C_SAT,
};

code StructOsdUserDataType tEEPROM_OSDUSER_DATA =
{
	_OSD_H_POSITION,
	_OSD_V_POSITION,
	_LANGUAGE,
	_OSD_TIMEOUT,
	_OSD_BLEND,
};


//--------------------------------------------------
//VGA ADC Gain/Offset Default Value
//--------------------------------------------------

code StructAdcDataType tEEPROM_ADC_DATA =
{
    _ADC_GAIN_RED,
    _ADC_GAIN_GREEN,
    _ADC_GAIN_BLUE,
    _ADC_OFFSET_RED,
    _ADC_OFFSET_GREEN,
    _ADC_OFFSET_BLUE,
};

//--------------------------------------------------
//YPbPr ADC Gain/Offset Default Value
//--------------------------------------------------

code StructYPbPrDataType tEEPROM_YPbPr_DATA =
{
    _YPbPr_GAIN_RED,
    _YPbPr_GAIN_GREEN,
    _YPbPr_GAIN_BLUE,
    _YPbPr_OFFSET_RED,
    _YPbPr_OFFSET_GREEN,
    _YPbPr_OFFSET_BLUE,
#if(_VIDEO_AUTO_WHITE_BLANCE == _ENABLE)
    _VDC_GAIN,				// VDC Contrast
    _VDC_OFFSET,			// VDC Brightness
    _VDC_CHOMA,				// VDC Saturation
#endif
};

//--------------------------------------------------
// Brightness/Contrast Default Value
//--------------------------------------------------
code StructColorProc0DataType tEEPROM_COLOR_PROC0_DATA[] =
{    
    // VGA
    _BRIGHTNESS_DEF,
    _CONTRAST_DEF,

    // DVI/HDMI
    _BRIGHTNESS_DEF,
    _CONTRAST_DEF,

    //VIDEO
    _BRIGHTNESS_DEF,
    _CONTRAST_DEF,

    // YPbPr
    _BRIGHTNESS_DEF,
    _CONTRAST_DEF,
};

//--------------------------------------------------
// Color Temperature Default Value
//--------------------------------------------------


code StructColorProc1DataType tEEPROM_COLORTEMP_DATA[] =
{
    // VGA
    {
        _CT9300_RED_VGA,
        _CT9300_GREEN_VGA,
        _CT9300_BLUE_VGA,
	}, 
    {	
        _CT6500_RED_VGA,
        _CT6500_GREEN_VGA,
        _CT6500_BLUE_VGA,
	}, 
    {	        
        _CT5800_RED_VGA,
        _CT5800_GREEN_VGA,
        _CT5800_BLUE_VGA,
	}, 
    {	        
        _CTSRGB_RED_VGA,
        _CTSRGB_GREEN_VGA,
        _CTSRGB_BLUE_VGA,
	}, 
    {	        
        _CTUSER_RED_VGA,
        _CTUSER_GREEN_VGA,
        _CTUSER_BLUE_VGA,
    },

    // DVI/HDMI
    {
        _CT9300_RED_DVI,
        _CT9300_GREEN_DVI,
        _CT9300_BLUE_DVI,
	}, 
    {	        
        _CT6500_RED_DVI,
        _CT6500_GREEN_DVI,
        _CT6500_BLUE_DVI,
	}, 
    {	        
        _CT5800_RED_DVI,
        _CT5800_GREEN_DVI,
        _CT5800_BLUE_DVI,
	}, 
    {	        
        _CTSRGB_RED_DVI,
        _CTSRGB_GREEN_DVI,
        _CTSRGB_BLUE_DVI,
	}, 
    {	        
        _CTUSER_RED_DVI,
        _CTUSER_GREEN_DVI,
        _CTUSER_BLUE_DVI,
    },

    // VIDEO
    {
		_CT9300_RED_VIDEO,
        _CT9300_GREEN_VIDEO,
        _CT9300_BLUE_VIDEO,
	}, 
    {	        
        _CT6500_RED_VIDEO,
        _CT6500_GREEN_VIDEO,
        _CT6500_BLUE_VIDEO,
	}, 
    {	        
        _CT5800_RED_VIDEO,
        _CT5800_GREEN_VIDEO,
        _CT5800_BLUE_VIDEO,
	}, 
    {	        
        _CTSRGB_RED_VIDEO,
        _CTSRGB_GREEN_VIDEO,
        _CTSRGB_BLUE_VIDEO,
	}, 
    {	        
        _CTUSER_RED_VIDEO,
        _CTUSER_GREEN_VIDEO,
        _CTUSER_BLUE_VIDEO,
    },

    // YPBPR
    {
		_CT9300_RED_YPBPR,
        _CT9300_GREEN_YPBPR,
        _CT9300_BLUE_YPBPR,
	}, 
    {	        
        _CT6500_RED_YPBPR,
        _CT6500_GREEN_YPBPR,
        _CT6500_BLUE_YPBPR,
	}, 
    {	        
        _CT5800_RED_YPBPR,
        _CT5800_GREEN_YPBPR,
        _CT5800_BLUE_YPBPR,
	}, 
    {	        
        _CTSRGB_RED_YPBPR,
        _CTSRGB_GREEN_YPBPR,
        _CTSRGB_BLUE_YPBPR,
	}, 
    {	        
        _CTUSER_RED_YPBPR,
        _CTUSER_GREEN_YPBPR,
        _CTUSER_BLUE_YPBPR,
    },

};
code BYTE tEEPROM_USER_FIFO_MODE_DEFAULT[] =
{
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
};

//--------------------------------------------------
// TV Default Value
//--------------------------------------------------

code StructTvDataType tEEPROM_TV_DATA =
{
	_TV_DEFAULT_CH_NUM,
    _FM_DEFAULT_CH_NUM,
	_TV_DEFAULT_SET_FLAG,
    _TV_DEFAULT_MAX_CHANNEL,
};


// Audio Default Value
code StructAudioDataType tEEPROM_AUDIO_DATA =
{
	_AUDIO_Mode,
	_AUDIO_Volume,
	_AUDIO_Balance,
	_AUDIO_Bass,
	_AUDIO_Treble,
	_AUDIO_Woofer,
};

//--------------------------------------------------
// Hue/Saturation Default Value
//--------------------------------------------------
code StructHueSaturationDataType tEEPROM_HUE_SAT_DATA[] =
{
    // VGA
    _HUE_DEF,     
    _SATURATION_DEF,

    // DVI/HDMI
    _HUE_DEF,     
    _SATURATION_DEF,

    //VIDEO
    _HUE_DEF,     
    _SATURATION_DEF,

    // YPbPr
    _HUE_DEF,     
    _SATURATION_DEF,
};


#else

extern code StructSystemDataType tEEPROM_SYSTEM_DATA;
extern code StructOsdUserDataType tEEPROM_OSDUSER_DATA;
extern code StructAdcDataType tEEPROM_ADC_DATA;
extern code StructYPbPrDataType tEEPROM_YPbPr_DATA;
extern code StructColorProc0DataType tEEPROM_COLOR_PROC0_DATA[];
extern code StructColorProc1DataType tEEPROM_COLORTEMP_DATA[];
extern code BYTE tEEPROM_USER_FIFO_MODE_DEFAULT[];
extern code StructTvDataType tEEPROM_TV_DATA;
extern code StructAudioDataType tEEPROM_AUDIO_DATA;
extern code StructHueSaturationDataType tEEPROM_HUE_SAT_DATA[];

#endif

