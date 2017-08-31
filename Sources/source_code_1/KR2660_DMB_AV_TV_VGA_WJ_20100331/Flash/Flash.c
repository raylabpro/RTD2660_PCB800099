// Modify for using Flash to replace Eeprom.

//----------------------------------------------------------------------------------------------------
// ID Code      : Flash.c No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#define __KX_FLASH__

#include "Core\Header\Include.h"

#if(_MEMORY_LOCATION == _FLASH)
//----------------------------------------------------------------------------------------------------

#define _VERSION_CODE               0xAA


void CEepromStartupCheck(void)
{
    BYTE xdata *pFlashVersion = 0xF000;

    //This delay is for Eeprom power rising time when the connector plug in (VGA_5V or DVI_5V).
    CTimerDelayXms(20);    //CTimerDelayXms(20);

    if(*pFlashVersion != _VERSION_CODE)
    {
    	CUartSendString("EEProm Load default.\n");
        CEepromLoadDefault(1);

    	CFlashWREN(0);        
        *pFlashVersion = _VERSION_CODE;
    	CFlashWRDis();
    }
    else
    {
        CEepromLoadSystemData();
        CEepromLoadOsdUserData();
        CEepromLoadAdcData();
        CEepromLoadBriConData();
        CEepromLoadColorTempData();
        CEepromLoadTvData();    
        CEepromLoadHueSatData();
        CEepromLoadAudioData();
        CLoadTVModeData(stTvInfo.CurChn);
    }
}
//----------------------------------------------------------------------------------------------------

