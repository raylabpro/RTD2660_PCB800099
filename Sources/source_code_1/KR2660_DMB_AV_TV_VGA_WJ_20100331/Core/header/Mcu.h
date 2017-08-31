//----------------------------------------------------------------------------------------------------
// ID Code      : Mcu.h No.0001
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Crystal Frequency
//--------------------------------------------------

#define _MCU_INST_CYCLE             	((DWORD)1000000 * 4 / _MCU_XTAL)
#define _MCU_INST_CYCLE_PD				((DWORD)1000000 * 4 / _RTD_XTAL)		//pwr-dn case(reset 27M xtal clk)

//--------------------------------------------------
// Timer Period (unit: ns)
//--------------------------------------------------
#define _16MS_PERIOD                	(DWORD)16000000
#define _8MS_PERIOD                		(DWORD)8000000
#define _5MS_PERIOD                		(DWORD)5000000
#define _4167uS_PERIOD            		(DWORD)4167000
#define _8333uS_PERIOD              	(DWORD)8333000
#define _10MS_PERIOD                	(DWORD)10000000
#define _1MS_PERIOD                 	(DWORD)1000000		//330000	//380000	//1000000		//eric 20070509 IrDA
#define _HALF_MS_PERIOD             	(DWORD)500000
#define _375uS_PERIOD              		(DWORD)375000
#define _250uS_PERIOD 					(DWORD)250000		//830000	//95000	//250000		//eric 20070509 IrDA
#define _150uS_PERIOD 					(DWORD)150000
#define _125uS_PERIOD 					(DWORD)125000

#define _TIMER0_PERIOD					_250uS_PERIOD
#define _EVENT_PERIOD					_1MS_PERIOD / _TIMER0_PERIOD

//--------------------------------------------------
// Timer0 Settings (1ms)
//--------------------------------------------------
#define _TIMER0_COUNT_NUM				(0xFFFF - (_TIMER0_PERIOD / _MCU_INST_CYCLE))			//pwr-up case(reset 24.3M pll clk)
#define _TIMER0_COUNT_LBYTE				(_TIMER0_COUNT_NUM & 0x00FF)
#define _TIMER0_COUNT_HBYTE				(_TIMER0_COUNT_NUM >> 8)

#define _TIMER0_COUNT_NUM_PD			(0xFFFF - (_TIMER0_PERIOD / _MCU_INST_CYCLE_PD))		//pwr-dn case(reset 27M xtal clk)
#define _TIMER0_COUNT_LBYTE_PD			(_TIMER0_COUNT_NUM_PD & 0x00FF)
#define _TIMER0_COUNT_HBYTE_PD			(_TIMER0_COUNT_NUM_PD >> 8)

