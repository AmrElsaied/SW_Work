/*******************************************************************************************/
/*  Author      : Amr Mohamed                                                              */
/*  Date        : 5 Sep 2019                                                               */
/*  Version     : 1.0 V                                                                    */
/*******************************************************************************************/



#ifndef EXTINT_INTERFACE_H_
#define EXTINT_INTERFACE_H_

#include "EXTINT_priv.h"
/*
 * To initiate the external interrupt
 * INTNUM			:	INTR0, INTR1, INTR2
 */
void EXTINT_voidIntInit(u8 INTNUM);
/*
 * To Set ISR of an external interrupt
 * INTNUM			:	INTR0, INTR1, INTR2
 *
 * Local_ISR		: pass the target function
 * void LedState()
 * {
 * ........
 * }
 * EXTINT_voidIntSetIsr(LedState);
 *
 */
void EXTINT_voidIntSetIsr(u8 INT,void (*Local_ISR)(void));



#endif /* EXTINT_INTERFACE_H_ */
