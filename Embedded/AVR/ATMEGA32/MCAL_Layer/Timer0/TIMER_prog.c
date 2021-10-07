/*******************************************************************************************/
/*  Author      : Amr Mohamed                                                              */
/*  Date        : 8 Sep 2019                                                               */
/*  Version     : 1.0 V                                                                    */
/*******************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER_interface.h"
#include "TIMER_config.h"
#include "TIMER_private.h"
#include <avr/interrupt.h>
void (*OVF_ISR)(void)  = '\0';
void (*COMP_ISR)(void) = '\0';

u8 StartTime=0;
u8 EndTime=0;
void TIMER_voidStartTimer()
{
#if (TIMER_MODE == MODE_NORMAL)
	CLR_BIT(TCCR0,3);
	CLR_BIT(TCCR0,6);
#if (TIMER_OC_MODE == TIMER_NON_PWM_DISCONNECT_OC0)
	CLR_BIT(TCCR0,4);
	CLR_BIT(TCCR0,5);
#elif(TIMER_OC_MODE == TIMER_NON_PWM_TOGGLE_OC0)
	SET_BIT(TCCR0,4);
	CLR_BIT(TCCR0,5);
#elif(TIMER_OC_MODE == TIMER_NON_PWM_CLEAR_OC0)
	CLR_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#else
	SET_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#endif
#elif(TIMER_MODE == MODE_PWM_PHASECORRECT)

#elif(TIMER_MODE == MODE_CTC)
	SET_BIT(TCCR0,3);
	CLR_BIT(TCCR0,6);
#if (TIMER_OC_MODE == TIMER_NON_PWM_DISCONNECT_OC0)
	CLR_BIT(TCCR0,4);
	CLR_BIT(TCCR0,5);
#elif(TIMER_OC_MODE == TIMER_NON_PWM_TOGGLE_OC0)
	SET_BIT(TCCR0,4);
	CLR_BIT(TCCR0,5);
#elif(TIMER_OC_MODE == TIMER_NON_PWM_CLEAR_OC0)
	CLR_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#else
	SET_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);
#endif
#else

#endif

    /*** CLOCK SELECT ***/
    #if (TIMER_PRESCALER == PRESCALER_1)
        SET_BIT(TCCR0, 0);
        CLR_BIT(TCCR0, 1);
        CLR_BIT(TCCR0, 2);
    #elif (TIMER_PRESCALER == PRESCALER_8)
        CLR_BIT(TCCR0, 0);
        SET_BIT(TCCR0, 1);
        CLR_BIT(TCCR0, 2);
    #elif (TIMER_PRESCALER == PRESCALER_64)
        SET_BIT(TCCR0, 0);
        SET_BIT(TCCR0, 1);
        CLR_BIT(TCCR0, 2);
    #elif (TIMER_PRESCALER == PRESCALER_256)
        CLR_BIT(TCCR0, 0);
        CLR_BIT(TCCR0, 1);
        SET_BIT(TCCR0, 2);
    #elif (TIMER_PRESCALER == PRESCALER_1024)
        SET_BIT(TCCR0, 0);
        CLR_BIT(TCCR0, 1);
        SET_BIT(TCCR0, 2);
    #endif

        /*** Enable the interrupts ***/
    	SET_BIT(TIMSK, 0);
        SET_BIT(SREG,7);
}

void TIMER_voidSetTimerStart(u8 Copy_u8StartTime)
{
	StartTime = Copy_u8StartTime;
	TCNT0 = StartTime;
}

void TIMER_voidLoad_OCR(u8 Copy_u8EndTime)
{
	OCR0 = Copy_u8EndTime;
}

void TIMER_voidSetOverFlow_ISR(void (*Local_OV_ISR)(void))
{
    OVF_ISR = Local_OV_ISR;
}

void TIMER_voidSetCompareMatch_ISR(void (*Local_COMP_ISR)(void))
{
	COMP_ISR = Local_COMP_ISR;
}

ISR(TIMER0_OVF_vect)
{
	TCNT0 = StartTime;
    OVF_ISR();
}

ISR(TIMER0_COMP_vect)
{
	TCNT0 = StartTime;
    COMP_ISR();
}
