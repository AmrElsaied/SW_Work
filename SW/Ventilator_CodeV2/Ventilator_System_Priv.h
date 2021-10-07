#ifndef  _Private_
#define _Private_
#include "Modes_Priv.h"
#include <Arduino.h>


// ----Configuration of the SYSTEM HARDWARE----
#define MOTOR_DIR_PIN   9
#define MOTOR_PWM_PIN   8
#define MOTOR_FEEDBACK_PIN  18
#define STEPPER_PULSE_PIN 7
#define STEPPER_DIRECTION_PIN 6
#define RELAY_PIN 24



//Some signals used in debuging
#define ON_OFF_SIGNAL 0                 // TO know in which state you are
#define STEPPER_STEPS_SIGNAL 0
#define SPEED_SIGNAL   0
#define RECIEVED_TIME_SIGNAL  1
#define PID_ERROR_SIGNAL      0
#define Pressure_SIGNAL  1

//SOME NEEDED DEFINES FOR THE SYSTEM
#define TRUE 1
#define FALSE 0
#define WORK_STATE_ON     1
#define WORK_STATE_OFF     2
#define WORK_STATE_HOMMING 3
#define STOP 0
#define Begin_SPEED 180
#define Valid_Cycle_Threshold  1300
#define POSITIVE_DIR 1
#define NEGATIVE_NEG -1


//SOME DEFINES FOR THE STEPPER MOTOR
#define MAX_STEPS 50025  //Accroding to the system
#define MIN_STEPS 140
#define Stepper_Speed 1200
#define Pressure_ID 5
#define DC_MOTOR_ID 3
long int TOTAL_TAKED_STEPS = 30000;










//ESSENTIAL VARIABLES FOR THE SYSTEM
long int Motor_Time_NOW = 0;                      //THE current time vaalue
long int Motor_Last_Time_ON = 0;                  // THE time at which the system lef the ON STATE
long int Motor_Last_Time_OFF = 0;                 // THE time at which the system lef the OFF STATE


#if (TESTINGMODE == FALSE)
extern double BREATH_PER_MINUETE ;
extern double INSPIRATION ;
extern double EXPIRATION ;
double Cycle = (60 / BREATH_PER_MINUETE);
double  TIME_I = ((Cycle / (INSPIRATION + EXPIRATION)) * INSPIRATION);
double TIME_E = (Cycle / (INSPIRATION + EXPIRATION)) * EXPIRATION;
double  Motor_Time_ON = (TIME_I * 2) * 1000;
double Motor_Time_OFF = (TIME_E - TIME_I) * 1000;

#elif (TESTINGMODE == TRUE)
double  Motor_Time_ON = Device_ON_Period * 1000;    // The time specified for the ON STATE in msec
double  Motor_Time_OFF = Device_OFF_Period * 1000;  // The time specified for the OFF STATE in msec
#endif
double Motor_Time_FEEDBACK = Motor_Time_ON;      // The time that motor nedded to finish a complete cycle

//Function of the SYSTEM
void Determine_STATE (int state);           // Function to determine what to do acroding to the input state
void Ventilator_ON (void);                  // do what is demannded in the on state
void Ventilator_OFF (void);                  // Do what demanded in the OFF state
void Stepper_Init(void);
void Stepper_Move (int Place , int iteration);
void Ventilator_Homming (void);
void FIRE_FLAG (void);
#endif _Private_
