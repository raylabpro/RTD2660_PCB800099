//----------------------------------------------------------------------------------------------------
// ID Code      : Eeprom.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of EEPROM 2404/2416
//--------------------------------------------------
#define _EEPROM_ADDRESS                 		0xA0


//--------------------------------------------------
// Definitions of Eeprom Data Address
//--------------------------------------------------
#define _EEPROM_PAGE0_BANK0             	0
#define _EEPROM_PAGE0_BANK1             	128
#define _EEPROM_PAGE1_BANK0             	256
#define _EEPROM_PAGE1_BANK1             	384
#define _EEPROM_PAGE2_BANK0             	512
#define _EEPROM_PAGE2_BANK1             	640
#define _EEPROM_PAGE3_BANK0             	768
#define _EEPROM_PAGE3_BANK1             	896
#define _EEPROM_PAGE4_BANK0             	1024
#define _EEPROM_PAGE4_BANK1             	1152
#define _EEPROM_PAGE5_BANK0             	1280
#define _EEPROM_PAGE5_BANK1             	1408
#define _EEPROM_PAGE6_BANK0             	1536
#define _EEPROM_PAGE6_BANK1             	1664
#define _EEPROM_PAGE7_BANK0             	1792
#define _EEPROM_PAGE7_BANK1             	1920


#define _MODE_DATA_0_ADDRESS            		(_EEPROM_PAGE0_BANK0)		// Max 64 is 2 Page
#define _USER_FIFO_MODE_DATA_0_ADDRESS  		(_EEPROM_PAGE2_BANK0)		// Max 16 is 0.5 Page
#define _USER_FIFO_MODE_DATA_1_ADDRESS  		(_EEPROM_PAGE2_BANK1)		// Max 16 is 0.5 Page

#define _USER_DATA_ADDRESS              		(_EEPROM_PAGE5_BANK0)
#define _MODE_CENTER_DATA_ADDRESS			    (_EEPROM_PAGE6_BANK0)

#define _SYSTEM_DATA_ADDRESS         			(_USER_DATA_ADDRESS + 0)
#define _ICM_COLOR_ADDRESS						(_SYSTEM_DATA_ADDRESS + sizeof(stSystemData))
#define _OSDUSER_DATA_ADDRESS					(_ICM_COLOR_ADDRESS + sizeof(StructICMColor))
#define _ADC_DATA_ADDRESS               		(_OSDUSER_DATA_ADDRESS + sizeof(stOsdUserData))
#define _YPbPr_DATA_ADDRESS      				(_ADC_DATA_ADDRESS + sizeof(stAdcData))
#define _COLOR_PROC0_ADDRESS        			(_YPbPr_DATA_ADDRESS + sizeof(stYPbPrData))
#define _TV_DATA_ADDRESS						(_COLOR_PROC0_ADDRESS + (2*4))
#define _AUDIO_DATA_ADDRESS						(_TV_DATA_ADDRESS + sizeof(stTvInfo))
#define _COLORTEMP_DATA_ADDRESS  				(_AUDIO_DATA_ADDRESS +sizeof(stAudioData))
#define _HueSaturation_DATA_ADDRESS  			(_COLORTEMP_DATA_ADDRESS+(15*4))

//----------------------------------------------------------------------------------------------------
//TV
//=======================================================================================
//                                                                                      ]
//EEPROM address: 0xA6  0x50~0xFF    [ Save channel freq or tv sound and tv color type  ]
//EEPROM address: 0xA8  0x00~0xFC    [ Save channel freq or tv sound and tv color type  ]
//                      0xFE         [ Search max channel                               ]
//                      0xFF         [ User select search ch tv and sound type          ]
// Modify TV EEPROM address by EricLee 04-30-2007                                       ]
//=======================================================================================
// Definitions for max channel count

#define _TV_SYSTEM_EEPROM_ADDR       0xA6   // 24C16 Page 3
#define _TV_SYSTEM_START_ADDR        0x20   // Save tv system data start address

#define _MAX_CHANNEL_COUNT           ((WORD)((0xFF-_TV_SYSTEM_START_ADDR+0xFF-2)/3))

#define _TV_FREQ_EEPROM_ADDR0        0xA6   // 24C16 Page 3
#define _TV_FREQ_EP_START_ADDR0      (((_TV_SYSTEM_START_ADDR+_MAX_CHANNEL_COUNT)/2)*2 + 2) // Freq page6 start address
#define _TV_FREQ_EP0_TV_NUMBER       ((0xFF-_TV_FREQ_EP_START_ADDR0)/2)         // Page6 save tv channel total
#define _TV_FREQ_EEPROM_ADDR1        0xA8   // 24C16 Page 4
#define _TV_MAX_CHANNEL_EEPROM_ADDR  0xA8   // 24C16 Page 4
//#define EEPROM_SEARCH_TYPE_ADDR        0xFF
//#define _MAX_CHANNEL_ADDR            0xFE

// FM definition
#define _FM_START_ADDR               0x00
#define _FM_MAX_CHANNEL              16

#if(_MEMORY_LOCATION == _EEPROM)


