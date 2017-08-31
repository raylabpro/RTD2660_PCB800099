////////////////////////////////////////////////////////////////////////////
//         Copyright of KaiXuang Video Technology Co.,LTD                 //
//                                                                        //
//                                                                        //
//                  Analog/Digital Video/TV source code                   //
//   Ver: V19                                                             //
//   Create file time: 2008.11.1                                          //
//   End modify time:  2009.4.14                                          //
//   For RTD2660/RTD2662  KR266Xseries                                    //
////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------------------------------
// Basic Settings
//----------------------------------------------------------------------------------------------------

#define _DEFAULT                            	0	//xx.xx%
#define _OVERSCAN_PERCENT_93_75             	1	//93.75%
#define _OVERSCAN_PERCENT_95_00             	2	//95.00%
#define _OVERSCAN_PERCENT_97_00             	3	//97.00%
#define _OVERSCAN_PANASONIC_SIZE            	4

#define _HDMI_OVERSCAN_PERCENT              	_OVERSCAN_PERCENT_93_75
#define _YPBPR_OVERSCAN_PERCENT             	_OVERSCAN_PERCENT_93_75
#define _VIDEO8_OVERSCAN_PERCENT            	_OVERSCAN_PANASONIC_SIZE

#define _NEW_DV_CTRL_ENABLE                 	       _DISABLE

#define _SUPPORTDDCCI						1

//--------------------------------------------------
// Debug Tool
//--------------------------------------------------
//_NONE,_ISP_FOR_RTD3580D_EMCU,_ISP_FOR_DDCCI
#define _DEBUG_TOOL                             _ISP_FOR_DDCCI

#define _RS232_EN					 _OFF

#define _ACPOWERON_RS232			 _OFF

//--------------------------------------------------
// OSD Type
//--------------------------------------------------
#define _OSD001						   1
#define _OSD002			                        2
#define _OSD003			                        3

#define _OSD_TYPE					   _OSD003

#define _FAC_OSD                                     _DISABLE//_ENABLE


#define _LOGO_ENABLE                           	        _OFF//  _ON//_OFF	
#define _LOGO_SIZE							0x00
#define _LOGO_DISPLAY_TIME					3

#define _LOGO_Visatech                       _OFF//_ON //100423wtao

#define _EEPROM 								0
#define _FLASH								1

#define _MEMORY_LOCATION					_FLASH//_EEPROM




//--------------------------------------------------
// Definitions of MPLL M Code
//--------------------------------------------------
#define _MPLL_M_CODE                    		0x34

//--------------------------------------------------
// Definitions of MPLL N Code
//--------------------------------------------------
#define _MPLL_N_CODE                    		0x02

//--------------------------------------------------
//Nonlinear scale up method
//--------------------------------------------------
#define _ROOF              			               0
#define _BOUL              				        1

#define _NONLINEAR_SCALEUP_METHOD       _ROOF
                                               

//--------------------------------------------------
// Color Preference
//--------------------------------------------------
#define _REALTEK_STYLE					        0
#define _PANASONIC_STYLE				        1

#define _COLOR_PREFERENCE				        _PANASONIC_STYLE
                                               
//--------------------------------------------------
// Definitions of Gamma Table Type
//--------------------------------------------------
#define _COMPACT_GAMMA_NORMAL_TABLE     		0
#define _FULL_GAMMA_NORMAL_TABLE        		1
#define _COMPACT_GAMMA_COMPRESS_TABLE   		2
#define _FULL_GAMMA_COMPRESS_TABLE      		3
#define _FULL_GAMMA_COMPRESS_TABLE2                4

#define _GAMMA_TYPE                         	_COMPACT_GAMMA_NORMAL_TABLE


//--------------------------------------------------
// Definitions of Nonlinear Scaling
//--------------------------------------------------
#define _NONLINEAR_SCALING              		_DISABLE

//--------------------------------------------------
// Definitions of APLL1 M/N Code
//--------------------------------------------------
#define _APLL1_M_CODE                   		25
#define _APLL1_N_CODE                   		2

//--------------------------------------------------
// Definitions of APLL1 M/N Code
//--------------------------------------------------
#define _APLL_M_CODE                   			25   //default = 25
#define _APLL_N_CODE                   			3    //default = 3

//--------------------------------------------------
// Definitions of DDS P Code
//--------------------------------------------------
#define _DDS_P_CODE                     		23


//--------------------------------------------------
// Definitions of APLL Fast Lock
//--------------------------------------------------
#define _APLL_FAST_LOCK                 		_ON


//--------------------------------------------------
// Definitions of DPLL N Code
//--------------------------------------------------
#define _M2PLL_USE                      		_OFF//_OFF
#define _M2PLL_XTAL                     		_XTAL12000K
#define _RTD_M2PLL_RATIO                	(_RTD_XTAL / _M2PLL_XTAL)

//--------------------------------------------------
// DVI Long Cable Supported
//--------------------------------------------------
#define _DVI_LONG_CABLE_SUPPORT         		       _OFF

//--------------------------------------------------
// DVI-I Source Switch (VGA/DVI) Supported
//--------------------------------------------------
#define _DVI_I_SOURCE_SWITCH_SUPPORT    		_OFF

//--------------------------------------------------
// VGA/DVI Auto Switch (VGA/DVI) Supported
//--------------------------------------------------
#define _VGA_DVI_AUTO_SWITCH_SUPPORT     		_FALSE