//#define _TIMER1_COUNT_NUM           	(0xFFFF - (_16MS_PERIOD / _MCU_INST_CYCLE))
//#define _TIMER1_COUNT_NUM            	(0xFFFF - (_1MS_PERIOD / _MCU_INST_CYCLE))//(0x1)
#define _TIMER1_COUNT_NUM           	(1)
#define _TIMER1_COUNT_LBYTE         	(_TIMER1_COUNT_NUM & 0x00FF)
#define _TIMER1_COUNT_HBYTE         	(_TIMER1_COUNT_NUM >> 8)

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of mcu I/O pin
//--------------------------------------------------
// MCU Port 5
#define _MCU_PORT52                     MCU_PORT52_PIN_REG_FFC1
#define _MCU_PORT53                     MCU_PORT53_PIN_REG_FFC2
#define _MCU_PORT54                     MCU_PORT54_PIN_REG_FFC3
#define _MCU_PORT55                     MCU_PORT55_PIN_REG_FFC4
#define _MCU_PORT56                     MCU_PORT56_PIN_REG_FFC5
#define _MCU_PORT57                     MCU_PORT57_PIN_REG_FFC6
// MCU Port 6
#define _MCU_PORT60                     MCU_PORT60_PIN_REG_FFC7
#define _MCU_PORT61                     MCU_PORT61_PIN_REG_FFC8
#define _MCU_PORT62                     MCU_PORT62_PIN_REG_FFC9
#define _MCU_PORT63                     MCU_PORT63_PIN_REG_FFCA
#define _MCU_PORT64                     MCU_PORT64_PIN_REG_FFCB
#define _MCU_PORT65                     MCU_PORT65_PIN_REG_FFCC
#define _MCU_PORT66                     MCU_PORT66_PIN_REG_FFCD
#define _MCU_PORT67                     MCU_PORT67_PIN_REG_FFCE
// MCU Port 7
#define _MCU_PORT70                     MCU_PORT70_PIN_REG_FFCF
#define _MCU_PORT71                     MCU_PORT71_PIN_REG_FFD0
#define _MCU_PORT72                     MCU_PORT72_PIN_REG_FFD1
#define _MCU_PORT73                     MCU_PORT73_PIN_REG_FFD2
#define _MCU_PORT74                     MCU_PORT74_PIN_REG_FFD3
#define _MCU_PORT75                     MCU_PORT75_PIN_REG_FFD4
#define _MCU_PORT76                     MCU_PORT76_PIN_REG_FFD5
// MCU Port 8
#define _MCU_PORT80                     MCU_PORT80_PIN_REG_FFD6
#define _MCU_PORT81                     MCU_PORT81_PIN_REG_FFD7
// MCU Port 9
#define _MCU_PORT90                     MCU_PORT90_PIN_REG_FFD8
#define _MCU_PORT91                     MCU_PORT91_PIN_REG_FFD9
#define _MCU_PORT92                     MCU_PORT92_PIN_REG_FFDA
#define _MCU_PORT93                     MCU_PORT93_PIN_REG_FFDB
#define _MCU_PORT94                     MCU_PORT94_PIN_REG_FFDC




#ifdef __MCU__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------



#if(_MCU_TYPE == _REALTEK_RTD3580D_EMCU)


sfr P4 = 0xA5;

BYTE xdata _NOT_USE_REG	_at_ 0xFEFF;

#if(_HDMI_EDID==_ON)

    #if(_HDMI_DDC_CHANNEL_SELECT==_DDC2)
    BYTE xdata MCU_DDCRAM_HDMI[256]         _at_ 0xFD80;
    #elif (_HDMI_DDC_CHANNEL_SELECT==_DDC3)
    BYTE xdata MCU_DDCRAM_HDMI[256]         _at_ 0xFE00;
    #endif

#endif

#if(_DVI_EDID==_ON)

    #if(_DVI_DDC_CHANNEL_SELECT==_DDC2)
    BYTE xdata MCU_DDCRAM_DVI[128]         _at_ 0xFD80;
    #elif (_DVI_DDC_CHANNEL_SELECT==_DDC3)
    BYTE xdata MCU_DDCRAM_DVI[128]         _at_ 0xFE80;
    #endif

#endif

#if _VGA_EDID
    #if(_HDMI_EDID==_ON || _DVI_EDID==_ON)
        #if(((_HDMI_DDC_CHANNEL_SELECT==_DDC2) && (_HDMI_EDID==_ON)) || ((_DVI_DDC_CHANNEL_SELECT==_DDC2) && (_DVI_EDID==_ON)))
        BYTE xdata MCU_DDCRAM_VGA[128]     _at_ 0xFD00;
        #else
        BYTE xdata MCU_DDCRAM_VGA[128]     _at_ 0xFD80;
        #endif
    #else
    BYTE xdata MCU_DDCRAM_VGA[128]         _at_ 0xFD80;
    #endif
#endif

BYTE xdata MCU_IRQ_PRIORITY_FF01		_at_ 0xFF01;

BYTE xdata MCU_THRESHOLD_VALUE_FF0F         _at_ 0xFF0F;//new add

BYTE xdata MCU_ADC_DDC_ENA_FF1B         _at_ 0xFF1B;
BYTE xdata MCU_DVI_DDC_ENA_FF1E         _at_ 0xFF1E;
BYTE xdata MCU_DDCRAM_PART_FF21         _at_ 0xFF21;

