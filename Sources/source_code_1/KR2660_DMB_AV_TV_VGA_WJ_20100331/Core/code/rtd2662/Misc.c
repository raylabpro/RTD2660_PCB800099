//----------------------------------------------------------------------------------------------------
// ID Code      : Misc.c No.0002
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#define __MISC__

#include "Core\Header\Include.h"

//----------------------------------------------------------------------------------------------------
// Polling Events
//----------------------------------------------------------------------------------------------------



#if(_HSYNC_TYPE_DETECTION == _AUTO_RUN)
/**
 * CMiscHsyncTypeAutoRunFlagPollingEvent
 * Hsync Type Detection Auto Run flag polling event
 * @param <none>
 * @return {_TRUE if event occurs,_FALSE if not}
 *
*/
//--------------------------------------------------
// Description  : Hsync Type Detection Auto Run flag polling event
// Input Value  : None
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
bit CMiscHsyncTypeAutoRunFlagPollingEvent(void)
{
    if((bit)CScalerGetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, _BIT7))
        return _TRUE;
    else
        return _FALSE;
}
#endif  // End of #if(_HSYNC_TYPE_DETECTION == _AUTO_RUN)

/**
 * CMiscModeMeasurePollingEvent
 * Measure start/end polling event
 * @param <none>
 * @return {none}
 *
*/
//--------------------------------------------------
// Description  : Measure start/end polling event
// Input Value  : None
// Output Value : Return _TRUE if measure finished
//--------------------------------------------------
bit CMiscModeMeasurePollingEvent(void)
{
#if (0)
	BYTE count=20;

	do{
		if(!(bit)CScalerGetBit(_MEAS_HS_PERIOD_H_52, _BIT5))
			return _TRUE;
		CTimerDelayXms(5);
		count--;
	}while(count!=0);
	return _FALSE;
#else
    if(!(bit)CScalerGetBit(_MEAS_HS_PERIOD_H_52, _BIT5))
        return _TRUE;
    else
        return _FALSE;
#endif
}

bit CMiscMeasureResultPOPPollingEvent(void)
{
    if(!(bit)CScalerGetBit(_MEAS_HS_PERIOD_H_52, _BIT6))
        return _TRUE;
    else
        return _FALSE;
}


