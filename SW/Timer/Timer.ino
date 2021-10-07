#include "Timer.h"
Timer myTimer("SEC", 2);
void setup() {
  // put your setup code here, to run once:
//  Serial.begin(9600);
  //  voidTimerInit("SEC",1);
  myTimer.voidTimerStart();
}

void loop() {
  // put your main code here, to run repeatedly:
  myTimer.voidTimerLoop();
  if (myTimer.voidTimerFinishState())
  {
//    Serial.println("Finish");
//    delay(1000);
    myTimer.voidTimerReset();
//    voidTimerStop();
  }
  else
  {
//        Serial.println("Not Yet");
  }
}

//void voidTimerInit(String copyTimerMode , unsigned long copyTime)
//{
//  timerPeriod = copyTime;
//  timerMode = copyTimerMode;
//}
//void voidTimerStart()
//{
//  timerStartFlag = true;
//  timerFinishFlag = false;
//  voidTimerReset();
//}
//void voidTimerStop()
//{
//  timerStartFlag = false;
//  timerFinishFlag = false;
//}
//void voidTimerLoop()
//{
//
//  if (!timerStartFlag || timerPeriod == 0)return;
//  if (timerMode == "MIN")
//  {
//    timerCurTime = ((millis() - timerRecTime)/(60000));
//  }
//  else if (timerMode == "SEC")
//  {
//    timerCurTime = ((millis() - timerRecTime)/(1000));
//  }
//  else
//  {
//    timerCurTime = (millis() - timerRecTime);
//  }
//
//  if (timerCurTime >= timerPeriod)
//  {
//    timerFinishFlag = true;
//  }
//  else
//  {
//    timerFinishFlag = false;
//  }
//}
//
//bool voidTimerFinishState()
//{
//  return timerFinishFlag;
//}
//bool voidTimerWorkState()
//{
//  return timerStartFlag;
//}
//void voidTimerReset()
//{
//  timerRecTime = millis();
//}