void CEepromLoadDefault(bit bMode)
{
    StructModeUserFIFODataType stFIFOModeTemp;

    if((GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE) && (stModeInfo.ModeCurr < 16))
    {
        CEepromLoadUserFIFOModeData((stModeInfo.ModeCurr / 4), pData);
        stFIFOModeTemp.ModeNum = pData[(stModeInfo.ModeCurr % 4) * 4];
    }

    CEepromInitialModeData();
    CEepromInitialUserFIFOModeData();
    CEepromInitialCenterModeData();
    CEepromLoadSystemDataDefault();
    CEepromLoadOsdUserDataDefault();
    
    if (bMode)
    {
       CEepromLoadAdcDataDefault();
       CEepromLoadYPbPrDataDefault();
       CEepromLoadColorTempDataDefault();
    }
    
    CEepromLoadBriConDataDefault();
    CEepromLoadHueSatDataDefault();
    CEepromLoadAudioDataDefault();

    CEepromLoadTvDataDefault();
    CLoadTVModeData(stTvInfo.CurChn);

    if((GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE) && (stModeInfo.ModeCurr < 16))
    {
        if(stSystemData.UserFIFOMode >= 15)
            stSystemData.UserFIFOMode = 0;
        else
            stSystemData.UserFIFOMode++;

        stFIFOModeTemp.IHFreq  = stModeInfo.IHFreq;
        stFIFOModeTemp.IVFreq  = stModeInfo.IVFreq;
        CEepromSaveUserFIFOModeData(stFIFOModeTemp);

        stModeUserData.FirstAuto    = 0;
        stModeUserData.HPosition    = tINPUTMODE_PRESET_TABLE[stFIFOModeTemp.ModeNum].IHStartPos;
        stModeUserData.VPosition    = tINPUTMODE_PRESET_TABLE[stFIFOModeTemp.ModeNum].IVStartPos;
        stModeUserData.Clock        = tINPUTMODE_PRESET_TABLE[stFIFOModeTemp.ModeNum].IHTotal;
        stModeUserData.Phase        = 0;
        CEepromSaveModeData(stSystemData.UserFIFOMode);
        stModeInfo.ModeCurr = stSystemData.UserFIFOMode;
    }
    else if((GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE) && (stModeInfo.ModeCurr < _MAX_PRESET_MODE))
    {
        CEepromLoadModeData(stModeInfo.ModeCurr);
        CEepromLoadCenterModeData(stModeInfo.ModeCurr);
    }

#if(0)//_VIDEO_TV_SUPPORT)
    if (bMode)
        CRecallTVData();
#endif
}
//----------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------
void FLSaveStruct(BYTE ucPage,BYTE Cnt,BYTE *Array)
{
	bit fRT;
	BYTE ucWriteSize;
	BYTE ID = 1;
	BYTE ucWriteCnt = Cnt / 14;
	if(Cnt % 14)	ucWriteCnt++;

	CFlashWREN(ucPage);
	
	while(Cnt)
	{
		if(Cnt > 14)
			ucWriteSize = 14;
		else ucWriteSize = Cnt;
		Cnt -= ucWriteSize;
		
		FillFFToMemory(g_szFlashBuf,16);
		MemoryCpy(g_szFlashBuf, Array, ucWriteSize);
		Array += ucWriteSize;

		fRT = FLSaveData(ucPage,ID,ucWriteCnt);
		if(fRT == _FAIL)
		{
			CUartPrintf("Erase Page:", ucPage);
			CFlashErase(ucPage);
			FLSaveData(ucPage,ID,ucWriteCnt);
		}

		ID++;
	}

	CFlashWRDis();
}
//----------------------------------------------------------------------------------------------------
bit FLLoadStruct(BYTE ucPage,BYTE ID,BYTE Cnt,BYTE *Array)
{
	bit fRT;
	BYTE ucSize;
	
	while(Cnt)
	{
		if(Cnt > 14)
			ucSize = 14;
		else ucSize = Cnt;
		Cnt -= ucSize;

		fRT = FLLoadData(ucPage,ID++);

		if(fRT == _FAIL)
		{
			return _FAIL;
		}
		
		MemoryCpy(Array,g_szFlashBuf,ucSize);
		Array += ucSize;
		
	}

	return _SUCCESS;
}
//----------------------------------------------------------------------------------------------------
bit FLRandomPageSaveData(BYTE ucPage,BYTE ID,BYTE Cnt,BYTE *Array)
{
	bit fRT;
	BYTE ucWriteSize;
	BYTE ucWriteCnt = Cnt / 14;
	if(Cnt % 14)	ucWriteCnt++;

	CFlashWREN(ucPage);
	
	while(Cnt)
	{
		if(Cnt > 14)
			ucWriteSize = 14;
		else ucWriteSize = Cnt;
		Cnt -= ucWriteSize;
		
		FillFFToMemory(g_szFlashBuf,16);
		MemoryCpy(g_szFlashBuf, Array, ucWriteSize);
		Array += ucWriteSize;

		fRT = FLSaveData(ucPage,ID,ucWriteCnt);
		if(fRT == _FAIL)
		{
			
			//CFlashErase(ucPage);
			//FLSaveData(ucPage,ID,ucWriteCnt);
			break;
		}

		ID++;
	}

	CFlashWRDis();

	return fRT;
}
//----------------------------------------------------------------------------------------------------
void FLRandomPageSaveStruct(BYTE ucPageIndex,BYTE ID,BYTE Cnt,BYTE *Array)
{
	bit fRT;
	BYTE ucNewPage;
	BYTE ucPage = g_szRandomSavePage[ucPageIndex];

	// 如果第一次保存执行下面的条件
	if(ucPage == 0xFF)
	{
		ucPage = FoundEmptyRandomPage();
		CUartPrintf("Fonnd Empty Page:", ucPage);

		// 如果没有发现没有用到的 Page,那么退出
		if(ucPage == 0xFF)
			return;

		g_szRandomSavePage[ucPageIndex] = ucPage;
		InitRandomPage(ucPage,ucPageIndex);
	}

	fRT = FLRandomPageSaveData(ucPage,ID,Cnt,Array);

	// 如果失败，将数据移到新的 Page 中。
	if(fRT == _FAIL)
	{
		ucNewPage = FoundEmptyRandomPage();

		CUartPrintf("Fonnd new Empty Page:", ucNewPage);

		// 如果没有发现没有用到的 Page,那么退出
		if(ucNewPage == 0xFF)
			return;

		CUartPrintf("Move page:", ucPage);
		CUartPrintf("to:", ucNewPage);

		// 将数据,移动新的 Page 中.
		g_szRandomSavePage[ucPageIndex] = ucNewPage;
		InitRandomPage(ucNewPage,ucPageIndex);
		CFlashMovePage(ucNewPage,ucPage);

		// 移动数据后将以前的页面删除
		CFlashErase(ucPage);
		FLRandomPageSaveData(ucNewPage,ID,Cnt,Array);
	}
}
//----------------------------------------------------------------------------------------------------


