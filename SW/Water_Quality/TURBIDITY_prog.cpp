#include <Arduino.h>
#include "TURBIDITY_config.h"

int sensorValue;
float voltage;
float TURB_Read ()
{
  float Ret_Val = 0;
  sensorValue = analogRead(SensorPin)*2;
//  Serial.print("Reading: ");Serial.println(sensorValue);
  voltage = sensorValue * (4.2 / 1023);
  Ret_Val = voltage;
  return Ret_Val;
}



