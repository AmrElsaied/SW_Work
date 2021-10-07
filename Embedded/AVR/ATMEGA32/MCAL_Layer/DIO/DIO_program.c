/*******************************************************************************************/
/*  Author      : Amr Mohamed                                                              */
/*  Date        : 3 Sep 2019                                                               */
/*  Version     : 1.0 V                                                                    */
/*******************************************************************************************/
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "BIT_MATH.h"

void DIO_voidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction) {
	switch (Copy_u8Port) {
	case PRTA:
		if (Copy_u8Direction == OUTPUT) {
			SET_BIT(DDRA, Copy_u8Pin);
		} else {
			CLR_BIT(DDRA, Copy_u8Pin);
		}
		break;
	case PRTB:

		if (Copy_u8Direction == OUTPUT) {
			SET_BIT(DDRB, Copy_u8Pin);
		} else {
			CLR_BIT(DDRB, Copy_u8Pin);
		}
		break;
	case PRTC:

		if (Copy_u8Direction == OUTPUT) {
			SET_BIT(DDRC, Copy_u8Pin);
		} else {
			CLR_BIT(DDRC, Copy_u8Pin);
		}
		break;

	case PRTD:
		if (Copy_u8Direction == OUTPUT) {
			SET_BIT(DDRD, Copy_u8Pin);
		} else {
			CLR_BIT(DDRD, Copy_u8Pin);
		}
		break;
	default:
		//INVALID PORT PINA0 WILL OUTPUT HIGH
		SET_BIT(DDRA, 0);
		SET_BIT(PORTA, 0);
		break;
	}
}

void DIO_voidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value) {
	switch (Copy_u8Port) {
	case PRTA:

		if (Copy_u8Value == HIGH) {
			SET_BIT(PORTA, Copy_u8Pin);
		} else {
			CLR_BIT(PORTA, Copy_u8Pin);
		}
		break;

	case PRTB:

		if (Copy_u8Value == HIGH) {
			SET_BIT(PORTA, Copy_u8Pin);
		} else {
			CLR_BIT(PORTA, Copy_u8Pin);
		}
		break;

	case PRTC:

		if (Copy_u8Value == HIGH) {
			SET_BIT(PORTA, Copy_u8Pin);
		} else {
			CLR_BIT(PORTA, Copy_u8Pin);
		}
		break;
	case PRTD:
		if (Copy_u8Value == HIGH) {
			SET_BIT(PORTA, Copy_u8Pin);
		} else {
			CLR_BIT(PORTA, Copy_u8Pin);
		}
		break;
	default:
		//INVALID PORT PINA0 WILL OUTPUT HIGH
		SET_BIT(DDRA, 0);
		SET_BIT(PORTA, 0);
		break;
	}
}

u8 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin) {
	u8 RetVal = 0;
	switch (Copy_u8Port) {
	case PRTA:
		CLR_BIT(DDRA, Copy_u8Pin);
		RetVal = GET_BIT(PINA, Copy_u8Pin);
		break;

	case PRTB:
		CLR_BIT(DDRB, Copy_u8Pin);
		RetVal = GET_BIT(PINB, Copy_u8Pin);
		break;

	case PRTC:
		CLR_BIT(DDRC, Copy_u8Pin);
		RetVal = GET_BIT(PINC, Copy_u8Pin);
		break;

	case PRTD:
		CLR_BIT(DDRD, Copy_u8Pin);
		RetVal = GET_BIT(PIND, Copy_u8Pin);
		break;

	default:
		//INVALID PORT PINA0 WILL OUTPUT HIGH
		SET_BIT(DDRA, 0);
		SET_BIT(PORTA, 0);
		break;
	}
	return RetVal;
}
void DIO_voidSetPinPullUP(u8 Copy_u8Port, u8 Copy_u8Pin) {
	CLR_BIT(SFIOR, 2);
	switch(Copy_u8Port)
	{
	case PRTA:
	CLR_BIT(DDRA, Copy_u8Pin);
	SET_BIT(PORTA, Copy_u8Pin);
	break;

	case PRTB:
	CLR_BIT(DDRB, Copy_u8Pin);
	SET_BIT(PORTB, Copy_u8Pin);
	break;

	case PRTC:
	CLR_BIT(DDRC, Copy_u8Pin);
	SET_BIT(PORTC, Copy_u8Pin);
	break;

	case PRTD:
	CLR_BIT(DDRD, Copy_u8Pin);
	SET_BIT(PORTD, Copy_u8Pin);
	break;

	default:
	//INVALID PORT PINA0 WILL OUTPUT HIGH
	SET_BIT(DDRA, 0);
	SET_BIT(PORTA, 0);
	break;
	}

}
