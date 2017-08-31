//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerDef.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------
//--------------------------------------------------
// Definitions of RTD2528R Control Register Address
//--------------------------------------------------

//--------------------------------------------------
// Global Event Flag
//--------------------------------------------------
#define _ID_REG_00                          	0x00        // ID Code Register
#define _HOST_CTRL_01                       	0x01        // Host Control Register
#define _STATUS0_02                         	0x02        // Status0 Register
#define _STATUS1_03                         	0x03        // Status1 Register
#define _IRQ_CTRL0_04                       	0x04        // IRQ Control Register0
#define _HDMI_STATUS0_05                    	0x05        // HDMI Status0 Register
#if(_SCALER_TYPE == _RTD3580D)
#define _NEW_ADDED_STATUS0_07        			0x07        // NEW Added Status0 Register
#define _NEW_ADDED_STATUS1_08					0x08        // NEW Added Status1 Register
#endif

//#define _HDMI_STATUS1_06                    		0x06        // HDMI Status1 Register
//Address: 07~0B Reserved
#define _WATCH_DOG_CTRL0_0C              		0x0C        // Watch Dog Control Register0
#define _WATCH_DOG_CTRL1_0D         			0x0D        // Watch Dog Control Register1
//Address: 0E~0F Reserved
#define _VGIP_CTRL_10                       	0x10        // Video Graphic Input Port(VGIP) Control Register
#define _VGIP_SIGINV_11                     	0x11        // Input Control Signal Inverted Register
#define _VGIP_DELAY_CTRL_12                 	0x12        // VGIP Delay Control Register
#define _VGIP_ODD_CTRL_13                   	0x13        // VGIP Odd Control Register

//--------------------------------------------------
// Input Frame Window
//-------------------------------------------------
#define _IPH_ACT_STA_H_14                   	0x14        // Input Horizontal Active Start HByte
#define _IPH_ACT_STA_L_15                   	0x15        // Input Horizontal Active Start LByte
#define _IPH_ACT_WID_H_16                   	0x16        // Input Horizontal Active Width HByte
#define _IPH_ACT_WID_L_17                   	0x17        // Input Horizontal Active Width LByte
#define _IPV_ACT_STA_H_18                   	0x18        // Input Vertical Active Start HByte
#define _IPV_ACT_STA_L_19                   	0x19        // Input Vertical Active Start LByte
#define _IPV_ACT_LEN_H_1A                   	0x1A        // Input Vertical Active Length HByte
#define _IPV_ACT_LEN_L_1B                   	0x1B        // Input Vertical Active Length LByte
#define _IVS_DELAY_1C                       	0x1C        // Internal Input Vertical Sync(VS) Delay Control Register
#define _IHS_DELAY_1D                       	0x1D        // Internal Input Horizontal Sync(HS) Delay Control Register
#define _VGIP_HV_DELAY_1E                   	0x1E        // VGIP HS/VS Delay
#if(_SCALER_TYPE == _RTD3580D)
#define _IPH_PORCH_NUM_H_1F         			0x1F        // Input Video Horizontal Porch HByte
#define _IPH_PORCH_NUM_L_20                		0x20        // Input Video Horizontal Porch LByte
#endif

#if(_SCALER_TYPE == _RTD3580D)
//--------------------------------------------------
// FIFO Frequency
//--------------------------------------------------
#define _FIFO_FREQUENCY_22                  	0x22        // FIFO Frequency

//--------------------------------------------------
// Input Pattern Generator
//--------------------------------------------------
#define _FIFO_BIST_CTRL_23                  	0x23        // FIFO BIST Control Register
#define _INPUT_PAT_GEN_ACCESS_PORT_24  			0x24        // Input Pattern Generator Access Port
#define _INPUT_PAT_GEN_DATA_PORT_25      		0x25        // Input Pattern Generator Data Port
//#define _RESERVED_26                        0x26       // Reserved 26
//#define _RESERVED_27                        0x27        // Reserved 27
#else
//--------------------------------------------------
// FIFO Frequency
//--------------------------------------------------
#define _FIFO_FREQUENCY_22                  	0x22        // FIFO Frequency
#define _SCALE_DOWN_CTRL_23                 	0x23        // Scale Down Control Register

//--------------------------------------------------
// Scale Down Function(Port)
//--------------------------------------------------
#define _SD_ACCESS_PORT_24                  	0x24        // Scale Down Access Port
#define _SD_DATA_PORT_25                    	0x25        // Scale Down Data Port
//Address: 26~27 Reserved
#endif

//--------------------------------------------------
// Display Format(Port)
//--------------------------------------------------
#define _VDISP_CTRL_28                      	0x28        // Video Display Control Register
#define _VDISP_SIGINV_29                    	0x29        // Display Control Signal Inverted Register
#define _DISP_ACCESS_PORT_2A              		0x2A        // Display Format Access Port
#define _DISP_DATA_PORT_2B                  	0x2B        // Display Format Data Port
#if(_SCALER_TYPE == _RTD3580D)
#define _OP_CRC_CTRL_2C                     	0x2C        // Output CRC Control Register 
#define _OP_CRC_CHECKSUM_2D               		0x2D        // Output CRC Checksum
#endif
//Address: 2C~2F Reserved

//--------------------------------------------------
// FIFO Window(Port)
//--------------------------------------------------
#define _FIFO_ACCESS_PORT_30                	0x30        // FIFO Window Address Port
#define _FIFO_DATA_PORT_31                  	0x31        // FIFO Window Data Port

//--------------------------------------------------
// Scale Up Function(Port)
//--------------------------------------------------
#define _SCALE_CTRL_32                      	0x32        // Scale Control Register
#define _SU_ACCESS_PORT_33                  	0x33        // Scale Up Factor Access Port
#define _SU_DATA_PORT_34                    	0x34        // Scale Up Factor Data Port
#define _FILTER_CTRL_35                     	0x35        // Filter Control Register
#define _FILTER_ACCESS_PORT_36              	0x36        // User Defined Filter Access Port
//Address: 37~3F Reserved

//--------------------------------------------------
// Frame Sync Fine Tune
//--------------------------------------------------
#define _IVS2DVS_DELAY_LINES_40             	0x40        // IVS to DVS Delay Lines
#define _IV_DV_DELAY_CLK_ODD_41           		0x41        // Frame Sync Delay Fine Tuning ODD
#define _IV_DV_DELAY_CLK_EVEN_42         		0x42        // Frame Sync Delay Fine Tuning EVEN
#define _FS_DELAY_FINE_TUNING_43        		0x43        // Frame Sync Delay Fine Tuning Control Register
#define _LAST_LINE_H_44                     	0x44        // Last Line HByte
#define _LAST_LINE_L_45                     	0x45        // Last Line LByte
//Address: 46 Reserved

//--------------------------------------------------
// Sync Processor(Port)
//--------------------------------------------------
#define _SYNC_SELECT_47                     	0x47        // Sync Select Control Register
#define _SYNC_INVERT_48                     	0x48        // Sync Invert Control Register
#define _SYNC_CTRL_49                       	0x49        // Sync Processor Control Register
#define _STABLE_HIGH_PERIOD_H_4A         		0x4A        // Stable High Period HByte
#define _STABLE_HIGH_PERIOD_L_4B         		0x4B        // Stable High Period LByte
#define _VSYNC_COUNTER_LEVEL_MSB_4C  			0x4C        // Vertical Sync Counter Level MSB
#define _VSYNC_COUNTER_LEVEL_LSB_4D 			0x4D        // Vertical Sync Counter Level LSB
#define _HSYNC_TYPE_DETECTION_FLAG_4E			0x4E        // Hsync Type Detection Flag
#define _STABLE_MEASURE_4F                  	0x4F        // Stable Measure
#define _STABLE_PERIOD_H_50                 	0x50        // Stable Period HByte
#define _STABLE_PERIOD_L_51                 	0x51        // Stable Period LByte
#define _MEAS_HS_PERIOD_H_52               		0x52        // HSync Period Measured Result HByte
#define _MEAS_HS_PERIOD_L_53                	0x53        // HSync Period Measured Result LByte
#define _MEAS_VS_PERIOD_H_54                	0x54        // VSync Period Measured Result HByte
#define _MEAS_VS_PERIOD_L_55                	0x55        // VSync Period Measured Result LByte
#define _MEAS_HS_VS_HIGH_PERIOD_H_56			0x56        // HSync and VSync High Period Measured Results HByte
#define _MEAS_HS_HIGH_PERIOD_L_57       		0x57        // HSync High Period Measured Results LByte
#if(_SCALER_TYPE == _RTD3580D)
#define _MEAS_HS_VS_HI_SEL_58               	0x58        // HSync and VSync High Period Measured Select
#else
#define _MEAS_VS_HIGH_PERIOD_L_58       		0x58        // VSync High Period Measured Results LByte
#endif
#define _MEAS_ACTIVE_REGION_59              	0x59        // Active Region Measured by Crystal Clock
//#define _SYNC_TEST_MISC_5A                  	0x5A        // Sync Test MISC Register
//Address: 5B Reserved
#define _SYNC_PROC_ACCESS_PORT_5C     			0x5C        // Sync Processor Access Port Address
#define _SYNC_PROC_DATA_PORT_5D          		0x5D        // Sync Processor Access Port Data
//Address: 5E~5F Reserved

//--------------------------------------------------
// Hightlight Window(Port)
//--------------------------------------------------
#define _HW_ACCESS_PORT_60                  	0x60        // Highlight Window Access Port
#define _HW_DATA_PORT_61                    	0x61        // Highlight Window Data Port

//--------------------------------------------------
// Color Processor Control(Port)
//--------------------------------------------------
#define _COLOR_CTRL_62                      	0x62        // Color Processor Control Register
#define _SRGB_ACCESS_PORT_63                	0x63        // sRGB Access Port
#define _CB_ACCESS_PORT_64                  	0x64        // Contrast/Brightness Access Port
#define _CB_DATA_PORT_65                    	0x65        // Contrast/Brightness Data Port

//--------------------------------------------------
// Gamma Control
//--------------------------------------------------
#define _GAMMA_PORT_66                      	0x66        // Gamma Access Port
#define _GAMMA_CTRL_67                      	0x67        // Gamma Control Register
#define _GAMMA_BIST_68                      	0x68        // Gamma BIST Control Register

#if(_SCALER_TYPE == _RTD3580D)
//--------------------------------------------------
// Dithering Control
//--------------------------------------------------
#define _DITHERING_DATA_ACCESS_69          		0x69        // Dithering Table DATA ACCESS
#define _DITHERING_CTRL_6A                 		0x6A        // Dithering Control Register
//#define _RESERVED_6B                        		0x6B        // Reserved 6B
#else
//--------------------------------------------------
// Dithering Control
//--------------------------------------------------
#define _DITHERING_SEQUENCE_TABLE_69        	0x69        // Dithering Sequence Table
#define _DITHERING_TABLE_ACCESS_PORT_6A 		0x6A        // Dithering Table Access Port
#define _DITHERING_CTRL_6B                  	0x6B        // Dithering Control Register
#endif


//--------------------------------------------------
// Overlay/Color Palette/Background Color Control
//--------------------------------------------------
#define _OVERLAY_CTRL_6C                    	0x6C        // Overlay Display Control Register
#define _BGND_COLOR_CTRL_6D                 	0x6D        // Background Color Control Register
#define _OVERLAY_LUT_ADDR_6E                	0x6E        // Overlay Look Up Table (LUT) Address
#define _COLOR_LUT_PORT_6F                  	0x6F        // Color LUT Access Port

//--------------------------------------------------
// Image Auto Function
//--------------------------------------------------
#define _H_BOUNDARY_H_70                    	0x70        // Horizontal Start/End Boundary HByte
#define _H_BOUNDARY_STA_L_71                	0x71        // Horizontal Start Boundary HByte
#define _H_BOUNDARY_END_L_72                	0x72        // Horizontal End Boundary HByte
#define _V_BOUNDARY_H_73                    	0x73        // Vertical Start/End Boundary HByte
#define _V_BOUNDARY_STA_L_74                	0x74        // Vertical Start Boundary LByte
#define _V_BOUNDARY_END_L_75                	0x75        // Vertical End Boundary LByte
#define _RED_NOISE_MARGIN_76                	0x76        // Red Noise Margin Control Register
#define _GRN_NOISE_MARGIN_77                	0x77        // Green Noise Margin Control Register
#define _BLU_NOISE_MARGIN_78                	0x78        // Blue Noise Margin Control Register
#define _DIFF_THRESHOLD_79                  	0x79        // Difference Threshold
#define _AUTO_ADJ_CTRL0_7A                  	0x7A        // Auto Adjusting Control Register 0
#define _HW_AUTO_PHASE_CTRL0_7B          		0x7B        // Hardware Auto Phase Control Register 0
#define _HW_AUTO_PHASE_CTRL1_7C          		0x7C        // Hardware Auto Phase Control Register 1
#define _AUTO_ADJ_CTRL1_7D                  	0x7D        // Auto Adjusting Control Register 1
#define _V_START_END_H_7E                   	0x7E        // Actuve Region Vertical Start/End HByte
#define _V_START_L_7F                       	0x7F        // Actuve Region Vertical Start LByte
#define _V_END_L_80                         	0x80        // Actuve Region Vertical End LByte
#define _H_START_END_H_81                   	0x81        // Actuve Region Horizontal Start/End HByte
#define _H_START_L_82                       	0x82        // Actuve Region Horizontal Start LByte
#define _H_END_L_83                         	0x83        // Actuve Region Horizontal End LByte
#define _AUTO_PHASE_3_84                   		0x84        // Auto Phase Result Register Byte 3
#define _AUTO_PHASE_2_85                    	0x85        // Auto Phase Result Register Byte 2
#define _AUTO_PHASE_1_86                    	0x86        // Auto Phase Result Register Byte 1
#define _AUTO_PHASE_0_87                    	0x87        // Auto Phase Result Register Byte 0
//Address: 88~8A Reserved


//--------------------------------------------------
// Embedded Timing Controller(Port)
//--------------------------------------------------
#define _TCON_ADDR_PORT_8B                  	0x8B        // TCON Address Port for Embedded TCON Access
#define _TCON_DATA_PORT_8C                  	0x8C        // TCON Data Port for Embedded TCON Access
//
#define _LVDS_CTRL0_A0                      	0xA0        //
#define _LVDS_CTRL1_A1                      	0xA1        //
#define _LVDS_CTRL2_A2                      	0xA2        //
#define _LVDS_CTRL3_A3                      	0xA3        //
#define _LVDS_CTRL4_A4                      	0xA4        //
#define _LVDS_CTRL5_A5                      	0xA5        //

//--------------------------------------------------
// Pin Configuration(Port)
//--------------------------------------------------
#define _PS_ACCESS_PORT_8D                  	0x8D        // Pin Share Access Port
#define _PS_DATA_PORT_8E                    	0x8E        // Pin Share Data Port
//Address: 8F Reserved

//--------------------------------------------------
// Embedded OSD
//--------------------------------------------------
#define _OSD_ADDR_MSB_90                    	0x90        // OSD Address MSB
#define _OSD_ADDR_LSB_91                    	0x91        // OSD Address LSB
#define _OSD_DATA_PORT_92                   	0x92        // OSD Data Port
#define _OSD_SCRAMBLE_93                    	0x93        // OSD Scramble
#define _OSD_TEST_94                        	0x94        // OSD Test
//Address: 95~97 Reserved

//--------------------------------------------------
// Digital Filter
//--------------------------------------------------
#define _DIGITAL_FILTER_CTRL_98            		0x98        // Digital Filter Control Register
#define _DIGITAL_FILTER_PORT_99             	0x99        // Digital Filter Port

//--------------------------------------------------
// Peaking Filter and Coring Control(Port)
//--------------------------------------------------
#define _PC_ACCESS_PORT_9A                  	0x9A        // Peaking/Coring Access Port
#define _PC_DATA_PORT_9B                    	0x9B        // Peaking/Coring Data Port

//--------------------------------------------------
// Video Color Space Conversion
//--------------------------------------------------
#define _YUV2RGB_CTRL_9C                    	0x9C        // YUV to RGB Control Register
#define _YUV_RGB_COEF_DATA_9D               	0x9D        // YUV to RGB Coefficient Data Port
//Address:9E~9F Reserved


#if(_SCALER_TYPE == _RTD3580D)
//--------------------------------------------------
// VBI(Port)
//--------------------------------------------------
#define _VBI_ACCESS_PORT_9A                 	0x9A        // VBI Access Port
#define _VBI_DATA_PORT_9B                   	0x9B        // VBI Data Port 
#endif

////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE
//PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE
//PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE

//--------------------------------------------------
// Paged Control Register
//--------------------------------------------------
#if(_SCALER_TYPE == _RTD3580D)
#define _PAGE_SELECT_9F                     	0x9F        // Page Selector (CRA0~CRFF)
#else
#define _PAGE_SELECT_A0                     	0xA0        // Page Selector (CRA1~CRDF)
#endif

#if(_SCALER_TYPE == _RTD3580D)
//--------------------------------------------------
// Video ADC (Page0)
//--------------------------------------------------
#define _P0_VADC_SOY_COMPAR_A0           		0xA0        // VADC SOY Comparator Select
#define _P0_VADC_CTRL_A1                     	0xA1        // VADC Control Register
#define _P0_VADC_CLOCK_A2                    	0xA2        // VADC Clock Source
#define _P0_VADC_OUTPUT_DELAY_A3      			0xA3        // VADC Output Delay 
//#define _P0_RESERVED_A4                     	0xA4        // P0 Reserved A4
#define _P0_VADC_INPUT_BW_A5                 	0xA5        // VADC Input BW 
#define _P0_VADC1_INPUT_PGA_A6             		0xA6        // VADC1 Input PGA 
#define _P0_VADC0_INPUT_PGA_A7             		0xA7        // VADC0 Input PGA 
#define _P0_VADC_CLAMP_A8                    	0xA8        // VADC Clamp
#define _P0_VADC_INRANGE_A9                  	0xA9        // VADC Input Range
//#define _P0_RESERVED_AA                     		0xAA        // P0 Reserved AA
#define _P0_VADC1_SOY_BIAS_CUR_AB      			0xAB        // VADC1 SOY Bias Current
#define _P0_VADC_IN_CH_BIAS_CUR_AC     			0xAC        // VADC Input Channel Bias Current
#define _P0_VADC_POS_IN_SOY_RES_AD  			0xAD        // VADC Posive Input SOY Restore Resistor
#define _P0_VADC_CLAMP_POWER_AE         		0xAE        // VADC Clamp Power
#define _P0_VADC_SWITCH_AF                   	0xAF        // VADC/Video8 Switch 

