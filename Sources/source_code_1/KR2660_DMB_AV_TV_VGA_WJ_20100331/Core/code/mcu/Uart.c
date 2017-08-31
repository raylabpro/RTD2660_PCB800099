//----------------------------------------------------------------------------------------------------
// ID Code      : Video.c No.0002
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#define __UART__

#include "Core\Header\Include.h"

#if(_RS232_EN)

bit fInUartMode = 0;

BIT fUartStart = 0;
BIT fUartRxCmdSuccess = 0;
BIT fUartDebugLoop = 0;

BYTE xdata ucUartRxIndex = 1;
BYTE xdata ucUartRxCount = 0;
BYTE xdata pUartData[9];

BYTE code tEnterDebugMode[] = {0x01,0x02,0x03,0x04};
BYTE code tExitDebugMode[] = {0x04,0x03,0x02,0x01};


//----------------------------------------------------------------------------
void CUartInit(void)
{
	WORD usTemp = 0xFFFF - (UINT32)27000 * 1000 / 19200 / 32;
	// Initialize SBuf to zero
	SBUF = 0x00;

	// Set to 8051 UART mode 1, refer to Page 2-43
	SCON = 0x50;

	// Set the baudrate refer to Timer2, Page 2-37
	T2CON = 0x34;

	//	Timer2's value is 65536 - (crystal / baud * 32)), Page 2-43
	RCAP2L = LOBYTE(usTemp);
	RCAP2H = HIBYTE(usTemp);

	//RCAP2L = 0xD4;	//0FFh , 0D4h	//19200
	//RCAP2H = 0xFF;	//0FFh , 0D4h	//19200

#if(_ACPOWERON_RS232)
	CTimerActiveTimerEvent(SEC(10), CSwitchToUart);
#endif
}
//----------------------------------------------------------------------------
void CSwitchToUart(void)
{
	BYTE i;
	bit fTest = 0;
	
	MCU_PIN_SHARE_CTRL00_FF96 |= 0xF8;
	ES = 1; // Enable UART's interrupt
	PS = 1; // Change UART's interrupt to high priority

	fInUartMode = 1;

    DebugPrintf("Swtich to Uart mode.\n",0x00);

    for(i=0;i<10;i++)
    {
		bLED1 = fTest;
		fTest = ~fTest;
		CTimerDelayXms(20);		
    }
    
}
//----------------------------------------------------------------------------
void CSwitchToI2C(void)
{
	BYTE i;
	bit fTest = 0;
	
	MCU_PIN_SHARE_CTRL00_FF96 &= 0x07;
	ES = 0; // Enable UART's interrupt
	PS = 0; // Change UART's interrupt to high priority	
	fInUartMode = 0;

    for(i=0;i<10;i++)
    {
		bLED2 = fTest;
		fTest = ~fTest;
		CTimerDelayXms(20);		
    }	
}
//----------------------------------------------------------------------------
void DebugPrintf(const BYTE code* pstr,BYTE value)
{
	BYTE i;
	char *p = pstr;

	for (i =0x00; *p != '\0'; i++)
    {
		if(*p == '\n')
		{
			CUartPutCharToScr('\r');
			CUartPutCharToScr(*p);
       	}
        else if(*p == '%')
		{
			switch(*(p+1))
			{
				case 'd':
					i++;
					p++;
					CUartPutToScr(value,1);
					break;
				case 'x':
					i++;
					p++;
					CUartPutToScr(value,2);
					break;
				case 'c':
					i++;
					p++;
					CUartPutCharToScr(value);
					break;	
				default:
					CUartPutCharToScr(*p);
					break;
			}
        }
		else
		{
			CUartPutCharToScr(*p);
		}
		p++;
    }
}
//----------------------------------------------------------------------------
void CUartPutToScr(const BYTE ch,const BYTE mode)
{
	BYTE NO1[3];
	BYTE i,time;

	if(mode == 1) 
	{	//dec
		NO1[2] = ch / 100;
		NO1[1] = (ch % 100) / 10;
		NO1[0] = (ch % 100) % 10;
		
		if (NO1[2])					time = 3;
		else if (NO1[1])			time = 2;
		else						time = 1;

		for (i = 0; i < time; i++) 
		{
			CUartPutCharToScr(NO1[time - i - 1] + '0');
		}
	}
	else if (mode == 2) 
	{	//hex
		NO1[1] = (ch & 0x0F);
		NO1[0] = ((ch >> 4) & 0x0F);
		for (i = 0; i < 2; i++) 
		{

			if (NO1[i] > 9)
				time = NO1[i] - 10 + 'A';
			else
				time = NO1[i] + '0';	 	// transfer UART
			CUartPutCharToScr(time);
		}
	}

}
//----------------------------------------------------------------------------
void CUartPutCharToScr(BYTE ch)
{
	ES = 0;

	TI = 0;
	SBUF = ch; 			// transfer UART
	while (!TI);		// wait buffer completing.
	
	ES = 1;
}
//----------------------------------------------------------------------------


void CUartHandler(void)
{
	do
	{		
		if (!fUartRxCmdSuccess)
			continue;

		fUartRxCmdSuccess = 0;

		switch (pUartData[0])
		{	
			case UartCMD_DebugModeExit:
				UartCMDDebugModeExit();
				break;
			case UartCMD_DebugModeEnter:
				UartCMDDebugModeEnter();
				break;
			
			case UartCMD_CScalerRead:
				UartCMDScalerRead();
				break;

			case UartCMD_I2CRead:
				break;

			case UartCMD_CScalerWrite:
				UartCMDScalerWrite();
				break;

			case UartCMD_I2CWrite:
				break;

		}

   	}
   	while(fUartDebugLoop);

}
//----------------------------------------------------------------------------
void UartCMDDebugModeExit(void)
{
	BYTE i;
	for(i=0;i<4;i++)
	{
		if(pUartData[i + 1] != tExitDebugMode[i])
			return;
	}

	CUartPutCharToScr(0x11);
	fUartDebugLoop = 0;
}
//----------------------------------------------------------------------------
void UartCMDDebugModeEnter(void)
{
	BYTE i;
	for(i=0;i<4;i++)
	{
		if(pUartData[i + 1] != tEnterDebugMode[i])
			return;
	}

	CUartPutCharToScr(0x10);
	fUartDebugLoop = 1;
}
//----------------------------------------------------------------------------
void UartCMDScalerRead(void)
{
	BYTE i;

	if (!pUartData[3])
		CScalerRead(pUartData[1], pUartData[2], pData, _AUTOINC);
	else
		CScalerRead(pUartData[1], pUartData[2], pData, _NON_AUTOINC);

	CUartPutCharToScr(pUartData[2]);
	for(i=0;i<pUartData[2];i++)
		CUartPutCharToScr(pData[i]);

}
//----------------------------------------------------------------------------
void UartCMDScalerWrite(void)
{
	CScalerSetByte(pUartData[1], pUartData[2]);
	CUartPutCharToScr(0x30);	// willy 050810 for sync RS232
}
//----------------------------------------------------------------------------

#endif
