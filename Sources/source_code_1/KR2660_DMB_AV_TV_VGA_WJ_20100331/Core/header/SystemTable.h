//----------------------------------------------------------------------------------------------------
// ID Code      : SystemTable.h No.0002
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#ifdef __SCALER__

//----------------------------------------------------------------------------------------------------
// Initial Tables
//----------------------------------------------------------------------------------------------------
BYTE code tSCALER_POWERUP_DVI[] =
{
	4,  	_NON_AUTOINC,   	_PAGE_SELECT_9F,                	_PAGE2,
	11, 	_AUTOINC,       	_P2_TMDS_OUTPUT_CTRL_A6,    	0x80,0x10,0x03,0x00,0x70,0x70,0xe3,0x24,
    _END
};

//----------------------------------------------------------------------------------------------------
// Reset Tables
//----------------------------------------------------------------------------------------------------
BYTE code tSCALER_RESET_TABLE[] =
{
    4,  _NON_AUTOINC,   _HOST_CTRL_01,                  0x40,

    5,  _AUTOINC,       _WATCH_DOG_CTRL0_0C,            0x00,0x00,                          //CR[0C] ~ CR[0D]
    22, _AUTOINC,       _VGIP_CTRL_10,                  0x00,0x00,0x00,0x00,0x00,0x00,0x08, //CR[10] ~ CR[16]
                                                        0x00,0x00,0x00,0x00,0x00,0x00,0x00, //CR[17] ~ CR[1D]
                                                        0x00,0x10,0x00,0x00,0x00, //CR[1E] ~ CR[22]  //fjyang20070712 for FV set
//    5,  _AUTOINC,       _VDISP_CTRL_28,                 0x00,0x00,                          //CR[28] ~ CR[29]
    6,  _AUTOINC,       _FIFO_ACCESS_PORT_30,           0x00,0x00,0x00,                     //CR[30] ~ CR[32]
    5,  _AUTOINC,       _FS_DELAY_FINE_TUNING_43,       0x00,0x00,                          //CR[43] ~ CR[44]
    6,  _AUTOINC,       _SYNC_SELECT_47,                0x00,0x00,0x00,                     //CR[47] ~ CR[49]
    5,  _AUTOINC,       _STABLE_MEASURE_4F,             0x00,0x00,                          //CR[4F] ~ CR[50]

    4,  _NON_AUTOINC,   _SYNC_PROC_ACCESS_PORT_5C,      _SYNC_G_CLAMP_START_00,
    13, _NON_AUTOINC,   _SYNC_PROC_DATA_PORT_5D,        0x04,0x10,0x04,0x10,0x02,0x01,0x20,0x21,0x04,0x00,

    // 4,  _NON_AUTOINC,   _OVERLAY_CTRL_6C,               0x00,//tommy delete
    4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,               0x00,
    6,  _AUTOINC,       _P0_ADC_RED_CTL_CF,             0x50,0x50,0x50,

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE0,
    // Eric Lee mark
    //----------------------------
   // 4,  _NON_AUTOINC,   _P0_VADC_SWITCH_AF,             0x00,

    //6,  _AUTOINC,       _P0_ADC_SOG0_CTRL_D2,           0x20, 0x11, 0x00, //for SOG0 CTRL, DC Restore/Clamp Enable	//v003
	// 4,  _NON_AUTOINC,   _P0_SOG1_CTRL_AC,               0x20, //for SOG1 CTRL
		
    4,  _NON_AUTOINC,   _P0_ADC_POWER_C6,               0x38,
    4,  _NON_AUTOINC,   _P0_ADC_V_BAIS1_CB,             0x00,	//v003	
    4,  _NON_AUTOINC,   _P0_ADC_CLAMP_CTRL1_D5,         0x00, 

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE1,	//v003
    4,  _NON_AUTOINC,   _P1_MIX_B0,                     0x00,				//v003

	// 4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE2,
	//11, _AUTOINC,       _P2_TMDS_OUTPUT_CTRL_A6,        0x78,0x0f,0x03,0x00,0x31,0x70,0xe3,0x24,

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE6,
	4,  _NON_AUTOINC,   _P6_UZD_CTRL1_E4,        				0x00,		
    4,  _NON_AUTOINC,   _P6_ENABLE_BIST_CTRL_A0,        0x00,//v003
    4,  _NON_AUTOINC,   _P6_PEAKING_ENABLE_C1,          0x00,//v003
    4,  _NON_AUTOINC,   _P6_YUV422_TO_YUV444_D4,        0x00,

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE7,
    5,  _AUTOINC,       _P7_YUV2RGB_CTRL_BF,            0x02,0x00,
    4,  _NON_AUTOINC,   _P7_YUV2RGB_CTRL_BF,            0x00,

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE3,

    _END
};


