//----------------------------------------------------------------------------------------------------
// ID Code      : Mode.h No.0001
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of
//--------------------------------------------------


//----------------------------------------------------------------------------------------------------

#ifdef __MODE__

//RGB -> YUV
//RGB Source(OnSource601rgb)		
//REG 9C=0x11
//m_M11 = +0.2990 ;	m_M21 = -0.1687 ;	 m_M31 = +0.5000 ;
//m_M12 = +0.5870 ;	m_M22 = -0.3313 ;	 m_M32 = -0.4187 ;
//m_M13 = +0.1140 ;	m_M23 = +0.5000 ;	 m_M33 = -0.0813 ;
//M11 = 0x01,0x32 	//M12 = 0x02,0x59 	//M13 = 0x00,0x74 
//M21 = 0xFF,0x54 		//M22 = 0xFE,0xAD 	//M23 = 0x02,0x00 
//M31 = 0x02,0x00 	//M32 = 0xFE,0x54 	//M33 = 0xFF,0xAD
BYTE code tRGB2YUV601_TABLE_FOR_RGB_SOURCE[] =
{                   
//20080114***
#if 0
	4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,             0x00,	//reset data port addr to 0. 
	4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,             0x08,	//enable YVU/RGB coeff access
	21, _NON_AUTOINC,   _YUV_RGB_COEF_DATA_9D,          
																					0x01,0x32,0x02,0x59,0x00,0x74,
																					0xFF,0x54,0xFE,0xAD,0x02,0x00,
																					0x02,0x00,0xFE,0x54,0xFF,0xAD,
	4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,				0x17,		//RGB->YUV & enable
#else
	    4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,               0x18,
    21, _NON_AUTOINC,   _YUV_RGB_COEF_DATA_9D,          0x01,0x32,0x02,0x59,0x00,0x75,
                                                        0xFF,0x53,0xFE,0xAD,0x02,0x00,
                                                        0x02,0x00,0xFE,0x53,0xFF,0xAD,
    4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,               0x17,
#endif
//20080114###
    _END
};
	//RGB Source(OnSource709rgb)		
	//REG 9C=0x11
	//m_M11 = 0.2974;		m_M21 = -0.1690;	m_M31 = 0.5000 ;	
	//m_M12 = 0.5897;		m_M22 = -0.3310;	m_M32 = -0.4188;	
	//m_M13 = 0.1129;		m_M23 = 0.5000;		m_M33 = -0.0812;
	//M11 = 0x01,0x30		//M12 = 0x02,0x5B		//M13 = 0x00,0x73 
	//M21 = 0xFF,0x53 		//M22 = 0xFE,0xAE 	//M23 = 0x01,0xFF 
	//M31 = 0x02,0x00 	//M32 = 0xFE,0x54 	//M33 = 0xFF,0xAD
BYTE code tRGB2YUV709_TABLE_FOR_RGB_SOURCE[] =
{
	4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,             0x00,	//reset data port addr to 0. 
	4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,             0x08,	//enable YVU/RGB coeff access
	21, _NON_AUTOINC,   _YUV_RGB_COEF_DATA_9D,        0x01,0x30,0x02,0x5B,0x00,0x73,
													  0xFF,0x53,0xFE,0xAE,0x01,0xFF,
													  0x02,0x00,0xFE,0x54,0xFF,0xAD,
	4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,			  0x11,		//RGB->YUV & enable
    _END
};

	//!RGB Source(OnSource601rgb)		
	//REG 9C = 0x00
BYTE code tRGB2YUV601_TABLE_FOR_NON_RGB_SOURCE[] =
{
	4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,             0x00,	//disable RGB->YUV conv 
    _END
};

	//!RGB Source(OnSource709rgb)		
	//REG 9C = 0x00
BYTE code tRGB2YUV709_TABLE_FOR_NON_RGB_SOURCE[] =
{
	4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,             0x00,	//disable RGB->YUV conv 
    _END
};

//YUV->RGB
	//VGA source
	//page7 0xc0(2) = 0 & 0xc0(3) = 1	 
	//for 601: 
	//0x04, 0x00, // k11
	//0x05, 0x9B, // k13
	//0x01, 0x60, // k22
	//0x02, 0xDB, // k23
	//0x07, 0x16, // k32
	//0x00, 0x00, // R-offset
	//0x00, 0x00, // G-offset
	//0x00, 0x00, // B-offset
