#ifndef _SD_
#define _SD_
#include <Arduino.h>


bool SD_boolStarted(); // Check if SD is connected
bool SD_boolfileOpened(); // Check if RTC is running
bool SD_boolWriteString(String line);

#endif
