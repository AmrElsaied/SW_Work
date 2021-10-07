/*******************************************************************************************/
/*  Author      : Amr Mohamed                                                              */
/*  Date        : 12 Sep 2019                                                               */
/*  Version     : 1.0 V                                                                    */
/*******************************************************************************************/



#ifndef PWM_PRIVATE_H_
#define PWM_PRIVATE_H_

#define TCCR0   (*((volatile unsigned char*)0x53))
#define OCR0   	(*((volatile unsigned char*)0x5C))

#define DDRB	(*((volatile unsigned char*)0x37))

#define FAST_PWM	0
#define PHASE_CORRECT_PWM	1



#define PRESCALER_1                                1U
#define PRESCALER_8                                8U
#define PRESCALER_64                               64U
#define PRESCALER_256                              256U
#define PRESCALER_1024                             1024U


#define PWM_DISCONNECT_OC0                      1
#define PWM_CLEAR_OC0                           2
#define PWM_SET_OC0                         	3


#endif /* PWM_PRIVATE_H_ */
