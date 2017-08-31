/*=============================================
  * Copyright (c)      Realtek Semiconductor Corporation, 2005
  * All rights reserved.
  * ============================================ */

#define __RTDACCESS__

#include "Core\Header\Include.h"

//----------------------------------------------------------------------------------------------------
// Scaler communication basic function
//----------------------------------------------------------------------------------------------------
void CScalerSendAddr(BYTE ucAddr, bit bAutoInc)
{
    if(bAutoInc)
        *(&MCU_SCA_INF_CTRL_FFF3) = 0x20;
    else
        *(&MCU_SCA_INF_CTRL_FFF3) = 0x00;

    *(&MCU_SCA_INF_ADDR_FFF4) = ucAddr;
}
//--------------------------------------------------
// Description  : Write a data array into registers of scaler
// Input Value  : ucAddr    --> Start address of register
//                ucLength  --> Numbers of data we want to write
//                pArray    --> Pointer of the writing data array
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------
void CScalerWrite(BYTE ucAddr, WORD usLength, BYTE *pArray, bit bAutoInc)
{
    CScalerSendAddr(ucAddr, bAutoInc);

    if(usLength > 0)
    {

        do
        {
            *(&MCU_SCA_INF_DATA_FFF5) = *pArray++;

        }while(--usLength);
    }


}

//--------------------------------------------------
// Description  : Read data from registers of scaler and put it into an reading data array
// Input Value  : ucAddr    --> Start address of register
//                ucLength  --> Numbers of data we want to read
//                pArray    --> Pointer of the reading data array
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------
void CScalerRead(BYTE ucAddr, BYTE ucLength, BYTE *pArray, bit bAutoInc)
{
    CScalerSendAddr(ucAddr, bAutoInc);

    if(ucLength > 0)
    {
        do
        {
            *pArray++ = *(&MCU_SCA_INF_DATA_FFF5);

        }while(--ucLength);

    }


}

/**
* CScalerWriteAmount
* Write a data array into register of scaler
* @param <ucAddress> {Start address of register}
* @param <ucCol> {The colume of blank}
* @param <ucLength> {Number of data}
* @param <ucValue> {The data wroten}
* @param <bAutoInc> {Address auto increase or not}
* @return {none}
*
*/
void CScalerWriteAmount(BYTE ucAddr, WORD usLength, BYTE ucValue, bit bAutoInc)
{
    CScalerSendAddr(ucAddr, bAutoInc);

    if(usLength > 0)
    {
        do
        {
            *(&MCU_SCA_INF_DATA_FFF5) = ucValue;

        }while(--usLength);
    }


}


//--------------------------------------------------
// Description  : Set the value into selected register
// Input Value  : ucAddr    --> Address of register
//                ucValue   --> Value we want to set
// Output Value : None
//--------------------------------------------------
void CScalerSetByte(BYTE ucAddr, BYTE ucValue)
{
    CScalerWrite(ucAddr, 1, &ucValue, _AUTOINC);
}

//--------------------------------------------------
// Description  : Set the value into selected register in data port
// Input Value  : ucAddr    --> Access Port Address of register
//                ucValue1  --> Data Port Value we want to set
//                ucValue2  --> Data Value we want to set
// Output Value : None
//--------------------------------------------------
void CScalerSetDataPortByte(BYTE ucAddr, BYTE ucValue1, BYTE ucValue2)
{
    if((ucAddr == _SU_ACCESS_PORT_33) || (ucAddr == _HW_ACCESS_PORT_60) 
    || (ucAddr == _CB_ACCESS_PORT_64) || (ucAddr == _PC_ACCESS_PORT_9A))
    {
        CScalerSetByte(ucAddr, 0x80);
        ucValue1 = ucValue1 | 0x80;
    }
    CScalerWrite(ucAddr, 1, &ucValue1, _AUTOINC);
    CScalerWrite(ucAddr + 1, 1, &ucValue2, _AUTOINC);
    CScalerSetByte(ucAddr, 0x00);
}

