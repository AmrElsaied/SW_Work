/*******************************************************************************************/
/*  Author      : Amr Mohamed                                                              */
/*  Date        : 12 Sep 2019                                                               */
/*  Version     : 1.0 V                                                                    */
/*******************************************************************************************/
#include	"PWM_interface.h"
#include	"PWM_private.h"
#include	"PWM_config.h"
#include	"BIT_MATH.h"
void PWM0_voidInit()
{
#if (PWM0_MODE == FAST_PWM)
	SET_BIT(TCCR0,3);
	SET_BIT(TCCR0,6);
#else

#endif


#if (PWM0_PRESCALER == PRESCALER_1)
    SET_BIT(TCCR0, 0);
    CLR_BIT(TCCR0, 1);
    CLR_BIT(TCCR0, 2);
#elif (PWM0_PRESCALER == PRESCALER_8)
    CLR_BIT(TCCR0, 0);
    SET_BIT(TCCR0, 1);
    CLR_BIT(TCCR0, 2);
#elif (PWM0_PRESCALER == PRESCALER_64)
    SET_BIT(TCCR0, 0);
    SET_BIT(TCCR0, 1);
    CLR_BIT(TCCR0, 2);
#elif (PWM0_PRESCALER == PRESCALER_256)
    CLR_BIT(TCCR0, 0);
    CLR_BIT(TCCR0, 1);
    SET_BIT(TCCR0, 2);
#elif (PWM0_PRESCALER == PRESCALER_1024)
    SET_BIT(TCCR0, 0);
    CLR_BIT(TCCR0, 1);
    SET_BIT(TCCR0, 2);
#endif


#if (PWM0_OC_MODE == PWM_DISCONNECT_OC0)
	CLR_BIT(TCCR0,4);
	CLR_BIT(TCCR0,5);
#elif(PWM0_OC_MODE == PWM_CLEAR_OC0)
	CLR_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
	SET_BIT(DDRB,3);
#else
	SET_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
	SET_BIT(DDRB,3);
#endif
}

void PWM0_voidSetDutyCycle(u8 Copy_u8DutyCycle)
{
	OCR0 = Copy_u8DutyCycle;
}

