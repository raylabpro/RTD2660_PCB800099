

#if(_VIDEO_TV_SUPPORT)
#if(_IF_PLL_DE_CHIP == _IF_PLL_DE_1338 || _IF_PLL_DE_CHIP == _IF_PLL_DE_135X)
#define _TB1338_ADDR           0x86//0x96

//----------------------------------
// Definition for Secam L
//----------------------------------
#define _SECAML_MODE           1
#define _OTHER_MODE            0

//----------------------------------
// Definition for carrier select
//----------------------------------
#define _INTER_CARRIER        0x81
#define _SPLIT_CARRIER        0x01

//----------------------------------
// Definition for sound freq select
//----------------------------------
#define _SIF_4_5_MHZ          (0x03 << 3)
#define _SIF_5_5_MHZ          (0x00 << 3)
#define _SIF_6_0_MHZ          (0x01 << 3)
#define _SIF_6_5_MHZ          (0x02 << 3)


extern bit bFM;


void CInitialTB1338(void);
BYTE CReadTB1338(void);
//============================================================================== 
// ucMode:  _TUNNING_MODE/_NORMAL_MODE
// _TUNNING_MODE        0x00
// _NORMAL_MODE         0x80
// bSecamLMode:   1: TV is Secam L
// CarrierSelect: 0: Inter carrier    1: Split carrier
//============================================================================== 
void CSetPifFreq(const unsigned char ucAFTMode, const bit bSecamLMode, const unsigned int PifFreq,
                 const unsigned char CarrierSelect);
void CSetSoundFreq(const unsigned char ucSoundFreq);
void CFMInit(void);
#endif  // #if(_IF_PLL_DE_CHIP == _IF_PLL_DE_1338 || _IF_PLL_DE_CHIP == _IF_PLL_DE_135X)
#endif  // #if(_VIDEO_TV_SUPPORT)

