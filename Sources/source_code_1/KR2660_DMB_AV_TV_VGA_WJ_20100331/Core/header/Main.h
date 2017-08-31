//----------------------------------------------------------------------------------------------------
// ID Code      : Main.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of
//--------------------------------------------------


//----------------------------------------------------------------------------------------------------

#ifdef __MAIN__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
BYTE data pData[16];

#if(_SLEEP_FUNC)
bit bTimerOnScreen            = 0;
bit bShowTimerChg			  = 0;
WORD data ucMinuteCount       = 0;
BYTE data ucAutoPowerDownTime = 0xFF;
#endif
//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CMainUserInitial();
void CMainSystemInitial(void);

void DbgLed(unsigned char ucCount);

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE data pData[16];
extern void DbgLed(unsigned char ucCount);
#if(_SLEEP_FUNC)
extern bit bTimerOnScreen;
extern bit bShowTimerChg;
extern WORD data ucMinuteCount;
extern BYTE data ucAutoPowerDownTime;
#endif

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------

#endif


//----------------------------------------------------------------------------------------------------

