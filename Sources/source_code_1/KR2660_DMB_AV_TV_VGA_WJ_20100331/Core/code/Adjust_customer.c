/*===========================================================
 * Copyright (c)      Realtek Semiconductor Corporation, 2005
 * All rights reserved.
 * ========================================================== */

/*==================== File Description ===================== */
/**
 * @file
 *  This file is osd control declaration related functions.
 *
 * @author  $Author: forster $
 * @date    $Date: 2006-03-21 20:24:23 +0800 (?Ÿæ?äº? 21 ä¸‰æ? 2006) $
 * @version     $Revision: 451 $
 * @ingroup Auto
 */

/**
 * @addtogroup Auto
 * @{
 */

#define _ADJUST_CUSTOMER_C
/*===================== Module dependency  ================== */
#include "Core\Header\Include.h"

void CAdjustAudio(void)
{
    if(0)//_GET_INPUT_SOURCE() == _SOURCE_VIDEO_AV || _GET_INPUT_SOURCE() == _SOURCE_VIDEO_SV)
    {
		pData[0] = (0x78 + stAudioData.Volume - 50);//0x80
		pData[1] = (0x78 + stAudioData.Volume - 50);//0x80
		pData[2] = (0x78 + stAudioData.Volume - 50);//0x80
    }
    else
    {
		pData[0] = (0x80 + stAudioData.Volume - 50);//0x80
		pData[1] = (0x80 + stAudioData.Volume - 50);//0x80
		pData[2] = (0x80 + stAudioData.Volume - 50);//0x80

    }
     CAdjustVolume();
}

//--------------------------------------------------
// Description  : Adjust color precessing brightness
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustBrightness(void)
{
   	if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
	{
		pData[0] = (128 + stConBriData.Brightness - 50);// + stColorTempData.ColorTemp[0];
		pData[1] = pData[0];//(128 + stConBriData.Brightness - 50);// + stColorTempData.ColorTemp[1];
		pData[2] = pData[0];//(128 + stConBriData.Brightness - 50);// + stColorTempData.ColorTemp[2];
	}
    //   EricLee modify for AV/SV gary-scale
    else if(0)//_GET_INPUT_SOURCE() == _SOURCE_VIDEO_AV || _GET_INPUT_SOURCE() == _SOURCE_VIDEO_SV)
    {
		pData[0] = (0x78 + stConBriData.Brightness - 50);//0x80
		pData[1] = (0x78 + stConBriData.Brightness - 50);//0x80
		pData[2] = (0x78 + stConBriData.Brightness - 50);//0x80
    }
    else
    {
		pData[0] = (0x80 + stConBriData.Brightness - 50);//0x80
		pData[1] = (0x80 + stConBriData.Brightness - 50);//0x80
		pData[2] = (0x80 + stConBriData.Brightness - 50);//0x80
    }
    
	CAdjustSetBrightness();
#if(_BACKLIGHT_USE_FAC_ADJ == _DISABLE)
    CAdjustBacklight();
#endif
}

//--------------------------------------------------
// Description  : Adjust color processing contrast
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustContrast(void)
{
	BYTE cnt;

    if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
    {
	    for(cnt=0;cnt<3;cnt++)
		{
    		//pData[cnt] = (((WORD)stColorTempData.ColorTemp[cnt] * stConBriData.Contrast / 128) > 255) ? 255 : (BYTE)((WORD)stColorTempData.ColorTemp[cnt] * stConBriData.Contrast / 128);
        	pData[cnt] = (BYTE)(((WORD)stColorTempData.ColorTemp[cnt] * (stConBriData.Contrast+_CONTRAST_MIN) / 128) > 255) ? 255 : (BYTE)((WORD)stColorTempData.ColorTemp[cnt] * (stConBriData.Contrast+_CONTRAST_MIN) / 128);
		}
	}			
    else if(_GET_INPUT_SOURCE() == _SOURCE_VIDEO_AV || _GET_INPUT_SOURCE() == _SOURCE_VIDEO_SV)
    {
		pData[0] = (0x80 + stConBriData.Contrast - 50);
		pData[1] = (0x80 + stConBriData.Contrast - 50);
		pData[2] = (0x80 + stConBriData.Contrast - 50);
	}	
    else
    {
		pData[0] = (0x80 + stConBriData.Contrast - 50);
		pData[1] = (0x80 + stConBriData.Contrast - 50);
		pData[2] = (0x80 + stConBriData.Contrast - 50);
	}	

    CAdjustSetContrast();
}

#if (sRGB_Color_Enhance == _ENABLE)
void CAdjustYpbprhue(BYTE  ucYPbPrhue)
{
    CAdjustSaturationHue(ucYPbPrhue, _FALSE);
}
             /*

#define _YUV2RGB_k13   1
#define _YUV2RGB_k22   2
#define _YUV2RGB_k23   3
#define _YUV2RGB_k32   4
UINT16 tYUV2RGB_COEF_601_YCbCr[] =
{
 
  0x0100, // k11
  0x0166, // k13
  0x0058, // k22
  0x00b6, // k23
  0x01c5, // k32
  0x0000, // R-offset
  0x0000, // G-offset
  0x0000, // B-offset
 
  0x0000, // Y Clamp (Y-16)
  0x0001, // UV Clamp (UV-512)
 
};              */

void CAdjustYpbprSaturation(BYTE  ucYPbPrSaturation)
{
    WORD PB,PR;//,new_k13,new_k22,new_k23,new_k32,new_coeffs;
    BYTE temp;

    temp=ucYPbPrSaturation;

    if(_GET_INPUT_SOURCE() == _SOURCE_YPBPR||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1)
    {
        PR = (temp <= 50)  ? ((WORD)stYPbPrData.YPbPrGain[_RED] + ((50 - temp) << 2)) :
        ((WORD)stYPbPrData.YPbPrGain[_RED] - (temp - 50));
    
        PB = (temp <= 50)  ? ((WORD)stYPbPrData.YPbPrGain[_BLUE] + ((50 - temp) << 2)) :
        ((WORD)stYPbPrData.YPbPrGain[_BLUE] - (temp - 50));
    
        if(HIBYTE(PB)>0)
            PB  = HIBYTE(PB) < 0x02 ? 0x00FF : 0 ;
        if (HIBYTE(PR)>0)
            PR  = HIBYTE(PR) < 0x02 ? 0x00FF : 0 ;
    
    #if(_ADC1_INPUT_SWAP_RG == _ON)
    
        pData[1] = PR;
        pData[0] = stYPbPrData.YPbPrGain[_GREEN];
        pData[2] = PB;
    
    #elif(_ADC1_INPUT_SWAP_RB == _ON)
    
        pData[2] = PR;
        pData[1] = stYPbPrData.YPbPrGain[_GREEN];
        pData[0] = PB;
    
    #elif(_ADC1_INPUT_SWAP_GB == _ON)
    
        pData[0] = PR;
        pData[2] = stYPbPrData.YPbPrGain[_GREEN];
        pData[1] = PB;
    
    #else
    
        pData[0] = PR;
        pData[1] = stYPbPrData.YPbPrGain[_GREEN];
        pData[2] = PB;
    
    #endif
        //CAdjustSetYpbprSaturation();//eric 20070613
        CAdjustSaturationHue(ucYPbPrSaturation, _TRUE);
    }

    //Lewis, adjust sRGB domain
    CAdjustSaturationHue(ucYPbPrSaturation, _TRUE);
                  /*

    new_coeffs =  (double)  tYUV2RGB_COEF_601_YCbCr[_YUV2RGB_k13] * ucYPbPrSaturation;
    new_coeffs = (new_coeffs >> 7) ;
    new_k13 = (new_coeffs > 0x1ff) ? 0x1ff: new_coeffs;
    
    new_coeffs = (double)  tYUV2RGB_COEF_601_YCbCr[_YUV2RGB_k22]  * ucYPbPrSaturation;
    new_coeffs = (new_coeffs >> 7) ;
    
    new_k22 = (new_coeffs > 0xff) ? 0xff: new_coeffs;
    
    new_coeffs = (double)   tYUV2RGB_COEF_601_YCbCr[_YUV2RGB_k23]  * ucYPbPrSaturation;
    new_coeffs = (new_coeffs >> 7) ;
    
    new_k23 = (new_coeffs > 0xff) ? 0xff: new_coeffs;
    
    new_coeffs = (double)   tYUV2RGB_COEF_601_YCbCr[_YUV2RGB_k32]  * ucYPbPrSaturation;
    new_coeffs = (new_coeffs >> 7) ;
    
    new_k32 = (new_coeffs > 0x3ff) ? 0x3ff: new_coeffs;


    CScalerPageSelect(_PAGE7);
    CScalerSetByte(_P7_YUV2RGB_ACCESS_C0,(WORD)(new_k13 >> 8));
    CScalerSetByte(_P7_YUV2RGB_DATA_C1,(WORD)(new_k13 & 0xFF));
    CScalerSetByte(_P7_YUV2RGB_ACCESS_C0,(WORD)(new_k22 >> 8));
    CScalerSetByte(_P7_YUV2RGB_DATA_C1,(WORD)(new_k22 & 0xFF));
    CScalerSetByte(_P7_YUV2RGB_ACCESS_C0,(WORD)(new_k23 >> 8));
    CScalerSetByte(_P7_YUV2RGB_DATA_C1,(WORD)(new_k23 & 0xFF));
    CScalerSetByte(_P7_YUV2RGB_ACCESS_C0,(WORD)(new_k32 >> 8));
    CScalerSetByte(_P7_YUV2RGB_DATA_C1,(WORD)(new_k32 & 0xFF)); */
}

