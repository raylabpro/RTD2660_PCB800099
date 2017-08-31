//----------------------------------------------------------------------------------------------------
// ID Code      : I2c.c No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#define __I2C__

#include "Core\Header\Include.h"

//#undef CONFIG_VBI_ENABLE
//----------------------------------------------------------------------------------------------------
// I2C communication basic function
//----------------------------------------------------------------------------------------------------
void Delay5us(void)
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();



	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();


}

void Delay_us(WORD us)
{
	for(;us>0;us--);
	{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	}
}

BYTE CI2cStart(BYTE ucDeviceAddr)
{

    SETI2CSCL();
    Delay5us();
    while(!(CHECKI2CSCL()));
    SETI2CSDA();
    CLRI2CSDA();
    Delay5us();
    CLRI2CSCL();

    return CI2cSendByte(ucDeviceAddr);
}

BYTE CI2cStartFM(BYTE ucDeviceAddr)
{

    SETI2CSCLFM();
    Delay5us();
  //  while(!(CHECKI2CSCLFM()));
    SETI2CSDAFM();
	Delay5us();
    CLRI2CSDAFM();
    Delay5us();
    CLRI2CSCLFM();
	Delay5us();
	
    return CI2cSendByteFM(ucDeviceAddr);
}

void CI2cStop(void)
{
    CLRI2CSDA();
    SETI2CSCL();
    Delay5us();
    SETI2CSDA();
}

void CI2cStopFM(void)
{
    CLRI2CSDAFM();
    SETI2CSCLFM();
    Delay5us();
    SETI2CSDAFM();
}

BYTE CI2cGetAck(void)
{
    BYTE ack;

    SETI2CSDA();
    SETI2CSCL();
    Delay5us();
    ack = CHECKI2CSDA();
    CLRI2CSCL();
    SETI2CSDA();

    return ack;
}

BYTE CI2cGetAckFM(void)
{
    BYTE ack;

    SETI2CSDAFM();
    SETI2CSCLFM();
    Delay5us();
	Delay5us();
	Delay5us();
  //  ack = CHECKI2CSDAFM();
    CLRI2CSCLFM();
    SETI2CSDAFM();
	Delay5us();
	Delay5us();

    return ack;
}

void CI2cSendAck(void)
{
    CLRI2CSDA();
    SETI2CSCL();
    Delay5us();
    CLRI2CSCL();
}

void CI2cSendNoAck(void)
{
    SETI2CSDA();
    SETI2CSCL();
    Delay5us();
    CLRI2CSCL();
}


BYTE CI2cSendByte(BYTE ucValue)
{
    BYTE cnt;

    for(cnt=0;cnt<8;cnt++)
    {
        if((bit)(ucValue & 0x80))
            SETI2CSDA();
        else
            CLRI2CSDA();
            
        SETI2CSCL();
        Delay5us();
        CLRI2CSCL();
        ucValue = ucValue << 1;
    }
    if(CI2cGetAck())
    {
        CI2cStop();
        return _I2C_BUSY;
    }
    else
    {
        return _I2C_OK;
    }
}

BYTE CI2cSendByteFM(BYTE ucValue)
{
    BYTE cnt;

    for(cnt=0;cnt<8;cnt++)
    {
        if((bit)(ucValue & 0x80))
            SETI2CSDAFM();
        else
            CLRI2CSDAFM();
        SETI2CSCLFM();
        Delay5us();
		Delay5us();
		Delay5us();
        CLRI2CSCLFM();
		Delay5us();
		Delay5us();
        ucValue = ucValue << 1;
    }
	Delay5us();
	Delay5us();
    if(CI2cGetAckFM())
    {
       // CI2cStopFM();
        return _I2C_OK;
    }
    else
    {
        return _I2C_OK;
    }
		Delay5us();
		Delay5us();
		Delay5us();
		Delay5us();
}

BYTE CI2cGetByte(void)
{
    BYTE cnt, value;

    value = 0;
    SETI2CSDA();
    for(cnt=0;cnt<8;cnt++)
    {
        SETI2CSCL();
        Delay5us();
        value = (value << 1) | CHECKI2CSDA();
        CLRI2CSCL();
    }
    return value;
}

