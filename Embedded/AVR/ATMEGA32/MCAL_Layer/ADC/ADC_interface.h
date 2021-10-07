/*******************************************************************************************/
/*  Author      : Amr Mohamed                                                              */
/*  Date        : 6 Sep 2019                                                               */
/*  Version     : 1.0 V                                                                    */
/*******************************************************************************************/


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include "STD_TYPES.h"

/*
 * To Initialize the ADC for a specific channel
 */

void ADC_voidInit();
/*
 * To Start the conversion and this function is used
 * for one time at the beginning
 */
void ADC_voidStartConversion();

/*
 * To get the output of the conversion
 */
u16 ADC_u16GetData();

#endif /* ADC_INTERFACE_H_ */
