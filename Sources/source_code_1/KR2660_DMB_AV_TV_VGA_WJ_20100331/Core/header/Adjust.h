//----------------------------------------------------------------------------------------------------
// ID Code      : Adjust.h No.0001
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Digital Filter
//--------------------------------------------------
#define _DISABLE_PORT                   0
#define _PHASE_ACCESS_PORT              1
#define _NEG_SMEAR_ACCESS_PORT          2
#define _POS_SMEAR_ACCESS_PORT          3
#define _NEG_RING_ACCESS_PORT           4
#define _POS_RING_ACCESS_PORT           5
#define _MISMATCH_ACCESS_PORT           6
#define _YPBPR_ACCESS_PORT              7
#define _NOISE_REDUCTION_PORT           8

#define _YPBPR_DISABLE                  0
#define _YPBPR_ENABLE                   7

#define _FUNCTION_DISABLE               0
#define _FUNCTION_ENABLE                1

#define _PHASE_THD_0                    0
#define _PHASE_THD_1                    1
#define _PHASE_THD_2                    2
#define _PHASE_THD_3                    3
#define _PHASE_THD_4                    4
#define _PHASE_THD_5                    5
#define _PHASE_THD_6                    6
#define _PHASE_THD_7                    7

#define _SMEAR_RING_THD_0               0
#define _SMEAR_RING_THD_1               1
#define _SMEAR_RING_THD_2               2
#define _SMEAR_RING_THD_3               3
#define _SMEAR_RING_THD_4               4
#define _SMEAR_RING_THD_5               5
#define _SMEAR_RING_THD_6               6
#define _SMEAR_RING_THD_7               7

#define _MISMATCH_THD_0                 0
#define _MISMATCH_THD_1                 1

#define _NOISE_REDUCTION_THD_0          0
#define _NOISE_REDUCTION_THD_1          1
#define _NOISE_REDUCTION_THD_2          2
#define _NOISE_REDUCTION_THD_3          3
#define _NOISE_REDUCTION_THD_4          4
#define _NOISE_REDUCTION_THD_5          5
#define _NOISE_REDUCTION_THD_6          6
#define _NOISE_REDUCTION_THD_7          7

#define _DIV_VALUE_0                    0
#define _DIV_VALUE_1                    1
#define _DIV_VALUE_2                    2
#define _DIV_VALUE_3                    3


//--------------------------------------------------
// Definitions of Coring Type
//--------------------------------------------------
#define _CORING_MIN                     3   // (0~5)
#define _CORING_MAX_POS                 50  // (50~60)
#define _CORING_MAX_NEG                 -50 // (-50~-60)

//--------------------------------------------------
// Definitions of Hor. Position Settings Used by COsdFxGetHPositionRange()
//--------------------------------------------------
#define _HPOSITION_BIAS                 (ucHStartBias  - abs(stModeInfo.IHStartPos - stModeUserCenterData.CenterHPos))
#define _GET_HPOSITIONRANGE_MAX         0
#define _GET_HPOSITIONRANGE_MIN         1


//--------------------------------------------------
// Definitions of Ver. Position Settings Used by COsdFxGetVPositionRange()
//--------------------------------------------------
#define _VPOSITION_BIAS                 (ucVStartBias - abs(stModeInfo.IVStartPos - stModeUserCenterData.CenterVPos))
#define _GET_VPOSITIONRANGE_MAX         0
#define _GET_VPOSITIONRANGE_MIN         1

/*
//--------------------------------------------------
// Definitions of Gamma Table Type
//--------------------------------------------------
#define _COMPACT_GAMMA_NORMAL_TABLE     0
#define _FULL_GAMMA_NORMAL_TABLE        1
#define _COMPACT_GAMMA_COMPRESS_TABLE   2
#define _FULL_GAMMA_COMPRESS_TABLE      3
*/

//--------------------------------------------------
// Definitions of TMDS Measurement
//--------------------------------------------------
#define _TMDS_MEASURE_HSYNC_BE          0x00
#define _TMDS_MEASURE_HSYNC_AF          0x01
#define _TMDS_MEASURE_DE_BE             0x02
#define _TMDS_MEASURE_DE_AF             0x03

#define _TMDS_MEASURE_AVE               0x00
#define _TMDS_MEASURE_MAX               0x01
#define _TMDS_MEASURE_MIN               0x02

#define _MEASURE_HSYNC                  0
#define _MEASURE_DE                     1


//--------------------------------------------------
// Definations of Watch Dogs
//--------------------------------------------------
#define _WD_DV_TIMEOUT                  0x20
#define _WD_APLL_NONLOCK                0x10
#define _WD_FRAMESYNC                   0x08
#define _WD_DV_TIMEOUT_APLL_NONLOCK     (_WD_DV_TIMEOUT | _WD_APLL_NONLOCK)
#define _WD_FRAMESYNC_APLL_NONLOCK      (_WD_APLL_NONLOCK | _WD_FRAMESYNC)
#define _WD_ALL                         (_WD_DV_TIMEOUT | _WD_APLL_NONLOCK | _WD_FRAMESYNC)


