//----------------------------------------------------------------------------------------------------
// ID Code      : RTD2528R_Hdmi.h No.0000
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------
#define _HM_480I			0
#define _HM_480P			1
#define _HM_576I			2
#define _HM_576P			3
#define _HM_720P			4
#define _HM_1080I			5
#define _HM_1080P			6
#define _HM_OTHER			7


//--------------------------------------------------
// Definitions of MCK Frequence
//--------------------------------------------------
#define _AUDIO_128_TIMES        1
#define _AUDIO_256_TIMES        2

#define _AUDIO_MCK_32000        _AUDIO_256_TIMES
#define _AUDIO_MCK_44100        _AUDIO_256_TIMES
#define _AUDIO_MCK_48000        _AUDIO_256_TIMES
#define _AUDIO_MCK_88200        _AUDIO_256_TIMES
#define _AUDIO_MCK_96000        _AUDIO_256_TIMES
#define _AUDIO_MCK_176400       _AUDIO_128_TIMES
#define _AUDIO_MCK_192000       _AUDIO_128_TIMES

//--------------------------------------------------
// Definitions of DAC
//--------------------------------------------------
#define _DAC_DEVICE_ADDR        0x20    //CS4360
#define _DAC_CONTROL_ADDR       0x01

#define _HDMI_CHECK_CNT							5	//741001
#define _HDMI_NO_SIGNAL_CHECK_CNT	15	// 4 //741001
//----------------------------------------------------------------------------------------------------
#if(_HDMI_SUPPORT == _ON)
#ifdef __HDMI__

//--------------------------------------------------
// Global Hdmi Table
//--------------------------------------------------

BYTE code tHDMI_YPBPR_ITU601[] =
{
    // 9CH
    21, _NON_AUTOINC,   _YUV_RGB_COEF_DATA_9D,          0x04,0x00,0x00,0x00,0x05,0x9b,
                                                        0x04,0x00,0xfe,0xaa,0xfd,0x25,
                                                        0x04,0x00,0x07,0x16,0x00,0x00,
    _END
};

BYTE code tHDMI_YPBPR_ITU709[] =
{
    // 9CH
    21, _NON_AUTOINC,   _YUV_RGB_COEF_DATA_9D,          0x04,0x00,0x00,0x00,0x06,0x4b,
                                                        0x04,0x00,0xff,0x41,0xfe,0x20,
                                                        0x04,0x00,0x07,0x6c,0x00,0x00,
    _END
};

BYTE code tSCALER_POWERUP_HDMI[] =
{
	4,  	_NON_AUTOINC,   	_PAGE_SELECT_9F,                	_PAGE2,
	11, 	_AUTOINC,       	_P2_TMDS_OUTPUT_CTRL_A6,    	0x78,0x6F,0x03,0x00,0x70,0x70,0xe3,0x24,////Alanli20070801
    _END
};

BYTE code tHDCP_CTRL[] =
{
    4,   	_NON_AUTOINC,   	_PAGE_SELECT_9F,                	_PAGE2,
    4,   	_NON_AUTOINC,   	_P2_HDCP_PORT_CTRL_C2,          	0x01,
    5,   	_AUTOINC,       	_P2_HDCP_ADDR_PORT_C3,          	0x00,0xb7,
    5,   	_AUTOINC,       	_P2_HDCP_ADDR_PORT_C3,          	0x01,0x28,
    5,   	_AUTOINC,       	_P2_HDCP_ADDR_PORT_C3,          	0x02,0xa9,
    5,   	_AUTOINC,       	_P2_HDCP_ADDR_PORT_C3,          	0x03,0x51,
    5,   	_AUTOINC,       	_P2_HDCP_ADDR_PORT_C3,          	0x04,0xd6,
    5,   	_AUTOINC,       	_P2_HDCP_ADDR_PORT_C3,          	0x40,0x91,
    _END
};


//--------------------------------------------------
// Global Variables
//--------------------------------------------------
BYTE idata ucHdmiCtrl = 0;
BYTE ucHdmiTimerEvent = 0;//741001
BYTE ucHdmiAVMuteCnt  = 0;
BYTE ucHDMIMode = _HM_OTHER;
//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
bit CHdmiFormatDetect(void);
bit CHdmiAudioFIFODetect(void);
void CHdmiAudioModeDetect(void);
bit CHdmiVideoSetting(void);
//void CHdmiResetDAC(void);
void CHdmiAdjustDACSampleRate(BYTE ucModeType);
void CHdmiAudioWaitingFlagReadyEven(void);
void CHdmiAudioFirstTracking(void);
void CHdmiEnableAudioOutput(void);
void CHdmiModeChange();//741001
#if (_HDMI_SUPPORT && _HDMI_HOT_PLUG_OPTION == _ENABLE)   //2007-8-23 15:36
//eric 20070326 philips DVD
	BYTE ucHDMIChangeCnt=0;
	BIT bHDMIFrameOk=0; //Confirm 5 times 
	BYTE ucHDMIFrameOkCnt=0;
//20070409, philips DVP5960 unstable
	#define _HDMI_OK_CNT 7
	#define _HDMI_CHANGE_CNT 10///4
//eric 20070326 philips DVD
	void CHDMIStableConfirm(void);
	void CModeHDMIChageDelay(void);
