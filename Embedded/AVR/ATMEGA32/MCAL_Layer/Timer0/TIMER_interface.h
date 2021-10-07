/*******************************************************************************************/
/*  Author      : Amr Mohamed                                                              */
/*  Date        : 8 Sep 2019                                                               */
/*  Version     : 1.0 V                                                                    */
/*******************************************************************************************/

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#include "STD_TYPeS.h"
/*
 * To Start Timer0
 * Check TIMER_config.h File First to configure Settings of Timer0
 */
void TIMER_voidStartTimer();

/*
 * To Select The Start Value of TCCN0
 * Copy_u8StartTime 	:	0 --->255
 */
void TIMER_voidSetTimerStart(u8 Copy_u8StartTime);
/*
 * To Select The CallBcak Function when Timer0 Overflow
 * Local_OV_ISR 	:	Put the name of Function
 */
void TIMER_voidSetOverFlow_ISR(void (*Local_OV_ISR)(void));
/*
 * To Select The CallBcak Function when Timer0 compare match successfully
 * Local_COMP_ISR 	:	Put the name of Function
 */
void TIMER_voidSetCompareMatch_ISR(void (*Local_COMP_ISR)(void));
/*
 * To Select The Value of OCR
 * Copy_u8StartTime 	:	0 --->255
 */
void TIMER_voidLoad_OCR(u8 Copy_u8EndTime);

#endif /* TIMER_INTERFACE_H_ */