//--------------------------------------------------
// Definitions of Clock Settings Used by COsdFxGetAdcClockRange()
//--------------------------------------------------
#define _CLOCK_BIAS                     50
#define _GET_CLOCKRANGE_MAX             0
#define _GET_CLOCKRANGE_MIN             1


//--------------------------------------------------
// Definitions of Hor. Position Settings Used by COsdFxGetHPositionRange()
//--------------------------------------------------
#define _HPOSITION_BIAS                 (ucHStartBias  - abs(stModeInfo.IHStartPos - stModeUserCenterData.CenterHPos))
#define _GET_HPOSITIONRANGE_MAX         0
#define _GET_HPOSITIONRANGE_MIN         1


//--------------------------------------------------
// Definitions of Ver. Position Settings Used by COsdFxGetVPositionRange()
//--------------------------------------------------
#define _VPOSITION_BIAS                 (ucVStartBias - abs(stModeInfo.IVStartPos - stModeUserCenterData.CenterVPos))
#define _GET_VPOSITIONRANGE_MAX         0
#define _GET_VPOSITIONRANGE_MIN         1


//--------------------------------------------------
// Definitions of Contrast Range (Real Value)
//--------------------------------------------------

//#define _CONTRAST_MAX                   178
//#define _CONTRAST_MIN                   120//78


//--------------------------------------------------
// Definitions of Backlight Range
//--------------------------------------------------
#define _BACKLIGHT_MAX                  255
#define _BACKLIGHT_MIN                  0

//----------------------------------------------------------------------------------------------------

#ifdef _ADJUST_C
                               
//--------------------------------------------------
// Global Variables
//--------------------------------------------------
BYTE idata ucAdjustCtrl = 0;
WORD idata usPEValue = 120;

//080324
DWORD idata usPllDivider;
DWORD idata usPllDividerRem;
DWORD idata usIHFreqApllFast;

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CAdjustIHSDelay(WORD usIHSDelay);
void CAdjustIVSDelay(WORD usIVSDelay);
void CAdjustDclkOffset(WORD usDclkOffset);
void CAdjustSpreadSpectrumRange(BYTE ucSpreadRange);
void CAdjustSyncProcessorMeasureStart(void);
void CAdjustTMDSErrorCorrectionOn(void);
//void CAdjustTMDSErrorCorrectionOff(void);
BYTE CAdjustTMDSMeasure(BYTE ucType, BYTE ucSelect);
DWORD CAdjustTMDSCRCMeasure(void);
void CAdjustTMDSCRCCheck(void);
BYTE CAdjustTMDSEqualizerCheck(BYTE ucPar);
bit CAdjustTMDSEqualizer(void);
void CAdjustSetDigitalCapture(void);
BYTE CAdjustTMDSCRC(BYTE *pArray);
void CAdjustTMDSCaptureCheck(void);
void CAdjustEnableWatchDog(BYTE ucPar);
void CAdjustDisableWatchDog(BYTE ucPar);
//void CAdjustSRGB(void);
void CAdjustGamma(BYTE ucGammaTableType, BYTE *pGammaTableArrayR, BYTE *pGammaTableArrayG, BYTE *pGammaTableArrayB);
void CAdjustDither(BYTE *pDitherSeqTable, BYTE * pDitherTable);
void CAdjustSharpnessForScaleUp(void);
void CAdjustSharpnessForScaleDown(void);

void CAdjustSetSharpnessTable(bit scaling,BYTE code *pArray0, BYTE code *pArray1);

void CAdjustSetBrightness(void);
void CAdjustSetContrast(void);
void CAdjustVolume(void);
void CAdjustAdcGain(void);
void CAdjustAdcOffset(void);
void CAdjustAdcGainOffset(void);
void CAdjustBackgroundColor(BYTE ucRed, BYTE ucGreen, BYTE ucBlue);
void CAdjustColorPalette(BYTE *pColorPaletteArray);
BYTE CAdjustIVS2DVSDelay(BYTE ucOption);
void CAdjustDPLL(DWORD ulFreq, BYTE ucDpllNCode);
void CAdjustUpdateCenterData(void);
bit CAdjustCheckAdcClockRange(WORD usClock, WORD *delta);
//080324
///void CAdjustAdcClock(WORD usClock);
void CAdjustAdcClock(WORD usClock , BYTE ucControl);
void CAdjustAPLLFastLock(WORD usClock);
void CAdjustAdcClock_OSD(WORD usClock);
BYTE CAdjustGetAPLLSetting(WORD usClock);
void CAdjustPhase(BYTE ucPhase);
void CAdjustHPosition(void);
void CAdjustVPosition(void);
void CAdjustDigitalFilter(BYTE ucAccess, BYTE ucOffset, BYTE ucDiv, BYTE ucEnable);
void CAdjustSetYpbprRhue(void);
void CAdjustSetYpbprGhue(void);
void CAdjustSetYpbprBhue(void);
//void CAdjustSetYpbprSaturation(void);
void CAdjustInterlaceIVS2DVSProtection(void);
#if(_GAMMA_TYPE == _FULL_GAMMA_COMPRESS_TABLE2)
void CRtdWriteGamma(UINT8 *array);
#endif
        
