#if(_MEMORY_LOCATION == _FLASH)

#ifdef __FLASH_KX_FUNC__
BYTE xdata g_szRandomSavePage[7];
BYTE xdata g_szFlashBuf[16];
#else
extern BYTE xdata g_szRandomSavePage[7];
extern BYTE xdata g_szFlashBuf[16];
#endif
#endif	//#if(_MEMORY_LOCATION == _EEPROM)

void FillFFToMemory(BYTE *Array,BYTE ucCnt);
bit CTimerPollingFlagProcForMcu(WORD usTimeout, BYTE *ucAddress, BYTE ucBit, bit bSuccess);

void FlashProtectEnable(void);
void FlashProtectDisable(void); 
void FlSetOpCode(void);
bit CFlashWRDis(void);
bit CFlashWREN(BYTE ucPage);
bit CFlashErase(BYTE ucPage);
void CFlashMovePage(BYTE ucObjPage,BYTE ucSrcPage);
// 一次固定存写 16 字节，ID CHECK SUM 占二个字节，所以只能存 14 BYTE
bit FLSaveData(BYTE ucPage,BYTE ID,BYTE FreeGroup);
bit FLLoadData(BYTE ucPage,BYTE ID);

void InitFlash(void);
BYTE FoundRandomPage(BYTE ucRandomPageIndex);
BYTE FoundEmptyRandomPage(void);
void InitRandomPage(BYTE ucPage,BYTE ucRandomPageIndex);


