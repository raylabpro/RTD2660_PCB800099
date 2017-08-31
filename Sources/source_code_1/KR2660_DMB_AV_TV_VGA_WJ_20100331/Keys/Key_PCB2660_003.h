#if(_KEY_TYPE == _KT_PCB2660_003)

#define _FUNC_EN_CHK_KEY_DOWN       0
#define _FUNC_EN_CHK_KEY_UP         1



#ifdef __OSDPROC003__


// Key map
SKeyToOsdEvent code tKONoSignal[] =
{
	// source

	// End flag,not modify there
    {_NONE_KEY_MESSAGE,         _NONE_MSG         },
};
//------------------------------------------------------------
// Key map
SKeyToOsdEvent code tKOPublic[] =
{         
	// source
	{_SOURCE_KEY_MESSAGE,		_OE_CHG_SOURCE_AV_SV},
	{_IR_SOURCE_KEY_MESSAGE,	_OE_CHG_SOURCE_AV_SV},
	
#if(_SLEEPKEY_FUNC == _FUNC_SLEEP)	
	{_SLEEP_KEY_MESSAGE,		_OE_SC_TIMER_CHANGE},
#else
	{_SLEEP_KEY_MESSAGE,		_OE_CHANGE_PICTURE_MODE},
#endif	       
       {_MUTE_KEY_MESSAGE,              _OE_SC_MUTE       },
       
       { _IR_DISPLAY_RATIO_MESSAGE, _OE_CHANGE_PICTURE_MODE},//wtao100416
       
	{_LEFT_KEY_MESSAGE,		       _OE_GOTO_MENU_VOLUME},   // Vol-
	{_RIGHT_KEY_MESSAGE,		_OE_GOTO_MENU_VOLUME},   // Vol+
	
	{_IR_LEFT_KEY_MESSAGE,		_OE_GOTO_MENU_VOLUME},   // Vol-
	{_IR_RIGHT_KEY_MESSAGE,		_OE_GOTO_MENU_VOLUME},   // Vol+

       {_DISPLAY_RATIO_MESSAGE,	_OE_CHG_DISPLAY_MODE},
       {_DISPLAY_MODE_MESSAGE,	_OE_CHG_DISPLAY_MODE},
       {_TCON_MESSAGE,	              _OE_TCON_MODE},
       {_SCR_LRSWAP_MESSAGE,		_OE_PANEL_LR_SWAP},
       {_SCR_UDSWAP_MESSAGE,		_OE_PANEL_UD_SWAP},

       {_CONTRAST_DEC_KEY_MESSAGE,	_OE_GOTO_MENU_CONTRAST},
       {_CONTRAST_INC_KEY_MESSAGE,	_OE_GOTO_MENU_CONTRAST},
       {_BRIGHT_DEC_KEY_MESSAGE,	_OE_GOTO_MENU_BRIGHTNESS},
       {_BRIGHT_INC_KEY_MESSAGE,	_OE_GOTO_MENU_BRIGHTNESS},
       {_SATURATION_DEC_KEY_MESSAGE,	_OE_GOTO_MENU_SATURATION},
       {_SATURATION_INC_KEY_MESSAGE,	_OE_GOTO_MENU_SATURATION},    
   
       {_Reset_KEY_MESSAGE,_OE_GOTO_MENU_RESET},//KEY Reset wtao100413
       {_IR_Reset_KEY_MESSAGE,_OE_GOTO_MENU_RESET},//IRKEY Reset wtao100413
    // End flag,not modify there
       {_NONE_KEY_MESSAGE,         _NONE_MSG         },
};
//------------------------------------------------------------

