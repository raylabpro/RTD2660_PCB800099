//----------------------------------------------------------------------------------------------------
// ID Code      : Key.c No.0001
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#define __KEY__

#include "Core\Header\include.h"
               
//--------------------------------------------------
// Description  : Key scan process     
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void IrProcessMessage(void);
void CKeyHandler(void)
{
    // Clear the key message
    ucKeyMessage = _NONE_KEY_MESSAGE;
    
    if(CKeyScanReady())// || _ACTIVE_STATE != ucCurrState)
    {
        // Store previous key state
        ucKeyStatePrev = ucKeyStateCurr;
        
        // Get current key state
        ucKeyStateCurr = CKeyScan();
           
        // Power key process, return if power key is pressed
        if(CKeyPowerKeyProc())
            return;
        
        // Convert key state to key message, store in (ucKeyNotify)
        CKeyMessageProc();

    #if(_REMOTE_CONTROLLER != _IR_NONE) 
        {
            if(ucKeyMessage == _NONE_KEY_MESSAGE)
            {        
               ucKeyMessage = CIRKeyScan();
               #ifdef IRSEND_ENABLE
                   IrProcessMessage();      
               #endif
	#if 0   //Debug
		OSDPosition(120, 18, 0, 1, 0x03); 	
		COsdFxEnableOsd();    
		Gotoxy(20, 0, BYTE_DISPLAY);
		PrintfDec(ucKeyMessage);
		CTimerCancelTimerEvent(COsdTimeOut);
	#endif

               if (ucKeyMessage != _NONE_KEY_MESSAGE)
                  ucPrevKey = ucKeyMessage;                   
            }
        }
    #endif
    }
    
#if(_DEBUG_TOOL != _NONE)
    GetVirtualKey();
#endif
    
    if(ucKeyMessage == _POWER_KEY_MESSAGE)
    {
        CIrdaReadData();	
        CIrdaReadData();	
        SET_POWERSWITCH();
    }

    // debug info
    //if(ucKeyMessage != _NONE_KEY_MESSAGE)
	//	CUartPrintf("KeyMessage:",ucKeyMessage);
}

//--------------------------------------------------
// Description  : Check power key process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
/*
void CKeyCheckPowerKey(void)
{
    // Store previous key state
    ucKeyStatePrev = ucKeyStateCurr;
    
    // Get current key state
    ucKeyStateCurr = CKeyScan();
    
    // Power key process
    CKeyPowerKeyProc();
}
*/
//--------------------------------------------------
// Description  : Initial key status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CKeyInitial(void)
{
    CLR_KEYSCANREADY();
    CLR_KEYSCANSTART();
}

//--------------------------------------------------
// Description  : Key scan ready process. We wait 0.02 sec in order to keep the keypad debounce
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit CKeyScanReady(void)
{
    if(GET_KEYSCANSTART() && GET_KEYSCANREADY())
    {
		CLR_KEYSCANSTART();  //
		CLR_KEYSCANREADY();  //
        return _TRUE;
    }
    else if(!GET_KEYSCANSTART())
    {
        // Wait 0.02 sec in order to keep the keypad debounce
        SET_KEYSCANSTART();
        //CTimerReactiveTimerEvent(SEC(0.02), CKeyScanReadyTimerEvent);
        CTimerReactiveTimerEvent(SEC(0.03), CKeyScanReadyTimerEvent);
        
        return _FALSE;
    }
    else
    {
        return _FALSE;
    }  
}

//--------------------------------------------------
// Description  : Key scan ready timer event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CKeyScanReadyTimerEvent(void)
{
    SET_KEYSCANREADY();
}

//--------------------------------------------------
// Description  : Key repeat enable timer event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CKeyRepeatEnableTimerEvent(void)
{
    SET_KEYREPEATSTART();
}

