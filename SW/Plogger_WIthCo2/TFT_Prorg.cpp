#include"TFT_Prog.h"
#include "TFT_Config.h"
#include "Images.h"
String LogTime = "4";
String LastLogTime = "4";
String RTCTime = "22052021220520";
String RTCLastTime = "22052021220520";
String RTCString1 = "";
String RTCString2 = "";
char lastScreen = HOME_SCREEN;
bool UpdateLogFlag = true;
bool UpdateRTCFlag = true;
bool Cleared = false;
bool Cleared2 = false;
bool ButtonRestart = false;
int Interval = 2000;
unsigned long LastTime = 0;
int BatteryPer = 100;
int HumidiyPer = 100;
int Temperature = 100;
extern bool FileIndicator;
extern unsigned long LogCount;
extern int timeInterval;
extern bool SDSTATE;
int Page_Update = 0;
extern String timeIntervalString;
int Co2 = 7000 ;
void TFT_DisableButton()
{
  BACK_MAIN_HOME_btn.drawButton(true);
  One_btn.drawButton(true);
  Two_btn.drawButton(true);
  Three_btn.drawButton(true);
  Four_btn.drawButton(true);
  Five_btn.drawButton(true);
  Six_btn.drawButton(true);
  Seven_btn.drawButton(true);
  Eight_btn.drawButton(true);
  Nine_btn.drawButton(true);
  Back_btn.drawButton(true);
  Zero_btn.drawButton(true);
  Next_btn.drawButton(true);
  LogTime_btn.drawButton(true);
  SET_RTC_btn.drawButton(true);
}
void TFT_voidInit()
{
  myGLCD.InitLCD();
  myGLCD.clrScr();
}
void TFT_voidClear()
{
  myGLCD.clrScr();
}
void TFT_voidHomeScreen() {
  // currentPage = '0';
  // Title
  myGLCD.setFont(NULL);
  myGLCD.setBackColor(0, 0, 0); // Sets the background color of the area where the text will be printed to black
  myGLCD.setColor(255, 255, 255); // Sets color to white
  // myGLCD.setFont(BigFont); // Sets font to big
  myGLCD.setFont(&FreeSans9pt7b);
  myGLCD.print("MOG Controllers PLogger", CENTER, 10); // Prints the string on the screen
  myGLCD.setColor(255, 0, 0); // Sets color to red
  myGLCD.drawLine(0, 32, 490, 32); // Draws the red line
  myGLCD.setColor(255, 255, 255); // Sets color to white
  //  myGLCD.setFont(SmallFont); // Sets the font to small
  //  myGLCD.print("by ENG. Mohamed Abd El-Samie", CENTER, 41); // Prints the string
  myGLCD.setFont(NULL);
  //Draw Buttons
  //  myGLCD.setFont(NULL);
  LogTime_btn.drawButton(false);
  SET_RTC_btn.drawButton(false);
  Battery_btn.drawButton(false);
}

void TFT_voidButtonInit()
{
  HOME_PAGE_btn.initButton(&myGLCD,  250, 250, 250, 40, WHITE, RED, WHITE, "HOME PAGE", 2);
  SET_RTC_btn.initButton(&myGLCD,  250, 150, 250, 40, WHITE, RED, WHITE, "SET RTC", 2);
  BACK_MAIN_HOME_btn.initButton(&myGLCD,  30, 20, 60, 36, WHITE, MAGENTA, WHITE, "<-", 2);
  One_btn.initButton(&myGLCD,  30, 120, 60, 36, WHITE, BLUE, WHITE, "1", 2);
  Two_btn.initButton(&myGLCD,  90, 120, 60, 36, WHITE, BLUE, WHITE, "2", 2);
  Three_btn.initButton(&myGLCD,  150, 120, 60, 36, WHITE, BLUE, WHITE, "3", 2);
  Four_btn.initButton(&myGLCD,  30, 165, 60, 36, WHITE, BLUE, WHITE, "4", 2);
  Five_btn.initButton(&myGLCD,  90, 165, 60, 36, WHITE, BLUE, WHITE, "5", 2);
  Six_btn.initButton(&myGLCD,  150, 165, 60, 36, WHITE, BLUE, WHITE, "6", 2);
  Seven_btn.initButton(&myGLCD,  30, 210, 60, 36, WHITE, BLUE, WHITE, "7", 2);
  Eight_btn.initButton(&myGLCD,  90, 210, 60, 36, WHITE, BLUE, WHITE, "8", 2);
  Nine_btn.initButton(&myGLCD,  150, 210, 60, 36, WHITE, BLUE, WHITE, "9", 2);
  Back_btn.initButton(&myGLCD,  30, 255, 60, 36, WHITE, BLUE, WHITE, "<-", 2);
  Zero_btn.initButton(&myGLCD,  90, 255, 60, 36, WHITE, BLUE, WHITE, "0", 2);
  Next_btn.initButton(&myGLCD,  150, 255, 60, 36, WHITE, BLUE, WHITE, "->", 2);
  LogTime_btn.initButton(&myGLCD,  250, 200, 250, 40, WHITE, RED, WHITE, "LOG Time", 2);
  UpdateLogTime_btn.initButton(&myGLCD,  350, 250, 250, 40, WHITE, RED, WHITE, "UPDATE", 2);
  UpdateRTC_btn.initButton(&myGLCD,  350, 250, 250, 40, WHITE, RED, WHITE, "UPDATE", 2);
  Battery_btn.initButton(&myGLCD,  250, 250, 250, 40, WHITE, RED, WHITE, "HOME PAGE", 2);
}