#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Auto measure start/end polling event
// Input Value  : None
// Output Value : Return _TRUE if auto measure finished
//--------------------------------------------------
bit CMiscAutoMeasurePollingEvent(void)
{
    if(!(bit)CScalerGetBit(_AUTO_ADJ_CTRL1_7D, _BIT0))
        return _TRUE;
    else
        return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : Apply double buffer polling event
// Input Value  : None
// Output Value : Return _TRUE if apply double buffer finished
//--------------------------------------------------
bit CMiscApplyDoubleBufferPollingEvent(void)
{
    if(!(bit)CScalerGetBit(_VGIP_CTRL_10, _BIT5))
        return _TRUE;
    else
        return _FALSE;
}

#if(((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON)) && (_DVI_LONG_CABLE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : TMDS transition measure polling event
// Input Value  : None
// Output Value : Return _TRUE if measure finished
//--------------------------------------------------
bit CMiscTMDSMeasureEvent(void)
{
    CScalerPageSelect(_PAGE2);
    if(!(bit)CScalerGetBit(_P2_TMDS_MEAS_RESULT0_A2, _BIT7))
        return _TRUE;
    else
        return _FALSE;
}

//--------------------------------------------------
// Description  : TMDS CRC measure polling event
// Input Value  : None
// Output Value : Return _TRUE if CRC measure finished
//--------------------------------------------------
bit CMiscTMDSCRCEvent(void)
{
    CScalerPageSelect(_PAGE2);
    if(!(bit)CScalerGetBit(_P2_TMDS_CTRL_A4, _BIT0))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif  // End of #if(((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON)) && (_DVI_LONG_CABLE_SUPPORT == _ON))


//----------------------------------------------------------------------------------------------------
// Misc Functions
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Enable double buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscEnableDoubleBuffer(void)
{
    CScalerSetBit(_VGIP_CTRL_10, ~_BIT4, _BIT4);
}
//--------------------------------------------------
// Description  : Disable double buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscDisableDoubleBuffer(void)
{
    CScalerSetBit(_VGIP_CTRL_10, ~_BIT4, 0x00);
}

//--------------------------------------------------
// Description  : Apply double buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscApplyDoubleBuffer(void)
{
    BYTE ucTimeout=12;
    if((bit)CScalerGetBit(_VGIP_CTRL_10, _BIT4))
    {
        CScalerSetBit(_VGIP_CTRL_10, ~_BIT5, _BIT5);
        do
            {
                CTimerDelayXms(5);
                if(CMiscApplyDoubleBufferPollingEvent())
                {
                    break;
                }
            }
            while(--ucTimeout); 
    }
}

//--------------------------------------------------
// Description  : Clear status Reg[02] and Reg[03]
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscClearStatusRegister(void)
{
    CScalerSetByte(_STATUS0_02, 0x00);
    CScalerSetByte(_STATUS1_03, 0x00);
}

//--------------------------------------------------
// Description  : Set pin share
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscSetPinShare(void)
{
        
    //MCU_PIN_SHARE_CTRL00_FF96 = (((BYTE)_PIN_58_59_DDC1_ENABLE<<7) | (_PIN_58<<5) | (_PIN_59<<3) | (_PIN_50));
    // uart add
    MCU_PIN_SHARE_CTRL00_FF96 = (MCU_PIN_SHARE_CTRL00_FF96 & 0xF8) | (_PIN_50);
    MCU_PIN_SHARE_CTRL01_FF97 = (((BYTE)_PIN_51<<6) | (_PIN_64<<3) | (_PIN_65));
    MCU_PIN_SHARE_CTRL02_FF98 = (((BYTE)_PIN_52<<6) | (_PIN_66<<3) | (_PIN_67));
    MCU_PIN_SHARE_CTRL03_FF99 = (((BYTE)_PIN_53<<6) | (_PIN_69<<3) | (_PIN_70));
    MCU_PIN_SHARE_CTRL04_FF9A = (((BYTE)_PIN_55<<5) | (_PIN_56_57_IIC_ENABLE<<4) | (_PIN_56<<2) | (_PIN_57));
    MCU_PIN_SHARE_CTRL05_FF9B = (((BYTE)_PIN_68<<4) | (_PIN_71));
    MCU_PIN_SHARE_CTRL06_FF9C = (((BYTE)_PIN_54<<6) | (_PIN_96<<3) | (_PIN_97));
    MCU_PIN_SHARE_CTRL07_FF9D = (((BYTE)_PIN_74to83<<6) | (_PIN_99<<3) | (_PIN_100));
    MCU_PIN_SHARE_CTRL08_FF9E = (((BYTE)_PIN_102<<3) | (_PIN_105));
    MCU_PIN_SHARE_CTRL09_FF9F = (((BYTE)_PIN_98<<6) | (_PIN_101<<3) | (_PIN_108));
    MCU_PIN_SHARE_CTRL0A_FFA0 = (((BYTE)_PIN_103<<4) | (_PIN_104<<1));
    MCU_PIN_SHARE_CTRL0B_FFA1 = (((BYTE)_PIN_109<<4) | (_PIN_110));
    MCU_PIN_SHARE_CTRL0C_FFA2 = (((BYTE)_PIN_111<<4) | (_PIN_112));
    MCU_PIN_SHARE_CTRL0D_FFA3 = (((BYTE)_PIN_113<<4) | (_PIN_114));
    MCU_PIN_SHARE_CTRL0E_FFA4 = (((BYTE)_PIN_124<<6) | (_PIN_123<<4) | (_PIN_122<<2) | (_PIN_121));
}


//----------------------------------------------------------------------------------------------------
// Debug Functions
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : ISP process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#if(_DEBUG_TOOL == _ISP_FOR_RTD3580D_EMCU)
void CMiscIspack(void)
{
    BYTE halt = 0;

    do
    {
        if(bRunCommand)
        {
            switch(ucDdcciData[0])
            {

                case 0x80:
                    halt = ucDdcciData[1];
                    break;

                // andy extand 
                case 0x10:
                     ucVirtualKey = ucDdcciData[1];
                     break;                    

                case 0x41:
                    MCU_I2C_IRQ_CTRL2_FF2A  |= 0x20;
                    CScalerRead(ucDdcciData[1], 1, pData, _NON_AUTOINC);
                    TxBUF= pData[0];
                    MCU_I2C_DATA_OUT_FF26 = pData[0];
                    break;

                case 0x44:
                    MCU_I2C_IRQ_CTRL2_FF2A  |= 0x20;
                    CI2cRead(ucDdcciData[2], ucDdcciData[1], 1, pData);
                    TxBUF = pData[0];
                    MCU_I2C_DATA_OUT_FF26 = TxBUF;
                    
                    break;

                // for RTD & I2c Device
                case 0x22:
                    ucDdcciData[2] = ucDdcciData[1];
                    break;

                case 0x28:
                    ucDdcciData[3] = ucDdcciData[1];
                    break;

                case 0x24:
                    CI2cWrite(ucDdcciData[2], ucDdcciData[1], 1, &ucDdcciData[3]);
                    
                    break;
                    
                case 0x20:
                    CScalerSetByte(ucDdcciData[2], ucDdcciData[1]);
                    break;

                default:

                    break;
            }

            bRunCommand=0;
            ucDdcciCommandNumber = 0;
        }
    }
    while(halt != 0);
}

//--------------------------------------------------
void GetVirtualKey(void)
{
    if(ucKeyMessage == _NONE_KEY_MESSAGE)
    {
        ucKeyMessage = ucVirtualKey;
    }
    ucVirtualKey = _NONE_KEY_MESSAGE;
}
//--------------------------------------------------

// Description  : ISP for RTD3580D Embeded MCU Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CInitIspack(void) 
{
    MCU_I2C_SET_SLAVE_FF23 = 0x6a;
    MCU_I2C_IRQ_CTRL_FF28  = 0x3f;
    MCU_IRQ_PRIORITY_FF01  = 0x01;      //assign int1 (IRQ2)

    EX1  = 1;
}

#endif
//--------------------------------------------------

/**
 * CMiscIspDebugProc
 * Debug tool process
 * @param <none>
 * @return {none}
 *
 */
void CMiscIspDebugProc(void)
{
    #if(_DEBUG_TOOL == _ISP_FOR_RTD3580D_EMCU)
    CMiscIspack();
    #endif

    #if(_DEBUG_TOOL == _ISP_FOR_DDCCI && _SUPPORTDDCCI)
    CDDCCICommand();
    #endif

    #if(_RS232_EN)
    CUartHandler();
    #endif
}
//--------------------------------------------------
void CDDCCIInitial()
{
    #if(_DEBUG_TOOL == _ISP_FOR_RTD3580D_EMCU)
    CInitIspack();
    #endif

    #if((_DEBUG_TOOL == _ISP_FOR_DDCCI) && _SUPPORTDDCCI)
    CInitDDCCI();
    #endif

    CInitEdid();
}
//--------------------------------------------------
void CInitEdid(void)
{
    MCU_HDMI_DDC_ENA_FF2C = 0x00;  //disable HDMI DDC channel
    
//Gary for Interior HDMI  DDC   20070711
#if ((_HDMI_EDID==_ON)&&(_HDMI_DDC_CHANNEL_SELECT==_DDC2))
              
    MCU_DVI_DDC_ENA_FF1E  = 0x01;
    MCU_HDMI_DDC_ENA_FF2C = 0x00;//0x01;  //disable HDMI DDC channel
    MCU_DDCRAM_PART_FF21  = 0x2b;  //addcram_st=2(0xfd00),dddcram_st=20(0xfd80),hddcram_st=3 
    
#elif((_HDMI_EDID==_ON)&&(_HDMI_DDC_CHANNEL_SELECT==_DDC3))

    MCU_DVI_DDC_ENA_FF1E  = 0x01;  //disable DVI DDC channel
    MCU_HDMI_DDC_ENA_FF2C = 0x01;  
    MCU_DDCRAM_PART_FF21  = 0x3a;  //addcram_st=3(0xFd80),dddcram_st=2(0xfd80),hddcram_st=2(0xfe00) 

#else
    
    MCU_DVI_DDC_ENA_FF1E  = 0x00;  //Disable DVI DDC channel
    MCU_HDMI_DDC_ENA_FF2C = 0x00;  //disable HDMI DDC channel
    MCU_DDCRAM_PART_FF21  = 0x3f;  //addcram_st=3,dddcram_st=3,hddcram_st=3 (Xram=640 Byte) 
#endif  

#if _VGA_EDID
    MCU_ADC_DDC_ENA_FF1B = 0x01;  
#else
    MCU_ADC_DDC_ENA_FF1B = 0x00;   //Disable ADC DDC channel
#endif

    CLoadEdid();
}
//--------------------------------------------------
void CLoadEdid(void)
{
    WORD i;

    BYTE xdata *p;
    BYTE code *pEdid;
    
    #if(_HDMI_EDID == _ON) 
    p = MCU_DDCRAM_HDMI;
    pEdid = &tHDMI_EDID_DATA[0];
    for(i=0;i<256;i++)
    {
        *p++ = *pEdid++;
    }
    #endif

    #if(_DVI_EDID == _ON)
    p = MCU_DDCRAM_DVI;
    pEdid = &tDVI_EDID_DATA[0];
    for(i=0;i<128;i++)
    {
        *p++ = *pEdid++;
    }
    
    #endif


    #if(_VGA_EDID == _ON)
    p = MCU_DDCRAM_VGA;
    pEdid = &tVGA_EDID_DATA[0];
    for(i=0;i<128;i++)
    {
        *p++ = *pEdid++;
    }
    #endif  
}
//--------------------------------------------------