BYTE code tYUV2RGB601_TABLE_FOR_RGB_SOURCE[] =
{
//20080114***
#if 1 
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                	_PAGE7,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,        	0x02,				//enable YUV->RGB coeff access
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,         	0x0C,0x04,	//K11 MSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x1C,0x00,	//K11 LSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x2C,0x05,	//K13 MSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x3C,0x9B,	//K13 LSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x4C,0x01,	//K22 MSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x5C,0x60,	//K22 LSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x6C,0x02,	//K23 MSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x7C,0xDB,	//K23 LSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x8C,0x07,	//K32 MSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x9C,0x16,	//K32 LSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0xAC,0x00,	//ROffset MSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0xBC,0x00,	//ROffset LSB	
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0xCC,0x00,	//GOffset MSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0xDC,0x00,	//GOffset LSB	
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0xEC,0x00,	//BOffset MSB	
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0xFC,0x00,	//GOffset LSB	
    4,  _NON_AUTOINC,   _P7_YUV2RGB_ACCESS_C0,      		0x08,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,           		0x01,		//enable YUV->RGB conv
 #else
     4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE7,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,            0x02,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x0C,0x04,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x1C,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x2C,0x05,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x3C,0x9B,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x4C,0x01,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x5C,0x56,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x6C,0x02,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x7C,0xDB,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x8C,0x07,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x9C,0x16,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0xAC,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0xBC,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0xCC,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0xDC,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0xEC,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0xFC,0x00,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_ACCESS_C0,          0x0c,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,            0x01,
 #endif
//20080114###
    _END
};

#if(_TMDS_SUPPORT == _ON)
BYTE code tYUV2RGB601_TABLE_FOR_DVI_SOURCE[] =
{
//20080114***
#if 0 
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                	_PAGE7,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,        	0x02,				//enable YUV->RGB coeff access
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,         	0x0C,0x04,	//K11 MSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x1C,0xA7,	//K11 LSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x2C,0x05,	//K13 MSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x3C,0x9B,	//K13 LSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x4C,0x01,	//K22 MSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x5C,0x60,	//K22 LSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x6C,0x02,	//K23 MSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x7C,0xDB,	//K23 LSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x8C,0x07,	//K32 MSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x9C,0x16,	//K32 LSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0xAC,0x00,	//ROffset MSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0xBC,0x00,	//ROffset LSB	
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0xCC,0x00,	//GOffset MSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0xDC,0x00,	//GOffset LSB	
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0xEC,0x00,	//BOffset MSB	
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0xFC,0x00,	//GOffset LSB	
    4,  _NON_AUTOINC,   _P7_YUV2RGB_ACCESS_C0,      0x0C,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,           0x01,				//enable YUV->RGB conv
 #else
     4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE7,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,            0x02,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x0C,0x04,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x1C,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x2C,0x05,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x3C,0x9B,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x4C,0x01,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x5C,0x56,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x6C,0x02,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x7C,0xDB,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x8C,0x07,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x9C,0x16,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0xAC,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0xBC,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0xCC,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0xDC,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0xEC,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0xFC,0x00,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_ACCESS_C0,          0x0c,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,            0x01,
 #endif
//20080114###
    _END
};
#endif // end #if(_TMDS_SUPPORT == _ON)

	//!VGA source
	//page7 0xc0(2) = 1 & 0xc0(3) = 1
	//for 601:
	//0x04, 0xA7, // k11
	//0x05, 0x9B, // k13
	//0x01, 0x60, // k22
	//0x02, 0xDB, // k23
	//0x07, 0x16, // k32
	//0x00, 0x00, // R-offset
	//0x00, 0x00, // G-offset
	//0x00, 0x00, // B-offset
BYTE code tYUV2RGB601_TABLE_FOR_NON_RGB_SOURCE[] =
{
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE7,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,            0x02,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x0C,0x04,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x1C,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x2C,0x05,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x3C,0x9B,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x4C,0x01,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x5C,0x56,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x6C,0x02,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x7C,0xDB,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x8C,0x07,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0x9C,0x16,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0xAC,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0xBC,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0xCC,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0xDC,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0xEC,0x00,
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          0xFC,0x00,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_ACCESS_C0,          0x0c,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,            0x01,
    _END
};

	//!VGA source
	//page7 0xc0(2) = 1 & 0xc0(3) = 1
	//for 709:
	//0x04, 0xA7, 	// k11
	//0x06, 0x4C, 	// k13
	//0x00, 0xBF, 	// k22
	//0x01, 0xDF, // k23
	//0x07, 0x6C, // k32
	//0x00, 0x00, // R-offset
	//0x00, 0x00, // G-offset
	//0x00, 0x00, // B-offset
