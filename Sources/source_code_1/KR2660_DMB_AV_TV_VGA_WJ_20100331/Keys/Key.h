//----------------------------------------------------------------------------------------------------
// ID Code      : Key.h No.0000
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------
#define _ABS(VALUE1,VALUE2)      (VALUE1 > VALUE2 ? (VALUE1) - (VALUE2) : (VALUE2) - (VALUE1))

//--------------------------------------------------
// Macro of Key Scan Ready Flag
//--------------------------------------------------
#define GET_KEYSCANREADY()          ((bit)(ucKeyControl & _BIT0))
#define SET_KEYSCANREADY()          (ucKeyControl |= _BIT0)
#define CLR_KEYSCANREADY()          (ucKeyControl &= ~_BIT0)


//--------------------------------------------------
// Macro of Key Scan Start Flag
//--------------------------------------------------
#define GET_KEYSCANSTART()          ((bit)(ucKeyControl & _BIT1))
#define SET_KEYSCANSTART()          (ucKeyControl |= _BIT1)
#define CLR_KEYSCANSTART()          (ucKeyControl &= ~_BIT1)


//--------------------------------------------------
// Macro of Key Repeat Start
//--------------------------------------------------
#define GET_KEYREPEATSTART()        (bit)(ucKeyControl & _BIT2)
#define SET_KEYREPEATSTART()        ucKeyControl |= _BIT2
#define CLR_KEYREPEATSTART()        ucKeyControl &= ~_BIT2


//--------------------------------------------------
// Macro of Key Repeat Function Enable
// If you want to use repeat function, please set this flag. If not, please clear it.
//--------------------------------------------------
#define GET_KEYREPEATENABLE()       (bit)(ucKeyControl & _BIT3)
#define SET_KEYREPEATENABLE()       ucKeyControl |= _BIT3
#define CLR_KEYREPEATENABLE()       ucKeyControl &= ~_BIT3





//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Key Repeat Start Time (Unit in sec)
//--------------------------------------------------
#define _KEY_REPEAT_START_TIME      0.5

//--------------------------------------------------
// Definitions of Key Mask
//--------------------------------------------------

//--------------------------------------------------
// Definitions of Key Message
//--------------------------------------------------
enum
{
    _NONE_KEY_MESSAGE = 0,
//LCD Panel Key
    _POWER_KEY_MESSAGE,    
    _MENU_KEY_MESSAGE,
    _AUTO_KEY_MESSAGE,
    _SOURCE_KEY_MESSAGE,
    _ENTER_KEY_MESSAGE,
    _EXIT_KEY_MESSAGE,
    _RIGHT_KEY_MESSAGE,
    _LEFT_KEY_MESSAGE,
    _UP_KEY_MESSAGE,
    _DOWN_KEY_MESSAGE,


    _FAC_KEY_MESSAGE,

//Remoter
    _IR_SOURCE_KEY_MESSAGE,
    _IR_MENU_KEY_MESSAGE,
    _IR_RIGHT_KEY_MESSAGE,
    _IR_LEFT_KEY_MESSAGE,
    _IR_UP_KEY_MESSAGE,
    _IR_DOWN_KEY_MESSAGE,

    _MUTE_KEY_MESSAGE,
    _VOL_DEC_KEY_MESSAGE,
    _VOL_INC_KEY_MESSAGE,
    _CH_DEC_KEY_MESSAGE,
    _CH_INC_KEY_MESSAGE,

    _DISPLAY_MODE_MESSAGE,
    _SCR_LRSWAP_MESSAGE,
    _SCR_UDSWAP_MESSAGE,

    _CONTRAST_DEC_KEY_MESSAGE,
    _CONTRAST_INC_KEY_MESSAGE,
    _BRIGHT_DEC_KEY_MESSAGE,
    _BRIGHT_INC_KEY_MESSAGE,
    _SATURATION_DEC_KEY_MESSAGE,
    _SATURATION_INC_KEY_MESSAGE,    
    
