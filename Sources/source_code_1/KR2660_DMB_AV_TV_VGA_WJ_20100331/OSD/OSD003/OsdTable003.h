#if(_OSD_TYPE == _OSD003)


#define ROW_COUNT    						15
#define COL_WIDTH    						30

#define _MAINMENU_WITDH						348
#define _MAINMENU_HEIGHT					72
#define _MAINMENU_XPostion				    50
#define _MAINMENU_YPostion					90

#define FONT_BASE_ADDRESS					0x300



enum
{
	// Strings
	_MI_MENU_NONE,

	// MainMenu
	_MI_CONTRAST,
	_MI_BRIGHTNESS,	
	_MI_SATURATION,
	_MI_HUE,
	_MI_VOLUME,
    	_MI_ATUOADJ,    	
	_MI_SOURCE,
	_MI_LANGUAGE,		
	_MI_FM_SEND,	
	_MI_LR_SWAP,
	_MI_UD_SWAP,
	_MI_DISPLAY_RATIO,	
////--TV	
	_MI_SYSTEM,
	_MI_AUTOSEARCH,
	_MI_MANUALSEARCH,
	_MI_TUNING,
	_MI_CHANNEL,
//	_MI_BLUE,
//	_MI_AUTO_POWER_DOWN,
	
	_MI_RESET,
	_MI_EXIT,
    _MI_SC_INPUT_CH_NUM
	
};



#ifdef __OSDTABLE003__

#else


#endif



// extand function & Var
extern code SMenuItem g_tMenuItem[];

#endif		//#if(_OSD_TYPE == _OSD003)

