//----------------------------------------------------------------------------------------------------
// ID Code      : Sync.h No.0001
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of
//--------------------------------------------------


//----------------------------------------------------------------------------------------------------

#ifdef __SYNC__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
bit bHsyncSelection        = 0; // 1 --> select
bit bInputSignalAvailable  = 0; // 1 --> signal ok
BYTE idata ucInputSyncType = 0;
bit bSourceAutoChange      = 0;

BYTE idata ucInputSyncType;
BYTE idata ucStablePol; //Ming-Yen
BYTE idata ucTimerEvent = 255;

#if(_YPBPR_AUTO_SOY == _ENABLE)
BYTE xdata SyncLevelOffset = 0;

#define SOGSyncLevel 		0x20
#define MinSOGSyncLevel		0x18
#endif

#if(_HDMI_SUPPORT == _ON && _HDMI_HOT_PLUG_OPTION == _ENABLE)
bit bDVIDetect = 0;
#endif

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CSyncProcess(void);
bit CSyncHandler(void);
void CSyncInitialSyncProcessor(void);
BYTE CSyncMeasureSyncType(void);
BYTE CSyncSearchSyncTypeVGA(void);
BYTE CSyncGetSyncTypeStepVGA(void);
void CSyncModifyPolarityVGA(void);
BYTE CSyncSearchSyncTypeDVI(void);
BYTE CSyncGetSyncTypeAutoRun(void);

#if(_YPBPR_AUTO_SOY == _ENABLE)
void CYPbPrAutoSOY(void);
#endif

void CSetModeReady(void);
bit bCNoCheckSyncMode(void);

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern bit bHsyncSelection;
extern bit bInputSignalAvailable;
extern BYTE idata ucInputSyncType;
extern bit bSourceAutoChange;

extern BYTE idata ucInputSyncType;
extern BYTE idata ucStablePol;  //Ming-Yen
//extern BYTE idata ucSyncProcessState;
extern BYTE idata ucTimerEvent;

#if(_YPBPR_AUTO_SOY == _ENABLE)
extern BYTE xdata SyncLevelOffset;
#endif

#if(_HDMI_SUPPORT == _ON && _HDMI_HOT_PLUG_OPTION == _ENABLE)
extern bit bDVIDetect;
#endif

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CSyncProcess(void);
extern bit CSyncHandler(void);
extern void CSyncInitialSyncProcessor(void);
extern BYTE CSyncGetSyncTypeStepVGA(void);
extern BYTE CSyncGetSyncTypeAutoRun(void);
extern void CSyncModifyPolarityVGA(void);

#if(_YPBPR_AUTO_SOY == _ENABLE)
extern void CYPbPrAutoSOY(void);
#endif
extern bit bCNoCheckSyncMode(void);

#endif


//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Macro of Input Sync Type
//--------------------------------------------------
/*
#define GET_INPUTSYNC_TYPE()            (ucInputSyncType & (_BIT0 | _BIT1 | _BIT2 | _BIT3))
#define SET_INPUTSYNC_TYPE(x)           (ucInputSyncType = ((ucInputSyncType & ~(_BIT0 | _BIT1 | _BIT2 | _BIT3)) | x))
  */

//--------------------------------------------------
// Macro of Source Auto Change
//--------------------------------------------------
#define GET_SOURCE_AUTOCHANGE()         (bSourceAutoChange)
#define SET_SOURCE_AUTOCHANGE()         (bSourceAutoChange = 1)
#define CLR_SOURCE_AUTOCHANGE()         (bSourceAutoChange = 0)


//--------------------------------------------------
// Macro of DVII Source Switch
//--------------------------------------------------
#define GET_DVI_I_SOURCE_SWITCH()       ((bit)(stSystemData.MonitorFlag & _BIT6))
#define SET_DVI_I_DVI_SWITCH()          (stSystemData.MonitorFlag |= _BIT6)
#define CLR_DVI_I_VGA_SWITCH()          (stSystemData.MonitorFlag &= ~_BIT6)