//--------------------------------------------------
// YPbPr ADC (Page0)
//--------------------------------------------------
#define _P0_RED_GAIN_C0                     	0xC0        // ADC Red Channel Gain Adjust
#define _P0_GRN_GAIN_C1                     	0xC1        // ADC Green Channel Gain Adjust
#define _P0_BLU_GAIN_C2                     	0xC2        // ADC Blue Channel Gain Adjust
#define _P0_RED_OFFSET_C3                 	 	0xC3        // ADC Red Channel Offset Adjust  
#define _P0_GRN_OFFSET_C4                   	0xC4        // ADC Green Channel Offset Adjust
#define _P0_BLU_OFFSET_C5                   	0xC5        // ADC Blue Channel Offset Adjust 
#define _P0_ADC_POWER_C6                   		0xC6        // ADC Power Control Register
#define _P0_ADC_I_BAIS0_C7                  	0xC7        // ADC Bais Current Control Register0
#define _P0_ADC_I_BAIS1_C8                  	0xC8        // ADC Bais Current Control Register1
#define _P0_ADC_I_BAIS2_C9                  	0xC9        // ADC Bais Current Control Register2
#define _P0_ADC_V_BAIS0_CA                  	0xCA        // ADC Bais Voltage Control Register0
#define _P0_ADC_V_BAIS1_CB                  	0xCB        // ADC Bais Voltage Control Register1
#define _P0_ADC_CLOCK_CTRL_CC               	0xCC        // ADC Clock Control Register
#define _P0_ADC_TEST_CTRL_CD                	0xCD        // ADC Test Control Register
#define _P0_ADC_RBG_CTRL_CE                 	0xCE        // ADC RGB Control Register
#define _P0_ADC_RED_CTL_CF                  	0xCF        // ADC Red Channel Control Register
#define _P0_ADC_GREEN_CTL_D0                	0xD0        // ADC Green Channel Control Register
#define _P0_ADC_BLUE_CTL_D1                 	0xD1        // ADC Blue Channel Control Register
#define _P0_ADC_SOG0_CTRL_D2               		0xD2        // ADC SOG0 Reference Control Register
#define _P0_ADC_DCR_CTRL_D3                 	0xD3        // ADC DCR Reference Control Register
#define _P0_ADC_CLAMP_CTRL0_D4             		0xD4        // ADC Clamp Control Register0
#define _P0_ADC_CLAMP_CTRL1_D5             		0xD5        // ADC Clamp Control Register1
#define _P0_ADC_SOG_CTRL_D6                 	0xD6        // ADC SOG Control Register
//#define _P0_TEST_PTN_POS_H_D7              	0xD7        // Test Pattern H/V Position HByte
//#define _P0_TEST_PTN_VPOS_L_D8              	0xD8        // Assign the test pattern digitized position(LByte) in line after V_Start.
//#define _P0_TEST_PTN_HPOS_L_D9              	0xD9        // Assign the test pattern digitized position(LByte) in line after H_Start.
//#define _P0_TEST_PTN_RD_DA                  	0xDA        // Test Pattern Red Channel Digitized Result
//#define _P0_TEST_PTN_GD_DB                  	0xDB        // Test Pattern Green Channel Digitized Result
//#define _P0_TEST_PTN_BD_DC                  	0xDC        // Test Pattern Blue Channel Digitized Result

//--------------------------------------------------
// Auto Black Level (Page0)
//--------------------------------------------------
#define _P0_ABL_CTRL1_E2                    	0xE2        // Auto Black Level Control Register1
#define _P0_ABL_CTRL2_E3                    	0xE3        // Auto Black Level Control Register2
#define _P0_ABL_CTRL3_E4                    	0xE4        // Auto Black Level Control Register3
#define _P0_ABL_CTRL4_E5                    	0xE5        // Auto Black Level Control Register4
#define _P0_ABL_CTRL5_E6                    	0xE6        // Auto Black Level Control Register5
#define _P0_ABL_CTRL6_E7                    	0xE7        // Auto Black Level Control Register6
#define _P0_ABL_CTRL7_E8                    	0xE8        // Auto Black Level Control Register6
//#define _P0_ABL_R_VALUE_E9                  	0xE9        // Auto Black Level Value of Red Channel in Test Mode
//#define _P0_ABL_G_VALUE_EA                  	0xEA        // Auto Black Level Value of Green Channel in Test Mode
//#define _P0_ABL_B_VALUE_EB                  	0xEB        // Auto Black Level Value of Blue Channel in Test Mode
//#define _P0_ABL_R_NOISE_VALUE_EC           	0xEC        // Auto Black Level Noise Value of Red Channel in Test Mode
//#define _P0_ABL_G_NOISE_VALUE_ED           	0xED        // Auto Black Level Noise Value of Green Channel in Test Mode
//#define _P0_ABL_B_NOISE_VALUE_EE           	0xEE        // Auto Black Level Noise Value of Blue Channel in Test Mode

//Address: P0-EF ~ P0-F2 Reserved

//--------------------------------------------------
// Low Voltage Reset (Page0)
//--------------------------------------------------
#define _P0_POWER_ON_RESET_F3               	0xF3        // Negative Threshold Value For Power On Reset

//--------------------------------------------------
// Schmitt Trigger Control (Page0)
//--------------------------------------------------
#define _P0_HS_SCHMITT_TRIGGER_CTRL_F4     		0xF4        // Schmitt Trigger Control Register
//Address: P0-F5 ~ P0-FF Reserved

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////      Page 1: PLL     //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// DDS Setting For ADC PLL (Page1)
//--------------------------------------------------
#define _P1_PLL_DIV_CTRL_A0                 	0xA0        // PLL DIV Control Register
#define _P1_I_CODE_M_A1                     	0xA1        // I Code MByte
#define _P1_I_CODE_L_A2                     	0xA2        // I Code LByte
#define _P1_P_CODE_A3                       	0xA3        // P Code
//#define _P1_PFD_CALIBRATED_RESULTS_H_A4     	0xA4        // PFD Calibrated Result HByte
//#define _P1_PFD_CALIBRATED_RESULTS_L_A5     	0xA5        // PFD Calibrated Result LByte
//#define _P1_PE_MEASURE_H_A6                 	0xA6        // Phase Error Measure HByte
//#define _P1_PE_MEASURE_L_A7                 	0xA7        // Phase Error Measure LByte
//#define _P1_PE_MAX_MEASURE_H_A8             	0xA8        // Phase Error Max MEasure HByte
//#define _P1_PE_MAX_MEASURE_L_A9             	0xA9        // Phase Error Max MEasure LByte
#define _P1_FAST_PLL_CTRL_AA                	0xAA        // Fast PLL Control Register
#define _P1_FAST_PLL_ISUM_AB                	0xAB        // Fast PLL I_SUM
	
//--------------------------------------------------
// ADC PLL (Page1)
//--------------------------------------------------
#define _P1_PLL_M_AC                        	0xAC        // PLL M code
#define _P1_PLL_N_AD                        	0xAD        // PLL N Code
#define _P1_PLL_CRNT_AE                     	0xAE        // PLL Current/Resistor Register
#define _P1_PLL_WD_AF                       	0xAF        // PLL Watch Dog Register
#define _P1_MIX_B0                          	0xB0        // PLL Mix Register
#define _P1_PLLDIV_H_B1                     	0xB1        // PLL DIV HByte
#define _P1_PLLDIV_L_B2                     	0xB2        // PLL DIV LByte
//#define _P1_PLLPHASE_CTRL0_B3               	0xB3        // PLL Phase Control Register0
#define _P1_PLLPHASE_CTRL1_B4               	0xB4        // PLL Phase Control Register1
#define _P1_PLL_PHASE_INTERPOLATION_B5     		0xB5        // PLL Phase Interpolation
#define _P1_P_CODE_MAPPING_METHOD_B6      		0xB6        // P Code Mapping Method
#define _P1_PE_TRACKING_METHOD_B7           	0xB7        // PE Tracking Method
#define _P1_DDS_MIX_1_B8                    	0xB8        // DDS Mix 1
#define _P1_DDS_MIX_2_B9                    	0xB9        // DDS Mix 2
#define _P1_DDS_MIX_3_BA                    	0xBA        // DDS Mix 3
//#define _P1_DDS_MIX_4_BB                    	0xBB        // DDS Mix 4
//#define _P1_DDS_MIX_5_BC                    	0xBC        // DDS Mix 5
//#define _P1_DDS_MIX_6_BD                    	0xBD        // DDS Mix 6
//#define _P1_DDS_MIX_7_BE                    	0xBE        // DDS Mix 7
//--------------------------------------------------
// DPLL (Page1)
//--------------------------------------------------
#define _P1_DPLL_M_BF                       	0xBF        // DPLL M Divider
#define _P1_DPLL_N_C0                       	0xC0        // DPLL N Divider
#define _P1_DPLL_CRNT_C1                   	 	0xC1        // DPLL Current/Resistor Register

//--------------------------------------------------
// DCLK Spread Spectrum (Page1)
//--------------------------------------------------
#define _P1_DPLL_WD_C2                      	0xC2        // DPLL Watch Dog Register
#define _P1_DPLL_OTHER_C3                   	0xC3        // DPLL Other Register 
#define _P1_DCLK_FINE_TUNE_OFFSET_MSB_C4    	0xC4        // Display Clock Fine Tune Offset MSB
#define _P1_DCLK_FINE_TUNE_OFFSET_LSB_C5    	0xC5        // Display Clock Fine Tune Offset LSB
#define _P1_DCLK_SPREAD_SPECTRUM_C6         	0xC6        // Display Clock Spread Spectrum
#define _P1_EVEN_FIX_LASTLINE_M_C7          	0xC7        // Even Fixed Last Line MSB
#define _P1_EVEN_FIX_LASTLINE_DVTOTAL_L_C8 		0xC8        // Even Fixed Last Line DVTotal LSB
#define _P1_EVEN_FIX_LASTLINE_LENGTH_L_C9   	0xC9        // Even Fixed Last Line Length LSB
#define _P1_EVEN_FIXED_LAST_LINE_CTRL_CA    	0xCA        // Fixed Last Line Control Register

//Address: P1-C4 ~ P1-CF Reserved

//--------------------------------------------------
// Multiply PLL For Input Crystal (Page1)
//--------------------------------------------------
#define _P1_MULTIPLY_PLL_CTRL0_E0           	0xE0        // M2PLL Control Register0
#define _P1_MULTIPLY_PLL_CTRL1_E1           	0xE1        // M2PLL Control Register1
//#define _P1_RESERVED_E2                     	0xE2        // P1 Reserved E2
//#define _P1_RESERVED_E3                     	0xE3        // P1 Reserved E3
#define _P1_MULTIPLY_POWER_DOWN_E4          	0xE4        // M2PLL Power Down
//Address: P1-E5 ~ P1-E9 Reserved
//#define _P1_PLL_CHARGE_PUMP_CURRENT_0_EA     	0xEA        // PLL Charge Pump Current 0
#define _P1_LOOP_FILTER_CAPACITOR_EB            0xEB        // PLL Loop Filter Capacitor
//#define _P1_PLL_CHARGE_PUMP_CURRENT_2_EC     	0xEC        // PLL Charge Pump Current 2
//Address: P1-ED ~ P1-FF Reserved

#else

/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Page 0: Embedded ADC //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
#define _P0_ADC_CTRL_A1                     	0xA1        // ADC Control Register
#define _P0_ADC_RED_CTL_A2                  	0xA2        // ADC Red Channel Control Register
#define _P0_ADC_GREEN_CTL_A3                	0xA3        // ADC Green Channel Control Register
#define _P0_ADC_BLUE_CTL_A4                 	0xA4        // ADC Blue Channel Control Register
#define _P0_RED_GAIN_A5                     	0xA5        // ADC Red Channel Gain Adjust
#define _P0_RED_OFFSET_A8                   	0xA8        // ADC Red Channel Offset Adjust
#define _P0_SOG0_CTRL_AB                    	0xAB        // SOG Control Register0
#define _P0_SOG1_CTRL_AC                    	0xAC        // SOG Control Register1
#define _P0_ADC_POWER_AD                    	0xAD        // ADC Power Control Register
#define _P0_ADC_CLOCK_CTRL_AE               	0xAE        // ADC Clock Control Register
#define _P0_ADC_TEST_CTRL_AF                	0xAF        // ADC Test Control Register
#define _P0_ADC_V_BAIS1_B2                  	0xB2        // ADC Bais Voltage Control Register1
//Address: P0-B9~P0-BF Reserved
//--------------------------------------------------
// Auto Black Level
//--------------------------------------------------
#define _P0_AUTO_BLACK_LEVEL_CTRL1_C0       	0xC0        // Auto Black Level Control Register1
#define _P0_AUTO_BLACK_LEVEL_CTRL2_C1       	0xC1        // Auto Black Level Control Register2
#define _P0_AUTO_BLACK_LEVEL_CTRL3_C2       	0xC2        // Auto Black Level Control Register3
#define _P0_AUTO_BLACK_LEVEL_CTRL4_C3       	0xC3        // Auto Black Level Control Register4
#define _P0_AUTO_BLACK_LEVEL_CTRL5_C4       	0xC4        // Auto Black Level Control Register5
#define _P0_AUTO_BLACK_LEVEL_CTRL6_C5       	0xC5        // Auto Black Level Control Register6
//Address: P0-C6~P0-C7 Reserved
#define _P0_AUTO_BLACK_LEVEL_R_VALUE_C8     	0xC8        // Average Value of Red Channel in Test Mode
#define _P0_AUTO_BLACK_LEVEL_G_VALUE_C9     	0xC9        // Average Value of Green Channel in Test Mode
#define _P0_AUTO_BLACK_LEVEL_B_VALUE_CA     	0xCA        // Average Value of Blue Channel in Test Mode


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////      Page 1: PLL     //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// DDS Setting For ADC PLL
//--------------------------------------------------
#define _P1_PLL_DIV_CTRL_A1                 	0xA1        // PLL DIV Control Register
//#define _P1_I_CODE_L_A2                     	0xA2        // I Code LByte
#define _P1_I_CODE_M_A3                     	0xA3        // I Code MByte
//#define _P1_P_CODE_A4                       	0xA4        // P Code
//#define _P1_PFD_CALIBRATED_RESULTS_A5  0xA5        // PFD Calibrated Result
//#define _P1_PE_MEASURE_A6                   	0xA6        // Phase Error Measure
//#define _P1_PE_MAX_MEASURE_A7               	0xA7        // Phase Error Max MEasure
#define _P1_FAST_PLL_CTRL_A8                	0xA8        // Fast PLL Control Register
#define _P1_FAST_PLL_ISUM_A9                	0xA9        // Fast PLL I_SUM

//--------------------------------------------------
// ADC PLL1
//--------------------------------------------------
#define _P1_PLL1_M_AA                       	0xAA        // PLL1 M code
#define _P1_PLL1_N_AB                       	0xAB        // PLL1 N Code
//#define _P1_PLL1_CRNT_AC                    	0xAC        // PLL1 Current/Resistor Register
//#define _P1_PLL1_WD_AD                      	0xAD        // PLL1 Watch Dog Register

//--------------------------------------------------
// ADC PLL2
//--------------------------------------------------
#define _P1_PLL2_M_AE                       	0xAE        // PLL2 M code
#define _P1_PLL2_N_AF                       	0xAF        // PLL2 N code
#define _P1_PLL2_CRNT_B0                  		0xB0        // PLL2 Current/Resistor Register
#define _P1_PLL2_WD_B1                      	0xB1        // PLL2 Watch Dog Register
#define _P1_PLLDIV_H_B2                     	0xB2        // PLL DIV HByte
#define _P1_PLLDIV_L_B3                     	0xB3        // PLL DIV LByte
//#define _P1_PLLPHASE_CTRL0_B4              	0xB4        // PLL Phase Control Register0
#define _P1_PLLPHASE_CTRL1_B5               	0xB5        // PLL Phase Control Register1
#define _P1_PLL2_PHASE_INTERPOLATION_B6			0xB6        // PLL2 Phase Interpolation

//--------------------------------------------------
// DPLL
//--------------------------------------------------
#define _P1_DPLL_M_B7                       	0xB7        // DPLL M Divider
#define _P1_DPLL_N_B8                       	0xB8        // DPLL N Divider
//#define _P1_DPLL_CRNT_B9                 		0xB9        // DPLL Current/Resistor Register
#define _P1_DPLL_WD_BA                      	0xBA        // DPLL Watch Dog Register
#define _P1_DPLL_OTHER_BB	             		0xBB        // DPLL Other Register
//--------------------------------------------------
// DCLK Spread Spectrum
//--------------------------------------------------
#define _P1_DCLK_FINE_TUNE_OFFSET_MSB_BC		0xBC        // Display Clock Fine Tune Offset MSB
#define _P1_DCLK_FINE_TUNE_OFFSET_LSB_BD    	0xBD        // Display Clock Fine Tune Offset LSB
#define _P1_DCLK_SPREAD_SPECTRUM_BE         	0xBE        // Display Clock Spread Spectrum
#define _P1_FIXED_LAST_LINE_MSB_BF          	0xBF        // Fixed Last Line MSB
//#define _P1_FIXED_LAST_LINE_DVTOTAL_LSB_C0  	0xC0        // Fixed Last Line DVTotal LSB
//#define _P1_FIXED_LAST_LINE_LENGTH_LSB_C1   	0xC1        // Fixed Last Line Length LSB
#define _P1_FIXED_LAST_LINE_CTRL_C2         	0xC2        // Fixed Last Line Control Register
//Address: C3 Reserved

