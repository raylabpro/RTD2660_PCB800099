#define __KX_EXTENDFUNC__

#include "Core\Header\Include.h"


//------------------------------------------------------------------------

void KxEFGetRealAddress(void)				// data count 8
{
	ucDDCCI_TxBuf[3] = ((DWORD)_EXTFUNC_REAL_BEGIN_ADDRESS >> 24);
	ucDDCCI_TxBuf[4] = ((DWORD)_EXTFUNC_REAL_BEGIN_ADDRESS >> 16);
	ucDDCCI_TxBuf[5] = ((DWORD)_EXTFUNC_REAL_BEGIN_ADDRESS >> 8);
	ucDDCCI_TxBuf[6] = ((DWORD)_EXTFUNC_REAL_BEGIN_ADDRESS);

	ucDDCCI_TxBuf[7] = ((DWORD)_EXTFUNC_REAL_END_ADDRESS >> 24);
	ucDDCCI_TxBuf[8] = ((DWORD)_EXTFUNC_REAL_END_ADDRESS >> 16);
	ucDDCCI_TxBuf[9] = ((DWORD)_EXTFUNC_REAL_END_ADDRESS >> 8);
	ucDDCCI_TxBuf[10] = ((DWORD)_EXTFUNC_REAL_END_ADDRESS);

	
}
//------------------------------------------------------------------------
void KxEFGetLogoInfo(void)			// data count 3
{
	ucDDCCI_TxBuf[3] = tEFLogoInfo.Support;
	ucDDCCI_TxBuf[4] = (tEFLogoInfo.Offset >> 8);
	ucDDCCI_TxBuf[5] = (tEFLogoInfo.Offset);
	
}
//------------------------------------------------------------------------
void KxEFGetEdidGroupCnt(void)			// data count 1
{
	ucDDCCI_TxBuf[3] = g_EFEdidGroupCnt;
}
//------------------------------------------------------------------------
void KxEFGetEdidInfo(BYTE ucIndex)			// data count 20
{
	ucDDCCI_TxBuf[3] = tEFEdids[ucIndex].Support;

	ucDDCCI_TxBuf[4] = (tEFEdids[ucIndex].Offset >> 8);
	ucDDCCI_TxBuf[5] = (tEFEdids[ucIndex].Offset);

	MemoryCpy(&ucDDCCI_TxBuf[5],tEFEdids[ucIndex].Name,16);

	ucDDCCI_TxBuf[22] = tEFEdids[ucIndex].Type;
	
	
}
//------------------------------------------------------------------------
void KxEFGetIRInfo(void)			// data count 4
{

	ucDDCCI_TxBuf[3] = tEFIR.Support;

	ucDDCCI_TxBuf[4] = (tEFIR.Offset >> 8);
	ucDDCCI_TxBuf[5] = tEFIR.Offset;
	ucDDCCI_TxBuf[6] = tEFIR.KeyCount;
}
//------------------------------------------------------------------------


void KxEFGetIRKeyInfo(BYTE ucIndex)			// data count 17
{
	MemoryCpy(&ucDDCCI_TxBuf[3],tEFIRKeys[ucIndex].Name,16);

	ucDDCCI_TxBuf[19] = tEFIRKeys[ucIndex].KeyMessage;
	
}
//------------------------------------------------------------------------
void KxEFGetIRValue(BYTE *p)
{
	BYTE ucIrdaStatus = MCU_IR_STATUS_FF89;
	
	if (ucIrdaStatus & (_BIT4 | _BIT3))
	{
		*p++ = MCU_IR_DATA2_FF8C;
		*p++ = MCU_IR_DATA3_FF8D;
		*p++ = MCU_IR_DATA4_FF8E;
		*p++ = MCU_IR_DATA5_FF8F;
	}
	else
	{
		*p++ = 0x00;
		*p++ = 0x00;
		*p++ = 0x00;
		*p++ = 0x00;
		
	}
}
//------------------------------------------------------------------------
void KxEFGetSDKeyInfo(void)			// data count 4
{

	ucDDCCI_TxBuf[3] = tEFSDKeyInf.Support;

	ucDDCCI_TxBuf[4] = (tEFSDKeyInf.Offset >> 8);
	ucDDCCI_TxBuf[5] = tEFSDKeyInf.Offset;
	ucDDCCI_TxBuf[6] = tEFSDKeyInf.KeyCount;
}
//------------------------------------------------------------------------

void KxEFGetOneSDKeyInfo(BYTE ucIndex) // data count 17
{
	MemoryCpy(&ucDDCCI_TxBuf[3],tEFSDKey[ucIndex].Name,16);

	ucDDCCI_TxBuf[19] = tEFSDKey[ucIndex].KeyMessage;
	
}
//------------------------------------------------------------------------
void KxEFGetSDKeyMask(void)
{
	ucDDCCI_TxBuf[3] = CKeyScanIO();
}
//------------------------------------------------------------------------



