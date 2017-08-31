#define _EXTFUNC_REAL_BEGIN_ADDRESS						0x28000	
#define _EXTFUNC_REAL_END_ADDRESS						0x30000	

#define _EXTFUNC_EDID_OFFSET							0x0000
#define _EXTFUNC_PANEL_OFFSET							0x0400
#define _EXTFUNC_IR_OFFSET								0x0600
#define _EXTFUNC_ADKEY_OFFSET							0x0A00
#define _EXTFUNC_SDKEY_OFFSET							0x0C00
#define _EXTFUNC_OTHER_OFFSET							0x0D00
#define _EXTFUNC_LOGO_OFFSET							0x1800


#define _EDID_128										0
#define _EDID_256										1





#ifdef __KX_EXTENDFUNC__



/*
    MDT_GET_EXT_ADDRESS,            // 扩展地址最小值,最大值.
    Real Address Begin      :4		0x28000
    Real Address End        :4		0x30000
    

    MDT_GET_EXT_LOGO_INF,           // Logo 信息
    MDT_GET_EXT_EDID_GROUP_CNT,     // Edid 组数
    MDT_GET_EXT_EDID_INF,           // Edid 信息
    MDT_GET_EXT_IR_INF,             // 得到 IR 信息
    MDT_GET_EXT_IRKEY_INF,          // 得到 IR 每一个 key 的信息
    MDT_GET_EXT_ADKEY_INF,          // 得到 IR 信息
    MDT_GET_EXT_ADKEY_DATA,         // 得到 IR 每一个 key 的信息
    MDT_GET_EXT_ADLINE_CNT,         // 获取AD口数量
    MDT_GET_EXT_ADVALUE,            // 获取AD口的AD值
    MDT_GET_EXT_PANEL_INF,          // 获取 Panel 信息
    MDT_GET_EXT_OTHERFUNC_CNT,      // 获取 Other Function 的数量
    MDT_GET_EXT_OTHERFUNC_INF,      // 获取 Other Function 的信息


    MEMORY MAP
	EDID :  0x0000 ~ 0x0400
	Panel:  0x0400 ~ 0x0600
	IR KEY: 0x0600 ~ 0x0A00
	ADKey:	0x0A00 ~ 0x0C00
	Other Func : 0x0C00 ~ 0x1400
	预留 : 0x1400 ~ 0x1800	
	Logo : 0x1800 ~ 0x8000
    
*/
//------------------------------------------------------------------------

code SEFLogo tEFLogoInfo = 
{
	0,								//BYTE Support;
	_EXTFUNC_LOGO_OFFSET,			//WORD Offset;
};

//------------------------------------------------------------------------

BYTE code g_EFEdidGroupCnt = 3;
code SEFEdid tEFEdids[] =
{
	{
		1,							//BYTE Support;
		_EXTFUNC_EDID_OFFSET,		//WORD Offset;
		"VGA",						//char Name[16];
		_EDID_128,					//BYTE Type;
	},

	{
		1,							//BYTE Support;
		_EXTFUNC_EDID_OFFSET + 128,	//WORD Offset;
		"DVI",						//char Name[16];
		_EDID_128,					//BYTE Type;
	},

	{
		1,							//BYTE Support;
		_EXTFUNC_EDID_OFFSET + 256,		//WORD Offset;
		"HDMI",						//char Name[16];
		_EDID_256,					//BYTE Type;
	},
	
} ;

//------------------------------------------------------------------------

code SEFIR tEFIR = 
{
	1,					//BYTE Support;
	_EXTFUNC_IR_OFFSET,	//WORD Offset;
	29,					//BYTE KeyCount;
};


code SEFIRKey tEFIRKeys[] = 
{
	{"Power", 		_POWER_KEY_MESSAGE   },	//char Name[16]; BYTE KeyMessage;

	{"Menu",	 	_MENU_KEY_MESSAGE    },	//char Name[16]; BYTE KeyMessage;
	{"Left", 	    _IR_LEFT_KEY_MESSAGE },	//char Name[16]; BYTE KeyMessage;
	{"Right",	    _IR_RIGHT_KEY_MESSAGE},	//char Name[16]; BYTE KeyMessage;
	{"Up", 		    _IR_UP_KEY_MESSAGE   },	//char Name[16]; BYTE KeyMessage;
	{"Down",	 	_IR_DOWN_KEY_MESSAGE },	//char Name[16]; BYTE KeyMessage;

	{"Source", 		_SOURCE_KEY_MESSAGE  },	//char Name[16]; BYTE KeyMessage;
	{"Mute", 		_MUTE_KEY_MESSAGE    },	//char Name[16]; BYTE KeyMessage;

	{"VGA", 		_VGA_KEY_MESSAGE     },	//char Name[16]; BYTE KeyMessage;
	{"DVI", 		_DVI_KEY_MESSAGE     },	//char Name[16]; BYTE KeyMessage;
	{"S VIDEO", 	_S_VIDEO_KEY_MESSAGE },	//char Name[16]; BYTE KeyMessage;
	{"AV", 			_AV_KEY_MESSAGE      },	//char Name[16]; BYTE KeyMessage;
	{"TV", 			_TV_KEY_MESSAGE      },	//char Name[16]; BYTE KeyMessage;
	{"DVD",			_DVD_KEY_MESSAGE     },	//char Name[16]; BYTE KeyMessage;

	{"0", 		    _NUM_0_KEY_MESSAGE   },	//char Name[16]; BYTE KeyMessage;
	{"1", 		    _NUM_1_KEY_MESSAGE   },	//char Name[16]; BYTE KeyMessage;
	{"2", 		    _NUM_2_KEY_MESSAGE   },	//char Name[16]; BYTE KeyMessage;
	{"3", 		    _NUM_3_KEY_MESSAGE   },	//char Name[16]; BYTE KeyMessage;
	{"4", 		    _NUM_4_KEY_MESSAGE   },	//char Name[16]; BYTE KeyMessage;
	{"5", 		    _NUM_5_KEY_MESSAGE   },	//char Name[16]; BYTE KeyMessage;
	{"6", 		    _NUM_6_KEY_MESSAGE   },	//char Name[16]; BYTE KeyMessage;
	{"7", 		    _NUM_7_KEY_MESSAGE   },	//char Name[16]; BYTE KeyMessage;
	{"8", 		    _NUM_8_KEY_MESSAGE   },	//char Name[16]; BYTE KeyMessage;
	{"9", 		    _NUM_9_KEY_MESSAGE   },	//char Name[16]; BYTE KeyMessage;

	{"AUTO", 		_AUTO_KEY_MESSAGE    },	//char Name[16]; BYTE KeyMessage;
	{"ESC", 		_ESC_KEY_MESSAGE     },	//char Name[16]; BYTE KeyMessage;
	{"Display", 	_DISPLAY_KEY_MESSAGE },	//char Name[16]; BYTE KeyMessage;

	{"INPUT_CH",	_INPUT_CH_KEY_MESSAGE},	//char Name[16]; BYTE KeyMessage;
	{"Return",		_RETURN_KEY_MESSAGE  } 	//char Name[16]; BYTE KeyMessage;

};