#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE idata ucAdjustCtrl;
extern WORD idata usPEValue;

//080324
extern DWORD idata usPllDivider;
extern DWORD idata usPllDividerRem;
extern DWORD idata usIHFreqApllFast;
                  
//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CAdjustIHSDelay(WORD usIHSDelay);
extern void CAdjustIVSDelay(WORD usIVSDelay);
extern void CAdjustDclkOffset(WORD usDclkOffset);
extern void CAdjustSpreadSpectrumRange(BYTE ucSpreadRange);
extern void CAdjustSyncProcessorMeasureStart(void);
extern void CAdjustTMDSErrorCorrectionOn(void);
extern DWORD CAdjustTMDSCRCMeasure(void);
extern void CAdjustTMDSCRCCheck(void);
extern bit CAdjustTMDSEqualizer(void);
extern void CAdjustSetDigitalCapture(void);
extern void CAdjustTMDSCaptureCheck(void);
extern void CAdjustEnableWatchDog(BYTE ucPar);
extern void CAdjustDisableWatchDog(BYTE ucPar);
//extern void CAdjustSRGB(void);
extern void CAdjustGamma(BYTE ucGammaTableType, BYTE *pGammaTableArrayR, BYTE *pGammaTableArrayG, BYTE *pGammaTableArrayB);
extern void CAdjustDither(BYTE *pDitherSeqTable, BYTE * pDitherTable);
extern void CAdjustSharpnessForScaleUp(void);
extern void CAdjustSharpnessForScaleDown(void);
//extern void CAdjustPeakingCoding(void);
extern void CAdjustSetBrightness(void);
extern void CAdjustSetContrast(void);
extern void CAdjustVolume(void);
extern void CAdjustAdcGain(void);
extern void CAdjustAdcOffset(void);
extern void CAdjustAdcGainOffset(void);
extern void CAdjustBackgroundColor(BYTE ucRed, BYTE ucGreen, BYTE ucBlue);
extern void CAdjustColorPalette(BYTE *pColorPaletteArray);
extern BYTE CAdjustIVS2DVSDelay(BYTE ucOption);
extern void CAdjustDPLL(DWORD ulFreq, BYTE ucDpllNCode);
extern void CAdjustUpdateCenterData(void);
extern bit CAdjustCheckAdcClockRange(WORD usClock, WORD *delta);
//080324
///extern void CAdjustAdcClock(WORD usClock);
extern void CAdjustAdcClock(WORD usClock , BYTE ucControl);
extern void CAdjustAPLLFastLock(WORD usClock);
extern void CAdjustAdcClock_OSD(WORD usClock);
extern BYTE CAdjustGetAPLLSetting(WORD usClock);
extern void CAdjustPhase(BYTE ucPhase);
extern void CAdjustHPosition(void);
extern void CAdjustVPosition(void);
extern void CAdjustDigitalFilter(BYTE ucAccess, BYTE ucOffset, BYTE ucDiv, BYTE ucEnable);

extern void CAdjustSetYpbprRhue(void);
extern void CAdjustSetYpbprGhue(void);
extern void CAdjustSetYpbprBhue(void);
extern void CAdjustSetYpbprSaturation(void);
extern void CAdjustInterlaceIVS2DVSDelay(void);
extern void CAdjustInterlaceIVS2DVSProtection(void);
#if(_GAMMA_TYPE == _FULL_GAMMA_COMPRESS_TABLE2)
extern void CRtdWriteGamma(UINT8 *array);
#endif
   
extern void CAdjustAdcClockYPbPr(WORD usClock);
   
#endif


//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Macro of Start Display
//--------------------------------------------------
#define GET_FIRST_ADCCLOCK()        ((bit)(ucAdjustCtrl & _BIT0))
#define SET_FIRST_ADCCLOCK()        (ucAdjustCtrl |= _BIT0)
#define CLR_FIRST_ADCCLOCK()        (ucAdjustCtrl &= ~_BIT0)


//--------------------------------------------------
// Macro of Mode Search Type
//--------------------------------------------------
#define GET_MODE_SEARCH_TYPE()      ((bit)(ucAdjustCtrl & _BIT1))
#define SET_MODE_SEARCH_TYPE(x)     (ucAdjustCtrl = ((ucAdjustCtrl & ~(_BIT1)) | (x << 1)))


//--------------------------------------------------
// Macro of DVI Use Transition Result Flag
//--------------------------------------------------
#define GET_USE_TRANSITION_RESULT() ((bit)(ucAdjustCtrl & _BIT2))
#define SET_USE_TRANSITION_RESULT() (ucAdjustCtrl |= _BIT2)
#define CLR_USE_TRANSITION_RESULT() (ucAdjustCtrl &= ~_BIT2)

