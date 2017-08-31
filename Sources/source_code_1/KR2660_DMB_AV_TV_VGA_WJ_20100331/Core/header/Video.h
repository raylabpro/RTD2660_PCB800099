//----------------------------------------------------------------------------------------------------
// ID Code      : Video.h No.0001
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#if(_VIDEO_SUPPORT == _ON)

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of
//--------------------------------------------------
#define _VIDEO_DEVICE			0x40    // 2610 device address
#define _VIDEO_50HZ         	0
#define _VIDEO_60HZ         	1
#define _VIDEO_NOT_EXIST    	_MODE_NOSIGNAL
#define _VIDEO_EXIST        	_MODE_EXIST
#define _HSLCK					_BIT1
#define _VLINF					_BIT2
#define _VDNOSIGNAL				_BIT0

#define _VDC_2D_MODE		    0
#define _VDC_3D_MODE		    1

#if(_VIDEO_TV_SUPPORT)
#define _TV_SIGNAL_FAIL         70
#define _TV_NO_SIGNAL           0
#define _TV_IS_SIGNAL           1

#define _THRESHOLD_POINT        0x17
#endif

#define _VIDEO_SEARCH_COUNT     100

//=======================================
/*
#define ZPAL_I          		0x70
#define ZPAL_M          		0x71
#define ZPAL_N          		0x72
#define ZPAL_60         		0x73
#define ZNTSC          			0x74
#define ZNTSC_443   			0x75
#define ZNTSC_50				0x76
#define ZSECAM          		0x77
  */
#define ZNTSC          			0x01
#define ZNTSC_443   			0x02
#define ZPAL_M          		0x03
#define ZPAL_60         		0x04
#define ZPAL_N          		0x05
#define ZPAL_I          		0x06
#define ZNTSC_50				0x07
#define ZSECAM          		0x08

#define fcmore      			0x04
#define fcless      			0x02
#define fcsame      			0x01

#define noisy					0x01
#define very_noisy				0x02
#define ultra_noisy				0x03

#define	SET_TEXT_POS			0x4808// for vbi

#define SET_2404_DELAY			8
//============================
//----------------------------------------------------------------------------------------------------

#ifdef __VIDEO__

//--------------------------------------------------
// Video Tables
//--------------------------------------------------



//=================================================

unsigned char code RTD2610_NTSC_M_ini[]=
{
	//need modify by 263x parameters
	4,  _NON_AUTOINC,   _PAGE_SELECT_9F,  		    _PAGE8,         
	4,  _NON_AUTOINC,   _P8_YCSEP_CTRL_E0,	      0x02, // 0x00,     // YC Seperate Control     //Samwen 20080801
	4,  _NON_AUTOINC,   _P8_BPF_BW_SEL_Y_E1,	    0x25,     // BPF BandWidth Select Y
	// andy av color
	4,  _NON_AUTOINC,   _P8_BPF_BW_SEL_C_E2,	    0x66,//0x00,     // BPF BandWidth Select C
	// andy av color
	4,  _NON_AUTOINC,   _P8_YC_BW_CTRL_EA,	        0x07,//0x00,//0x01,     // YC BandWidth Control
	4,  _NON_AUTOINC,   _P8_2D_ALPHA_MOD_ENABLE_F2,	0xC2,     // 2D ALPHA Mode Enable 
	4,  _NON_AUTOINC,   _P8_H2V_CORING_THR_F3,	    0x21,     // H2V Coring Threshold
	4,  _NON_AUTOINC,   _P8_H2V_Y_NOISE_THR_F4,	    0x01,     // H2V Y Noise Threshold	//eric 20070608
	4,  _NON_AUTOINC,   _P8_H2V_CVBS_NOISE_THR_F5,	0x15,     // H2V CVBS Noise Threshold
	4,  _NON_AUTOINC,   _P8_1D_BLEND_THR_F6,	    0x03,     // 1D Blend Threshold 
	//
//	4,  _NON_AUTOINC,   _P8_ZORAN_REG_EN_D7,	0x20,			//color mode reg enable	
	4,  _NON_AUTOINC,   _P8_VIDEO_CTRL0_A0,	        0x00,					//NTSC

	4,  _NON_AUTOINC,   _PAGE_SELECT_9F,  		    _PAGEA,         
	4,  _NON_AUTOINC,   _PA_SECAM_CTRL_C4,	        0x82,     // SECAM Control
	_END

};