BYTE code tSCALER_POWERUP_INITIAL[] =
{
    4,  _NON_AUTOINC,   _IRQ_CTRL0_04,                  0x00,
    4,  _NON_AUTOINC,   _HDMI_STATUS0_05,               0x80,
    4,  _NON_AUTOINC,   _MEAS_HS_VS_HI_SEL_58,          0x00,
    4,  _NON_AUTOINC,   _COLOR_CTRL_62,                 0x03,
    4,  _NON_AUTOINC,   _GAMMA_CTRL_67,                 0x00,

    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_CTRL0_00,
    9,  _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x01,0x00,0x00,0x00,0x00,0x00,

    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_RSDS_OUTPUT_CTRL0_C0,
    6,  _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x00,0x00,0x00,

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGEB,//eric 20070530
    4,  _NON_AUTOINC,   _PB_SOYCH0_CFG3_C3,             _SOY_LEVEL,
    
    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE0,
    4,  _NON_AUTOINC,   _P0_ADC_RBG_CTRL_CE,            0x7E,
    4,  _NON_AUTOINC,   _P0_ADC_POWER_C6, 	            0x08,
   // 6,  _AUTOINC,       _P0_ADC_SOG0_CTRL_D2,           0x20, 0x11, 0xff, //for SOG0 CTRL, DC Restore/Clamp Enable
#if(_YPBPR_SYNC_SOURCE == _SOG0)	    
  	6,  _AUTOINC,       _P0_ADC_SOG0_CTRL_D2,           _SOY_LEVEL, 0x01,0x0F, 
#else
   	6,  _AUTOINC,       _P0_ADC_SOG0_CTRL_D2,           _SOY_LEVEL, 0x10,0xF0, 
#endif
//    4,  _NON_AUTOINC,   _P0_POWER_ON_RESET_F3,          0xC0,//0x00,//eric 20070529
    4,  _NON_AUTOINC,   _P0_HS_SCHMITT_TRIGGER_CTRL_F4, 0xe9,

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE1,
    7,  _AUTOINC,       _P1_PLL_DIV_CTRL_A0,            0x04,0x47,0x00,0x18,
    4,  _NON_AUTOINC,   _P1_PLL_PHASE_INTERPOLATION_B5, 0x50,
    4,  _NON_AUTOINC,   _P1_DDS_MIX_1_B8,               0x0c,
    7,  _AUTOINC,       _P1_DPLL_OTHER_C3,              0x16,0x10,0x00,0x04,

    4,  _NON_AUTOINC,   _P1_MULTIPLY_POWER_DOWN_E4,     0x00,
#if(_M2PLL_USE == _ON)
    4,  _NON_AUTOINC,   _P1_MULTIPLY_PLL_CTRL0_E0,      0xe0,
#else
    4,  _NON_AUTOINC,   _P1_MULTIPLY_PLL_CTRL0_E0,      0x82, //0xe2,
#endif  // End of #if(_M2PLL_USE == _ON)

#if(_YPBPR_HW_AUTO_SOY == _ENABLE)
    4,  _NON_AUTOINC,   _P1_LOOP_FILTER_CAPACITOR_EB,      0xDC, 
 #endif   

    4,  _NON_AUTOINC,   _PAGE_SELECT_9F,                _PAGE2,
    7,  _AUTOINC,       _P2_ADAPTIVE_EQUALIZER_B4,      0x02,0x58,0x00,0x00,
    4,  _NON_AUTOINC,   _P2_HDMI_APC_C8,                0x01,//For DVI/HDMI enable
    4,  _NON_AUTOINC,   _P2_HDMI_ADDR_PORT_C9,          _P2_HDMI_AVMCR_30,
#if(_HDMI_SUPPORT == _ON)
    7,  _NON_AUTOINC,   _P2_HDMI_DATA_PORT_CA,          0x68,0x00,0x80,0x00,//For Audio Output Enable and Mute
#elif(_TMDS_SUPPORT == _ON)
    4,  _NON_AUTOINC,   _P2_HDMI_DATA_PORT_CA,          0x08,//Enable Video Output
#endif

#if(_HDMI_SUPPORT == _ON)
    4,  _NON_AUTOINC,   _P2_HDMI_ADDR_PORT_C9,          _P2_HDMI_PVGCR0_45,
    5,  _NON_AUTOINC,   _P2_HDMI_DATA_PORT_CA,          0x09,0x00,//For HDMI Packet
    4,  _NON_AUTOINC,   _P2_HDMI_ADDR_PORT_C9,          _P2_HDMI_ACRCR_51,
    4,  _NON_AUTOINC,   _P2_HDMI_DATA_PORT_CA,          0x44,//For HDMI Color space auto switch between 4:2:2/4:4:4
    4,  _NON_AUTOINC,   _P2_HDMI_ADDR_PORT_C9,          _P2_HDMI_DPCR0_38,
    4,  _NON_AUTOINC,   _P2_HDMI_DATA_PORT_CA,          0x00,//Power On Audio PLL
    4,  _NON_AUTOINC,   _P2_HDMI_ADDR_PORT_C9,          _P2_HDMI_AFCR_03,
    4,  _NON_AUTOINC,   _P2_HDMI_DATA_PORT_CA,          0x06,//Enable Audio FIFO
    4,  _NON_AUTOINC,   _P2_HDMI_ADDR_PORT_C9,          _P2_HDMI_AOCR_62,
    4,  _NON_AUTOINC,   _P2_HDMI_DATA_PORT_CA,          0x00,//Disable SPDIF/I2S Output
#endif
    6,  _AUTOINC,       _P2_CDR_CTRL0_B0,               0x02,0x0a,0x0a,
    4,  _NON_AUTOINC,   _P2_HDCP_PORT_CTRL_C2,          0x01,
    4,  _NON_AUTOINC,   _DISP_ACCESS_PORT_2A,           _DISP_NEW_DV_DLY_23,
    4,  _NON_AUTOINC,   _DISP_DATA_PORT_2B,             0x40,
    4,  _NON_AUTOINC,   _DISP_ACCESS_PORT_2A,           _DISP_NEW_DV_CTRL_22,
    4,  _NON_AUTOINC,   _DISP_DATA_PORT_2B,             0xa0,
    4,  _NON_AUTOINC,   _DDC_ENABLE_FA,                 0x04,
    4,  _NON_AUTOINC,   _DDC_DVI_ENABLE_FD,             0x04,

    _END
};