bool Touch_getXY(void)
{
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT);      //restore shared pins
  pinMode(XM, OUTPUT);
  digitalWrite(YP, HIGH);   //because TFT control pins
  digitalWrite(XM, HIGH);
  bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
  if (pressed) {
    pixel_x = map(p.y, TS_LEFT, TS_RT, 0, myGLCD.width()); //.kbv makes sense to me
    pixel_y = map(p.x, TS_TOP, TS_BOT, 0, myGLCD.height());
    Serial.print("TouchX:"); Serial.print(pixel_x); Serial.print("   TouchY:"); Serial.println(pixel_y);
  }
  return pressed;
}

char TFT_voidTouchHandle()
{
  static char RetVal = HOME_SCREEN;
  bool down = Touch_getXY();
//  Serial.println("H");
  if (down)
  {
    Serial.print("Down:"); Serial.println(down);
    BACK_MAIN_HOME_btn.press(down && BACK_MAIN_HOME_btn.contains(pixel_x, pixel_y));
    if (lastScreen == HOME_SCREEN)
    {
      SET_RTC_btn.press(down && SET_RTC_btn.contains(pixel_x, pixel_y));
      LogTime_btn.press(down && LogTime_btn.contains(pixel_x, pixel_y));
      Battery_btn.press(down && Battery_btn.contains(pixel_x, pixel_y));
      if (LogTime_btn.justPressed())
      {
        Serial.print("LogTime: "); Serial.print("X: "); Serial.print(pixel_x);
        Serial.print("LogTime: "); Serial.print("Y: "); Serial.println(pixel_y);
        RetVal = LOG_SCREEN;
        UpdateLogFlag = false;
        LastLogTime = LogTime;
        LogTime = "";
        Cleared = false;
      }
      else if (SET_RTC_btn.justPressed())
      {
        Serial.print("RTC: "); Serial.print("X: "); Serial.print(pixel_x);
        Serial.print("RTC: "); Serial.print("Y: "); Serial.println(pixel_y);
        RetVal = RTC_SCREEN;
        RTCString1 = "";
        RTCString2 = "";
        RTCLastTime = RTCTime;
        RTCTime = "";
        Cleared = false;
        Cleared2 = false;
        UpdateRTCFlag = false;
      }
      else if (Battery_btn.justPressed())
      {
        RetVal = BATTERY_SCREEN;
      }
    }
    else if (lastScreen == LOG_SCREEN)
    {
      //      BACK_MAIN_HOME_btn.press(down && BACK_MAIN_HOME_btn.contains(pixel_x, pixel_y));
      UpdateLogTime_btn.press(down && UpdateLogTime_btn.contains(pixel_x, pixel_y));
      if (UpdateLogTime_btn.justPressed())
      {
        Serial.print("Update: "); Serial.print("X: "); Serial.print(pixel_x);
        Serial.print("Update: "); Serial.print("Y: "); Serial.println(pixel_y);
        RetVal = HOME_SCREEN;
        UpdateLogFlag = true;
        UpdateLogTime_btn.drawButton(true);
      }
      if (UpdateLogTime_btn.justReleased()) {
        //       myGLCD.setFont(NULL);
        UpdateLogTime_btn.drawButton();
      }
    }
    else if (lastScreen == RTC_SCREEN)
    {
      //      BACK_MAIN_HOME_btn.press(down && BACK_MAIN_HOME_btn.contains(pixel_x, pixel_y));
      UpdateRTC_btn.press(down && UpdateRTC_btn.contains(pixel_x, pixel_y));
      if (UpdateRTC_btn.justPressed())
      {
        RetVal = HOME_SCREEN;
        UpdateRTC_btn.drawButton(true);
        UpdateRTCFlag = true;
      }
      if (UpdateRTC_btn.justReleased()) {
        //       myGLCD.setFont(NULL);
        UpdateRTC_btn.drawButton();
      }
    }
    if (lastScreen != HOME_SCREEN)
    {
      //      BACK_MAIN_HOME_btn.press(down && BACK_MAIN_HOME_btn.contains(pixel_x, pixel_y));
      //      BACK_MAIN_HOME_btn.press(down && BACK_MAIN_HOME_btn.contains(pixel_x, pixel_y));
      if (BACK_MAIN_HOME_btn.justPressed())
      {
        Serial.print("Update: "); Serial.print("X: "); Serial.print(pixel_x);
        Serial.print("Update: "); Serial.print("Y: "); Serial.println(pixel_y);
        RetVal = HOME_SCREEN;
        if (lastScreen == LOG_SCREEN)
        {
          LogTime = LastLogTime;
          UpdateLogFlag = true;
        }
        if (lastScreen == RTC_SCREEN)
        {
          RTCTime = RTCLastTime;
          UpdateRTCFlag = true;
        }
      }
    }
  }
  return RetVal;
}

