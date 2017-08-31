
#if(_TV_CHIP == _TN835CPF)

//-------------------------------------------------------------------------------------
// Tuner support tv type
#define _TV_NTSC_M_SUPPORT       _TV_TYPE_SUPPORT        // 60Hz Sound 4.5M  NTSC M
#define _TV_NTSC_4_BG_SUPPORT    _TV_TYPE_NOT_SUPPORT    // 60Hz Sound 5.5M  NTSC 4/BG
#define _TV_NTSC_4_DK_SUPPORT    _TV_TYPE_NOT_SUPPORT    // 60Hz Sound 6.5M  NTSC 4/DK
#define _TV_NTSC_4_I_SUPPORT     _TV_TYPE_NOT_SUPPORT    // 60Hz Sound 6.0M  NTSC 4/I
#define _TV_PAL_M_SUPPORT        _TV_TYPE_NOT_SUPPORT    // 60Hz Sound 4.5M  PAL M

#define _TV_PAL_BG_SUPPORT       _TV_TYPE_SUPPORT        // 50Hz Sound 5.5M  PAL B/G
#define _TV_PAL_I_SUPPORT        _TV_TYPE_SUPPORT        // 50Hz Sound 6.0M  PAL I
#define _TV_PAL_DK_SUPPORT       _TV_TYPE_SUPPORT        // 50Hz Sound 6.5M  PAL D/K
#define _TV_PAL_N_SUPPORT        _TV_TYPE_SUPPORT        // 50Hz Sound 4.5M  PAL N

#define _TV_SECAM_BG_SUPPORT     _TV_TYPE_NOT_SUPPORT    // 50Hz Sound 5.5M  SECAM B/G
#define _TV_SECAM_DK_SUPPORT     _TV_TYPE_NOT_SUPPORT    // 50Hz Sound 6.5M  SECAM D/K
#define _TV_SECAM_L_SUPPORT      _TV_TYPE_NOT_SUPPORT    // 50Hz Sound 6.5M  SECAM L
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
#define _TUNER_HIGH_BAND         0x00  // UHF

//-------------------------------------------------------------------------------------
#define _TUNER_DK                0x0c
#define _TUNER_I                 0x08
#define _TUNER_BG                0x04
#define _TUNER_MN                0x00

//-------------------------------------------------------------------------------------
#define _TUNER_BP                20//16 // (1000/62.5)
#define _FM_TUNER_BP             20//16 // (1000/62.5)

#define _PIF_FREQ                38900  // KHz

#define _VHF_LOW_BAND            ((148.25 + (WORD)(_PIF_FREQ/1000)) * _TUNER_BP)
#define _VHF_HIGH_BAND           ((467.25 + (WORD)(_PIF_FREQ/1000)) * _TUNER_BP)

#define _MAX_TV_TYPE             _TV_SECAM_DK

#define _MAX_FREQ                ((866.25 + (WORD)(_PIF_FREQ/1000)) * _TUNER_BP)
#define _MIN_FREQ                ((44.25 + (WORD)(_PIF_FREQ/1000)) * _TUNER_BP)//((48.25 + (WORD)(_PIF_FREQ/1000)) * _TUNER_BP)

#define _NORMAL_TV_TYPE          _TV_PAL_I


#define _FM_DEVICE               _OFF

#define _NTSC_SEARCH_TABLE       _DISABLE

#endif // #if(_TV_CHIP == _TN835CPF)

