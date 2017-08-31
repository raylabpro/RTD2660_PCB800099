

// Definitions for auto power down
#define _ONE_MINUTE_COUNT            60000  // On minute count 1ms*60000 = 1 minute

//----------------------------------------------------------
// For show tv number option
#define _SHOW_CH_TV_NUMBER           0x01
#define _SHOW_CH_TV_TYPE             0x02
#define _SHOW_CH_SOUND_TYPE          0x04

//----------------------------------------------------------
//Definitions for change channel Method
#define _CHANGE_CHANNEL_M1           0   // Normal Method
#define _CHANGE_CHANNEL_M2           1

#define _CHANGE_CHANNEL_MTD          _CHANGE_CHANNEL_M2
                               
//----------------------------------------------------------
//Definitions for change channel display Method
#define _CHANGE_CHANNEL_DISP_M1      0   // Normal
#define _CHANGE_CHANNEL_DISP_M2      1   // Show blue screen
#define _CHANGE_CHANNEL_DISP_M3      2   // Show black screen

#define _CHANGE_CHANNEL_DISP_MTD     _CHANGE_CHANNEL_DISP_M3//_CHANGE_CHANNEL_DISP_M1
                                               
//----------------------------------------------------------
#define _AUTO_SEARCH_METHOD_0        0   // Normal,search channel show blue screen
#define _AUTO_SEARCH_METHOD_1        1   // Lock channel show channel picture
#define _AUTO_SEARCH_TEST            2   // Teset autosearch

#define _AUTO_SERACH_METHOD          _AUTO_SEARCH_METHOD_0

//----------------------------------------------------------
//Definitions for change channel
#define _PREV_CHANNEL                0
#define _NEXT_CHANNEL                1


//----------------------------------------------------------
//Definitions for tuner mute on/off
#define _TUNER_MUTE_ON               1
#define _TUNER_MUTE_OFF              0

//----------------------------------------------------------
#define _TV_TYPE_SUPPORT             1       // Support this type
#define _TV_TYPE_NOT_SUPPORT         0       // Not support this type


//----------------------------------------------------------
#define _TV_AFC_START                0
#define _TV_AFC_TIMEOUT              20      // +-1Mhz -->Step size 50Khz
#define _TV_AFC_STOP                 (_TV_AFC_TIMEOUT+5)
#define _TV_AFC                      _DISABLE

//----------------------------------------------------------
// Definitions for TV chip
#define _TV_NONE              0       // 0:No tv chip
#define _TV_JS_6B1            1       // 1:EYTYANT JS_6B1/111 for PAL B/G,PAL I,PAL D/K,NTSC M/N
#define _TV_JS_6B2            2
#define _TV_TDQ_6F6           3       // 2:XuGuang TDQ-6F6/T126CW
#define _TNF_8337             4       // 3:TNF 8337-BFD
#define _TNJ_8355             5       // 4:TNJ 8366-CF
#define _TV_JS_6AM            6       // 6:EYTYANT JS_6B1/111 for PAL B/G,PAL I,PAL D/K,NTSC M/N
#define _TNJ7359_MF           7
#define _TN835CPF	          8
#define _CDT_3FP212		  	  9
#define _CDT_3FP212_9886      10
#define _TV_XF_6AC            11

//--------------------------------------------------
// Definitions for TV color
//--------------------------------------------------
#define _TV_NTSC_M            0x01    // 60Hz Sound 4.5M  NTSC M
#define _TV_NTSC_4_BG         0x02    // 60Hz Sound 5.5M  NTSC 4/BG
#define _TV_NTSC_4_DK         0x03    // 60Hz Sound 6.5M  NTSC 4/DK
#define _TV_NTSC_4_I          0x04    // 60Hz Sound 6.0M  NTSC 4/I
#define _TV_PAL_M             0x05    // 60Hz Sound 4.5M  PAL M

#define _TV_PAL_BG            0x06    // 50Hz Sound 5.5M  PAL B/G
#define _TV_PAL_I             0x07    // 50Hz Sound 6.0M  PAL I
#define _TV_PAL_DK            0x08    // 50Hz Sound 6.5M  PAL D/K
#define _TV_PAL_N             0x09    // 50Hz Sound 4.5M  PAL N