void KxEFGetADPortInfo(void)			// data count 5
{
	ucDDCCI_TxBuf[3] = tEFADC.Support;

	ucDDCCI_TxBuf[4] = (tEFADC.Offset >> 8);
	ucDDCCI_TxBuf[5] = tEFADC.Offset;
	ucDDCCI_TxBuf[6] = tEFADC.ADIOCount;
	ucDDCCI_TxBuf[7] = tEFADC.ADKeyCount;
}
//------------------------------------------------------------------------
void KxEFGetADKeyInfo(BYTE ucIndex)			// data count 17
{
	MemoryCpy(&ucDDCCI_TxBuf[3],tEFIRKeys[ucIndex].Name,16);

	ucDDCCI_TxBuf[19] = tEFIRKeys[ucIndex].KeyMessage;
}
//------------------------------------------------------------------------
void KxEFGetADCValue(BYTE *p)
{
	MCU_ADC_ACONTROL_FF08 = 0x82;			//start adc convert(STRT_ADC_ACKT=1) 
	MCU_ADC_BCONTROL_FF0E = 0x82;			//start adc convert(STRT_ADC_ACKT=1) 

	while(MCU_ADC_ACONTROL_FF08 & 0x80)
	{
		_nop_();
	}


	*p++ = MCU_ADC_A0_CONVERT_RESULT_FF09 >> 2;	
	*p++ = MCU_ADC_A1_CONVERT_RESULT_FF0A >> 2;	
	*p++ = MCU_ADC_A2_CONVERT_RESULT_FF0B >> 2;	
	*p++ = MCU_ADC_A3_CONVERT_RESULT_FF0C >> 2;	
	*p++ = MCU_ADC_A4_CONVERT_RESULT_FF0D >> 2;	


	//只取高 8 位，低二位忽略
	while(MCU_ADC_BCONTROL_FF0E & 0x80)
	{
		_nop_();
	}

	*p++ = ADC_B0H_convert_result_FF15;			
	*p++ = ADC_B1H_convert_result_FF16;	
	*p++ = ADC_B2H_convert_result_FF17;	
}
//------------------------------------------------------------------------
void KxEFPanelInfo(void)			// data count 3
{
	ucDDCCI_TxBuf[3] = tEFPanel.Support;

	ucDDCCI_TxBuf[4] = (tEFPanel.Offset >> 8);
	ucDDCCI_TxBuf[5] = tEFPanel.Offset;
}
//------------------------------------------------------------------------
void KxEFGetOtherFuncCnt(void)			// data count 1
{
	ucDDCCI_TxBuf[3] = g_EFOtherCnt;
}
//------------------------------------------------------------------------
void KxEFGetOtherFuncInfo(BYTE ucIndex)			// data count 20
{
	ucDDCCI_TxBuf[3] = tEFOtherFunc[ucIndex].Support;

	ucDDCCI_TxBuf[4] = (tEFOtherFunc[ucIndex].Offset >> 8);
	ucDDCCI_TxBuf[5] = (tEFOtherFunc[ucIndex].Offset);

	MemoryCpy(&ucDDCCI_TxBuf[5],tEFOtherFunc[ucIndex].Name,16);

	ucDDCCI_TxBuf[22] = tEFOtherFunc[ucIndex].DefaultValue;
}
//------------------------------------------------------------------------






//------------------------------------------------------------------------
BYTE ScanExtendIR(void)
{

	BYTE ucIRCode; 
    BYTE ucIRMessage = _NONE_KEY_MESSAGE;
    BYTE code *pIRTable = _EF_IR_KEYMSG_ADDRESS;

	if((pIRTable[0] == ucIrQueue[0]) && (pIRTable[1] == ucIrQueue[1]))
	{
		pIRTable += 2;
		
		if(ucIrQueue[2] == (~ucIrQueue[3])) 
		{
			ucIRCode = ucIrQueue[2];

			// Search key message
			while(1)
			{
				if((pIRTable[0] == 0) && (pIRTable[1] == 0))
				{
					break;
				}

				if (ucIRCode == pIRTable[0])
				{
					ucIRMessage = pIRTable[1];
					break;
				}

				pIRTable += 2;

			}

			ucRepKeyCount = 0;
		}
	} 
	
	return ucIRMessage;
}
//------------------------------------------------------------------------
void GetExtendEnable(void)
{
	BYTE code *p = _EF_IR_ENABLE_ADDRESS;

	// iR 
       if(*p == 0xFF)
		g_bUsePresetIR = 1;
	else 
		g_bUsePresetIR = 0;

    // sdkey
	p = _EF_SDKEY_ENABLE_ADDRESS;

	if(*p == 0xFF)
		g_bUsePresetKey = 1;
	else g_bUsePresetKey = 0;
	
    
    // logo
	p = _EF_LOGO_ENABLE_ADDRESS;

	if(*p == 0xFF)
		g_fUserPresetLogo = 1;
	else
		g_fUserPresetLogo = 0;
    
	
}
//------------------------------------------------------------------------

BYTE CIOMaskToKeyMaskExt(BYTE ucIOMask)
{
	BYTE code *p = _EF_SDKEY_KEYMSG_ADDRESS;
	BYTE ucKeyState = _NONE_KEY_MASK;
	
	while(1)
	{
		if(p[0] == 0xFF && p[1] == 0xFF)
			break;

		if(ucIOMask & p[1])
			ucKeyState |= p[0];	

		p += 2;
	}

	return ucKeyState;
}
//--------------------------------------------------
WORD KxEFLogo1BitAddress(void)
{
    WORD *p = _EF_LOGO_SAVE_1BITFONT_ADDRESS;
    WORD usAddress = _EF_LOGO_BEGIN_ADDRESS + (*p);
    return usAddress;
}
//--------------------------------------------------
WORD KxEFLogo2BitAddress(void)
{
    WORD *p = _EF_LOGO_SAVE_2BITFONT_ADDRESS;
    WORD usAddress = _EF_LOGO_BEGIN_ADDRESS + (*p);
    return usAddress;
}
//--------------------------------------------------
WORD KxEFLogo4BitAddress(void)
{
    WORD *p = _EF_LOGO_SAVE_4BITFONT_ADDRESS;
    WORD usAddress = _EF_LOGO_BEGIN_ADDRESS + (*p);
    return usAddress;

}
//--------------------------------------------------