/**
* CScalerSetBit
* Set bit of register
* @param <ucAddr> {register address}
* @param <ucAnd> {data &}
* @param <ucOr> {data |}
* @return {none}
*
*/
void CScalerSetBit(BYTE ucAddr, BYTE ucAnd, BYTE ucOr)
{
    BYTE value;

    CScalerRead(ucAddr, 1, &value, _AUTOINC);
    value   = (value & ucAnd) | ucOr;
    CScalerWrite(ucAddr, 1, &value, _AUTOINC);
}


//--------------------------------------------------
// Description  : Set some bits of selected register in data port
// Input Value  : ucAddr    --> Access Port Address of register
//                ucValue   --> Data Port Value we want to set
//                ucAnd     --> & operation
//                ucOr      --> | operation
// Output Value : None
//--------------------------------------------------
#if(1)//_HDCP_SUPPORT == _ON)

void CScalerSetDataPortBit(BYTE ucAddr, BYTE ucValue, BYTE ucAnd, BYTE ucOr)
{
    BYTE value;

    if((ucAddr == _SU_ACCESS_PORT_33) || (ucAddr == _HW_ACCESS_PORT_60) 
    || (ucAddr == _CB_ACCESS_PORT_64) || (ucAddr == _PC_ACCESS_PORT_9A))
    {
        CScalerSetByte(ucAddr, 0x80);
        ucValue = ucValue | 0x80;
    }

    CScalerWrite(ucAddr, 1, &ucValue, _AUTOINC);
    CScalerRead(ucAddr + 1, 1, &value, _AUTOINC);

    value   = (value & ucAnd) | ucOr;
    if((ucAddr == _SU_ACCESS_PORT_33) || (ucAddr == _HW_ACCESS_PORT_60) 
    || (ucAddr == _CB_ACCESS_PORT_64) || (ucAddr == _PC_ACCESS_PORT_9A))
    {
        CScalerSetByte(ucAddr, 0x80);
        ucValue = ucValue | 0x80;
    }

    CScalerWrite(ucAddr, 1, &ucValue, _AUTOINC);
    CScalerWrite(ucAddr + 1, 1, &value, _AUTOINC);
    CScalerSetByte(ucAddr, 0x00);
}
#endif

//--------------------------------------------------
// Description  : Get bits from selected register
// Input Value  : ucAddr    --> Address of register
//                ucAnd     --> & operation
// Output Value : Value after & operation
//--------------------------------------------------
BYTE CScalerGetBit(BYTE ucAddr, BYTE ucAnd)
{
    BYTE value;

    CScalerRead(ucAddr, 1, &value, _AUTOINC);
    return (value & ucAnd);
}

/**
* CScalerCodeW
* Write a table to scaler
* @param <pArray> {Selected table which contains numbers, address auto increasing information, address of registers and values}
* @return {none}
*
*/
void CScalerCodeW(BYTE *pArray)
{
    BYTE length;

#if(_MCU_TYPE == _REALTEK_RTD3580D_EMCU)

    do
    {
        if((*pArray & 0xfc) == 0)
            return;

        length  = *pArray - 3;

        if((*(pArray + 1)) == _BURST)
        {
            *(&MCU_SCA_INF_CTRL_FFF3) = 0x20;
            *(&MCU_SCA_INF_ADDR_FFF4) = *(pArray + 2);

            pArray += 3;
            
            do
            {
                *(&MCU_SCA_INF_DATA_FFF5) = *pArray;

            }while(--length);

            pArray++;
        }
        else if((*(pArray + 1) == _AUTOINC) || (*(pArray + 1) == _NON_AUTOINC))
        {
            
            if(*(pArray + 1) == _NON_AUTOINC)
                *(&MCU_SCA_INF_CTRL_FFF3) = 0x20;
            else
                *(&MCU_SCA_INF_CTRL_FFF3) = 0x00;

            *(&MCU_SCA_INF_ADDR_FFF4) = *(pArray + 2);

            pArray += 3;

            do
            {
                *(&MCU_SCA_INF_DATA_FFF5) = *pArray++;

            }while(--length);

        }

    }while(_TRUE);

#else
		
    do
    {
        if((*pArray & 0xfc) == 0)
            return;

        length  = *pArray - 3;

        if((*(pArray + 1)) == _BURST)
        {
            CScalerSendAddr(*(pArray + 2), _WRITE, _NON_AUTOINC);

            pArray += 3;

            do
            {
                CScalerSendByte(*pArray);

            }while(--length);

            pArray++;
        }
        else if((*(pArray + 1) == _AUTOINC) || (*(pArray + 1) == _NON_AUTOINC))
        {
            CScalerSendAddr(*(pArray + 2), _WRITE, *(pArray + 1));

            pArray += 3;

            do
            {
                CScalerSendByte(*pArray++);

            }while(--length);

        }

        CScalerSendWriteStop();

    }while(_TRUE);

#endif		
}