// Key map
SKeyToOsdEvent code tKOMenuNone[] =
{
	{_MENU_KEY_MESSAGE,         _OE_ENTER_SUBMENU      },
	{_IR_MENU_KEY_MESSAGE,	  _OE_ENTER_SUBMENU      },
       {_MUTE_KEY_MESSAGE,         _OE_SC_MUTE            },

 	// End flag,not modify there
    {_NONE_KEY_MESSAGE,         _NONE_MSG              },
};
//------------------------------------------------------------
// Key map
SKeyToOsdEvent code tKOMainMenu[] =
{
	{_MENU_KEY_MESSAGE,         _OE_MENU_NEXT		},
	{_LEFT_KEY_MESSAGE,         _OE_ADJ_DEC			},
	{_RIGHT_KEY_MESSAGE,        _OE_ADJ_INC			},

	{_IR_MENU_KEY_MESSAGE,		_OE_MENU_NEXT      },
	{_IR_LEFT_KEY_MESSAGE,      _OE_ADJ_DEC			},
	{_IR_RIGHT_KEY_MESSAGE,     _OE_ADJ_INC			},
	
	{_IR_DOWN_KEY_MESSAGE,      _OE_MENU_PREV			},//IRkey up down wtao100413
	{_IR_UP_KEY_MESSAGE,     _OE_MENU_NEXT},
//       {_EXIT_KEY_MESSAGE,   _OE_RETURN_UPMENU},//wtao100412
    // End flag,not modify there
    {_NONE_KEY_MESSAGE,         _NONE_MSG         },
};
//------------------------------------------------------------
SKeyToOsdEvent code tKOExit[] =
{
	{_MENU_KEY_MESSAGE,         _OE_RETURN_UPMENU			},
	{_LEFT_KEY_MESSAGE,         _OE_RETURN_UPMENU			},
	{_RIGHT_KEY_MESSAGE,        _OE_RETURN_UPMENU			},

	{_IR_MENU_KEY_MESSAGE,		_OE_RETURN_UPMENU      		},
	{_IR_LEFT_KEY_MESSAGE,      _OE_RETURN_UPMENU			},
	{_IR_RIGHT_KEY_MESSAGE,     _OE_RETURN_UPMENU			},
	{_IR_DOWN_KEY_MESSAGE,      _OE_RETURN_UPMENU			},//IRkey up down wtao100413
	{_IR_UP_KEY_MESSAGE,          _OE_RETURN_UPMENU},
    // End flag,not modify there
    {_NONE_KEY_MESSAGE,         _NONE_MSG         },
};
//------------------------------------------------------------

SKeyToOsdEvent code tKOContrastMenu[] =
{
	{_MENU_KEY_MESSAGE,         _OE_MENU_NEXT		},
	{_LEFT_KEY_MESSAGE,         _OE_ADJ_DEC			},
	{_RIGHT_KEY_MESSAGE,        _OE_ADJ_INC			},
	{_CONTRAST_DEC_KEY_MESSAGE, _OE_ADJ_DEC			},
	{_CONTRAST_INC_KEY_MESSAGE, _OE_ADJ_INC			},

	{_IR_MENU_KEY_MESSAGE,		_OE_MENU_NEXT      },
	{_IR_LEFT_KEY_MESSAGE,      _OE_ADJ_DEC			},
	{_IR_RIGHT_KEY_MESSAGE,     _OE_ADJ_INC			},
	
	{_IR_DOWN_KEY_MESSAGE,      _OE_MENU_PREV			},//IRkey up down wtao100413
	{_IR_UP_KEY_MESSAGE,     _OE_MENU_NEXT},
    // End flag,not modify there
    {_NONE_KEY_MESSAGE,         _NONE_MSG         },
};
//------------------------------------------------------------
SKeyToOsdEvent code tKOBrightnessMenu[] =
{
	{_MENU_KEY_MESSAGE,         _OE_MENU_NEXT		},
	{_LEFT_KEY_MESSAGE,         _OE_ADJ_DEC			},
	{_RIGHT_KEY_MESSAGE,        _OE_ADJ_INC			},
	{_BRIGHT_DEC_KEY_MESSAGE, 	_OE_ADJ_DEC			},
	{_BRIGHT_INC_KEY_MESSAGE, 	_OE_ADJ_INC			},


	{_IR_MENU_KEY_MESSAGE,		_OE_MENU_NEXT      },
	{_IR_LEFT_KEY_MESSAGE,      _OE_ADJ_DEC			},
	{_IR_RIGHT_KEY_MESSAGE,     _OE_ADJ_INC			},
	
	{_IR_DOWN_KEY_MESSAGE,      _OE_MENU_PREV			},//IRkey up down wtao100413
	{_IR_UP_KEY_MESSAGE,     _OE_MENU_NEXT},
	

    // End flag,not modify there
    {_NONE_KEY_MESSAGE,         _NONE_MSG         },
};
//------------------------------------------------------------

