#include "SYS_interface.h"
#include "SYS_config.h"
#include <EEPROM.h>

//System Variables
unsigned long pumpWorkTime  = 2;
unsigned long pumpDownTime  = 2;
unsigned long defrostTime   = 4;
unsigned long dryingTime    = 4;
unsigned long coilFreezingTime    = 2;
float setPoint = 0;
float deffrentialValue = 0;
bool emergencydeFrost = false;
bool emergencydeFrostEnabledFlag = false;
unsigned long emergencydeFrostTime = 0;
extern float sysTempreature;
bool reachDeffrentialValue = false;
byte byteSysGetState(unsigned long copySysTimer)
{
  static unsigned long lastSysTimer = 0;
  byte RetVal = 0;
  copySysTimer = ((millis() - lastSysTimer) / (60000));
  //  Serial.print ("Here1: ");
  //  Serial.println(copySysTimer);
  if (digitalRead(emrFrostPin) == false && emergencydeFrost == false && copySysTimer < pumpWorkTime  )
  {
    emergencydeFrostTime = copySysTimer;

    //    Serial.print("Here1: ");
    //    Serial.println(emergencyFrostTime);
    //    delay(300);
  }
  if (digitalRead(emrFrostPin) == false || emergencydeFrostEnabledFlag)
  {
    emergencydeFrostEnabledFlag = true;
    copySysTimer = (copySysTimer + pumpWorkTime) - emergencydeFrostTime;
    emergencydeFrost = true;
    //    Serial.print ("Here2: ");
    //    Serial.println(copySysTimer);
    //    delay(200);
  }
  else
  {
    emergencydeFrost = false;
  }
  if (copySysTimer < pumpWorkTime )
  {
    RetVal = pumpWorkTimeState;
    //    Serial.println("One");
  }
  else if (copySysTimer >= pumpWorkTime && copySysTimer < (pumpWorkTime + pumpDownTime))
  {
    RetVal = pumpDownTimeState;
    //    Serial.println("Two");
  }
  else if (copySysTimer >= (pumpWorkTime + pumpDownTime) && copySysTimer < (pumpWorkTime + pumpDownTime + defrostTime))
  {
    RetVal = defrostTimeState;
    //    Serial.println("Three");
  }
  else if (copySysTimer >= (pumpWorkTime + pumpDownTime + defrostTime) && copySysTimer < (pumpWorkTime + pumpDownTime + defrostTime + dryingTime))
  {
    RetVal = dryingTimeState;
    //    Serial.println("Four");
  }
  else if (copySysTimer >= (pumpWorkTime + pumpDownTime + defrostTime + dryingTime) && copySysTimer < (pumpWorkTime + pumpDownTime + defrostTime + dryingTime + coilFreezingTime))
  {
    //    Serial.println("Five");
    RetVal = coilFreezingTimeState;
  }
  else
  {
    RetVal = pumpWorkTimeState;
    emergencydeFrostEnabledFlag = false;
    if (emergencydeFrost)
    {
      RetVal = pumpDownTimeState;
    }
    lastSysTimer = millis();
    emergencydeFrostTime = 0;
  }
  return RetVal;
}
void voidSysApplyState(byte copyState)
{
  switch (copyState)
  {
    case pumpWorkTimeState:
      Serial.println("1");
      if ((sysTempreature > (setPoint - deffrentialValue)) && reachDeffrentialValue == false)
      {
        digitalWrite(pumpPin, HIGH);
        digitalWrite(drainTrayPin, LOW);
        digitalWrite(coilPin, LOW);
        digitalWrite(fanPin, HIGH);
      }
      else
      {
        reachDeffrentialValue = true;
        digitalWrite(pumpPin, LOW);
        digitalWrite(drainTrayPin, LOW);
        digitalWrite(coilPin, LOW);
        digitalWrite(fanPin, HIGH);
        if(sysTempreature >= setPoint)
        {
          reachDeffrentialValue = false;
        }
      }

      break;
    case pumpDownTimeState:
      Serial.println("2");
      digitalWrite(pumpPin, LOW);
      digitalWrite(drainTrayPin, HIGH);
      digitalWrite(coilPin, LOW);
      digitalWrite(fanPin, HIGH);
      break;
    case defrostTimeState:
      Serial.println("3");
      digitalWrite(pumpPin, LOW);
      digitalWrite(drainTrayPin, HIGH);
      digitalWrite(coilPin, HIGH);
      digitalWrite(fanPin, LOW);
      break;
    case dryingTimeState:
      Serial.println("4");
      digitalWrite(pumpPin, LOW);
      digitalWrite(drainTrayPin, HIGH);
      digitalWrite(coilPin, LOW);
      digitalWrite(fanPin, LOW);
      break;
    case coilFreezingTimeState:
      Serial.println("5");
      digitalWrite(pumpPin, HIGH);
      digitalWrite(drainTrayPin, HIGH);
      digitalWrite(coilPin, LOW);
      digitalWrite(fanPin, LOW);
      break;
  }

}

void voidGetSavedData(void)
{

  EEPROM.get( pumpWorkTimeAddress, pumpWorkTime );
  EEPROM.get( pumpDownTimeAddress, pumpDownTime );
  EEPROM.get( defrostTimeAddress, defrostTime );
  EEPROM.get( dryingTimeAddress, dryingTime );
  EEPROM.get( coilFreezingTimeAddress, coilFreezingTime );
  EEPROM.get( setPointAddress, setPoint );
  EEPROM.get( deffrentialValueAddress, deffrentialValue );
}

void voidSystemInit()
{
  pinMode(pumpPin, OUTPUT);
  pinMode(drainTrayPin, OUTPUT);
  pinMode(coilPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(emrFrostPin, INPUT_PULLUP);
}

