/*******************************************************************************************/
/*  Author      : Amr Mohamed                                                              */
/*  Date        : 3 Sep 2019                                                               */
/*  Version     : 1.0 V                                                                    */
/*******************************************************************************************/


#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

#include "DIO_private.h"

/*
 * To determine the direction or mode of the pin
 * Copy_u8Port		:	PRTA, PRTB, PRTC, PRTD
 * Copy_u8Pin		:	0,................,7
 * Copy_u8Direction	:	OUTPUT, INPUT
 */
void DIO_voidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction);

/*
 * To determine the Value of the an OUTPUT Pin
 * Copy_u8Port		:	PRTA, PRTB, PRTC, PRTD
 * Copy_u8Pin		:	0,................,7
 * Copy_u8Value		:	HIGH, LOW
 */

void DIO_voidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value);

/*
 * To The chosen pin INPUT with Internal PULLUP
 * Copy_u8Port		:	PRTA, PRTB, PRTC, PRTD
 * Copy_u8Pin		:	0,................,7
 * Copy_u8Value		:	HIGH, LOW
 */
void DIO_voidSetPinPullUP(u8 Copy_u8Port, u8 Copy_u8Pin);

/*
 * To Get the value on an input pin
 * Copy_u8Port		:	PRTA, PRTB, PRTC, PRTD
 * Copy_u8Pin		:	0,................,7
 */
u8 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin);



#endif