#else
// cftsai 20061031 modify
INT16 code RR[]=
{
-155,-149,-143,-138,-132,-127,-121,-116,-111,-105,
-100, -95, -90, -85, -80, -75, -71, -66, -62, -57,
 -53, -49, -45, -40, -36, -33, -29, -25, -22, -18,
 -15, -12,  -8,  -5,  -2,   0,   2,   5,   7,  10,
  12,  14,  16,  18,  20,  22,  24,  25,  26,  28,
  29,  30,  31,  32,  32,  33,  33,  34,  34,  34,
  34,  34,  34,  33,  33,  32,  32,  31,  30,  29,
  28
};

INT16 code RG[]=
{
-100, -99, -98, -96, -95, -93, -92, -90, -88, -86,
 -84, -81, -79, -77, -74, -72, -69, -66, -63, -60,
 -57, -54, -51, -47, -44, -40, -36, -33, -29, -25,
 -21, -17, -13,  -8,  -4,   0,   4,   9,  13,  18,
  23,  28,  33,  38,  43,  48,  53,  58,  64,  69,
  74,  80,  86,  91,  97, 102, 108, 114, 120, 126,
 132, 138, 144, 150, 156, 162, 168, 174, 180, 186,
 193
};

INT16 code RB[]=
{
255, 249, 242, 235, 227, 220, 213, 206, 199, 192,
184, 177, 170, 162, 155, 148, 140, 133, 125, 118,
110, 103,  96,  88,  81,  73,  66,  58,  51,  44,
 36,  29,  21,  14,   7,   0,  -7, -14, -21, -28,
-35, -42, -49, -56, -63, -70, -77, -84, -91, -97,
-104, -110, -117, -123, -130, -136, -142, -148, -154, -160,
-166, -172, -178, -184, -189, -195, -200, -205, -211, -216,
-221
};

INT16 code GR[]=
{
162 ,157 ,152 ,147 ,142 ,137 ,132 ,127 ,
122 ,117 ,113 ,108 ,103 ,98  ,93  ,88  ,
84  ,79  ,74  ,70  ,65  ,60  ,56  ,51  ,
47  ,42  ,38  ,33  ,29  ,25  ,20  ,16  ,
12  ,8   ,4   ,0   ,-4  ,-7  ,-11 ,-15 ,
-19 ,-23 ,-27 ,-30 ,-34 ,-37 ,-41 ,-44 ,
-48 ,-51 ,-54 ,-57 ,-60 ,-63 ,-66 ,-69 ,
-72 ,-75 ,-77 ,-80 ,-83 ,-85 ,-87 ,-90 ,
-92 ,-94 ,-96 ,-98 ,-100,-102,-104
};

INT16 code GG[]=
{
-9 ,-7 ,-6 ,-4 ,-3 ,-2 ,-1 ,0  ,
1  ,2  ,3  ,3  ,4  ,5  ,5  ,6  ,
6  ,7  ,7  ,7  ,7  ,7  ,7  ,7  ,
7  ,7  ,6  ,6  ,5  ,5  ,4  ,3  ,
2  ,2  ,1  ,0  ,-1 ,-2 ,-3 ,-5 ,
-6 ,-8 ,-9 ,-11,-13,-15,-16,-18,
-20,-23,-25,-27,-29,-32,-34,-37,
-39,-42,-45,-48,-51,-53,-56,-60,
-63,-66,-69,-72,-76,-79,-83
};

INT16 code GB[]=
{
-152,-149,-145,-142,-138,-135,-131,-127,
-123,-120,-116,-112,-108,-103,-99 ,-95 ,
-91 ,-86 ,-82 ,-77 ,-73 ,-68 ,-64 ,-59 ,
-54 ,-49 ,-45 ,-40 ,-35 ,-30 ,-25 ,-20 ,
-15 ,-10 ,-5  ,0   ,5   ,10  ,15  ,20  ,
26  ,31  ,36  ,42  ,47  ,52  ,58  ,63  ,
69  ,74  ,79  ,85  ,90  ,96  ,101 ,107 ,
112 ,117 ,123 ,128 ,134 ,139 ,144 ,150 ,
155 ,160 ,166 ,171 ,176 ,181 ,187
};

INT16 code BR[]=
{
-172, -169, -165, -162 , -158, -154, -150, -146, -142, -138,
-133, -129, -124,-120,-115,-110,-105,-100,-95,-90,
-85,-80,-75,-69,-64,-58,-53,-47,-41,-35,
-30,-24,-18,-12,-6,0,6,12,18,24,
31,37,44,50,57,63,70,76,83,89,
96,103,109,116,123,130,136,143,150,157,
163,170,177,183,190,197,204,210,217,224,
230
};

INT16 code BG[]=
{
193 ,186 ,180 ,174 ,168 ,162 ,156 ,150 ,
144 ,138 ,132 ,126 ,120 ,114 ,108 ,102 ,
97  ,91  ,86  ,80  ,74  ,69  ,64  ,58  ,
53  ,48  ,43  ,38  ,33  ,28  ,23  ,18  ,
13  ,9   ,4   ,0   ,-4  ,-8  ,-13 ,-17 ,
-21 ,-25 ,-29 ,-33 ,-36 ,-40 ,-44 ,-47 ,
-51 ,-54 ,-57 ,-60 ,-63 ,-66 ,-69 ,-72 ,
-74 ,-77 ,-79 ,-81 ,-84 ,-86 ,-88 ,-90 ,
-92 ,-93 ,-95 ,-96 ,-98 ,-99 ,-100
};

INT16 code BB[]=
{
-20 ,-17, -14, -12, -9, -7, -5, -3,
-1  ,0   ,1   ,3   ,4   ,5   ,6   ,7   ,
8   ,9   ,9   ,10  ,10  ,10  ,10  ,10  ,
10  ,10  ,9   ,9   ,8   ,7   ,6   ,5   ,
4   ,3   ,1   ,0   ,-1  ,-3  ,-5  ,-7  ,
-9  ,-12 ,-14 ,-17 ,-20 ,-22 ,-25 ,-29 ,
-32 ,-35 ,-39 ,-42 ,-46 ,-50 ,-53 ,-57 ,
-62 ,-66 ,-70 ,-75 ,-79 ,-84 ,-88 ,-93 ,
-98 ,-103,-108,-114,-119,-124,-130
};

void CAdjustYpbprhue(BYTE  ucYPbPrhue)
{
    BYTE uchue ;

    uchue = ucYPbPrhue *0.7 ;
    //Write R
    pData[0] = ((RR[uchue] >> 8) & 0x01);   // RRH
    pData[1] = (RR[uchue] & 0xff);      // RRL
    pData[2] = ((RG[uchue] >> 8) & 0x01);   // RGH
    pData[3] = (RG[uchue] & 0xff);      // RGL
    pData[4] = ((RB[uchue] >> 8) & 0x01);   // RBH
    pData[5] = (RB[uchue] & 0xff);      // RBL
    CAdjustSetYpbprRhue();

    //Write G
    pData[0] = ((GR[uchue] >> 8) & 0x01);   // GRH
    pData[1] = (GR[uchue] & 0xff);      // GRL
    pData[2] = ((GG[uchue] >> 8) & 0x01);   // GGH
    pData[3] = (GG[uchue] & 0xff);      // GGL
    pData[4] = ((GB[uchue] >> 8) & 0x01);   // GBH
    pData[5] = (GB[uchue] & 0xff);      // GBL
    CAdjustSetYpbprGhue();

    //Write B
    pData[0] = ((BR[uchue] >> 8) & 0x01);   // BRH
    pData[1] = (BR[uchue] & 0xff);      // BRL
    pData[2] = ((BG[uchue] >> 8) & 0x01);   // BGH
    pData[3] = (BG[uchue] & 0xff);      // BGL
    pData[4] = ((BB[uchue] >> 8) & 0x01);   // BBH
    pData[5] = (BB[uchue] & 0xff);      // BBL
    CAdjustSetYpbprBhue();

    CScalerSetBit(_COLOR_CTRL_62, 0xff, 0x80);          // cftsai 20061031 added, ready to write
}