void CEepromSaveSystemData(void)
{
	FLSaveStruct(_FL_SYSTEM_DATA_PAGE,sizeof(StructSystemDataType),&stSystemData.MonitorFlag);
}
//----------------------------------------------------------------------------------------------------
void CEepromLoadSystemData(void)
{
	bit fRT = FLLoadStruct(_FL_SYSTEM_DATA_PAGE,1,sizeof(StructSystemDataType),&stSystemData.MonitorFlag);

	if(fRT == _FAIL)
	{
		CEepromLoadSystemDataDefault();
	}
}
//----------------------------------------------------------------------------------------------------
void CEepromLoadSystemDataDefault(void)
{
    stSystemData = tEEPROM_SYSTEM_DATA;
    //MemoryCpy(&stSystemData.MonitorFlag,tEEPROM_SYSTEM_DATA.MonitorFlag, sizeof(StructSystemDataType));
    CEepromSaveSystemData();
}
//----------------------------------------------------------------------------------------------------
void CEepromSaveOsdUserData(void)
{
	FLSaveStruct(_FL_OSD_USER_DATA_PAGE,sizeof(StructOsdUserDataType),&stOsdUserData.OsdHPos);
}
//----------------------------------------------------------------------------------------------------
void CEepromLoadOsdUserData(void)
{
	bit fRT = FLLoadStruct(_FL_OSD_USER_DATA_PAGE,1,sizeof(StructOsdUserDataType),&stOsdUserData.OsdHPos);

	if(fRT == _FAIL)
	{
		CEepromLoadOsdUserDataDefault();
	}
}
//----------------------------------------------------------------------------------------------------
void CEepromLoadOsdUserDataDefault(void)
{
    stOsdUserData = tEEPROM_OSDUSER_DATA;
	CEepromSaveOsdUserData();
}
//----------------------------------------------------------------------------------------------------
void CEepromSaveAdcData(void)
{
	if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
		FLSaveStruct(_FL_ADC_DATA_PAGE,sizeof(StructAdcDataType),&stAdcData.AdcGain[0]);
	else
		FLSaveStruct(_FL_YPBPR_DATA_PAGE,sizeof(StructYPbPrDataType),&stYPbPrData.YPbPrGain[0]);
}
//----------------------------------------------------------------------------------------------------
void CEepromLoadAdcData(void)
{
	bit fRT = FLLoadStruct(_FL_ADC_DATA_PAGE,1,sizeof(StructAdcDataType),&stAdcData.AdcGain[0]);	

	if(fRT == _FAIL)
	{
		CEepromLoadAdcDataDefault();
	}

	fRT = FLLoadStruct(_FL_YPBPR_DATA_PAGE,1,sizeof(StructYPbPrDataType),&stYPbPrData.YPbPrGain[0]);

	if(fRT == _FAIL)
	{
		CEepromLoadYPbPrDataDefault();
	}
	

}
//----------------------------------------------------------------------------------------------------
void CEepromLoadAdcDataDefault(void)
{
	stAdcData = tEEPROM_ADC_DATA;
	FLSaveStruct(_FL_ADC_DATA_PAGE,sizeof(StructAdcDataType),&stAdcData.AdcGain[0]);
}
//----------------------------------------------------------------------------------------------------
void CEepromLoadYPbPrDataDefault(void)
{
    stYPbPrData = tEEPROM_YPbPr_DATA;
	FLSaveStruct(_FL_YPBPR_DATA_PAGE,sizeof(StructYPbPrDataType),&stYPbPrData.YPbPrGain[0]);
}
//----------------------------------------------------------------------------------------------------
void CEepromSaveAudioData(void)
{
	FLSaveStruct(_FL_AUDIO_DATA_PAGE,sizeof(StructAudioDataType),&stAudioData.Mode);
}
//----------------------------------------------------------------------------------------------------
void CEepromLoadAudioData(void)
{
	bit fRT = FLLoadStruct(_FL_AUDIO_DATA_PAGE,1,sizeof(StructAudioDataType),&stAudioData.Mode);

	if(fRT == _FAIL)
	{
		CEepromLoadAudioDataDefault();
	}
}
//----------------------------------------------------------------------------------------------------
void CEepromLoadAudioDataDefault(void)
{
    stAudioData = tEEPROM_AUDIO_DATA;
	CEepromSaveAudioData();	

}
//----------------------------------------------------------------------------------------------------

