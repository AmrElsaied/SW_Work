/*******************************************************************************************/
/*  Author      : Amr Mohamed                                                              */
/*  Date        : 12 Sep 2019                                                               */
/*  Version     : 1.0 V                                                                    */
/*******************************************************************************************/


#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_
#include "STD_TYPES.h"

/*
 * To Initialize PWM0
 * Check PWM_config.h File First to configure Settings of PWM0
 */

void PWM0_voidInit();

/*
 * To Set DutyCycle of PWM0
 * Copy_u8DutyCycle : from 0 to 255
 */

void PWM0_voidSetDutyCycle(u8 Copy_u8DutyCycle);

#endif /* PWM_INTERFACE_H_ */
