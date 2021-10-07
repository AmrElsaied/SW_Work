/*******************************************************************************************/
/*  Author      : Amr Mohamed                                                              */
/*  Date        : 8 Sep 2019                                                               */
/*  Version     : 1.0 V                                                                    */
/*******************************************************************************************/


#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#define TCCR0   (*((volatile unsigned char*)0x53))
#define TCNT0  	(*((volatile unsigned char*)0x52))
#define OCR0   	(*((volatile unsigned char*)0x5C))
#define TIMSK   (*((volatile unsigned char*)0x59))
#define TIFR   	(*((volatile unsigned char*)0x58))

#define SREG    (*((volatile unsigned char*)0x5F))


#define MODE_NORMAL					0
#define MODE_PWM_PHASECORRECT		1
#define MODE_CTC					2
#define MODE_PWM_FAST				3


#define PRESCALER_1                                1U
#define PRESCALER_8                                8U
#define PRESCALER_64                               64U
#define PRESCALER_256                              256U
#define PRESCALER_1024                             1024U


#define TIMER_NON_PWM_DISCONNECT_OC0                      1
#define TIMER_NON_PWM_TOGGLE_OC0                          2
#define TIMER_NON_PWM_CLEAR_OC0                           3
#define TIMER_NON_PWM_SET_OC0                             4


#endif /* TIMER_PRIVATE_H_ */
