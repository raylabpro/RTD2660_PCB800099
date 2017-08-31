/*=============================================
  * Copyright (c)      Realtek Semiconductor Corporation, 2005
  * All rights reserved.
  * ============================================ */

/*================= File Description ================= */
/**
 * @file
 * 	This file is for global structure's declaration.
 *
 * @author 	$Author: kingee $
 * @date 	$Date: 2006-06-09 11:09:32 +0800 (?Ÿæ?äº? 09 ?­æ? 2006) $
 * @version 	$Revision: 872 $
 * @ingroup 	timer
 */

/**
* @addtogroup timer
* @{
*/

/*===================== Module dependency  ================== */
#include "Core\Header\Include.h"

/*======================= Private Types ===================== */

/*======================== Definitions ====================== */

/*========================== Variables ====================== */
struct CTimerEventTable idata TimerEvent[_MAX_EVENT_AMOUNT];		//idata
bit bNotifyTimer0Int;
bit bTimer0Ctrl;

/*=================== Local Functions Phototype ==============*/

/*=========================== Functions ===================== */
/**
 * CTimerHandler
 * Check if  any event is time up to execute
 * @param <none>
 * @return {none}
 *
*/
void CTimerHandler(void)
{
	BYTE timereventcnt;

	for(timereventcnt=0;timereventcnt<_MAX_EVENT_AMOUNT;timereventcnt++) 
	{
		if(TimerEvent[timereventcnt].Time == 0) 
		{
			bTimer0Ctrl = _TRUE;
			TimerEvent[timereventcnt].Time = _INACTIVE_TIMER_EVENT;
			bTimer0Ctrl = _FALSE;
			(*TimerEvent[timereventcnt].Event)();
		}

	}
}

//--------------------------------------------------
// Description  : Set up a timer for an event. If the event is exist,
//                this function is ignored and do not change the executing time.
// Input Value  : usTime    --> Unit in 10ms, range in 0.01 ~ 655.3 sec
//                Event     --> Execute Event while timeup
// Output Value : None
//--------------------------------------------------
void CTimerActiveTimerEvent(WORD usTime, void (*Event)())
{
    BYTE timereventcnt;

    for(timereventcnt=0;timereventcnt<_MAX_EVENT_AMOUNT;timereventcnt++)
    {
        if((TimerEvent[timereventcnt].Time != _INACTIVE_TIMER_EVENT) && (TimerEvent[timereventcnt].Event == Event))
            return;
    }
    
    for(timereventcnt=0;timereventcnt<_MAX_EVENT_AMOUNT;timereventcnt++)
    {
        if(TimerEvent[timereventcnt].Time == _INACTIVE_TIMER_EVENT)
        {
            bTimer0Ctrl = _TRUE;
            TimerEvent[timereventcnt].Time = usTime;
            bTimer0Ctrl = _FALSE;
            TimerEvent[timereventcnt].Event = Event;
            break;
        }
    }
}

//--------------------------------------------------
// Description  : Reactive a timer for an event. If the event is exist,
//                this function will reset the executing time and restart.
// Input Value  : usTime    --> Unit in 10ms, range in 0.01 ~ 655.3 sec
//                Event     --> Execute Event while timeup
// Output Value : None
//--------------------------------------------------
void CTimerReactiveTimerEvent(WORD usTime, void (*Event)())
{
    BYTE timereventcnt;

    for(timereventcnt=0;timereventcnt<_MAX_EVENT_AMOUNT;timereventcnt++)
    {
        if((TimerEvent[timereventcnt].Time != _INACTIVE_TIMER_EVENT) && (TimerEvent[timereventcnt].Event == Event))
        {
            bTimer0Ctrl = _TRUE;
            TimerEvent[timereventcnt].Time = usTime;
            bTimer0Ctrl = _FALSE;
            return;
        }
    }
    CTimerActiveTimerEvent(usTime, Event);
}

//--------------------------------------------------
// Description  : Cancel an event
// Input Value  : Event     --> Event which we want to cancel
// Output Value : None
//--------------------------------------------------
void CTimerCancelTimerEvent(void (*Event)())
{
    BYTE timereventcnt;

    for(timereventcnt=0;timereventcnt<_MAX_EVENT_AMOUNT;timereventcnt++)
    {
        if(TimerEvent[timereventcnt].Event == Event)
        {
            bTimer0Ctrl = _TRUE;
            TimerEvent[timereventcnt].Time = _INACTIVE_TIMER_EVENT;
            bTimer0Ctrl = _FALSE;
        }
    }
}




