//----------------------------------------------------------------------------------------------------
// ID Code      : Int.c No.0002
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#include "Core\Header\Include.h"

#if defined(CONFIG_VBI_ENABLE)
void VBI_GetData();
#else
#define	VBI_GetData();
#endif     
//--------------------------------------------------
// Timer0 Interrupt (375 us)
//--------------------------------------------------
void IntProcTimer0(void) interrupt 1
{
#if(0)
	static BYTE data ucTimer0Cnt = 0x00;

    TR0 = _ON;
    TL0 = _TIMER0_COUNT_LBYTE;
    TH0 = _TIMER0_COUNT_HBYTE;

    bNotifyTimer0Int = _TRUE;

    if(--ucTimer0Cnt)
    {

    }
    else
    {
        if(bTimer0Ctrl == _FALSE)
        {
            CTimerDecreaseTimerCnt();
        }
        ucTimer0Cnt = 10;
    }

#else
	static BYTE data ucTimer0Cnt = 0x00;
	static BYTE data ucTimerCnt = 10;

	
	EA = 0;
	TR0 = _ON;

	TL0 = _TIMER0_COUNT_LBYTE;	
	TH0 = _TIMER0_COUNT_HBYTE;
	
	
	if((++ucTimer0Cnt) >= _EVENT_PERIOD) 
	{
		ucTimer0Cnt = 0;
		bNotifyTimer0Int = _TRUE;
		if(ucTimerCnt)
			ucTimerCnt--;
			
		else if(bTimer0Ctrl == _FALSE) 
		{

			CTimerDecreaseTimerCnt();
			ucTimerCnt = 0x0a; 	//including the above 1.125ms, this will
								//give about 5 sec delay before OSD
								//menu/channel# got turn off
		}


#if(1)//_VIDEO_TV_SUPPORT)


#if(_SLEEP_FUNC)
        if (0xff != ucAutoPowerDownTime && 0x00 != ucAutoPowerDownTime)
        {
            ucMinuteCount++;
            bShowTimerChg = 1;
            if (ucMinuteCount == _ONE_MINUTE_COUNT)  // 1 minute
            {
                ucAutoPowerDownTime--;
                ucMinuteCount = 0; 
            }
        }
#endif
#endif
	}
	EA = 1;
#endif	
}

//--------------------------------------------------
#if(_RS232_EN)

//--------------------------------------------------
void UartRxData(void)
{
	if (fUartStart == 0) 
	{
		pUartData[0] = SBUF;
		fUartStart = 1;
		switch(pUartData[0])
		{
			case UartCMD_DebugModeEnter:  		// Enter debug mode
			case UartCMD_DebugModeExit:  		// Exit debug mode
				ucUartRxCount = 4;
				break;
			case UartCMD_CScalerRead:  			// Read RTD2553V
			case UartCMD_I2CRead:  				// Read I2C
			case UartCMD_I2CWrite:  			// Write I2C
				ucUartRxCount = 3;
				break;
			case UartCMD_CScalerWrite:  		// Write RTD2553V
				ucUartRxCount = 2;
				break;
			default:
				fUartStart = 0;
				break;
		}

		ucUartRxIndex = 1;
	}
	else 
	{
		pUartData[ucUartRxIndex] = SBUF;
		ucUartRxIndex++;
		if (ucUartRxIndex > ucUartRxCount)
		{
			fUartRxCmdSuccess = 1;
			fUartStart = 0;
		}
	}
}

//--------------------------------------------------
void IntProcUart(void) interrupt 4
{
	ES = 0; // disable uart interrupt.
	if (TI) 
	{
		TI = 0;
	}
	else if (RI) 
	{
		UartRxData();
		RI = 0;
	}
	ES = 1;
}


#endif
//--------------------------------------------------

#if(_DEBUG_TOOL == _ISP_FOR_RTD3580D_EMCU)
void IntProcDdcci(void)  interrupt 2
{
    BYTE tempbuf;
    
    EA=0;
    MCU_I2C_IRQ_CTRL2_FF2A  &= 0xDF; //host write/read enable
    if(!bRunCommand)
    {
        tempbuf = MCU_I2C_STATUS_FF27;   

        if(tempbuf & 0x08)
            MCU_I2C_DATA_OUT_FF26 = TxBUF;       

        if(tempbuf & 0x01) 
            ucDdcciCommandNumber = 0;

        if(tempbuf & 0x02) 
            ucDdcciCommandNumber =0;
        		
        if(tempbuf & 0x04)
        {
            if(ucDdcciCommandNumber==0)
                ucDdcciData[ucDdcciCommandNumber] = MCU_I2C_SUB_IN_FF24;

            ucDdcciCommandNumber++;
            ucDdcciData[ucDdcciCommandNumber] = MCU_I2C_DATA_IN_FF25;
            bRunCommand=_TRUE; 
        }

        MCU_I2C_STATUS_FF27 = tempbuf & 0xc0;
    }

    EA=1;
}


#endif
//--------------------------------------------------