//--------------------------------------------------
// Multiply PLL For Input Crystal
//--------------------------------------------------
#define _P1_MULTIPLY_PLL_CTRL0_C4           	0xC4        // Multiply PLL Control Register0
//#define _P1_MULTIPLY_PLL_CTRL1_C5           	0xC5        // Multiply PLL Control Register1
//Address: C6,C7 Reserved

//--------------------------------------------------
// Memory PLL
//--------------------------------------------------
#define _P1_MPLL_M_C8                       	0xC8        // MPLL M Divider Register
//#define _P1_MPLL_N_C9                       	0xC9        // MPLL N Divider Register
//#define _P1_MPLL_CRNT_CA                    	0xCA        // MPLL Current/Resistor Register
//#define _P1_MPLL_WD_CB                      	0xCB        // MPLL Watch Dog Register
//#define _P1_MPLL_MISC_CC                    	0xCC        // MPLL MISC Register

//--------------------------------------------------
// MCLK Spread Spectrum
//--------------------------------------------------
//#define _P1_MCLK_FINE_TUNE_OFFSET_MSB_CD    	0xCD        // Memory Clock Fine Tune Offset MSB
//#define _P1_MCLK_FINE_TUNE_OFFSET_LSB_CE    	0xCE        // Memory Clock Fine Tune Offset LSB
//#define _P1_MCLK_SPREAD_SPECTRUM_CF         	0xCF        // Memory Clock Spread Spectrum
//Address: P1-D0~P1-DF Reserved
#endif

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////Page 2: TMDS/HDCP/HDMI//////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// TMDS Receiver(Page 2)
//--------------------------------------------------
//#define _P2_RESERVED_A0                     	0xA0        // P2 Reserved A0
#define _P2_TMDS_MEAS_SELECT_A1           		0xA1        // TMDS Measure Select
#define _P2_TMDS_MEAS_RESULT0_A2         		0xA2        // TMDS Measure Result0
#define _P2_TMDS_MEAS_RESULT1_A3         		0xA3        // TMDS Measure Result1
#define _P2_TMDS_CTRL_A4                    	0xA4        // TMDS Control Register
#define _P2_CRC_OUTPUT_BYTE_2_A5         		0xA5        // CRC Output Byte2
#define _P2_TMDS_OUTPUT_CTRL_A6           		0xA6        // TMDS Output Control Register
#define _P2_POWER_ON_OFF_CTRL_A7       			0xA7        // TMDS Power On/Off Control Register
#define _P2_ANALOG_COMMON_CTRL0_A8  			0xA8        // Analog Common Control Register 0
#define _P2_ANALOG_COMMON_CTRL1_A9  			0xA9        // Analog Common Control Register 1
#define _P2_ANALOG_BIAS_CTRL_AA            		0xAA        // Analog Bias Control Register
#define _P2_ANALOG_COMMON_CTRL2_AB  			0xAB        // Analog Common Control Register 2
#define _P2_Z0_CALIBRATION_CTRL_AC       		0xAC        // Z0 Calibration Control Register
#define _P2_CLOCK_PLL_SETTING_AD          		0xAD        // Clock PLL Setting
#define _P2_RGB_PLL_SETTING_AE              	0xAE        // R/G/B PLL Setting
#define _P2_WATCH_DOG_CTRL_AF              		0xAF        // Watch Dog Control Register
#define _P2_CDR_CTRL0_B0                    	0xB0        // CDR Control Register 0
#define _P2_CDR_CTRL1_B1                    	0xB1        // CDR Control Register 1
#define _P2_CDR_CTRL2_B2                    	0xB2        // CDR Control Register 2
#define _P2_UP_DOWN_ADJUSTING1_B3     			0xB3        // Up/Down Adjusting 1
#define _P2_ADAPTIVE_EQUALIZER_B4         		0xB4        // Adaptive Equalizer
#define _P2_UP_DOWN_CTRL0_B5                	0xB5        // Up/Down Control Register 0
#define _P2_UP_DOWN_CTRL1_B6                	0xB6        // Up/Down Control Register 1
#define _P2_UP_DOWN_CTRL2_B7                	0xB7        // Up/Down Control Register 2
#define _P2_ADAPTIVE_EQUALIZER2_B8      		0xB8        // Adaptive Equalizer accumulative threshold (LPF1)//731301
//#define _P2_ADAPTIVE_EQUALIZER3_B9        	0xB9        // Adaptive Equalizer continuous threshold (LPF2)
//#define _P2_ADAPTIVE_EQUALIZE4_BA          	0xBA        // Adaptive Equalizer auto stop threshold

//--------------------------------------------------
// HDCP1.1(Port)
//--------------------------------------------------
#define _P2_HDCP_CTRL_C0                    	0xC0        // HDCP Control Register
#define _P2_DEVICE_KEY_ACCESS_PORT_C1   		0xC1        // Device Key Access Port
#define _P2_HDCP_PORT_CTRL_C2		        	0xC2        // HDCP Port Control Register
#define _P2_HDCP_ADDR_PORT_C3               	0xC3        // HDCP Address Port
#define _P2_HDCP_DATA_PORT_C4               	0xC4        // HDCP Data Port
//Address: P2-C5~P2-C6 Reserved

//--------------------------------------------------
// HDMI(Port)
//--------------------------------------------------
#define _P2_HDMI_APC_C8                     	0xC8        //
#define _P2_HDMI_ADDR_PORT_C9               	0xC9        // HDMI Address Port
#define _P2_HDMI_DATA_PORT_CA               	0xCA        // HDMI Data Port
#define _P2_HDMI_SR_CB                      	0xCB        // HDMI Status Register
#define _P2_HDMI_GPVS_CC                    	0xCC        // HDMI Packet Variation Status Register
#define _P2_HDMI_PSAP_CD                    	0xCD        // HDMI Address For Packet Storage SRAM
#define _P2_HDMI_DSAP_CE                    	0xCE        // HDMI Data For Packet Storage SRAM
//Address: P2-CF ~ P2-FF Reserved


#if(_SCALER_TYPE == _RTD3580D)
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////   Page 3: Reserved   //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//Reserved Page (Page 3)

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////   Page 4: Reserved   //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//Reserved Page (Page 4)

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////   Page 5: Reserved   //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//Reserved Page (Page 5)
#else

/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////Page 3: LiveShowTM Control////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
#define _P3_LS_CTRL0_A1                     	0xA1        // Live Show Control Register0
#define _P3_LS_CTRL1_A2                     	0xA2        // Live Show Control Register1
//Address: P3-A3 Reserved
#define _P3_LS_CPRS_CTRL_A4                 	0xA4        // Live Show Compression Type Control Register
#define _P3_LS_TG_SIZE_H_A5                 	0xA5        // Live Show Target Size For Compression HByte
//#define _P3_LS_TG_SIZE_L_A6                 	0xA6        // Live Show Target Size For Compression LByte
#define _P3_LS_GRP_NUM_H_A7                 	0xA7        // Live Show Number Of Pixel Per Group To Be Analyzed And Compressed HByte
//#define _P3_LS_GRP_NUM_L_A8                 	0xA8        // Live Show Number Of Pixel Per Group To Be Analyzed And Compressed LByte
//#define _P3_LS_FAIL_CNT_H_A9                	0xA9        // Live Show The Count Of Compression Fail HByte
//#define _P3_LS_FAIL_CNT_L_AA                	0xAA        // Live Show The Count Of Compression Fail LByte
//Address: P3-AB~P3-AD Reserved
#define _P3_LS_LUT_ROW_ADDR_AE            		0xAE        // Live Show LUT Row Address
#define _P3_LS_LUT_COL_ADDR_AF          		0xAF        // Live Show LUT Colunm Address
#define _P3_LS_LUT_DATA_B0                  	0xB0        // Live Show LUT Data Port
//#define _P3_LS_DELTA_GAIN_B1                	0xB1        // Live Show Delta Gain Setting
//#define _P3_LS_UDST_THD_B2                 	0xB2        // Live Show Undershoot Threshold(2's Complement)
//#define _P3_LS_OVST_THD_B3                  	0xB3        // Live Show Overshoot Threshold
//#define _P3_LS_UDST_GAIN_B4                 	0xB4        // Live Show Undershoot Gain
//#define _P3_LS_OVST_GAIN_B5                 	0xB5        // Live Show Overshoot Gain
#define _P3_LS_STATUS0_B6                   	0xB6        // Live Show Status Register0
//#define _P3_LS_STATUS1_B7                   	0xB7        // Live Show Status Register1
//Address: P3-B8~P3-BF Reserved
#define _P3_LS_WTLVL_W_C0                   	0xC0        // Live Show Water Level Write Register
#define _P3_LS_WTLVL_R_C1                   	0xC1        // Live Show Water Level Read Register
#define _P3_LS_MEM_FIFO_RW_NUM_H_C2    			0xC2        // The Read/Write Times Of Total Memory Access HByte
//#define _P3_LS_MEM_FIFO_RW_NUM_L_C3       	0xC3        // The Read/Write Times Of Total Memory Access LByte
#define _P3_LS_MEM_FIFO_RW_LEN_C4          		0xC4        // The Read/Write Number Of Words In Each Memory Access
#define _P3_LS_MEM_FIFO_RW_REMAIN_C5   			0xC5        // The Read/Write Number Of Words At The Last Access. This Register Must Be 4X
#define _P3_LS_MEM_START_ADDR_H_C6        		0xC6        // Start Address Of Live Show Memory Block HByte(Total 22/23 bits)
//#define _P3_LS_MEM_START_ADDR_M_C7         	0xC7        // Start Address Of Live Show Memory Block MByte(Total 22/23 bits)
//#define _P3_LS_MEM_START_ADDR_L_C8         	0xC8        // Start Address Of Live Show Memory Block LByte(Total 22/23 bits)
//#define _P3_LS_BIST_CTRL_C9                 	0xC9        // Live Show BIST Control Register
//#define _P3_LS_COMP_CHK_CA                  	0xCA        // Live Show Decompression Previous Buffer Status Check
//#define _P3_LS_COMP_REOVFW_CB               	0xCB        // Reorder Buffer Overflow By Group Dummy Purge LSB


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////Page 4: SDRAM Control///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
#define _P4_SDR_CTRL0_A1                    	0xA1        // SDRAM Control Register0
//#define _P4_SDR_CTRL1_A2                    	0xA2        // SDRAM Control Register1
//#define _P4_SDR_AREF_TIME_A3                	0xA3        // SDRAM Auto Refresh Time
#define _P4_SDR_PRCG_A4                     	0xA4        // SDRAM Precharge Control Register
//#define _P4_SDR_MEM_TYPE_A5                 	0xA5        // SDRAM Memory Size Select
//#define _P4_SDR_SLEW_RATE_A6                	0xA6        // SDRAM Slew Rate Control Register
//#define _P4_SDR_AREF_CNT_A7                 	0xA7        // Number Of Auto Refresh
//Address: P4-A8~P4-A9 Reserved
//#define _P4_SDR_RSC_AREF_AA                 	0xAA        // SDRAM Arbiter Token Ring For Auto Refresh
//#define _P4_SDR_RSC_MCU_AB                  	0xAB        // SDRAM Arbiter Token Ring For MCU
//#define _P4_SDR_RSC_CAP1_AC                 	0xAC        // SDRAM Arbiter Token Ring For CAP1
//Address: P4-AD Reserved
//#define _P4_SDR_RSC_MAIN_AE                 	0xAE        // SDRAM Arbiter Token Ring For Main
//Address: P4-AF Reserved
//#define _P4_SDR_RSC_RD_B0                   	0xB0        // SDRAM Arbiter Token Ring For RD
//#define _P4_SDR_RSC_WR_B1                   	0xB1        // SDRAM Arbiter Token Ring For WR
//Address: P4-B2~P4-B3 Reserved
//#define _P4_SDR_ABTR_STATUS0_B4          		0xB4        // SDRAM Arbiter Status Register0
//#define _P4_SDR_ABTR_STATUS1_B5          		0xB5        // SDRAM Arbiter Status Register1
//Address: P4-B6~P4-B7 Reserved
//#define _P4_SDR_ADDR_H_B8                   	0xB8        // SDRAM Access Address HByte
//#define _P4_SDR_ADDR_M_B9                   	0xB9        // SDRAM Access Address MByte
//#define _P4_SDR_ADDR_L_BA                   	0xBA        // SDRAM Access Address LByte
//#define _P4_SDR_ACCESS_CMD_BB            		0xBB        // SDRAM Access Command
//#define _P4_SDR_DATA_BUF_BC                 	0xBC        // SDRAM Data Buffer
//Address: P4-BD~P4-BF Reserved
#define _P4_SDR_CLK_DELAY_C0                	0xC0        // SDRAM Clock Delay Control Register
#define _P4_SDR_CLK_DELAY0_C1               	0xC1        // SDRAM Clock Delay Control Register0
//#define _P4_SDR_CLK_DELAY1_C2               	0xC2        // SDRAM Clock Delay Control Register1
//#define _P4_SDR_CLK_DELAY2_C3               	0xC3        // SDRAM Clock Delay Control Register2
//#define _P4_SDR_CLK_DELAY3_C4               	0xC4        // SDRAM Clock Delay Control Register3
//Address: P4-C5~P4-DF Reserved

/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////Page 5: SDR_FIFO Control/////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//#define _P5_SDRF_IN1_FIFO_STATUS_A1         	0xA1        // SDRAM IN1 FIFO Status Register
//#define _P5_SDRF_MAIN_FIFO_STATUS_A2        	0xA2        // SDRAM MAIN FIFO Status Register
//Address: P5-A3~P5-A7 Reserved
//#define _P5_SDRF_IN1_WATER_LEVEL_A8         	0xA8        // SDRAM FIFO IN1 Water Level Register
//#define _P5_SDRF_IN1_WR_NUM_H_A9            	0xA9        // Number Of Length To Fill In The SDR Memory HByte
//#define _P5_SDRF_IN1_WR_NUM_L_AA            	0xAA        // Number Of Length To Fill In The SDR Memory LByte
//#define _P5_SDRF_IN1_WR_LEN_AB              	0xAB        // Length Of Data To Fill In The SDR Memory Once (unit : 64 bit)
//#define _P5_SDRF_IN1_WR_REMAIN_AC           	0xAC        // The Remained Part That Can't Make A Complete Length (unit : 64 bit)
//#define _P5_SDRF_IN1_MEM_ADDR_H_AD          	0xAD        // The Initial Write Address Of SDR Memory HByte
//#define _P5_SDRF_IN1_MEM_ADDR_M_AE          	0xAE        // The Initial Write Address Of SDR Memory MByte
//#define _P5_SDRF_IN1_MEM_ADDR_L_AF          	0xAF        // The Initial Write Address Of SDR Memory LByte
//#define _P5_SDRF_IN1_LINE_STEP_H_B0         	0xB0        // The Distance Between Two Lines Of SDR Memory HByte
//#define _P5_SDRF_IN1_LINE_STEP_L_B1         	0xB1        // The Distance Between Two Lines Of SDR Memory LByte
//#define _P5_SDRF_IN1_BLOCK_STEP_H_B2        	0xB2        // The Distance Between Two Blocks Of SDR Memory HByte
//#define _P5_SDRF_IN1_BLOCK_STEP_L_B3        	0xB3        // The Distance Between Two Blocks Of SDR Memory LByte
//#define _P5_SDRF_IN1_BL2_ADDR_H_B4          	0xB4        // Second Block Of SDR To Progress The Double Buffer. The Given Address Is The Absolute One HByte
//#define _P5_SDRF_IN1_BL2_ADDR_M_B5          	0xB5        // Second Block Of SDR To Progress The Double Buffer. The Given Address Is The Absolute One MByte
//#define _P5_SDRF_IN1_BL2_ADDR_L_B6          	0xB6        // Second Block Of SDR To Progress The Double Buffer. The Given Address Is The Absolute One LByte
//#define _P5_SDRF_IN1_LINE_NUM_H_B7          	0xB7        // The Total Line Number Of One Image HByte (Total 12 bits)
//#define _P5_SDRF_IN1_LINE_NUM_L_B8          	0xB8        // The Total Line Number Of One Image LByte (Total 12 bits)
#define _P5_SDRF_IN1_SDR_CTRL_B9            	0xB9        // SDRAM IN1 FIFO Control Register
//Address: P5-BA Reserved
//#define _P5_SDRF_IN1_SDR_STATUS_BB          	0xBB        // SDRAM IN1 Status Register
//#define _P5_SDRF_MN_PRERD_VST_H_BC          	0xBC        // Vertical Start Line Of MAIN To Pre-Read Input Data HByte (Total 11-bits)
//#define _P5_SDRF_MN_PRERD_VST_L_BD          	0xBD        // Vertical Start Line Of MAIN To Pre-Read Input Data LByte (Total 11-bits)
//#define _P5_SDRF_MN_PXL_NUM_H_BE            	0xBE        // Pixel Number Of One Line, For FIFO To Clear Garbage From Capture Side HByte (Total 11-bits)
//#define _P5_SDRF_MN_PXL_NUM_L_BF            	0xBF        // Pixel Number Of One Line, For FIFO To Clear Garbage From Capture Side LByte (Total 11-bits)
//#define _P5_SDRF_MN_WTLVL_C0                	0xC0        // When FIFO Depth Is Under Water Level, FIFO Requests Data
//Address: P5-C1 Reserved
//#define _P5_SDRF_MN_READ_NUM_H_C2           	0xC2        // Number Of Length To Read From SDR In One Line HByte
//#define _P5_SDRF_MN_READ_NUM_L_C3           	0xC3        // Number Of Length To Read From SDR In One Line LByte
//#define _P5_SDRF_MN_READ_LEN_C4             	0xC4        // The Length Of Data To Read From SDR Once
//#define _P5_SDRF_MN_READ_REMAIN_C5          	0xC5        // The Remain Part That Can't Be A Complete Length In One Line
//#define _P5_SDRF_MN_READ_ADDR_H_C6          	0xC6        // The Initial Read Address Of SDR HByte (Total 23-bits)
//#define _P5_SDRF_MN_READ_ADDR_M_C7          	0xC7        // The Initial Read Address Of SDR MByte (Total 23-bits)
//#define _P5_SDRF_MN_READ_ADDR_L_C8          	0xC8        // The Initial Read Address Of SDR LByte (Total 23-bits)
//#define _P5_SDRF_MN_LINE_STEP_H_C9          	0xC9        // Line Step Indicates The Distance Between Two Lines HByte (Total 12 bits)
//#define _P5_SDRF_MN_LINE_STEP_L_CA          	0xCA        // Line Step Indicates The Distance Between Two Lines LByte (Total 12 bits)
//#define _P5_SDRF_MN_BLOCK_STEP_H_CB         	0xCB        // The Distance Between Two Blocks Of SDR HByte (Total 12-bits)
//#define _P5_SDRF_MN_BLOCK_STEP_L_CC         	0xCC        // The Distance Between Two Blocks Of SDR LByte (Total 12-bits)
//#define _P5_SDRF_MN_LINE_NUM_H_CD           	0xCD        // The Total Line Number Of One Image HByte (Total 12 bits)
//#define _P5_SDRF_MN_LINE_NUM_L_CE           	0xCE        // The Total Line Number Of One Image LByte (Total 12 bits)
#define _P5_SDRF_MN_DISP_CTRL_CF            	0xCF        // SDRAM FIFO MAIN Display Control Register
#define _P5_SDRF_MN_SDR_STATUS_D0           	0xD0        // SDRAM Status Register
//Address: P5-D1~P5-DF Reserved
#endif