/**
 * CTimerInitialTimerEvent
 * Initial timer and events for once when power up
 * @param <none>
 * @return {none}
 *
 */
//--------------------------------------------------
// Description  : Initial timer and events. We have to run this function at firmware startup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CTimerInitialTimerEvent(void)
{
    BYTE timereventcnt;

    for (timereventcnt = 0; timereventcnt < _MAX_EVENT_AMOUNT; timereventcnt ++)
    {
    	TimerEvent[timereventcnt].Time = _INACTIVE_TIMER_EVENT;
    }
    TR0 = 1;
}

//--------------------------------------------------
// Description  : Decrease timer counts while 10ms Interrupt is up
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CTimerDecreaseTimerCnt(void)
{
    BYTE timerdeccnt;

    for(timerdeccnt=0;timerdeccnt<_MAX_EVENT_AMOUNT;timerdeccnt++)
    {
        if((TimerEvent[timerdeccnt].Time != _INACTIVE_TIMER_EVENT) && (TimerEvent[timerdeccnt].Time != 0))
        {
            TimerEvent[timerdeccnt].Time--;
        }
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : Count down event process
// Input Value  : pEventCnt --> Event counter
//                ucWaitCnt --> Count down number (Max: 254)
//                Event     --> Execute Event while counter is zero
// Output Value : None
//----------------------------------------------------------------------------------------------------
void CTimerCountDownEventProc(BYTE *pEventCnt, BYTE ucWaitCnt, void (*Event)(void))
{
    if(*pEventCnt == _INACTIVE_COUNTDOWN_EVENT)
    {
        *pEventCnt = ucWaitCnt;
    }
    else if(*pEventCnt == 0)
    {
        *pEventCnt = _INACTIVE_COUNTDOWN_EVENT;
        Event();
    }
    else
    {
        *pEventCnt = *pEventCnt - 1;
    }
}

/**
 * CTimerPollingEventProc
 * Polling Event Process
 * @param <ucTimeout --> Timeout number (Max: 255 ms)>
 * @param <Event     --> Polling event. This event has to return _TRUE or _FALSE>
 * @return {_TRUE while polling success, _FALSE for timeout}
 *
*/
bit CTimerPollingEventProc(BYTE ucTimeout, bit (*Event)(void)) 
{
	BYTE data temp;

	temp = ucTimeout;
	do
    	{
        	CTimerDelayXms(1);
        	if(Event())
        	{
            		return _TRUE;
        	}
       }
    while(--temp);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Hold program for 0 ~ 65535 ms
// Input Value  : usNum     --> Delay time
// Output Value : None
//--------------------------------------------------
void CTimerDelayXms(WORD usNum)
{
    if(usNum)
    {
        bNotifyTimer0Int = _FALSE;
        while(_TRUE)
        {
            if(bNotifyTimer0Int)
            {
                bNotifyTimer0Int = _FALSE;
                if(--usNum)
                    TR0 = _ON;
                else
                    return;
            }
        }
    }
}

/**
* CTimerWaitForEvent
* Wait event occur or timeout
* @param <ucEvent> {Event of status1 register}
* @return {_FALSE if event occur, _TRUE if timeout}
*
*/
bit CTimerWaitForEvent(BYTE ucEvent)
{
    BYTE temp;
    BYTE timeoutcnt = 30;                   // 30ms timeout

    CScalerSetByte(_STATUS1_03, 0x00);      // Clear status (status register will be cleared after write)

    bNotifyTimer0Int = _FALSE;

    do
    {
        if(bNotifyTimer0Int)
        {
            bNotifyTimer0Int  = _FALSE;
            if(--timeoutcnt)
                TR0 = _ON;
        }
        CScalerRead(_STATUS1_03, 1, &temp, _NON_AUTOINC);
        temp &= ucEvent;
    }
    while((temp == 0) && (timeoutcnt != 0));

    return timeoutcnt ? _FALSE : _TRUE;
}

