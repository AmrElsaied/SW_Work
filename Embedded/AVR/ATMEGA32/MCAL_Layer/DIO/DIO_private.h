/*******************************************************************************************/
/*  Author      : Amr Mohamed                                                              */
/*  Date        : 3 Sep 2019                                                               */
/*  Version     : 1.0 V                                                                    */
/*******************************************************************************************/
#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H


#define PORTA	(*((volatile unsigned char*)0x3B))
#define PORTB	(*((volatile unsigned char*)0x38))
#define PORTC	(*((volatile unsigned char*)0x35))
#define PORTD	(*((volatile unsigned char*)0x32))

#define DDRA	(*((volatile unsigned char*)0x3A))
#define DDRB	(*((volatile unsigned char*)0x37))
#define DDRC	(*((volatile unsigned char*)0x34))
#define DDRD	(*((volatile unsigned char*)0x31))

#define PINA	(*((volatile unsigned char*)0x39))
#define PINB	(*((volatile unsigned char*)0x36))
#define PINC	(*((volatile unsigned char*)0x33))
#define PIND	(*((volatile unsigned char*)0x30))

#define SFIOR   (*((volatile unsigned char*)0x50))

#define INPUT			0
#define OUTPUT			1
#define HIGH			1
#define LOW				0
#define PRTA			0
#define PRTB			1
#define PRTC			2
#define PRTD			3
#endif
