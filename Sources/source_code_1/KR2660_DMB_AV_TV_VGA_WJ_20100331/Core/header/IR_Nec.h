/*=============================================
  * Copyright (c)      Realtek Semiconductor Corporation, 2005
  * All rights reserved.
  * ============================================ */


#ifndef  _IR_H
#define  _IR_H
//--------------------------------------------------
// Remote Control
//--------------------------------------------------
#define _IR_NONE               	0
#define _IR_CF					1//18keys
#define _IR_CF2					2
#define _IR_DMB                              3 //wtao100410 //27keys

#define _REMOTE_CONTROLLER     _IR_DMB//_IR_CF//_IR_KX_BLACK


//--------------------------------------------------
// Remote LEFT/RIGHT/UP/DOWN function
//--------------------------------------------------
#define _IR_LR_UD_NORMAL       0
#define _IR_LR_UD_TO_VOL_CH    1 // Remote left/right/up/down to vol-/vol+/ch-/ch+


#define _IR_LR_UD_FUNCTION     _IR_LR_UD_TO_VOL_CH

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
#ifdef _IR_C
bit g_bUsePresetIR = 1;
//--------------------------------------------------

code BYTE IRKeyMsg[][2] =
{
#if(_REMOTE_CONTROLLER == _IR_CF)
	{0x00, 0xFF},    				// custom code		
	
	{0x00, _POWER_KEY_MESSAGE},    // Power
	{0x01, _IR_SOURCE_KEY_MESSAGE},// Source
	{0x15, _IR_MENU_KEY_MESSAGE},  // Menu
	{0x14, _IR_LEFT_KEY_MESSAGE},  // Left
	{0x16, _IR_RIGHT_KEY_MESSAGE}, // Right
	{0x12, _MUTE_KEY_MESSAGE},     // Mute

	{0x05, _MP5_UP_KEY_MESSAGE}, 	  // Up
	{0x0D, _MP5_DOWN_KEY_MESSAGE},	  // Down
	{0x08, _MP5_LEFT_KEY_MESSAGE},	  //
	{0x0A, _MP5_RIGHT_KEY_MESSAGE},    //	 
	{0x04, _MP5_FAST_PREV_KEY_MESSAGE}, // <<
	{0x09, _MP5_ENTER_KEY_MESSAGE}, 	// ENT
	{0x06, _MP5_FAST_NEXT_KEY_MESSAGE}, // >>
	{0x0C, _MP5_PREV_KEY_MESSAGE},		// |<<
	{0x0e, _MP5_NEXT_KEY_MESSAGE},		// >>|
	{0x10, _MP5_EXIT_KEY_MESSAGE},		// EXIT
	{0x11, _MP5_PLAY_KEY_MESSAGE},		// >||	
#endif


#if(_REMOTE_CONTROLLER == _IR_CF2)
	{0x00, 0xFF},    				// custom code		
	
	{0x02, _POWER_KEY_MESSAGE},    // Power
	{0x12, _IR_SOURCE_KEY_MESSAGE},// Source
	{0x15, _IR_MENU_KEY_MESSAGE},  // Menu
	{0x14, _IR_LEFT_KEY_MESSAGE},  // Left
	{0x16, _IR_RIGHT_KEY_MESSAGE}, // Right
	{0x00, _MUTE_KEY_MESSAGE},     // Mute
	{0x10, _VOL_DEC_KEY_MESSAGE},  // Vol-
	{0x11, _VOL_INC_KEY_MESSAGE},  // Vol+
	
       {0x06,	_DISPLAY_MODE_MESSAGE},
       {0x0A,	_SCR_LRSWAP_MESSAGE},
       {0x0E,	_SCR_UDSWAP_MESSAGE},

       {0x08,	_CONTRAST_DEC_KEY_MESSAGE},
       {0x09,	_CONTRAST_INC_KEY_MESSAGE},
       {0x04,	_BRIGHT_DEC_KEY_MESSAGE},
       {0x05,	_BRIGHT_INC_KEY_MESSAGE},
       {0x0c,	_SATURATION_DEC_KEY_MESSAGE},
       {0x0d,	_SATURATION_INC_KEY_MESSAGE},    
#endif
	
#if(_REMOTE_CONTROLLER == _IR_DMB) //wtao100412
	{0x85, 0x30},    				// custom code			
//LCD
	{0x00, _POWER_KEY_MESSAGE},    // Power
	{0x01, _IR_SOURCE_KEY_MESSAGE},// Source
	{0x03, _IR_DISPLAY_RATIO_MESSAGE},// 16:9/4:3
	{0x04, _IR_UP_KEY_MESSAGE},//Up
	{0x05, _IR_Reset_KEY_MESSAGE},//Reset
	{0x10, _IR_DOWN_KEY_MESSAGE},//Down
	{0x07, _IR_MENU_KEY_MESSAGE},  // Menu
	{0x06, _IR_LEFT_KEY_MESSAGE},  // Left
	{0x08, _IR_RIGHT_KEY_MESSAGE}, // Right
	{0x02, _MUTE_KEY_MESSAGE},     // Mute
	
	{0x09, _NONE_KEY_MESSAGE}, //reserved
       {0x24, _NONE_KEY_MESSAGE}, //reserved
//MP5+DMB
	{0x26, _MP5_UP_KEY_MESSAGE}, 	   // Up
	{0x22, _MP5_DOWN_KEY_MESSAGE},	   // Down
	{0x12, _MP5_LEFT_KEY_MESSAGE},	   //Vol-
	{0x1E, _MP5_RIGHT_KEY_MESSAGE},    //Vol+	 
	{0x1F, _MP5_ENTER_KEY_MESSAGE},    // Enter
//MP5	
	{0x13, _MP5_FAST_PREV_KEY_MESSAGE}, // <<
	{0x15, _MP5_FAST_NEXT_KEY_MESSAGE}, // >>
	{0x16, _MP5_PREV_KEY_MESSAGE},		// |<<
	{0x18, _MP5_NEXT_KEY_MESSAGE},		// >>|
	{0x14, _MP5_EXIT_KEY_MESSAGE},		// EXIT
	{0x17, _MP5_PLAY_KEY_MESSAGE},		// >||	
//DMB	
	{0x1A, _DMB_MODE_KEY},		// DMB/DAB
	{0x19, _DMB_INFO_KEY},		// Information
	{0x23, _DMB_SCAN_KEY},		// Scan
	{0x11, _DMB_MENU_KEY},		// Menu
	
#endif	

	{0x00,0x00}					//end flag

};

#else

extern BYTE ucPrevKey;
extern BYTE ucRepKeyCount;
extern BYTE ucIrQueue[4];
extern bit g_bUsePresetIR;


#endif



/*======================= Extern Functions ================== */
BYTE CIRKeyScan(void);
void CIrdaInitial(void);
BYTE ScanPresetIR(void);

#endif // #ifndef _IR_H