BYTE xdata MCU_I2C_SET_SLAVE_FF23       _at_ 0xFF23;
BYTE xdata MCU_I2C_SUB_IN_FF24          _at_ 0xFF24;
BYTE xdata MCU_I2C_DATA_IN_FF25         _at_ 0xFF25;
BYTE xdata MCU_I2C_DATA_OUT_FF26        _at_ 0xFF26;
BYTE xdata MCU_I2C_STATUS_FF27          _at_ 0xFF27;
BYTE xdata MCU_I2C_IRQ_CTRL_FF28        _at_ 0xFF28;
BYTE xdata MCU_I2C_STATUS2_FF29         _at_ 0xFF29;
BYTE xdata MCU_I2C_IRQ_CTRL2_FF2A       _at_ 0xFF2A;
BYTE xdata MCU_I2C_CHANNEL_CTRL_FF2B    _at_ 0xFF2B;
BYTE xdata MCU_HDMI_DDC_ENA_FF2C        _at_ 0xFF2C;

BYTE xdata MCU_PWML_FF46			_at_ 0xFF46;
BYTE xdata MCU_PWM_EN_FF48              _at_ 0xFF48;

BYTE xdata MCU_PWM0H_DUT_FF4A           _at_ 0xFF4A;
BYTE xdata MCU_PWM1H_DUT_FF4B           _at_ 0xFF4B;
BYTE xdata MCU_PWM01L_DUT_FF4C          _at_ 0xFF4C;

BYTE xdata MCU_PWM2H_DUT_FF4D           _at_ 0xFF4D;
BYTE xdata MCU_PWM3H_DUT_FF4E           _at_ 0xFF4E;
BYTE xdata MCU_PWM23L_DUT_FF4F          _at_ 0xFF4F;

BYTE xdata MCU_PWM4H_DUT_FF50           _at_ 0xFF50;
BYTE xdata MCU_PWM5H_DUT_FF51           _at_ 0xFF51;
BYTE xdata MCU_PWM45L_DUT_FF52          _at_ 0xFF52;

//BYTE xdata MCU_PWM01L_DUT_FF4C        	_at_ 0xFF4C;

BYTE xdata MCU_COMMON_INST_EN_FF60		_at_ 0xFF60;
BYTE xdata MCU_COMMON_OP_CODE_FF61		_at_ 0xFF61;
BYTE xdata MCU_WREN_OP_CODE_FF62		_at_ 0xFF62;
BYTE xdata MCU_EWSR_OP_CODE_FF63		_at_ 0xFF63;
BYTE xdata MCU_FLASH_PROG_ISP0_FF64		_at_ 0xFF64;
BYTE xdata MCU_FLASH_PROG_ISP1_FF65		_at_ 0xFF65;
BYTE xdata MCU_FLASH_PROG_ISP2_FF66		_at_ 0xFF66;
BYTE xdata MCU_COMMON_INST_RD_PT0_FF67	_at_ 0xFF67;
BYTE xdata MCU_COMMON_INST_RD_PT1_FF68	_at_ 0xFF68;
BYTE xdata MCU_COMMON_INST_RD_PT2_FF69	_at_ 0xFF69;

BYTE xdata MCU_READ_OP_CODE_FF6A			_at_ 0xFF6A;
BYTE xdata MCU_FAST_READ_OP_CODE_FF6B		_at_ 0xFF6B;

BYTE xdata MCU_PROG_OP_CODE_FF6D			_at_ 0xFF6D;
BYTE xdata MCU_PROG_INST_FF6F				_at_ 0xFF6F;
BYTE xdata MCU_PROG_DATA_PORT_FF70		_at_ 0xFF70;
BYTE xdata MCU_PROG_LEN_FF71				_at_ 0xFF71;
BYTE xdata MCU_CRC_END_ADDR0_FF72			_at_ 0xFF72;
BYTE xdata MCU_CRC_END_ADDR1_FF73			_at_ 0xFF73;
BYTE xdata MCU_CRC_END_ADDR2_FF74			_at_ 0xFF74;