//----------------------------------------------------------------------------------------------------
// Display Interface Initial
//----------------------------------------------------------------------------------------------------
#if(_OUTPUT_BUS  == _PANEL_RSDS)
BYTE code tRSDS_INITIAL[] =
{
/* 4,  _NON_AUTOINC,   	_PS_ACCESS_PORT_8D,    		0x02,
    6,  _NON_AUTOINC,   	_PS_DATA_PORT_8E,			0xff,0xee,0x42,

    4,  _NON_AUTOINC,   	_M2PLL_ACCESS_PORT_B3,        	0x03,
    5,  _NON_AUTOINC,   	_M2PLL_DATA_PORT_B4,            	0x17,0x15,

    5,  _AUTOINC,  			_ANALOG_COMMON_CTRL0_C3, 	0x42,0x40,
*///cyc_ask
    5,  	_AUTOINC,       	_TCON_ADDR_PORT_8B,             	_TCON_CTRL0_00,0x82,
    5,  	_AUTOINC,       	_TCON_ADDR_PORT_8B,             	_TCON_CTRL1_01,0x1e,
    5,  	_AUTOINC,       	_TCON_ADDR_PORT_8B,            		_TCON_RSDS_INTERLEAVING_H_C1,0x0a,
    5,  	_AUTOINC,       	_TCON_ADDR_PORT_8B,             	_TCON_RSDS_INTERLEAVING_L_C2,0x7f,

    // YCLK TCON0	 TCON13
    4,  	_NON_AUTOINC,   	_TCON_ADDR_PORT_8B,             	_TCON_TCON13_V_STA_LSB_70,
    10, 	_NON_AUTOINC,   	_TCON_DATA_PORT_8C,             	0x0c,0x40,0x0c,0xf4,0x21,0x94,0x80,

    // FXDIO TCON1	 TCON3
    4,  	_NON_AUTOINC,   	_TCON_ADDR_PORT_8B,             	_TCON_TCON3_V_STA_LSB_20,
    10, 	_NON_AUTOINC,   	_TCON_DATA_PORT_8C,             	0x0c,0x40,0x0c,0xab,0x22,0xaf,0x80,

    // YOE TCON3 	 TCON12
    4,  	_NON_AUTOINC,   	_TCON_ADDR_PORT_8B,             	_TCON_TCON12_V_STA_LSB_68,
    10, 	_NON_AUTOINC,   	_TCON_DATA_PORT_8C,             	0x0c,0x40,0x0c,0x94,0x52,0x14,0x80,

    // POL TCON7	 TCON6 test
    // 4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_TCON6_V_STA_LSB_38,
    //10, _NON_AUTOINC,   	_TCON_DATA_PORT_8C,             0x0c,0x40,0x0d,0x00,0x00,0x01,0x88,

    // POL TCON7	 TCON7
    4,  	_NON_AUTOINC,   	_TCON_ADDR_PORT_8B,             	_TCON_TCON7_V_STA_LSB_40,
    10, 	_NON_AUTOINC,   	_TCON_DATA_PORT_8C,             	0x0c,0x40,0x0d,0x00,0x00,0x01,0x88,

    // BXDIO TCON11	 TCON9
    4,  	_NON_AUTOINC,   	_TCON_ADDR_PORT_8B,             	_TCON_TCON9_V_STA_LSB_50,
    10, 	_NON_AUTOINC,   	_TCON_DATA_PORT_8C,             	0x0c,0x40,0x0c,0xab,0x22,0xaf,0x80,

    // YDIO TCON12	 TCON1
    4,  	_NON_AUTOINC,   	_TCON_ADDR_PORT_8B,             	_TCON_TCON1_V_STA_LSB_10,
    10, 	_NON_AUTOINC,   	_TCON_DATA_PORT_8C,             	0x0c,0x00,0x0e,0xd0,0x33,0xd7,0x88,

    // XSTB TCON13	 TCON2
    4,  	_NON_AUTOINC,   	_TCON_ADDR_PORT_8B,             	_TCON_TCON2_V_STA_LSB_18,
    10, 	_NON_AUTOINC,   	_TCON_DATA_PORT_8C,             	0x0c,0x40,0x0c,0x35,0x22,0xac,0x80,

    _END
};
#endif //#if(_OUTPUT_BUS  == _PANEL_RSDS)


