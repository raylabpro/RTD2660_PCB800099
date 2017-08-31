//----------------------------------------------------------------------------------------------------
// ID Code      : Sync.h No.0001
// Update Note  :
//
//----------------------------------------------------------------------------------------------------
#if(_RS232_EN)

#define UartCMD_OFFSET1 			0x00
#define UartCMD_OFFSET2 			0xB0
#define UartCMD_OFFSET				UartCMD_OFFSET2

#define UartCMD_DebugModeEnter		(0x10 + UartCMD_OFFSET)
#define UartCMD_DebugModeExit		(0x11 + UartCMD_OFFSET)
#define UartCMD_CScalerRead			(0x20 + UartCMD_OFFSET)
#define UartCMD_CScalerWrite		(0x30 + UartCMD_OFFSET)
#define UartCMD_I2CRead				(0x21 + UartCMD_OFFSET)
#define UartCMD_I2CWrite 			(0x31 + UartCMD_OFFSET)

// not use
#define UartCMD_24C32Read       	(0x26 + UartCMD_OFFSET)
#define UartCMD_24C32Write      	(0x36 + UartCMD_OFFSET)
#define UartCMD_TunerRead			(0x24 + UartCMD_OFFSET)
#define UartCMD_TunerWrite			(0x34 + UartCMD_OFFSET)
#define UartCMD_FlashRead			(0x25 + UartCMD_OFFSET)

extern bit fInUartMode;

extern BIT fUartStart;
extern BIT fUartRxCmdSuccess;
extern BIT fUartDebugLoop;

extern BYTE xdata ucUartRxIndex;
extern BYTE xdata ucUartRxCount;
extern BYTE xdata pUartData[9];


void CUartInit(void);
void CSwitchToUart(void);
void CSwitchToI2C(void);
/*
void CUartPrintf(char *pStr,WORD usValue);
void CUartPrintfHex(BYTE ucValue);
void CUartPrintfDec(WORD usValue);
void CUartPutCharToScr(BYTE ch);
*/
void DebugPrintf(const BYTE code* pstr,BYTE value);
void CUartPutToScr(const BYTE ch,const BYTE mode);
void CUartPutCharToScr(BYTE ch);
void CUartHandler(void);
void UartCMDDebugModeExit(void);
void UartCMDDebugModeEnter(void);
void UartCMDScalerRead(void);
void UartCMDScalerWrite(void);

#endif