void CAdjustHDCP(void);
#endif
void CAdjustHdmiCbCr422(void); //730702
void CAdjustEnableHDMIWatchDog(BYTE ucPar);//731301
void CAdjustDisableHDMIWatchDog(BYTE ucPar);//731301

#else

//--------------------------------------------------
// Extern Global Hdmi Edid Data
//--------------------------------------------------
extern BYTE code tSCALER_POWERUP_HDMI[] ;


//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE idata ucHdmiCtrl;
extern BYTE ucHdmiTimerEvent;//741001
extern BYTE ucHDMIMode;
extern BYTE ucHdmiAVMuteCnt;

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern bit CHdmiFormatDetect(void);
extern bit CHdmiAudioFIFODetect(void);
extern bit CHdmiVideoSetting(void);
extern void CHdmiAudioModeDetect(void);
//extern void CHdmiResetDAC(void);
extern void CHdmiAdjustDACSampleRate(BYTE ucModeType);
extern void CHdmiAudioWaitingFlagReadyEven(void);
extern void CHdmiAudioFirstTracking(void);
extern void CHdmiEnableAudioOutput(void);
extern void CHdmiModeChange();//741001

extern void CModeHDMIChageDelay(void);
extern void CAdjustHdmiCbCr422(void); //730702
extern void CAdjustEnableHDMIWatchDog(BYTE ucPar);//731301
extern void CAdjustDisableHDMIWatchDog(BYTE ucPar);//731301

#if (_HDMI_HOT_PLUG_OPTION == _ENABLE)   //2007-8-23 15:36
extern BYTE ucHDMIChangeCnt;
extern BIT bHDMIFrameOk; //Confirm 5 times 
extern BYTE ucHDMIFrameOkCnt;
extern void CHDMIStableConfirm(void);
extern void CAdjustHDCP(void);
#endif

#endif

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Definations of HDMI Watch Dog Control
//--------------------------------------------------
#define _WD_SET_AVMUTE_ENABLE           0x01
#define _WD_AUDIO_FOR_TMDS_CLOCK        0x02
#define _WD_PACKET_VARIATION            0x04
#define _WD_AUDIO_FIFO                  0x08
#define _WD_HDMI_ALL                    (_WD_SET_AVMUTE_ENABLE | _WD_AUDIO_FOR_TMDS_CLOCK | _WD_PACKET_VARIATION | _WD_AUDIO_FIFO)

#endif
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Macro of Input source is the HDMI format
//--------------------------------------------------
#define GET_HDMIINPUT()             (bit)(ucHdmiCtrl & _BIT0)
#define SET_HDMIINPUT()             ucHdmiCtrl |= _BIT0
#define CLR_HDMIINPUT()             ucHdmiCtrl &= ~_BIT0


//--------------------------------------------------
// Macro of HDMI Audio PLL Lock Ready Flag
//--------------------------------------------------
#define GET_AUDIOPLLLOCKREADY()        (bit)(ucHdmiCtrl & _BIT1)
#define SET_AUDIOPLLLOCKREADY()        ucHdmiCtrl |= _BIT1
#define CLR_AUDIOPLLLOCKREADY()        ucHdmiCtrl &= ~_BIT1


//--------------------------------------------------
// Macro of HDMI Audio Resume Flag
//--------------------------------------------------
#define GET_AVRESUME()             (bit)(ucHdmiCtrl & _BIT2)
#define SET_AVRESUME()             ucHdmiCtrl |= _BIT2
#define CLR_AVRESUME()             ucHdmiCtrl &= ~_BIT2


//--------------------------------------------------
// Macro of HDMI Audio Waiting Time Flag
//--------------------------------------------------
#define GET_AUDIOWAITINGFLAG()     (bit)(ucHdmiCtrl & _BIT3)
#define SET_AUDIOWAITINGFLAG()     ucHdmiCtrl |= _BIT3
#define CLR_AUDIOWAITINGFLAG()     ucHdmiCtrl &= ~_BIT3


//--------------------------------------------------
// Macro of HDMI Audio Waiting Time Out Flag
//--------------------------------------------------
#define GET_AUDIOWAITINGTIMEOUT()  (bit)(ucHdmiCtrl & _BIT4)
#define SET_AUDIOWAITINGTIMEOUT()  ucHdmiCtrl |= _BIT4
#define CLR_AUDIOWAITINGTIMEOUT()  ucHdmiCtrl &= ~_BIT4

//741001***
//--------------------------------------------------
// Macro of HDMI Show Search Flag
//--------------------------------------------------
#define GET_HDMISHOWSEARCH()  (bit)(ucHdmiCtrl & _BIT5)
#define SET_HDMISHOWSEARCH()  ucHdmiCtrl |= _BIT5
#define CLR_HDMISHOWSEARCH()  ucHdmiCtrl &= ~_BIT5

//--------------------------------------------------
// Macro of HDMI Mode Change Flag
//--------------------------------------------------
#define GET_HDMISTABLE()  (bit)(ucHdmiCtrl & _BIT6)
#define SET_HDMISTABLE()  ucHdmiCtrl |= _BIT6
#define CLR_HDMISTABLE()  ucHdmiCtrl &= ~_BIT6
//741001###

#else


#endif //End of #if(_HDMI_SUPPORT == _ON)

extern BYTE code cCodeHDMITemp;