void TFT_voidScreenHandle(char ScreenNum)
{
  if (lastScreen != ScreenNum)
  {
    lastScreen = ScreenNum;

    switch (ScreenNum)
    {
      case HOME_SCREEN:
        myGLCD.clrScr();
        TFT_voidHomeScreen();
        Serial.print("Changed");
        Page_Update = 1;
        break;
      case RTC_SCREEN:
        myGLCD.clrScr();
        TFT_voidSetRTC();
        Page_Update = 2;
        break;
      case LOG_SCREEN:
        myGLCD.clrScr();
        TFT_voidSetLog();
        Page_Update = 3;
        break;
      case BATTERY_SCREEN:
        myGLCD.clrScr();
        TFT_voidBattery();
        Page_Update = 4;
        break;
    }
    //  myGLCD.setContrast('16');
  }
  if (lastScreen == LOG_SCREEN)
  {
    TFT_voidLogKeypadHandle();
  }
  else if (lastScreen == RTC_SCREEN)
  {
    TFT_voidRTCKeypadHandle();
  }
  else if (lastScreen == BATTERY_SCREEN)
  {
    if (millis() - LastTime > Interval)
    {
      LastTime = millis();

      myGLCD.setColor(255, 255, 255);
      myGLCD.fillRoundRect(120, 85, 200, 120);
      myGLCD.setColor(255, 255, 255);
      myGLCD.fillRoundRect(120, 150, 200, 200);
      myGLCD.setColor(255, 255, 255);
      myGLCD.fillRoundRect(120, 230, 200, 275);

      myGLCD.setColor(255, 255, 255);
      myGLCD.fillRoundRect(370, 225, 470, 270);

      myGLCD.setColor(0, 100, 190);
      myGLCD.setTextSize(3);
      myGLCD.printNumI(HumidiyPer, 132, 90);
      myGLCD.setColor(255, 0, 0);
      myGLCD.setTextSize(3);
      myGLCD.printNumI(Temperature, 132, 165);
      myGLCD.setColor(255, 0, 0);
      myGLCD.setTextSize(3);
      myGLCD.printNumI(BatteryPer, 132, 242);

      myGLCD.setColor(255, 0, 0);
      myGLCD.setBackColor(255, 255, 255);
      myGLCD.setTextSize(3);
      myGLCD.printNumI(Co2, 380, 239);

      myGLCD.setTextSize(2);
      myGLCD.setBackColor(255, 255, 255);
      myGLCD.setColor(255, 0, 0);
      myGLCD.print("          ", 345, 82);
      myGLCD.print(String(RTCTime[0]) + String(RTCTime[1]) + "/" + String(RTCTime[2]) + String(RTCTime[3]) + "/" + String(RTCTime[4]) + String(RTCTime[5]) + String(RTCTime[6]) + String(RTCTime[7]), 345, 82);
      myGLCD.setTextSize(2);
      myGLCD.setBackColor(255, 255, 255);
      myGLCD.setColor(255, 0, 0);
      myGLCD.print("          ", 345, 102);
      myGLCD.print(String(RTCTime[8]) + String(RTCTime[9]) + ":" + String(RTCTime[10]) + String(RTCTime[11]) + ":" + String(RTCTime[12]) + String(RTCTime[13]), 345, 102);
      myGLCD.setTextSize(2);
      myGLCD.setBackColor(255, 255, 255);
      myGLCD.print("         ", 370, 132);
      if (SDSTATE)
      {
        myGLCD.setColor(0, 255, 0);
        myGLCD.print("AVAILABLE", 370, 132);
      }
      else
      {
        myGLCD.setColor(255, 0, 0);
        myGLCD.print("MISSING", 370, 132);
      }
      myGLCD.setTextSize(2);
      myGLCD.setBackColor(255, 255, 255);
      myGLCD.print("      ", 390, 162);
      myGLCD.setColor(255, 0, 0);
      myGLCD.printNumI(LogCount, 390, 162);
      myGLCD.setBackColor(255, 255, 255);
      myGLCD.print("    ", 395, 190);
      myGLCD.setColor(255, 0, 0);
      //      Serial.print ("TRIMEEEEEEE : " ); Serial.println(timeIntervalString);
      //myGLCD.printNumI(timeInterval / 1000, 395, 202);
      myGLCD.print(timeIntervalString, 395, 190);
    }
  }
}

