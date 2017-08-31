#define _FL_SD_BANK_NUMBER						5
#define _PAGE_SIZE                  			0x1000
#define _PAGE_SAVE_DATA_CNT						0xFF		//(_PAGE_SIZE / 16) 在运算时用 Byte 运算所以没有设置为 0x100 而设置为 0xFF



// Fix page save
#define _FL_SYSTEM_DATA_PAGE				0
#define _FL_OSD_USER_DATA_PAGE			1
#define _FL_ADC_DATA_PAGE					2
#define _FL_YPBPR_DATA_PAGE				3
#define _FL_AUDIO_DATA_PAGE				4
#define _FL_TV_DATA_PAGE					5

// random page save
#define _RANDOM_SAVE_START_PAGE			6
#define _RANDOM_SAVE_END_PAGE			14

#define _FL_CONBIR_DATA_PAGE_INDEX		0
#define _FL_COLORTEMP_DATA_PAGE_INDEX	1
#define _FL_HUE_DATA_PAGE_INDEX			2
#define _FL_TVFREQ_PAGE_INDEX				3
#define _FL_MODE_DATA_PAGE_INDEX			4
#define _FL_CENTER_DATA_PAGE_INDEX		5
#define _FL_FIFO_DATA_PAGE_INDEX			6

#if(_MEMORY_LOCATION == _FLASH)
//----------------------------------------------------------------------------------------------------
// ID Code      : Flash.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------
#ifdef __KX_FLASH__


#else		//#ifdef __KX_FLASH__


#endif		//#ifdef __KX_FLASH__

void CEepromStartupCheck(void);
void CEepromLoadDefault(bit bMode);

void CEepromSaveSystemData(void);
void CEepromLoadSystemData(void);
void CEepromLoadSystemDataDefault(void);

void CEepromSaveOsdUserData(void);
void CEepromLoadOsdUserData(void);
void CEepromLoadOsdUserDataDefault(void);

void CEepromSaveAdcData(void);
void CEepromLoadAdcData(void);
void CEepromLoadAdcDataDefault(void);
void CEepromLoadYPbPrDataDefault(void);

void CEepromSaveAudioData(void);
void CEepromLoadAudioData(void);
void CEepromLoadAudioDataDefault(void);

void CEepromSaveTvData(void);
void CEepromLoadTvData(void);
void CEepromLoadTvDataDefault(void);


void CEepromSaveBriConData(void);
void CEepromLoadBriConData(void);
void CEepromLoadBriConDataDefault(void);

void CEepromSaveColorTempData(void);
void CEepromLoadColorTempData(void);
void CEepromLoadColorTempDataDefault(void);

void CEepromSaveHueSatData(void);
void CEepromLoadHueSatData(void);
void CEepromLoadHueSatDataDefault(void);

void CEepromSaveModeData(BYTE ucMode);
void CEepromLoadModeData(BYTE ucMode);
void CEepromInitialModeData(void);

void CEepromSaveUserFIFOModeData(StructModeUserFIFODataType stUserFIFOMode);
void CEepromLoadUserFIFOModeData(BYTE ucNum, BYTE *pArray);
void CEepromInitialUserFIFOModeData(void);

void CEepromSaveCenterModeData(BYTE ucMode);
void CEepromLoadCenterModeData(BYTE ucMode);
void CEepromInitialCenterModeData(void);

void CSaveTVModeData(BYTE ucChannel);
void CLoadTVModeData(BYTE ucChannel);


#endif		//#if(_MEMORY_LOCATION == _FLASH)





