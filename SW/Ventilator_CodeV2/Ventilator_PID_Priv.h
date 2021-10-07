#ifndef _PIDPRI_
#define _PIDPRI_
#include "Ventilator_Config.h"
#include "Modes_Priv.h"


//PID Print Signals
// PID Debugging "Inside compute()"

#define PRINT_LastInput 0                  // print lastInput in compute function 
#define PRINT_LastInput_Next_Time 0        // print lastInput in compute function for next time "it will be equal to input"
#define PRINT_K_PARAMETERS 0               // print K parameters in compute function
#define PRINT_ERROR_COMPUTE 1              // print error without direction "in compute function"
#define PRINT_OUTPUT_PARAMETERS 1          // print: ITerm, dInput, output "in compute function"




#if (TESTINGMODE == FALSE)
extern double BREATH_PER_MINUETE ;
extern double INSPIRATION ;
extern double EXPIRATION ;
double Cycle_PID = (60 / BREATH_PER_MINUETE);
double TIME_I_PID = ((Cycle_PID / (INSPIRATION + EXPIRATION)) * INSPIRATION);
double PID_SETPOINT = (TIME_I_PID * 2)*1000;
extern int Pressure_PID_SETPOINT ;
//Will be added
//int Pressure_PID_SETPOINT = 

#elif (TESTINGMODE == TRUE)
double PID_SETPOINT = Device_ON_Period*1000;
extern int Pressure_PID_SETPOINT ;
#endif


#define DIRECT 0
#define REVERSE 1
#define MANUAL 0
#define AUTOMATIC 1
#define Pressure_ID 5
#define DC_MOTOR_ID 3
#endif
