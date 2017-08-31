#include "Core\Header\include.h"


#if(_KEY_TYPE == _KT_PCB2660_003)

#define AD_KEY_STEP    3

//--------------------------------------------------
// Description  : Get key status
// Input Value  : None
// Output Value : Return Key status
//--------------------------------------------------
#if(_KEY_SCAN_TYPE == _KEY_SCAN_NORMAL)

BYTE CKeyScanIO(void)
{
	BYTE ucKeyState = _NONE_KEY_MASK;    
    
    if(!bKey0)   	ucKeyState    = ucKeyState | _AT_KEY0;
    if(!bKey1)   	ucKeyState    = ucKeyState | _AT_KEY1;
    if(!bKey2)   	ucKeyState    = ucKeyState | _AT_KEY2;
    if(!bKey3)   	ucKeyState    = ucKeyState | _AT_KEY3;
    if(!bKey4)   	ucKeyState    = ucKeyState | _AT_KEY4;
    if(!bKey5)   	ucKeyState    = ucKeyState | _AT_KEY5;
    if(!bKey6)   	ucKeyState    = ucKeyState | _AT_KEY6;
    if(!bKey7)   	ucKeyState    = ucKeyState | _AT_KEY7;
    
	return ucKeyState;
}
//--------------------------------------------------
BYTE CIOMaskToKeyMaskPreset(BYTE ucIOMask)
{
	BYTE code *p = tIOKeyMask;
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
BYTE CIOMaskToKeyMask(BYTE ucIOMask)
{
	if(g_bUsePresetKey)
	{
		return CIOMaskToKeyMaskPreset(ucIOMask);
	}
	else
	{
		return CIOMaskToKeyMaskExt(ucIOMask);
	}
}

#else

BYTE CKeyScanIO(void)
{
	return 0;
}

#endif
//--------------------------------------------------
BYTE CKeyScan(void)
{
    BYTE ucKeyState = _NONE_KEY_MASK;    

#if(_KEY_SCAN_TYPE == _KEY_SCAN_NORMAL)
    ucKeyState = CKeyScanIO();
    ucKeyState = CIOMaskToKeyMask(ucKeyState);
#else
    BYTE ADa0 = CGetADCAValue(AD_KEY);
    BYTE ADa1 = CGetADCAValue(AD_KEY);
	
	if(_ABS(ADa0, ADa1) < AD_KEY_STEP)
	{
// ADC key0	    
	    if(ADa0 == bAD0_Key_NONE)  			ucKeyState = _NONE_KEY_MASK;
//POWER/Input/Sleep time/Left/Menu/Right/Display mode //wtao100410		
	    else if(_ABS(ADa0, bAD0_Key_1) < AD_KEY_STEP)  	ucKeyState = _POWER_KEY_MASK;
	    else if(_ABS(ADa0, bAD0_Key_2) < AD_KEY_STEP)  	ucKeyState = _SOURCE_KEY_MASK;
	    else if(_ABS(ADa0, bAD0_Key_3) < AD_KEY_STEP)  	ucKeyState = _SLEEP_KEY_MASK;
	    else if(_ABS(ADa0, bAD0_Key_4) < AD_KEY_STEP)  	ucKeyState = _LEFT_KEY_MASK;
	    else if(_ABS(ADa0, bAD0_Key_5) < AD_KEY_STEP)  	ucKeyState = _MENU_KEY_MASK;
	    else if(_ABS(ADa0, bAD0_Key_6) < AD_KEY_STEP)  	ucKeyState = _RIGHT_KEY_MASK;
	    else if(_ABS(ADa0, bAD0_Key_7) < AD_KEY_STEP)  	ucKeyState = _Reset_KEY_MASK;//_DISPLAYMODE_KEY_MASK;
           else ucKeyState= _NONE_KEY_MASK;
	#if 0   //Debug wtao100410
		OSDPosition(120, 18, 0, 1, 0x03); 	
		COsdFxEnableOsd();    
		Gotoxy(20, 0, BYTE_DISPLAY);
		PrintfDec(ADa0);
		CTimerCancelTimerEvent(COsdTimeOut);
	#endif
		
	}
#endif

    if(ucKeyState != _NONE_KEY_MASK)
       CKeyInitial();

    return ucKeyState;
}
//--------------------------------------------------
/*
void CScanAutoKey(void)
{
     if(GET_POWERSTATUS())
     {
         // check 3 sec do change source ???
         #if(_TMDS_SUPPORT)
         {
             if(CheckKeyUp(_AUTO_KEY_MASK,50))
                ucKeyMessage = _AUTO_KEY_MESSAGE;
             else ucKeyMessage = _SOURCE_KEY_MESSAGE;
         }
         #else
         {
             CKeyMessageConvert(_AUTO_KEY_MASK, _AUTO_KEY_MESSAGE);
         }
         #endif
     }
     else
     {
         if(CheckKeyDown(_AUTO_KEY_MASK | _POWER_KEY_MASK,20))
         {
             SET_POWERSWITCH();
             ucKeyMessage = _AUTO_POWER_KEY_MESSAGE;
         }
     }
}
*/
//--------------------------------------------------

void CheckMenuKey(void)
{
	if(CheckKeyUp(_MENU_KEY_MASK,250) == 0)
	{
       if(stSystemData.InputSource == _SOURCE_VGA)
	    {		
	    	ucKeyMessage = _FAC_KEY_MESSAGE;
		}
		else
		{
		    CKeyMessageConvert(_MENU_KEY_MASK, _MENU_KEY_MESSAGE);
		}

	}
	else
	{
		CKeyMessageConvert(_MENU_KEY_MASK, _MENU_KEY_MESSAGE);
	}
		
}
//--------------------------------------------------

void CKeyMessageProc(void)
{          
    switch(ucKeyStateCurr)
    {        
        case _MENU_KEY_MASK:	 //Menu
            CheckMenuKey();     
            break;
/*        case _UP_KEY_MASK:	     
            CKeyMessageConvert(_UP_KEY_MASK, _UP_KEY_MESSAGE);
            break;
        
           case _DOWN_KEY_MASK:	 
            CKeyMessageConvert(_DOWN_KEY_MASK, _DOWN_KEY_MESSAGE);
            break;
*/

        case _SLEEP_KEY_MASK:	     
            CKeyMessageConvert(_SLEEP_KEY_MASK, _SLEEP_KEY_MESSAGE);
            break;
        
        case _DISPLAYMODE_KEY_MASK:	 
            CKeyMessageConvert(_DISPLAYMODE_KEY_MASK, _DISPLAY_RATIO_MESSAGE);
            break;

        case _TCON_KEY_MASK:	 
            CKeyMessageConvert(_TCON_KEY_MASK, _TCON_MESSAGE);
            break;

        case _LEFT_KEY_MASK:     //Left
            CKeyMessageConvert(_LEFT_KEY_MASK, _LEFT_KEY_MESSAGE);
            break;

        case _RIGHT_KEY_MASK:    //Right
            CKeyMessageConvert(_RIGHT_KEY_MASK, _RIGHT_KEY_MESSAGE);
            break; 
               
        case _SOURCE_KEY_MASK:
            CKeyMessageConvert(_SOURCE_KEY_MASK, _SOURCE_KEY_MESSAGE);
            break;
        case _Reset_KEY_MASK:
	     //CKeyMessageConvert(_Reset_KEY_MASK, _Reset_KEY_MESSAGE);	
	    break;	 
        default:
            CLR_KEYREPEATSTART();
            CTimerCancelTimerEvent(CKeyRepeatEnableTimerEvent);
            break;
    }
} 
//--------------------------------------------------
              
#endif      //#if(_KEY_TYPE == _KT_PCB2660_003)