void CAdjustYpbprSaturation(BYTE  ucYPbPrSaturation)
{
    WORD    PB, PR ;

    PR = (WORD)stYPbPrData.YPbPrGain[_RED] * (100 - ucYPbPrSaturation) /(WORD)50  ;
    PB = (WORD)stYPbPrData.YPbPrGain[_BLUE] * (100 - ucYPbPrSaturation) /(WORD)50 ;
if(HIBYTE(PB)>0)
    PB  = 0x00FF ;
if (HIBYTE(PR)>0)
    PR  = 0x00FF ;

 #if(_ADC_INPUT_SWAP_RG == _ON)

    pData[1] = PR;
    pData[0] = stYPbPrData.YPbPrGain[_GREEN];
    pData[2] = PB;

#elif(_ADC_INPUT_SWAP_RB == _ON)

    pData[2] = PR;
    pData[1] = stYPbPrData.YPbPrGain[_GREEN];
    pData[0] = PB;

#elif(_ADC_INPUT_SWAP_GB == _ON)

    pData[0] = PR;
    pData[2] = stYPbPrData.YPbPrGain[_GREEN];
    pData[1] = PB;

#else

    pData[0] = PR;
    pData[1] = stYPbPrData.YPbPrGain[_GREEN];
    pData[2] = PB;

#endif
    CAdjustSetYpbprSaturation();

}
#endif      // sRGB_Color_Enhance end



