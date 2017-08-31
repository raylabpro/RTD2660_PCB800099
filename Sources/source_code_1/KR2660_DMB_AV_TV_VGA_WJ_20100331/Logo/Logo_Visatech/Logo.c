#define __LOGO__

#include "Core\Header\Include.h"

BYTE code tLogoTemp;

//--------------------------------------------------

#if(_LOGO_ENABLE)


void CDrawLogo(void)
{
    SLogoOsdMap code *pMap;
    BYTE code *pOther;
	
    SetOSDDouble(_LOGO_SIZE);
	
    if(g_fUserPresetLogo)
        pMap = &tLogoOsdMap;
    else
        pMap = _EF_LOGO_OSDMAP_ADDRESS;

	g_ucRowCnt = pMap->LogoHeight;
	g_usFontBaseAddress = pMap->FontBassAddress;
	
	
// Init
    COsdFxDisableOsd();
    CCloseAllWindows();


	SetOSDRamAddress();
	
    // Row Command Byte 0
    // 0x80
    //   Character border/shadow     000: None
    //   Double character width         0: 0x01
    //   Double character height        0: 0x01
    DirectWOSDRam(0x00,g_ucRowCnt,THE_BYTE0,0x80);

    //Row End Command
    OutputChar(0x00);

    //Row Command Byte 1
    //    0x90
    //    Row height (1~32) : 18
    //    Column space      : 0
    DirectWOSDRam(0x00,g_ucRowCnt,THE_BYTE1,0x88);

	
    // Row Command Byte 2
	DirectWOSDRam(0x00,g_ucRowCnt,THE_BYTE2,pMap->LogoWidth);


    if(g_fUserPresetLogo)
        pOther = tLogoPalette;
    else
        pOther = _EF_LOGO_PALETTE_ADDRESS;

	// 装调色板
	COsdLogoColorPalette(pOther);    

	// 装字库
	if(pMap->Font1BitCnt)
	{
	    if(g_fUserPresetLogo)
	        pOther = tLogoFont1Bit;
	    else
	        pOther = KxEFLogo1BitAddress();
	        
		CScalerLoadHardwareVLCFont(pOther, pMap->Font1BitOffset);
	}
	
    if(pMap->Font2BitCnt)
    {
	    if(g_fUserPresetLogo)
	        pOther = tLogoFont2Bit;
	    else
	        pOther = KxEFLogo2BitAddress();
	        
    	CScalerLoadHardwareVLCFont(pOther, pMap->Font2BitOffset);
    }

    if(pMap->Font4BitCnt)
    {
	    if(g_fUserPresetLogo)
	        pOther = tLogoFont4Bit;
	    else
	        pOther = KxEFLogo4BitAddress();
    
    	CScalerLoadHardwareVLCFont(pOther, pMap->Font4BitOffset);

	}

    if(g_fUserPresetLogo)
        pOther = tLogoTable;
    else
        pOther = _EF_LOGO_TABLE_ADDRESS;	
	// Draw Logo
	COsdFxCodeWrite(pOther);


	// Set back ground color
	CAdjustBackgroundColor(pMap->BackGroundColorR, pMap->BackGroundColorG, pMap->BackGroundColorB);
	
	OSDPosition((WORD)pMap->LogoWidth * 12, (WORD)pMap->LogoHeight * 18, 50, 50, 0x03);
	
	COsdFxEnableOsd();

    CPowerPanelOn();
    CPowerLightPowerOn();

    CTimerDelayXms(2000);	
}
//--------------------------------------------------

void COsdFxCodeWrite(BYTE *pArray)
{
    BYTE cnt, temp;

    CScalerWrite(_OSD_ADDR_MSB_90, 2, pArray, _AUTOINC);
    pArray += 2;

    cnt = 0;

    while(_TRUE)
    {
        if(*pArray == _EXT_)
        {
            CScalerWrite(_OSD_DATA_PORT_92, cnt, pArray - cnt, _NON_AUTOINC);
            cnt = 0;

            if(*(pArray + 1) > 3)
                return;

            temp = _EXT_ + *(pArray + 1);

            if(*(pArray + 2) == _REPEAT_)
            {
                CScalerWriteAmount(_OSD_DATA_PORT_92, *(pArray + 3), temp, _NON_AUTOINC);
                pArray += 4;
            }
            else
            {
                CScalerWrite(_OSD_DATA_PORT_92, 1, &temp, _NON_AUTOINC);
                pArray += 2;
            }
        }
        else if(*pArray == _REPEAT_)
        {
            CScalerWrite(_OSD_DATA_PORT_92, cnt, pArray - cnt, _NON_AUTOINC);

            CScalerWriteAmount(_OSD_DATA_PORT_92, *(pArray + 1) - 1, *(pArray - 1), _NON_AUTOINC);

            pArray += 2;
            cnt = 0;
        }
        else if(*pArray == _NEXT_)
        {
            CScalerWrite(_OSD_DATA_PORT_92, cnt, pArray - cnt, _NON_AUTOINC);
            pArray++;
            cnt = 0;

            if(*(pArray + 1) != _END_)
            {
                CScalerWrite(_OSD_ADDR_MSB_90, 2, pArray, _AUTOINC);
                pArray += 2;
            }
            else
            {
                break;
            }
        }
        else if(*(pArray) == _END_)
        {
            CScalerWrite(_OSD_DATA_PORT_92, cnt, pArray - cnt, _NON_AUTOINC);
            break;
        }
        else
        {
            pArray++;
            cnt++;
        }
    }
}

//--------------------------------------------------
void COsdLogoColorPalette(BYTE *pColorPaletteArray)
{
	CScalerSetByte(_OVERLAY_LUT_ADDR_6E, 0x80);
	CScalerWrite(_COLOR_LUT_PORT_6F, 48, pColorPaletteArray, _NON_AUTOINC);
	CScalerSetByte(_OVERLAY_LUT_ADDR_6E, 0x00);
}
//-------------------------------------------------------------


#endif
