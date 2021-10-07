#ifndef _MODES_
#define _MODES_

/*
 * NOTE !!!!!!!!!
 * Change the (TESTINGMODE) to False if you will run the program
 */
#define TRUE 1
#define FALSE 0
#define TESTINGMODE FALSE

#if (TESTINGMODE == TRUE)
#define Device_ON_Period  3   //Write the time at which the device will remain running (in Seconds)
#define Device_OFF_Period 1   //Write the time at which the device will remain off (in Seconds) 

#endif

#endif
