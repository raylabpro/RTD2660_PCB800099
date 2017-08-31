#if(_OSD_TYPE == _OSD003)


// TV no signal show "No Signal" definition
#define _SHOW_TV_NO_SIGNAL          0

//---------------------------------------
// For change source method
#define _CHANGE_SOURCE_METHOD_0     0
#define _CHANGE_SOURCE_METHOD_1     1

#define _CHANGE_SOURCE_METHOD       _CHANGE_SOURCE_METHOD_0

//---------------------------------------
// Menu func define
#define CURRENT_MENU_ITEM			g_tMenuItem[ucOsdState]

//---- language type define--------------
#define ENGLISH                       0
#define LNG_CHI_S                   1
#define LNG_FRA                      2
#define LNG_ITA                       3
#define LNG_DEU                      4
#define LNG_ESP                      5
#define LNG_CHI_T                   6
#define LNG_JAP                      7
#define LNG_KOR                      8
#define LNG_RUS                      9
#define LNG_ARA                      10
#define LNG_THAI                     11

//---- language mask---------------------
// 请不要超过11国语言,OSD显示不到12国语言
#define ENGLISH_EN                  1  //英语
#define LNG_FRA_EN                  0  //法语
#define LNG_ITA_EN                  0  //意大利语
#define LNG_DEU_EN                  0  //德语
#define LNG_ESP_EN                  0  //西班牙语
#define LNG_CHI_S_EN                1  //中文简
#define LNG_CHI_T_EN                0  //中文繁
#define LNG_JAP_EN                  0  //日语
#define LNG_KOR_EN                  0  //韩语
#define LNG_RUS_EN                  0  //俄语
#define LNG_ARA_EN                  0  //阿拉伯语
#define LNG_THAI_EN                 0  //泰语

#define _LANGUAGE_CNT				2///12
#define _NOT_SHOW					0xFF

#define _ST_NORMAL					1
#define _ST_SELECT					2
#define _ST_DISABLE					3
#define _ST_ADJUST					4



#define _LF_COLOR_PAGE				0
#define _LF_ADJUST_PAGE				1
#define _LF_OSD_PAGE				2
#define _LF_TV_PAGE					3
#define _LF_FUNC_PAGE				4
#define _LF_SOUND_PAGE				5
#define _LF_OTHER					6

#define BEGIN(x)					x
#define END(x)						x


#ifdef __OSDPROC003__

bit bOSDOnScreen = 0;
bit bDrawMute    = 0;
#if(_SHOW_TV_NO_SIGNAL)
BYTE ucSignalOSDState = 0;
#endif
WORD code usLANGUAGE_MASK  =  ( ENGLISH_EN   << ENGLISH ) |
                              ( LNG_FRA_EN   << LNG_FRA ) |
                              ( LNG_ITA_EN   << LNG_ITA ) |
                              ( LNG_DEU_EN   << LNG_DEU ) |
                              ( LNG_ESP_EN   << LNG_ESP ) |
                              ( LNG_CHI_S_EN << LNG_CHI_S ) |
                              ( LNG_CHI_T_EN << LNG_CHI_T ) |  
                              ( LNG_JAP_EN   << LNG_JAP ) |
                              ( LNG_KOR_EN   << LNG_KOR ) |
                              ( LNG_RUS_EN   << LNG_RUS ) |
				  ( LNG_ARA_EN   << LNG_ARA ) |
				  ( LNG_THAI_EN   << LNG_THAI );


#if(_VIDEO_TV_SUPPORT)
BYTE ucNoSigCount = 0;
#endif
BYTE ucSourceTemp;

#if(_LOGO_ENABLE)
bit bLoadLogoFont = 0;
#endif

bit bLoadOtherFont = 0;    

#else
                         
extern bit bOSDOnScreen;
extern bit bDrawMute;
extern bit bLoadOtherFont;
#if(_SHOW_TV_NO_SIGNAL)
extern BYTE ucSignalOSDState;
#endif
extern BYTE ucSourceTemp;
extern WORD code usLANGUAGE_MASK;

#if(_LOGO_ENABLE)
extern bit bLoadLogoFont;
#endif



#endif
// extand function & Var


void COsdHandler(void);
void CNotUse(void);

void CKeyOSDMsgCover(void);

void COsdSystemFlowProc(void);
void COsdEventMsgProc(void);
void COsdDispFirstTimeLoadFont(void);

void COsdDispOsdTimerEvent(void);
void InitOsdFrame(void);
BYTE CFoundKeyMsgToOsdEvent(SKeyToOsdEvent *tMsgTable);
void CCoverKeyMsgToOsdEvent(SKeyToOsdEvent *tMsgTable,BYTE bUserPublicKeyEvnet);
void DbgShowOSDState(void);
void CShowNote(void);
void CShowNoSignal(void);
void CShowVisatech(void);
void CChangeSourceAvSv(void);
void ChangeDisplayMode(void);
void PanelLRSwap(void);
void PanelUDSwap(void);

BYTE AdjustMenuItem(BYTE ucBeginItem,BYTE ucEndItem,BYTE ucMode);
BYTE GetShowIndex(BYTE ucMenuItem,BYTE ucBeginItem,BYTE ucEndItem);
BYTE GetShowCount(BYTE ucBeginItem,BYTE ucEndItem);

void CShowTVNumber(BYTE ucNumber, BYTE ucOption);
void GotoContrastMenu(void);
void GotoSaturationMenu(void);
void GotoBrightnessMenu(void);
void GotoVolumeMenu(void);
void SetSleepTimer(void);
void CShowTimer(void) small;
void ChangeSourceReset(void);

void CChangePictureMode(void);
void EnterSCInputNum(void);
void MScInputChNumProc(void);
void SInceptNumber(const WORD ucNumber);
void SShowCurrentInputState(BYTE ucInputState);

void CDrawMuteState(void);
void CSetMuteState(void);
void ChangeSourceState(void);
void CFMControl(void);

#endif		//#if(_OSD_TYPE == _OSD003)