//----------------------------------------------------------------------------------------------------
// OSD Power Up Initial
//----------------------------------------------------------------------------------------------------
BYTE code tOSD_POWERUP_INITIAL[] =
{
    6,  _AUTOINC,       	_OSD_ADDR_MSB_90,               		0x40,0x02,0x10,
    6,  _AUTOINC,       	_OSD_ADDR_MSB_90,               		0x00,0x03,0x70,

    4,  _NON_AUTOINC,  		_DISP_OSD_REFERENCE_DEN_21,      		0x02,

    _END
};


//----------------------------------------------------------------------------------------------------
// Dithering Table
//----------------------------------------------------------------------------------------------------
BYTE code tDITHER_SEQ_TABLE_0[] =
{
    0xe4,0xa2,0x05,0x37,0xf6,0x31,0x69,0xcb,0x1f,0xd2,0xb0,0xe6,
    0x45,0x1b,0x87,0xc6,0x9e,0xb4,0xc6,0x38,0xd4,0xdb,0x12,0x1b,
};

#if(_DISP_BIT == _DISP_24_BIT)
BYTE code tDITHER_TABLE_10_TO_8[] =
{
    // 10 --> 8
    0x01,0x32,0x12,0x03,0x23,0x10,0x30,0x21,
    0x23,0x10,0x30,0x21,0x01,0x32,0x12,0x03,
    0x30,0x21,0x01,0x32,0x12,0x03,0x23,0x10,
};
#else
BYTE code tDITHER_TABLE_10_TO_6[] =
{
    // 10 --> 6
    0x07,0xf8,0x69,0x1e,0xad,0x52,0xc3,0xb4,
    0xad,0x52,0xc3,0xb4,0x07,0xf8,0x69,0x1e,
    0xad,0x52,0x69,0x1e,0xc3,0xb4,0x07,0xf8,
};
#endif // end #if(_DISP_BIT == _DISP_24_BIT)

