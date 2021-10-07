/*******************************************************************************************/
/*  Author      : Amr Mohamed                                                              */
/*  Date        : 6 Sep 2019                                                               */
/*  Version     : 1.0 V                                                                    */
/*******************************************************************************************/


#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define ADMUX   (*((volatile unsigned char*)0x27))
#define ADCSRA  (*((volatile unsigned char*)0x26))
#define ADCH   	(*((volatile unsigned char*)0x25))
#define ADCL    (*((volatile unsigned char*)0x24))
#define SREG    (*((volatile unsigned char*)0x5F))
#define SFIOR   (*((volatile unsigned char*)0x50))

#define AREF_PIN        0
#define AVCC_PIN        1
#define INTERNAL_VREF   3

#define REFS0	6
#define REFS1	7
#define ADLAR	5
#define MUX4	4
#define MUX3	3
#define MUX2	2
#define MUX1	1
#define MUX0	0

#define ADC0_CH         4
#define ADC1_CH         5
#define ADC2_CH         6
#define ADC3_CH         7
#define ADC4_CH         8
#define ADC5_CH         9
#define ADC6_CH         10
#define ADC7_CH         11


#define ADEN	7
#define ADSC	6
#define ADATE	5
#define ADIF	4
#define ADIE	3
#define ADPS2	2
#define ADPS1	1
#define ADPS0	0

#define ADTS0	5
#define ADTS1	6
#define ADTS2	7

#endif /* ADC_PRIVATE_H_ */
