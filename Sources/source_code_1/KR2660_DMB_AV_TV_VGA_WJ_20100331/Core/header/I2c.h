//----------------------------------------------------------------------------------------------------
// ID Code      : I2c.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of I2c.c
//--------------------------------------------------
#define _I2C_WRITE_SIZE                 	16
#define _I2C_TIMEOUT_LIMIT                  255

#define _I2C_BUSY                       	0
#define _I2C_OK                         	1

#define _I2C_WR                         	0
#define _I2C_RD                         	1

//----------------------------------------------------------------------------------------------------

#ifdef __I2C__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void Delay5us(void);
BYTE CI2cStart(BYTE ucDeviceAddr);
void CI2cStop(void);
BYTE CI2cGetAck(void);

BYTE CI2cSendByte(BYTE ucValue);
BYTE CI2cSendByteFM(BYTE ucValue);

BYTE CI2cGetByte(void);

void CI2cSendAck(void);
bit CI2cRead(BYTE ucDeviceAddr, BYTE ucStartAddr, WORD usLength, BYTE *pReadArray);
bit CI2cWrite(BYTE ucDeviceAddr, BYTE ucStartAddr, WORD usLength, BYTE *pWriteArray);
bit CI2cWriteFM( BYTE ucStartAddr, BYTE ucdata1, BYTE ucdata2);

//================================
//void BitDly(void);
unsigned char I2CGetByte(unsigned char ack);
void I2CSendByte(unsigned char send);
void I2CSendAddr(unsigned char addr, unsigned char index ,unsigned char rd);
void I2CSendStop(void);
void I2CRead(unsigned char addr, unsigned char index, unsigned char count);	// main I2C control Read
void I2CWrite(unsigned char *array);						// main I2C control write
void CI2cWriteArray(unsigned char dev_addr,unsigned char *array);
void I2CByteWrite(unsigned char index,unsigned char address,unsigned char value);
void I2CSetBit(unsigned char addr,unsigned char and1,unsigned char or1);
//for Audio/Tuner using
//reserved for furture 
//BYTE CIICStart(BYTE ucDeviceAddr);
void CIICStop(void);
BYTE CIICGetAck(void);
//reserved for furture 
//void CIICSendAck(void);
//void CIICSendNoAck(void);
BYTE CIICSendByte(BYTE ucValue);
//reserved for furture
//BYTE CIICGetByte(void);
//bit CIICWriteStart(BYTE ucDeviceAddr, BYTE ucStartAddr);
void CIICSendAddr(unsigned char addr, unsigned char index, unsigned char rd);
//reserved for furture
//bit CIICRead(BYTE ucDeviceAddr, BYTE ucStartAddr, WORD usLength, BYTE *pReadArray);
//bit CIICWrite(BYTE ucDeviceAddr, BYTE ucStartAddr, WORD usLength, BYTE *pWriteArray);
//void CIICWriteArray(BYTE dev_addr, BYTE *array);

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void Delay5us(void);
extern BYTE CI2cStart(BYTE ucDeviceAddr);
extern void CI2cStop(void);
extern BYTE CI2cGetAck(void);
extern void CI2cSendAck(void);
extern void CI2cSendNoAck(void);
extern BYTE CI2cSendByte(BYTE ucValue);
extern BYTE CI2cSendByteFM(BYTE ucValue);
extern BYTE CI2cGetByte(void);
extern void IR_Trans_Command(WORD customcode,WORD idcode);
extern bit CI2cRead(BYTE ucDeviceAddr, BYTE ucStartAddr, WORD usLength, BYTE *pReadArray);
extern bit CI2cWrite(BYTE ucDeviceAddr, BYTE ucStartAddr, WORD usLength, BYTE *pWriteArray);
extern bit CI2cRead1(BYTE ucDeviceAddr, BYTE ucStartAddr, WORD usLength, BYTE *pReadArray);
extern bit CI2cWriteFM( BYTE ucStartAddr, BYTE ucdata1, BYTE ucdata2);
extern void AS6300_Set_Freq(WORD frq);

//================================
//extern void BitDly(void);
extern unsigned char I2CGetByte(unsigned char ack);
extern void I2CSendByte(unsigned char send);
extern void I2CSendAddr(unsigned char addr, unsigned char index ,unsigned char rd);
extern void I2CSendStop(void);
extern void I2CRead(unsigned char addr, unsigned char index, unsigned char count);	// main I2C control Read
extern void I2CWrite(unsigned char *array);						// main I2C control write
extern void CI2cWriteArray(unsigned char dev_addr,unsigned char *array);
extern void I2CByteWrite(unsigned char index,unsigned char address,unsigned char value);
extern void I2CSetBit(unsigned char addr,unsigned char and1,unsigned char or1);
#if defined(CONFIG_VBI_ENABLE)
extern bit CI2cRead1(BYTE ucDeviceAddr, BYTE ucStartAddr, BYTE usLength, BYTE *pReadArray);
#endif
extern void MyI2CByteWrite(unsigned char index, unsigned char address, unsigned char value);  // Ken

#ifdef _RS232_MSP34xxG
extern void CMicronasI2CWrite(UINT8 device_addr, UINT8 sub_addr, UINT8 high_addr, UINT8 low_addr, UINT8 high_data, UINT8 low_data, UINT8 kind);
extern void CMicronasI2CRead(UINT8 device_addr, UINT8 sub_addr, UINT8 high_addr, UINT8 low_addr, UINT8 kind);
#endif

extern void I2CMaskByteWrite( unsigned char address, unsigned char index, unsigned char value, unsigned char maskvalue);	// kevin add

#endif


extern void Send2DTV(BYTE subaddr, BYTE *dData);
extern void ReadDTV(BYTE subaddr);
extern void SendData(BYTE offset, BYTE kind, BYTE *dData);
//----------------------------------------------------------------------------------------------------

extern void CIICStop(void);
extern BYTE CIICGetAck(void);
extern BYTE CIICSendByte(BYTE ucValue);
extern void CIICSendAddr(unsigned char addr, unsigned char index, unsigned char rd);

//--------------------------------------------------
// Macro of I2c.c for group1 
//--------------------------------------------------
#define SETI2CSDA()                 (bI2CSDA = _TRUE)
#define CLRI2CSDA()                 (bI2CSDA = _FALSE)
#define CHECKI2CSDA()               (bI2CSDA)

#define SETI2CSCL()                 (bI2CSCL = _TRUE)
#define CLRI2CSCL()                 (bI2CSCL = _FALSE)
#define CHECKI2CSCL()               (bI2CSCL)

#define SETI2CSDAFM()                 (FMI2CSDA = _TRUE)
#define CLRI2CSDAFM()                 (FMI2CSDA = _FALSE)
#define CHECKI2CSDAFM()               (FMI2CSDA)

#define SETI2CSCLFM()                 (FMI2CSCL = _TRUE)
#define CLRI2CSCLFM()                 (FMI2CSCL = _FALSE)
#define CHECKI2CSCLFM()               (FMI2CSCL)

