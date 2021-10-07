#ifndef _TFT_P
#define _TFT_P
#include <Arduino.h>
void TFT_voidHomeScreen();
void TFT_voidInit();
void TFT_voidButtonInit();
void TFT_voidClear();
char TFT_voidTouchHandle();
void TFT_voidScreenHandle(char ScreenNum);
void TFT_voidSetRTC();
void TFT_voidLogKeypadHandle();
void TFT_voidRTCKeypadHandle();
void TFT_voidSetLog();
String TFT_LogTimeCallBack();
String TFT_RTCCallBack();
void TFT_voidBattery();
#endif