#if(_AdjustCustomerColorMode==_ENABLE)
void CAdjustCustomerColorMode(void)
{
#if(_COLOR_PREFERENCE == _PANASONIC_STYLE)

// Brightness_R,Brightness_G,Brightness_B,Contrast_R,Contrast_G,Contrast_B,Sharpness_Num
// VDC_Contrast,VDC_Brightness,VDC_Saturation,VDC_Hue,VDC_Shaprness

    BYTE code ColorType[][12] = {
    // CVBS,SV
    //    B_R    B_G   B_B     C_R    C_G    C_B    Sharp   VD_Con   VD_Bri   VD_Sat   VD_Hue    VD_Sharp
        0x80,  0x80,  0x7F,  0x87,  0x80,  0x7A,   6,        38,           0x78,     64,         46,          0x17,

    // TV
    //    B_R    B_G   B_B     C_R    C_G    C_B    Sharp   VD_Con   VD_Bri   VD_Sat   VD_Hue    VD_Sharp
        0x80,  0x80,  0x80,  0x80,  0x80,  0x80,  6,        52,           0x85,     52,         47,          0x17,
       //0x80,  0x80,  0x80,  0x80,  0x80,  0x80,   6,        33,           0x85,     58,         46,          0x17,

    // YPbPr  , HDMI
    //    B_R    B_G   B_B     C_R    C_G    C_B    Sharp   VD_Con   VD_Bri   VD_Sat   VD_Hue    VD_Sharp
        0x80,  0x80,  0x7F,  0xB3,  0xAA,  0xA2,   6,        38,           0x78,     50,         50,          0x17,
       //0x80,  0x80,  0x7F,  0xB3,  0xAA,  0xA2,   6,        38,           0x78,     50,         50,          0x17,


    };

    if(!bSourceVideo())
    {

            pData[0] = ColorType[2][0];
            pData[1] = ColorType[2][1];
            pData[2] = ColorType[2][2];
            pData[3] = ColorType[2][3];
            pData[4] = ColorType[2][4];
            pData[5] = ColorType[2][5];

            CScalerSetByte(_CB_ACCESS_PORT_64, 0x80);
                CScalerWrite(_CB_DATA_PORT_65, 6, pData, _NON_AUTOINC);
                CScalerSetByte(_CB_ACCESS_PORT_64, 0x00);

            SET_PEAKING_CORING(ColorType[2][6]);
            SET_CONTRAST(ColorType[2][7]);
            //SET_YPbPrSaturation(ColorType[2][9]);
            //SET_YPbPrHue(ColorType[2][10]);
                     SET_SATURATION(ColorType[2][9]);
            SET_HUE(ColorType[2][10]);          
            CEepromSaveSystemData();

            CAdjustPeakingFilter(GET_PEAKING_CORING());
            CAdjustContrast();
            //CAdjustYpbprSaturation(GET_YPbPrSaturation());
            //CAdjustYpbprhue(GET_YPbPrHue());
            CAdjustYpbprSaturation(GET_SATURATION());
            CAdjustYpbprhue(50);//GET_HUE());
#ifdef _SRGB_ENLARGE_RANGE
			CScalerSetBit(_COLOR_CTRL_62,~(_BIT6|_BIT2),(_BIT6|_BIT2));   	//  Enable SRGB
#else //#ifdef _SRGB_ENLARGE_RANGE
			CScalerSetBit(_COLOR_CTRL_62, 0xFF, _BIT2);
#endif //#ifdef _SRGB_ENLARGE_RANGE

    }
    else
    {   
        if(_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
        {
            
            pData[0] = ColorType[1][0];
            pData[1] = ColorType[1][1];
            pData[2] = ColorType[1][2];
            pData[3] = ColorType[1][3];
            pData[4] = ColorType[1][4];
            pData[5] = ColorType[1][5];

            CScalerSetByte(_CB_ACCESS_PORT_64, 0x80);
                CScalerWrite(_CB_DATA_PORT_65, 6, pData, _NON_AUTOINC);
                CScalerSetByte(_CB_ACCESS_PORT_64, 0x00);


            SET_PEAKING_CORING(ColorType[1][6]);
            SET_CONTRAST(ColorType[1][7]);
            SET_SATURATION(ColorType[1][9]);
            SET_HUE(ColorType[1][10]);
            CVideoSetVDCBrightness(ColorType[1][8]);
            I2CByteWrite(0x80,_VIDEO_DEVICE,ColorType[1][11]);
            
            CEepromSaveSystemData();
        }
        else
        {
        
        
            pData[0] = ColorType[0][0];
            pData[1] = ColorType[0][1];
            pData[2] = ColorType[0][2];
            pData[3] = ColorType[0][3];
            pData[4] = ColorType[0][4];
            pData[5] = ColorType[0][5];

            CScalerSetByte(_CB_ACCESS_PORT_64, 0x80);
                CScalerWrite(_CB_DATA_PORT_65, 6, pData, _NON_AUTOINC);
                CScalerSetByte(_CB_ACCESS_PORT_64, 0x00);

            SET_PEAKING_CORING(ColorType[0][6]);
            SET_CONTRAST(ColorType[0][7]);
            SET_SATURATION(ColorType[0][9]);
            SET_HUE(ColorType[0][10]);
            CVideoSetVDCBrightness(ColorType[0][8]);
            I2CByteWrite(0x80,_VIDEO_DEVICE,ColorType[0][11]);
            
            CEepromSaveSystemData();

        }
        CAdjustPeakingFilter(GET_PEAKING_CORING());
        CVideoSetContrast(GET_CONTRAST());
        CVideoSetSaturation(GET_SATURATION());
        kx_CAdjustVDCHue(GET_HUE());       
    }


#endif


#if(sRGB_Color_Enhance == _ENABLE)

    CVideoSetSaturation(GET_SATURATION());
    kx_CAdjustVDCHue(GET_HUE());
#ifdef _SRGB_ENLARGE_RANGE
	CScalerSetBit(_COLOR_CTRL_62,~(_BIT6|_BIT2),(_BIT6|_BIT2));   	//  Enable SRGB
#else //#ifdef _SRGB_ENLARGE_RANGE
	CScalerSetBit(_COLOR_CTRL_62, ~_BIT2, _BIT2);		// enable sRGB
#endif //#ifdef _SRGB_ENLARGE_RANGE

#endif

}
#endif


#if(_VIDEO_AUTO_WHITE_BLANCE == _ENABLE)
#define _VIDEO_SATURATION_MAX   0xFF
#define _VIDEO_SATURATION_MIN   0x00
#endif

//--------------------------------------------------
// Description  : Set  2610 Saturation
// Input Value  : saturationNone
// Output Value : None
//--------------------------------------------------
void CVideoSetSaturation(BYTE ucValue)
{
#if(_VIDEO_AUTO_WHITE_BLANCE == _ENABLE)
	BYTE ucSaturation;
	BYTE temp;
	
   	if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
    	ucSaturation = 106; // 140
    else
    	ucSaturation = 140;

    if(ucValue > 50)
    {
        temp = ((UINT16)((_VIDEO_SATURATION_MAX - ucSaturation)*(ucValue - 50))) / 50;
        temp += ucSaturation;
    }
    else if(ucValue < 50)
    {
        temp = ((UINT16)((ucSaturation -_VIDEO_SATURATION_MIN) * (50 - ucValue))) / 50;
        temp = ucSaturation - temp;
    }
    else
        temp = ucSaturation;
    CVideoSetVDCSaturation(temp);
#else
    ucValue = ucValue * 2.5;
    CVideoSetVDCSaturation(ucValue);
#endif
}

//--------------------------------------------------
// Description  : Set  2610 Contrast
// Input Value  : ucValue
// Output Value : None
//--------------------------------------------------
void CVideoSetContrast(BYTE ucValue)
{
    ucValue = ucValue * 2.5;
    CVideoSetVDCContrast(ucValue);
}

void CAdjustHueSatSet(BYTE color, SWORD TempU1, SWORD TempU2, SWORD TempV1, SWORD TempV2)
{
    BYTE i;
    SWORD u,v;

    BYTE value = (color & 0x0f);
    //CTimerWaitForEvent(_EVENT_DEN_STOP);
    CScalerPageSelect(_PAGE7);

    CScalerSetByte(_P7_ICM_SEL_D1, value);
    CScalerSetByte(_P7_ICM_ACCESS_PORT_D2,0x00);
    if(value == 0)
    {       //R
        CScalerSetByte(_P7_ICM_DATA_PORT_D3,0x02);
        CScalerSetByte(_P7_ICM_DATA_PORT_D3,0xd2);
        if(CGetInputSourceNum(_GET_INPUT_SOURCE())>1)
            CScalerSetByte(_P7_ICM_DATA_PORT_D3,0xaa);
        else
            CScalerSetByte(_P7_ICM_DATA_PORT_D3,0xee);
    }
    else if(value == 1)
    {//G
        CScalerSetByte(_P7_ICM_DATA_PORT_D3,0x08);
        CScalerSetByte(_P7_ICM_DATA_PORT_D3,0x00);
        if(CGetInputSourceNum(_GET_INPUT_SOURCE())>1)
            CScalerSetByte(_P7_ICM_DATA_PORT_D3,0x66);
        else
            CScalerSetByte(_P7_ICM_DATA_PORT_D3,0xee);
    }
    else if(value == 2)
    {//B
        CScalerSetByte(_P7_ICM_DATA_PORT_D3,0x0d);
        CScalerSetByte(_P7_ICM_DATA_PORT_D3,0x2e);
        if(CGetInputSourceNum(_GET_INPUT_SOURCE())>1)
            CScalerSetByte(_P7_ICM_DATA_PORT_D3,0x66);
        else
            CScalerSetByte(_P7_ICM_DATA_PORT_D3,0xbe);
    }
    else if(value == 3)
    {//Y
        CScalerSetByte(_P7_ICM_DATA_PORT_D3,0x05);
        CScalerSetByte(_P7_ICM_DATA_PORT_D3,0x2e);
        CScalerSetByte(_P7_ICM_DATA_PORT_D3,0x62);  //ff
    }
    else if(value == 4)
    {//C
        CScalerSetByte(_P7_ICM_DATA_PORT_D3,0x0a);
        CScalerSetByte(_P7_ICM_DATA_PORT_D3,0xd2);
        CScalerSetByte(_P7_ICM_DATA_PORT_D3,0x66);
    }
    //CTimerWaitForEvent(_EVENT_DEN_STOP);
    CScalerSetByte(_P7_ICM_SEL_D1,value);
    CScalerSetByte(_P7_ICM_ACCESS_PORT_D2,((color & 0xf0)+0x03));
    //CScalerSendAddr(_P7_ICM_DATA_PORT_D3, _WRITE, _NON_AUTOINC);//provisional ¼È©w
    
    for(i=1; i<9; i++)
    {
        u = ((TempU1+TempU2)*CAdjustColorGammaCal(value, i)/64) - ((TempU1*i)/8);
        v = ((TempV1+TempV2)*CAdjustColorGammaCal(value, i)/64) - ((TempV1*i)/8);
        CScalerSetByte(_P7_ICM_DATA_PORT_D3,u); //CScalerSetByte(0xe3,u);       
        CScalerSetByte(_P7_ICM_DATA_PORT_D3,v); //CScalerSetByte(0xe3,v);       
    }
    if(_GET_INPUT_SOURCE() == _SOURCE_VGA || _GET_INPUT_SOURCE() == _SOURCE_DVI)//CGetInputSourceNum(_GET_INPUT_SOURCE())>1)
        CScalerSetByte(_P7_ICM_CTRL_D0,0xdf);
    else
        CScalerSetByte(_P7_ICM_CTRL_D0,0xdc);
    
}

#define CENTER    0x00
#define RIGHT     0x10
#define LEFT      0x20
void CAdjustSetHueUVDelta(BYTE color, BYTE select)
{
    SWORD TempU1,TempV1,TempU2,TempV2;

    pData[0] = (select >> 3); //(select >> 4) << 1
    pData[1] = pData[0] + 1;

    if(CGetInputSourceNum(_GET_INPUT_SOURCE())>1)
    {
      TempU1 = Video_TempUV1[color][pData[0]];
      TempV1 = Video_TempUV1[color][pData[1]];
    }
    else
    {
      TempU1 = Graphic_TempUV1[color][pData[0]];
      TempV1 = Graphic_TempUV1[color][pData[1]];
    }

    pData[2] = color*3 + (select >> 4);

    if(stICMColor.ICM_COLOR[color] < 8)
    {
       TempU2 = (long)TempUV2[pData[2]][0] * (8 - stICMColor.ICM_COLOR[color]) >> 3;
       TempV2 = (long)TempUV2[pData[2]][1] * (8 - stICMColor.ICM_COLOR[color]) >> 3;
    }
    else
    {
       TempU2 = (long)TempUV2[pData[2]][2] * (stICMColor.ICM_COLOR[color] - 8) >> 3;
       TempV2 = (long)TempUV2[pData[2]][3] * (stICMColor.ICM_COLOR[color] - 8) >> 3;
    }
    CAdjustHueSatSet((select | color), TempU1, TempU2, TempV1, TempV2);


}
#if(_COLOR_PREFERENCE == _PANASONIC_STYLE)

#define	RF_StartOffset		5
#define	AV_StartOffset		0
#define	YPbPr_StartOffset	0

void CAdjustPeakingFilter(SBYTE ucPeaking)
{
    if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
    {
        CScalerPageSelect(_PAGE7);
        CScalerSetBit(_P7_PEAKING_ENABLE_A9, ~_BIT3, 0x00); // disable Peaking and Coring
        CScalerSetBit(_P7_DLTI_DCTI_ENABLE_A1, ~(_BIT6 | _BIT7), 0x00);
        CScalerPageSelect(_PAGE6);
        CScalerSetByte(_P6_DCTI_1ST_GAIN_D8, 0x4A);
        CScalerSetByte(_P6_SPATIAL_CTRL_DB, 0x00);
        return;
    }
	else if(_GET_INPUT_SOURCE() == _SOURCE_HDMI || _GET_INPUT_SOURCE() == _SOURCE_DVI)
    {
        //if(HDMI_V_Height>=720)        //720p above
            pData[0] = 0x00;                    //bit[3:2]->10: 9 pixels; ->01: 7 pixels; ->00: 5 pixels      
        //else
            //pData[0] = 0x00;                  //bit[3:2]->10: 9 pixels; ->01: 7 pixels; ->00: 5 pixels      
        pData[1] = 0x7E;                        //Peaking_C0 (126) 
        pData[2] = 0xF7;                        //Peaking_C1 (-19)  
        pData[3] = 0x4A;                        //Peaking_C2 (82)
        pData[4] = 0x00;                        //Gain_Blur
        pData[5] = (WORD)(ucPeaking*195)/100;       //Gain_Pos(Min~Max)
        pData[6] = (WORD)(ucPeaking*195)/100;       //Gain_Neg(Min~Max)
        pData[7] = 0x0F;                        //Pos_Range(MSB)+Neg_Range(MSB)
        pData[8] = 0x20;                        //Pos_Range(LSB)(1023)
        pData[9] = 0x40;                        //Neg_Range(LSB)(1023)
        pData[10] = 0x09;                   //Coring(LV_min~LV_max)     
    }       
    else if(_GET_INPUT_SOURCE() == _SOURCE_YPBPR||_GET_INPUT_SOURCE() == _SOURCE_YPBPR1)
    {
        //if(HDMI_V_Height>=720)        //720p above
            pData[0] = 0x00;                    //bit[3:2]->10: 9 pixels; ->01: 7 pixels; ->00: 5 pixels      
        //else
            //pData[0] = 0x00;                  //bit[3:2]->10: 9 pixels; ->01: 7 pixels; ->00: 5 pixels      
        pData[1] = 0x7E;                        //Peaking_C0 (126) 
        pData[2] = 0xF7;                        //Peaking_C1 (-19)  
        pData[3] = 0x4A;                        //Peaking_C2 (82)
        pData[4] = 0x00;                        //Gain_Blur
        pData[5] = (WORD)(ucPeaking*195)/100;       //Gain_Pos(Min~Max)
        pData[6] = (WORD)(ucPeaking*195)/100;       //Gain_Neg(Min~Max)
        pData[7] = 0x00;                        //Pos_Range(MSB)+Neg_Range(MSB)
        pData[8] = 0x20;                        //Pos_Range(LSB)(1023)
        pData[9] = 0x40;                        //Neg_Range(LSB)(1023)
        pData[10] = 0x0E;                   //Coring(LV_min~LV_max)         
    }   
    else
    {//AV SV TV
        pData[0] = 0x00;                        //bit[3:2]->10: 9 pixels; ->01: 7 pixels; ->00: 5 pixels             
        pData[1] = 126;      //Peaking_C0 (126) 
        pData[2] = 11;      //Peaking_C1 (-9)  
        pData[3] = 54;      //Peaking_C2 (74)
        pData[4] = 0x00;      //Gain_Blur
        pData[5] = (WORD)(ucPeaking*255)/100;  //Gain_Pos(Min~Max)
        pData[6] = (WORD)(ucPeaking*255)/100;  //Gain_Neg(Min~Max)
        pData[7] = 0x00;       //Pos_Range(MSB)+Neg_Range(MSB)
        pData[8] = 128;        //Pos_Range(LSB)(1023)
        pData[9] = 128;        //Neg_Range(LSB)(1023)
        pData[10] =  0x26;     //Coring(LV_min~LV_max)
    }   
        
    // D-Domain Peaking 
    CScalerPageSelect(_PAGE7);
    CScalerWrite(_P7_PEAKING_DATA00_AA, 11, pData, _AUTOINC);
#if(_HDMI_SUPPORT == _OFF)
    if(_GET_INPUT_SOURCE()==_SOURCE_DVI)//HDMI Source & input DVI timing
        CScalerSetBit(_P7_PEAKING_ENABLE_A9, ~_BIT3, 0x00);     // disable Peaking and Coring
    else
#elif(_HDMI_SUPPORT == _ON || _TMDS_SUPPORT == _ON)
    if(_GET_INPUT_SOURCE()==_SOURCE_DVI || (_GET_INPUT_SOURCE() == _SOURCE_HDMI))// && !CHdmiFormatDetect()))//HDMI Source & input DVI timing
        CScalerSetBit(_P7_PEAKING_ENABLE_A9, ~_BIT3, 0x00);     // disable Peaking and Coring
    else
#endif
    {
        if (bSourceVideo())
        {
            CScalerSetByte(_P7_DLTI_DCTI_ENABLE_A1, 0xC0);       //Open  D DOMAIN's DCTI, Open GAIN to 0xOF
            CScalerSetByte(_P7_DLTI_GAIN_A3, 0x05);              //DLTi_Gain
            CScalerSetByte(_P7_DLTI_GAIN_THRESHOLD_A4, 0x01);    //DLTi_Gain_Threshold   0x1e
            CScalerSetByte(_P7_DLTI_OPTIONS_A5, 0x70);           //DLTi_Options
            CScalerSetByte(_P7_DCTI_1ST_GAIN_A6, 0x0F);          //Open GAIN to 0xOF
            CScalerSetBit(_P7_PEAKING_ENABLE_A9, ~_BIT3, _BIT3);    // enable Peaking and Coring
        }
        else
        {
            CScalerSetBit(_P7_DLTI_DCTI_ENABLE_A1, ~(_BIT6 | _BIT7), 0x00);
            CScalerSetBit(_P7_PEAKING_ENABLE_A9, ~_BIT3, _BIT3);    // enable Peaking and Coring
        }
    }

    switch(_GET_INPUT_SOURCE())
    {
    case _SOURCE_VGA:
        CScalerPageSelect(_PAGE6);
        CScalerSetBit(_P6_PEAKING_ENABLE_C1, ~_BIT3, 0x00); // disable Peaking and Coring
        return;

    case _SOURCE_HDMI:
    case _SOURCE_DVI:
        //if(HDMI_V_Height>=720)        //720p above
            pData[0] = 0x00;                    //bit[3:2]->10: 9 pixels; ->01: 7 pixels; ->00: 5 pixels      
        //else
            //pData[0] = 0x00;                  //bit[3:2]->10: 9 pixels; ->01: 7 pixels; ->00: 5 pixels      
        pData[1] = 0x7E;                        //Peaking_C0 (126) 
        pData[2] = 0xF7;                        //Peaking_C1 (-19)  
        pData[3] = 0x4A;                        //Peaking_C2 (82)
        pData[4] = 0x00;                        //Gain_Blur
        pData[5] = 0x14/*ucPeaking*13*/;        //Gain_Pos(Min~Max)
        pData[6] = 0x14/*ucPeaking*13*/;        //Gain_Neg(Min~Max)
        pData[7] = 0x0F;                        //Pos_Range(MSB)+Neg_Range(MSB)
        pData[8] = 0xFF;                        //Pos_Range(LSB)(80)
        pData[9] = 0xFF;                        //Neg_Range(LSB)(80)
        pData[10] = 0x09;                   //Coring(LV_min~LV_max)     
        break;

    case _SOURCE_YPBPR:
        pData[0] = 0x00;                    //bit[3:2]->10: 9 pixels; ->01: 7 pixels; ->00: 5 pixels               
        pData[1] = 0x7E;                        //Peaking_C0 (126) 
        pData[2] = 0xF7;                        //Peaking_C1 (-19)  
        pData[3] = 0x4A;                        //Peaking_C2 (82)
        pData[4] = 0x00;                        //Gain_Blur
        pData[5] = 0x14/*ucPeaking*13*/;        //Gain_Pos(Min~Max)
        pData[6] = 0x14/*ucPeaking*13*/;        //Gain_Neg(Min~Max)
        pData[7] = 0x0F;                        //Pos_Range(MSB)+Neg_Range(MSB)
        pData[8] = 0xFF;                        //Pos_Range(LSB)(1023)
        pData[9] = 0xFF;                        //Neg_Range(LSB)(1023)
        pData[10] = 0x09;                   //Coring(LV_min~LV_max)         
        break;
    case _SOURCE_YPBPR1:
        pData[0] = 0x00;                    //bit[3:2]->10: 9 pixels; ->01: 7 pixels; ->00: 5 pixels               
        pData[1] = 0x7E;                        //Peaking_C0 (126) 
        pData[2] = 0xF7;                        //Peaking_C1 (-19)  
        pData[3] = 0x4A;                        //Peaking_C2 (82)
        pData[4] = 0x00;                        //Gain_Blur
        pData[5] = 0x14/*ucPeaking*13*/;        //Gain_Pos(Min~Max)
        pData[6] = 0x14/*ucPeaking*13*/;        //Gain_Neg(Min~Max)
        pData[7] = 0x0F;                        //Pos_Range(MSB)+Neg_Range(MSB)
        pData[8] = 0xFF;                        //Pos_Range(LSB)(1023)
        pData[9] = 0xFF;                        //Neg_Range(LSB)(1023)
        pData[10] = 0x09;                   //Coring(LV_min~LV_max)         
        break;

    default:   //AV TV SV       
            pData[0] = 0x00;     //bit[3:2]->10: 9 pixels; ->01: 7 pixels; ->00: 5 pixels      
            pData[1] = 127;      //Peaking_C0 (126) 
            pData[2] = 74;      //Peaking_C1 (11)  
            pData[3] = 0xF6;      //Peaking_C2 (-10)
            pData[4] = 0x00;      //Gain_Blur
            pData[5] = 128;      //Gain_Pos(Min~Max)
            pData[6] = 128;      //Gain_Neg(Min~Max)
            pData[7] = 0x00;      //Pos_Range(MSB)+Neg_Range(MSB)
            pData[8] = 20;      //Pos_Range(LSB)(1023)
            pData[9] = 20;       //Neg_Range(LSB)(1023)
            pData[10] =  4 ;     //Coring(LV_min~LV_max)
        break;
    }

    // I-Domain Peaking 
    CScalerPageSelect(_PAGE6);
    CScalerWrite(_P6_PEAKING_DATA00_C2, 11, pData, _AUTOINC);
#if(_HDMI_SUPPORT == _OFF)
    if(_GET_INPUT_SOURCE()==_SOURCE_DVI)//HDMI Source & input DVI timing
        CScalerSetBit(_P6_PEAKING_ENABLE_C1, ~_BIT3, 0x00);     // disable Peaking and Coring
    else
#elif(_HDMI_SUPPORT == _ON || _TMDS_SUPPORT == _ON)
    //if(_GET_INPUT_SOURCE()==_SOURCE_DVI || (_GET_INPUT_SOURCE() == _SOURCE_HDMI && !CHdmiFormatDetect()))//HDMI Source & input DVI timing
    if((_GET_INPUT_SOURCE()==_SOURCE_DVI || _GET_INPUT_SOURCE() == _SOURCE_HDMI) && !CHdmiFormatDetect())//HDMI Source & input DVI timing
        CScalerSetBit(_P6_PEAKING_ENABLE_C1, ~_BIT3, 0x00);     // disable Peaking and Coring
    else
#endif
    {
        if (bSourceVideo())
        {
			if (ucVideoType == ZNTSC || ucVideoType == ZNTSC_443 || ucVideoType == ZNTSC_50)
				CScalerSetByte(_P6_DCTI_1ST_GAIN_D8, 0x0f);  //Close  I DOMAIN's DCTI,Open GAIN to 0xOF
			else
				CScalerSetByte(_P6_DCTI_1ST_GAIN_D8, 0x8f);  //Open  I DOMAIN's DCTI,Open GAIN to 0xOF
            CScalerSetByte(_P6_SPATIAL_CTRL_DB, 0x02);
            CScalerSetByte(_P6_PEAKING_ENABLE_C1, 0x00);            // disable Peaking and Coring
        }
        else
        {
            CScalerSetByte(_P6_DCTI_1ST_GAIN_D8, 0x4A);
            CScalerSetByte(_P6_SPATIAL_CTRL_DB, 0x00);
            CScalerSetBit(_P6_PEAKING_ENABLE_C1, ~_BIT3, _BIT3);    // enable Peaking and Coring
        }
    }
}
    
#else

#if(_Peaking_Coring_Table == SharpnessTable1)
                                                                                                    
BYTE code PeakingCoeff[][6] =
{
        //Peaking_Coef0,  Peaking_Coef1,  Peaking_Coef2,  Coring_Min,  Coring_Max_Pos,  Coring_Max_Neg ,

        //level=1 :
        0x30, 0xe5, 0x3, 0x5, 0x50, 0xb0,
        //level=2 :
        0x38, 0xe1, 0x3, 0x5, 0x50, 0xb0,
        //level=3 :
        0x40, 0xdc, 0x4, 0x5, 0x50, 0xb0,
        //level=4 :
        0x46, 0xd7, 0x6, 0x5, 0x50, 0xb0,
        //level=5 :
        0x4e, 0xd3, 0x6, 0x5, 0x50, 0xb0,
        //level=6 :
        0x56, 0xce, 0x7, 0x5, 0x50, 0xb0,
        //level=7 :
        0x5e, 0xca, 0x7, 0x5, 0x50, 0xb0,
        //level=8 :
        0x66, 0xc5, 0x8, 0x5, 0x50, 0xb0,
        //level=9 :
        0x6e, 0xc1, 0x8, 0x5, 0x50, 0xb0,
        //level=10 :
        0x76, 0xbc, 0x9, 0x5, 0x50, 0xb0,
        //level=11 :
        0x40, 0xdc, 0x4, 0x5, 0x50, 0xb0,
        //level=12 :
        0x46, 0xd7, 0x6, 0x5, 0x50, 0xb0,
        //level=13 :
        0x4e, 0xd3, 0x6, 0x5, 0x50, 0xb0,
        //level=14 :
        0x56, 0xce, 0x7, 0x5, 0x50, 0xb0,
        //level=15 :
        0x5e, 0xca, 0x7, 0x5, 0x50, 0xb0,
        //level=16 :
        0x66, 0xc5, 0x8, 0x5, 0x50, 0xb0,

};

BYTE code TVPeakingCoeff[][6] =
{
        //Peaking_Coef0,  Peaking_Coef1,  Peaking_Coef2,  Coring_Min,  Coring_Max_Pos,  Coring_Max_Neg ,

        //level=0 :
        0x0, 0x0, 0x0, 0x14, 0x50, 0xb0,
        //level=1 :
        0x4, 0x1, 0xfd, 0x16, 0x50, 0xb0,
        //level=2 :
        0x6, 0x2, 0xfb, 0x18, 0x50, 0xb0,
        //level=3 :
        0xa, 0x3, 0xf8, 0x1a, 0x50, 0xb0,
        //level=4 :
        0xc, 0x5, 0xf5, 0x1c, 0x50, 0xb0,
        //level=5 :
        0x10, 0x6, 0xf2, 0x1e, 0x50, 0xb0,
        //level=6 :
        0x12, 0x7, 0xf0, 0x1f, 0x50, 0xb0,
        //level=7 :
        0x16, 0x8, 0xed, 0x1f, 0x50, 0xb0,
        //level=8 :
        0x1a, 0xa, 0xe9, 0x1f, 0x50, 0xb0,
        //level=9 :
        0x1c, 0xb, 0xe7, 0x1f, 0x50, 0xb0,
        //level=10 :
        0x20, 0xc, 0xe4, 0x1f, 0x50, 0xb0,
        //level=11 :
        0x22, 0xd, 0xe2, 0x1f, 0x50, 0xb0,
        //level=12 :
        0x26, 0xf, 0xde, 0x1f, 0x50, 0xb0,
        //level=13 :
        0x2c, 0x11, 0xd9, 0x1f, 0x50, 0xb0,
        //level=14 :
        0x32, 0x14, 0xd3, 0x1f, 0x50, 0xb0,
        //level=15 :
        0x38, 0x16, 0xce, 0x1f, 0x50, 0xb0,
        //level=16 :
        0x3e, 0x19, 0xc8, 0x1f, 0x50, 0xb0,
};

#elif(_Peaking_Coring_Table == SharpnessTable2)

BYTE code PeakingCoeff[][6] =
{
        //Peaking_Coef0,  Peaking_Coef1,  Peaking_Coef2,  Coring_Min,  Coring_Max_Pos,  Coring_Max_Neg ,

        //level=1 :
        0x08, 0x00, 0xFC, 0x00, 0x28, 0xF8,
        //level=2 :
        0x0C, 0x00, 0xFA, 0x00, 0x28, 0xF8,
        //level=3 :
        0x10, 0x00, 0xF8, 0x00, 0x28, 0xF8,
        //level=4 :
            0x18, 0x00, 0xF4, 0x00, 0x28, 0xF8, //3
        //level=5 :
        0x20, 0x00, 0xF0, 0x00, 0x28, 0xF8,
        //level=6 :
        0x28, 0x00, 0xEC, 0x00, 0x28, 0xF8,
        //level=7 :
        0x30, 0x00, 0xE8, 0x00, 0x28, 0xF8,
        //level=8 :
        0x38, 0x00, 0xE4, 0x00, 0x28, 0xF8,
        //level=9 :
        0x40, 0x00, 0xE0, 0x00, 0x28, 0xF8,
        //level=10 :
        0x46, 0x00, 0xDD, 0x00, 0x28, 0xF8,
        //level=11 :
        0x4E, 0x00, 0xD9, 0x00, 0x28, 0xF8,
        //level=12 :
        0x56, 0x00, 0xD5, 0x00, 0x28, 0xF8,
        //level=13 :
        0x5E, 0x00, 0xD1, 0x00, 0x28, 0xF8,
        //level=14 :
        0x66, 0x00, 0xCD, 0x00, 0x28, 0xF8,
        //level=15 :
        0x6E, 0x00, 0xC9, 0x00, 0x28, 0xF8,
        //level=16 :
        0x76, 0x00, 0xC5, 0x00, 0x28, 0xF8,
};


BYTE code TVPeakingCoeff[][6] =
 {
        //Peaking_Coef0,  Peaking_Coef1,  Peaking_Coef2,  Coring_Min,  Coring_Max_Pos,  Coring_Max_Neg ,

        //level=1 :
         0x08, 0x00, 0xFC, 0x12, 0x60, 0xF8,
        //level=2 :
         0x0A, 0x00, 0xFB,  0x12, 0x60, 0xF8,
        //level=3 :
         0x0C, 0x00, 0xFA,  0x12, 0x60, 0xF8,
        //level=4 :
         0x0E, 0x00, 0xF9,  0x12, 0x60, 0xF8,
        //level=5 :
         0x10, 0x00, 0xF8,  0x12, 0x60, 0xF8,
        //level=6 :
         0x12, 0x00, 0xF7,  0x12, 0x60, 0xF8,
        //level=7 :
         0x14, 0x00, 0xF6,  0x12, 0x60, 0xF8,
        //level=8 :
         0x16, 0x00, 0xF5,  0x12, 0x60, 0xF8,
        //level=9 :
             0x18, 0x00, 0xF4,  0x12, 0x60, 0xF8,
        //level=10 :
         0x1A, 0x00, 0xF3,  0x12, 0x60, 0xF8,
        //level=11 :
         0x1C, 0x00, 0xF2,  0x12, 0x60, 0xF8,
        //level=12 :
         0x1E, 0x00, 0xF1,  0x12, 0x60, 0xF8,
        //level=13 :
         0x20, 0x00, 0xF0,  0x12, 0x60, 0xF8,
        //level=14 :
         0x22, 0x00, 0xEF,  0x12, 0x60, 0xF8,
         //level=15 :
         0x24, 0x00, 0xEE,  0x12, 0x60, 0xF8,
        //level=16 :
         0x26, 0x00, 0xED,  0x12, 0x60, 0xF8,
};
#endif
//----------------------------------------------------
// CAdjustPeakingFilter
// Adjust Peaking Filter and Coring Control
// @param <Coefficient C0 of Peaking Filter>
// @return {none}
//----------------------------------------------------
            
void CAdjustPeakingFilter(SBYTE ucPeaking)
{
#if (_Peaking_Coring_Table != SharpnessNoneTable)//reference Table
    if((_GET_INPUT_SOURCE()==_SOURCE_VGA)||(_GET_INPUT_SOURCE()==_SOURCE_DVI) || (_GET_INPUT_SOURCE() == _SOURCE_HDMI))
    {
        CScalerPageSelect(_PAGE7);
        CScalerSetByte(_P7_PC_ACCESS_PORT_D6, 0x00);

        return;
    }
    else
    {

        if(_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
        {
            pData[0] = TVPeakingCoeff[ucPeaking][0];
            pData[1] = TVPeakingCoeff[ucPeaking][1];
            pData[2] = TVPeakingCoeff[ucPeaking][2];
            pData[3] = TVPeakingCoeff[ucPeaking][3];
            pData[4] = TVPeakingCoeff[ucPeaking][4];
            pData[5] = TVPeakingCoeff[ucPeaking][5];

        }
        else
        {
            pData[0] = PeakingCoeff[ucPeaking][0];
            pData[1] = PeakingCoeff[ucPeaking][1];
            pData[2] = PeakingCoeff[ucPeaking][2];
            pData[3] = PeakingCoeff[ucPeaking][3];
            pData[4] = PeakingCoeff[ucPeaking][4];
            pData[5] = PeakingCoeff[ucPeaking][5];
        }

        CScalerPageSelect(_PAGE7);
        CScalerSetByte(_P7_PC_ACCESS_PORT_D6, 0x80);
        CScalerWrite(_P7_PC_DATA_PORT_D7, 6, pData, _NON_AUTOINC);
        CScalerSetByte(_P7_PC_ACCESS_PORT_D6, 0x40);

    }

#else//default

    if((_GET_INPUT_SOURCE() == _SOURCE_VGA)||(_GET_INPUT_SOURCE() == _SOURCE_DVI) || (_GET_INPUT_SOURCE() == _SOURCE_HDMI))
        ucPeaking = ucPeaking * 2;
    else
        ucPeaking = ucPeaking * 8;

    if(ucPeaking > 126)
        ucPeaking = 126;
    if(ucPeaking < 14 && ucPeaking > 0)
        ucPeaking = 14;
        
    pData[0] = ((ucPeaking +1) >> 1) << 1;
    if((bit)(ucPeaking & 0x01))
    {
        pData[1] = (SWORD)-72 * pData[0] / 126;
        pData[2] = (SWORD)-(pData[0] + 2*pData[1]) / 2;
    }
    else
    {
        pData[1] = (SWORD)-73 * pData[0] / 126;
        pData[2] = (SWORD)-(pData[0] + 2*pData[1]) / 2;
    }

    pData[3] = (BYTE)_CORING_MIN;
    pData[4] = (BYTE)_CORING_MAX_POS;
    pData[5] = (SBYTE)_CORING_MAX_NEG;
    CScalerPageSelect(_PAGE7);
    CScalerSetByte(_P7_PC_ACCESS_PORT_D6, 0x80);
    CScalerWrite(_P7_PC_DATA_PORT_D7, 6, pData, _NON_AUTOINC);
    CScalerSetByte(_P7_PC_ACCESS_PORT_D6, 0x40);

#endif
}


#endif

//--------------------------------------------------
// Description  : Adjust sharpness
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustPeakingCoding(void)
{
    CAdjustPeakingFilter(GET_PEAKING_CORING());
}

void CAdjustVolume(void)
{
    BYTE iVolume;

    iVolume = (WORD)(_MAX_VOLUME - _MIN_VOLUME) * stAudioData.Volume/ 100;

    if(_VOLUME_INV == 0)
        iVolume = _MAX_VOLUME - iVolume;
    else
        iVolume = _MIN_VOLUME + iVolume;
      
    CSetPWM(bVOLUME_PWM,iVolume);
}

//--------------------------------------------------
// Description  : Adjust backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustBacklight(void)
{
#if(_BACKLIGHT_USE_FAC_ADJ == _DISABLE)

    BYTE ucLight;

    ucLight = (WORD)(_BACKLIGHT_MAX - _BACKLIGHT_MIN) * stConBriData.Brightness/100;

 #if(_BACKLIGHT_PWM_INVERSE == _ENABLE)

    ucLight = _BACKLIGHT_MAX - ucLight;
 #else

    ucLight = _BACKLIGHT_MIN + ucLight;

 #endif

    CSetPWM(_BACKLIGHT_PWM, ucLight);

#else

    BYTE ucLight;

    ucLight = (BYTE)((WORD)(255) * stSystemData.BackLight/100);

	CSetPWM(_BACKLIGHT_PWM, ucLight);
#endif
}
//--------------------------------------------------
void CAdjustGammaTable(BYTE index)
{
    index = index;
#if(_GAMMA_TYPE ==  _FULL_GAMMA_NORMAL_TABLE)
    switch(index)
    {
    case 1:
        CAdjustGamma(_FULL_GAMMA_NORMAL_TABLE, GAMMA_1_R, GAMMA_1_G, GAMMA_1_B);
        break;

    case 2:
        CAdjustGamma(_FULL_GAMMA_NORMAL_TABLE, GAMMA_2_R, GAMMA_2_G, GAMMA_2_B);
        break;

    case 3:
        CAdjustGamma(_FULL_GAMMA_NORMAL_TABLE, GAMMA_3_R, GAMMA_3_G, GAMMA_3_B);
        break;

    case 0:
        CScalerSetBit(_GAMMA_CTRL_67, ~_BIT6, 0x00);
        break;

    default:
        break;
    }
    
#elif(_GAMMA_TYPE == _FULL_GAMMA_COMPRESS_TABLE2)

    switch(index)
    {
    case 0:     // disable Gamma
        CScalerSetBit(_GAMMA_CTRL_67, ~_BIT6, 0x00);
        break;

    case 1:
        CAdjustGamma(_FULL_GAMMA_COMPRESS_TABLE2, GAMMA_1_R, GAMMA_1_G, GAMMA_1_B);
        break;

    case 2:
        CAdjustGamma(_FULL_GAMMA_COMPRESS_TABLE2, GAMMA_2_R, GAMMA_2_G, GAMMA_2_B);
        break;

    case 3:
        CAdjustGamma(_FULL_GAMMA_COMPRESS_TABLE2, GAMMA_3_R, GAMMA_3_G, GAMMA_3_B);
        break;
    
    default:
        break;
    }
#endif
}


#if(sRGB_Color_Enhance == _ENABLE)
//Use sRGB to adjust Saturation and Hue
void CAdjustSaturationHue(BYTE  ucValue, BOOL bSaturationIndex)
{
//Lewis, this table have multiplied by 1024
    INT16 code YUV2RGB[3][3] =
    {
      {1024,   0,      1436},
      {1024,   -342,   -731},
      {1024,   1815,   0}
     };

//Lewis, this table have multiplied by 1024
    INT16 code RGB2YUV[3][3] =
    {
        {306,     601,   117},
      {-173,   -339,    512},
        {512,   -429,   -83}
     };

    BYTE i, j;
    INT16 temp_buff0[3][3];
    //731401***
    //INT16 temp_buff1[3][3];
    //INT16 temp_buff2[3][3];
    INT16 MATRIX_GAIN_HUE[3][3];
    //INT16 MATRIX_GAIN[3][3];
    //INT16 MATRIX_HUE[3][3];
    //731401###
    INT16 temp_hue, temp_saturation;


    if(bSaturationIndex == _TRUE) //adjust saturation
    {
        temp_saturation=(INT16)ucValue;
        temp_hue=(INT16)GET_HUE() - 50;
    }
    else
    {
        temp_saturation = (INT16)GET_SATURATION();
        temp_hue=(INT16)ucValue - 50;
    }

    //Lewis 20060717, to prevent adjust CSC matrix, the saturation overflow
    if(temp_saturation>75)
        temp_saturation = 75;
    else if(temp_saturation<25)
        temp_saturation = 25;

    temp_hue = temp_hue*19>>5; //Lewis, 20060720, limited Hue range to prevent grey bar have color
//731401***
//Lewis, this table have multiplied by 1024
    MATRIX_GAIN_HUE[0][0] = 1024;
    MATRIX_GAIN_HUE[0][1] = 0;
    MATRIX_GAIN_HUE[0][2] = 0;
    MATRIX_GAIN_HUE[1][0] = 0;
    MATRIX_GAIN_HUE[1][1] = ((temp_saturation<<7)/25)<<2;
    MATRIX_GAIN_HUE[1][2] = 0;
    MATRIX_GAIN_HUE[2][0] = 0;
    MATRIX_GAIN_HUE[2][1] = 0;
    MATRIX_GAIN_HUE[2][2] = MATRIX_GAIN_HUE[1][1];

    CAdjustMatrixMultiply(MATRIX_GAIN_HUE,RGB2YUV,temp_buff0);
    
//Lewis, this table have multiplied by 1024
    MATRIX_GAIN_HUE[0][0] = 1024;
    MATRIX_GAIN_HUE[0][1] = 0;
    MATRIX_GAIN_HUE[0][2] = 0;
    MATRIX_GAIN_HUE[1][0] = 0;
    MATRIX_GAIN_HUE[1][1] = CAdjustCosine(temp_hue);
    MATRIX_GAIN_HUE[1][2] = CAdjustSine(temp_hue);
    MATRIX_GAIN_HUE[2][0] = 0;
    MATRIX_GAIN_HUE[2][1] = (-1)*MATRIX_GAIN_HUE[1][2];//-CAdjustSine(temp);
    MATRIX_GAIN_HUE[2][2] = MATRIX_GAIN_HUE[1][1]; //CAdjustCosine(temp);


    CAdjustMatrixMultiply(MATRIX_GAIN_HUE,temp_buff0,temp_buff0);
    CAdjustMatrixMultiply(YUV2RGB,temp_buff0,temp_buff0);

    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            if (i==j)
               temp_buff0[i][j]-=1024;
    
            temp_buff0[i][j] = temp_buff0[i][j]>>1;
    
            if (temp_buff0[i][j]>255)
                temp_buff0[i][j] = 255;
            else if(temp_buff0[i][j]<-256)
                temp_buff0[i][j] = -256;
        }
    }

    //Write R
    //frank CScalerSetBit(_COLOR_CTRL_62,0xc7,0x08);
    pData[0] =(temp_buff0[0][0]<0?1:0);
    pData[1]=(BYTE)(temp_buff0[0][0]);
    pData[2] =(temp_buff0[0][1]<0?1:0);
    pData[3]=(BYTE)(temp_buff0[0][1]);
    pData[4] =(temp_buff0[0][2]<0?1:0);
    pData[5]=(BYTE)(temp_buff0[0][2]);

//  CAdjustSetsRGBRhue();
    CAdjustSetYpbprRhue();

    //Write G
    //frank CScalerSetBit(_COLOR_CTRL_62,0xc7,0x10);

    pData[0] =(temp_buff0[1][0]<0?1:0);
    pData[1]=(BYTE)(temp_buff0[1][0]);
    pData[2] =(temp_buff0[1][1]<0?1:0);
    pData[3]=(BYTE)(temp_buff0[1][1]);
    pData[4] =(temp_buff0[1][2]<0?1:0);
    pData[5]=(BYTE)(temp_buff0[1][2]);

//  CAdjustSetsRGBGhue();
    CAdjustSetYpbprGhue();

    //Write B

    pData[0] =(temp_buff0[2][0]<0?1:0);
    pData[1]=(BYTE)(temp_buff0[2][0]);
    pData[2] =(temp_buff0[2][1]<0?1:0);
    pData[3]=(BYTE)(temp_buff0[2][1]);
    pData[4] =(temp_buff0[2][2]<0?1:0);
    pData[5]=(BYTE)(temp_buff0[2][2]);
//731401###
//  CAdjustSetsRGBBhue();
    CAdjustSetYpbprBhue();

    CScalerSetBit(_COLOR_CTRL_62, 0xff, 0x80);          // cftsai 20061031 added, ready to write
}

