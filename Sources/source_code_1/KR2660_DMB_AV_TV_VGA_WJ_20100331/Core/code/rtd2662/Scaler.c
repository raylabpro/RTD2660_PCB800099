//----------------------------------------------------------------------------------------------------
// ID Code      : Scaler.c No.0003
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

#define __SCALER__

#include "Core\Header\Include.h"

//--------------------------------------------------
// Description  : Get bytes from selected register in data port
// Input Value  : ucAddr    --> Access Port Address of register
//                ucValue   --> Data Port Address we want to Get
//                ucLength  --> Numbers of data we want to read
//                pArray    --> Pointer of the reading data array
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------

void CScalerGetDataPortByte(BYTE ucAddr, BYTE ucValue, BYTE ucLength, BYTE *pArray, BIT bAutoInc)
{
    if(ucLength > 0)
    {
        if((ucAddr == _SU_ACCESS_PORT_33) || (ucAddr == _HW_ACCESS_PORT_60) 
        || (ucAddr == _CB_ACCESS_PORT_64) || (ucAddr == _PC_ACCESS_PORT_9A))
        {
            CScalerSetByte(ucAddr, 0x80);
            ucValue = ucValue | 0x80;
        }

        CScalerSetByte(ucAddr, ucValue);
        CScalerRead( ucAddr + 1, ucLength, pArray, bAutoInc);
    }
}

//--------------------------------------------------
// Description  : Initial settings for scaler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerInitial(void)
{
    // Software reset for scaler
    CScalerSetBit(_HOST_CTRL_01, ~_BIT0, _BIT0);
    CTimerDelayXms(20);
    CScalerSetBit(_HOST_CTRL_01, ~_BIT0, 0x00);
    CIrdaInitial();
    CScalerCodeW(tSCALER_POWERUP_INITIAL);
    
#if(_YPBPR_SUPPORT && _YPBPR_HW_AUTO_SOY == _ENABLE)
    CYPbPrHWAutoSOY();
#endif

#if (_HDMI_SUPPORT == _ON)
    CScalerCodeW(tSCALER_POWERUP_HDMI);
#else
    CScalerCodeW(tSCALER_POWERUP_DVI);
#endif  

    CScalerReset();

#if(_HDCP_SUPPORT == _ON)
    bHot_Plug = _HOT_PLUG_LOW;
    bHot_Plug2 = _HOT_PLUG_LOW;    
	CScalerPageSelect(_PAGE2);
	CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT1 | _BIT0),  0);
    CAdjustHDCP();
    CTimerDelayXms(90);
    //bHot_Plug = _HOT_PLUG_HI;
    bHot_Plug = _HOT_PLUG_HI;
    bHot_Plug2 = _HOT_PLUG_HI;       
#endif
}