unsigned char code RTD2610_NTSC_443_ini[]=
{

	//need modify by 263x parameters
	4,  _NON_AUTOINC,   _PAGE_SELECT_9F,  		    _PAGE8,         
	4,  _NON_AUTOINC,   _P8_YCSEP_CTRL_E0,	        0x02,     // YC Seperate Control
	4,  _NON_AUTOINC,   _P8_BPF_BW_SEL_Y_E1,	    0x25,     // BPF BandWidth Select Y
	// andy av color
	4,  _NON_AUTOINC,   _P8_BPF_BW_SEL_C_E2,	    0x66,//0x00,     // BPF BandWidth Select C
	// andy av color
	4,  _NON_AUTOINC,   _P8_YC_BW_CTRL_EA,	        0x07,//0x00,//0x49,     // YC BandWidth Control
	4,  _NON_AUTOINC,   _P8_2D_ALPHA_MOD_ENABLE_F2,	0xC2,     // 2D ALPHA Mode Enable 
	4,  _NON_AUTOINC,   _P8_H2V_CORING_THR_F3,	    0x21,     // H2V Coring Threshold
	4,  _NON_AUTOINC,   _P8_H2V_Y_NOISE_THR_F4,	    0x01,     // H2V Y Noise Threshold //eric 20070608
	4,  _NON_AUTOINC,   _P8_H2V_CVBS_NOISE_THR_F5,	0x15,     // H2V CVBS Noise Threshold
	4,  _NON_AUTOINC,   _P8_1D_BLEND_THR_F6,	    0x03,     // 1D Blend Threshold 
	//
	4,  _NON_AUTOINC,   _P8_ZORAN_REG_EN_D7,    	0x20,     //color mode reg enable	
	4,  _NON_AUTOINC,   _P8_VIDEO_CTRL0_A0,	        0x0A,     //NTSC443(1127 & 135 mode)

	4,  _NON_AUTOINC,   _PAGE_SELECT_9F,  		    _PAGEA,         
	4,  _NON_AUTOINC,   _PA_SECAM_CTRL_C4,	        0x82,     // SECAM Control
	_END
};

unsigned char code RTD2610_PAL_I_ini[]=
{

	//need modify by 263x parameters
	4,  _NON_AUTOINC,   _PAGE_SELECT_9F,  		    _PAGE8,         
	4,  _NON_AUTOINC,   _P8_YCSEP_CTRL_E0,   	    0x02,     // YC Seperate Control
	4,  _NON_AUTOINC,   _P8_BPF_BW_SEL_Y_E1,	    0x25,     // BPF BandWidth Select Y
    // andy av color
	4,  _NON_AUTOINC,   _P8_BPF_BW_SEL_C_E2,	    0x66,//0x00,     // BPF BandWidth Select C
    // andy av color
	4,  _NON_AUTOINC,   _P8_YC_BW_CTRL_EA,	        0x07,//0x00,//0x49,     // YC BandWidth Control
	4,  _NON_AUTOINC,   _P8_2D_ALPHA_MOD_ENABLE_F2,	0xC2,     // 2D ALPHA Mode Enable 
	4,  _NON_AUTOINC,   _P8_H2V_CORING_THR_F3,	    0x21,     // H2V Coring Threshold
	4,  _NON_AUTOINC,   _P8_H2V_Y_NOISE_THR_F4,	    0x06,     // H2V Y Noise Threshold 	//eric 20070608 
	4,  _NON_AUTOINC,   _P8_H2V_CVBS_NOISE_THR_F5,	0x15,     // H2V CVBS Noise Threshold	//eric 20070608
	4,  _NON_AUTOINC,   _P8_1D_BLEND_THR_F6,	    0x03,     // 1D Blend Threshold 
	//
//	4,  _NON_AUTOINC,   _P8_ZORAN_REG_EN_D7,	0x20,		  //color mode reg enable	
	4,  _NON_AUTOINC,   _P8_VIDEO_CTRL0_A0,	        0x02,     //PAL(I,B,G,H,D,N)
	4,  _NON_AUTOINC,   _P8_YCSEP_CTRL_E0,	         0x02, // 0x00,     // YC Seperate Control     //Samwen 20080801

	4,  _NON_AUTOINC,   _PAGE_SELECT_9F,  		    _PAGEA,         
	4,  _NON_AUTOINC,   _PA_SECAM_CTRL_C4,	        0x82,     // SECAM Control
	_END

};

