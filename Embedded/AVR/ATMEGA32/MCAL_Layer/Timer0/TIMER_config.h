/*******************************************************************************************/
/*  Author      : Amr Mohamed                                                              */
/*  Date        : 8 Sep 2019                                                               */
/*  Version     : 1.0 V                                                                    */
/*******************************************************************************************/


#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

/*
 * Modes of TIMER:
 *					MODE_NORMAL
 *					MODE_PWM_PHASECORRECT
 *					MODE_CTC
 *					MODE_PWM_FAST
 *	Available Mode:
 *					MODE_NORMAL - MODE_CTC
 */
#define TIMER_MODE				MODE_NORMAL
/*
 * To prescale the frequency of ATMEGA32
 * Clk/Prescaler
 * Available values:
 * 					PRESCALER_1
 * 					PRESCALER_8
 * 					PRESCALER_64
 * 					PRESCALER_256
 * 					PRESCALER_1024
 */
#define TIMER_PRESCALER			PRESCALER_1024
/*
 * choose the mode of output compare
 * Available Modes:
 * 					TIMER_NON_PWM_DISCONNECT_OC0
 * 					TIMER_NON_PWM_TOGGLE_OC0
 * 					TIMER_NON_PWM_CLEAR_OC0
 * 					TIMER_NON_PWM_SET_OC0
 */
#define TIMER_OC_MODE			TIMER_NON_PWM_DISCONNECT_OC0
#endif /* TIMER_CONFIG_H_ */