INT16 CAdjustCosine(INT16 fDegree)
{
    //Lewis, the curve value table have multiplied by 1024
    UINT16 code fCosCurveAngle[13] = {   0,   6,  12,  18,  24,  30,  37,  44,  52,  60,  68,  78, 90};
    UINT16 code fCosCurveValue[13] = {1024, 1018, 1002, 974, 935, 887, 818, 737, 630, 512, 384, 213,  0};
    UINT8 i,cQuadrant;
    INT16 fDegreeTemp, fDegreeSpan, fCosValueSpan, fCosValue;

    if (fDegree < 0)
        fDegree += 360;

    fDegree = fDegree%360;

    //locate degree on which quadrant
    cQuadrant = (UINT8)(fDegree / 90);
    cQuadrant++;
    if (cQuadrant==1) //first quadrant
        fDegree = fDegree;
    else if(cQuadrant==2) //second quadrant
        fDegree = 180 - fDegree;
    else if(cQuadrant==3) //third quadrant
        fDegree = fDegree - 180;
    else if(cQuadrant==4) //forth quadrant
        fDegree = 360 -fDegree;
    //locate degree on which quadrant

    if (fDegree<=fCosCurveAngle[0])
        fCosValue = fCosCurveValue[0];
    else
    {
        for (i=0;fCosCurveAngle[i] < fDegree; i++);

        i--;
        fDegreeTemp = fDegree-fCosCurveAngle[i];
        fDegreeSpan = fCosCurveAngle[i+1]-fCosCurveAngle[i];
        fCosValueSpan = fCosCurveValue[i+1]-fCosCurveValue[i];
        fCosValue = fCosCurveValue[i]+fDegreeTemp*fCosValueSpan/fDegreeSpan;
    }

    if (cQuadrant==2 || cQuadrant==3)
        fCosValue = fCosValue*(-1);

    return fCosValue;
}

