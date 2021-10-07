#include <Arduino.h>
#include "UltraSonic_Int.h"

//UltraSonic Readings
long duration;
int distance;

int buf1[15], temp1;
void UltraSonic_Init (void)
{
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}

int UltraSonic_Reading (void)
{
  unsigned long int avgValue;
  int Ret_Val = 0;
  int lastDistance = 0;
  for (int i = 0 ; i < 15 ; i++)
  {
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(EchoPin, HIGH, 23529);
    distance = duration * 0.034 / 2;
    if (distance > lastDistance)
    {
      lastDistance = distance;
    }
    buf1[i] = distance;
  }
  for (int i = 0; i < 14; i++) //sort the analog from small to large
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buf1[i] > buf1[j])
      {
        temp1 = buf1[i];
        buf1[i] = buf1[j];
        buf1[j] = temp1;
      }
    }
  }
  avgValue = 0;
  for (int i = 6; i < 10; i++)               //take the average value of 6 center sample
    avgValue += buf1[i];
//Ret_Val = avgValue / 4;
 Ret_Val = lastDistance;
  return Ret_Val;
}

