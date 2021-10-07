#ifndef FLOWSENSOR_CONFIG_H
#define FLOWSENSOR_CONFIG_H



#define sensorPin 5          //pH meter Analog output to Arduino Analog Input 0

float FLOWSen_Init();
float FLOWSen_Read_LperM();
float FLOWSen_Read_mLperS();
void pulseCounter();
void DisableFlow();
void EnableFlow();
#endif