//--------------------------------------------------
// Description  : Reset scaler process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerReset(void)
{
    CScalerCodeW(tSCALER_RESET_TABLE);
    /*
    CScalerCodeW(tSCALER_POWERUP_INITIAL);
#if (_HDMI_SUPPORT == _ON)
    //if(CHdmiFormatDetect())//Input source is the HDMI format.
        CScalerCodeW(tSCALER_POWERUP_HDMI);
    //else//DVI
#else
        CScalerCodeW(tSCALER_POWERUP_DVI);
#endif     */
    CMiscSetPinShare();

	MCU_PIN_DRIVING_CTRL10_FFA6 = 0x07;
 
    CAdjustDisableWatchDog(_WD_ALL);

    CMiscClearStatusRegister();

    CScalerInitialDisplayInterface();

    CScalerInitialDisplayOutput();

    CModeSetFreeRun();
    /*
    //EricLee add for VGA
    if (_GET_INPUT_SOURCE() == _SOURCE_VGA)
    {
        CScalerPageSelect(_PAGE0);
        CScalerSetByte(_P0_ADC_DCR_CTRL_D3,0x11);
        //CScalerSetByte(_P0_ADC_CLAMP_CTRL0_D4,0x00);
    }        */

    if(GET_POWERSTATUS())
    {
        CScalerEnableDisplayOutput();
        // OSD power up initial
        CScalerCodeW(tOSD_POWERUP_INITIAL);
        //EricLee add for YPBPR
        if (_GET_INPUT_SOURCE() == _SOURCE_YPBPR||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1)
        {
            CScalerPageSelect(_PAGE0);
            CScalerSetByte(_P0_ADC_DCR_CTRL_D3,0x11);
            CScalerSetByte(_P0_ADC_CLAMP_CTRL0_D4,0x00);
        }        

        CAdjustTMDSErrorCorrectionOn();
        //CAdjustSRGB();
		if (Panel.DHWidth > 1000)
#if(_GAMMA_TYPE ==  _COMPACT_GAMMA_NORMAL_TABLE)
        CAdjustGamma(_COMPACT_GAMMA_NORMAL_TABLE, tGAMMA_COMPACT1, tGAMMA_COMPACT1, tGAMMA_COMPACT1);
#elif(_GAMMA_TYPE == _FULL_GAMMA_NORMAL_TABLE)||(_GAMMA_TYPE == _FULL_GAMMA_COMPRESS_TABLE2)    
        CAdjustGammaTable(GET_GAMMA());
#endif

#if(_DISP_BIT == _DISP_24_BIT)
        CAdjustDither(tDITHER_SEQ_TABLE_0, tDITHER_TABLE_10_TO_8);
#else            
        CAdjustDither(tDITHER_SEQ_TABLE_0, tDITHER_TABLE_10_TO_6);
#endif

        CScalerSetBit(_IPH_ACT_WID_H_16, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
        //if(GET_INPUTSOURCE_TYPE() == _SOURCE_VGA)
        //  CScalerSetBit(_IPH_ACT_WID_H_16, ~(_BIT6 | _BIT5 | _BIT4), ((_ADC0_INPUT_SWAP_RG << 4) | (_ADC0_INPUT_SWAP_RB << 5)| (_ADC0_INPUT_SWAP_GB << 6)));
        //else if(GET_INPUTSOURCE_TYPE() == _SOURCE_YPBPR)
        //  CScalerSetBit(_IPH_ACT_WID_H_16, ~(_BIT6 | _BIT5 | _BIT4), ((_ADC1_INPUT_SWAP_RG << 4) | (_ADC1_INPUT_SWAP_RB << 5)| (_ADC1_INPUT_SWAP_GB << 6)));      
        
        CAdjustBrightness();
        CAdjustContrast();

#if(_OD_SUPPORT == _ON)
        CMemoryLoadODLUT(_OD_TABLE_COMMON);
        CMemorySDRAMReset();
#endif

#if(_VIDEO_SUPPORT == _ON)
        // Initial video settings
        CVideoInitial();
        kx_CVDCOutputDisable();
#else
        CInitInputSource();
#endif  // End of #if(_VIDEO_SUPPORT == _ON)


    }
    else
    {
#if(AUDIO_TYPE == _AUDIO_SC7313)
        CSc7313MuteOn();
#endif
        CPowerDPLLOff();
        //CScalerSetByte(_HOST_CTRL_01, 0x42);//731301
        //CScalerSetBit(_HOST_CTRL_01, ~_BIT1,(_BIT4 | _BIT1)); //V307 modify//731301
        CPowerDownScaler();
        CScalerDisableDisplayOutput();
    }
}

//--------------------------------------------------
void CCustomerInitial(void)
{
   //@ For RTD2662 version auto detect using.
   CScalerPageSelect(_PAGE0);//eric 20070529
   CScalerRead(_P0_POWER_ON_RESET_F3, 1, &pData[0], _NON_AUTOINC);

   if((pData[0]&0xC0) == 0xC0)
   {//@Version B
        CScalerSetByte(_TCON_ADDR_PORT_8B, _LVDS_CTRL1_A1);
        CScalerSetByte(_TCON_DATA_PORT_8C, 0xD7);
   }
   else
   {//@Version A
        CScalerSetByte(_TCON_ADDR_PORT_8B, _LVDS_CTRL1_A1);
        CScalerSetByte(_TCON_DATA_PORT_8C, 0x17);
   }
}

//--------------------------------------------------
// Description  : Initial display interface for TTL, LVDS and RSDS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerInitialDisplayInterface(void)
{
#if(_OUTPUT_BUS == _PANEL_TTL)
    CScalerCodeW(tTTL_INITIAL);
#endif

#if(_OUTPUT_BUS == _PANEL_LVDS)
    CScalerCodeW(tLVDS_INITIAL);
#endif

#if(_OUTPUT_BUS == _PANEL_RSDS)
    CScalerCodeW(tLVDS_INITIAL);
    CScalerCodeW(tRSDS_INITIAL);
#endif

    // Set LVDS MAP  EricLee modify
#if(_LVDS_MAP == _LVDS_MAP1)
    CScalerSetDataPortBit(_TCON_ADDR_PORT_8B, _TCON_LVDS_CTRL3_A3, ~_BIT0, 0x00);
#else
    CScalerSetDataPortBit(_TCON_ADDR_PORT_8B, _TCON_LVDS_CTRL3_A3, ~_BIT0, _BIT0);
#endif

    // Eric Lee add for IC version auto detect
    CCustomerInitial();
}

//--------------------------------------------------
// Description  : Initial display output from Panel.h settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerInitialDisplayOutput(void)
{
    // Display signal control settings
    BYTE ucTemp = 0x00;

#if(_DISP_BIT == _DISP_18_BIT)
    ucTemp |= _BIT4;
#endif

#if(_DISPLAY_PORT == _DISP_DOUBLE_PORT)
    ucTemp |= _BIT2; 
#endif
    
    CScalerSetBit(_VDISP_CTRL_28, ~(_BIT4 | _BIT2), ucTemp);
    CScalerSetByte(_VDISP_SIGINV_29, Panel.PanelConfig & (~_BIT3));
}

//--------------------------------------------------
// Description  : Enable display output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerEnableDisplayOutput(void)
{
    CScalerSetBit(_VDISP_CTRL_28, ~(_BIT6 | _BIT1), _BIT1);
    CScalerSetBit(_VDISP_CTRL_28, ~_BIT0, _BIT0);

    CScalerSetBit(_VDISP_CTRL_28, ~_BIT7, _BIT7);
    CScalerSetBit(_VDISP_CTRL_28, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : Disable display output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerDisableDisplayOutput(void)
{
    CScalerSetBit(_VDISP_CTRL_28, ~(_BIT6 | _BIT1), _BIT6);
    CScalerSetBit(_VDISP_CTRL_28, ~_BIT0, 0x00);
}

#if(_NONLINEAR_SCALING)

//--------------------------------------------------
// Description  : Disable Nonlinear scale up function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerDisableNonlinearScaleUp(void)
{
    ((DWORD*) pData)[0] = 0; //Disable non linear scale up first
    
    CScalerSetByte(_SU_ACCESS_PORT_33, 0x8c);
    CScalerSetByte(_SU_ACCESS_PORT_33, 0x8c);
    CScalerWrite(_SU_DATA_PORT_34, 4, pData, _NON_AUTOINC);
    CScalerSetByte(_SU_ACCESS_PORT_33, 0x00);
}

//--------------------------------------------------
// Description  : Disable Nonlinear scale down function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerDisableNonlinearScaleDown(void)
{
    
    CScalerSetBit(_SCALE_DOWN_CTRL_23, 0xf7, 0x00);//disable non-linear scale down
}

//--------------------------------------------------
// Description  : Progress the Nonlinear scale up
// Input Value  :
//                Option : Indicate whether scale up be acyivate now
// Output Value : None
//--------------------------------------------------
void CScalerNonlinearScaleUp(BYTE Option)
{

    UINT8 FlatSuFac = 0;
    UINT8 InitSuFac = 0;
    UINT16 w1;  // segment1 pixel
    UINT16 w2;  // segment2 pixel
    UINT16 w3;  // segment3 pixel
    UINT8 SU_Waighting;//range from 35 ~ 45

    if(GET_NONLINEAR_VALUE() == 0)
    {
        CTimerDelayXms(120);
        CScalerSetByte(_STATUS0_02, 0x00);
        return;
    }

    SU_Waighting =  35 + GET_NONLINEAR_VALUE();

    if(Option & _BIT2)
    {
                w1 = stDisplayInfo.DHWidth/5 + 71;
        w2 = w1 - 71; //w2
        w3 = stDisplayInfo.DHWidth - SHL(w1, 1) - SHL(w2, 1); //w3

#if(_NONLINEAR_SCALEUP_METHOD == _BOUL)
        ((unsigned int *) pData)[2] = stDisplayInfo.DHWidth;

        FlatSuFac = (DWORD)512 * stModeInfo.IHWidth* 4 /((unsigned int *) pData)[2] / 5;
        FlatSuFac = FlatSuFac & 0x0001 ? SHR(FlatSuFac + 1, 1) : SHR(FlatSuFac, 1);//round

        //Csu > Fsu
        //Fsu - Csu < 0
        //Fsu(w1 + w2) - [Xm - Su(w1 + 1) - Fsu(1 + w2 + w3)] < 0
        //Fsu(1 + w1 + 2w2 + w3) - Xm + Su(w1 + 1) < 0
        //Su < [Xm - Fsu(1 + w1 + 2w2 + w3)]/(w1 + 1)

        ((unsigned long *) pData)[3] = 512 * ((DWORD)(stModeInfo.IHWidth - 1) -
                                        (DWORD)FlatSuFac * (w1 + SHL(w2, 1) + w3) / 255)
                                        /(DWORD)(w1 + 1);
              ((unsigned long *) pData)[3] = ((unsigned long *) pData)[3] & 0x00000001 ?
        SHR(((unsigned long *) pData)[3] + 1, 1) : SHR(((unsigned long *) pData)[3], 1);//round

        //ucInit_SU_Fac = ((unsigned long*)Data)[3] > 254 ? 254 : (BYTE)((unsigned long*)Data)[3]; //scaling factor can't larger than 1
        if (((unsigned long *) pData)[3] > 254)
        {
            return;
        }
        else
            InitSuFac = ((unsigned long *) pData)[3];
#else
        //Set the initial scale up factor equal to average scale up factor * 0.2
        //Calculate the scaling factor normalize to 255
        ((UINT32*)pData)[0] = (UINT32)255 * stModeInfo.IHWidth / stDisplayInfo.DHWidth;
        InitSuFac = SHR(((UINT32*)pData)[0]*3 , 2);


        //Fsu > Csu
        //Fsu - Csu > 0
        //Fsu - [Xm - Su(w1 + 1) - Fsu(1 + w2 + w3)]/(w1 + w2) > 0
        //Fsu(w1 + w2) - [Xm - Su(w1 + 1) - Fsu(1 + w2 + w3)] > 0
        //Fsu(1 + w1 + 2w2 + w3) - Xm + Su(w1 + 1) > 0
        //Fsu > [Xm - Su(w1 + 1)]/(1 + w1 + 2w2 + w3)
        ((UINT32*)pData)[3] = 255 * ((UINT32)(stModeInfo.IHWidth - 1) -
                            (UINT32)w1 * InitSuFac / 255) /(w1 + SHL(w2, 1) + w3 - 8);
        if (((UINT32*)pData)[3] > 254)
        {
            return;
        }
        else
        {
            //FlatSuFac = (SHR(((UINT32*)pData)[0] * 3, 1) > 255) ? 255 : SHR(((UINT32*)pData)[0] * 3, 1);
            FlatSuFac = (SHR(((UINT32*)pData)[0] * SU_Waighting, 5) > 255) ? 255 : SHR(((UINT32*)pData)[0] * SU_Waighting, 5);

        }

#endif
        //((UINT32 *) pData)[3] = 16777216 * (UINT32) InitSuFac / 255 + 0x00000008;
        ((UINT32 *) pData)[3] = 1048576 * (UINT32) InitSuFac / 255;

        CTimerWaitForEvent(_EVENT_DEN_STOP);
              pData[0] = ((((DWORD *) pData)[3] >> 16) & 0x0f);
        pData[1] = ((((DWORD *) pData)[3] >> 8) & 0xff);
        pData[2] = ((((DWORD *) pData)[3]) & 0xff);


        CScalerSetByte(_SU_ACCESS_PORT_33, 0x80); //don't remove this code thus the value can be fill in register
        CScalerSetByte(_SU_ACCESS_PORT_33, 0x80);
           CScalerWrite(_SU_DATA_PORT_34, 3, pData, _NON_AUTOINC);
           CScalerSetByte(_SU_ACCESS_PORT_33, 0x00);


        //Calculate Csu = (Xm - Su(w1 + 1) - Fsu(1 + w2 + w3))/(w1 + w2)
        ((UINT32*)pData)[2] = 1048576 * ((UINT32)stModeInfo.IHWidth -
                            (UINT32)InitSuFac * w1 / 255 -
                            (UINT32)FlatSuFac * (w2 + w3 - 1) / 255) /(w1 + w2 - 2);

        //Calculate SU
        ((UINT32*)pData)[3] = SHR((2097152 * (UINT32)InitSuFac /255) + 1, 1);

        if (((unsigned long *)pData)[3] > ((unsigned long *) pData)[2]) {
            ((unsigned long *) pData)[3] = 0 -(((unsigned long *) pData)[3] -
                                                   ((unsigned long *) pData)[2]) /(DWORD)w1; //The MSB is sign bit
        }
 else {
               if (((unsigned long *)pData)[3] > ((unsigned long *) pData)[2]) {
                ((unsigned long *) pData)[3] = 0 -(((unsigned long *) pData)[3] -
                                                   ((unsigned long *) pData)[2]) /(DWORD)w1; //The MSB is sign bit
            } else {
            //Calculate d1
            ((UINT32*) pData)[3] = (((UINT32*)pData)[2] - ((UINT32*)pData)[3]) / (UINT32)w1;
            }

            pData[6] = ((((DWORD *) pData)[3] >> 8) & 0xff);
            pData[7] = (((DWORD *) pData)[3]  & 0xff);

            //Calculate Fsu
            ((UINT32*)pData)[3] = SHR((2097152 * (UINT32)FlatSuFac / 255) + 1, 1);

                if (((unsigned long *) pData)[3] > ((unsigned long *) pData)[2]) {
                ((UINT32*)pData)[3] = (((UINT32*)pData)[3] - ((UINT32*)pData)[2]) / (UINT32)w2;
                }else{
                            ((unsigned long *) pData)[3] = 0 -  (((unsigned long *) pData)[2] - ((unsigned long *) pData)[3]) /(DWORD)w2;
                }

              }

        pData[8] = ((((DWORD *) pData)[3] >> 8) & 0xff);
        pData[9] = (((DWORD *) pData)[3] & 0xff);

#if(_NONLINEAR_SCALEUP_METHOD == _BOUL)
        w2 += 1;
        w3 += 1;
#else
        w1 -= 1;
        w2 -= 1;
        w3 -= 1;
#endif

        pData[0] = AND(HIBYTE(w1), 0x07);
        pData[1] = LOBYTE(w1);
        pData[2] = AND(HIBYTE(w2), 0x07);
        pData[3] = LOBYTE(w2);
        pData[4] = AND(HIBYTE(w3), 0x07);
        pData[5] = LOBYTE(w3);

        CScalerSetByte(_SU_ACCESS_PORT_33, 0x86);  //don't remove this code thus the value can be fill in register
        CScalerSetByte(_SU_ACCESS_PORT_33, 0x86);
        CScalerWrite(_SU_DATA_PORT_34, 10, pData, _NON_AUTOINC);
        CScalerSetByte(_SU_ACCESS_PORT_33, 0x00);
        CTimerDelayXms(120);
        CScalerSetByte(_STATUS0_02, 0x00);
    }
}

//--------------------------------------------------
// Description  : Progress the Nonlinear scale up
// Input Value  :
//                Option : Indicate whether scale up be acyivate now
// Output Value : None
//--------------------------------------------------
void CScalerNonlinearScaleDown(BYTE Option)
{
    UINT8 FlatSdFac;//This value must large than 64, scale down factor can't exceed 4 times
    UINT16 w1;
    UINT16 w2;

    //if(FlatSdFac < 68)
    //   return;
        if(GET_NONLINEAR_VALUE() == 0)
    {
       //CScalerSetBit(_SCALE_DOWN_CTRL_23, 0xf7, 0x00);//disable non-linear scale down
        return;
    }
    
    FlatSdFac =  68 + (10 - GET_NONLINEAR_VALUE()); //range from 68 ~ 78

    if (Option & _BIT3 ) // non-linear scaling down
    {
        w1 = SHR(stDisplayInfo.DHWidth, 2);
            w2 = (stDisplayInfo.DHWidth - SHL(w1, 1)) - 1;


        //Calculate the Initial Scale down factor
        ((UINT32*)pData)[3] = 1048576 * ((UINT32)((UINT32)stModeInfo.IHWidth - 1) -
            (w1 + w2) * (UINT32)FlatSdFac / 64) / w1;

        //Data[0] = 5;
        //Data[1] = info->channel ? _P1_47_H_SCALE : _P1_27_H_SCALE_DH;
        pData[0] = pData[13];
        pData[1] = pData[14];
        pData[2] = pData[15];

        ((UINT32*)pData)[3] = (((UINT32*)pData)[3] - (UINT32) 1048576 * FlatSdFac / 64) / (w1 - 1);

        if (((UINT32*)pData)[3] > 0x3fff) //Accumulated factor too large
            return;
        
        pData[3] = pData[14] & 0x3f;
        pData[4] = pData[15];


        CTimerWaitForEvent(_EVENT_IEN_STOP);

        CScalerSetByte(_SD_ACCESS_PORT_24, 0x85);
        CScalerSetByte(_SD_ACCESS_PORT_24, 0x85);
        CScalerWrite(_SD_DATA_PORT_25, 5, pData, _NON_AUTOINC); //hill modified for scale down error
        CScalerSetByte(_SD_ACCESS_PORT_24, 0x00);

        //Data[0] = 4;
        //Data[1] = info->channel ? _P1_4C_SD_ACC_WIDTHH : _P1_2C_SD_ACC_WIDTHH;
        pData[0] = HIBYTE(w1);
        pData[1] = LOBYTE(w1);
        pData[2] = HIBYTE(w2);
        pData[3] = LOBYTE(w2);
        //Data[6] = 0;
        //CRtdWrite();
        CScalerSetByte(_SD_ACCESS_PORT_24, 0x8a);
        CScalerSetByte(_SD_ACCESS_PORT_24, 0x8a);
        CScalerWrite(_SD_DATA_PORT_25, 4, pData, _NON_AUTOINC); //hill modified for scale down error
        CScalerSetByte(_SD_ACCESS_PORT_24, 0x00);

        CScalerSetBit(_SCALE_DOWN_CTRL_23, 0xff, 0x08);
        CTimerDelayXms(120);
        CScalerSetByte(_STATUS0_02, 0x00);
        //CRtdClearBits((info->channel ? _P1_41_SD_CTRL2 : _P1_21_SD_CTRL2), _BIT2); // enable non-linear scaling down
    } // end of (GET_NONLINEAR_ON() && GET_HSCALE_UP()) // non-linear scaling

}
#endif
//731301***
#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))//V402 modify
//--------------------------------------------------
// Description  : Switch the Digital Input Port
// Input Value  : usSwitch  --> Parameter for Digital Input Port
// Output Value : None
//--------------------------------------------------
#if 0
void CScalerDigitalPortSwitch(void)
{
    CScalerPageSelect(_PAGE2);

    if(!CHdmiFormatDetect())
    {
            CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT6 | _BIT5), 0x00);
    }
    else
    {
            CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));
    }

   /* switch(usSwitch)
    {
        case _DVI_D0_PORT:
        case _HDMI_H0_PORT:
            CScalerSetBit(_P2_TMDS_MEAS_RESULT0_A2, ~_BIT1, 0x00);
            CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT1 | _BIT0), _BIT1 | _BIT0);
            CScalerSetBit(_P2_HDCP_PORT_CTRL_C2, ~_BIT1, 0x00);
            break;

        case _DVI_D1_PORT:
        case _HDMI_H1_PORT:
            CScalerSetBit(_P2_TMDS_MEAS_RESULT0_A2, ~_BIT1, _BIT1);
            CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT1 | _BIT0), _BIT1 | _BIT0);
            CScalerSetBit(_P2_HDCP_PORT_CTRL_C2, ~_BIT1, _BIT1);
            break;
    }*/
    CTimerDelayXms(200);
    CScalerSetBit(_P2_HDCP_CTRL_C0, ~_BIT0, _BIT0);
}
#endif
#endif
//731301###