void TFT_voidSetRTC() {
  //  myGLCD.setFont(NULL);
  BACK_MAIN_HOME_btn.drawButton(false);
  One_btn.drawButton(false);
  Two_btn.drawButton(false);
  Three_btn.drawButton(false);
  Four_btn.drawButton(false);
  Five_btn.drawButton(false);
  Six_btn.drawButton(false);
  Seven_btn.drawButton(false);
  Eight_btn.drawButton(false);
  Nine_btn.drawButton(false);
  Back_btn.drawButton(false);
  Zero_btn.drawButton(false);
  Next_btn.drawButton(false);
  UpdateLogTime_btn.drawButton(false);
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.setBackColor(0, 0, 0);
  // myGLCD.setFont(SmallFont);
  myGLCD.print("Back to Main Menu", 70, 18);
  myGLCD.drawRGBBitmap(360, 5, MOG, 110, 70);
  //  myGLCD.setFont(BigFont);
  myGLCD.print("MOG Controllers PLogger", CENTER, 50);
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawLine(0, 76, CENTER, 76);
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.setBackColor(0, 0, 0);
  //  myGLCD.setFont(SmallFont);
  //  myGLCD.print("by ENG. Mohamed Abd El-Samie", CENTER, 280);
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRoundRect(270, 140, 440, 170);
  //  myGLCD.setFont(BigFont);
  myGLCD.setTextSize(2);
  //  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("DD-MM-YYYY", 295, 148);
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRoundRect(270, 180, 440, 210);
  //  myGLCD.setFont(BigFont);
  myGLCD.setTextSize(2);
  //  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("HH:MM:SS", 295, 188);
}

