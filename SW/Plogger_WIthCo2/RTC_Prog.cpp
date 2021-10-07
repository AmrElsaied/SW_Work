
#include <Wire.h>
#include "RTClib.h"
#include "RTC_Prog.h"
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
bool RTC_boolStarted()
{
  bool RetVal = false;
  RetVal = rtc.begin();
//  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //rtc.adjust(DateTime(2021, 01, 25, 12, 31, 11));
  return RetVal;
}
bool RTC_boolRunning()
{
  bool RetVal = false;
  RetVal = rtc.isrunning();

  return RetVal;
}

String RTC_StringCurrentTime()
{
  String RetVal = "";
  DateTime now = rtc.now();
  RetVal = String(now.year()) + "/" + String(now.month()) + "/" + String(now.day()) + "," + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());

  return RetVal;
}
String RTC_StringCurrentTimeRefernce()
{
  String RetVal = "";
  DateTime now = rtc.now();
  if (String(now.day()).length() == 1){RetVal += "0" + String(now.day());}
  else {RetVal += String(now.day());}
  if (String(now.month()).length() == 1){RetVal += "0" + String(now.month());}
  else {RetVal += String(now.month());}
  RetVal += String(now.year());
  if (String(now.hour()).length() == 1){RetVal += "0" + String(now.hour());}
  else {RetVal += String(now.hour());}
  if (String(now.minute()).length() == 1){RetVal += "0" + String(now.minute());}
  else {RetVal += String(now.minute());}

  if (String(now.second()).length() == 1){RetVal += "0" + String(now.second());}
  else {RetVal += String(now.second());}
//  RetVal = String(now.day()) + String(now.month()) + String(now.year()) + String(now.hour()) + String(now.minute()) + String(now.second());
  return RetVal;
}

void UpdateRTC(String RTCString)
{
  rtc.adjust(DateTime(String(RTCString[4]).toInt()*1000+String(RTCString[5]).toInt()*100+String(RTCString[6]).toInt()*10+String(RTCString[7]).toInt(),String(RTCString[2]).toInt()*10+String(RTCString[3]).toInt(), String(RTCString[0]).toInt()*10+String(RTCString[1]).toInt(), String(RTCString[8]).toInt()*10+String(RTCString[9]).toInt(), String(RTCString[10]).toInt()*10+String(RTCString[11]).toInt(), String(RTCString[12]).toInt()*10+String(RTCString[13]).toInt()));
}

