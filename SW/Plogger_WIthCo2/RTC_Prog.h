#ifndef _RTC_
#define _RTC_



bool RTC_boolStarted(); // Check if RTC is connected
bool RTC_boolRunning(); // Check if RTC is running
String RTC_StringCurrentTime();
String RTC_StringCurrentTimeRefernce();
void UpdateRTC(String Date);
#endif