INT16 CAdjustSine(INT16 fDegree)
{
    //Lewis, this table have multiplied by 1024
    UINT16 code fSinCurveAngle[13] = {0,   6,  12,  18,  24,  30,  37,  44,  52,  60,  68,  78, 90};
    UINT16 code fSinCurveValue[13] = {0, 107, 213, 316, 416, 512, 616, 711, 807, 887, 949, 1002,  1024};
    UINT8 i,cQuadrant;
    INT16 fDegreeTemp,fDegreeSpan,fSinValueSpan,fSinValue;

    if (fDegree < 0)
        fDegree += 360;

    fDegree = fDegree%360;

    //locate degree on which quadrant
    cQuadrant = (UINT8)(fDegree / 90);
    cQuadrant++;
    if (cQuadrant==1) //first quadrant
        fDegree = fDegree;
    else if(cQuadrant==2) //second quadrant
        fDegree = 180 - fDegree;
    else if(cQuadrant==3) //third quadrant
        fDegree = fDegree - 180;
    else if(cQuadrant==4) //forth quadrant
        fDegree = 360 -fDegree;
    //locate degree on which quadrant

    if (fDegree<=fSinCurveAngle[0])
        fSinValue = fSinCurveValue[0];
    else
    {
        for (i=0;fSinCurveAngle[i] < fDegree; i++);

        i--;
        fDegreeTemp = fDegree-fSinCurveAngle[i];
        fDegreeSpan = fSinCurveAngle[i+1]-fSinCurveAngle[i];
        fSinValueSpan = fSinCurveValue[i+1]-fSinCurveValue[i];
        fSinValue = fSinCurveValue[i]+fDegreeTemp*fSinValueSpan/fDegreeSpan;
    }

    if (cQuadrant==3 || cQuadrant==4)
        fSinValue = fSinValue*(-1);

    return fSinValue;
}