//code BYTE g_ucEFIREnable _at_ ((_EXTFUNC_REAL_BEGIN_ADDRESS & 0xFFFF) + _EXTFUNC_IR_OFFSET);
//code BYTE *g_pEFIRKeyMsg _at_ ((_EXTFUNC_REAL_BEGIN_ADDRESS & 0xFFFF) + _EXTFUNC_IR_OFFSET + 1);
//------------------------------------------------------------------------


code SEFAD tEFADC =
{
	0,							//BYTE Support;
	_EXTFUNC_ADKEY_OFFSET,		//WORD Offset;
	8,							//BYTE ADIOCount;	ADC_A : 5 + ADC_B : 3
	7,							//BYTE ADKeyCount;
};

code SEFADKey tEFADKeys[] =
{
	{"Power", 		_POWER_KEY_MESSAGE   },	//char Name[16]; BYTE KeyMessage;
	{"Menu",	 	_MENU_KEY_MESSAGE	 },	//char Name[16]; BYTE KeyMessage;
	{"Left", 		_LEFT_KEY_MESSAGE 	 },	//char Name[16]; BYTE KeyMessage;
	{"Right",		_RIGHT_KEY_MESSAGE   },	//char Name[16]; BYTE KeyMessage;
	{"Up", 			_UP_KEY_MESSAGE  	 },	//char Name[16]; BYTE KeyMessage;
	{"Down",	 	_DOWN_KEY_MESSAGE 	 },	//char Name[16]; BYTE KeyMessage;
	{"Source", 		_SOURCE_KEY_MESSAGE  },	//char Name[16]; BYTE KeyMessage;
};
//------------------------------------------------------------------------

code SEFPanel tEFPanel = 
{
	0,						//BYTE Support;
	_EXTFUNC_PANEL_OFFSET,	//WORD Offset;
};
//------------------------------------------------------------------------

BYTE code g_EFOtherCnt = 2;

code SEFOther tEFOtherFunc[] =
{
	{
		0,								//BYTE Support;
		_EXTFUNC_OTHER_OFFSET,			//WORD Offset;
		"U/D",							//char Name[16];
		1,								//BYTE DefaultValue;
	},
	{
		0,								//BYTE Support;
		_EXTFUNC_OTHER_OFFSET + 1,		//WORD Offset;
		"L/R",							//char Name[16];
		1,								//BYTE DefaultValue;
	},
	
};
//------------------------------------------------------------------------
code SEFSDKeyInf tEFSDKeyInf =
{
	1,										//BYTE Support;
	_EXTFUNC_SDKEY_OFFSET,					//WORD Offset;
	7,										//BYTE KeyCount;
};
//------------------------------------------------------------------------
code SEFSDKey tEFSDKey[] =
{
	{
		"Power",				//char Name[16];
		_POWER_KEY_MASK,		//BYTE KeyMessage;
	},
	{
		"Menu",				//char Name[16];
		_MENU_KEY_MASK,		//BYTE KeyMessage;
	},
	{
		"Left",				//char Name[16];
		_LEFT_KEY_MASK,		//BYTE KeyMessage;
	},
	{
		"Right",				//char Name[16];
		_RIGHT_KEY_MASK,		//BYTE KeyMessage;
	},
/*	
	{
		"Up",				//char Name[16];
		_UP_KEY_MASK,		//BYTE KeyMessage;
	},
	{
		"Down",				//char Name[16];
		_DOWN_KEY_MASK,		//BYTE KeyMessage;
	},
*/
	{
		"Source",				//char Name[16];
		_SOURCE_KEY_MASK,		//BYTE KeyMessage;
	},
	
	
};

#else


extern code SEFLogo tEFLogoInfo;
extern BYTE code g_EFEdidGroupCnt;
extern code SEFEdid tEFEdids[];
extern code SEFIR tEFIR;
extern code SEFIRKey tEFIRKeys[];
extern code SEFAD tEFADC;
extern code SEFADKey tEFADKeys[];
extern code SEFPanel tEFPanel;
extern BYTE code g_EFOtherCnt;
extern code SEFOther tEFOtherFunc[];

extern code SEFSDKeyInf tEFSDKeyInf;
extern code SEFSDKey tEFSDKey[];

#endif
