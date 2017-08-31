//----------------------------------------------------------------------------------------------------
// ID Code      : FrameSync.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Offset_Step is the DCLK frequency step for searching frame-sync.
//--------------------------------------------------
#define _OFFSET_STEP    24
#define _SEARCH_TIME    24


//----------------------------------------------------------------------------------------------------

#ifdef __FRAMESYNC__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
bit CFrameSyncDetect(void);
bit CFrameSyncLastLineFinetune(WORD *pDelta);
BYTE CFrameSyncSpreadSpectrumFinetune(WORD *pDelta);
WORD CFrameSyncFastDo(void);
bit CFrameSyncTestSync(WORD usOffset);
BYTE CFrameSyncDo(void);


#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern bit CFrameSyncDetect(void);
extern BYTE CFrameSyncDo(void);
#endif


//----------------------------------------------------------------------------------------------------