BYTE code tDCLK_OFFSET[16] =
{
    0,   0,  0,  0,
    0,   0,  0,  0,
    0,   0,  0,  0,
    0,   0,  0,  0,
};


//----------------------------------------------------------------------------------------------------
// HDCP Key Table
//----------------------------------------------------------------------------------------------------
#if(_HDCP_SUPPORT == _ON)

BYTE code tHDCP_KEY_TABLE_0[] =
{
    0x3a, 0x21, 0x17, 0x06, 0x72, 0x60, 0x3b, 0x6e,     // Key0
    0x0c, 0x58, 0x16, 0x4c, 0x5b, 0x3b, 0x68, 0x4b,     // Key1
    0x2f, 0x7b, 0x5d, 0x64, 0x10, 0x60, 0x71, 0x41,     // Key2
    0x6d, 0x4a, 0x1f, 0x48, 0x35, 0x78, 0x4b, 0x6a,     // Key3
    0x4b, 0x3c, 0x69, 0x2a, 0x20, 0x38, 0x55, 0x1c,     // Key4
    0x10, 0x16, 0x09, 0x5d, 0x0d, 0x07, 0x6e, 0x7a,     // Key5
    0x75, 0x1a, 0x35, 0x55, 0x7b, 0x5c, 0x26, 0x0d,     // Key6
    0x2c, 0x49, 0x1a, 0x1b, 0x3e, 0x55, 0x1f, 0x40,     // Key7
    0x11, 0x24, 0x4b, 0x4a, 0x5d, 0x56, 0x4b, 0x5c,     // Key8
    0x62, 0x70, 0x0b, 0x10, 0x52, 0x3f, 0x2b, 0x4d,     // Key9
    0x5d, 0x06, 0x78, 0x16, 0x72, 0x70, 0x2e, 0x06,     // Key10
    0x3a, 0x2c, 0x60, 0x06, 0x12, 0x6c, 0x32, 0x55,     // Key11
    0x54, 0x62, 0x38, 0x05, 0x13, 0x42, 0x49, 0x40,     // Key12
    0x61, 0x54, 0x28, 0x0c, 0x4a, 0x21, 0x7c, 0x32,     // Key13
    0x4b, 0x74, 0x04, 0x5d, 0x10, 0x69, 0x72, 0x62,     // Key14
    0x5d, 0x77, 0x55, 0x0d, 0x19, 0x79, 0x59, 0x43,     // Key15
    0x0a, 0x5f, 0x0d, 0x50, 0x58, 0x4f, 0x48, 0x42,     // Key16
    0x14, 0x64, 0x65, 0x54, 0x2f, 0x7a, 0x75, 0x04,     // Key17
    0x48, 0x35, 0x00, 0x59, 0x16, 0x0e, 0x2f, 0x4b,     // Key18
    0x4a, 0x7b, 0x04, 0x6c, 0x1a, 0x6d, 0x4b, 0x44,     // Key19
    0x50, 0x11, 0x63, 0x63, 0x47, 0x6e, 0x1a, 0x6b,     // Key20
    0x0f, 0x4c, 0x3e, 0x17, 0x66, 0x0d, 0x3b, 0x3a,     // Key21
    0x47, 0x62, 0x5a, 0x25, 0x3d, 0x0e, 0x1d, 0x55,     // Key22
    0x42, 0x0f, 0x43, 0x60, 0x3e, 0x7e, 0x56, 0x3c,     // Key23
    0x44, 0x4a, 0x44, 0x3b, 0x69, 0x17, 0x1b, 0x47,     // Key24
    0x19, 0x77, 0x2c, 0x7d, 0x72, 0x03, 0x66, 0x53,     // Key25
    0x7f, 0x5a, 0x03, 0x26, 0x17, 0x01, 0x28, 0x5e,     // Key26
    0x09, 0x1d, 0x43, 0x13, 0x35, 0x26, 0x4c, 0x15,     // Key27
    0x1e, 0x7f, 0x4d, 0x6b, 0x4d, 0x52, 0x46, 0x00,     // Key28
    0x3c, 0x38, 0x5c, 0x64, 0x6f, 0x72, 0x78, 0x11,     // Key29
    0x30, 0x65, 0x47, 0x70, 0x7a, 0x3c, 0x38, 0x69,     // Key30
    0x78, 0x26, 0x35, 0x09, 0x37, 0x14, 0x34, 0x57,     // Key31
    0x73, 0x4d, 0x28, 0x28, 0x7e, 0x5a, 0x28, 0x09,     // Key32
    0x08, 0x28, 0x6c, 0x69, 0x42, 0x43, 0x31, 0x15,     // Key33
    0x54, 0x23, 0x60, 0x1c, 0x03, 0x48, 0x7d, 0x48,     // Key34
    0x25, 0x5f, 0x2b, 0x04, 0x6c, 0x42, 0x22, 0x66,     // Key35
    0x11, 0x2a, 0x1a, 0x14, 0x29, 0x68, 0x59, 0x73,     // Key36
    0x76, 0x61, 0x16, 0x00, 0x3e, 0x11, 0x31, 0x20,     // Key37
    0x10, 0x59, 0x13, 0x44, 0x54, 0x32, 0x4f, 0x0e,     // Key38
    0x76, 0x47, 0x13, 0x6f, 0x7e, 0x24, 0x5a, 0x6a,     // Key39

};