#if(_DEBUG_TOOL == _ISP_FOR_DDCCI && _SUPPORTDDCCI)
void ReceiveEDIDINT1(void) interrupt 2
{
	BYTE tempflag;
	
	//MCU_I2C_IRQ_CTRL2_FF2A  &= 0xDF; //host write/read enable
	tempflag = MCU_I2C_STATUS_FF27;

	EA  = 0;
 	
    if(tempflag & DINI)	    // SLAVEB Interrupt
	{
		DDCCI_RxInt();
		MCU_I2C_STATUS_FF27 = tempflag & (~DINI);  //Clear DDCRAMA IIC Stop Interrupt detect
	}
	else if(tempflag & DOUTI)	    // SLAVEB Interrupt
	{
		//MCU_I2C_IRQ_CTRL2_FF2A |= 0x20;
		DDCCI_TxInt();
		MCU_I2C_STATUS_FF27 = tempflag & (~DOUTI);  //Clear DDCRAMA IIC Stop Interrupt detect
    }

    MCU_I2C_STATUS2_FF29 = 0x00; 
    EA  = 1;
}

//---------------------------------------------------------------------------------------

void DDCCI_RxInt()
{	
	unsigned char rxByte = MCU_I2C_DATA_IN_FF25;
	
	switch(rxStatus)
	{
	case DDC2B_CLEAR:

		if ( MCU_I2C_SUB_IN_FF24 == DDC2B_SRC_ADDRESS )
		{
			rxStatus = DDC2B_SRCADDRESS;
			ucDDCCI_CheckSum = INITRxCK;
		}
		else
		{
			DDCCI_InitRx();
			break;
		}
		
		// getting the length...
	case DDC2B_SRCADDRESS:
		// get the length

		ucDDCCI_RxCount = rxByte & (~DDC2Bi_CONTROL_STATUS_FLAG);
		// ...and if yes save the received byte in the rxBuffer
		// and update the pointers...
		ucDDCCI_RxBuf[ucDDCCI_RxIndex++] = rxByte;
		ucDDCCI_CheckSum ^= rxByte;
		// ...set the receive body state...
		rxStatus = DDC2B_COMMAND;
		//...and if it is a NULL message...
		if (ucDDCCI_RxCount == 0)
		{
			// ...wait for CK
			//rxStatus++;// = DDC2B_RECBODY;
			//rxStatus++;// = DDC2B_WAITFORCK;
			rxStatus = DDC2B_WAITFORCK; 
		}
		
		else if(ucDDCCI_RxCount > RX_BUFFER_SIZE)
		{
			DDCCI_InitRx();
		}
		
		break;
		// ...here we are getting the command...
	case DDC2B_COMMAND:
		// ...go to the recbody state
		rxStatus = DDC2B_RECBODY;
		// ...here we are getting the message body...
	case DDC2B_RECBODY:
		ucDDCCI_RxBuf[ucDDCCI_RxIndex++] = rxByte;
		ucDDCCI_CheckSum ^= rxByte;
		ucDDCCI_RxCount--;
		// ...and if this is the last byte in the message body...
		if (ucDDCCI_RxCount == 0)
			// ...set the wait for checksum flag
			rxStatus = DDC2B_WAITFORCK;
		break;
	case DDC2B_WAITFORCK:
		// ...and if we have a checksum match...
		if (ucDDCCI_CheckSum == rxByte)
		{
			// ...raise the completed flag - the buffer will be
			// processed by the parser...
			rxStatus = DDC2B_COMPLETED;

		}
		// ..else we have a checksum error...
		else
		{
			// ...clear the rxState and the current buffer for a new message
			DDCCI_InitRx();
		}
		break;
	default:
		DDCCI_InitRx();
		break;
		
	}
}
//---------------------------------------------------------------------------------------
void DDCCI_TxInt()
{
/*
    if (ucDDCCI_TxCount == 0)
    {
		MCU_I2C_IRQ_CTRL2_FF2A  &= 0xDF; //host write/read enable
		txBufferPtr = &ucDDCCI_NullStr[0];
		ucDDCCI_TxCount = sizeof (ucDDCCI_NullStr);
    }*/
    // ...send out the current byte
	
    MCU_I2C_DATA_OUT_FF26 = *txBufferPtr++;
	
    ucDDCCI_TxCount--;

    if (ucDDCCI_TxCount == 0)
    {
		MCU_I2C_IRQ_CTRL2_FF2A  = (MCU_I2C_IRQ_CTRL2_FF2A | _BIT6) & (~_BIT5); //host write/read enable
		txBufferPtr = &ucDDCCI_NullStr[0];
		ucDDCCI_TxCount = sizeof (ucDDCCI_NullStr);
    }    
}
//---------------------------------------------------------------------------------------
void DDCCI_InitRx(void)
{
	// clear the rxState...
	rxStatus = DDC2B_CLEAR;
	// ...and the current buffer for a new message
	ucDDCCI_RxIndex = 0;
}
//---------------------------------------------------------------------------------------
void DDC2Bi_InitTx (void)
{
	// initialize the transmit communication, so that either a valid...
	// ...or a NULL message is sent on a request from host
	txBufferPtr = &ucDDCCI_NullStr[0];
	ucDDCCI_TxCount = sizeof(ucDDCCI_NullStr) - 1;
	
    // a113
    //MCU_I2C_IRQ_CTRL2_FF2A |= 0x20;

    MCU_I2C_DATA_OUT_FF26 = *txBufferPtr++;
}
//---------------------------------------------------------------------------------------

#endif



