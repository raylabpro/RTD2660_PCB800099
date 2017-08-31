//----------------------------------------------------------------------------------------------------
// ID Code      : Scaler.h No.0002
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Scaler
//--------------------------------------------------

//----------------------------------------------------------------------------------------------------

#ifdef __SCALER__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
BYTE data ucVLDCnt, ucVLDTemp;
BYTE code *pvldarray;


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CScalerInitial(void);
void CScalerResetInForResetIn(void);
void CScalerReset(void);
void CScalerInitialDisplayInterface(void);
void CScalerInitialDisplayOutput(void);
void CScalerEnableDisplayOutput(void);
void CScalerDisableDisplayOutput(void);
void CScalerGetDataPortByte(BYTE ucAddr, BYTE ucValue, BYTE ucLength, BYTE *pArray, BIT bAutoInc);

#if(_NONLINEAR_SCALING)

void CScalerDisableNonlinearScaleUp(void);
void CScalerDisableNonlinearScaleDown(void);

void CScalerNonlinearScaleUp(BYTE Option);
void CScalerNonlinearScaleDown(BYTE Option);
#endif


#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE data ucVLDCnt, ucVLDTemp;
extern BYTE code *pvldarray;


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CScalerInitial(void);
extern void CScalerResetInForResetIn(void);
extern void CScalerEnableDisplayOutput(void);
extern void CScalerDisableDisplayOutput(void);
extern void CScalerReset(void);
extern void CScalerGetDataPortByte(BYTE ucAddr, BYTE ucValue, BYTE ucLength, BYTE *pArray, BIT bAutoInc);

#if(_NONLINEAR_SCALING)

extern void CScalerDisableNonlinearScaleUp(void);
extern void CScalerDisableNonlinearScaleDown(void);

extern void CScalerNonlinearScaleUp(BYTE Option);
extern void CScalerNonlinearScaleDown(BYTE Option);
#endif


#endif


//----------------------------------------------------------------------------------------------------

