
#include "SYS_interface.h"

//System Variables
extern unsigned long pumpWorkTime;
extern unsigned long pumpDownTime;
extern unsigned long defrostTime;
extern unsigned long dryingTime;
extern unsigned long coilFreezingTime;
extern  float setPoint;
extern float deffrentialValue;
float sysTempreature = 0;
byte SysState = 0;
void setup() {
  // put your setup code here, to run once:
  //  voidGetSavedData();
  Serial.begin(9600);
  voidSystemInit();
}

void loop() {
  // put your main code here, to run repeatedly:
  SysState = byteSysGetState(millis());
  voidSysApplyState(SysState);
}