unsigned char code RTD2610_PAL_M_ini[]=
{
	//need modify by 263x parameters
	4,  _NON_AUTOINC,   _PAGE_SELECT_9F,  		    _PAGE8,         
	4,  _NON_AUTOINC,   _P8_YCSEP_CTRL_E0,	        0x02,     // YC Seperate Control
	4,  _NON_AUTOINC,   _P8_BPF_BW_SEL_Y_E1,	    0x25,     // BPF BandWidth Select Y
	// andy av color
	4,  _NON_AUTOINC,   _P8_BPF_BW_SEL_C_E2,	    0x66,//0x00,     // BPF BandWidth Select C
	// andy av color
	4,  _NON_AUTOINC,   _P8_YC_BW_CTRL_EA,	        0x07,//0x00,//0x49,     // YC BandWidth Control
	4,  _NON_AUTOINC,   _P8_2D_ALPHA_MOD_ENABLE_F2,	0xC2,     // 2D ALPHA Mode Enable 
	4,  _NON_AUTOINC,   _P8_H2V_CORING_THR_F3,	    0x21,     // H2V Coring Threshold
	4,  _NON_AUTOINC,   _P8_H2V_Y_NOISE_THR_F4,	    0x03,     // H2V Y Noise Threshold
	4,  _NON_AUTOINC,   _P8_H2V_CVBS_NOISE_THR_F5,	0x15,     // H2V CVBS Noise Threshold
	4,  _NON_AUTOINC,   _P8_1D_BLEND_THR_F6,	    0x03,     // 1D Blend Threshold 
	//
//	4,  _NON_AUTOINC,   _P8_ZORAN_REG_EN_D7,	0x20,		  //color mode reg enable	
	4,  _NON_AUTOINC,   _P8_VIDEO_CTRL0_A0,	        0x04,     //PAL(M)
	4,  _NON_AUTOINC,   _P8_YCSEP_CTRL_E0,	        0x02,     //5-tap adaptive comb filter

	4,  _NON_AUTOINC,   _PAGE_SELECT_9F,  		    _PAGEA,         
	4,  _NON_AUTOINC,   _PA_SECAM_CTRL_C4,	        0x82,     // SECAM Control
	_END

};

