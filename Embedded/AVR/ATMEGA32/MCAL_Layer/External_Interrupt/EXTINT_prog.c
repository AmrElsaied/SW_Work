/*******************************************************************************************/
/*  Author      : Amr Mohamed                                                              */
/*  Date        : 5 Sep 2019                                                               */
/*  Version     : 1.0 V                                                                    */
/*******************************************************************************************/
#include "STD_TYPES.h"
#include"BIT_MATH.h"
#include "EXTINT_priv.h"
#include "EXTINT_config.h"
#include <avr/interrupt.h>

void (*ISR0)(void) = '\0';
void (*ISR1)(void) = '\0';
void (*ISR2)(void) = '\0';

void EXTINT_voidIntInit(u8 INTNUM) {
	switch (INTNUM) {
	case 0:
		CLR_BIT(DDRD, 2); //Set pin as input
		SET_BIT(SREG, 7); //Enable global EXT interrupt
#if	(INT0_MOD == MOD_LOWLVL )
		CLR_BIT(MCUCR, ISC00);
		CLR_BIT(MCUCR, ISC01);
	#elif	(INT0_MOD == MOD_CHLVL )
		SET_BIT(MCUCR, ISC00);
		CLR_BIT(MCUCR, ISC01);
	#elif	(INT0_MOD == MOD_FALLEDGE )
		CLR_BIT(MCUCR, ISC00);
		SET_BIT(MCUCR, ISC01);
#elif	(INT0_MOD == MOD_RISEDGE )
		SET_BIT(MCUCR, ISC00);
		SET_BIT(MCUCR, ISC01);
	#endif
		SET_BIT(GICR, INT0);  // Enable INT0
		/*** Clear Interrupts Flags ***/
		SET_BIT(GIFR, INTF0);
		break;
	case 1:
		CLR_BIT(DDRD, 3); //Set pin as input
		SET_BIT(SREG, 7); //Enable global EXT interrupt
#if	(INT0_MOD == MOD_LOWLVL )
		CLR_BIT(MCUCR, ISC10);
		CLR_BIT(MCUCR, ISC11);
	#elif	(INT0_MOD == MOD_CHLVL )
		SET_BIT(MCUCR, ISC10);
		CLR_BIT(MCUCR, ISC11);
	#elif	(INT0_MOD == MOD_FALLEDGE )
		CLR_BIT(MCUCR, ISC10);
		SET_BIT(MCUCR, ISC11);
#elif	(INT0_MOD == MOD_RISEDGE )
		SET_BIT(MCUCR, ISC10);
		SET_BIT(MCUCR, ISC11);
	#endif
		SET_BIT(GICR, INT1);  // Enable INT0
		/*** Clear Interrupts Flags ***/
		SET_BIT(GIFR, INTF1);
		break;

	case 2:
		CLR_BIT(DDRB, 2); //Set pin as input
		SET_BIT(SREG, 7); //Enable global EXT interrupt

#if	(INT0_MOD == MOD_FALLEDGE )
		CLR_BIT(MCUCSR, ISC2);
#elif	(INT0_MOD == MOD_RISEDGE )
		SET_BIT(MCUCSR, ISC2);
	#endif
		SET_BIT(GICR, INT2);  // Enable INT0
		/*** Clear Interrupts Flags ***/
		SET_BIT(GIFR, INTF2);
		break;
	}

}
void EXTINT_voidIntSetIsr(u8 INTNUM, void (*Local_ISR)(void)) {
	switch (INTNUM) {
	case 0:
		ISR0 = Local_ISR;
		break;

	case 1:
		ISR1 = Local_ISR;
		break;

	case 2:
		ISR2 = Local_ISR;
		break;
	}
}
ISR(INT0_vect) {
	ISR0();
}

ISR(INT1_vect) {
	ISR1();
}
ISR(INT2_vect) {
	ISR2();
}