#endif  // End of #if(_HDCP_SUPPORT == _ON)

#if((_DE_INTERLACE_SUPPORT == _ON) && (_TMDS_SUPPORT == _ON))	//v003_interlace_check
BYTE code tTMDS_RGB_TO_YUV[] = 
{
    4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,               0x18,
    21, _NON_AUTOINC,   _YUV_RGB_COEF_DATA_9D,          0x01,0x32,0x02,0x59,0x00,0x75,
                                                        0xFF,0x53,0xFE,0xAD,0x02,0x00,
                                                        0x02,0x00,0xFE,0x53,0xFF,0xAD,
    4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,               0x00,//0x17,

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
#endif  // End of #if((_DE_INTERLACE_SUPPORT == _ON) && (_TMDS_SUPPORT == _ON))

#else

extern BYTE code tSCALER_RESET_TABLE[];


extern BYTE code tSCALER_POWERUP_INITIAL[];
extern BYTE code tSCALER_POWERUP_DVI[] ;
extern BYTE code tRSDS_INITIAL[];


extern BYTE code tOSD_POWERUP_INITIAL[];

extern BYTE code tDITHER_SEQ_TABLE_0[];
extern BYTE code tDITHER_TABLE_10_TO_8[];
extern BYTE code tDITHER_TABLE_10_TO_6[];

extern BYTE code tHDCP_KEY_TABLE_0[];
extern BYTE code tHDCP_CTRL[];
extern BYTE code tDCLK_OFFSET[16];

extern BYTE code tDDC_TABLE[];
extern BYTE code tTMDS_RGB_TO_YUV[];
#endif