BYTE xdata MCU_PIN_SHARE_CTRL00_FF96    _at_ 0xFF96;
BYTE xdata MCU_PIN_SHARE_CTRL01_FF97    _at_ 0xFF97;
BYTE xdata MCU_PIN_SHARE_CTRL02_FF98    _at_ 0xFF98;
BYTE xdata MCU_PIN_SHARE_CTRL03_FF99    _at_ 0xFF99;
BYTE xdata MCU_PIN_SHARE_CTRL04_FF9A    _at_ 0xFF9A;
BYTE xdata MCU_PIN_SHARE_CTRL05_FF9B    _at_ 0xFF9B;
BYTE xdata MCU_PIN_SHARE_CTRL06_FF9C    _at_ 0xFF9C;
BYTE xdata MCU_PIN_SHARE_CTRL07_FF9D    _at_ 0xFF9D;
BYTE xdata MCU_PIN_SHARE_CTRL08_FF9E    _at_ 0xFF9E;
BYTE xdata MCU_PIN_SHARE_CTRL09_FF9F    _at_ 0xFF9F;
BYTE xdata MCU_PIN_SHARE_CTRL0A_FFA0    _at_ 0xFFA0;
BYTE xdata MCU_PIN_SHARE_CTRL0B_FFA1    _at_ 0xFFA1;
BYTE xdata MCU_PIN_SHARE_CTRL0C_FFA2    _at_ 0xFFA2;
BYTE xdata MCU_PIN_SHARE_CTRL0D_FFA3    _at_ 0xFFA3;
BYTE xdata MCU_PIN_SHARE_CTRL0E_FFA4    _at_ 0xFFA4;

BYTE xdata MCU_PIN_DRIVING_CTRL10_FFA6    _at_ 0xFFA6;

BYTE xdata MCU_PORT_READ_CTRL_FFC0      _at_ 0xFFC0;
BYTE xdata MCU_PORT52_PIN_REG_FFC1      _at_ 0xFFC1;
BYTE xdata MCU_PORT53_PIN_REG_FFC2      _at_ 0xFFC2;
BYTE xdata MCU_PORT54_PIN_REG_FFC3      _at_ 0xFFC3;
BYTE xdata MCU_PORT55_PIN_REG_FFC4      _at_ 0xFFC4;//eric 20070515 IrDA
BYTE xdata MCU_PORT56_PIN_REG_FFC5      _at_ 0xFFC5;//eric 20070515 power key
BYTE xdata MCU_PORT57_PIN_REG_FFC6      _at_ 0xFFC6;
BYTE xdata MCU_PORT60_PIN_REG_FFC7      _at_ 0xFFC7;//eric 20070515 AMP_STB_A
BYTE xdata MCU_PORT61_PIN_REG_FFC8      _at_ 0xFFC8;//eric 20070515 PANEL_ON
BYTE xdata MCU_PORT62_PIN_REG_FFC9      _at_ 0xFFC9;//eric 20070515 un-use pin
BYTE xdata MCU_PORT63_PIN_REG_FFCA      _at_ 0xFFCA;//eric 20070515 Write_Protect
BYTE xdata MCU_PORT64_PIN_REG_FFCB      _at_ 0xFFCB;
BYTE xdata MCU_PORT65_PIN_REG_FFCC      _at_ 0xFFCC;
BYTE xdata MCU_PORT66_PIN_REG_FFCD      _at_ 0xFFCD;
BYTE xdata MCU_PORT67_PIN_REG_FFCE      _at_ 0xFFCE;
BYTE xdata MCU_PORT70_PIN_REG_FFCF      _at_ 0xFFCF;
BYTE xdata MCU_PORT71_PIN_REG_FFD0      _at_ 0xFFD0;
BYTE xdata MCU_PORT72_PIN_REG_FFD1      _at_ 0xFFD1;
BYTE xdata MCU_PORT73_PIN_REG_FFD2      _at_ 0xFFD2;
BYTE xdata MCU_PORT74_PIN_REG_FFD3      _at_ 0xFFD3;
BYTE xdata MCU_PORT75_PIN_REG_FFD4      _at_ 0xFFD4;
BYTE xdata MCU_PORT76_PIN_REG_FFD5      _at_ 0xFFD5;
BYTE xdata MCU_PORT80_PIN_REG_FFD6      _at_ 0xFFD6;//eric 20070531
BYTE xdata MCU_PORT81_PIN_REG_FFD7      _at_ 0xFFD7;
BYTE xdata MCU_PORT90_PIN_REG_FFD8      _at_ 0xFFD8;
BYTE xdata MCU_PORT91_PIN_REG_FFD9      _at_ 0xFFD9;
BYTE xdata MCU_PORT92_PIN_REG_FFDA      _at_ 0xFFDA;
BYTE xdata MCU_PORT93_PIN_REG_FFDB      _at_ 0xFFDB;
BYTE xdata MCU_PORT94_PIN_REG_FFDC      _at_ 0xFFDC;


