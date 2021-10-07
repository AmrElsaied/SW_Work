
#ifndef _TFT_C
#define _TFT_C
#include <Adafruit_GFX.h>
#include <UTFTGLUE.h>
#include <TouchScreen.h>
#include <Fonts/FreeSans9pt7b.h>
//#include <Fonts/FreeSans24pt7b.h>
//#include "Fonts/FreeSansBold24pt7b.h"
//#include "Fonts/FreeSerif12pt7b.h"
//#include "FreeDefaultFonts.h"
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
//extern char currentPage;
UTFTGLUE myGLCD(0, A2, A1, A3, A4, A0); //all dummy args
const int XP = 8, XM = A2, YP = A3, YM = 9; //ID=0x9341
const int TS_LEFT = 937, TS_RT = 100, TS_TOP = 879, TS_BOT = 143;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
Adafruit_GFX_Button HOME_PAGE_btn, SET_RTC_btn, BACK_MAIN_HOME_btn, One_btn, Two_btn, Three_btn, Four_btn, Five_btn, Six_btn, Seven_btn, Eight_btn, Nine_btn, Zero_btn, Delete_btn, Back_btn, Next_btn, LogTime_btn,UpdateLogTime_btn,UpdateRTC_btn,Battery_btn ;
//==== Defining Variables
//#if !defined(SmallFont)
//extern uint8_t SmallFont[];
//#endif
//#if !defined(BigFont)
//extern uint8_t BigFont[];
//#endif
//#if !defined(SevenSegNumFont)
//extern uint8_t SevenSegNumFont[];
//#endif
// ======= Touch_getXY() updates global vars
int pixel_x, pixel_y;
#define MINPRESSURE 150
#define MAXPRESSURE 1000
#define HOME_SCREEN '0'
#define RTC_SCREEN '1'
#define LOG_SCREEN '2'
#define BATTERY_SCREEN '3'
#endif
