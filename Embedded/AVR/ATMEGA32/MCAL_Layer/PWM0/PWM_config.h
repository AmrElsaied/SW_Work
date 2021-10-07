/*******************************************************************************************/
/*  Author      : Amr Mohamed                                                              */
/*  Date        : 12 Sep 2019                                                               */
/*  Version     : 1.0 V                                                                    */
/*******************************************************************************************/


#ifndef PWM_CONFIG_H_
#define PWM_CONFIG_H_

/*
 * Modes of PWM:
 *					FAST_PWM
 *					PHASE_CORRECT_PWM
 *	Available Mode:
 *					FAST_PWM
 */
#define PWM0_MODE				FAST_PWM

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

#define PWM0_PRESCALER			PRESCALER_1
/*
 * choose the mode of output compare
 * Available Modes:
 * 					PWM_DISCONNECT_OC0
 * 					PWM_CLEAR_OC0
 * 					PWM_SET_OC0
 */
#define PWM0_OC_MODE			PWM_SET_OC0


#endif /* PWM_CONFIG_H_ */
