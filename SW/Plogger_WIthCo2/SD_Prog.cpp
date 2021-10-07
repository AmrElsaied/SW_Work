#include"SD_Prog.h"
#include <SPI.h>
#include <SD.h>

File logFile;
String fileName = "MOOG.txt" ;
const int chipSelect = 53;

bool SD_boolStarted()
{
  bool RetVal = false;
  RetVal = SD.begin(chipSelect);
  return RetVal;
}

bool SD_boolfileOpened()
{
  bool RetVal = false;
  //RetVal = SD.open(fileName,FILE_WRITE);
  logFile = SD.open(fileName, FILE_WRITE);
  RetVal = logFile;
 // logFile.close();

  return RetVal;
}

bool SD_boolWriteString(String line)
{
  bool RetVal = false;
 // logFile = SD.open(fileName, FILE_WRITE);
  logFile.println(line);
  RetVal = logFile;
  logFile.close();
  return RetVal;
}

