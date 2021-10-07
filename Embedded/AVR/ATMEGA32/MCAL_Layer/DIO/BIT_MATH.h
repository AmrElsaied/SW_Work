/*******************************************************************************************/
/*  Author      : Amr Mohamed                                                              */
/*  Date        : 3 Sep 2019                                                               */
/*  Version     : 1.0 V                                                                    */
/*******************************************************************************************/
#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(X,Bit) ((X)|=(unsigned char )1<<(Bit))
#define SETM_BIT(X,Bit1,Bit2,Bit3) ((X)|=((unsigned char )1<<(Bit1))|((unsigned char )1<<(Bit2))|((unsigned char )1<<(Bit3)))
#define CLR_BIT(X,Bit) ((X)&=~(1<<(Bit)))
#define GET_BIT(X,Bit) (((X)>>(Bit))&(1))
#define TOGLE_BIT(X,Bit) ((X)^=1<<(Bit))

#endif /* BIT_MATH_H_ */
