#include "Pressure_Int.h"
#include <Arduino.h>


#include <Wire.h>
#include <SFE_BMP180.h>

SFE_BMP180 bmp180;

int sensorValue = 0;         // the sensor value

void Pressure_Init()
{
  bool success = bmp180.begin();
  char status;
  double T, P;
  status = bmp180.startTemperature();
  if (status != 0) {
    delay(1000);
    status = bmp180.getTemperature(T);
    if (status != 0) {
      status = bmp180.startPressure(3);
      if (status != 0) {
        delay(status);
        status = bmp180.getPressure(P, T);
        delay(1000);
        status = bmp180.getPressure(P, T);
        sensorValue = (P * 1.0197442889221 + 0.3);
      }
    }
  }
}

float Pressure_Reading()
{
  char status;
  double T, P;
  bool success = false;
  status = bmp180.startTemperature();
  if (status != 0) {
    delay(3);
    status = bmp180.getTemperature(T);
    if (status != 0) {
      status = bmp180.startPressure(3);

      if (status != 0) {
        delay(status);
        status = bmp180.getPressure(P, T);
        if (status != 0) {
          return ( 1.0197442889221 * P - sensorValue - 0.58 +2);
        }
      }
    }
  }
}




//#include "Pressure_Int.h"
//
//int readings[numReadings];      // the readings from the analog input
//int readIndex = 0;              // the index of the current reading
//int total = 0;                  // the running total
//int average = 0;                // the average
//int inputPin = A0;
//int Base_Value = 936;
//int End_Value  = Base_Value;
//void Pressure_Init (void)
//{
//  for (int thisReading = 0; thisReading < numReadings; thisReading++)
//  {
//    readings[thisReading] = 0;
//  }
//
//  for (int b = 0 ; b < numReadings ; b++)
//  {
//    total = total - readings[readIndex];
//    // read from the sensor:
//    readings[readIndex] = analogRead(inputPin);
//    // add the reading to the total:
//    total = total + readings[readIndex];
//    // advance to the next position in the array:
//    readIndex = readIndex + 1;
//
//    // if we're at the end of the array...
//    if (readIndex >= numReadings) {
//      // ...wrap around to the beginning:
//      readIndex = 0;
//    }
//
//    // calculate the average:
//    average = total / numReadings;
//  }
//  Base_Value = analogRead(A0);
//}
//
//int Pressure_Reading (void)
//{
//  int RetVal = 0;
//  // subtract the last reading:
//  total = total - readings[readIndex];
//  // read from the sensor:
//  readings[readIndex] = analogRead(inputPin);
//  // add the reading to the total:
//  total = total + readings[readIndex];
//  // advance to the next position in the array:
//  readIndex = readIndex + 1;
//
//  // if we're at the end of the array...
//  if (readIndex >= numReadings) {
//    // ...wrap around to the beginning:
//    readIndex = 0;
//  }
//  // calculate the average:
//  average = total / numReadings;
//  // send it to the computer as ASCII digits
//
//  // read the analog in value:
//  //  sensorValue = analogRead(inputPin);
//  // map it to the range of the analog out:
//  if (analogRead(A0) < Base_Value + 50 )
//  {
//    RetVal = map(analogRead(A0), Base_Value-1, Base_Value + 50, 0, 25);
//  }
//  else if (analogRead(A0) >= Base_Value + 50)
//  {
//    int  outputValue = map(analogRead(A0),  Base_Value + 50-1,  Base_Value + 50 + 10 , 26, 35) ;
//  }
//  // change the analog out value:
//  // print the results to the Serial Monitor:
//  // wait 2 milliseconds before the next loop for the analog-to-digital
//  // converter to settle after the last reading:
//  delay(2);
//  return RetVal;
//}