bit CI2cWriteStart(BYTE ucDeviceAddr, BYTE ucStartAddr)
{
    BYTE timeoutcnt, control;

    timeoutcnt  = _I2C_TIMEOUT_LIMIT;
    control     = ucDeviceAddr | _I2C_WR;
    while(CI2cStart(control) != _I2C_OK)
    {
        timeoutcnt--;
        
        if(!timeoutcnt)
            return _FAIL;

    }
    if(CI2cSendByte(ucStartAddr) != _I2C_OK)
        return _FAIL;
        
    return _SUCCESS;
}


//--------------------------------------------------
// Description  : Read data from the selected device by I2C protocol
// Input Value  : ucDeviceAddr  --> Device address
//                ucStartAddr   --> Start address of selected device
//                usLength      --> Numbers of data we want to read
//                pReadArray    --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit CI2cRead(BYTE ucDeviceAddr, BYTE ucStartAddr, WORD usLength, BYTE *pReadArray)
{
    BYTE control;

    if(usLength == 0)
        return _FAIL;

    if(CI2cWriteStart(ucDeviceAddr, ucStartAddr) == _FAIL)
        return _FAIL;

    control = ucDeviceAddr | _I2C_RD;

    if(CI2cStart(control) != _I2C_OK)
        return _FAIL;

    while(--usLength)
    {
        *pReadArray++ = CI2cGetByte();
        CI2cSendAck();
    }

    *pReadArray++ = CI2cGetByte();

    CI2cSendNoAck();
    CI2cStop();

    return _SUCCESS;
}

//--------------------------------------------------

//--------------------------------------------------

// Description  : Write data to the selected device by I2C protocol
// Input Value  : ucDeviceAddr  --> Device address
//                ucStartAddr   --> Start address of selected device
//                usLength      --> Numbers of data we want to write
//                pWriteArray   --> Writing data array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit CI2cWrite(BYTE ucDeviceAddr, BYTE ucStartAddr, WORD usLength, BYTE *pWriteArray)
{
    BYTE control;

    if(usLength == 0)
        return _FAIL;
    while(usLength > 0)
    {
        if(CI2cWriteStart(ucDeviceAddr, ucStartAddr) == _FAIL)
            return _FAIL;

        control = _I2C_WRITE_SIZE - (ucStartAddr & 0x0f);

        if(usLength > control)
        {
            usLength -= control;
            if(ucStartAddr >= 0xf0)
                ucDeviceAddr += 2;
            ucStartAddr += control;
        }
        else
        {
            control = usLength;
            usLength = 0;
        }

        while(control--)
        {
            if(CI2cSendByte(*pWriteArray++) != _I2C_OK)
                return _FAIL;
        }

        CI2cStop();
    }

    return _SUCCESS;
}
bit CI2cWriteFM( BYTE ucStartAddr, BYTE ucdata1, BYTE ucdata2)
{
    BYTE timeoutcnt, control;
    timeoutcnt  = _I2C_TIMEOUT_LIMIT;
    control = ((ucStartAddr)<<1)|0x80;	
    control = control | _I2C_WR;
    while(CI2cStartFM(control) != _I2C_OK)
    {
        timeoutcnt--;      
        if(!timeoutcnt)
            return _FAIL;
    }
	CI2cSendByteFM(ucdata1);
	CI2cSendByteFM(ucdata2);	
	CI2cStopFM();   
    return _SUCCESS;
}

void AS6300_Set_Freq(WORD frq)
{
	char  rfpll_pb;
	char  rfpll_sb;
	WORD	temp;
	BYTE temp1,temp2;
	temp = frq+2;
	rfpll_sb  = temp % 15;
	rfpll_pb = (temp - rfpll_sb) / 15 - 1;
	
	temp1 = (rfpll_pb >> 1);
	temp1 |= (rfpll_sb<<7);
	temp2 = (rfpll_pb<<7)|0x20;
	CI2cWriteFM(5,temp1,temp2);
	temp1 = 0x88;
	temp2 = rfpll_sb>>1;
	CI2cWriteFM(6,temp1,temp2);
}