#if(_SCALER_TYPE == _RTD3580D)
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////   Page 6: De-interlace  ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// De-interlace (Page6)
//--------------------------------------------------
#define _P6_ENABLE_BIST_CTRL_A0             	0xA0        // Enable and Bist Control Register
#define _P6_INTERPOLATION_CTRL_A1           	0xA1        // Interpolation Control Register
#define _P6_PIXEL_DIFF_THRESHOLD_A2         	0xA2        // Pixel Difference Threshold
#define _P6_PIXEL_REF_DIFF_THRESHOLD_A3   		0xA3        // Pixel Reference Difference Threshold
#define _P6_GRADIENT_THRESHOLD_POS_A4      		0xA4        // Pixel Gradient Threshold Positive
#define _P6_GRADIENT_THRESHOLD_NEG_A5       	0xA5        // Pixel Gradient Threshold Negative

//--------------------------------------------------
// Post Processing Control (Page6)
//--------------------------------------------------
#define _P6_SMOOTHING_ERROR_CORR_CTRL_A6 		0xA6        // Smoothing and Error Correction Control Register
#define _P6_DELETE_LINE_PIXEL_ENABLE_A7     	0xA7        // Delete Line and Pixel Enable
#define _P6_MEDIAN_FILTER_THRESHOLD_A8      	0xA8        // Median Filter Threshold

//--------------------------------------------------
// Noise Estimation (Page6)
//--------------------------------------------------
#define _P6_HORIZONTAL_ACTIVE_SIZE_MSB_A9 		0xA9        // Horizontal Active Size MSB
#define _P6_HORIZONTAL_ACTIVE_SIZE_LSB_AA  		0xAA        // Horizontal Active Size LSB
#define _P6_VERTICAL_ACTIVE_SIZE_MSB_AB     	0xAB        // Vertical Active Size MSB
#define _P6_VERTICAL_ACTIVE_SIZE_LSB_AC     	0xAC        // Vertical Active Size LSB
#define _P6_CALCULATED_REGION_CTRL_AD       	0xAD        // Calculated Region Control Register 
#define _P6_H1_ACTIVE_START_POINT_MSB_AE    	0xAE        // Horizontal Active Start Point 1 MSB
#define _P6_H1_ACTIVE_START_POINT_LSB_AF    	0xAF        // Horizontal Active Start Point 1 LSB
#define _P6_H1_ACTIVE_END_POINT_MSB_B0      	0xB0        // Horizontal Active End Point 1 MSB
#define _P6_H1_ACTIVE_END_POINT_LSB_B1      	0xB1        // Horizontal Active End Point 1 LSB
#define _P6_H2_ACTIVE_START_POINT_MSB_B2    	0xB2        // Horizontal Active Start Point 2 MSB
#define _P6_H2_ACTIVE_START_POINT_LSB_B3   		0xB3        // Horizontal Active Start Point 2 LSB
#define _P6_H2_ACTIVE_END_POINT_MSB_B4      	0xB4        // Horizontal Active End Point 2 MSB
#define _P6_H2_ACTIVE_END_POINT_LSB_B5      	0xB5        // Horizontal Active End Point 2 LSB
#define _P6_H3_ACTIVE_START_POINT_MSB_B6    	0xB6        // Horizontal Active Start Point 3 MSB
#define _P6_H3_ACTIVE_START_POINT_LSB_B7    	0xB7        // Horizontal Active Start Point 3 LSB
#define _P6_H3_ACTIVE_END_POINT_MSB_B8      	0xB8        // Horizontal Active End Point 3 MSB
#define _P6_H3_ACTIVE_END_POINT_LSB_B9      	0xB9        // Horizontal Active End Point 3 LSB
#define _P6_MIN_SPA_NOISE_VALUE_BIN1_BA     	0xBA        // Minimum Spatial Noise Value Within Bin1
#define _P6_MIN_SPA_NOISE_VALUE_BIN2_BB     	0xBB        // Minimum Spatial Noise Value Within Bin2
#define _P6_MIN_SPA_NOISE_VALUE_BIN3_BC     	0xBC        // Minimum Spatial Noise Value Within Bin3
#define _P6_MIN_SPA_NOISE_VALUE_BIN4_BD    		0xBD        // Minimum Spatial Noise Value Within Bin4
#define _P6_MIN_SPA_NOISE_VALUE_BIN5_BE     	0xBE        // Minimum Spatial Noise Value Within Bin5
#define _P6_MIN_SPA_NOISE_VALUE_BIN6_BF     	0xBF        // Minimum Spatial Noise Value Within Bin6
#define _P6_MIN_SPA_NOISE_VALUE_BIN7_C0     	0xC0        // Minimum Spatial Noise Value Within Bin7

//--------------------------------------------------
// Peaking and Coring and EMF/Chroma Lowpass (Page6)
//--------------------------------------------------
#define _P6_PEAKING_ENABLE_C1               	0xC1        // Peaking Enable 
#define _P6_PEAKING_DATA00_C2               	0xC2        // Peaking Data 00  
#define _P6_PEAKING_DATA01_C3               	0xC3        // Peaking Data 01 
#define _P6_PEAKING_DATA02_C4               	0xC4        // Peaking Data 02
#define _P6_PEAKING_DATA03_C5               	0xC5        // Peaking Data 03
#define _P6_PEAKING_DATA04_C6               	0xC6        // Peaking Data 04
#define _P6_PEAKING_DATA05_C7               	0xC7        // Peaking Data 05
#define _P6_PEAKING_DATA06_C8               	0xC8        // Peaking Data 06
#define _P6_PEAKING_DATA07_C9               	0xC9        // Peaking Data 07
#define _P6_PEAKING_DATA08_CA               	0xCA        // Peaking Data 08
#define _P6_PEAKING_DATA09_CB               	0xCB        // Peaking Data 09
#define _P6_PEAKING_DATA0A_CC               	0xCC        // Peaking Data 0A
#define _P6_PEAKING_DATA0B_CD               	0xCD        // Peaking Data 0B
#define _P6_CHROMA_LOWPASS_FACTOR_CE        	0xCE        // Peaking Chroma Lowpass Factor

//--------------------------------------------------
// YUV422 to YUV444 Conversion & 2 to 1 Setup (Page6)
//--------------------------------------------------
#define _P6_YUV422_TO_YUV444_D4             	0xD4        // YUV422 to YUV444 Control Register 
#define _P6_ACTIVE_BLANK_WINDOW_CTRL_MSB_D5 	0xD5        // Active Window & Blanking Window Control Register MSB 
#define _P6_ACTIVE_WINDOW_CTRL_LSB_D6       	0xD6        // Active Window Control Register LSB 
#define _P6_BLANK_WINDOW_CTRL_LSB_D7        	0xD7        // Blanking Window Control Register LSB 

//--------------------------------------------------
// DCTi in I-Domain (Page6)
//--------------------------------------------------
#define _P6_DCTI_1ST_GAIN_D8                	0xD8        // DCTi 1st Gain 
#define _P6_DCTI_1ST_GAIN_THRESHOLD_D9      	0xD9        // DCTi 1st Gain Threshold

//--------------------------------------------------
// Noise Reduction in I-domain (Page6)
//--------------------------------------------------
#define _P6_CP_CTRL_DA                      	0xDA        // CP Control Register 
#define _P6_SPATIAL_CTRL_DB                 	0xDB        // Spatial Control Register 
#define _P6_SPATIAL_THLY_DC                 	0xDC        // Spatial Threshold for Luma
#define _P6_SPATIAL_THLC_DD                 	0xDD        // Spatial Threshold for Chroma
#define _P6_IMPULSE_PIXEL_DIFF_THL_DE       	0xDE        // Impulse Pixel Diff Threshold
#define _P6_IMPULSE_THLY_DF                 	0xDF        // Impulse Threshold for Luma
#define _P6_IMPULSE_THLC_E0                 	0xE0        // Impulse Threshold for Chroma
#define _P6_IMPULSE_SMOOTH_THLY_E1          	0xE1        // Impulse Smooth Threshold for Luma
#define _P6_IMPULSE_SMOOTH_THLC_E2          	0xE2        // Impulse Smooth Threshold for Chroma

//--------------------------------------------------
// Scale Down (Page6)
//--------------------------------------------------
#define _P6_UZD_CTRL0_E3                    	0xE3        // UZD Control Register 0 
#define _P6_UZD_CTRL1_E4                    	0xE4        // UZD Control Register 1
#define _P6_UZD_SCALE_HOR_FACTOR_H_E5       	0xE5        // Horizontal Scale Factor HByte
#define _P6_UZD_SCALE_HOR_FACTOR_M_E6       	0xE6        // Horizontal Scale Factor MByte
#define _P6_UZD_SCALE_HOR_FACTOR_L_E7       	0xE7        // Horizontal Scale Factor LByte
#define _P6_UZD_SCALE_VER_FACTOR_H_E8       	0xE8        // Vertical Scale Factor HByte
#define _P6_UZD_SCALE_VER_FACTOR_M_E9       	0xE9        // Vertical Scale Factor MByte
#define _P6_UZD_SCALE_VER_FACTOR_L_EA       	0xEA        // Vertical Scale Factor LByte
#define _P6_UZD_HOR_DELTA1_H_EB             	0xEB        // Horizontal Non-Linear Delta1 HByte
#define _P6_UZD_HOR_DELTA1_L_EC             	0xEC        // Horizontal Non-Linear Delta1 LByte
#define _P6_UZD_HOR_SEGMENT1_H_ED           	0xED        // Horizontal Non-Linear Segment1 HByte
#define _P6_UZD_HOR_SEGMENT1_L_EE           	0xEE        // Horizontal Non-Linear Segment1 LByte
#define _P6_UZD_HOR_SEGMENT2_H_EF           	0xEF        // Horizontal Non-Linear Segment2 HByte
#define _P6_UZD_HOR_SEGMENT2_L_F0           	0xF0        // Horizontal Non-Linear Segment2 LByte
#define _P6_UZD_HOR_INITIAL_VALUE_F1        	0xF1        // Horizontal Scaling Initial Value
#define _P6_UZD_VER_INITIAL_VALUE_F2        	0xF2        // Vertical Scaling Initial Value
#define _P6_UZD_FIR_COEF_INDEX_F3           	0xF3        // Filter Coefficient Index 
#define _P6_UZD_FIR_COEF_PORT_F4            	0xF4        // Filter Coefficient Port
#define _P6_UZD_CRC_CTRL_F5                 	0xF5        // CRC Control Register
#define _P6_UZD_CRC_HH_F6                   	0xF6        // CRC HHByte
#define _P6_UZD_CRC_H_F7                    	0xF7        // CRC HByte
#define _P6_UZD_CRC_M_F8                    	0xF8        // CRC MByte
#define _P6_UZD_CRC_L_F9                    	0xF9        // CRC LByte
#else
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////   Page 6: Reserved   //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//Reserved Page (Page 6)
#endif


#if(_SCALER_TYPE == _RTD3580D)
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////   Page 7: Vivid Color  ////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// Vivid Color - DLTi/DCTi (Page7)
//--------------------------------------------------
//#define _P7_RESERVED_A0                     	0xA0        // P7 Reserved A0
#define _P7_DLTI_DCTI_ENABLE_A1             	0xA1        // DLTi DCTi Enable
#define _P7_DLTI_HF_THRESHOLD_A2            	0xA2        // DLTi HF Threshold
#define _P7_DLTI_GAIN_A3                    	0xA3        // DLTi Gain 
#define _P7_DLTI_GAIN_THRESHOLD_A4       		0xA4        // DLTi Gain Threshold 
#define _P7_DLTI_OPTIONS_A5                 	0xA5        // DLTi Options
#define _P7_DCTI_1ST_GAIN_A6                	0xA6        // DCTi 1st Gain 
#define _P7_DCTI_1ST_GAIN_THRESHOLD_A7    		0xA7        // DCTi 1st Gain Threshold 
//#define _P7_RESERVED_A8                     	0xA8        // P7 Reserved A0

//--------------------------------------------------
// Peaking and Coring and EMF/Chroma Lowpass (Page7)
//--------------------------------------------------
#define _P7_PEAKING_ENABLE_A9               	0xA9        // Peaking Enable 
#define _P7_PEAKING_DATA00_AA               	0xAA        // Peaking Data 00  
#define _P7_PEAKING_DATA01_AB               	0xAB        // Peaking Data 01 
#define _P7_PEAKING_DATA02_AC               	0xAC        // Peaking Data 02
#define _P7_PEAKING_DATA03_AD               	0xAD        // Peaking Data 03
#define _P7_PEAKING_DATA04_AE               	0xAE        // Peaking Data 04
#define _P7_PEAKING_DATA05_AF               	0xAF        // Peaking Data 05
#define _P7_PEAKING_DATA06_B0               	0xB0        // Peaking Data 06
#define _P7_PEAKING_DATA07_B1               	0xB1        // Peaking Data 07
#define _P7_PEAKING_DATA08_B2               	0xB2        // Peaking Data 08
#define _P7_PEAKING_DATA09_B3               	0xB3        // Peaking Data 09
#define _P7_PEAKING_DATA0A_B4               	0xB4        // Peaking Data 0A
#define _P7_PEAKING_DATA0B_B5               	0xB5        // Peaking Data 0B
#define _P7_CHROMA_LOWPASS_FACTOR_B6     		0xB6        // Peaking Chroma Lowpass Factor

//--------------------------------------------------
// Auto Sharpness (Page7)
//--------------------------------------------------
#define _P7_AUTO_SHP_CTRL_B7                	0xB7        // Auto Sharpness Control Register
#define _P7_AUTO_SHP_ADDR_B8                	0xB8        // Noise Reduction and Sharpness Port Address
#define _P7_AUTO_SHP_DATA_B9                	0xB9        // Auto Sharpness DATA Port

//Address: P7-BA ~ P7-BE Reserved

//--------------------------------------------------
// Vivid Color - Video Color Space Conversion (Page7)
//--------------------------------------------------
#define _P7_YUV2RGB_CTRL_BF                 	0xBF        // YUV2RGB Control Register
#define _P7_YUV2RGB_ACCESS_C0               	0xC0        // YUV2RGB Access Port
#define _P7_YUV2RGB_DATA_C1                 	0xC1        // YUV2RGB Data Port

//Address: P7-C2 ~ P7-C6 Reserved

//--------------------------------------------------
// Vivid Color - DCC (Page7)
//--------------------------------------------------
#define _P7_DCC_CTRL0_C7                    	0xC7        // DCC Control Register 0
#define _P7_DCC_CTRL1_C8                    	0xC8        // DCC Control Register 1
#define _P7_DCC_ACCESS_PORT_C9              	0xC9        // DCC Access Port
#define _P7_DCC_DATA_PORT_CA                	0xCA        // DCC Data Port

//Address: P7-CB ~ P7-CF Reserved

//--------------------------------------------------
// Vivid Color - ICM (Page7)
//--------------------------------------------------
#define _P7_ICM_CTRL_D0                     	0xD0        // ICM Control Register
#define _P7_ICM_SEL_D1                      	0xD1        // ICM Accessing Through Data Port Select
#define _P7_ICM_ACCESS_PORT_D2              	0xD2        // ICM Access Port
#define _P7_ICM_DATA_PORT_D3                	0xD3        // ICM Data Port
#define _P7_PC_ACCESS_PORT_D6					0xD6		 //peaking & coring Access Port
#define _P7_PC_DATA_PORT_D7						0xD7		//peaking & coring Access data Port

#else
/////////////////////////////////////////////////////////////////////////////////////////
//////////Page 7: Misc. (LVR / Schmitt Trigger / PLL Test / MacroVision / VBI)///////////
/////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// Low Voltage Reset
//--------------------------------------------------
#define _P7_POWER_ON_RESET_A1               	0xA1        // Negative Threshold Value For Power On Reset
//Address: P7-A2~P7-A3 Reserved

//--------------------------------------------------
// Schmitt Trigger Control
//--------------------------------------------------
#define _P7_HS_SCHMITT_TRIGGER_CTRL_A4     		0xA4        // Schmitt Trigger Control Register
//Address: P7-A5~P7-B7 Reserved

