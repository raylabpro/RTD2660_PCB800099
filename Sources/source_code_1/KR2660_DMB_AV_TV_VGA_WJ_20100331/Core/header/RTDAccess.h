/*=============================================
  * Copyright (c)      Realtek Semiconductor Corporation, 2005
  * All rights reserved.
  * ============================================ */
#ifdef __RTDACCESS__


#else


#endif


extern void CScalerSendAddr(BYTE ucAddr, bit bAutoInc);
extern void CScalerWrite(BYTE ucAddr, WORD usLength, BYTE *pArray, bit bAutoInc);
extern void CScalerRead(BYTE ucAddr, BYTE ucLength, BYTE *pArray, bit bAutoInc);
extern void CScalerWriteAmount(BYTE ucAddr, WORD usLength, BYTE ucValue, bit bAutoInc);
extern void CScalerSetByte(BYTE ucAddr, BYTE ucValue);
extern void CScalerSetDataPortByte(BYTE ucAddr, BYTE ucValue1, BYTE ucValue2);
extern void CScalerSetBit(BYTE ucAddr, BYTE ucAnd, BYTE ucOr);
extern void CScalerSetDataPortBit(BYTE ucAddr, BYTE ucValue, BYTE ucAnd, BYTE ucOr);
extern void CScalerPageSelect(BYTE page);
extern BYTE CScalerGetBit(BYTE ucAddr, BYTE ucAnd);
extern BYTE CScalerGetDataPortBit(BYTE ucAddr, BYTE ucValue, BYTE ucAnd);
extern void CScalerCodeW(BYTE *pArray);
extern void CScalerLoadFont(BYTE code *pArray, WORD usOffset, WORD usLength, BYTE ucPar);
extern void CScalerLoadFontInAbAddr(BYTE code *pArray, WORD usStartAddr, WORD usLength, BYTE ucPar);
extern void CScalerLoadHardwareVLCFont(BYTE *pArray, WORD usOffset);
extern BYTE CScalerGetVLD(void);
extern bit CScalerGetBitVLD(void);