void CEepromSaveTvData(void)
{
	FLSaveStruct(_FL_TV_DATA_PAGE,sizeof(StructTvDataType), &stTvInfo.CurChn);	
}
//----------------------------------------------------------------------------------------------------
void CEepromLoadTvData(void)
{
	bit fRT = FLLoadStruct(_FL_TV_DATA_PAGE,1,sizeof(StructTvDataType), &stTvInfo.CurChn);	

	if(fRT == _FAIL)
	{
		CEepromLoadTvDataDefault();
	}

}
//----------------------------------------------------------------------------------------------------
void CEepromLoadTvDataDefault(void)
{
    stTvInfo = tEEPROM_TV_DATA;
    CEepromSaveTvData();
}
//----------------------------------------------------------------------------------------------------







void CEepromSaveBriConData(void)
{
	BYTE ID = CGetInputSourceNum(_GET_INPUT_SOURCE()) + 1;

	//CUartPrintf("Save Con Data:", ID);
	FLRandomPageSaveStruct(_FL_CONBIR_DATA_PAGE_INDEX,ID,sizeof(StructColorProc0DataType),&stConBriData.Brightness);
}
//----------------------------------------------------------------------------------------------------
void CEepromLoadBriConData(void)
{
	bit fRT;
	BYTE ucPage = g_szRandomSavePage[_FL_CONBIR_DATA_PAGE_INDEX];
	BYTE ID = CGetInputSourceNum(_GET_INPUT_SOURCE()) + 1;

	fRT = FLLoadStruct(ucPage,ID,sizeof(StructColorProc0DataType),&stConBriData.Brightness);

	if(fRT == _FAIL)
	{
		CEepromLoadBriConDataDefault();
	}

}
//----------------------------------------------------------------------------------------------------
void CEepromLoadBriConDataDefault(void)
{
	BYTE i;
	
	for(i=0;i<4;i++)
	{
    	stConBriData = tEEPROM_COLOR_PROC0_DATA[i];
    	FLRandomPageSaveStruct(_FL_CONBIR_DATA_PAGE_INDEX,i + 1,sizeof(StructColorProc0DataType),&stConBriData.Brightness);
    }

    stConBriData = tEEPROM_COLOR_PROC0_DATA[CGetInputSourceNum(_GET_INPUT_SOURCE())];
}
//----------------------------------------------------------------------------------------------------
void CEepromSaveHueSatData(void)
{
	BYTE ID = CGetInputSourceNum(_GET_INPUT_SOURCE()) + 1;
	FLRandomPageSaveStruct(_FL_HUE_DATA_PAGE_INDEX,ID,sizeof(StructHueSaturationDataType),&stHueSatData.Hue);
}
//----------------------------------------------------------------------------------------------------
void CEepromLoadHueSatData(void)
{
	bit fRT;
	BYTE ucPage = g_szRandomSavePage[_FL_HUE_DATA_PAGE_INDEX];
	BYTE ID = CGetInputSourceNum(_GET_INPUT_SOURCE()) + 1;

	fRT = FLLoadStruct(ucPage,ID,sizeof(StructHueSaturationDataType),&stHueSatData.Hue);

	if(fRT == _FAIL)
	{
		CEepromLoadHueSatDataDefault();
	}
}
//----------------------------------------------------------------------------------------------------
void CEepromLoadHueSatDataDefault(void)
{
	BYTE i;
	
	for(i=0;i<4;i++)
	{
		stHueSatData = tEEPROM_HUE_SAT_DATA[i];
		FLRandomPageSaveStruct(_FL_HUE_DATA_PAGE_INDEX,i + 1,sizeof(StructHueSaturationDataType),&stHueSatData.Hue);
    }

    stHueSatData = tEEPROM_HUE_SAT_DATA[CGetInputSourceNum(_GET_INPUT_SOURCE())];

}
//----------------------------------------------------------------------------------------------------
void CEepromSaveColorTempData(void)
{
	BYTE ID = CGetInputSourceNum(_GET_INPUT_SOURCE()) * 5 + GET_COLOR_TEMP_TYPE() + 1;
	FLRandomPageSaveStruct(_FL_COLORTEMP_DATA_PAGE_INDEX,ID,sizeof(StructColorProc1DataType),&stColorTempData.ColorTemp[_RED]);
}
//----------------------------------------------------------------------------------------------------
void CEepromLoadColorTempData(void)
{
	bit fRT;
	BYTE ucPage = g_szRandomSavePage[_FL_COLORTEMP_DATA_PAGE_INDEX];
	BYTE ID = CGetInputSourceNum(_GET_INPUT_SOURCE()) * 5 + GET_COLOR_TEMP_TYPE() + 1;

	fRT = FLLoadStruct(ucPage,ID,sizeof(StructColorProc1DataType),&stColorTempData.ColorTemp[_RED]);

	if(fRT == _FAIL)
	{
		CEepromLoadColorTempDataDefault();
	}
}
//----------------------------------------------------------------------------------------------------
void CEepromLoadColorTempDataDefault(void)
{
	BYTE i;
	
	for(i=0;i<4 * 5;i++)
	{
		stColorTempData = tEEPROM_COLORTEMP_DATA[i];
		FLRandomPageSaveStruct(_FL_COLORTEMP_DATA_PAGE_INDEX,i + 1,sizeof(StructColorProc1DataType),&stColorTempData.ColorTemp[_RED]);
    }
    
    stColorTempData = tEEPROM_COLORTEMP_DATA[CGetInputSourceNum(_GET_INPUT_SOURCE()) * 5 + GET_COLOR_TEMP_TYPE()];
}
//----------------------------------------------------------------------------------------------------
void CEepromSaveModeData(BYTE ucMode)
{
	BYTE ID;
    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        ID = ucMode + 1;
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        ID = ucMode + 150;
    }

    FLRandomPageSaveStruct(_FL_MODE_DATA_PAGE_INDEX,ID,sizeof(StructModeUserDataType), &stModeUserData.FirstAuto);

}
//----------------------------------------------------------------------------------------------------
void CEepromLoadModeData(BYTE ucMode)
{

	bit fRT;
	BYTE ucPage = g_szRandomSavePage[_FL_MODE_DATA_PAGE_INDEX];
	BYTE ID ;


    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        ID = ucMode + 1;
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        ID = ucMode + 150;
    }

	fRT = FLLoadStruct(ucPage,ID,sizeof(StructModeUserDataType), &stModeUserData.FirstAuto);
	if(fRT == _FAIL)
	{
		stModeUserData.FirstAuto    = 0;
		stModeUserData.HPosition    = stModeInfo.IHStartPos;
		stModeUserData.VPosition    = stModeInfo.IVStartPos;
		stModeUserData.Clock        = stModeInfo.IHTotal;
		stModeUserData.Phase        = 0;
	}	
    
}
//----------------------------------------------------------------------------------------------------
void CEepromInitialModeData(void)
{
    BYTE modecnt, modetype;

    modetype = GET_MODE_SEARCH_TYPE();
    SET_MODE_SEARCH_TYPE(_PRESET_MODE_TYPE);

    for(modecnt=0;modecnt<_MAX_PRESET_MODE;modecnt++)
    {
        stModeUserData.FirstAuto    = 0;
        stModeUserData.HPosition    = tINPUTMODE_PRESET_TABLE[modecnt].IHStartPos;
        stModeUserData.VPosition    = tINPUTMODE_PRESET_TABLE[modecnt].IVStartPos;
        stModeUserData.Clock        = tINPUTMODE_PRESET_TABLE[modecnt].IHTotal;
        stModeUserData.Phase        = 0;

        CEepromSaveModeData(modecnt);
    }

    SET_MODE_SEARCH_TYPE(modetype);
}
//----------------------------------------------------------------------------------------------------
void CEepromSaveCenterModeData(BYTE ucMode)
{
	BYTE ID;
    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
		ID = ucMode + 1;	    	
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)   
        ID = ucMode + 150;

	FLRandomPageSaveStruct(_FL_CENTER_DATA_PAGE_INDEX,ID,sizeof(StructModeUserCenterDataType), (BYTE *)&stModeUserCenterData.CenterHPos);
}
//----------------------------------------------------------------------------------------------------
void CEepromLoadCenterModeData(BYTE ucMode)
{
	bit fRT;
	BYTE ucPage = g_szRandomSavePage[_FL_CENTER_DATA_PAGE_INDEX];
	BYTE ID ;

    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        ID = ucMode + 1;
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
		ID = ucMode + 150;
    }

 	fRT = FLLoadStruct(ucPage,ID,sizeof(StructModeUserCenterDataType), (BYTE *)&stModeUserCenterData.CenterHPos);

    if(fRT == _FAIL)
    {
        stModeUserCenterData.CenterHPos     = stModeInfo.IHStartPos;
        stModeUserCenterData.CenterVPos     = stModeInfo.IVStartPos;
        stModeUserCenterData.CenterClock    = stModeInfo.IHTotal;
    }
}
//----------------------------------------------------------------------------------------------------
void CEepromInitialCenterModeData(void)
{
    BYTE modecnt, modetype;

    modetype = GET_MODE_SEARCH_TYPE();
    SET_MODE_SEARCH_TYPE(_PRESET_MODE_TYPE);

    for(modecnt=0;modecnt<_MAX_PRESET_MODE;modecnt++)
    {
        stModeUserCenterData.CenterHPos     = tINPUTMODE_PRESET_TABLE[modecnt].IHStartPos;
        stModeUserCenterData.CenterVPos     = tINPUTMODE_PRESET_TABLE[modecnt].IVStartPos;
        stModeUserCenterData.CenterClock    = tINPUTMODE_PRESET_TABLE[modecnt].IHTotal;
        CEepromSaveCenterModeData(modecnt);
    }

    SET_MODE_SEARCH_TYPE(modetype);
}
//----------------------------------------------------------------------------------------------------