BYTE code tYUV2RGB709_TABLE_FOR_NON_RGB_SOURCE[] =
{
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                	_PAGE7,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,        	0x02,				//enable YUV->RGB coeff access
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,         	0x0C,0x04,	//K11 MSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x1C,0xA7,	//K11 LSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x2C,0x06,	//K13 MSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x3C,0x4C,	//K13 LSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x4C,0x00,	//K22 MSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x5C,0xBF,	//K22 LSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x6C,0x01,	//K23 MSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x7C,0xDF,	//K23 LSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x8C,0x07,	//K32 MSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0x9C,0x6C,	//K32 LSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0xAC,0x00,	//ROffset MSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0xBC,0x00,	//ROffset LSB	
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0xCC,0x00,	//GOffset MSB
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0xDC,0x00,	//GOffset LSB	
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0xEC,0x00,	//BOffset MSB	
    5,  _AUTOINC,       _P7_YUV2RGB_ACCESS_C0,          	0xFC,0x00,	//GOffset LSB	
    4,  _NON_AUTOINC,   _P7_YUV2RGB_ACCESS_C0,      0x0C,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,           0x01,				//enable YUV->RGB conv
    _END
};

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
bit bShowOSDCurr = 0;
BYTE idata ucCurrState = _PWOFF_STATE;
BYTE idata ucModeControl = 0;
BYTE idata ucEvent0 = 255;
BYTE idata ucEvent1 = 255;
BYTE idata ucModeFound;
BYTE idata ucHStartBias;
BYTE idata ucVStartBias;
WORD xdata HDMI_H_Width;
WORD xdata HDMI_V_Height;


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CModeHandler(void);
bit CModeMeasureReady(void);
bit CModeMeasureData(void);
bit CModeDetect(void);
bit CModeDetectCommon(void);
bit CModeIsChange(void);
BYTE CModeSearchDisplayMode(void);
BYTE CModeSearchModeVGA(void);
bit CModeComparePresetModeVGA(BYTE ucModeCnt);
BYTE CModeSearchAcceptiveModeVGA(void);
BYTE CModeCheckFIFOModeVGA(BYTE ucModeCnt);
bit CModeCompareFIFOModeVGA(BYTE ucNum, BYTE ucModeCnt);
BYTE CModeSearchModeDVI(void);
bit CModeCompareModeDVI(BYTE ucModeCnt);
bit CModeDisplayActiveMode(void);
bit CModeSetupModeVGA(void);
bit CModeSetupModeDVI(void);
void CModeSetupDisplay(void);
void CModeSetupColorProcess(void);
void CModeSetupColorConversion(void);//jerry20070605
void CModeSetupEtcs(BYTE ucPar);
void CModeGetModeTableInfo(void);
void CModeStartUpVGA(void);
void CModeStartUpDVI(void);
BYTE CModeGetScaleSetting(void);
void CModeSetCaptureWindow(BYTE ucOption);
void CModeSetScaling(BYTE ucOption);
void CModeSetDisplay(BYTE ucOption);
void CModeModifyVTotal(void);
void CModeResetMode(void);
void CModeSetFreeRun(void);
bit CModeConnectIsChange(void);
void CModeAutoMeasureOn(void);
void CModeAutoMeasureOff(void);
void CModeSyncTimeoutCountDownEvent(void);
void CModeStableCountDownEvent(void);

void CModePowerSavingEvent(void);
/*
void CModeNoSignalEvent(void);
void CModeNoCableEvent(void);
void CModeNoSupportEvent(void);
*/
BYTE CModeGetScaleSetting(void);
void CModeHDMITimeoutCountDownEvent();
void CModeInterlaceCheck(void);//v003_interlace_check
void CModeDeInterlaceSetting(void);

void CModeNoSupportEvent(void);
void CModeNoSignalEvent(void);
void CModeNoCableEvent(void);
void COsdDispOsdTimerEvent(void);

