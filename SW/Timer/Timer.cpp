#include <Arduino.h>
#include "Timer.h"


Timer::Timer(String copyTimerMode , unsigned long copyTime)
{
  timerPeriod = copyTime;
  timerMode = copyTimerMode;
}
void Timer::voidTimerStart()
{
  timerStartFlag = true;
  timerFinishFlag = false;
  voidTimerReset();
}

void Timer::voidTimerStop()
{
  timerStartFlag = false;
  timerFinishFlag = false;
}
void Timer::voidTimerReset()
{
  timerRecTime = millis();
}

void Timer::voidTimerLoop()
{
  if (!timerStartFlag || timerPeriod == 0)return;
  if (timerMode == "MIN")
  {
    timerCurTime = ((millis() - timerRecTime) / (60000));
  }
  else if (timerMode == "SEC")
  {
    timerCurTime = ((millis() - timerRecTime) / (1000));
  }
  else
  {
    timerCurTime = (millis() - timerRecTime);
  }

  if (timerCurTime >= timerPeriod)
  {
    timerFinishFlag = true;
  }
  else
  {
    timerFinishFlag = false;
  }
}
bool Timer::voidTimerFinishState()
{
  return timerFinishFlag;
}
bool Timer::voidTimerWorkState()
{
  return timerStartFlag;
}

void Timer::voidTimerChangePeriod(unsigned long copyTimerPeriod)
{
  timerPeriod = copyTimerPeriod;
}

