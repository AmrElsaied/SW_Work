#ifndef  _System_
#define _System_
#include <Arduino.h>

/*
   All configuration of System (PINS .. ) in the (Ventilator_System_Priv.h) File *For developper ONLY!!!*
   The configuration of the Time (ON/OFF) in the (Ventilator_Config.h) File *For Normall USERS*
*/
void Ventilator_Init (void);  // Call this function in void Setup to initialize the system

void Ventilator_Start (void); // Call this function in void LOOP to Start the system

#endif _System_
