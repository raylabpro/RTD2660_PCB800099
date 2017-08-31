#ifdef __FUNCC__
#else
#endif


bit bChangeSource(void);
void CInitInputSource(void);
void CInitSoundChannel(BYTE ucChannel);
void DoSetBackColor(void);
void MemoryCpy(BYTE *Obj,BYTE *Src,BYTE ucCnt);
BYTE CGetInputSourceNum(BYTE ucInputSource);
void SetPanelLR(void);
void SetPanelUD(void);
void SetFM(void);
void CInitFM(void);
void CSetFMFreq(BYTE ucFreq);
void FMAudioTran(void);