void TFT_voidBattery() {
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.setBackColor(0, 0, 0);
  //  myGLCD.setFont(SmallFont);
  myGLCD.setFont(&FreeSans9pt7b);
  myGLCD.print("Back to Main Menu", 70, 18);
  myGLCD.drawRGBBitmap(360, 5, MOG, 110, 70);
  //  myGLCD.setFont(BigFont);
  myGLCD.setFont(&FreeSans9pt7b);
  myGLCD.print("MOG Controllers PLogger", CENTER, 50);
  myGLCD.setFont(NULL);
  BACK_MAIN_HOME_btn.drawButton(false);
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawLine(0, 76, CENTER, 76);
  myGLCD.drawRGBBitmap(15, 85, HUM, 60, 40);
  myGLCD.drawRGBBitmap(18, 135, Temperaure, 60, 70);
  myGLCD.drawRGBBitmap(0, 210, Battery, 80, 70);

  myGLCD.setColor(255, 0, 0);
  myGLCD.drawLine(80, 76, 80, 290);
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawLine(0, 125, 270, 125);
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawLine(0, 205, 480, 205);
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.setBackColor(0, 0, 0);
  //  myGLCD.setFont(SmallFont);
  //  myGLCD.print("by ENG. Mohamed Abd El-Samie", CENTER, 300);
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRoundRect(120, 85, 200, 120);
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRoundRect(120, 150, 200, 200);
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRoundRect(120, 230, 200, 275);
  myGLCD.drawRGBBitmap(210, 82, Percenage2, 40, 40);
  //  myGLCD.drawRGBBitmap(210, 150, Cel, 1, 1);
  myGLCD.drawRGBBitmap(210, 150, Co, 50, 50);
  myGLCD.drawRGBBitmap(210, 225, Percentage, 50, 50);
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawLine(270, 76, 270, 290);
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRoundRect(272, 78, 480, 202);
  myGLCD.setTextSize(2);
  myGLCD.setBackColor(255, 255, 255);
  myGLCD.setColor(0, 0, 0);
  myGLCD.print("DATE: ", 275, 82);
  myGLCD.print("TIME: ", 275, 102);
  myGLCD.print("SD CARD: ", 275, 132);
  myGLCD.print("LOGs Num: ", 275, 162);
  myGLCD.print("LOG TIME: ", 275, 190);
  myGLCD.setColor(255, 0, 0);
  myGLCD.print("SEC", 443, 190);
  myGLCD.setFont(NULL);
  myGLCD.setTextSize(5);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setColor(0, 191, 255);
  myGLCD.print("CO2:", 275, 230);
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawLine(365, 205, 365, 290);
  myGLCD.setFont(NULL);
  //  myGLCD.drawRGBBitmap(275, 211, Cel, 70, 70);
  //  myGLCD.drawRGBBitmap(275, 210, Cel, 70, 70);
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawLine(0, 290, 480, 290);

}
void TFT_voidSetLog() {
  //  myGLCD.setFont(NULL);
  BACK_MAIN_HOME_btn.drawButton(false);
  One_btn.drawButton(false);
  Two_btn.drawButton(false);
  Three_btn.drawButton(false);
  Four_btn.drawButton(false);
  Five_btn.drawButton(false);
  Six_btn.drawButton(false);
  Seven_btn.drawButton(false);
  Eight_btn.drawButton(false);
  Nine_btn.drawButton(false);
  Back_btn.drawButton(false);
  Zero_btn.drawButton(false);
  Next_btn.drawButton(false);
  UpdateLogTime_btn.drawButton(false);
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.setBackColor(0, 0, 0);
  //  myGLCD.setFont(SmallFont);
  myGLCD.print("Back to Main Menu", 70, 18);
  myGLCD.drawRGBBitmap(360, 5, MOG, 110, 70);
  //  myGLCD.setFont(BigFont);
  myGLCD.print("MOG Controllers PLogger", CENTER, 50);
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawLine(0, 76, CENTER, 76);
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.setBackColor(0, 0, 0);
  //  myGLCD.setFont(SmallFont);
  //  myGLCD.print("by ENG. Mohamed Abd El-Samie", CENTER, 280);
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRoundRect(270, 150, 420, 190);
  //  myGLCD.setFont(BigFont);
  myGLCD.setTextSize(2);
  //  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("SECONDS", 305, 163);
}

