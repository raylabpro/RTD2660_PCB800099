#if(_OSD_TYPE == _OSD003)


#define OSD_SLIDER(pos)			OSDSlider(ROW(2), COL(3), LENGTH(16), pos, 100,0xe0)
#define OSD_TITLE_OUT(str)		CCenterTextout(str, COL(14), ROW(0))
#define OSD_CLEAR_MENU()		OSDClear(ROW(0), HEIGHT(ROW_COUNT), COL(0), WIDTH(COL_WIDTH), 0x00, BYTE_DISPLAY)

#define _SEL_CLEAR					0x00
#define _SEL_SELECT					0x3B


#ifdef __OSDDRAW003__

bit m_fResetMenuState = 0;

#else

extern bit m_fResetMenuState;

extern BYTE code tOSDMenuFunc;

#endif


// extand function & Var
bit CEnable(void);
bit CDisable(void);
bit CMITVEnable(void);
bit CPanelLRUD(void);
bit CTVSourceEnable(void);
bit CVideoEnable(void);
bit CVideoNTSCEnable(void);
bit CVgaEnable(void);
bit MDisplayRatioEnable(void);
bit CTVEnable(void);


void OSDSlider(unsigned char row, unsigned char col, unsigned char length, unsigned char value, unsigned char range,
                unsigned char color);



void DrawContrast(void);
void DrawBrightness(void);
void DrawHue(void);
void DrawSaturation(void);

void DrawSystem(void);
void DrawAutoSearch(void);
void DrawManualSearch(void);
void DrawTuning(void);
void DrawChannel(void);
void DrawVolume(void);
void DrawLanguage(void);
void DrawSource(void);
void DrawLRSwap(void);
void DrawUDSwap(void);
void DrawDisplayRatio(void);
void DrawReset(void);
void DrawExit(void);


void MAdjustContrast(BYTE ucMode);
void MAdjustBrightness(BYTE ucMode);
void MAdjustHue(BYTE ucMode);
void MAdjustSaturation(BYTE ucMode);

void MAdjustSystem(BYTE ucMode);
void CShowFreq(WORD iFreqN);
void MAdjustAutoSearch(BYTE ucMode);
void MAdjustManualSearch(BYTE ucMode);
void MAdjustTuning(BYTE ucMode);
void MAdjustChannel(BYTE ucMode);
void MAdjustVolume(BYTE ucMode);
void MAdjustSource(BYTE ucMode);
void MAdjustFM(BYTE LR);
void MAdjustLRSwap(BYTE ucMode);
void MAdjustUDSwap(BYTE ucMode);
void MAdjustDisplayRatio(BYTE ucMode);
void MAdjustReset(BYTE ucMode);
void DrawMainMenu(void);
void LoadLanguageFont(void);
void MAdjustLanguage(BYTE ucMode);
void CShowAutoSerachTotal(BYTE ucSearchTotal);
void CShowAutoSearchSliderInOSD(WORD ucCurrentValue);
bit CKeyStopAutoSearch(void);
// Extent function define
extern void MMenuNoneProc(void);
extern void MMenuNoneEnterSubMenu(void);
//---------------------------------------------------------------------------
// MainMenu
extern void MMainMenuProc(void);
extern void MMainMenuValueAdj(BYTE ucMode);
extern void MMainMenuMenuAdj(BYTE ucMode);
extern void MMainMenuEnterSubMenu(void);
extern void MMainMenuReturnUpMenu(void);








#endif		//#if(_OSD_TYPE == _OSD003)