BYTE xdata MCU_WATCHDOG_TIMER_FFEA      _at_ 0xFFEA;
BYTE xdata MCU_CTRL_FFED                _at_ 0xFFED;
BYTE xdata MCU_CLOCK_CTRL_FFEE          _at_ 0xFFEE;

BYTE xdata MCU_SCA_INF_CTRL_FFF3        _at_ 0xFFF3;
BYTE xdata MCU_SCA_INF_ADDR_FFF4        _at_ 0xFFF4;
BYTE xdata MCU_SCA_INF_DATA_FFF5        _at_ 0xFFF5;

BYTE xdata MCU_BANK_SWITCH_CTRL_FFFC    _at_ 0xFFFC;
BYTE xdata MCU_BANK_START_FFFD          _at_ 0xFFFD;
BYTE xdata MCU_BANK_SEL_FFFE            _at_ 0xFFFE;

BYTE xdata MCU_FAST_READ_OP_CODE_FF6B   _at_ 0xFF6B;
BYTE xdata MCU_READ_INSTRUCTION_FF6C    _at_ 0xFF6C;
BYTE xdata MCU_CEN_CTRL_FF76            _at_ 0xFF76;


BYTE xdata MCU_ADC_ACONTROL_FF08			_at_ 0xFF08;
BYTE xdata MCU_ADC_A0_CONVERT_RESULT_FF09	_at_ 0xFF09;	
BYTE xdata MCU_ADC_A1_CONVERT_RESULT_FF0A	_at_ 0xFF0A;	
BYTE xdata MCU_ADC_A2_CONVERT_RESULT_FF0B	_at_ 0xFF0B;	
BYTE xdata MCU_ADC_A3_CONVERT_RESULT_FF0C	_at_ 0xFF0C;	
BYTE xdata MCU_ADC_A4_CONVERT_RESULT_FF0D	_at_ 0xFF0D;	
BYTE xdata MCU_ADC_BCONTROL_FF0E			_at_ 0xFF0E;	
BYTE xdata TARGET0_HIGH_VALUE_FF10 			_at_ 0xFF10;
BYTE xdata TARGET1_HI_VALUE_FF11 			_at_ 0xFF11;
BYTE xdata TARGET2_HI_VALUE_FF12 			_at_ 0xFF12;
BYTE xdata MEAS_T_LO_VALUE_FF13 			_at_ 0xFF13;
BYTE xdata TARGET_MEAS_LO_VALUE_FF14 		_at_ 0xFF14;
BYTE xdata ADC_B0H_convert_result_FF15      _at_ 0xFF15;
BYTE xdata ADC_B1H_convert_result_FF16      _at_ 0xFF16;
BYTE xdata ADC_B2H_convert_result_FF17      _at_ 0xFF17;
BYTE xdata ADC_BxL_convert_result_FF18      _at_ 0xFF18;

//-----------Irda-----20070625-----------------------
//=======================================

BYTE xdata MCU_IR_CTRL1_FF80			_at_	0xFF80;
BYTE xdata MCU_IR_DEBOUNCE_FF81		_at_	0xFF81;
BYTE xdata MCU_IR_BURST_LENGTH_FF82	_at_	0xFF82;
BYTE xdata MCU_IR_SILENCE_LENGTH_FF83	_at_	0xFF83;
BYTE xdata MCU_IR_REPEAT_LENGTH_FF84	_at_	0xFF84;
BYTE xdata MCU_IR_MOD_LENGTH_FF85		_at_	0xFF85;
BYTE xdata MCU_IR_DATA0_LENGTH_FF86	_at_	0xFF86;
BYTE xdata MCU_IR_DATA1_LENGTH_FF87	_at_	0xFF87;
BYTE xdata MCU_IR_CTRL2_FF88			_at_	0xFF88;
BYTE xdata MCU_IR_STATUS_FF89			_at_	0xFF89;
BYTE xdata MCU_IR_DATA0_FF8A			_at_	0xFF8A;
BYTE xdata MCU_IR_DATA1_FF8B			_at_	0xFF8B;
BYTE xdata MCU_IR_DATA2_FF8C			_at_	0xFF8C;
BYTE xdata MCU_IR_DATA3_FF8D			_at_	0xFF8D;
BYTE xdata MCU_IR_DATA4_FF8E			_at_	0xFF8E;
BYTE xdata MCU_IR_DATA5_FF8F			_at_	0xFF8F;