//--------------------------------------------------
// Description  : Key message translation
// Input Value  : ucKeyMask     --> Key mask
//                ucKeyMsg      --> Key message
// Output Value : None
//--------------------------------------------------
void CKeyMessageConvert(WORD ucKeyMask, BYTE ucKeyMsg)
{
    if((ucKeyStatePrev ^ ucKeyStateCurr) == ucKeyMask)
    {
        ucKeyMessage = ucKeyMsg;
    }
    else
    { 
        if(GET_KEYREPEATENABLE())
        {
            if(GET_KEYREPEATSTART())
            {
                ucKeyMessage = ucKeyMsg;
                //CLR_KEYREPEATSTART();
            }
            else
            {
                CTimerActiveTimerEvent(SEC(_KEY_REPEAT_START_TIME),CKeyRepeatEnableTimerEvent);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Power key process
// Input Value  : None
// Output Value : Return _TRUE if power key is pressed
//--------------------------------------------------
bit CKeyPowerKeyProc(void)
{
    if(ucKeyStateCurr == _POWER_KEY_MASK)
    {
        if((ucKeyStatePrev ^ ucKeyStateCurr) == _POWER_KEY_MASK)
        {
            CTimerDelayXms(25);
            ucKeyStateCurr = CKeyScan();
            
            if((ucKeyStatePrev ^ ucKeyStateCurr) == _POWER_KEY_MASK)
            {
                CKeyPowerKeyMix();
                SET_POWERSWITCH();
                return _TRUE;
            }
        }
    }
    
    return _FALSE;
}
//--------------------------------------------------
// Description  : We can add some settings here while combo key with power key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CKeyPowerKeyMix(void)
{
/*
    switch(ucKeyStateCurr)
    {

	default:
	    break;
    }
*/
}
//--------------------------------------------------
#if(_FUNC_EN_CHK_KEY_DOWN)
BYTE CheckKeyDown(BYTE KeyMask,BYTE Cnt)
{
    BYTE i = 0;
    while(i < Cnt)
    {
        if(CKeyScan() == KeyMask)
    	{
    	    return 1;
    	}
    	CTimerDelayXms(20);
    	i++;
    }
    return 0;
}
#endif
//--------------------------------------------------
#if(_FUNC_EN_CHK_KEY_UP)
BYTE CheckKeyUp(BYTE KeyMask,BYTE Cnt)
{
    BYTE i = 0;
    while(i < Cnt)
    {
        if(CKeyScan() != KeyMask)
    	{
    	    return 1;
    	}
    	CTimerDelayXms(20);
    	i++;
    }
    return 0;
}
#endif




#if(_KEY_SCAN_TYPE == _KEY_SCAN_AD)
//--------------------------------------------------
// Description  : Get key status
// Input Value  : None
// Output Value : Return Key status
//--------------------------------------------------
BYTE CGetADCAValue(BYTE Port)
{
	BYTE xdata *p;
    BYTE ucValue;

	MCU_ADC_ACONTROL_FF08 = 0x82;			//start adc convert(STRT_ADC_ACKT=1) 

	while(MCU_ADC_ACONTROL_FF08 & 0x80)
	{
		_nop_();
	}


	p = (0xFF09 + Port);			
	ucValue = *p;

	ucValue >>= 2;

	return ucValue;
    
}
#ifdef IRSEND_ENABLE
#if(_REMOTE_CONTROLLER == _IR_CF)
void IrProcessMessage(void)
{
            if (_GET_INPUT_SOURCE() != _SOURCE_VIDEO_TV)
             {
		  switch(ucKeyMessage)
		  {
       	//	case _IR_MENU_KEY_MESSAGE:					IR_Trans_Command(0xff00,0xF609); break;
       	//	case _MP5_CALLMENU_KEY_MESSAGE:			IR_Trans_Command(0xff00,0xF609); break;
       	//	case _MP5_MAINMENU_KEY_MESSAGE:  			IR_Trans_Command(0xff00,0xF609); break;
       		case _MP5_EXIT_KEY_MESSAGE:					IR_Trans_Command(0xff00,0xEF10); break;
       		case _MP5_FAST_PREV_KEY_MESSAGE:			IR_Trans_Command(0xff00,0xFB04); break;
       		case _MP5_FAST_NEXT_KEY_MESSAGE:			IR_Trans_Command(0xff00,0xF906); break;
       		case _MP5_PREV_KEY_MESSAGE:				IR_Trans_Command(0xff00,0xF30c); break;
       		case _MP5_NEXT_KEY_MESSAGE:				IR_Trans_Command(0xff00,0xF10E); break;
       		case _MP5_PLAY_KEY_MESSAGE:				IR_Trans_Command(0xff00,0xEE11); break;
       		case _MP5_LEFT_KEY_MESSAGE:					IR_Trans_Command(0xff00,0xF708); break;
       		case _MP5_RIGHT_KEY_MESSAGE:    				IR_Trans_Command(0xff00,0xFA0A); break;
       		case _MP5_UP_KEY_MESSAGE:					IR_Trans_Command(0xff00,0xFA05); break;
       		case _MP5_DOWN_KEY_MESSAGE:   				IR_Trans_Command(0xff00,0xF20D); break;
       		case _MP5_ENTER_KEY_MESSAGE:				IR_Trans_Command(0xff00,0xF609); break;
       		default:	break;
			
		}
             }
		else// for DMB
              {							
        		switch(ucKeyMessage)
        		{
        		case _MP5_EXIT_KEY_MESSAGE:					IR_Trans_Command(0x3085,0xE619); break;  // info
        		case _MP5_PREV_KEY_MESSAGE:				IR_Trans_Command(0x3085,0xE51A); break;	//mode
        		case _MP5_NEXT_KEY_MESSAGE:				IR_Trans_Command(0x3085,0xDC23); break;	//scan     //debug
        		case _MP5_PLAY_KEY_MESSAGE:				IR_Trans_Command(0x3085,0xDB24); break;	//menu  
        		case _MP5_LEFT_KEY_MESSAGE:					IR_Trans_Command(0x3085,0xED12); break;	
        		case _MP5_RIGHT_KEY_MESSAGE:    				IR_Trans_Command(0x3085,0xE11E); break;
        		case _MP5_UP_KEY_MESSAGE:					IR_Trans_Command(0x3085,0xD926); break;
        		case _MP5_DOWN_KEY_MESSAGE:   				IR_Trans_Command(0x3085,0xDD22); break;
        		case _MP5_ENTER_KEY_MESSAGE:				IR_Trans_Command(0x3085,0xE01F); break;
        		default:	break;
		}
                	}					
	//	ucKeyMessage = 0; // Reset IR command  
}
//--------------------------------------------------------------

#elif(_REMOTE_CONTROLLER == _IR_DMB)
void IrProcessMessage(void)
{
              if (_GET_INPUT_SOURCE() != _SOURCE_VIDEO_TV)
              {
          		switch(ucKeyMessage)
          		{
                 	      //case _IR_MENU_KEY_MESSAGE:				IR_Trans_Command(0xff00,0xF609); break;
                 	       //case _MP5_CALLMENU_KEY_MESSAGE:			IR_Trans_Command(0xff00,0xF609); break;
                 	       //case _MP5_MAINMENU_KEY_MESSAGE:  			IR_Trans_Command(0xff00,0xF609); break;
                 		case _MP5_EXIT_KEY_MESSAGE:					IR_Trans_Command(0xff00,0xEF10); break;
                 		case _MP5_FAST_PREV_KEY_MESSAGE:			IR_Trans_Command(0xff00,0xFB04); break;
                 		case _MP5_FAST_NEXT_KEY_MESSAGE:			IR_Trans_Command(0xff00,0xF906); break;
                 		case _MP5_PREV_KEY_MESSAGE:				IR_Trans_Command(0xff00,0xF30c); break;
                 		case _MP5_NEXT_KEY_MESSAGE:				IR_Trans_Command(0xff00,0xF10E); break;
                 		case _MP5_PLAY_KEY_MESSAGE:				IR_Trans_Command(0xff00,0xEE11); break;
                 		case _MP5_LEFT_KEY_MESSAGE:					IR_Trans_Command(0xff00,0xF708); break;
                 		case _MP5_RIGHT_KEY_MESSAGE:    				IR_Trans_Command(0xff00,0xFA0A); break;
                 		case _MP5_UP_KEY_MESSAGE:					IR_Trans_Command(0xff00,0xFA05); break;
                 		case _MP5_DOWN_KEY_MESSAGE:   				IR_Trans_Command(0xff00,0xF20D); break;
                 		case _MP5_ENTER_KEY_MESSAGE:				IR_Trans_Command(0xff00,0xF609); break;
                 		default:	break;			
		       }
             }
	     else // for DMB
             {	
       		switch(ucKeyMessage)
       		{
	                  //MP5+DMB
              		case _MP5_UP_KEY_MESSAGE:					IR_Trans_Command(0x3085,0xD926); break;
              		case _MP5_DOWN_KEY_MESSAGE:   				IR_Trans_Command(0x3085,0xDD22); break;
              		case _MP5_LEFT_KEY_MESSAGE:					IR_Trans_Command(0x3085,0xED12); break;	
              		case _MP5_RIGHT_KEY_MESSAGE:    				IR_Trans_Command(0x3085,0xE11E); break;
              		case _MP5_ENTER_KEY_MESSAGE:				IR_Trans_Command(0x3085,0xE01F); break;
			    //DMB
              		case _DMB_MODE_KEY:					       IR_Trans_Command(0x3085,0xE51A); break;//DMB/DAB
              		case _DMB_INFO_KEY:					              IR_Trans_Command(0x3085,0xE619); break;//INFO
              		//case _DMB_SCAN_KEY:					       IR_Trans_Command(0x3085,0xDC23); break;//Scan
              		case _DMB_MENU_KEY:					       IR_Trans_Command(0x3085,0xEE11); break;//Menu
              		default:	break;       			
       		}
            }					
	//	ucKeyMessage = 0; // Reset IR command  
}
//--------------------------------------------------------------
#endif
#endif
/*
WORD CGetADCBValue(BYTE Port)
{
	WORD usValue;
	MCU_ADC_BCONTROL_FF0E = 0x82;			//start adc convert(STRT_ADC_ACKT=1) 

	while(MCU_ADC_BCONTROL_FF0E & 0x80)
	{
		_nop_();
	}

	switch(Port)
	{
		case 0:
			usValue = ((WORD)ADC_B0H_convert_result_FF15 << 2) | ((ADC_BxL_convert_result_FF18 & 0xC0) >> 6);
			break;

		case 1:
			usValue = ((WORD)ADC_B1H_convert_result_FF16 << 2) | ((ADC_BxL_convert_result_FF18 & 0x30) >> 4);
			break;

		case 2:
			usValue = ((WORD)ADC_B2H_convert_result_FF17 << 2) | ((ADC_BxL_convert_result_FF18 & 0x0c) >> 2);
			break;
	}

	return usValue;
	
}
*/
/*
void CGetADCValue(BYTE *pBuf)
{
	BYTE xdata *p;
    BYTE i = 0;

	MCU_ADC_ACONTROL_FF08 = 0x82;			//start adc convert(STRT_ADC_ACKT=1) 

	while(MCU_ADC_ACONTROL_FF08 & 0x80)
	{
		_nop_();
	}

#if(AD_KEY0 != MCU_ADC_NONE)
	p = (0xFF09 + AD_KEY0);			
	pBuf[i] = *p;
    i++;
#endif

#if(AD_KEY1 != MCU_ADC_NONE)
	p = (0xFF09 + AD_KEY1);			
	pBuf[i] = *p;
    i++;
#endif

#if(AD_KEY2 != MCU_ADC_NONE)
	p = (0xFF09 + AD_KEY2);			
	pBuf[i] = *p;
    i++;
#endif

#if(AD_KEY3 != MCU_ADC_NONE)
	p = (0xFF09 + AD_KEY3);			
	pBuf[i] = *p;
    i++;
#endif

#if(AD_KEY4 != MCU_ADC_NONE)
	p = (0xFF09 + AD_KEY4);			
	pBuf[i] = *p;
#endif

	pBuf[0] >>= 2;
	pBuf[1] >>= 2;
	pBuf[2] >>= 2;
	pBuf[3] >>= 2;
	pBuf[4] >>= 2;
}  */
#endif
