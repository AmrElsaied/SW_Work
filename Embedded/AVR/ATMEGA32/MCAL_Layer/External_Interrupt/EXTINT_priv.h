/*******************************************************************************************/
/*  Author      : Amr Mohamed                                                              */
/*  Date        : 5 Sep 2019                                                               */
/*  Version     : 1.0 V                                                                    */
/*******************************************************************************************/


#ifndef EXTINT_PRIV_H_
#define EXTINT_PRIV_H_

#define SREG    (*((volatile unsigned char*)0x5F))
#define MCUCR   (*((volatile unsigned char*)0x55))
#define MCUCSR  (*((volatile unsigned char*)0x54))

#define GICR    (*((volatile unsigned char*)0x5B))
#define GIFR    (*((volatile unsigned char*)0x5A))


#define DDRB	(*((volatile unsigned char*)0x37))
#define DDRD	(*((volatile unsigned char*)0x31))

#define MOD_LOWLVL		0
#define MOD_CHLVL		1
#define MOD_FALLEDGE	2
#define MOD_RISEDGE		3

#define INT1  	7
#define INT0  	6
#define INT2  	2

#define ISC00	0
#define ISC01	1

#define ISC10	2
#define ISC11	3

#define ISC2	6
#define INTF1	7
#define INTF0	6
#define INTF2	5

#define INTR0	0
#define INTR1	1
#define INTR2	2
#endif /* EXTINT_PRIV_H_ */