//--------------------------------------------------
// VBI Control
//--------------------------------------------------
#define _P7_VBI_CTRL_B8                     	0xB8        // VBI Control Register
#define _P7_VBI_POS_EVEN_B9                 	0xB9        // VBI Position For Even Field
#define _P7_VBI_POS_ODD_BA                  	0xBA        // VBI Position For ODD Field
#define _P7_VBI_REF_LEVEL_BB                	0xBB        // The Threshold Level To Decode VBI
#define _P7_VBI_STATUS_BC                   	0xBC        // VBI Status Register
#define _P7_VBI_DATA0_BD                    	0xBD        // The First Byte of VBI Decode Data
#define _P7_VBI_DATA1_BE                    	0xBE        // The Second Byte of VBI Decode Data

//PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE
//PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE
//PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE
////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// Independent Color Management(Port)
//--------------------------------------------------
#define _ICM_CTRL_E0                        	0xE0        // ICM Control Register
#define _ICM_SEL_E1                         	0xE1        // ICM Accessing Through Data Port Select
#define _ICM_ACCESS_PORT_E2                 	0xE2        // ICM Access Port
#define _ICM_DATA_PORT_E3                   	0xE3        // ICM Data Port
#endif

#if(_SCALER_TYPE == _RTD3580D)
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////   Page 8: VD  /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
#define _P8_VIDEO_CTRL0_A0                   	0xA0        // Video Control 0
#define _P8_VIDEO_CTRL1_A1                   	0xA1        // Video Control 1
#define _P8_CLAMP_UPDN_EN_A2                 	0xA2        // ADC Switch Control
#define _P8_AGC_GATE_TH_SWAP_A3          		0xA3        // AGC Gate TH Swap
#define _P8_INOUT_CTRL_A4                    	0xA4        // Inout Control
//#define _RESERVED_A5                       	0xA5        // P8 Reserved A5 
//#define _RESERVED_A6                       	0xA6        // P8 Reserved A6
#define _P8_OUTPUT_CTRL_A7                  	0xA7        // Output Control
#define _P8_CONTRAST1_A8                     	0xA8        // Luma Contrast Adjust 
#define _P8_BRIGHTNESS1_A9                   	0xA9        // Luma Brightness Adjust 
#define _P8_SATURATION1_AA                   	0xAA        // Chroma Saturation Adjust 
#define _P8_HUE_AB                          	0xAB        // Chroma Hue Phase Adjust
#define _P8_DC_HACTIVE_START_AC            		0xAC        // DC Hactive Start
#define _P8_DC_VACTIVE_START_AD            		0xAD        // DC Vactive Start
#define _P8_THRESHOLD_AE                     	0xAE        // DC Threshold
#define _P8_DC_POSITIVE_GAIN_AF             	0xAF        // DC Positive Gain
#define _P8_NEGATIVE_GAIN_B0                 	0xB0        // DC Negetive Gain
#define _P8_YDC_STATUS_B1                    	0xB1        // YDC Status 
#define _P8_YDC_AVERAGE_STATUS_B2       		0xB2        // YDC Average Status 
#define _P8_DC_BALANCE_CTRL0_B3            		0xB3        // DC Balance Control 0
#define _P8_DC_BALANCE_CTRL1_B4            		0xB4        // DC Balance Control 1 
#define _P8_IRQ_MASK1_B5                     	0xB5        // IRQ Mask 1
#define _P8_IRQ_MASK2_B6                     	0xB6        // IRQ Mask 2
#define _P8_IRQ_STATUS1_B7                   	0xB7        // IRQ Status 1
#define _P8_IRQ_STATUS1_WCLR_B8           		0xB8        // IRQ Status 1 write 1 to clear
#define _P8_IRQ_STATUS2_B9                   	0xB9        // IRQ Status 2
#define _P8_IRQ_STATUS1_WCLR_BA           		0xBA        // IRQ Status 2write 1 to clear
#define _P8_ADC_LIMIT_TH_BB                  	0xBB        // ADC Limit Threshold
#define _P8_VD_STATUS1_BC                    	0xBC        // Video Status Register1
#define _P8_VD_STATUS2_BD                    	0xBD        // Video Status Register2
#define _P8_VD_STATUS3_BE                    	0xBE        // Video Status Register3
#define _P8_NOISE_TH_BF                      	0xBF        // Noise Threshold
#define _P8_HDTO_INC_STATUS4_C0           		0xC0        // HDTO Inc Status 4
#define _P8_HDTO_INC_STATUS3_C1           		0xC1        // HDTO Inc Status 3
#define _P8_HDTO_INC_STATUS2_C2           		0xC2        // HDTO Inc Status 2
#define _P8_HDTO_INC_STATUS1_C3           		0xC3        // HDTO Inc Status 1
#define _P8_CDTO_INC_STATUS4_C4           		0xC4        // CDTO Inc Status 4
#define _P8_CDTO_INC_STATUS3_C5           		0xC5        // CDTO Inc Status 3
#define _P8_CDTO_INC_STATUS2_C6           		0xC6        // CDTO Inc Status 2
#define _P8_CDTO_INC_STATUS1_C7           		0xC7        // CDTO Inc Status 1
#define _P8_AGAIN_STATUS_C8                  	0xC8        // Digital ADC Gain Value Hight byte
#define _P8_DGAIN_STATUS_C9                  	0xC9        // Digital ADC Gain Value Low byte
#define _P8_CMAG_STATUS_CA                   	0xCA        // Chroma Magnitude
#define _P8_CMAG_STATUS2_CB                  	0xCB        // Chroma Gain High Byte
#define _P8_CMAG_STATUS1_CC                  	0xCC        // Chroma Gain Low Byte
#define _P8_CORDIC_FREQ_STATUS_CD       		0xCD        // SECAM Cordic Frequency
#define _P8_NOISE_STATUS_CE                  	0xCE        // Noise Status
#define _P8_SOFT_RESET_CF                    	0xCF        // Video Soft Reset 
#define _P8_PALM_COMP1_D0                    	0xD0        // Palm Flag Compensation Counter.
#define _P8_PALM_COMP2_D1                    	0xD1        // Palm Flag Compensation Threshold
#define _P8_MANUAL_MODE_D2                   	0xD2        // AUTO Manual Mode Setting
#define _P8_MODE_DET_STATUS_D3             		0xD3        // Mode Detect Status 
#define _P8_STA_AND_DIS_MODE_D4          		0xD4        // Statistc and Disable Mode
#define _P8_PREFER_MODE_D5                   	0xD5        // Prefer Mode
#define _P8_STM_FIX_MODE_D6                  	0xD6        // State Machine Fix mode
#define _P8_ZORAN_REG_EN_D7                  	0xD7        // Zoran Register Enable
#define _P8_AUTO_MODE_STM_STA_D8       			0xD8        // AUTO Mode State Machine Statistic
//#define _RESERVED_D9                       	0xD9        // P8 Reserved D9 
#define _P8_COMB_FLT_CONF_DA                 	0xDA        // COMB Filter Config
#define _P8_COMB_FLT_TH1_DB                  	0xDB        // COMB Filter Threshold 1
#define _P8_COMB_FLT_TH2_DC                  	0xDC        // COMB Filter Threshold 2
#define _P8_COMB_FLT_TH3_DD                  	0xDD        // COMB Filter Threshold 3
#define _P8_COMB_FLT_TH4_DE                  	0xDE        // COMB Filter Threshold 4
//#define _RESERVED_DF                       	0xDF        // P8 Reserved DF
#define _P8_YCSEP_CTRL_E0                    	0xE0        // YC Seperate Control
#define _P8_BPF_BW_SEL_Y_E1                  	0xE1        // BPF BandWidth Select Y
#define _P8_BPF_BW_SEL_C_E2                  	0xE2        // BPF BandWidth Select C
#define _P8_ADAP_BPF_C_TH1_E3                	0xE3        // Chroma Adaptive BPF Detection Threshold 1
#define _P8_ADAP_BPF_C_TH2_E4                	0xE4        // Chroma Adaptive BPF Detection Threshold 2
#define _P8_ADAP_BPF_C_TH3_E5                	0xE5        // Chroma Adaptive BPF Detection Threshold 3
#define _P8_ADAP_BPF_C_TH4_E6                	0xE6        // Chroma Adaptive BPF Detection Threshold 4
#define _P8_ADAP_BPF_Y_TH1_E7                	0xE7        // Threshold 1 for Y Adaptive BPF detection 
#define _P8_ADAP_BPF_Y_TH2_E8                	0xE8        // Threshold 2 for Y Adaptive BPF detection
#define _P8_ADAP_BPF_Y_TH3_E9                	0xE9        // Threshold 3 for Y Adaptive BPF detection
#define _P8_YC_BW_CTRL_EA                    	0xEA        // YC BandWidth Control
#define _P8_2D_DEBUG_MODE_EB                 	0xEB        // 2D Debug Mode
#define _P8_RESOL_LP_TH_EC                   	0xEC        // RESOL LP TH
#define _P8_ENVELOPE_TH_ED                   	0xED        // ENVELOPE TH
#define _P8_COMB_FLT_TH5_EE                		0xEE        // Comb Filter THR5             
//#define _RESERVED_EF                       	0xEF        // P8 Reserved EF
#define _P8_BW_DETECTION_F0                  	0xF0        // Band Width Detection
#define _P8_BW_EDGE_THR_F1                   	0xF1        // Band Width Edge Threshold
#define _P8_2D_ALPHA_MOD_ENABLE_F2   			0xF2        // 2D ALPHA Mode Enable 
#define _P8_H2V_CORING_THR_F3               	0xF3        // H2V Coring Threshold
#define _P8_H2V_Y_NOISE_THR_F4             		0xF4        // H2V Y Noise Threshold
#define _P8_H2V_CVBS_NOISE_THR_F5       		0xF5        // H2V CVBS Noise Threshold
#define _P8_1D_BLEND_THR_F6                  	0xF6        // 1D Blend Threshold 
#define _P8_1D_BLEND_BPF_SEL_Y_F7       		0xF7        // 1D Blend BPF Select for Y
#define _P8_1D_BLEND_BPF_SEL_C_F8       		0xF8        // 1D Blend BPF Select for C
											 			 
//Address: P8-F9 ~ P8-FF Reserved			 

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////   Page 9: VD  /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

#define _P9_AGC_PEAK_NOM_A0                  	0xA0        //AGC Peak Nominal
#define _P9_AGC_PEAK_GATE_CTRL_A1       		0xA1        //AGC Peak and Gate Control
#define _P9_AGC_PEAK_CTRL_A2                 	0xA2        //AGC Peak Control
#define _P9_VIDEO_CTRL2_A3                   	0xA3        //Video Control
#define _P9_LUMA_AGC_VALUE_A4               	0xA4        //Luma AGC Value
#define _P9_AGC_GATE_STA_M_A5               	0xA5        //Rough Gate Generator MSB
#define _P9_AGC_GATE_STA_L_A6                	0xA6        //Rough Gate Generator LSB
#define _P9_AGC_GATE_WID_A7                  	0xA7        //Rough Gate Width
#define _P9_AGC_BP_DELAY_A8                  	0xA8        //Sync Tip To Backproch Delay
#define _P9_CLAMP_COMP_NEW_TH2_A9    			0xA9        //ClampAGC CompLuma Threshold2
#define _P9_CLAMP_COMP_NEW_TH1_AA    			0xAA        //ClampAGC CompLuma Threshold1
#define _P9_CLAMP_COMP_NEW_CTRL_AB  			0xAB        //ClampAGC CompLuma New Control
#define _P9_VS_AGC_MIN_AC                    	0xAC        //Vsync AGC minimun
#define _P9_VS_AGC_LOCK_END_AD            		0xAD        //Vsync AGC LockOut End
#define _RESERVED_AE                         	0xAE        //P9 Reserved AE
#define _RESERVED_AF                         	0xAF        //P9 Reserved AF
#define _P9_CPUMP_DLY_CTRL_B0               	0xB0        //Charge Pump Delay Control
#define _P9_CPUMP_ADJ_B1                     	0xB1        //Charge Pump Delay Adjustment
#define _P9_CPUMP_DELAY_B2                   	0xB2        //Charge Pump Delay
#define _RESERVED_B3                         	0xB3        //P9 Reserved B3
#define _P9_CAGC_B4                          	0xB4        //Chrona AGC 
#define _P9_CKILL_B5                         	0xB5        //Chroma Kill
#define _P9_C_LOCK_CONF_B6                   	0xB6        //Chroma Lock Configuation
#define _P9_CLOOP_GAIN_B7                    	0xB7        //Chroma LoopFilter Gain
#define _P9_CLOOP_STATE_B8                   	0xB8        //Chroma LoopFilter State
#define _P9_CAUTOPOS_B9                      	0xB9        //Chroma AutoPosition
//Address: P9-BA ~ P9-BF Reserved  			  
#define _P9_LOCK_COUNT_C0                    	0xC0        //Lock Count
#define _P9_HLOOP_MAXSTATE_C1               	0xC1        //H Loop MaxState
#define _P9_CLAMP_CTRL0_C2                   	0xC2        //ClampAGC Control 0
#define _P9_CLAMP_NEWSYNC_STA_C3       			0xC3        //ClampAGC New Coarse Sync Start Position
#define _P9_CLAMP_NEWSYNC_END_C4      			0xC4        //ClampAGC New Coarse Sync End Position
#define _P9_CLAMP_NEWBP_STA_C5            		0xC5        //ClampAGC New Coarse Back Porch Start Position
#define _P9_CLAMP_NEWBP_END_C6           		0xC6        //ClampAGC New Coarse Back Porch End Position
#define _P9_HDET_PHASE_SEL_C7                	0xC7        //H Detect Phase Select
#define _P9_HDET_CNT_TIP_STA_C8           		0xC8        //H Detect Counter Tip Start
#define _P9_HDET_CNT_TIP_END_C9            		0xC9        //H Detect Counter Tip End
#define _P9_HDET_CNT_BP_STA_CA            		0xCA        //H Detect Counter Back Porch Start
#define _P9_HDET_CNT_BP_END_CB            		0xCB        //H Detect Counter Back Porch End
#define _P9_HPLL_INT_CTRL_CC                 	0xCC        //HPLL Integral Ctrl
#define _P9_HPHASE_ERR_STATUS_H_CD    			0xCD        //H Detect Phase Error Status High Byte
#define _P9_HPHASE_ERR_STATUS_L_CE     			0xCE        //H Detect Phase Error Status Low Byte
#define _RESERVED_CF                         	0xCF        //P9 Reserved CF
#define _P9_HS_RISING_D0                     	0xD0        //Hsync Rising Position
#define _P9_HS_PHASE_OFFSET_D1             		0xD1        //Hsync Phase Offset
#define _P9_HS_GATE_STA_D2                   	0xD2        //Hsync Gate Detect Window Start
#define _P9_HS_GATE_END_D3                   	0xD3        //Hsync Gate Detect Window End
#define _P9_HS_TIP_STA_D4                    	0xD4        //Hsync Tip Detect Window Start
#define _P9_HS_TIP_END_D5                    	0xD5        //Hsync Tip Detect Window End
#define _P9_HS_RISING_STA_D6                 	0xD6        //Hsync Rising Detect Window Start
#define _P9_HS_RISING_END_D7                 	0xD7        //Hsync rising Detect Window End
#define _P9_BP_START_D8                      	0xD8        //BackPorch Detect Window Start
#define _P9_BP_END_D9                        	0xD9        //BackPorch Detect Window End
#define _P9_HBLANK_STA_DA                    	0xDA        //Hblank Window Start
#define _P9_HBLANK_END_DB                    	0xDB        //Hblank Window End
#define _P9_BURST_GATE_STA_DC                	0xDC        //Burst Gate Window Start
#define _P9_BURST_GATE_END_DD               	0xDD        //Burst Gate Window End
#define _P9_HACT_STA_DE                      	0xDE        //Hactive Start
#define _P9_HACT_WID_DF                      	0xDF        //Hactive Width
#define _P9_VACT_STA_E0                      	0xE0        //Vactive Start
#define _P9_VACT_HEIGHT_E1                   	0xE1        //Vactive Height
#define _P9_VS_H_MIN_E2                      	0xE2        //HalfLine After Vsync Detect Max
#define _P9_VS_H_MAX_E3                      	0xE3        //HalfLine After Vsync Detect Min
#define _P9_VS_VBI_MIN_E4                    	0xE4        //HalfLine After Vsync Detect Min When VBI Data is vaild
#define _P9_VS_VBI_LOCK_END_E5              	0xE5        //VBI LockOut End
#define _P9_VS_CTRL_E6                       	0xE6        //Vsync Control
#define _P9_VS_TC_E7                         	0xE7        //Vsync Time Constant
#define _P9_VS_TC2_E8                        	0xE8        //Vsync Time Constant 2
#define _P9_VS_TC1_E9                        	0xE9        //Vsync Time Constant 1
#define _P9_SERR_TH_EA                       	0xEA        //Serration Detection Threshold
#define _P9_NO_SINGAL_DEC_EB                 	0xEB        //No Singal Counter Decrement Value
//Address: P9-EC ~ P9-EF Reserved  		    
#define _P9_CDTO_INC4_F0                     	0xF0        //Chroma DTO INC4
#define _P9_CDTO_INC3_F1                     	0xF1        //Chroma DTO INC3
#define _P9_CDTO_INC2_F2                     	0xF2        //Chroma DTO INC2
#define _P9_CDTO_INC1_F3                     	0xF3        //Chroma DTO INC1
#define _P9_HDTO_INC4_F4                     	0xF4        //Hsync  DTO INC4
#define _P9_HDTO_INC3_F5                     	0xF5        //Hsync  DTO INC3
#define _P9_HDTO_INC2_F6                     	0xF6        //Hsync  DTO INC2
#define _P9_HDTO_INC1_F7                     	0xF7        //Hsync  DTO INC1
//Address: P9-F8 ~ P9-FF Reserved  			 											 
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////   Page A: VD  /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