unsigned char code RTD2610_PAL_CN_ini[]=
{
	//need modify by 263x parameters
	4,  _NON_AUTOINC,   _PAGE_SELECT_9F,  		    _PAGE8,         
	4,  _NON_AUTOINC,   _P8_YCSEP_CTRL_E0,	        0x02,     // YC Seperate Control
	4,  _NON_AUTOINC,   _P8_BPF_BW_SEL_Y_E1,	    0x25,     // BPF BandWidth Select Y
	// andy av color
	4,  _NON_AUTOINC,   _P8_BPF_BW_SEL_C_E2,	    0x66,//0x00,     // BPF BandWidth Select C
	// andy av color
	4,  _NON_AUTOINC,   _P8_YC_BW_CTRL_EA,	        0x07,//0x00,//0x49,     // YC BandWidth Control
	4,  _NON_AUTOINC,   _P8_2D_ALPHA_MOD_ENABLE_F2,	0xC2,     // 2D ALPHA Mode Enable 
	4,  _NON_AUTOINC,   _P8_H2V_CORING_THR_F3,	    0x21,     // H2V Coring Threshold
	4,  _NON_AUTOINC,   _P8_H2V_Y_NOISE_THR_F4,	    0x03,     // H2V Y Noise Threshold
	4,  _NON_AUTOINC,   _P8_H2V_CVBS_NOISE_THR_F5,	0x15,     // H2V CVBS Noise Threshold
	4,  _NON_AUTOINC,   _P8_1D_BLEND_THR_F6,	    0x03,     // 1D Blend Threshold 
	//
//	4,  _NON_AUTOINC,   _P8_ZORAN_REG_EN_D7,	0x20,		  //color mode reg enable	
	4,  _NON_AUTOINC,   _P8_VIDEO_CTRL0_A0,	        0x06,     //PAL(CN)
	4,  _NON_AUTOINC,   _P8_YCSEP_CTRL_E0,	        0x02,     //5-tap adaptive comb filter

	4,  _NON_AUTOINC,   _PAGE_SELECT_9F,  		    _PAGEA,         
	4,  _NON_AUTOINC,   _PA_SECAM_CTRL_C4,	        0x82,     // SECAM Control
	_END

};

unsigned char code RTD2610_SECAM_ini[]=
{
	//need modify by 263x parameters
	4,  _NON_AUTOINC,   _PAGE_SELECT_9F,  		    _PAGE8,         
	4,  _NON_AUTOINC,   _P8_YC_BW_CTRL_EA,	        0x07,//0x00,     // YC BandWidth Control
	4,  _NON_AUTOINC,   _PAGE_SELECT_9F,  		    _PAGEA,         
	4,  _NON_AUTOINC,   _PA_SECAM_CTRL_C4,	        0xC2,     // SECAM Control
	4,  _NON_AUTOINC,   _PA_DRDB_GAIN_TB_CA,	    0x00,     // Secam Gain DrDb Look Up Table 
	4,  _NON_AUTOINC,   _PA_Y_GAIN_TB_CB,	        0x00,     // Secam Gain Y Look Up Table 		
	//
	4,  _NON_AUTOINC,   _PAGE_SELECT_9F,  		    _PAGE8,         
//	4,  _NON_AUTOINC,   _P8_ZORAN_REG_EN_D7,  0x20,           // color mode reg enable	
	4,  _NON_AUTOINC,   _P8_VIDEO_CTRL0_A0,  	    0x08,     // SECAM
	4,  _NON_AUTOINC,   _P8_YCSEP_CTRL_E0,  	    0x02, // 0x00,     // YC Seperate Control     //Samwen 20080801         
	_END
};

unsigned char code RTD2610_PAL_60_ini[]=
{
	//need modify by 263x parameters
	4,  _NON_AUTOINC,   _PAGE_SELECT_9F,  		    _PAGE8,         
	4,  _NON_AUTOINC,   _P8_YCSEP_CTRL_E0,	        0x02,     // YC Seperate Control
	4,  _NON_AUTOINC,   _P8_BPF_BW_SEL_Y_E1,	    0x25,     // BPF BandWidth Select Y
	// andy av color
	4,  _NON_AUTOINC,   _P8_BPF_BW_SEL_C_E2,	    0x66,//0x00,     // BPF BandWidth Select C
	// andy av color
	4,  _NON_AUTOINC,   _P8_YC_BW_CTRL_EA,	        0x07,//0x00,//0x49,     // YC BandWidth Control
	4,  _NON_AUTOINC,   _P8_2D_ALPHA_MOD_ENABLE_F2,	0xC2,     // 2D ALPHA Mode Enable 
	4,  _NON_AUTOINC,   _P8_H2V_CORING_THR_F3,	    0x21,     // H2V Coring Threshold
	4,  _NON_AUTOINC,   _P8_H2V_Y_NOISE_THR_F4,	    0x00,     // H2V Y Noise Threshold
	4,  _NON_AUTOINC,   _P8_H2V_CVBS_NOISE_THR_F5,	0x15,     // H2V CVBS Noise Threshold //eric 20070608
	4,  _NON_AUTOINC,   _P8_1D_BLEND_THR_F6,	    0x03,     // 1D Blend Threshold
	//
	4,  _NON_AUTOINC,   _P8_ZORAN_REG_EN_D7,	    0x20,     // color mode reg enable	
	4,  _NON_AUTOINC,   _P8_VIDEO_CTRL0_A0,     	0x0E,     // color mode reg enable	
	4,  _NON_AUTOINC,   _P8_YCSEP_CTRL_E0,	        0x02,     // 5-tap adaptive comb filter

	4,  _NON_AUTOINC,   _PAGE_SELECT_9F,  		    _PAGEA,         
	4,  _NON_AUTOINC,   _PA_SECAM_CTRL_C4,	        0x82,     // SECAM Control
	_END
};