void CEepromSaveUserFIFOModeData(StructModeUserFIFODataType stUserFIFOMode)
{
    BYTE ID;

    stUserFIFOMode.IHFreq = ((stUserFIFOMode.IVFreq & 0x0f00) << 4) | (stUserFIFOMode.IHFreq & 0x0fff);
    stUserFIFOMode.IVFreq = ((stUserFIFOMode.IVFreq & 0x00ff) << 8);

	ID = stSystemData.UserFIFOMode + 1;
    FLRandomPageSaveStruct(_FL_FIFO_DATA_PAGE_INDEX,ID,4, &stUserFIFOMode.ModeNum);
}
//----------------------------------------------------------------------------------------------------
void CEepromLoadUserFIFOModeData(BYTE ucNum, BYTE *pArray)
{
	bit fRT;
	BYTE i;
	BYTE ucPage = g_szRandomSavePage[_FL_FIFO_DATA_PAGE_INDEX];
	BYTE ID = ucNum + 1;

	for(i=0;i<4;i++)
	{
		fRT = FLLoadStruct(ucPage,ID++,4, pArray);
		pArray += 4;
	}

}
//----------------------------------------------------------------------------------------------------
void CEepromInitialUserFIFOModeData(void)
{
	// 初始化 就是写 0xFF 写以不用做这个动做
}
//----------------------------------------------------------------------------------------------------
void CSaveTVModeData(BYTE ucChannel)
{
    BYTE ID = ucChannel + 1;

    FLRandomPageSaveStruct(_FL_TVFREQ_PAGE_INDEX,ID,sizeof(StructTvInformationData), &stTVChannelInfo.TYPE);
}
//----------------------------------------------------------------------------------------------------

void CLoadTVModeData(BYTE ucChannel)
{
	bit fRT;
	BYTE ucPage = g_szRandomSavePage[_FL_TVFREQ_PAGE_INDEX];
	BYTE ID = ucChannel + 1;

 	fRT = FLLoadStruct(ucPage,ID,sizeof(StructTvInformationData), &stTVChannelInfo.TYPE);

    if(fRT == _FAIL)
    {
        stTVChannelInfo.TYPE = _NORMAL_TV_TYPE;
        stTVChannelInfo.Freq = _MIN_FREQ;
    }

    ucTVType = _GET_CH_COLOR_TYPE();
}
//----------------------------------------------------------------------------------------------------




#endif  // End of #if(_MEMORY_LOCATION == _FLASH)