#define _PA_AUTO_MODE_TB1_A0                 	0xA0        //AutoMode Table 0
#define _PA_AUTO_MODE_TB2_A1                	0xA1        //AutoMode Table 1
#define _PA_AUTO_MODE_TB3_A2                 	0xA2        //AutoMode Table 2
#define _PA_AUTO_MODE_TB4_A3                 	0xA3        //AutoMode Table 3
#define _PA_AUTO_MODE_TB5_A4                 	0xA4        //AutoMode Table 4
#define _PA_AUTO_MODE_TB6_A5                 	0xA5        //AutoMode Table 5
#define _PA_AUTO_MODE_TB7_A6                 	0xA6        //AutoMode Table 6
#define _PA_AUTO_MODE_TB8_A7                 	0xA7        //AutoMode Table 7
#define _PA_AUTO_MODE_TB9_A8                 	0xA8        //AutoMode Table 8
#define _PA_625_FLAG_CNT_A9                  	0xA9        //625 Flag Counter
#define _PA_443_FLAG_CNT_AA                  	0xAA        //443 Flag Counter
#define _PA_SECAM_FLAG_CNT_AB                	0xAB        //SECAM Flag Counter
#define _PA_PALM_FLAG_CNT_AC                 	0xAC        //PALM Flag Counter
#define _PA_BURST_VLD_CNT_AD                 	0xAD        //Burst Magnitude not Vaild Counter
//Address: PA-AE ~ PA-AF Reserved  
#define _PA_MIDPT_ADJ_B0                     	0xB0        //MidPoint adjustment
#define _PA_FREQ_FLAG_TH_B1                  	0xB1        //Frequence Flag Threshold
#define _PA_FREQ_VLD_MAX_B2                  	0xB2        //Frequence Valid Max
#define _PA_FREQ_VLD_INNER_B3                	0xB3        //Frequence Valid Inner
#define _PA_FREQ_VLD_MIN_B4                  	0xB4        //Frequence Valid Min
#define _PA_SECAM_FLAG_CNT_MAX_B5      			0xB5        //SECAM Flag Counter Max
#define _PA_SECAM_FLAG_CNT_MIN_B6      			0xB6        //SECAM Flag Counter Min
#define _PA_PALM_FLAG_PHASE_B7             		0xB7        //PALM Flag Phase
#define _PA_BURST_LOW_LIMIT_B8             		0xB8        //Burst Low Limit
#define _PA_BURST_MAG_CHOICE_B9           		0xB9        //Burst Magnitude Choice
#define _PA_BURST_MAG_STATUS_BA           		0xBA        //Burst Magnitude Status
#define _PA_FIFO_CTRL_BB                     	0xBB        //FIFO control
#define _PA_FIFO_STATUS_BC                   	0xBC        //FIFO Status
#define _PA_I_GAIN_CTRL_BD                   	0xBD        //I-Gain Control
#define _PA_MISC_CTRL_BE                     	0xBE        //Misc Control
#define _PA_FIFO_DEP_MIN_BF                 	0xBF        //FIFO Depth Min Status
#define _PA_FIFO_DEP_MAX_C0                  	0xC0        //FIFO Depth Max Status
#define _PA_HSYNC_PULSE_STA_C1             		0xC1        //Hsync Start Position
#define _PA_HSYNC_PULSE_WID_C2            		0xC2        //Hsync Width
#define _PA_CRESAMP_CTRL_C3                  	0xC3        //Chroma Hresampler Control
#define _PA_SECAM_CTRL_C4                    	0xC4        //SECAM Control
#define _PA_SECAM_DR_OFFSET_C5             		0xC5        //SECAM DR Offset 
#define _PA_SECAM_DB_OFFSET_C6             		0xC6        //SECAM DB Offset
#define _PA_SECAM_HCOUNT_RST_C7          		0xC7        //Hcount Reset
#define _PA_PHASE_DIFF_DR_RST_C8          		0xC8        //Secam DR's Phase Diff from Cordic reset value
#define _PA_PHASE_DIFF_DB_RST_C9          		0xC9        //Secam DB's Phase Diff from Cordic reset value
#define _PA_DRDB_GAIN_TB_CA                  	0xCA        //Secam Gain DrDb Look Up Table 
#define _PA_Y_GAIN_TB_CB                     	0xCB        //Secam Gain Y Look Up Table 
#define _PA_SECAM_GAIN_DLY_CC               	0xCC        //Secam Y Delay For dr/db gain
#define _PA_SECAM_GAIN_TB_DBG_CD        		0xCD        //SECAM Gain Table Debug
//Address: PA-CE ~ PA-CF Reserved  
#define _PA_LDPAUSE_CTL_D0                   	0xD0        //LD pause detected
#define _PA_VCR_OPT_D1                       	0xD1        //VCR Option
#define _PA_CEN_LINE_COUNT_D2                	0xD2        //Cenable Line Count
#define _PA_MEAS_1ST_V_HI_D3                 	0xD3        //Measure First V HI
#define _PA_MEAS_1ST_V_LOW_D4              		0xD4        //Measure First V LOW
#define _PA_MEAS_2ND_V_HI_D5                 	0xD5        //Measure Second V HI
#define _PA_MEAS_2ND_V_LOW_D6             		0xD6        //Measure Second V LOW
#define _PA_PORCH_HEIGHT_M_D7               	0xD7        //Porch Height Measurement MSB
#define _PA_PORCH_HEIGHT_L_D8               	0xD8        //Porch Height Measurement LSB
#define _PA_SINGAL_STM_CTL_D9                	0xD9        //Singal STM Conttrol
#define _PA_CDET_PHASE_ERR2_DA              	0xDA        //Chroma Detect Phase Error 2
#define _PA_CDET_PHASE_ERR1_DB              	0xDB        //Chroma Detect Phase Error 1
#define _PA_MV_DET_WIN_DC                    	0xDC        //MacroVision Detect Window
#define _PA_MV_BURST_STA_DD                  	0xDD        //MacroVision Burst Detect Window Start
#define _PA_MV_BURST_END_DE                  	0xDE        //MacroVision Burst Detect Window End
#define _PA_COLORSTRIPE_CTRL_DF            		0xDF        //ColorStripe Control
#define _PA_DBG_MUX_E0                       	0xE0        //Debug Mux
#define _PA_VD_DBG_ANALOG_E1                 	0xE1        //Video Debug Analog 
#define _PA_VD_DBG_DIGITAL_E2                	0xE2        //Video Debug Digital 
#define _PA_BIST_TEST1_E3                    	0xE3        //BIST Test 1
#define _PA_BIST_TEST2_E4                    	0xE4        //BIST Test 2
#define _RESERVED_E5                         	0xE5        //PA Reserved E5
#define _PA_PATTERN_CTRL_E6                  	0xE6        //Pattern Control
#define _PA_CRC_RLT2_E7                      	0xE7        //CRC Result 2
#define _PA_CRC_RLT1_E8                      	0xE8        //CRC Result 1
#define _PA_CRC_RLT0_E9                      	0xE9        //CRC Result 0
#define _RESERVED_EA                         	0xEA        //PA Reserved EA
#define _RESERVED_EB                         	0xEB        //PA Reserved EB
#define _PA_FPGA_TEST1_EC                    	0xEC        //FPGA Test1
#define _PA_FPGA_TEST2_ED                    	0xED        //FPGA Test2
#define _PA_FPGA_TEST3_EE                    	0xEE        //FPGA Test3
#define _PA_FPGA_TEST4_EF                    	0xEF        //FPGA Test4
#define _PA_CLAMP_TEST0_F0                   	0xF0        //Clamp Test Reg 0
#define _PA_CLAMP_TEST1_F1                   	0xF1        //Clamp Test Reg 1
#define _PA_CLAMP_TEST6_F2                   	0xF2        //Clamp Test Reg 6
#define _PA_CLAMP_TEST7_F3                   	0xF3        //Clamp Test Reg 7
#define _PA_CLAMP_TEST8_F4                   	0xF4        //Clamp Test Reg 8
#define _PA_CLAMP_TEST9_F5                   	0xF5        //Clamp Test Reg 9
#define _PA_CLAMP_TEST10_F6                  	0xF6        //Clamp Test Reg 10
#define _PA_CLAMP_TEST11_F7                  	0xF7        //Clamp Test Reg 11
#define _PA_CLAMP_TEST12_F8                  	0xF8        //Clamp Test Reg 12
#define _PA_CLAMP_TEST13_F9                  	0xF9        //Clamp Test Reg 13
#define _PA_CLAMP_TEST17_FA                  	0xFA        //Clamp Test Reg 17
#define _RESERVED_FB                         	0xFB        //PA Reserved FB
#define _RESERVED_FC                         	0xFC        //PA Reserved FC
#define _RESERVED_FD                         	0xFD        //PA Reserved FD
#define _PA_CHIP_VER1_FE                     	0xFE        //Chip Version MSB
#define _PA_CHIP_VER2_FF                     	0xFF        //Chip Version LSB

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////   Page B: Off Line Sync Processor & Auto SOY  /////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------
// Off Line Sync Processor
//--------------------------------------------------
#define _PB_SYNC_SELECT_A0                  	0xA0        // Sync Select Control Register
#define _PB_SYNC_INVERT_A1                  	0xA1        // Sync Invert Control Register
#define _PB_SYNC_CTRL_A2                    	0xA2        // Sync Processor Control Register
#define _PB_STABLE_HIGH_PERIOD_H_A3       		0xA3        // Stable High Period HByte
#define _PB_STABLE_HIGH_PERIOD_L_A4         	0xA4        // Stable High Period LByte
#define _PB_VSYNC_COUNTER_LEVEL_MSB_A5   		0xA5        // Vertical Sync Counter Level MSB
#define _PB_VSYNC_COUNTER_LEVEL_LSB_A6      	0xA6        // Vertical Sync Counter Level LSB
#define _PB_HSYNC_TYPE_DETECTION_FLAG_A7   		0xA7        // Hsync Type Detection Flag
#define _PB_STABLE_MEASURE_A8               	0xA8        // Stable Measure
#define _PB_STABLE_PERIOD_H_A9              	0xA9        // Stable Period HByte
#define _PB_STABLE_PERIOD_L_AA              	0xAA        // Stable Period LByte
#define _PB_MEAS_HS_PERIOD_H_AB             	0xAB        // HSync Period Measured Result HByte
#define _PB_MEAS_HS_PERIOD_L_AC             	0xAC        // HSync Period Measured Result LByte
#define _PB_MEAS_VS_PERIOD_H_AD             	0xAD        // VSync Period Measured Result HByte
#define _PB_MEAS_VS_PERIOD_L_AE             	0xAE        // VSync Period Measured Result LByte
#define _PB_MEAS_HS_VS_HIGH_PERIOD_H_AF     	0xAF        // HSync and VSync High Period Measured Results HByte
#define _PB_MEAS_HS_VS_HIGH_PERIOD_L_B0     	0xB0        // HSync and VSync High Period Measured Results LByte
#define _PB_MEAS_HS_VS_HI_SEL_B1            	0xB1        // HSync and VSync High Period Measured Select
//#define _PB_RESERVED_B2                     					0xB2        // PB Reserved B2
#define _PB_SYNC_TEST_MISC_B3               	0xB3        // Sync Test MISC Register
#define _PB_G_CLAMP_START_B4                	0xB4        // Clamp Signal Output Start of G Channel
#define _PB_G_CLAMP_END_B5                  	0xB5        // Clamp Signal Output End of G Channel
#define _PB_BR_CLAMP_START_B6               	0xB6        // Clamp Signal Output Start of R/B Channel
#define _PB_BR_CLAMP_END_B7                 	0xB7        // Clamp Signal Output End of R/B Channel
#define _PB_CLAMP_CTRL0_B8                  	0xB8        // Clamp Signal Control Register 0
#define _PB_CLAMP_CTRL1_B9                  	0xB9        // Clamp Signal Control Register 1
#define _PB_CLAMP_CTRL2_BA                  	0xBA        // Clamp Signal Control Register 2
#define _PB_CLAMP_CTRL3_BB                  	0xBB        // Clamp Signal Control Register 3
#define _PB_COAST_CTRL_BC                   	0xBC        // Coast Control Register
#define _PB_CAPTURE_WINDOW_SETTING_BD       	0xBD        // Capture Window Setting
#define _PB_DETECT_TOLERANCE_SETTING_BE     	0xBE        // Detection Tolerance Setting
#define _PB_SKIP_LINE_CTRL_BF               	0xBF        // Skip Line Control Register
#define _PB_SOYCH0_CFG3_C3						0xC3//eric 20070530

#endif

//--------------------------------------------------
// Dynamic Contrast Control(Port)
//--------------------------------------------------
#define _DCC_CTRL0_E4                       	0xE4        // DCC Control Register0
#define _DCC_CTRL1_E5                       	0xE5        // DCC Control Register1
#define _DCC_ACCESS_PORT_E6                		0xE6        // DCC Access Port
#define _DCC_DATA_PORT_E7                   	0xE7        // DCC Data Port
//Address: E8~EF Reserved

//--------------------------------------------------
// CMDI(Port)
//--------------------------------------------------
#define _CMDI_ACCESS_PORT_F0                	0xF0        // CMDI Access Port
#define _CMDI_DATA_PORT_F1                  	0xF1        // CMDI Data Port

//--------------------------------------------------
// Cyclic Redundant Check(CRC)
//--------------------------------------------------
//#define _OP_CRC_CTRL_F2                     	0xF2        // Output CRC Control Register
//#define _OP_CRC_CHECKSUM_F3                 	0xF3        // Output CRC Checksum

//--------------------------------------------------
// DDC Special Function Access(DDC/CI)
//--------------------------------------------------
#define _DDC_SET_SLAVE_F4                   	0xF4        // DDC Set Slave Address
#define _DDC_SUB_IN_F5                      	0xF5        // DDC Sub Address Received
#define _DDC_DATA_IN_F6                     	0xF6        // DDC Data Received
#define _DDC_CTRL_F7                        	0xF7        // DDC Control Register
#define _DDC_STATUS_F8                      	0xF8        // DDC Status
#define _DDC_IRQ_CTRL_F9                    	0xF9        // DDC IRQ Control Register

//--------------------------------------------------
// DDC Channel (ADC/DVI)
//--------------------------------------------------
#define _DDC_ENABLE_FA                      	0xFA        // DDC Channel Enable Control Register
#define _DDC_INDEX_FB                       	0xFB        // DDC SRAM R/W Index Register
#define _DDC_ACCESS_PORT_FC                 	0xFC        // DDC Channel Access Port
#define _DDC_DVI_ENABLE_FD                  	0xFD        // DDC DVI Channel Enable Control Register
#define _DDC_DVI_INDEX_FE                   	0xFE        // DDC DVI SRAM R/W Index Register
#define _DDC_DVI_ACCESS_PORT_FF           		0xFF        // DDC DVI Channel Access Port

//-----------------------------------------------------------------------------------------
// PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT
// PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT
// PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT
// PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT
// PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT
//-----------------------------------------------------------------------------------------

//--------------------------------------------------
// Scale Down Port
//--------------------------------------------------
//#define _SD_V_SCALE_INIT_00                 	0x00        // Vertical Scale Down Initial Select
//#define _SD_V_SCALE_FACTOR_H_01            	0x01        // Vertical Scale Down Factor HByte
//#define _SD_V_SCALE_FACTOR_M_02            	0x02        // Vertical Scale Down Factor MByte
//#define _SD_V_SCALE_FACTOR_L_03             	0x03        // Vertical Scale Down Factor LByte
//#define _SD_H_SCALE_INIT_04                 	0x04        // Horizontal Scale Down Initial Select
//#define _SD_H_SCALE_FACTOR_H_05            	0x05        // Horizontal Scale Down Factor HByte
//#define _SD_H_SCALE_FACTOR_M_06            	0x06        // Horizontal Scale Down Factor MByte
//#define _SD_H_SCALE_FACTOR_L_07            	0x07        // Horizontal Scale Down Factor LByte
//#define _SD_H_SCALE_ACCH_08                 	0x08        // Horizontal Scale Down Accumulated Factor HByte
//#define _SD_H_SCALE_ACCL_09                 	0x09        // Horizontal Scale Down Accumulated Factor LByte
//#define _SD_ACC_WIDTHH_0A                   	0x0A        // Horizontal Scale Down Accumulated Width HByte
//#define _SD_ACC_WIDTHL_0B                   	0x0B        // Horizontal Scale Down Accumulated Width LByte
//#define _SD_FLAT_WIDTHH_0C                  	0x0C        // Horizontal Scale Down Flat Width HByte
//#define _SD_FLAT_WIDTHL_0D                  	0x0D        // Horizontal Scale Down Flat Width LByte
//Address: 25-0E~25-0F Reserved
//#define _SD_INPUT_PAT_GEN_CTRL0_10       		0x10        // Input Pattern Generator Control Register0
//#define _SD_INPUT_PAT_GEN_CTRL1_11       		0x11        // Input Pattern Generator Control Register1
//#define _SD_INPUT_PAT_GEN_RED_12           	0x12        // Input Pattern Generator RED Initial Value
//#define _SD_INPUT_PAT_GEN_GREEN_13       		0x13        // Input Pattern Generator GREEN Initial Value
//#define _SD_INPUT_PAT_GEN_BLUE_14          	0x14        // Input Pattern Generator BLUE Initial Value