//==============================================================================
//idcode: 高8位是低8位的补码//wtao100415
#ifdef IRSEND_ENABLE
void IR_Trans_Command(WORD customcode,WORD idcode)
{
	data BYTE index;

	EA = 0;
//-------------------------
	IR_PIN_H;
	IR_PIN_L;
	Delay_us(1520);
	IR_PIN_H;
	Delay_us(740);
	IR_PIN_L;

	for(index = 0;index<16;index++)
	{
		IR_PIN_L;
		Delay_us(88);
		if(customcode&0x0001)
		{//send 1
			IR_PIN_H;
			Delay_us(275);
		}
		else
		{
			IR_PIN_H;
			Delay_us(88);
		}		
		customcode >>= 1;
	} 

	for(index = 0;index<16;index++)
	{
		IR_PIN_L;
		Delay_us(88);
		if(idcode&0x0001)
		{//send 1
			IR_PIN_H;
			Delay_us(275);
		}
		else
		{
			IR_PIN_H;
			Delay_us(88);
		}
		idcode >>= 1;		
	}

	IR_PIN_L;
	Delay_us(88);
	IR_PIN_H;
//-------------------------
	EA = 1;
}
#endif

//==============================================================================
/*
#define _ALC_SLAVE				0x40

#define bMute
#define bALCPower

#define _MUTE_ON
#define _MUTE_OFF
#define _ALC_POWER_ON
#define _ALC_POWER_OFF

#define _ALC_CH0				0
#define _ALC_CH1				1
#define _ALC_CH2				2
#define _ALC_CH3				3

BYTE g_ucAlcCtrl0 = 0x1f;
//==============================================================================
void CAlcInit(void)
{
	//Zero Detection Control Bit8
	//0: Turn Off
	//1: Turn On
	
	//Output Clamping Control Bit5
	//0: Internal Control
	//1: External OPL Pin Control	

	
	BYTE ucCtrl = (1 << 8) | (0 << 5);
	CAlcWrite(0x01,g_ucAlcCtrl0);
	CAlcWrite(0x02,ucCtrl);

	CAlcSetMuteOn();
	CAlcSetPowerOff();	
}
//==============================================================================
WORD CAlcRead(BYTE usAddr)
{
	WORD usData;
	CI2cRead(_ALC_SLAVE, usAddr, 2, pData);
	
	usData = ((WORD)pData[0] << 8) | pData[1];
	return usData;
}
//==============================================================================
void CAlcWrite(BYTE usAddr,WORD usData)
{
	pData[0] = (usData >> 8) & 0xff;
	pData[1] = usData & 0xff;
	
	CI2cWrite(_ALC_SLAVE, usAddr, 2, pData);	
}
//==============================================================================
void CAlcSetMuteOn(void)
{
	WORD usRD;
	BYTE usTimeOut = 5;

	while(usTimeOut --)
	{
		bMute = _MUTE_ON;
		usRD = CAlcRead(0x00);
		if(usRD & _BIT8)
			return;
	}
}
//==============================================================================
void CAlcSetMuteOff(void)
{
	WORD usRD;
	BYTE usTimeOut = 5;

	while(usTimeOut --)
	{
		bMute = _MUTE_OFF;	
		usRD = CAlcRead(0x00);
		if((usRD & _BIT8) == 0x00)
			return;		
	}
}
//==============================================================================
void CAlcSetPowerOn(void)
{
	WORD usRD;
	BYTE usTimeOut = 5;

	while(usTimeOut --)
	{
		bALCPower = _ALC_POWER_ON;	
		usRD = CAlcRead(0x00);
		if(usRD & _BIT9)
			return;		
	}
}
//==============================================================================
void CAlcSetPowerOff(void)
{
	WORD usRD;
	BYTE usTimeOut = 5;

	while(usTimeOut --)
	{
		bALCPower = _ALC_POWER_ON;	
		usRD = CAlcRead(0x00);
		if((usRD & _BIT9) == 0x00)
			return;		
	}
}
//==============================================================================
void CAlcSetVolume(BYTE ucVolume)
{
	g_ucAlcCtrl0 = (g_ucAlcCtrl0 & (~0x1F)) | (ucVolume & 0x1F);
	CAlcWrite(0x01,g_ucAlcCtrl0);
}
//==============================================================================
void CAlcSetChannel(BYTE ucChannel)
{
	g_ucAlcCtrl0 = (g_ucAlcCtrl0 & (~0x60)) | (ucChannel << 5);
	CAlcWrite(0x01,g_ucAlcCtrl0);
}
//==============================================================================



void CAlcInit(void);
void CAlcSetMuteOn(void);
void CAlcSetMuteOff(void);
void CAlcSetPowerOn(void);
void CAlcSetPowerOff(void);
void CAlcSetVolume(BYTE ucVolume);
void CAlcSetChannel(BYTE ucChannel);
*/