unsigned char code VideoInit[]=
{
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE9,
    4,  _NON_AUTOINC,   _P9_C_LOCK_CONF_B6,             0x6B,
    5,  _AUTOINC,			_P9_AGC_GATE_STA_M_A5,      0x06,0x82,
    4,  _NON_AUTOINC,   _P9_CLAMP_CTRL0_C2,             0xE0,
    4,  _NON_AUTOINC,   _P9_CLAMP_NEWBP_STA_C5,         0x80,
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGEA,
    4,  _NON_AUTOINC,   _PA_FIFO_CTRL_BB,               0x84,
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE9,
    4,  _NON_AUTOINC,   _P9_CLOOP_GAIN_B7,               0x83,  //eric 20070607
	4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE8,
	4,  _NON_AUTOINC,   _P8_ZORAN_REG_EN_D7,	        0x00,	//color mode reg enable //fjyang20070710
	_END
};

unsigned char code VideoAdcInit[]=
{
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE0,
    4,  _NON_AUTOINC,   _P0_VADC_SOY_COMPAR_A0,         0x00,
    4,  _NON_AUTOINC,   _P0_VADC_CTRL_A1,               0x0F,
    4,  _NON_AUTOINC,   _P0_VADC_CLOCK_A2,              0x00,
    4,  _NON_AUTOINC,   _P0_VADC_OUTPUT_DELAY_A3,       0x00,
    4,  _NON_AUTOINC,   _P0_VADC_INPUT_BW_A5,           0x06,
    4,  _NON_AUTOINC,   _P0_VADC1_INPUT_PGA_A6,         0x84,//0x9C,//eric 20070702 Video over bright
    4,  _NON_AUTOINC,   _P0_VADC0_INPUT_PGA_A7,         0x84,//0x9C,
    4,  _NON_AUTOINC,   _P0_VADC_CLAMP_A8,              0x10,
    4,  _NON_AUTOINC,   _P0_VADC_INRANGE_A9,            0xC1,
    4,  _NON_AUTOINC,   _P0_VADC1_SOY_BIAS_CUR_AB,      0x18,
    4,  _NON_AUTOINC,   _P0_VADC_IN_CH_BIAS_CUR_AC,     0x88,
    4,  _NON_AUTOINC,   _P0_VADC_POS_IN_SOY_RES_AD,     0x00,
    4,  _NON_AUTOINC,   _P0_VADC_CLAMP_POWER_AE,        0x00,
 //   4,  _NON_AUTOINC,   _P0_VADC_SWITCH_AF,             0x01,
    _END
};


//==========================================================================================