//--------------------------------------------------
// Display Format Port
//--------------------------------------------------
#define _DISP_DH_TOTAL_H_00                 	0x00        // Display Horizontal Total Pixels HByte
#define _DISP_DH_TOTAL_L_01                 	0x01        // Display Horizontal Total Pixels LByte
#define _DISP_DHS_END_02                    	0x02        // Display Horizontal Sync End Pixels
#define _DISP_DH_BKGD_STA_H_03            		0x03        // Display Horizontal Background Start HByte
#define _DISP_DH_BKGD_STA_L_04           		0x04        // Display Horizontal Background Start LByte
#define _DISP_DH_ACT_STA_H_05               	0x05        // Display Horizontal Active Start HByte
#define _DISP_DH_ACT_STA_L_06               	0x06        // Display Horizontal Active Start LByte
#define _DISP_DH_ACT_END_H_07          			0x07        // Display Horizontal Active End HByte
#define _DISP_DH_ACT_END_L_08               	0x08        // Display Horizontal Active End LByte
#define _DISP_DH_BKGD_END_H_09        			0x09        // Display Horizontal Background End HByte
#define _DISP_DH_BKGD_END_L_0A        			0x0A        // Display Horizontal Background End LByte
#define _DISP_DV_TOTAL_H_0B                 	0x0B        // Display Vertical Total Lines HByte
#define _DISP_DV_TOTAL_L_0C                 	0x0C        // Display Vertical Total Lines LByte
#define _DISP_DVS_END_0D                    	0x0D        // Display Vertical Sync End Lines
#define _DISP_DV_BKGD_STA_H_0E       			0x0E        // Display Vertical Background Start HByte
#define _DISP_DV_BKGD_STA_L_0F       			0x0F        // Display Vertical Background Start LByte
#define _DISP_DV_ACT_STA_H_10               	0x10        // Display Vertical Active Start HByte
#define _DISP_DV_ACT_STA_L_11               	0x11        // Display Vertical Active Start LByte
#define _DISP_DV_ACT_END_H_12               	0x12        // Display Vertical Active End HByte
#define _DISP_DV_ACT_END_L_13               	0x13        // Display Vertical Active End LByte
#define _DISP_DV_BKGD_END_H_14      			0x14        // Display Vertical Background End HByte
#define _DISP_DV_BKGD_END_L_15       			0x15        // Display Vertical Background End LByte
//Address: 2B-16~2B-1F Reserved
#define _DISP_TIMING_20                     	0x20        // Display Clock Fine Tuning Register
#define _DISP_OSD_REFERENCE_DEN_21 				0x21        // Position Of Reference DEN for OSD
#define _DISP_NEW_DV_CTRL_22                	0x22        // New DV Control Register
#define _DISP_NEW_DV_DLY_23                 	0x23        // New DV Delay

//--------------------------------------------------
// FIFO Window Port
//--------------------------------------------------
#define _FIFO_DWRWL_H_BSU_00                	0x00        // Display Window Read Width/Length HByte Before Scaling Up
#define _FIFO_DWRW_L_BSU_01                 	0x01        // Display Window Read Width LByte Before Scaling Up
#define _FIFO_DWRL_L_BSU_02                 	0x02        // Display Window Read Length LByte Before Scaling Up
//Address: 31-03~31-0F Reserved
//#define _FIFO_DWRWL_H_ASD_10                	0x10        // Display Window Read Width/Length HByte After Scaling Down
//#define _FIFO_DWRW_L_ASD_11                 	0x11        // Display Window Read Width LByte After Scaling Down
//#define _FIFO_DWRL_L_ASD_12                 	0x12        // Display Window Read Length LByte After Scaling Down

//--------------------------------------------------
// Scale Up Port
//--------------------------------------------------
//#define _SU_H_SCALE_FACTOR_H_00             	0x00        // Horizontal Scale Up Factor HByte
//#define _SU_H_SCALE_FACTOR_M_01             	0x01        // Horizontal Scale Up Factor MByte
//#define _SU_H_SCALE_FACTOR_L_02             	0x02        // Horizontal Scale Up Factor LByte
//#define _SU_V_SCALE_FACTOR_H_03             	0x03        // Vertical Scale Up Factor HByte
//#define _SU_V_SCALE_FACTOR_M_04             	0x04        // Vertical Scale Up Factor MByte
//#define _SU_V_SCALE_FACTOR_L_05             	0x05        // Vertical Scale Up Factor LByte
//#define _SU_H_SF_SEGMENT_1PIXEL_H_06       	0x06        // Horizontal Scale Up Factor Segment 1 Pixel HByte
//#define _SU_H_SF_SEGMENT_1PIXEL_L_07       	0x07        // Horizontal Scale Up Factor Segment 1 Pixel LByte
//#define _SU_H_SF_SEGMENT_2PIXEL_H_08       	0x08        // Horizontal Scale Up Factor Segment 2 Pixel HByte
//#define _SU_H_SF_SEGMENT_2PIXEL_L_09       	0x09        // Horizontal Scale Up Factor Segment 2 Pixel LByte
//#define _SU_H_SF_SEGMENT_3PIXEL_H_0A       	0x0A        // Horizontal Scale Up Factor Segment 3 Pixel HByte
//#define _SU_H_SF_SEGMENT_3PIXEL_L_0B       	0x0B        // Horizontal Scale Up Factor Segment 3 Pixel LByte
//#define _SU_H_SF_DELTA_1PIXEL_H_0C          	0x0C        // Horizontal Scale Up Factor DELTA 1 Pixel HByte
//#define _SU_H_SF_DELTA_1PIXEL_L_0D          	0x0D        // Horizontal Scale Up Factor DELTA 1 Pixel LByte
//#define _SU_H_SF_DELTA_2PIXEL_H_0E          	0x0E        // Horizontal Scale Up Factor DELTA 2 Pixel HByte
//#define _SU_H_SF_DELTA_2PIXEL_L_0F          	0x0F        // Horizontal Scale Up Factor DELTA 2 Pixel LByte
//#define _SU_H_COEF_INI_VALUE_10             	0x10        // Accumulate Horizontal Filter Coefficient Initial Value
//#define _SU_V_COEF_INI_VALUE_11             	0x11        // Accumulate Vertical Filter Coefficient Initial value


#if(_SCALER_TYPE == _RTD3580D)
//--------------------------------------------------
// Sync Processor Port
//--------------------------------------------------
#define _SYNC_G_CLAMP_START_00              	0x00        // G/Y Channle Clamp Signal Output Start
#define _SYNC_G_CLAMP_END_01                	0x01        // G/Y Channle Clamp Signal Output End
#define _SYNC_BR_CLAMP_START_02           		0x02        // B/Pb & R/Pr Channle Clamp Signal Output Start
#define _SYNC_BR_CLAMP_END_03               	0x03        // B/Pb & R/Pr Channle Clamp Signal Output End
#define _SYNC_CLAMP_CTRL0_04                	0x04        // Clamp Signal Control Register 0
#define _SYNC_CLAMP_CTRL1_05                	0x05        // Clamp Signal Control Register 1
#define _SYNC_CLAMP_CTRL2_06                	0x06        // Clamp Signal Control Register 2
#define _SYNC_CAPTURE_WINDOW_SET_07    			0x07        // Capture Window Setting
#define _SYNC_DETECT_TOLERANCE_SET_08   		0x08        // Detection Tolerance Setting
//Address: 5D-08~5D-0F Reserved
#define _SYNC_MACRO_VISION_CTRL_10       		0x10        // Macro Vision Control Register
#define _SYNC_MV_START_LINE_EVEN_11      		0x11        // Macro Vision Start Line in Even Field
#define _SYNC_MV_END_LINE_EVEN_12           	0x12        // Macro Vision End Line in Even Field
#define _SYNC_MV_START_LINE_ODD_13        		0x13        // Macro Vision Start Line in Odd Field
#define _SYNC_MV_END_LINE_ODD_14            	0x14        // Macro Vision End Line in Odd Field
#else
//--------------------------------------------------
// Sync Processor Port
//--------------------------------------------------
#define _SYNC_G_CLAMP_START_00              	0x00        // G/Y Channle Clamp Signal Output Start
#define _SYNC_G_CLAMP_END_01                	0x01        // G/Y Channle Clamp Signal Output End
#define _SYNC_BR_CLAMP_START_02             	0x02        // B/Pb & R/Pr Channle Clamp Signal Output Start
#define _SYNC_BR_CLAMP_END_03               	0x03        // B/Pb & R/Pr Channle Clamp Signal Output End
#define _SYNC_CLAMP_CTRL0_04                	0x04        // Clamp Signal Control Register 0
#define _SYNC_CLAMP_CTRL1_05                	0x05        // Clamp Signal Control Register 1
//#define _SYNC_CAPTURE_WINDOW_SETTING_06     	0x06        // Capture Window Setting
//#define _SYNC_COAST_CTRL_07                 	0x07        // COAST Control Register
//Address: 5D-08~5D-0F Reserved
#define _SYNC_MACRO_VISION_CTRL_10       		0x10        // Macro Vision Control Register
#define _SYNC_MV_START_LINE_EVEN_11       		0x11        // Macro Vision Start Line in Even Field
#define _SYNC_MV_END_LINE_EVEN_12           	0x12        // Macro Vision End Line in Even Field
#define _SYNC_MV_START_LINE_ODD_13        		0x13        // Macro Vision Start Line in Odd Field
#define _SYNC_MV_END_LINE_ODD_14            	0x14        // Macro Vision End Line in Odd Field
#endif

//--------------------------------------------------
// Hightlight Window Port
//--------------------------------------------------
//#define _HW_H_START_H_00                    	0x00        // Highlight Window Horizontal Start HByte
//#define _HW_H_START_L_01                    	0x01        // Highlight Window Horizontal Start LByte
//#define _HW_H_END_H_02                      	0x02        // Highlight Window Horizontal End HByte
//#define _HW_H_END_L_03                      	0x03        // Highlight Window Horizontal End LByte
//#define _HW_V_START_H_04                    	0x04        // Highlight Window Vertical Start HByte
//#define _HW_V_START_L_05                    	0x05        // Highlight Window Vertical Start LByte
//#define _HW_V_END_H_06                      	0x06        // Highlight Window Vertical End HByte
//#define _HW_V_END_L_07                      	0x07        // Highlight Window Vertical End LByte
//#define _HW_BORDER_WIDTH_08                 	0x08        // Highlight Window Border Width
//#define _HW_BORDER_COLOR_R_09               	0x09        // Highlight Window Border Red Color MSB 6bit (Red Color 2-bit LSB = 00)
//#define _HW_BORDER_COLOR_G_0A               	0x0A        // Highlight Window Border Green Color MSB 6bit (Red Color 2-bit LSB = 00)
//#define _HW_BORDER_COLOR_B_0B               	0x0B        // Highlight Window Border Blue Color MSB 6bit (Red Color 2-bit LSB = 00)
#define _HW_WINDOW_CTRL0_0C                 	0x0C        // Highlight Window Control Register0
#define _HW_WINDOW_CTRL1_0D                 	0x0D        // Highlight Window Control Register1

//--------------------------------------------------
// Contrast/Brightness Coefficient Port
//--------------------------------------------------
//#define _CB_BRI_R_COEF_A_00                 	0x00        // Brightness Red Coefficient Set.A
//#define _CB_BRI_G_COEF_A_01                 	0x01        // Brightness Green Coefficient Set.A
//#define _CB_BRI_B_COEF_A_02                 	0x02        // Brightness Blue Coefficient Set.A
//#define _CB_CTS_R_COEF_A_03                 	0x03        // Contrast Red Coefficient Set.A
//#define _CB_CTS_G_COEF_A_04                 	0x04        // Contrast Green Coefficient Set.A
//#define _CB_CTS_B_COEF_A_05                 	0x05        // Contrast Blue Coefficient Set.A
//#define _CB_BRI_R_COEF_B_06                 	0x06        // Brightness Red Coefficient Set.B
//#define _CB_BRI_G_COEF_B_07                 	0x07        // Brightness Green Coefficient Set.B
//#define _CB_BRI_B_COEF_B_08                 	0x08        // Brightness Blue Coefficient Set.B
//#define _CB_CTS_R_COEF_B_09                 	0x09        // Contrast Red Coefficient Set.B
//#define _CB_CTS_G_COEF_B_0A                 	0x0A        // Contrast Green Coefficient Set.B
//#define _CB_CTS_B_COEF_B_0B                 	0x0B        // Contrast Blue Coefficient Set.B
//--------------------------------------------------
// Timing Controller Port
//--------------------------------------------------
#define _TCON_CTRL0_00                      	0x00        // Timing Controller Control Register0
#define _TCON_CTRL1_01                      	0x01        // Timing Controller Control Register1
#define _TCON_PIXEL_THRESHOLD_MSB_02      		0x02        // Pixel Threshold High Value for Smart Polarity
#define _TCON_PIXEL_THRESHOLD1_LSB_03     		0x03        // 2 Line Sum of Difference Threshold 1 Value: bit [7:0], ie:TH1 (Also refer to CR8C-02[7])
#define _TCON_PIXEL_THRESHOLD2_LSB_04     		0x04        // 2 Line Sum of Difference Threshold 2 Value: bit [7:0], ie:TH2 (Also refer to CR8C-02[6])
#define _TCON_LINE_THRESHOLD_05             	0x05        // Line Threshold Value for Smart Polarity
//Address: 8C-06~8C-07 Reserved to 0
#define _TCON_TCON0_V_STA_LSB_08            	0x08        // TCON[0] Vertical Start LSB Register
//#define _TCON_TCON0_V_SE_MSB_09             	0x09        // TCON[0] Vertical Start/End MSB Register
//#define _TCON_TCON0_V_END_LSB_0A            	0x0A        // TCON[0] Vertical End LSB Register
//#define _TCON_TCON0_H_STA_LSB_0B            	0x0B        // TCON[0] Horizontal Start LSB Register
//#define _TCON_TCON0_H_SE_MSB_0C             	0x0C        // TCON[0] Horizontal Start/End MSB Register
//#define _TCON_TCON0_H_END_LSB_0D            	0x0D        // TCON[0] Horizontal End LSB Register
//#define _TCON_TCON0_CTRL_0E                 	0x0E        // TCON[0] Control Register
//#define _TCON_TCON0_RESERVED_0F             	0x0F        // TCON[0] Reserved Register(TCON[0]~TCON[9] Have This Register)
#define _TCON_TCON1_V_STA_LSB_10            	0x10        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON2_V_STA_LSB_18            	0x18        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON3_V_STA_LSB_20            	0x20        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON4_V_STA_LSB_28            	0x28        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON5_V_STA_LSB_30            	0x30        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON6_V_STA_LSB_38            	0x38        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON7_V_STA_LSB_40            	0x40        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON8_V_STA_LSB_48            	0x48        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON9_V_STA_LSB_50            	0x50        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON10_V_STA_LSB_58        		0x58        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON11_V_STA_LSB_60          		0x60        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON12_V_STA_LSB_68          		0x68        // TCON[13] Vertical Start LSB Register
#define _TCON_TCON13_V_STA_LSB_70          		0x70        // TCON[13] Vertical Start LSB Register
//TCON[0]:08~0F    //TCON[1]:10~17    //TCON[2]:18~1F   //TCON[3]:20~27    //TCON[4]:28~2F
//TCON[5]:30~37    //TCON[6]:38~3F    //TCON[7]:40~47   //TCON[8]:48~4F    //TCON[9]:50~57
//TCON[10]:58~5F   //TCON[11]:60~67   //TCON[12]:68~6F  //TCON[13]:70~77

//##################################################
// Dot Masking
//##################################################
//#define _TCON_TCON10_DOT_MASK_CTRL_5F     	0x5F        // TCON[10] Dot Masking Control Register
//#define _TCON_TCON11_DOT_MASK_CTRL_67     	0x67        // TCON[11] Dot Masking Control Register
//#define _TCON_TCON12_DOT_MASK_CTRL_6F     	0x6F        // TCON[12] Dot Masking Control Register
//#define _TCON_TCON13_DOT_MASK_CTRL_77     	0x77        // TCON[13] Dot Masking Control Register
//Address: 8C-78~8C-9F Reserved

//##################################################
// Control For LVDS
//##################################################
#define _TCON_LVDS_CTRL0_A0                 	0xA0        // LVDS Control Register0
#define _TCON_LVDS_CTRL1_A1                 	0xA1        // LVDS Control Register1
#define _TCON_LVDS_CTRL2_A2                 	0xA2        // LVDS Control Register2
#define _TCON_LVDS_CTRL3_A3                 	0xA3        // LVDS Control Register3
#define _TCON_LVDS_CTRL4_A4                 	0xA4        // LVDS Control Register4
#define _TCON_LVDS_CTRL5_A5                 	0xA5        // LVDS Control Register5
//Address: 8C-A6~8C-BF Reserved

//##################################################
// Control For RSDS
//##################################################
#define _TCON_RSDS_OUTPUT_CTRL0_C0          	0xC0        // RSDS Output Control Register
#define _TCON_RSDS_INTERLEAVING_H_C1        	0xC1        // RSDS Display Data Bus Interleaving Line Buffer Length High Byte
#define _TCON_RSDS_INTERLEAVING_L_C2        	0xC2        // RSDS Display Data Bus Interleaving Line Buffer Length Low Byte
//--------------------------------------------------
// Pin Configuration Port
//--------------------------------------------------
#define _PS_CTRL00_00                       	0x00        // Pin Share Control Register0
//#define _PS_CTRL01_01                       	0x01        // Pin Share Control Register1
//#define _PS_CTRL02_02                       	0x02        // Pin Share Control Register2
//#define _PS_CTRL03_03                       	0x03        // Pin Share Control Register3
//#define _PS_CTRL04_04                       	0x04        // Pin Share Control Register4
//#define _PS_CTRL05_05                       	0x05        // Pin Share Control Register5
//#define _PS_CTRL06_06                       	0x06        // Pin Share Control Register6
//#define _PS_CTRL07_07                       	0x07        // Pin Share Control Register7
//#define _PS_CTRL08_08                       	0x08        // Pin Share Control Register8
//#define _PS_CTRL09_09                       	0x09        // Pin Share Control Register9
//#define _PS_CTRL0A_0A                       	0x0A        // Pin Share Control RegisterA
//#define _PS_CTRL0B_0B                       	0x0B        // Pin Share Control RegisterB
//#define _PS_CTRL0C_0C                       	0x0C        // Pin Share Control RegisterC
//#define _PS_CTRL0D_0D                       	0x0D        // Pin Share Control RegisterD
//#define _PS_CTRL0E_0E                       	0x0E        // Pin Share Control RegisterE
//Address: 8E-0F~8E-1F Reserved

