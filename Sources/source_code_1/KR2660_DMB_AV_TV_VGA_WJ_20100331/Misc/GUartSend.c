#define __GUART__

#include "Core\Header\Include.h"

#if(_UART_SND_EN == _ON)

//-------------------------------------------------------------------------
void CUartDelay(void)
{
/*   19200
     BYTE i;
     for(i=0;i<_UART_DELAY;i++)
     {
         _nop_();
     }
     _nop_();
     _nop_();
     _nop_();
     _nop_();
     _nop_();
     _nop_();
     _nop_();
     _nop_(); 
*/

	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();

}
//-------------------------------------------------------------------------
void CUartSend(BYTE c)
{
    ucUartSendData = c;
    
    EA = 0;
    // send begin
    UART_SEND(0);
    CUartDelay();
    
    UART_SEND(bSndBit0);
    CUartDelay();
    
    UART_SEND(bSndBit1);
    CUartDelay();
    
    UART_SEND(bSndBit2);
    CUartDelay();
    
    UART_SEND(bSndBit3);
    CUartDelay();
    
    UART_SEND(bSndBit4);
    CUartDelay();
    
    UART_SEND(bSndBit5);
    CUartDelay();
    
    UART_SEND(bSndBit6);
    CUartDelay();
    
    UART_SEND(bSndBit7);
    CUartDelay();
    
    // Send Stop 2 bit
    UART_SEND(1);
    CUartDelay();
    
    UART_SEND(1);
    CUartDelay();
    
    EA = 1;
}
//-------------------------------------------------------------------------
void CUartSendString(char* String)
{
     while(*String)
     {
         CUartSend(*String);
         String++;         
     }
}
//-------------------------------------------------------------------------
/*
void CUartFormatSendByte(BYTE Value)
{
     CUartSend(0xF0);
     CUartSend(Value);
}
//-------------------------------------------------------------------------
void CUartFormatSendWord(WORD Value)
{
     CUartSend(0xF1);
     CUartSend((Value >> 8) & 0xff);
     CUartSend(Value & 0xff);
}
//-------------------------------------------------------------------------
void CUartFormatSendDWord(DWORD Value)
{
     CUartSend(0xF2);
     CUartSend((Value >> 24) & 0xff);
     CUartSend((Value >> 16) & 0xff);
     CUartSend((Value >> 8) & 0xff);
     CUartSend(Value & 0xff);
}
//-------------------------------------------------------------------------
*/
void CUartSendWord(WORD Value)
{
     CUartSend(((Value / 10000) % 10) + '0');
     CUartSend(((Value / 1000) % 10) + '0');
     CUartSend(((Value / 100) % 10) + '0');
     CUartSend(((Value / 10) % 10) + '0');
     CUartSend((Value % 10) + '0');
}
//-------------------------------------------------------------------------
void CUartPrintf(char *str,WORD Value)
{
     CUartSendString(str);
     CUartSendWord(Value);
     CUartSendString("\r\n");
}
//-------------------------------------------------------------------------
/*
void CUartHex(BYTE Value)
{
       BYTE h,l;
       h = ((Value >> 4) & 0x0f);
       l = (Value & 0x0f);

       if(h > 9)
          h = h - 10 + 'A';
       else
          h += '0';

       if(l > 9)
          l = l - 10 + 'A';
       else
          l += '0';


       CUartSend(h);
       CUartSend(l);
       CUartSend(' ');
}  */
//-------------------------------------------------------------------------


#endif          //#if(_UART_SND_EN == _ON)