BYTE xdata MCU_IR_ONE_CMD_TIME_FF90	_at_	0xFF90;
BYTE xdata MCU_IR_IDLE_TIME_FF91		_at_	0xFF91;
BYTE xdata MCU_IR_CTRL3_FF92			_at_	0xFF92;
BYTE xdata MCU_IR_INTRQ_FF93			_at_	0xFF93;


//wtao add
//BYTE xdata MCU_EX                                         _at_ 0xFF94;

#endif

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CMcuInitial(void);

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------


#if(_MCU_TYPE == _REALTEK_RTD3580D_EMCU)		   

extern BYTE xdata _NOT_USE_REG;
extern BYTE xdata MCU_IRQ_PRIORITY_FF01;
//extern BYTE xdata MCU_PORT6_OE_FF04;

extern BYTE xdata MCU_THRESHOLD_VALUE_FF0F;//new add

extern BYTE xdata MCU_ADC_DDC_ENA_FF1B;
extern BYTE xdata MCU_DVI_DDC_ENA_FF1E;
extern BYTE xdata MCU_DDCRAM_PART_FF21;

extern BYTE xdata MCU_I2C_SET_SLAVE_FF23;
extern BYTE xdata MCU_I2C_SUB_IN_FF24;
extern BYTE xdata MCU_I2C_DATA_IN_FF25;
extern BYTE xdata MCU_I2C_DATA_OUT_FF26;
extern BYTE xdata MCU_I2C_STATUS_FF27;
extern BYTE xdata MCU_I2C_IRQ_CTRL_FF28;
extern BYTE xdata MCU_I2C_STATUS2_FF29;
extern BYTE xdata MCU_I2C_IRQ_CTRL2_FF2A;
extern BYTE xdata MCU_I2C_CHANNEL_CTRL_FF2B;
extern BYTE xdata MCU_HDMI_DDC_ENA_FF2C;

extern BYTE xdata MCU_PWML_FF46;
extern BYTE xdata MCU_PWM_EN_FF48;
extern BYTE xdata MCU_PWM0H_DUT_FF4A;
extern BYTE xdata MCU_PWM1H_DUT_FF4B;
extern BYTE xdata MCU_PWM01L_DUT_FF4C;

extern BYTE xdata MCU_PWM2H_DUT_FF4D;
extern BYTE xdata MCU_PWM3H_DUT_FF4E;
extern BYTE xdata MCU_PWM23L_DUT_FF4F;

extern BYTE xdata MCU_PWM4H_DUT_FF50;
extern BYTE xdata MCU_PWM5H_DUT_FF51;
extern BYTE xdata MCU_PWM45L_DUT_FF52;


extern BYTE xdata MCU_COMMON_INST_EN_FF60;
extern BYTE xdata MCU_COMMON_OP_CODE_FF61;
extern BYTE xdata MCU_WREN_OP_CODE_FF62;
extern BYTE xdata MCU_EWSR_OP_CODE_FF63;
extern BYTE xdata MCU_FLASH_PROG_ISP0_FF64;
extern BYTE xdata MCU_FLASH_PROG_ISP1_FF65;
extern BYTE xdata MCU_FLASH_PROG_ISP2_FF66;
extern BYTE xdata MCU_COMMON_INST_RD_PT0_FF67;
extern BYTE xdata MCU_COMMON_INST_RD_PT1_FF68;
extern BYTE xdata MCU_COMMON_INST_RD_PT2_FF69;

