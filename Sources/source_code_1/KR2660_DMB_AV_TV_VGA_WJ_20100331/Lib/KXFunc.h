extern BYTE code t7313Test[];

#if(AUDIO_TYPE == _AUDIO_SC7313)
void CSc7313MuteOn(void);
void CSetSc7313Volume(BYTE ucVolume);
void CSelect7313SoundChannel(BYTE ucChannel);
void CSetAudioProcessor(BYTE ucBalance, BYTE ucBass, BYTE ucTreble) small;
#endif 


void CMuteOn(void);
void CMuteOff(void);
void CSetVolume(void);

bit kx_CVideoModeDetect(void);
bit kx_CVideoIsChange(void);
void kx_CWriteTuner(BYTE *Array);
BYTE kx_CReadIfPllDM(void);
bit bCheckTuner(BYTE TunerAddr);
void CSetPWM(BYTE PWMId, WORD Value);

void CWriteDisable(void);
void kx_CSetTVFrameSync(void);
void CSetDivMcode(BYTE* ucDiv, WORD* iMcode);
void CAdjustTVPQ(BYTE ucLevel);
void CVideoSetVDCSaturation(BYTE ucValue);
void CPowerDownScaler(void);



