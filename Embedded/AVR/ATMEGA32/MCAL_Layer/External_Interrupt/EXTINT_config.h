/*******************************************************************************************/
/*  Author      : Amr Mohamed                                                              */
/*  Date        : 5 Sep 2019                                                               */
/*  Version     : 1.0 V                                                                    */
/*******************************************************************************************/

#ifndef EXTINT_CONFIG_H_
#define EXTINT_CONFIG_H_

/*
 * To choose the external interrupt mode for each one
 * For INT0: MOD_LOWLVL	- MOD_CHLVL - MOD_FALLEDGE - MOD_RISEDGE
 * For INT1: MOD_LOWLVL	- MOD_CHLVL - MOD_FALLEDGE - MOD_RISEDGE
 * For INT2: MOD_FALLEDGE - MOD_RISEDGE
 */
#define INT0_MOD		MOD_FALLEDGE
#define INT1_MOD		MOD_FALLEDGE
#define INT2_MOD		MOD_FALLEDGE
#endif /* EXTINT_CONFIG_H_ */
