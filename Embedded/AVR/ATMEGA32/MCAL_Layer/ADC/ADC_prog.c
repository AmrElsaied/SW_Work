/*******************************************************************************************/
/*  Author      : Amr Mohamed                                                              */
/*  Date        : 6 Sep 2019                                                               */
/*  Version     : 1.0 V                                                                    */
/*******************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ADC_private.h"
#include "ADC_config.h"
#include <avr/interrupt.h>

u16 ADC_Value=0;

void ADC_CalculateValue()
{
	u8 Temp_ADCL = ADCL;
	ADC_Value = ADCH;
	ADC_Value <<=8;
	ADC_Value |= Temp_ADCL;
}

void ADC_voidInit()
{
#if (VREF == AREF_PIN)
    CLR_BIT(ADMUX, REFS0);
    CLR_BIT(ADMUX, REFS1);
#elif (VREF == AVCC_PIN)
    SET_BIT(ADMUX, REFS0);
    CLR_BIT(ADMUX, REFS1);
#elif (VREF == INTERNAL_VREF)
    SET_BIT(ADMUX, REFS0);
    SET_BIT(ADMUX, REFS1);
#endif

    /*** Set Input Channel ***/

    CLR_BIT(ADMUX, MUX4);
    CLR_BIT(ADMUX, MUX3);

    #if (INPUT_CHANNEL == ADC0_CH)
        CLR_BIT(ADMUX, MUX2);
        CLR_BIT(ADMUX, MUX1);
        CLR_BIT(ADMUX, MUX0);
    #elif (INPUT_CHANNEL == ADC1_CH)
        CLR_BIT(ADMUX, MUX2);
        CLR_BIT(ADMUX, MUX1);
        SET_BIT(ADMUX, MUX0);
    #elif (INPUT_CHANNEL == ADC2_CH)
        CLR_BIT(ADMUX, MUX2);
        SET_BIT(ADMUX, MUX1);
        CLR_BIT(ADMUX, MUX0);
    #elif (INPUT_CHANNEL == ADC3_CH)
        CLR_BIT(ADMUX, MUX2);
        SET_BIT(ADMUX, MUX1);
        SET_BIT(ADMUX, MUX0);
    #elif (INPUT_CHANNEL == ADC4_CH)
        SET_BIT(ADMUX, MUX2);
        CLR_BIT(ADMUX, MUX1);
        CLR_BIT(ADMUX, MUX0);
    #elif (INPUT_CHANNEL == ADC5_CH)
        SET_BIT(ADMUX, MUX2);
        CLR_BIT(ADMUX, MUX1);
        SET_BIT(ADMUX, MUX0);
    #elif (INPUT_CHANNEL == ADC6_CH)
        SET_BIT(ADMUX, MUX2);
        SET_BIT(ADMUX, MUX1);
        CLR_BIT(ADMUX, MUX0);
    #elif (INPUT_CHANNEL == ADC7_CH)
        SET_BIT(ADMUX, MUX2);
        SET_BIT(ADMUX, MUX1);
        SET_BIT(ADMUX, MUX0);
    #endif

    CLR_BIT(ADMUX, ADLAR); // Use Right Adjusted

    /*** Configure control and status register ***/
     SET_BIT(ADCSRA, ADEN);
     CLR_BIT(ADCSRA, ADSC);
     SET_BIT(ADCSRA, ADPS0);
     SET_BIT(ADCSRA, ADPS1);
     SET_BIT(ADCSRA, ADPS2);

     SET_BIT(ADCSRA, ADIF);
     SET_BIT(SREG, 7);
     SET_BIT(ADCSRA, ADIE);

     SET_BIT(ADCSRA, ADATE);
     CLR_BIT(SFIOR,ADTS0);
     CLR_BIT(SFIOR,ADTS1);
     CLR_BIT(SFIOR,ADTS2);


}

void ADC_voidStartConversion(void)
{
    SET_BIT(ADCSRA, ADSC);
}

ISR(ADC_vect)
{
    ADC_CalculateValue();
}

u16 ADC_u16GetData(void)
{
    return (ADC_Value);
}


