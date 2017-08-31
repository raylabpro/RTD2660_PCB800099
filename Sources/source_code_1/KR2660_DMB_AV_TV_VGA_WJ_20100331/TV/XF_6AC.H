
#if(_TV_CHIP == _TV_XF_6AC)

//-------------------------------------------------------------------------------------
// Tuner support tv type
#define _TV_NTSC_M_SUPPORT       _TV_TYPE_SUPPORT        // 60Hz Sound 4.5M  NTSC M
#define _TV_NTSC_4_BG_SUPPORT    _TV_TYPE_NOT_SUPPORT    // 60Hz Sound 5.5M  NTSC 4/BG
#define _TV_NTSC_4_DK_SUPPORT    _TV_TYPE_NOT_SUPPORT    // 60Hz Sound 6.5M  NTSC 4/DK
#define _TV_NTSC_4_I_SUPPORT     _TV_TYPE_NOT_SUPPORT    // 60Hz Sound 6.0M  NTSC 4/I
#define _TV_PAL_M_SUPPORT        _TV_TYPE_SUPPORT    // 60Hz Sound 4.5M  PAL M

#define _TV_PAL_BG_SUPPORT       _TV_TYPE_SUPPORT        // 50Hz Sound 5.5M  PAL B/G
#define _TV_PAL_I_SUPPORT        _TV_TYPE_SUPPORT        // 50Hz Sound 6.0M  PAL I
#define _TV_PAL_DK_SUPPORT       _TV_TYPE_SUPPORT        // 50Hz Sound 6.5M  PAL D/K
#define _TV_PAL_N_SUPPORT        _TV_TYPE_SUPPORT    // 50Hz Sound 4.5M  PAL N

#if(_IF_PLL_DE_CHIP == _IF_PLL_DE_9886)
#define _TV_SECAM_L_SUPPORT      _TV_TYPE_SUPPORT        // 50Hz Sound 6.5M  SECAM L
#else
#define _TV_SECAM_L_SUPPORT      _TV_TYPE_NOT_SUPPORT    // 50Hz Sound 6.5M  SECAM L
#endif
#define _TV_SECAM_BG_SUPPORT     _TV_TYPE_SUPPORT    // 50Hz Sound 5.5M  SECAM B/G
#define _TV_SECAM_DK_SUPPORT     _TV_TYPE_SUPPORT    // 50Hz Sound 6.5M  SECAM D/K
#define _TV_SECAM_LL_SUPPORT     _TV_TYPE_NOT_SUPPORT    // 50Hz Sound 6.5M  Secam L'

//-------------------------------------------------------------------------------------
//Tuner Setting
//Control Byte1
#define _TUNER_CP                1
#define _TUNER_RSA               0
#define _TUNER_RSB               0
#define _TUNER_OS                0

#define _TUNER_CONTROL_BYTE1     (0x88 | (_TUNER_CP << 6) | (_TUNER_RSA << 2) | (_TUNER_RSB << 1) | _TUNER_OS)

//Control Byte2
#define _TUNER_LOW_BAND          0x01  // VHFLOW
#define _TUNER_MID_BAND          0x02  // VHFHIGH
#define _TUNER_HIGH_BAND         0x08  // UHF

//Control Byte3
#define _TUNER_CONTROL_BYTE3     (_TUNER_CONTROL_BYTE1 | 0x10)

//Control Byte4
#define _TUNER_CONTROL_BYTE4     0x60

//-------------------------------------------------------------------------------------
//TDA9886 Setting
//PAL B/G,I,D/K
#define _TDA9886_B_DATA_PAL      0xd6                    // PAL B/G,I,D/K
#define _TDA9886_C_DATA_PAL      0x70                    // PAL B/G,I,D/K
#define _TDA9886_E_DATA_PAL_BG   0x09                    // 5.5M
#define _TDA9886_E_DATA_PAL_I    0x0A                    // 6.0M
#define _TDA9886_E_DATA_PAL_DK   0x0B                    // 6.5M

//NTSC M/N
#define _TDA9886_B_DATA_NTSC     0x16                    // NTSC M/N
#define _TDA9886_C_DATA_NTSC     0x30                    // NTSC M/N
#define _TDA9886_E_DATA_NTSC     0x08                    // 4.5M

//SECAM L
#define _TDA9886_B_DATA_SECAML   _TDA9886_B_DATA_PAL                    // SECAM L
#define _TDA9886_C_DATA_SECAML   _TDA9886_C_DATA_PAL                    // SECAM L
#define _TDA9886_E_DATA_SECAML   _TDA9886_E_DATA_PAL_I                    // 6.5M

//SECAM L'
#define _TDA9886_B_DATA_SECAMLL  0xC6                    // Not support SECAM L'
#define _TDA9886_C_DATA_SECAMLL  0x50                    // Not support SECAM L'
#define _TDA9886_E_DATA_SECAMLL  0x53                    // Not support SECAM L'

//-------------------------------------------------------------------------------------
#define _VHF_LOW_BAND            ((148.25 + (WORD)(_PIF_FREQ/1000)) * _TUNER_BP)    // Band select
#define _VHF_HIGH_BAND           ((467.25 + (WORD)(_PIF_FREQ/1000)) * _TUNER_BP)

#if(_IF_PLL_DE_CHIP == _IF_PLL_DE_9886)
#define _MAX_TV_TYPE             _TV_SECAM_DK
#else
#define _MAX_TV_TYPE             _TV_PAL_I
#endif
#define _MAX_FREQ                ((864.25 + (WORD)(_PIF_FREQ/1000)) * _TUNER_BP)
#define _MIN_FREQ                ((44.25 + (WORD)(_PIF_FREQ/1000)) * _TUNER_BP)

#define _NORMAL_TV_TYPE          _TV_PAL_I

#define _TUNER_BP                20
#define _FM_TUNER_BP             32
//33400,33900,34200,38000,38900,45750 KHz
#define _PIF_FREQ                38900  // KHz

#define _FM_DEVICE               _OFF

#define _NTSC_SEARCH_TABLE       _DISABLE

#endif // #if(_TV_CHIP == _CDT_3FP212_9886)


