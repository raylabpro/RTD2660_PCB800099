/*=============================================
  * Copyright (c)      Realtek Semiconductor Corporation, 2005
  * All rights reserved.
  * ============================================ */

/*================= File Description ================= */
/**
 * @file
 * 	This file is for time function-structure's declaration.
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

#ifndef  _TIME_H
#define  _TIME_H
/*===================== Module Dependency  ================== */

/*========================== Types ========================== */

/*======================== Definitions ====================== */
#define _MAX_EVENT_AMOUNT           8
#define _INACTIVE_TIMER_EVENT       0xFFFF
#define _INACTIVE_COUNTDOWN_EVENT   0xFF

/*=====================  Extern Variables =================== */
#ifdef _TIME_C
    #define EXTERN
#else
    #define EXTERN   extern
#endif

EXTERN bit bNotifyTimer0Int;
EXTERN bit bTimer0Ctrl;

#undef EXTERN

/*======================= Extern Functions ================== */
void CTimerHandler(void);
void CTimerActiveTimerEvent(WORD usTime, void (*Event)());
void CTimerReactiveTimerEvent(WORD usTime, void (*Event)());
void CTimerCancelTimerEvent(void (*Event)());
void CTimerInitialTimerEvent(void);
void CTimerDecreaseTimerCnt(void);
void CTimerCountDownEventProc(BYTE *pEventCnt, BYTE ucWaitCnt, void (*Event)(void));
bit CTimerPollingEventProc(BYTE ucTimeout, bit (*Event)(void));
void CTimerDelayXms(WORD usNum);
bit CTimerWaitForEvent(BYTE ucEvent);


#endif 