void CAdjustMatrixMultiply(INT16 (*arrayA)[3], INT16 (*arrayB)[3], INT16 (*arrayC)[3])
{
    BYTE i, j;
    INT32 Temp[3][3];

    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            Temp[i][j] = ((INT32)arrayA[i][0]*arrayB[0][j]>>2)
                        + ((INT32)arrayA[i][1]*arrayB[1][j]>>2)
                        + ((INT32)arrayA[i][2]*arrayB[2][j]>>2);

            //arrayC[i][j] = (INT16)(Temp[i][j]>>8);//731401
        }
    }

    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            arrayC[i][j] = (INT16)(Temp[i][j]>>8);
        }
    }

}

#endif



BYTE code SatPlus[8]  = { 41, 44, 43, 39, 31, 22, 11, 0 }; // by 1/256
BYTE code SatMinus[8] = { 24, 35, 40, 41, 36, 28, 16, 0 }; // by 1/256

int CAdjustColorGammaCal(BYTE color, BYTE n) // n = 1~8
{
    BYTE temp;

    if (color == 0)     //R
        temp = GET_ICM_SAT_R();
    else if (color== 1) //G
        temp = GET_ICM_SAT_G();
    else if (color == 2)//B
        temp = GET_ICM_SAT_B();
    else if (color == 3)//Y
        temp = GET_ICM_SAT_Y();
    else if (color == 4)//C
        temp = GET_ICM_SAT_C();
    temp *= 2;  //Since the scale for OSD(from 0~16) and cloor(from 0~32) is different, we will have to multiply
               //temp by 2 to make up the difference
    if (temp >= 16)
    {
        return ((int)(512*n) + (int)((temp-16)*(int)SatPlus[n-1])) / 64 ;
    }
    else
    {
        return ((int)(512*n) - (int)((16-temp)*(int)SatMinus[n-1])) / 64 ;
    }
}

#define CENTER    0x00
#define RIGHT     0x10
#define LEFT      0x20

void CAdjustMZHueSat(BYTE color)
{
    //Value  0~4095 => angle 0~359
    //R / G / B / Y /C
    //range  256 => 22.5  degree
    //buffer 128 => 11.25 degree
    //R / G / B
    //range  512 => 45    degree
    //buffer 128 => 11.25 degree
    CTimerWaitForEvent(_EVENT_DEN_STOP);
    CAdjustSetHueUVDelta(color, CENTER);
    CAdjustSetHueUVDelta(color, RIGHT);
    CAdjustSetHueUVDelta(color, LEFT);

    CScalerPageSelect(_PAGE7);
    CScalerSetBit(_P7_ICM_CTRL_D0, ~_BIT7, _BIT7);

}


