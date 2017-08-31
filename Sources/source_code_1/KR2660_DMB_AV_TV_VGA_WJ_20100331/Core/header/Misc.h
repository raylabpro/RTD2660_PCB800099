//----------------------------------------------------------------------------------------------------
// ID Code      : Misc.h No.0001
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of
//--------------------------------------------------


//----------------------------------------------------------------------------------------------------

#ifdef __MISC__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------

#if(_DEBUG_TOOL == _ISP_FOR_RTD3580D_EMCU)

BYTE ucVirtualKey = 0;
BYTE ucDdcciCommandNumber = 0;
BYTE TxBUF=0;
bit bRunCommand=0;
BYTE idata ucDdcciData[4];

#endif


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
bit CMiscScalerResetEvent(void);
//bit CMiscStableFlagPollingEvent(void);
bit CMiscHsyncTypeAutoRunFlagPollingEvent(void);
bit CMiscModeMeasurePollingEvent(void);
bit CMiscAutoMeasurePollingEvent(void);
bit CMiscApplyDoubleBufferPollingEvent(void);
bit CMiscMeasureResultPOPPollingEvent(void);
bit CMiscTMDSMeasureEvent(void);
void CMiscEnableDoubleBuffer(void);
void CMiscDisableDoubleBuffer(void);
void CMiscApplyDoubleBuffer(void);
void CMiscClearStatusRegister(void);
void CMiscSetPinShare(void);
void CMiscKingmice(void);
void CMiscIspack(void);
void CMiscIspDebugProc(void);


void CDDCCIInitial(void);



#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------


#if(_DEBUG_TOOL == _ISP_FOR_RTD3580D_EMCU)

extern BYTE ucVirtualKey;
extern BYTE ucDdcciCommandNumber;
extern bit bRunCommand;
extern idata BYTE ucDdcciData[4];
extern BYTE TxBUF;

#endif



//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern bit CMiscScalerResetEvent(void);
//extern bit CMiscStableFlagPollingEvent(void);
extern bit CMiscHsyncTypeAutoRunFlagPollingEvent(void);
extern bit CMiscMeasureResultPOPPollingEvent(void);
extern bit CMiscModeMeasurePollingEvent(void);
extern bit CMiscAutoMeasurePollingEvent(void);
extern bit CMiscTMDSMeasureEvent(void);
extern bit CMiscTMDSCRCEvent(void);
extern void CMiscEnableDoubleBuffer(void);
extern void CMiscDisableDoubleBuffer(void);
extern void CMiscApplyDoubleBuffer(void);
extern void CMiscClearStatusRegister(void);
extern void CMiscSetPinShare(void);
extern void CMiscIspDebugProc(void);


extern void CDDCCIInitial(void);



#endif

void GetVirtualKey(void);
void CLoadEdid(void);
void CInitEdid(void);



//----------------------------------------------------------------------------------------------------