//--------------------------------------------------
// Hsync Type Detection Select of Input VGA Port
//--------------------------------------------------
//_HSYNC_ONLY,_HSYNC_WITH_SOG,_HSYNC_WITH_SOG_SOY
#define _HSYNC_TYPE_SELECT              		_HSYNC_WITH_SOG_SOY  //The setting only for _A0_VGA_PORT or _A1_VGA_PORT

//--------------------------------------------------
// A0 and A1 Hsync Source Swap
//--------------------------------------------------
#define _HSYNC_SOURCE_SWAP              		_OFF

//--------------------------------------------------
// 
//--------------------------------------------------
#define _DVI_DE_ONLY_SUPPORT            		_ON
 
//--------------------------------------------------
// Set Different Display Information by Mode
//--------------------------------------------------
#define _DISP_INFO_BY_MODE              		      _OFF


//--------------------------------------------------
// Set DClk Spread Spectrum Range
//--------------------------------------------------
#define _DCLK_SPREAD_RANGE              		0	//0~15, 0△disable, 15△7.5%


//--------------------------------------------------
// Hardware Load Font Supported (Only No Swap)
//--------------------------------------------------
#define _HARDWARE_LOAD_FONT             		_ON


//--------------------------------------------------
// Audio PLL Lock Mode
//--------------------------------------------------
//_HARDWARE_TRACKING,_N_CTS
#define _AUDIO_LOCK_MODE                		        _N_CTS


//--------------------------------------------------
// Set Adjusting Vertical Position Direction Method
//--------------------------------------------------
//_V_POSITION_METHOD_0,_V_POSITION_METHOD_1
#define _V_POSITION_DIRECTION           		_V_POSITION_METHOD_0

//--------------------------------------------------
// RTD2553V Set Method of Hsync Type Detection for Analog Input
//--------------------------------------------------
#define _NORMAL_RUN                     		0
#define _AUTO_RUN			            		1

#define _HSYNC_TYPE_DETECTION           	_AUTO_RUN

//-------------------------------------------------------
//	YPBPR Auto SOY function
//-------------------------------------------------------
#define _YPBPR_AUTO_SOY    					_DISABLE
#define _YPBPR_HW_AUTO_SOY    		  	    	_ENABLE

//-------------------------------------------------------
// SOG definition
//-------------------------------------------------------
#define _SOY_LEVEL					            0x20
#define _SOY_RESISTER				            2		// 0 ~ 3


//--------------------------------------------------
// YPbPr source non-check APLL unlock for DVD player 
//--------------------------------------------------
#define _YPBPR_NONE_CHECK_APLL			   	_ENABLE

//--------------------------------------------------
// YPBPR AUTO COLOR OPTION
//--------------------------------------------------
#define _ORIGINAL_TYPE							0
#define _NEW_TYPE								1

#define _YPBPR_AUTO_TYPE						_NEW_TYPE
	
//-------------------------------------------------------
// De-Interlace Supported
//-------------------------------------------------------
#define _DE_INTERLACE_SUPPORT           		       _ON

//-------------------------------------------------------
//
//-------------------------------------------------------
#define _DCC_FUNC								_DISABLE

//-------------------------------------------------------
//  Double Scaling
//-------------------------------------------------------
#define _Double_Scaling							_DISABLE	

//-------------------------------------------------------
//  AdjustCustomerColorMode
//-------------------------------------------------------
#define _AdjustCustomerColorMode				_DISABLE	


//--------------------------------------------------
// De-Interlace  TEST  OPTION
//--------------------------------------------------
#define _DE_INTERLACE_TEST_OPTION		 		_ENABLE


#define _VIDEO_AUTO_WHITE_BLANCE   			_ENABLE//_FALSE

//---------------------------------------------------------
//  Sharpness table
//  Panel resolution >1024x768 use table 1
//  Panel resolution <1024x768 use table 2
//---------------------------------------------------------

#define SharpnessNoneTable   			       0
#define SharpnessTable1		 			       1
#define SharpnessTable2					       2

#define _Peaking_Coring_Table 			       SharpnessTable2

//-------------------------------------------------------
// sRGB Color Enhance
// used sRGB to enhance Color
//-------------------------------------------------------
#define sRGB_Color_Enhance				       _ENABLE

//---------------------------------------
//2662 Enlarge sRGB Range
//---------------------------------------
#define _SRGB_ENLARGE_RANGE                         _TRUE


//---------------------------------------
//2660 ver B IC need set 1
//---------------------------------------
#define _2660_IC_VERB 	                       1     //scaler 是s4选1不是选0


// Key Define's

// Support pcb : _PCB_KR660TVL_V10
// Support osd : OSD001
#define _KT_PCB2660_001                        0

// Support pcb : _PCB_KR660TVL_V10
// Support osd : OSD002
#define _KT_PCB2660_002                        1

// Support pcb : _PCB_KR660TVL_V10
// Support osd : OSD003
#define _KT_PCB2660_003                        3

// Support pcb : _PCB_KR660TVL_V10
// Support osd : OSD003
#define _KT_PCB2660_003_5KEY              4

#define _READ_REMOTE_CODE                    _DISABLE

#define _READ_polarity_DATA                    _DISABLE

#define _READ_TV_MODE_DATA                  _DISABLE
                        

#define _CHECK_MCS                                     0
#define _TV_READY                                       1//0

#define _FUNC_SLEEP						1
#define _FUNC_PICTUREMODE				0

#define _SLEEPKEY_FUNC					_FUNC_SLEEP 