BYTE code tVIDEO_TABLE_SET_SCALER[] =
{
    7,  _AUTOINC,       _VGIP_CTRL_10,                  0x0d,0x01,0x00,0x03,
    4,  _NON_AUTOINC,   _IPH_ACT_WID_H_16,              0x08,
    4,  _NON_AUTOINC,   _IPV_ACT_STA_H_18,              0x10,
    4,  _NON_AUTOINC,   _SCALE_CTRL_32,                 0x00,
    4,  _NON_AUTOINC,   _SYNC_CTRL_49,                  0x05,
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE1,         
	4,  _NON_AUTOINC,   _P1_LOOP_FILTER_CAPACITOR_EB,   0xDC,
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE6,
    4,  _NON_AUTOINC,   _P6_PEAKING_DATA00_C2,          0x02,		//v004
    4,  _NON_AUTOINC,   _P6_YUV422_TO_YUV444_D4,        0xE0,//v003
    //4,  _NON_AUTOINC,   _P6_DCTI_1ST_GAIN_D8,           0x8A,		//v004
    4,  _NON_AUTOINC,   _P6_DCTI_1ST_GAIN_D8,           0x02,		//v004
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE7,

    // andy av color
    8,  _AUTOINC,       _P7_DLTI_DCTI_ENABLE_A1,        0x80,0x6A,0x04,0x01,0x74,//0xC0,//eric 20070608
    4,  _NON_AUTOINC,   _P7_DCTI_1ST_GAIN_A6,           0x0A,	//v003
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

	4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE9,		//v003
    4,  _NON_AUTOINC,   _P9_CLAMP_CTRL0_C2,             0xE0,		//v003
    4,  _NON_AUTOINC,   _P9_CLAMP_NEWBP_STA_C5,         0x80,	//v003

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE3,
	_END
};


//--------------------------------------------------
// Global Variables
//--------------------------------------------------
unsigned char idata ucMode_Pre_2610  = 0x00;
unsigned char idata ucMode_Curr_2610 = 0x00; //initial ntscm mode
unsigned char idata ucAV_Mode_Curr;
unsigned char idata ucAV_Mode_Pre    = 60;
BYTE ucVideoType                     = 0;
BYTE ucTVSyncFailCount               = 0;

#if(_VIDEO_TV_SUPPORT)
bit bTVSignal        = 0;
BYTE TVSignalCount   = 0;
BYTE TVNoSignalCount = 0;
#endif

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CVideoInitial(void);
bit CVideoIsExist(void);
UINT8 IdentifyColorStandard(UINT8 status);
void CSetTvColor(BYTE ucColorMode);

void CVideoDisplaySet(void);
void CVideoOutputDisable(void);
void CVideoDetectMode(void);
bit CVideoCheckMode(void);
void CVideoSoftReset(void);
void CVideoSetVDCSaturation(BYTE ucValue);
void CVideoSetVDCContrast(BYTE ucValue);
void CVideoSetVDCBrightness(BYTE ucValue);
void CVideoProcess(void);
void CVideoFixedFHFVBug(void);

#if(_DCC_FUNC==_ENABLE)
void CVideoDCCProcess(void);
#endif

void bTVSigChange(void);

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern unsigned char idata ucMode_Pre_2610;
extern unsigned char idata ucMode_Curr_2610;
extern BYTE ucVideoType;
extern BYTE ucTVSyncFailCount;
extern BYTE ucSearchCount;


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CSetTvColor(BYTE ucColorMode);
extern bit CVideoIsExist(void);
extern void CVideoOutputDisable(void);
extern UINT8 IdentifyColorStandard(UINT8 status);
extern void CVideoDisplaySet(void);
extern void CVideoSoftReset(void);
extern void CVideoProcess(void);
extern void CVideoSetVDCSaturation(BYTE ucValue);
extern void CVideoSetVDCContrast(BYTE ucValue);
extern void CVideoSetVDCBrightness(BYTE ucValue);
extern void CVideoSCART_CVBS(void) ;
extern void CVideoSCART_RGB(void) ;
extern void CVideoSCART_AUTO(void);
extern void CVideoInitial(void);

#if(_DCC_FUNC==_ENABLE)
extern void CVideoDCCProcess(void);
#endif

#endif

#if(_VIDEO_TV_SUPPORT)
extern bit  bTVNoSignal;
extern BYTE ucTVNoise;
extern bit bTVSignal;
extern BYTE TVSignalCount;
extern BYTE TVNoSignalCount;
#endif

#endif  