#if(_HARDWARE_LOAD_FONT == _ON)
//--------------------------------------------------
// Description  : Load OSD font into OSD SRAM
// Input Value  : pArray    --> Font table
//                usOffset  --> Offset of font base start address
// Output Value : None
//--------------------------------------------------
void CScalerLoadHardwareVLCFont(BYTE *pArray, WORD usOffset)
{
    WORD num;

    pData[0] = 0xc0;
    pData[1] = 0x05;
    CScalerWrite(_OSD_ADDR_MSB_90, 2, pData, _AUTOINC);
    CScalerWrite(_OSD_DATA_PORT_92, 8, pArray, _NON_AUTOINC);
    

    num = ((WORD)*(pArray + 8) << 8) | *(pArray + 9);

    usOffset = usOffset * 9;
    usOffset += GET_OSD_MAP_FONTBASEADDRESS();//_OSD_FONT_START_POSITION;

    pData[0] = 0x80;
    pData[1] = 0x07;
    pData[2] = 0x01;
    CScalerWrite(_OSD_ADDR_MSB_90, 3, pData, _AUTOINC);    

    pData[0] = (HIBYTE(usOffset) & 0x000f) | 0xd0;
    pData[1] = LOBYTE(usOffset);
    CScalerWrite(_OSD_ADDR_MSB_90, 2, pData, _AUTOINC);    

    
    pArray += 10;

	CScalerSendAddr(_OSD_DATA_PORT_92, _NON_AUTOINC);

    for(usOffset=0;usOffset<num;usOffset++)
    {
        *(&MCU_SCA_INF_DATA_FFF5) = *pArray++;
    }

    pData[0] = 0x80;
    pData[1] = 0x07;
    pData[2] = 0x00;
    CScalerWrite(_OSD_ADDR_MSB_90, 3, pData, _AUTOINC);      
}
#endif

BYTE CScalerGetVLD(void)
{
	BYTE zerocnt = 0;

    while(!CScalerGetBitVLD())   zerocnt  += 1;

    if(zerocnt == 0)    return *(pData);

    switch(zerocnt)
    {
        case 1:
            return (CScalerGetBitVLD() ? *(pData + 1) : *(pData + 2));

        case 2:
            return (CScalerGetBitVLD() ? *(pData + 3) : *(pData + 4));

        case 3:
            return (CScalerGetBitVLD() ? *(pData + 5) : *(pData + 6));

        case 4:
            if (CScalerGetBitVLD())
            {
                return (CScalerGetBitVLD() ? *(pData + 7) : *(pData + 8));
            }
            else
            {
                if (CScalerGetBitVLD())
                {
                    return (CScalerGetBitVLD() ? *(pData + 9) : *(pData + 10));
                }
                else
                {
                    return (CScalerGetBitVLD() ? *(pData + 11) : *(pData + 12));
                }
            }

        default:
            if (CScalerGetBitVLD())
            {
                return (CScalerGetBitVLD() ? *(pData + 13) : *(pData + 14));
            }
            else
            {
                CScalerGetBitVLD();

                return *(pData + 15);
            }
    }
}

bit CScalerGetBitVLD(void)
{
    ucVLDTemp = ((ucVLDCnt & 0x07) == 0) ? *(pvldarray++) : (ucVLDTemp << 1);

    ucVLDCnt += 1;

    return (bit)(ucVLDTemp & 0x80);
}

//--------------------------------------------------
// Description  : Page select for scalar(Only for CR[A1]~CR[DF])
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerPageSelect(BYTE page)
{
	CScalerSetByte(_PAGE_SELECT_9F, (page & 0x0F));	
}