    _DISPLAY_KEY_MESSAGE,
	_SIZE_KEY_MESSAGE,
    _VMODE_KEY_MESSAGE,	
    _AUDIO_KEY_MESSAGE,
    _VGA_KEY_MESSAGE,
    _DVI_KEY_MESSAGE,
    _S_VIDEO_KEY_MESSAGE,
    _AV_KEY_MESSAGE,
    _TV_KEY_MESSAGE,
    _DVD_KEY_MESSAGE,
    _ESC_KEY_MESSAGE,
    _NUM_0_KEY_MESSAGE,
    _NUM_1_KEY_MESSAGE,
    _NUM_2_KEY_MESSAGE,
    _NUM_3_KEY_MESSAGE,
    _NUM_4_KEY_MESSAGE,
    _NUM_5_KEY_MESSAGE,
    _NUM_6_KEY_MESSAGE,
    _NUM_7_KEY_MESSAGE,
    _NUM_8_KEY_MESSAGE,
    _NUM_9_KEY_MESSAGE,
    _INPUT_CH_KEY_MESSAGE,
    _RETURN_KEY_MESSAGE,
    _SLEEP_KEY_MESSAGE,
    _DISPLAY_RATIO_MESSAGE,
    _IR_DISPLAY_RATIO_MESSAGE,
    _TCON_MESSAGE,  

//MP5
    _MP5_EXIT_KEY_MESSAGE,
    _MP5_FAST_PREV_KEY_MESSAGE,
    _MP5_FAST_NEXT_KEY_MESSAGE,
    _MP5_PREV_KEY_MESSAGE,
    _MP5_NEXT_KEY_MESSAGE,
    _MP5_PLAY_KEY_MESSAGE,
    _MP5_LEFT_KEY_MESSAGE,
    _MP5_RIGHT_KEY_MESSAGE,    
    _MP5_UP_KEY_MESSAGE,
    _MP5_ENTER_KEY_MESSAGE,    
    _MP5_DOWN_KEY_MESSAGE,   
    _MP5_STOP_KEY_MESSAGE,
    _MP5_CALLMENU_KEY_MESSAGE,
    _MP5_MAINMENU_KEY_MESSAGE,
    
//DMB //wtao100410
   _DMB_MODE_KEY,
   _DMB_INFO_KEY,
   _DMB_SCAN_KEY,
   _DMB_MENU_KEY,
   _Reset_KEY_MESSAGE,
   _IR_Reset_KEY_MESSAGE
};


#ifdef __KEY__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
BYTE idata ucKeyControl;
BYTE idata ucKeyMessage;
BYTE idata ucKeyStatePrev;
BYTE idata ucKeyStateCurr;

bit g_bUsePresetKey = 1;			// ac power on init it

  
#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE idata ucKeyControl;
extern BYTE idata ucKeyMessage;
extern BYTE idata ucKeyStatePrev;
extern BYTE idata ucKeyStateCurr;
extern bit g_bUsePresetKey;


#endif


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CKeyHandler(void);
void CKeyCheckPowerKey(void);
void CKeyInitial(void);
bit CKeyScanReady(void);
void CKeyScanReadyTimerEvent(void);
void CKeyRepeatEnableTimerEvent(void);
void CKeyMessageConvert(WORD ucKeyMask, BYTE ucKeyMsg);
BYTE CKeyScan(void);
void CKeyPowerKeyMix(void);
bit CKeyPowerKeyProc(void);
//void CKeyMessageProc(void);

bit CKeyCheckExitKey(void);
void CKeyCheckEnterFactoryMenu(void);
bit CCheckAutoPowerKey(void);
bit CCheckAutoPowerKey(void);
//void CIrProc(void);
BYTE CheckKeyDown(BYTE KeyMask,BYTE Cnt);
BYTE CheckKeyUp(BYTE KeyMask,BYTE Cnt);
BYTE CGetADCAValue(BYTE Port);
WORD CGetADCBValue(BYTE Port);
BYTE CKeyScanIO(void);
void CIrdaReadData(void);
//----------------------------------------------------------------------------------------------------