#define _TV_SECAM_BG          0x0a    // 50Hz Sound 5.5M  SECAM B/G
#define _TV_SECAM_DK          0x0b    // 50Hz Sound 6.5M  SECAM D/K
#define _TV_SECAM_L           0x0c    // 50Hz Sound 6.5M  SECAM L
#define _TV_SECAM_LL          0x0d    // 50Hz Sound 6.5M  Secam L'


//--------------------------------------------------
//  TV IF PLL Demodulator definitions
//--------------------------------------------------
#define _IF_PLL_DE_9886       0       // Philips TDA9886
#define _IF_PLL_DE_1338       1       // Toshiba TB1338/TB1351
#define _IF_PLL_DE_9885       2       // Philips TDA9885  // No Secam
#define _IF_PLL_DE_135X       3       // Toshiba TB135X   // No Secam

//--------------------------------------------------
// Definition for search channel
//--------------------------------------------------
#define _TUNNING_MODE         0x00
#define _NORMAL_MODE          0x80


//--------------------------------------------------
// For FM freq
//--------------------------------------------------
#define _FM_MIN_FREQ          ((87.5 + (WORD)(_PIF_FREQ/1000)) * _FM_TUNER_BP)
#define _FM_MAX_FREQ          ((109 + (WORD)(_PIF_FREQ/1000)) * _FM_TUNER_BP)



extern BYTE idata ucTVType;

#if(_VIDEO_TV_SUPPORT)

#ifndef __TV__
#define __TV__

extern bit bBuleBackGround;
extern bit bChangeChannel;
extern BYTE xdata ucPrevChannel;
extern WORD xdata ucCurrentInputNumber;
extern BYTE xdata ucCurrentInputState;
extern BYTE xdata ucAudioState;
extern BYTE ucAddrIfPllDM;
#if(_TV_AFC)
extern BYTE AFCState;
extern WORD CurrAFCFreq;
#endif


void CForceBackGroundToBlack(void);

void kx_CI2CWriteIfPllDM(BYTE ucTvType, const bit bTunerMute, const BYTE ucAFTMode);
void kx_CSetTuner(BYTE ucTunerAddress, WORD Freq);
void CTvAutoSearch(void) small;
void CSetTVChannel(const BYTE ucCurrentChannel);
void CChangeChannel(bit bNext);

BYTE CloadMaxChannelNumber(void);
void CManualSearch(const bit bSearchAction, const BYTE ucCurrentChannel) small;
void CTuningCurrentChannel(const bit bSearchAction, const BYTE ucCurrentChannel) small;
/*
BYTE CLoadChannelSoundType(const BYTE ucCurrentChannel);
void CSaveChannelSoundType(const BYTE ucCurrentChannel, const BYTE ucSoundType);
BYTE CLoadChannelColorType(const BYTE ucCurrentChannel);
void CSaveChannelColorType(const BYTE ucCurrentChannel, const BYTE TVType);
WORD CLoadChannelFreq(const BYTE ucCurrentChannel);
void CSaveChannelFreq(const WORD iFreq, const BYTE ucCurrentChannel);
BYTE CLoadChannelSoundType(const BYTE ucCurrentChannel);
bit  CLoadChannelSkip(const BYTE ucCurrentChannel);
void CSaveChannelSkip(const bit bSkip, const BYTE ucCurrentChannel);
*/
void CInitTV(void);
BYTE CDetectTVSignalType(void);
//void CSaveChannelData(const WORD iFreq, const BYTE ucSound, const BYTE ucChannelNumber);
WORD CLockChannel(WORD iStartFreq, const bit bCLockMode) small;
void CModeResetTVMode(void);
void CAudioCtrl(void);
void CChangeFM(void);

#if(_SLEEP_FUNC)
void CShowTimer(void) small;
#endif

#if (_TV_AFC)
void CTVAFC(void);
#endif

#endif    //#ifndef __TV__
#endif 
