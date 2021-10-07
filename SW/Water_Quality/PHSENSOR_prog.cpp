#include <Arduino.h>
#include "PHSENSOR_Config.h"

unsigned long int avgValue;  //Store the average value of the sensor feedback
int buf[10], temp;

float PH_Read ()
{
  float Ret_Val;
  for (int i = 0; i < 10; i++) //Get 10 sample value from the sensor for smooth the value
  {
    buf[i] = analogRead(SensorPin);
    //Serial.println( buf[i]);
    delay(10);
  }
  for (int i = 0; i < 9; i++) //sort the analog from small to large
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buf[i] > buf[j])
      {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
  avgValue = 0;
  for (int i = 2; i < 8; i++)               //take the average value of 6 center sample
    avgValue += buf[i];
  float phValue = (float)avgValue * 3.3 / 1023 / 6; //convert the analog into millivolt
  phValue = (3.5 * phValue)+.5;                  //convert the millivolt into pH value
  Ret_Val = phValue;
//  Serial.print("    pH:");
//  Serial.print(phValue, 2);
//  Serial.println(" ");
  return Ret_Val;
}

