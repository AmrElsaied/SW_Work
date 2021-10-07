#include "RTC_Prog.h"
#include"TFT_Prog.h"
#include <EEPROM.h>
#include"SD_Prog.h"
//#include <SHT1x.h>
#include <Sensirion.h>
#include "Adafruit_CCS811.h"
#define dataPin  A9
#define clockPin A8
#define BatteryPin A10
//SHT1x sht1x(dataPin, clockPin);
Sensirion sht = Sensirion(dataPin, clockPin);
char page_status = '0';
extern int BatteryPer ;
extern int HumidiyPer ;
extern int Temperature ;
unsigned long lastTime = 0;
unsigned long timeInterval = 0;
String logData = "";
unsigned long inputTime = 400;
int Address = 0;
bool FileIndicator = false;
String RTCString = "";
String timeIntervalString = "";
extern String LogTime;
extern String LastLogTime;
extern String RTCTime;
extern String RTCLastTime;
bool RTCUpdateFlag = false;
int Battery = 100;
unsigned long LastRestartTime = 0;
unsigned long LogCount = 0;
unsigned long SensorsTime = 0;
bool SDSTATE = false;
extern int Page_Update ;
uint16_t rawData;
float dewpoint;
#define reset_Pin   14
extern int Co2;
Adafruit_CCS811 ccs;
#define AWAKE 16
void setup () {
  Serial.begin(9600);
  pinMode(BatteryPin, INPUT);
  //  RTC_boolStarted();
  Serial.print("RTC: "); Serial.println(RTC_boolStarted());
  EEPROM.get( Address, timeInterval );
  inputTime = timeInterval;
  LogTime = String(timeInterval / 1000);
  LastLogTime =   LogTime;
  Serial.println(SD_boolStarted());
  Serial.println();
  SDSTATE = SD_boolfileOpened();
  logData = "Date,Time,Temperature,Humidity";
  if (SDSTATE)
  {
    FileIndicator = SD_boolWriteString(logData);
    Serial.println("Written in File");
  }
  else
  {
    Serial.println("Failed Written");

  }

  RTCTime = RTC_StringCurrentTimeRefernce();
  RTCLastTime = RTCTime;
  sht.measTemp(&rawData);              // Maps to: sht.meas(TEMP, &rawData, BLOCK)
  Temperature = sht.calcTemp(rawData);
  sht.measHumi(&rawData);              // Maps to: sht.meas(HUMI, &rawData, BLOCK)
  HumidiyPer = sht.calcHumi(rawData, Temperature);
  dewpoint = sht.calcDewpoint(HumidiyPer, Temperature);

  pinMode(reset_Pin, OUTPUT);
  pinMode(AWAKE, OUTPUT);
  digitalWrite(AWAKE, LOW);
  digitalWrite(reset_Pin, HIGH);
  delay(20);
  while (!ccs.begin()) {
    digitalWrite(reset_Pin, LOW);
    delay(50);
    digitalWrite(reset_Pin, HIGH);
    delay(50);
  }
  while (!ccs.available());

  TFT_voidInit();
  TFT_voidButtonInit();
  TFT_voidHomeScreen();
}

