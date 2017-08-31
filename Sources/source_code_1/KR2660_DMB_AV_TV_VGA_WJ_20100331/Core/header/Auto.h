//----------------------------------------------------------------------------------------------------
// ID Code      : Auto.h No.0001
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Minumum Noise Margin
//--------------------------------------------------
#define _MIN_NOISE_MARGIN           0x50


//--------------------------------------------------
// Color Source Select for Detection
//--------------------------------------------------
#define _COLORS_BLUE                0x00
#define _COLORS_GREEN               0x01
#define _COLORS_RED                 0x02
#define _COLORS_ALL                 0x03

#define _COLOR_SELECT               _COLORS_ALL

//--------------------------------------------------
// Definations of Measure Color
//--------------------------------------------------
#define _MEASURE_COLORS_MIN         0x00
#define _MEASURE_COLORS_MAX         0x01


//--------------------------------------------------
// White Balance Max/Min Level Settings
//--------------------------------------------------
#define _WHITEBALANCE_MAX_LEVEL     250 //242
#define _WHITEBALANCE_MIN_LEVEL     2



//--------------------------------------------------
// Setting of Auto Black Level
//--------------------------------------------------
#define _TOTAL_LINES_OF_ABL         1   //N*32 lines, N=1~8
#define _START_POSITION_OF_ABL      4   //Start position of ABL in each line (0~63)



//--------------------------------------------------
// Hardware Auto Phase Step
//--------------------------------------------------
#define _HWAUTO_STEP_1              0x00
#define _HWAUTO_STEP_2              0x01
#define _HWAUTO_STEP_4              0x02
#define _HWAUTO_STEP_8              0x03
#define _HWAUTO_STEP_16             0x04

#define _HWAUTO_STEP                _HWAUTO_STEP_2


//--------------------------------------------------
// Auto Clock Precision (Unit in Clock Number)
//--------------------------------------------------
#define _AUTO_CLOCK_PRECISION_1     1
#define _AUTO_CLOCK_PRECISION_2     2

#define _AUTO_CLOCK_PRECISION       _AUTO_CLOCK_PRECISION_2


//--------------------------------------------------
// Definitions of Auto Function
//--------------------------------------------------
#define _ERROR_SUCCESS              0x00
#define _ERROR_FINISH               0x40
#define _ERROR_ABORT                0x80
#define _ERROR_INPUT                0xff
#define _ERROR_PHASE                0xfe


//----------------------------------------------------------------------------------------------------

#ifdef __AUTO__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
bit bDoAutoConfigFlag = _FALSE;
bit bDoAspectRatioFlag = _FALSE;

WORD idata usHStartPos;
WORD idata usHEndPos;
WORD idata usVStartPos;
WORD idata usVEndPos;

typedef struct
{
	UINT8 Y_ADC_GAIN;
	UINT8 U_ADC_GAIN;
	UINT8 V_ADC_GAIN;	
	UINT8 Y_ADC_OFFSET;
	UINT8 U_ADC_OFFSET;
	UINT8 V_ADC_OFFSET;
}ADCRGBYUV_2547D;

enum YPbPrModeDef
{
 _MODE_576I = 0,         
 _MODE_480I,           	
 _MODE_576P,    		// 720x 576px50HZ (802R)
 _MODE_480P,  			// 720x 480px50HZ (802R)
 _MODE_720P60,   		// 1280x 720px60HZ (802R) //forster modified 050823 
 _MODE_1080I25,    	// 1920x1080ix50HZ (802R) //forster modified 050823 
 _MODE_1080I30,   	// 1920x1080ix60HZ (802R) //forster modified 050823
 _MODE_720P50,   		// 1280x 720px50HZ        //forster modified 050823 
 _MODE_1080P50,    	// 1920x1080px50HZ (802R) //forster modified 050823
 _MODE_1080P60 		// 1920x1080px60HZ (802R) //forster modified 050823
};

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
BYTE CAutoDoAutoConfig(void);
BYTE CAutoWaitFinish(void);
BYTE CAutoWaitForIVS(BYTE ucTimes);
BYTE CAutoMeasurePositionH(BYTE ucNoiseMarginH);
BYTE CAutoMeasurePositionV(BYTE ucNoiseMarginV);
DWORD CAutoPhaseSearch(BYTE ucSelColor, BYTE ucSelStep, BYTE ucSelStepNum, BYTE ucSelStepStart, BYTE *ucPhaseResult);
BYTE CAutoReadPhaseInfo(BYTE ucColor);
BYTE CAutoDoAutoClock(void);
BYTE CAutoDoAutoPhase(void);
BYTE CAutoDoAutoPosition(void);
BYTE CAutoDoWhiteBalance(void);
BYTE CAutoTuneBalance(void);
#if(_YPBPR_AUTO_TYPE==_NEW_TYPE)
BYTE CAutoTuneBalanceNew(void);
void CYPbPrPorch_LevelCheck(void);
//void ADC_Swap_Check_2547D(ADCRGBYUV_2547D *Swap);
#endif
BYTE CAutoMeasureColor(BYTE ucColor, BYTE ucPar, BYTE *pMargin);
BYTE CAutoTuneDeviceGain(BYTE ucColor, BYTE *pMargin, BYTE ucMax_Target); //forster modified 061002
BYTE CAutoTuneDeviceOffset(BYTE ucColor, BYTE *pMargin, BYTE ucMin_Target); //forster modified 061002
BYTE CAutoChangeAdcGain(BYTE ucColor, BYTE ucDelta, BYTE ucInc);
BYTE CAutoChangeAdcOffset(BYTE ucColor, BYTE ucDelta, BYTE ucInc);
BYTE CAutoAdjustAdcOffset(void);

#if(_VIDEO_AUTO_WHITE_BLANCE == _ENABLE)
UINT8 Change_VDC_Gain(UINT8 color, UINT8 delta,UINT8 inc);
UINT8 Change_VDC_Offset(UINT8 color, UINT8 delta,UINT8 inc);
#endif

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern bit bDoAutoConfigFlag;
extern bit bDoAspectRatioFlag;

//730702***
extern WORD idata usHStartPos;
extern WORD idata usHEndPos;
extern WORD idata usVStartPos;
extern WORD idata usVEndPos;
//730702###

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern BYTE CAutoDoAutoConfig(void);
extern BYTE CAutoDoWhiteBalance(void);
extern BYTE CAutoAdjustAdcOffset(void);
//730702***
extern BYTE CAutoMeasurePositionH(BYTE);
extern BYTE CAutoMeasurePositionV(BYTE);
extern BYTE CAutoWaitFinish(void);
//730702###

extern void CYPbPrPorch_LevelCheck(void);
#endif


//----------------------------------------------------------------------------------------------------


#define HWAUTOSTEPNUM(x)                    x
#define HWAUTOSTEPSTART(x)                  x