void TFT_voidLogKeypadHandle() {
  //while (true) {
  //    Serial.println(Flag);
  bool down = Touch_getXY();
  One_btn.press(down && One_btn.contains(pixel_x, pixel_y));
  Two_btn.press(down && Two_btn.contains(pixel_x, pixel_y));
  Three_btn.press(down && Three_btn.contains(pixel_x, pixel_y));
  Four_btn.press(down && Four_btn.contains(pixel_x, pixel_y));
  Five_btn.press(down && Five_btn.contains(pixel_x, pixel_y));
  Six_btn.press(down && Six_btn.contains(pixel_x, pixel_y));
  Seven_btn.press(down && Seven_btn.contains(pixel_x, pixel_y));
  Eight_btn.press(down && Eight_btn.contains(pixel_x, pixel_y));
  Nine_btn.press(down && Nine_btn.contains(pixel_x, pixel_y));
  Zero_btn.press(down && Zero_btn.contains(pixel_x, pixel_y));
  Next_btn.press(down && Next_btn.contains(pixel_x, pixel_y));
  Back_btn.press(down && Back_btn.contains(pixel_x, pixel_y));
  if (LogTime.length() < 6)
  {
    if (One_btn.justReleased()) {
      //     myGLCD.setFont(NULL);
      One_btn.drawButton();
    }
    if (Two_btn.justReleased()) {
      //      myGLCD.setFont(NULL);
      Two_btn.drawButton();
    }
    else if (Three_btn.justReleased()) {
      //      myGLCD.setFont(NULL);
      Three_btn.drawButton();
    }
    else if (Four_btn.justReleased()) {
      //      myGLCD.setFont(NULL);
      Four_btn.drawButton();
    }
    else if (Five_btn.justReleased()) {
      //      myGLCD.setFont(NULL);
      Five_btn.drawButton();
    }
    else if (Six_btn.justReleased()) {
      //      myGLCD.setFont(NULL);
      Six_btn.drawButton();
    }
    else if (Seven_btn.justReleased()) {
      //      myGLCD.setFont(NULL);
      Seven_btn.drawButton();
    }
    else if (Eight_btn.justReleased()) {
      //      myGLCD.setFont(NULL);
      Eight_btn.drawButton();
    }
    else if (Nine_btn.justReleased()) {
      //      myGLCD.setFont(NULL);
      Nine_btn.drawButton();
    }
    else if (Zero_btn.justReleased()) {
      //      myGLCD.setFont(NULL);
      Zero_btn.drawButton();
    }
    else if (Next_btn.justReleased()) {
      //      myGLCD.setFont(NULL);
      Next_btn.drawButton();
    }
    else if (Back_btn.justReleased()) {
      //      myGLCD.setFont(NULL);
      Back_btn.drawButton();
    }
    if (One_btn.justPressed()) {
      //      myGLCD.setFont(NULL);
      One_btn.drawButton(true);
      LogTime += "1";
    }
    else if (Two_btn.justPressed()) {
      //      myGLCD.setFont(NULL);
      Two_btn.drawButton(true);
      LogTime += "2";
    }
    else if (Three_btn.justPressed()) {
      //      myGLCD.setFont(NULL);
      Three_btn.drawButton(true);
      LogTime += "3";
    }
    else if (Four_btn.justPressed()) {
      //      myGLCD.setFont(NULL);
      Four_btn.drawButton(true);
      LogTime += "4";
    }
    else if (Five_btn.justPressed()) {
      myGLCD.setFont(NULL);
      Five_btn.drawButton(true);
      LogTime += "5";
    }
    else if (Six_btn.justPressed()) {
      myGLCD.setFont(NULL);
      Six_btn.drawButton(true);
      LogTime += "6";
    }
    else if (Seven_btn.justPressed()) {
      myGLCD.setFont(NULL);
      Seven_btn.drawButton(true);
      LogTime += "7";
    }
    else if (Eight_btn.justPressed()) {
      myGLCD.setFont(NULL);
      Eight_btn.drawButton(true);
      LogTime += "8";
    }
    else if (Nine_btn.justPressed()) {
      myGLCD.setFont(NULL);
      Nine_btn.drawButton(true);
      LogTime += "9";
    }
    else if (Zero_btn.justPressed()) {
      myGLCD.setFont(NULL);
      Zero_btn.drawButton(true);
      if (LogTime.length() > 0)
      {
        LogTime += "0";
      }
    }
    else if (Back_btn.justPressed()) {
      myGLCD.setFont(NULL);
      Back_btn.drawButton(true);
      myGLCD.setBackColor(255, 0, 0);
      myGLCD.setColor(255, 255, 255);
      myGLCD.print("        ", 305, 163);
      if (LogTime.length() > 1)
      {
        String tempString = LogTime;
        LogTime = "";
        for (int j = 0 ; j < tempString.length() - 1 ; j++)
        {
          LogTime += tempString[j];
        }
      }
      else if (LogTime.length() > 0)
      {
        LogTime = "";
      }
    }
    else if (Next_btn.justPressed()) {
      myGLCD.setFont(NULL);
      Next_btn.drawButton(false);
    }

    if (LogTime.length() > 0)
    {
      if (!Cleared)
      {
        myGLCD.setBackColor(255, 0, 0);
        myGLCD.setColor(255, 255, 255);
        myGLCD.print("        ", 305, 163);
        Cleared = true;
      }
      myGLCD.setBackColor(255, 0, 0);
      myGLCD.setColor(255, 255, 255);
      myGLCD.print(LogTime, 305, 163);
    }
    else
    {
      Cleared = false;
      myGLCD.setBackColor(255, 0, 0);
      myGLCD.setColor(255, 255, 255);
      myGLCD.print("SECONDS", 305, 163);
    }
    ButtonRestart = false;
  }
  else
  {
    if (Back_btn.justPressed()) {
      myGLCD.setFont(NULL);
      Back_btn.drawButton(true);
      myGLCD.setBackColor(255, 0, 0);
      myGLCD.setColor(255, 255, 255);
      myGLCD.print("        ", 305, 163);
      if (LogTime.length() > 1)
      {
        String tempString = LogTime;
        LogTime = "";
        for (int j = 0 ; j < tempString.length() - 1 ; j++)
        {
          LogTime += tempString[j];
        }
      }
      else if (LogTime.length() > 0)
      {
        LogTime = "";
      }
    }
    if (!ButtonRestart)
    {
      ButtonRestart = true;
      One_btn.drawButton();
      Two_btn.drawButton();
      Three_btn.drawButton();
      Four_btn.drawButton();
      Five_btn.drawButton();
      Six_btn.drawButton();
      Seven_btn.drawButton();
      Eight_btn.drawButton();
      Nine_btn.drawButton();
      Zero_btn.drawButton();
    }
  }
}