#ifdef __EEPROM__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CEepromStartupCheck(void);
void CEepromWriteVersion(void);
void CEepromLoadDefault(bit bMode);
bit CEepromWrite(WORD usAddr, WORD usLength, BYTE *pWriteArray);
bit CEepromRead(WORD usAddr, WORD usLength, BYTE *pReadArray);

void CEepromSaveModeData(BYTE ucMode);
void CEepromLoadModeData(BYTE ucMode);
void CEepromInitialModeData(void);
void CEepromSaveUserFIFOModeData(StructModeUserFIFODataType stUserFIFOMode);
void CEepromLoadUserFIFOModeData(BYTE ucNum, BYTE *pArray);
void CEepromInitialUserFIFOModeData(void);
void CEepromSaveCenterModeData(BYTE ucMode);
void CEepromLoadCenterModeData(BYTE ucMode);
void CEepromInitialCenterModeData(void);
void CEepromSaveSystemData(void);
void CEepromLoadSystemData(void);
void CEepromLoadSystemDataDefault(void);
void CEepromSaveOsdUserData(void);
void CEepromLoadOsdUserData(void);
void CEepromLoadOsdUserDataDefault(void);
void CEepromSaveAdcData(void);
void CEepromLoadAdcData(void);
void CEepromLoadYPbPrDataDefault(void);
void CEepromLoadAdcDataDefault(void);
void CEepromSaveBriConData(void);
void CEepromLoadBriConData(void);
void CEepromLoadBriConDataDefault(void);
void CEepromSaveColorTempData(void);
void CEepromLoadColorTempData(void);
void CEepromLoadColorTempDataDefault(void);
void CEepromSaveEDIDData(void);
void CEepromLoadEDIDData(void);
void CEepromLoadEDIDDataDefault(void);
void CEepromSaveTvData(void);
void CEepromLoadTvData(void);
void CEepromLoadTvDataDefault(void);
void CEepromLoadTvDataDefault(void);
void CEepromSaveAudioData(void);
void CEepromLoadAudioData(void);
void CEepromLoadAudioDataDefault(void);
void CEepromSaveHueSatData(void);
void CEepromLoadHueSatData(void);
void CEepromLoadHueSatDataDefault(void);
void CSaveTVModeData(BYTE ucChannel);


#else
//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------

extern void CEepromStartupCheck(void);
extern void CEepromWriteVersion(void);
extern void CEepromLoadDefault(bit bMode);
extern bit CEepromWrite(WORD usAddr, WORD usLength, BYTE *pWriteArray);
extern bit CEepromRead(WORD usAddr, WORD usLength, BYTE *pReadArray);
extern void CEepromSaveModeData(BYTE ucMode);
extern void CEepromLoadModeData(BYTE ucMode);
extern void CEepromInitialModeData(void);
extern void CEepromSaveUserFIFOModeData(StructModeUserFIFODataType stUserFIFOMode);
extern void CEepromLoadUserFIFOModeData(BYTE ucNum, BYTE *pArray);
extern void CEepromInitialUserFIFOModeData(void);
extern void CEepromSaveCenterModeData(BYTE ucMode);
extern void CEepromLoadCenterModeData(BYTE ucMode);
extern void CEepromInitialCenterModeData(void);
extern void CEepromSaveSystemData(void);
extern void CEepromLoadSystemData(void);
extern void CEepromLoadSystemDataDefault(void);
extern void CEepromSaveOsdUserData(void);
extern void CEepromLoadOsdUserData(void);
extern void CEepromLoadOsdUserDataDefault(void);
extern void CEepromSaveAdcData(void);
extern void CEepromLoadAdcData(void);
extern void CEepromLoadAdcDataDefault(void);
extern void CEepromLoadYPbPrDataDefault(void);
extern void CEepromSaveBriConData(void);
extern void CEepromLoadBriConData(void);
extern void CEepromLoadBriConDataDefault(void);
extern void CEepromSaveColorTempData(void);
extern void CEepromLoadColorTempData(void);
extern void CEepromLoadColorTempDataDefault(void);
extern void CEepromSaveEDIDData(void);
extern void CEepromLoadEDIDData(void);
extern void CEepromLoadEDIDDataDefault(void);
extern void CEepromSaveTvData(void);
extern void CEepromLoadTvData(void);
extern void CEepromLoadTvDataDefault(void);
extern void CEepromGetTvOffsetData(BYTE chn, SBYTE *offset);
extern void CEepromSaveTvOffsetData(BYTE chn, SBYTE *offset);
extern void CEepromSaveAudioData(void);
extern void CEepromLoadAudioData(void);
extern void CEepromLoadAudioDataDefault(void);
extern bit CEepromWrite(WORD usAddr, WORD usLength, BYTE *pWriteArray);


extern void CEepromSaveHueSatData(void);
extern void CEepromLoadHueSatData(void);
extern void CEepromLoadHueSatDataDefault(void);
extern void CSaveTVModeData(BYTE ucChannel);
extern void CLoadTVModeData(BYTE ucChannel);

#endif

#endif	//#if(_MEMORY_LOCATION == _EEPROM)