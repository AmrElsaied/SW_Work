#ifndef  _Config_
#define _Config_
#include "Modes_Priv.h"
/*
 * 
 * This file is opene for users you can change the numbers as you want 
 * Accroding to the patient's needs before starting runnning the system
 * 
 * Explanation of what is this:
 * the variable (BREATH_PER_MINUETE) it's a number between 6 --> 40 SO TAKE CARE !!!!!!
 * the variable (INSPIRATION) is the Variable which depends on the patient status which used in calculating (I/E Ratio)
 * the variable (EXPIRATION) is the Variable which depends on the patient status which used in calculating (I/E Ratio)
 */
 
#if (TESTINGMODE == FALSE)
extern double BREATH_PER_MINUETE ;
extern double INSPIRATION ;
extern double EXPIRATION  ;
#endif

#endif _Config_