extern BYTE xdata MCU_READ_OP_CODE_FF6A;
extern BYTE xdata MCU_FAST_READ_OP_CODE_FF6B;
extern BYTE xdata MCU_PROG_OP_CODE_FF6D;
extern BYTE xdata MCU_PROG_INST_FF6F;
extern BYTE xdata MCU_PROG_DATA_PORT_FF70;
extern BYTE xdata MCU_PROG_LEN_FF71;
extern BYTE xdata MCU_CRC_END_ADDR0_FF72;
extern BYTE xdata MCU_CRC_END_ADDR1_FF73;
extern BYTE xdata MCU_CRC_END_ADDR2_FF74;

extern BYTE xdata MCU_PIN_SHARE_CTRL00_FF96;
extern BYTE xdata MCU_PIN_SHARE_CTRL01_FF97;
extern BYTE xdata MCU_PIN_SHARE_CTRL02_FF98;
extern BYTE xdata MCU_PIN_SHARE_CTRL03_FF99;
extern BYTE xdata MCU_PIN_SHARE_CTRL04_FF9A;
extern BYTE xdata MCU_PIN_SHARE_CTRL05_FF9B;
extern BYTE xdata MCU_PIN_SHARE_CTRL06_FF9C;
extern BYTE xdata MCU_PIN_SHARE_CTRL07_FF9D;
extern BYTE xdata MCU_PIN_SHARE_CTRL08_FF9E;
extern BYTE xdata MCU_PIN_SHARE_CTRL09_FF9F;
extern BYTE xdata MCU_PIN_SHARE_CTRL0A_FFA0;
extern BYTE xdata MCU_PIN_SHARE_CTRL0B_FFA1;
extern BYTE xdata MCU_PIN_SHARE_CTRL0C_FFA2;
extern BYTE xdata MCU_PIN_SHARE_CTRL0D_FFA3;
extern BYTE xdata MCU_PIN_SHARE_CTRL0E_FFA4;
extern BYTE xdata MCU_PIN_DRIVING_CTRL10_FFA6;

extern BYTE xdata MCU_PORT_READ_CTRL_FFC0;
extern BYTE xdata MCU_PORT52_PIN_REG_FFC1;
extern BYTE xdata MCU_PORT53_PIN_REG_FFC2;
extern BYTE xdata MCU_PORT54_PIN_REG_FFC3;
extern BYTE xdata MCU_PORT55_PIN_REG_FFC4;
extern BYTE xdata MCU_PORT56_PIN_REG_FFC5;
extern BYTE xdata MCU_PORT57_PIN_REG_FFC6;
extern BYTE xdata MCU_PORT60_PIN_REG_FFC7;
extern BYTE xdata MCU_PORT61_PIN_REG_FFC8;
extern BYTE xdata MCU_PORT62_PIN_REG_FFC9;
extern BYTE xdata MCU_PORT63_PIN_REG_FFCA;
extern BYTE xdata MCU_PORT64_PIN_REG_FFCB;
extern BYTE xdata MCU_PORT65_PIN_REG_FFCC;
extern BYTE xdata MCU_PORT66_PIN_REG_FFCD;
extern BYTE xdata MCU_PORT67_PIN_REG_FFCE;
extern BYTE xdata MCU_PORT70_PIN_REG_FFCF;
extern BYTE xdata MCU_PORT71_PIN_REG_FFD0;
extern BYTE xdata MCU_PORT72_PIN_REG_FFD1;
extern BYTE xdata MCU_PORT73_PIN_REG_FFD2;
extern BYTE xdata MCU_PORT74_PIN_REG_FFD3;
extern BYTE xdata MCU_PORT75_PIN_REG_FFD4;
extern BYTE xdata MCU_PORT76_PIN_REG_FFD5;
extern BYTE xdata MCU_PORT80_PIN_REG_FFD6;
extern BYTE xdata MCU_PORT81_PIN_REG_FFD7;
extern BYTE xdata MCU_PORT90_PIN_REG_FFD8;
extern BYTE xdata MCU_PORT91_PIN_REG_FFD9;
extern BYTE xdata MCU_PORT92_PIN_REG_FFDA;
extern BYTE xdata MCU_PORT93_PIN_REG_FFDB;
extern BYTE xdata MCU_PORT94_PIN_REG_FFDC;