void ModeLimit();

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern bit bShowOSDCurr;
extern BYTE idata ucCurrState;
extern BYTE idata ucModeControl;
extern BYTE idata ucHStartBias;
extern BYTE idata ucVStartBias;
extern UINT16 xdata HDMI_H_Width,HDMI_V_Height;
extern BYTE idata ucModeFound;
extern BYTE idata ucEvent1;


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CModeHandler(void);
extern bit CModeMeasureReady(void);
extern bit CModeMeasureData(void);
extern bit CModeDetect(void);
extern bit CModeIsChange(void);
extern void CModeSetScaling(BYTE ucOption);
extern void CModeResetMode(void);
extern void CModeSetFreeRun(void);
extern void CModeSyncTimeoutCountDownEvent(void);
extern void CModeStableCountDownEvent(void);
extern void CModeSetupDisplay(void);
extern void CModeSetupColorProcess(void);
extern void CModeSetupColorConversion(void);//jerry20070605
extern void CModeSetupEtcs(BYTE ucPar);
extern void CModeStartUpVGA(void);
extern void CModeAutoMeasureOn(void);
extern void CModeAutoMeasureOff(void);
extern bit CModeDisplayActiveMode(void);
extern bit CModeConnectIsChange(void);
extern void CModePowerSavingEvent(void);
extern BYTE CModeGetScaleSetting(void);
extern bit CModeSetupModeVGA(void);
extern void CModeHDMITimeoutCountDownEvent();
extern void CModeInterlaceCheck(void);//v003_interlace_check
extern void CModeDeInterlaceSetting(void);
extern void CModeSetCaptureWindow(BYTE ucOption);
extern void CModeSetDisplay(BYTE ucOption);


extern void CModeNoSupportEvent(void);
extern void CModeNoSignalEvent(void);
extern void CModeNoCableEvent(void);
extern void COsdDispOsdTimerEvent(void);


extern void CAccAdjust (BYTE mode);

#if (_HDMI_HOT_PLUG_OPTION == _ENABLE)   //2007-8-23 15:36
//eric 20070315
	void CModeHdmiHP(void);
//eric 20070315
	extern void CModeHdmiHP(void);
#endif
#endif



void COsdTimeOut(void);

//--------------------------------------------------
// Macro of Sync Processor Measure Ready Flag
//--------------------------------------------------
#define GET_VIDEOMODECHANGE()       (bit)(ucInputSyncType & _BIT6)
#define SET_VIDEOMODECHANGE()       ucInputSyncType |= _BIT6
#define CLR_VIDEOMODECHANGE()       ucInputSyncType &= ~_BIT6
//--------------------------------------------------
// Macro of Start Display for OSD Flow
//--------------------------------------------------

#define GET_SHOW_NO_SIGNAL()        (bit)(ucModeControl & _BIT0)
#define SET_SHOW_NO_SIGNAL()        ucModeControl |= _BIT0
#define CLR_SHOW_NO_SIGNAL()        ucModeControl &= ~_BIT0

#define GET_OSD_READYFORDISPLAY()   (bit)(ucModeControl & _BIT1)
#define SET_OSD_READYFORDISPLAY()   ucModeControl |= _BIT1
#define CLR_OSD_READYFORDISPLAY()   ucModeControl &= ~_BIT1


//--------------------------------------------------
// Macro of Mode Stable Flag
//--------------------------------------------------
#define GET_MODESTABLE()            ((bit)(ucModeControl & _BIT2))
#define SET_MODESTABLE()            (ucModeControl |= _BIT2)
#define CLR_MODESTABLE()            (ucModeControl &= ~_BIT2)


//--------------------------------------------------
// Macro of Frame Sync Status
//--------------------------------------------------
#define GET_FRAMESYNCSTATUS()       ((bit)(ucModeControl & _BIT3))
#define SET_FRAMESYNCSTATUS()       (ucModeControl |= _BIT3)
#define CLR_FRAMESYNCSTATUS()       (ucModeControl &= ~_BIT3)

//--------------------------------------------------
// Macro of Start Display for show note flag  // add by eric 20070718
//--------------------------------------------------
#define GET_FIRST_SHOW_NOTE()       (bit)(ucModeControl & _BIT4)
#define SET_FIRST_SHOW_NOTE()        ucModeControl |= _BIT4
#define CLR_FIRST_SHOW_NOTE()        ucModeControl &= ~_BIT4


#define GET_CLEAR_OSD_EN()          (bit)(ucModeControl & _BIT5)
#define SET_CLEAR_OSD_EN()          ucModeControl |= _BIT5
#define CLR_CLEAR_OSD_EN()          ucModeControl &= ~_BIT5
//--------------------------------------------------
// Macro of Start Display
//--------------------------------------------------
#define GET_READYFORDISPLAY()       ((bit)(ucModeControl & _BIT7))
#define SET_READYFORDISPLAY()       (ucModeControl |= _BIT7)
#define CLR_READYFORDISPLAY()       (ucModeControl &= ~_BIT7)




//----------------------------------------------------------------------------------------------------