void TFT_voidRTCKeypadHandle() {
  //while (true) {
  //    Serial.println(Flag);
  bool down = Touch_getXY();
  One_btn.press(down && One_btn.contains(pixel_x, pixel_y));
  Two_btn.press(down && Two_btn.contains(pixel_x, pixel_y));
  Three_btn.press(down && Three_btn.contains(pixel_x, pixel_y));
  Four_btn.press(down && Four_btn.contains(pixel_x, pixel_y));
  Five_btn.press(down && Five_btn.contains(pixel_x, pixel_y));
  Six_btn.press(down && Six_btn.contains(pixel_x, pixel_y));
  Seven_btn.press(down && Seven_btn.contains(pixel_x, pixel_y));
  Eight_btn.press(down && Eight_btn.contains(pixel_x, pixel_y));
  Nine_btn.press(down && Nine_btn.contains(pixel_x, pixel_y));
  Zero_btn.press(down && Zero_btn.contains(pixel_x, pixel_y));
  Next_btn.press(down && Next_btn.contains(pixel_x, pixel_y));
  Back_btn.press(down && Back_btn.contains(pixel_x, pixel_y));
  if (RTCTime.length() < 14)
  {
    if (One_btn.justReleased()) {
      myGLCD.setFont(NULL);
      One_btn.drawButton();
    }
    if (Two_btn.justReleased()) {
      myGLCD.setFont(NULL);
      Two_btn.drawButton();
    }
    else if (Three_btn.justReleased()) {
      myGLCD.setFont(NULL);
      Three_btn.drawButton();
    }
    else if (Four_btn.justReleased()) {
      myGLCD.setFont(NULL);
      Four_btn.drawButton();
    }
    else if (Five_btn.justReleased()) {
      myGLCD.setFont(NULL);
      Five_btn.drawButton();
    }
    else if (Six_btn.justReleased()) {
      myGLCD.setFont(NULL);
      Six_btn.drawButton();
    }
    else if (Seven_btn.justReleased()) {
      myGLCD.setFont(NULL);
      Seven_btn.drawButton();
    }
    else if (Eight_btn.justReleased()) {
      myGLCD.setFont(NULL);
      Eight_btn.drawButton();
    }
    else if (Nine_btn.justReleased()) {
      myGLCD.setFont(NULL);
      Nine_btn.drawButton();
    }
    else if (Zero_btn.justReleased()) {
      myGLCD.setFont(NULL);
      Zero_btn.drawButton();
    }
    else if (Next_btn.justReleased()) {
      myGLCD.setFont(NULL);
      Next_btn.drawButton();
    }
    else if (Back_btn.justReleased()) {
      myGLCD.setFont(NULL);
      Back_btn.drawButton();
    }
    if (One_btn.justPressed()) {
      myGLCD.setFont(NULL);
      One_btn.drawButton(true);
      RTCTime += "1";
    }
    else if (Two_btn.justPressed()) {
      myGLCD.setFont(NULL);
      Two_btn.drawButton(true);
      RTCTime += "2";
    }
    else if (Three_btn.justPressed()) {
      myGLCD.setFont(NULL);
      Three_btn.drawButton(true);
      RTCTime += "3";
    }
    else if (Four_btn.justPressed()) {
      myGLCD.setFont(NULL);
      Four_btn.drawButton(true);
      RTCTime += "4";
    }
    else if (Five_btn.justPressed()) {
      myGLCD.setFont(NULL);
      Five_btn.drawButton(true);
      RTCTime += "5";
    }
    else if (Six_btn.justPressed()) {
      myGLCD.setFont(NULL);
      Six_btn.drawButton(true);
      RTCTime += "6";
    }
    else if (Seven_btn.justPressed()) {
      myGLCD.setFont(NULL);
      Seven_btn.drawButton(true);
      RTCTime += "7";
    }
    else if (Eight_btn.justPressed()) {
      myGLCD.setFont(NULL);
      Eight_btn.drawButton(true);
      RTCTime += "8";
    }
    else if (Nine_btn.justPressed()) {
      myGLCD.setFont(NULL);
      Nine_btn.drawButton(true);
      RTCTime += "9";
    }
    else if (Zero_btn.justPressed()) {
      myGLCD.setFont(NULL);
      Zero_btn.drawButton(true);
      RTCTime += "0";
    }
    else if (Back_btn.justPressed()) {
      myGLCD.setFont(NULL);
      Back_btn.drawButton(true);
      myGLCD.setBackColor(255, 0, 0);
      myGLCD.setColor(255, 255, 255);
      if (RTCTime.length() < 9)
      {
        myGLCD.print("          ", 295, 148);
      }
      else
      {
        myGLCD.print("          ", 295, 188);
      }

      if (RTCTime.length() > 1)
      {
        String tempString = RTCTime;
        RTCTime = "";
        for (int j = 0 ; j < tempString.length() - 1 ; j++)
        {
          RTCTime += tempString[j];
        }
      }
      else if (RTCTime.length() > 0)
      {
        RTCTime = "";
      }
    }
    else if (Next_btn.justPressed()) {
      myGLCD.setFont(NULL);
      Next_btn.drawButton(false);
    }

    if (RTCTime.length() > 0 && RTCTime.length() < 9)
    {
      RTCString1 = "";
      for ( int o = 0 ; o < RTCTime.length() ; o++)
      {
        if (o == 2 || o == 4)
        {
          RTCString1 += "-";
        }
        RTCString1 += RTCTime[o];
      }
      if (!Cleared)
      {
        myGLCD.setBackColor(255, 0, 0);
        myGLCD.setColor(255, 255, 255);
        myGLCD.print("            ", 295, 148);
        //        myGLCD.print("DD-MM-YYYY", 295, 148);
        Cleared = true;
      }
      myGLCD.setBackColor(255, 0, 0);
      myGLCD.setColor(255, 255, 255);
      myGLCD.print(RTCString1, 295, 148);
    }
    else if (RTCTime == 0)
    {
      Cleared = false;
      myGLCD.setBackColor(255, 0, 0);
      myGLCD.setColor(255, 255, 255);
      myGLCD.print("DD-MM-YYYY", 295, 148);
    }
    if (RTCTime.length() > 8)
    {
      RTCString2 = "";
      for ( int c = 8 ; c < RTCTime.length() ; c++)
      {
        if (c == 10 || c == 12)
        {
          RTCString2 += ":";
        }
        RTCString2 += RTCTime[c];
      }
      if (!Cleared2)
      {
        myGLCD.setBackColor(255, 0, 0);
        myGLCD.setColor(255, 255, 255);
        myGLCD.print("          ", 295, 188);
        Cleared2 = true;
      }
      myGLCD.setBackColor(255, 0, 0);
      myGLCD.setColor(255, 255, 255);
      myGLCD.print(RTCString2, 295, 188);
    }
    else if (RTCTime.length() == 8)
    {
      Cleared2 = false;
      myGLCD.setBackColor(255, 0, 0);
      myGLCD.setColor(255, 255, 255);
      myGLCD.print("HH:MM:SS", 295, 188);
    }
    ButtonRestart = false;
  }
  else if (RTCTime.length() == 14)
  {

    if (Back_btn.justPressed()) {
      myGLCD.setFont(NULL);
      Back_btn.drawButton(true);
      myGLCD.setBackColor(255, 0, 0);
      myGLCD.setColor(255, 255, 255);
      if (RTCTime.length() < 9)
      {
        myGLCD.print("          ", 295, 148);
      }
      else
      {
        myGLCD.print("          ", 295, 188);
      }

      if (RTCTime.length() > 1)
      {
        String tempString = RTCTime;
        RTCTime = "";
        for (int j = 0 ; j < tempString.length() - 1 ; j++)
        {
          RTCTime += tempString[j];
        }
      }
      else if (RTCTime.length() > 0)
      {
        RTCTime = "";
      }
    }
    if (!ButtonRestart)
    {
      ButtonRestart = true;
      One_btn.drawButton();
      Two_btn.drawButton();
      Three_btn.drawButton();
      Four_btn.drawButton();
      Five_btn.drawButton();
      Six_btn.drawButton();
      Seven_btn.drawButton();
      Eight_btn.drawButton();
      Nine_btn.drawButton();
      Zero_btn.drawButton();
    }
  }
  //  Serial.println(RTCTime);
}


String TFT_LogTimeCallBack()
{
  String RetVal = "";
  if (UpdateLogFlag && LogTime.length() > 0)
  {
    RetVal = LogTime;
  }
  else if (UpdateLogFlag && LogTime.length() == 0)
  {
    RetVal = LastLogTime;
    LogTime = LastLogTime;
  }
  else
  {
    RetVal = "UP";
  }
  return RetVal;
}
String TFT_RTCCallBack()
{
  String RetVal = "";
  if (UpdateRTCFlag && RTCTime.length() == 14)
  {
    //RTCLastTime = RTCTime;
    RetVal = RTCTime;
  }
  else if (UpdateRTCFlag && RTCTime.length() < 14)
  {
    RetVal = RTCLastTime;
    RTCTime = RTCLastTime;
  }
  else
  {
    RetVal = "UP";
  }
  return RetVal;
}