//##################################################
// Pin Driving
//##################################################
#define _PS_PIN_DRIVING_CTRL0_20           		0x20        // Pin Driving Current Control Register0
//#define _PS_PIN_DRIVING_CTRL1_21          	0x21        // Pin Driving Current Control Register1
//#define _PS_PIN_DRIVING_CTRL2_22          	0x22        // Pin Driving Current Control Register2
//#define _PS_PIN_DRIVING_CTRL3_23          	0x23        // Pin Driving Current Control Register3
//#define _PS_PIN_DRIVING_CTRL4_24          	0x24        // Pin Driving Current Control Register4
//#define _PS_PIN_DRIVING_CTRL5_25            	0x25        // Pin Driving Current Control Register5
//#define _PS_PIN_DRIVING_CTRL6_26            	0x26        // Pin Driving Current Control Register6
//#define _PS_PIN_DRIVING_CTRL7_27            	0x27        // Pin Driving Current Control Register7
//#define _PS_PIN_DRIVING_CTRL8_28            	0x28        // Pin Driving Current Control Register8
//Address: 8E-29~8E-2F Reserved

//##################################################
// Configuration Of Test Pin
//##################################################
//#define _PS_TEST_PIN_CTRL0_30               	0x30        // Test Pin Control Register0
//#define _PS_TEST_PIN_CTRL1_31               	0x31        // Test Pin Control Register1
//#define _PS_TEST_PIN_CTRL2_32               	0x32        // Test Pin Control Register2
//#define _PS_TEST_PIN_CTRL3_33               	0x33        // Test Pin Control Register3

//--------------------------------------------------
// Peaking and Coring Port
//--------------------------------------------------
//#define _PC_PEAKING_COEF0_00                	0x00        // Coefficient C0 of Peaking filter
//#define _PC_PEAKING_COEF1_01                	0x01        // Coefficient C1 of Peaking filter
//#define _PC_PEAKING_COEF2_02                	0x02        // Coefficient C2 of Peaking filter
//#define _PC_CORING_MIN_03                   	0x03        // Coring Minimum value
//#define _PC_CORING_MAX_POS_04             	0x04        // Coring Maximum Positive value
//#define _PC_CORING_MAX_NEG_05          		0x05        // Coring Maximum Negitive value (2's complement)

//--------------------------------------------------
// ICM Port
//--------------------------------------------------
//#define _ICM_MST_HUE_HB_00                  	0x00        // High Byte Of Master Hue For Chroma Modifier N
//#define _ICM_MST_HUE_LB_01                  	0x01        // Low Byte Of Master Hue For Chroma Modifier N
//#define _ICM_HUE_SET_02                     	0x02        // ICM HUE Setting
//#define _ICM_U_OFFSET_03                    	0x03        // U Offset 00, -128~127
//#define _ICM_V_OFFSET_04                    	0x04        // V Offset 00, -128~127
// From E3-0x03 To E3-0x32 Is U/V Offset

//--------------------------------------------------
// CMDI Port
//--------------------------------------------------
//#define _CMDI_H_DISP_MSB_00                 	0x00        // CMDI Horizontal Display MSB
//#define _CMDI_H_DISP_LSB_01                 	0x01        // CMDI Horizontal Display LSB
///////////////////////////////////////////////////////////////////////////////////////////
//Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved
//Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved
//Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved
//Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved
//Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved
///////////////////////////////////////////////////////////////////////////////////////////





//PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE
//////////////////////////////         Page + Port         ////////////////////////////////
//PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT

//--------------------------------------------------
// {Page2} HDCP Acess Port
//--------------------------------------------------
//#define _P2_HDCP_FRAME_COUNTER_C0           	0xC0        // HDCP Frame Counter Register
//#define _P2_HDCP_SYS_INFO_C1                	0xC1        // HDCP System Information Register

//--------------------------------------------------
// {Page2} HDMI Acess Port
//--------------------------------------------------
//Port C9&CA Referance To Specification
//Following Register is Assigned By Port CD&CE
#define _P2_HDMI_SCR_00                     	0x00        // HDMI Switch Control Register
//#define _P2_HDMI_N_VAL_01                   	0x01        // HDMI N Value Register
//#define _P2_HDMI_BCHCR_02                   	0x02        // HDMI BCH Control Register
#define _P2_HDMI_AFCR_03                      	0x03        // HDMI Audio FIFO Control Register
//#define _P2_HDMI_AFSR_04                    	0x04        // HDMI Audio FIFO BIST Start Register
//#define _P2_HDMI_MAGCR0_05                  	0x05        // HDMI Maunal Gain Control Register0
//#define _P2_HDMI_MAGCR1_06                  	0x06        // HDMI Maunal Gain Control Register1
//Address: P2-CE-07 ~ P2-CE-0F Reserved
#define _P2_HDMI_CMCR_10                      	0x10        // HDMI Input Clock MUX Control Register
#define _P2_HDMI_MCAPR_11                     	0x11        // HDMI M code
#define _P2_HDMI_SCAPR_12                     	0x12        // HDMI S code
#define _P2_HDMI_DCAPR0_13                    	0x13        // HDMI D code HByte
#define _P2_HDMI_DCAPR1_14                    	0x14        // HDMI D code LByte
#define _P2_HDMI_PSCR_15                      	0x15        // HDMI Phase Tracking Enable Control Register
#define _P2_HDMI_FTR_1A                       	0x1A        // HDMI Target Time For Summation Of One Trent To Decide The Trent
#define _P2_HDMI_FBR_1B                       	0x1B        // HDMI Target FIFO Depth and Boundary Address Distance
#define _P2_HDMI_ICTPSR1_21                   	0x21        // HDMI I Code of Trend
#define _P2_HDMI_ICBPSR1_25                   	0x25        // HDMI I Code of Boundary
#define _P2_HDMI_PCBPSR0_26                   	0x26        // HDMI P Code of Boundary HByte
#define _P2_HDMI_PCBPSR1_27                   	0x27        // HDMI P Code of Boundary LByte
#define _P2_HDMI_NTX1024TR0_28                	0x28        // HDMI Masure the length of 1024 TV by Crystal
#define _P2_HDMI_STBPR_2A                     	0x2A        // HDMI Boundary Tracking Update Response Time
#define _P2_HDMI_AAPNR_2D                     	0x2D        // HDMI Phase Swallow Enable Control Register
#define _P2_HDMI_AVMCR_30                     	0x30        // HDMI Audio/Video Mute Control Register
#define _P2_HDMI_WDCR0_31                     	0x31        // HDMI Watch Dog Control Register0
#define _P2_HDMI_WDCR1_32                     	0x32        // HDMI Watch Dog Control Register1
#define _P2_HDMI_DBCR_34                      	0x34        // HDMI Auto Load Double Buffer Enable
#define _P2_HDMI_DPCR0_38                     	0x38        // HDMI DPLL Control Register0
#define _P2_HDMI_DPCR1_39                     	0x39        // HDMI DPLL Control Register1
#define _P2_HDMI_DPCR3_3B                     	0x3B        // HDMI DPLL Control Register3
#define _P2_HDMI_VWDSR_41                     	0x41        // HDMI Video Watch Dog For Packet Variation Status
#define _P2_HDMI_PVGCR0_45                    	0x45        // HDMI Packet Variation Status Enable Control Register0
#define _P2_HDMI_VCR_50                       	0x50        // HDMI Video Mode Control Register
#define _P2_HDMI_ACRCR_51                     	0x51        // HDMI Color Space Control Register0
#define _P2_HDMI_ACRSR0_52                    	0x52        // HDMI CTS in usage Register(CTS[19:12])
#define _P2_HDMI_AOCR_62                      	0x62        // HDMI SPDIF/I2S Switch Control Register
///////////////////////////////////////////////////////////////////////////////////////////
//Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved
//Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved
//Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved
//Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved
//Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved Reserved
///////////////////////////////////////////////////////////////////////////////////////////

//PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE
//////////////////////////////         Page + Port         ////////////////////////////////
//PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT


#if(_SCALER_TYPE == _RTD3580D)
//PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT
//----------------------------   DCC Acess Port + Page     --------------------------------
//PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE

//--------------------------------------------------
// Page 0 (For Histogram / Ymin-max / Soft-Clamping / Scene-Change)
//--------------------------------------------------
#define _DCC_P0_NOR_FACTOR_H_00             	0x00        // DCC Normalized Factor HByte
//#define _DCC_P0_NOR_FACTOR_M_01             	0x01        // DCC Normalized Factor MByte
//#define _DCC_P0_NOR_FACTOR_L_02             	0x02        // DCC Normalized Factor LByte
//#define _DCC_P0_BBE_CTRL_03                 	0x03        // DCC Black Background Exception Control Register
//#define _DCC_P0_NFLT_CTRL_04                	0x04        // DCC Noise Filter Control Register
//#define _DCC_P0_HIST_CTRL_05                	0x05        // DCC Histogram Control Register
//#define _DCC_P0_SOFT_CLAMP_06               	0x06        // DCC Slope Of Soft Clamping
//#define _DCC_P0_Y_MAX_LB_07                 	0x07        // DCC Lower Bound Of Y_MAX
//#define _DCC_P0_Y_MIN_HB_08                 	0x08        // DCC Higher Bound Of Y_MIN
//#define _DCC_P0_SCG_PERIOD_09               	0x09        // DCC Scene Change Mode Period
//#define _DCC_P0_SCG_LB_0A                   	0x0A        // SCG_DIFF Lower Bound For Exiting Scene Change Mode
//#define _DCC_P0_SCG_HB_0B                   	0x0B        // SCG_DIFF Higher Bound For Exiting Scene Change Mode
//#define _DCC_P0_POPUP_CTRL_0C               	0x0C        // DCC POP Up Status Register
//#define _DCC_P0_SCG_DIFF_0D                 	0x0D        // (Histogram Difference Between Current Frame And Average)/8
//#define _DCC_P0_Y_MAX_VAL_0E                	0x0E        // Max{Y_MAX_LB,(Y Maximum In Current Frame/4)}
//#define _DCC_P0_Y_MIN_VAL_0F                	0x0F        // Min{Y_MIN_HB,(Y Minimum In Current Frame/4)}
//#define _DCC_P0_S0_VALUE_10                 	0x10        // Normalized Histogram S0 Value
//#define _DCC_P0_S1_VALUE_11                 	0x11        // Normalized Histogram S1 Value
//#define _DCC_P0_S2_VALUE_12                 	0x12        // Normalized Histogram S2 Value
//#define _DCC_P0_S3_VALUE_13                 	0x13        // Normalized Histogram S3 Value
//#define _DCC_P0_S4_VALUE_14                 	0x14        // Normalized Histogram S4 Value
//#define _DCC_P0_S5_VALUE_15                 	0x15        // Normalized Histogram S5 Value
//#define _DCC_P0_S6_VALUE_16                 	0x16        // Normalized Histogram S6 Value

//--------------------------------------------------
// Page 1 (for Y-Curve / WBL Expansion)
//--------------------------------------------------
//#define _DCC_P1_DEF_CRV01_00                	0x00        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV02_01                	0x01        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV03_02                	0x02        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV04_03                	0x03        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV05_04                	0x04        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV06_05                	0x05        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV07_06                	0x06        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV08_07                	0x07        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV09_08                	0x08        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV10_09                	0x09        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV11_0A                	0x0A        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV12_0B                	0x0B        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV13_0C                	0x0C        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV14_0D                	0x0D        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV15_0E                	0x0E        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_Y_BL_BIAS_0F                	0x0F        // Y Offset For Black Level Expansion
//#define _DCC_P1_Y_WL_BIAS_10                	0x10        // Y Offset For While Level Expansion
//#define _DCC_P1_BLD_UB_11                   	0x11        // Upper Bound Of Blending Factor
//#define _DCC_P1_BLD_LB_12                   	0x12        // Lower Bound Of Blending Factor
//#define _DCC_P1_DEV_FACTOR_13               	0x13        // Deviation Weighting Factor
//#define _DCC_P1_BLD_VAL_14                  	0x14        // Blending Factor Value = Max{BLD_UB - [(DEV_VAL*DEV_FACTOR)/256], BLD_LB}
//#define _DCC_P1_DEV_VAL_HI_15               	0x15        // Deviation Value HByte
//#define _DCC_P1_DEV_VAL_LO_16               	0x16        // Deviation Value LByte

//--------------------------------------------------
// Page 2 (for Calculation Parameter)
//--------------------------------------------------
// E7-00 ~ E7-8F of Page2 is SRAM initial value
//#define _DCC_P3_SRAM_00                     	0x00        // SRAM Initial Value In Register 0x00

//--------------------------------------------------
// Page 3 (for Testing and Debug)
//--------------------------------------------------
//#define _DCC_P3_SRAM_BIST_00                	0x00        // DCC SRAM BIST Control Register

//PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT
//----------------------------   DCC Acess Port + Page     --------------------------------
//PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE

#else
//PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT
//----------------------------   DCC Acess Port + Page     --------------------------------
//PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE

//--------------------------------------------------
// Page 0 (For Histogram / Ymin-max / Soft-Clamping / Scene-Change)
//--------------------------------------------------
//#define _DCC_P0_NOR_FACTOR_H_00             	0x00        // DCC Normalized Factor HByte
//#define _DCC_P0_NOR_FACTOR_M_01             	0x01        // DCC Normalized Factor MByte
//#define _DCC_P0_NOR_FACTOR_L_02             	0x02        // DCC Normalized Factor LByte
//#define _DCC_P0_BBE_CTRL_03                 	0x03        // DCC Black Background Exception Control Register
//#define _DCC_P0_NFLT_CTRL_04                	0x04        // DCC Noise Filter Control Register
//#define _DCC_P0_HIST_CTRL_05                	0x05        // DCC Histogram Control Register
//#define _DCC_P0_SOFT_CLAMP_06               	0x06        // DCC Slope Of Soft Clamping
//#define _DCC_P0_Y_MAX_LB_07                 	0x07        // DCC Lower Bound Of Y_MAX
//#define _DCC_P0_Y_MIN_HB_08                 	0x08        // DCC Higher Bound Of Y_MIN
//#define _DCC_P0_SCG_PERIOD_09               	0x09        // DCC Scene Change Mode Period
//#define _DCC_P0_SCG_LB_0A                   	0x0A        // SCG_DIFF Lower Bound For Exiting Scene Change Mode
//#define _DCC_P0_SCG_HB_0B                   	0x0B        // SCG_DIFF Higher Bound For Exiting Scene Change Mode
//#define _DCC_P0_POPUP_CTRL_0C               	0x0C        // DCC POP Up Status Register
//#define _DCC_P0_SCG_DIFF_0D                 	0x0D        // (Histogram Difference Between Current Frame And Average)/8
//#define _DCC_P0_Y_MAX_VAL_0E                	0x0E        // Max{Y_MAX_LB,(Y Maximum In Current Frame/4)}
//#define _DCC_P0_Y_MIN_VAL_0F                	0x0F        // Min{Y_MIN_HB,(Y Minimum In Current Frame/4)}
//#define _DCC_P0_S0_VALUE_10                 	0x10        // Normalized Histogram S0 Value
//#define _DCC_P0_S1_VALUE_11                 	0x11        // Normalized Histogram S1 Value
//#define _DCC_P0_S2_VALUE_12                 	0x12        // Normalized Histogram S2 Value
//#define _DCC_P0_S3_VALUE_13                 	0x13        // Normalized Histogram S3 Value
//#define _DCC_P0_S4_VALUE_14                 	0x14        // Normalized Histogram S4 Value
//#define _DCC_P0_S5_VALUE_15                 	0x15        // Normalized Histogram S5 Value
//#define _DCC_P0_S6_VALUE_16                 	0x16        // Normalized Histogram S6 Value
//--------------------------------------------------
// Page 1 (for Y-Curve / WBL Expansion)
//--------------------------------------------------
//#define _DCC_P1_DEF_CRV01_00                	0x00        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV02_01                	0x01        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV03_02                	0x02        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV04_03                	0x03        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV05_04                	0x04        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV06_05                	0x05        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV07_06                	0x06        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV08_07                	0x07        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV09_08                	0x08        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV10_09                	0x09        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV11_0A                	0x0A        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV12_0B                	0x0B        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV13_0C                	0x0C        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV14_0D                	0x0D        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_DEF_CRV15_0E                	0x0E        // Pre-Defined Y-Curve; Keep DEF_CRV[N] >= DEF_CRV[N-1]
//#define _DCC_P1_Y_BL_BIAS_0F                	0x0F        // Y Offset For Black Level Expansion
//#define _DCC_P1_Y_WL_BIAS_10                	0x10        // Y Offset For While Level Expansion
//#define _DCC_P1_BLD_UB_11                   	0x11        // Upper Bound Of Blending Factor
//#define _DCC_P1_BLD_LB_12                   	0x12        // Lower Bound Of Blending Factor
//#define _DCC_P1_DEV_FACTOR_13           		0x13        // Deviation Weighting Factor
//#define _DCC_P1_BLD_VAL_14                  	0x14        // Blending Factor Value = Max{BLD_UB - [(DEV_VAL*DEV_FACTOR)/256], BLD_LB}
//#define _DCC_P1_DEV_VAL_HI_15               	0x15        // Deviation Value HByte
//#define _DCC_P1_DEV_VAL_LO_16               	0x16        // Deviation Value LByte

//--------------------------------------------------
// Page 2 (for Calculation Parameter)
//--------------------------------------------------
// E7-00 ~ E7-8F of Page2 is SRAM initial value
//#define _DCC_P3_SRAM_00                     	0x00        // SRAM Initial Value In Register 0x00

//--------------------------------------------------
// Page 3 (for Testing and Debug)
//--------------------------------------------------
//#define _DCC_P3_SRAM_BIST_00                	0x00        // DCC SRAM BIST Control Register

//PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT PORT
//----------------------------   DCC Acess Port + Page     --------------------------------
//PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE PAGE
#endif