void loop () {
  digitalWrite(AWAKE, HIGH);
  page_status = TFT_voidTouchHandle();
  TFT_voidScreenHandle(page_status);
  if (millis() - lastTime > timeInterval)
  {
    lastTime = millis();
    // Save data to txt file
    logData = RTC_StringCurrentTime() + ',' + String(Temperature) + ',' + String(HumidiyPer) + ',' + String(Co2) ;
    SDSTATE = SD_boolfileOpened();
    if (SDSTATE)
    {
      FileIndicator = SD_boolWriteString(logData);
      Serial.println("Written in File");
      LogCount++;
    }
    else
    {
      if (millis() - LastRestartTime > 30000 && timeIntervalString != "UP" && RTCString != "UP")
      {
        LastRestartTime = millis();
        SD_boolStarted();
      }
      Serial.println("Failed Written");
    }
  }
  timeIntervalString = TFT_LogTimeCallBack();
  if (timeIntervalString != "UP")
  {
    //    Serial.print("STRING: "); Serial.println(timeIntervalString);
    //    delay(5000);
    inputTime = timeIntervalString.toInt() * 1000;
  }
  if (inputTime != timeInterval)
  {
    // Update timeInterval
    Serial.println("Updated Time Interval");
    timeInterval = inputTime;
    Serial.print("STEP1: "); Serial.println(timeInterval);
    //    delay(2000);
    EEPROM.put( Address, timeInterval);
    //    Serial.print("STEP2: ");Serial.println(timeInterval);
    //    delay(2000);
  }
  //  RTCTime = RTC_StringCurrentTimeRefernce();
  //  Serial.println(RTCTime);
  //  RTCLastTime = RTCTime;
  RTCString = TFT_RTCCallBack();
  //  Serial.println(RTCString);
  if (RTCString != "UP")
  {
    if (!RTCUpdateFlag)
    {
      RTCTime = RTC_StringCurrentTimeRefernce();
      Serial.print("Time:"); Serial.println(RTCTime);
      RTCLastTime = RTCTime;
    }
    if (RTCString != RTCLastTime && RTCUpdateFlag)
    {
      RTCUpdateFlag = false;
      Serial.println("Update RTC");
      UpdateRTC(RTCString);
      Serial.println(RTCString);
    }
    if (RTCString == RTCLastTime && RTCUpdateFlag)
    {
      RTCUpdateFlag = false;
    }
  }
  else
  {
    RTCUpdateFlag = true;
  }
  if (Page_Update == 4) {
    //double timer = ;
    if ((millis() - SensorsTime) > (timeInterval - (timeInterval * (0.2))))
    {
      SensorsTime = millis();
      int raw = 0;
      for (int i = 0; i < 10; i++) raw += analogRead(BatteryPin);
      raw = raw / 10;
      float per = raw * (5.0 / 1023.0);
      Serial.print("BAttery ANalog: "); Serial.print(analogRead(BatteryPin));
      Serial.print("  Battery Per: "); Serial.println(per);
      if (per <= 3)
      {
        BatteryPer = 20;
      }
      else if (per > 3 && per <= 3.2)
      {
        BatteryPer = 30;
      }

      else if (per > 3.2 && per <= 3.35)
      {
        BatteryPer = 40;
      }

      else if (per > 3.35 && per <= 3.55)
      {
        BatteryPer = 50;
      }

      else if (per > 3.55 && per <= 3.7)
      {
        BatteryPer = 60;
      }
      else if (per > 3.7 && per <= 3.85)
      {
        BatteryPer = 70;
      }
      else if (per > 3.85 && per <= 4)
      {
        BatteryPer = 80;
      }
      else if (per > 4 && per <= 4.1)
      {
        BatteryPer = 90;
      }
      else if (per > 4.1 && per <= 4.23)
      {
        BatteryPer = 100;
      }
//      else if (per > 3 && per <= 4.23)
//      {
//        Serial.println("kkkkkkkk");
//        per = 3.9;
//        BatteryPer = map(3.9, 3.0, 4.23, 21.0, 100.0);
//        Serial.println(BatteryPer);
//      }
      else
      {
        BatteryPer = 0;
      }
      //      BatteryPer = raw;
      //BatteryPer = map(analogRead(BatteryPin),
      //      sht.measTemp(&rawData);              // Maps to: sht.meas(TEMP, &rawData, BLOCK)
      //      Temperature = sht.calcTemp(rawData);
      //      //      Temperature = sht1x.readTemperatureC();
      //      sht.measHumi(&rawData);              // Maps to: sht.meas(HUMI, &rawData, BLOCK)
      //      HumidiyPer = sht.calcHumi(rawData, Temperature);
      //      dewpoint = sht.calcDewpoint(HumidiyPer, Temperature);
      //      sht.meas(TEMP, &rawData, NONBLOCK);
      //      delay(20);
      //      //      if (sht.measRdy()) {                         // Process temperature measurement?
      //      Serial.println("HEreeeeeeeeeeeeeeeeeeeeeeeeeeeee");
      //      Temperature = sht.calcTemp(rawData);
      //      sht.meas(HUMI, &rawData, NONBLOCK);
      //      delay(20);
      //      HumidiyPer = sht.calcHumi(rawData, Temperature);
      sht.measTemp(&rawData);              // Maps to: sht.meas(TEMP, &rawData, BLOCK)
      Temperature = sht.calcTemp(rawData);
      sht.measHumi(&rawData);              // Maps to: sht.meas(HUMI, &rawData, BLOCK)
      HumidiyPer = sht.calcHumi(rawData, Temperature);
      //        dewpoint = sht.calcDewpoint(HumidiyPer, Temperature);
      //      Serial.println(Temperature);
      //      }
      digitalWrite(AWAKE, LOW);

      delay(20);
      if (!ccs.readData()) {
        Co2  = ccs.geteCO2();
        Serial.print("Co2: "); Serial.println(Co2);
      }
      //      HumidiyPer = sht1x.readHumidity();
    }
  }
  else
  {
    SensorsTime = millis();
  }
  //  Serial.print("Co2: "); Serial.println(Co2);
  //  Serial.print("STEP3: ");Serial.println(timeInterval);
}
