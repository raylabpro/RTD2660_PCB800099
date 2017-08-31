#define _UART_SND_EN            _OFF


#if(_UART_SND_EN == _ON)

#define _BR19200                0
#define _BR115200               1

#define _BR_TYPE                _BR115200

#if(_BR_TYPE == _BR19200)
#define _UART_DELAY             11      // NOT READY
#elif(_BR_TYPE == _BR115200)
#define _UART_DELAY             6       // NOT READY
#endif

sbit _UART_IO = P3^4;           // 2660 Pin 111
#define UART_SEND(x)            _UART_IO = x

#ifdef __GUART__

// Not access this Variable
BYTE bdata ucUartSendData;

sbit bSndBit0 = ucUartSendData ^ 0;
sbit bSndBit1 = ucUartSendData ^ 1;
sbit bSndBit2 = ucUartSendData ^ 2;
sbit bSndBit3 = ucUartSendData ^ 3;
sbit bSndBit4 = ucUartSendData ^ 4;
sbit bSndBit5 = ucUartSendData ^ 5;
sbit bSndBit6 = ucUartSendData ^ 6;
sbit bSndBit7 = ucUartSendData ^ 7;

#else           //#ifdef __GUART__

#endif          //#ifdef __GUART__

void CUartDelay(void);
void CUartSend(BYTE c);

void CUartSendString(char* String);
void CUartFormatSendByte(BYTE Value);
void CUartFormatSendWord(WORD Value);
void CUartFormatSendDWord(DWORD Value);
   
void CUartSendWord(WORD Value);
void CUartPrintf(char *str,WORD Value);
void CUartHex(BYTE Value);

#else

#define CUartSendString(String)
#define CUartFormatSendByte(Value)
#define CUartFormatSendWord(Value)
#define CUartFormatSendDWord(Value)
   
#define CUartSendWord(Value)
#define CUartPrintf(str,Value)
#define CUartHex(Value)


#endif          //#if(_UART_SND_EN == _ON)