SKeyToOsdEvent code tKOSaturationMenu[] =
{
	{_MENU_KEY_MESSAGE,         _OE_MENU_NEXT		},
	{_LEFT_KEY_MESSAGE,         _OE_ADJ_DEC			},
	{_RIGHT_KEY_MESSAGE,        _OE_ADJ_INC			},
	{_SATURATION_DEC_KEY_MESSAGE, 	_OE_ADJ_DEC			},
	{_SATURATION_INC_KEY_MESSAGE, 	_OE_ADJ_INC			},

	{_IR_MENU_KEY_MESSAGE,		_OE_MENU_NEXT      },
	{_IR_LEFT_KEY_MESSAGE,      _OE_ADJ_DEC			},
	{_IR_RIGHT_KEY_MESSAGE,     _OE_ADJ_INC			},
	
	{_IR_DOWN_KEY_MESSAGE,      _OE_MENU_PREV			},//IRkey up down wtao100413
	{_IR_UP_KEY_MESSAGE,     _OE_MENU_NEXT},
    // End flag,not modify there
    {_NONE_KEY_MESSAGE,         _NONE_MSG         },
};
//------------------------------------------------------------

SKeyToOsdEvent code tKOVolumeMenu[] =
{
	{_MENU_KEY_MESSAGE,         _OE_MENU_NEXT		},
	{_LEFT_KEY_MESSAGE,         _OE_ADJ_DEC			},
	{_RIGHT_KEY_MESSAGE,        _OE_ADJ_INC			},
	{_VOL_DEC_KEY_MESSAGE, 	    _OE_ADJ_DEC			},
	{_VOL_INC_KEY_MESSAGE, 	    _OE_ADJ_INC			},

	{_IR_MENU_KEY_MESSAGE,		_OE_MENU_NEXT       },
	{_IR_LEFT_KEY_MESSAGE,      _OE_ADJ_DEC			},
	{_IR_RIGHT_KEY_MESSAGE,     _OE_ADJ_INC			},
	
	{_IR_DOWN_KEY_MESSAGE,      _OE_MENU_PREV			},//IRkey up down wtao100413
	{_IR_UP_KEY_MESSAGE,     _OE_MENU_NEXT},
    // End flag,not modify there
    {_NONE_KEY_MESSAGE,         _NONE_MSG           },
};

#else               //#ifdef __PCB2660_003_KEY__


// Key map
extern SKeyToOsdEvent code tKONoSignal[];
extern SKeyToOsdEvent code tKOPublic[];
extern SKeyToOsdEvent code tKOMenuNone[];
extern SKeyToOsdEvent code tKOMainMenu[];
extern SKeyToOsdEvent code tKOExit[];
extern SKeyToOsdEvent code tKOContrastMenu[];
extern SKeyToOsdEvent code tKOBrightnessMenu[];
extern SKeyToOsdEvent code tKOSaturationMenu[];
extern SKeyToOsdEvent code tKOVolumeMenu[];
//extern SKeyToOsdEvent code tKOShortInputCHMenu[];


#endif              //#ifdef __PCB2660_003_KEY__

void CKeyMessageProc(void);

#endif              //#if(_KEY_TYPE == _KT_PCB2660_003)