extern BYTE xdata MCU_WATCHDOG_TIMER_FFEA;
extern BYTE xdata MCU_CTRL_FFED;
extern BYTE xdata MCU_CLOCK_CTRL_FFEE;

extern BYTE xdata MCU_SCA_INF_CTRL_FFF3;
extern BYTE xdata MCU_SCA_INF_ADDR_FFF4;
extern BYTE xdata MCU_SCA_INF_DATA_FFF5;

extern BYTE xdata MCU_BANK_SWITCH_CTRL_FFFC;
extern BYTE xdata MCU_BANK_START_FFFD;
extern BYTE xdata MCU_BANK_SEL_FFFE;

//-----------Irda-----20070625-----------------------
//=======================================
extern BYTE xdata MCU_IR_CTRL1_FF80;					
extern BYTE xdata MCU_IR_DEBOUNCE_FF81;				
extern BYTE xdata MCU_IR_BURST_LENGTH_FF82;					
extern BYTE xdata MCU_IR_SILENCE_LENGTH_FF83;					
extern BYTE xdata MCU_IR_REPEAT_LENGTH_FF84;					
extern BYTE xdata MCU_IR_MOD_LENGTH_FF85;				
extern BYTE xdata MCU_IR_DATA0_LENGTH_FF86;					
extern BYTE xdata MCU_IR_DATA1_LENGTH_FF87;					
extern BYTE xdata MCU_IR_CTRL2_FF88;					
extern BYTE xdata MCU_IR_STATUS_FF89;					
extern BYTE xdata MCU_IR_DATA0_FF8A;					
extern BYTE xdata MCU_IR_DATA1_FF8B;					
extern BYTE xdata MCU_IR_DATA2_FF8C;					
extern BYTE xdata MCU_IR_DATA3_FF8D;					
extern BYTE xdata MCU_IR_DATA4_FF8E;					
extern BYTE xdata MCU_IR_DATA5_FF8F;					

extern BYTE xdata MCU_IR_ONE_CMD_TIME_FF90;			
extern BYTE xdata MCU_IR_IDLE_TIME_FF91;				
extern BYTE xdata MCU_IR_CTRL3_FF92;				
extern BYTE xdata MCU_IR_INTRQ_FF93;				


extern BYTE xdata MCU_ADC_ACONTROL_FF08;					
extern BYTE xdata MCU_ADC_A0_CONVERT_RESULT_FF09;	
extern BYTE xdata MCU_ADC_A1_CONVERT_RESULT_FF0A;	
extern BYTE xdata MCU_ADC_A2_CONVERT_RESULT_FF0B;	
extern BYTE xdata MCU_ADC_A3_CONVERT_RESULT_FF0C;	
extern BYTE xdata MCU_ADC_A4_CONVERT_RESULT_FF0D;	
extern BYTE xdata MCU_ADC_BCONTROL_FF0E;
extern BYTE xdata TARGET0_HIGH_VALUE_FF10;
extern BYTE xdata TARGET1_HI_VALUE_FF11;
extern BYTE xdata TARGET2_HI_VALUE_FF12;
extern BYTE xdata MEAS_T_LO_VALUE_FF13;
extern BYTE xdata TARGET_MEAS_LO_VALUE_FF14;

extern BYTE xdata ADC_B0H_convert_result_FF15;
extern BYTE xdata ADC_B1H_convert_result_FF16;
extern BYTE xdata ADC_B2H_convert_result_FF17;
extern BYTE xdata ADC_BxL_convert_result_FF18;



#if(_HDMI_EDID==_ON)
extern BYTE xdata MCU_DDCRAM_HDMI[256];
#endif

#if(_DVI_EDID==_ON)
extern BYTE xdata MCU_DDCRAM_DVI[256];
#endif

#if _VGA_EDID
extern BYTE xdata MCU_DDCRAM_VGA[128];
#endif

#endif  // End of #if(_MCU_TYPE == _REALTEK_RTD3580D_EMCU)

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CMcuInitial(void);

#endif



//----------------------------------------------------------------------------------------------------

