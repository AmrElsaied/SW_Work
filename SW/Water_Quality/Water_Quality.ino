/* SD CARD*/
#include <mySD.h>
File myFile;
String PrintedLine = "";
String string1 = "";
String string2 = "";
String sol1 = "";
String SPHNEG = "";
String SPHPOS = "";
String STempNegFan = "";
String STempPosHeat = "";
String SLVLPos = "";
String SLVLNeg = "";
unsigned long int counter = 1;
unsigned long int Timer = 0;

/*Include library files for used modules       */
#include "FLOWSENSOR_Config.h"
#include "PHSENSOR_Config.h"
#include "TEMP_config.h"
#include "TURBIDITY_config.h"
#include "UltraSonic_Int.h"

/*Include of Configuration file            */
#include "Configurations.h"
double NTU = 0;
double NTU_equation = 0;
/*create LCD I2C object                 */
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define LCD_DOT_SIZE  LCD_5x8DOTS

/* Wifi library*/
#include <WiFi.h>
WiFiServer server = 80;
String i ;
String g ;

/* PWM variables*/
const int freq = 5000;
const int PumpChannel = 0;
const int resolution = 8;

/*Variables contain sensors readings*/
int ULTRASONIC = 0;
float PH = 0;
float TURB = 0;
float TEMP = 0;
float FLOW = 0;
int Pump = 0;
/* Timer Variables*/
long unsigned int TimerON = 0;
long unsigned int TimerOFF = 0;
void setup() {
  // put your setup code here, to run once:
  /*PWM */
  ledcSetup(PumpChannel, freq, resolution);
  ledcAttachPin(BUMP_PIN_EN , PumpChannel);
  /* Wifi Init*/
  i = "";
  g = "";
  WiFi.softAP("WaterQuality", "123456789");
  /* Sensors init*/
  //FLOWSen_Init();
  UltraSonic_Init();
  pinMode(32, INPUT);
  analogReadResolution(10);
  pinMode(36, INPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.begin(16, 2, LCD_DOT_SIZE);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Water Qual. SYS.");       /*Welcomming message*/
  delay (2000);
  lcd.clear();
  // Turn on the bumb
  pinMode (BUMP_PIN_EN, OUTPUT);
  pinMode (BUMP_PIN_DIR1, OUTPUT);
  pinMode (BUMP_PIN_DIR2, OUTPUT);
  pinMode (Solonid1_PIN, OUTPUT);
  pinMode (Solonid2_PIN, OUTPUT);
  pinMode (PHNeg, OUTPUT);
  pinMode (PHPos, OUTPUT);
  pinMode (TempNegFan, OUTPUT);
  pinMode (TempPosHeat, OUTPUT);
  pinMode (LVLPos, OUTPUT);
  pinMode (LVLNeg, OUTPUT);
  ledcWrite(PumpChannel, Pump);
  digitalWrite (BUMP_PIN_DIR1, HIGH);
  digitalWrite (BUMP_PIN_DIR2, LOW);
  digitalWrite (Solonid1_PIN, RelayLow);
  digitalWrite (Solonid2_PIN, RelayLow);
  digitalWrite (PHNeg, RelayLow);
  digitalWrite (PHPos, RelayLow);
  digitalWrite (TempNegFan, RelayLow);
  digitalWrite (TempPosHeat, RelayLow);
  digitalWrite (LVLPos, RelayLow);
  digitalWrite (LVLNeg, RelayLow);
  server.begin();
  if (!SD.begin(26, 14, 13, 27)) {
    Serial.println("initialization failed!");
  }
  else
  {
    Serial.println("initialization done.");
  }

  myFile = SD.open("T5.txt", FILE_WRITE);
  if (myFile) {
    myFile.println("/********************** New Start ***********************/");
    //    myFile.println("1st time");
    Serial.println("1st time");
    myFile.close();
  }
}

void loop() {
  /* LCD Data Section Dispaly*/
  //  myFile = SD.open("T1.txt", FILE_WRITE);
  //  analogWrite (BUMP_PIN_EN, Pump);
  ledcWrite(PumpChannel, Pump);
  ULTRASONIC = UltraSonic_Reading();

  lcd.setCursor(0, 0); lcd.print("W.LVL:");  lcd.print(ULTRASONIC);
  if (ULTRASONIC < 10)
  {
    lcd.setCursor(7, 0); lcd.print(" ");
    lcd.setCursor(8, 0); lcd.print(" ");
  }
  else if (ULTRASONIC < 99)
  {
    lcd.setCursor(8, 0); lcd.print(" ");
  }
  PH = PH_Read() ;
  lcd.setCursor(10, 0); lcd.print("PH:"); lcd.print(PH, 1);
  TEMP = TEMP_Read();
  //Serial.println(TEMP);
  lcd.setCursor(0, 1); lcd.print("T:"); lcd.print(TEMP, 2);
  // FLOW = FLOWSen_Read_mLperS();
  lcd.setCursor(9, 1); lcd.print("N:"); lcd.print(NTU_equation, 1); //lcd.print("mL/Sec");

  /* Taking descision accroding to Turbidity and PH sensors*/
  TURB = TURB_Read();
  NTU_equation = ((-1120.4 * TURB * TURB) + (5742.3 * TURB) - (4352.9)) - 2000;
  lcd.setCursor(9, 1); lcd.print("N:"); lcd.print(NTU_equation, 1); //lcd.print("mL/Sec");
  if (NTU_equation < 0)
  {
    NTU_equation = .5;
  }
  if (TURB < 5 && TURB >= NTU_CLEAR)
  {
    NTU = .5;
  }
  else if (TURB < NTU_CLEAR && TURB > NTU_HALFCLEAR)
  {
    NTU = 50;
  }
  else
  {
    NTU = 500;
  }
//  Serial.print("Volt: "); Serial.println(TURB);
//  Serial.print("NTU: "); Serial.println(NTU_equation);

  // ph >max (8)--> enable phneg
  // ph <min (6)--> enable phPos
  // between disable all
  if (PH > PH_MaxDangerVal)
  {
    digitalWrite(PHNeg, RelayHigh);
    digitalWrite(PHPos, RelayLow);
    SPHNEG = "1";
    SPHPOS = "0";
  }
  else if (PH < PH_MinDangerVal)
  {
    digitalWrite(PHNeg, RelayLow);
    digitalWrite(PHPos, RelayHigh);
    SPHNEG = "0";
    SPHPOS = "1";
  }
  else
  {
    digitalWrite(PHNeg, RelayLow);
    digitalWrite(PHPos, RelayLow);
    SPHNEG = "0";
    SPHPOS = "0";
  }

  // Turp >100 --> enable pumb and sol 2 1
  // Turp <100 --> disable pumb and sol 2 1
  if (NTU_equation > 1000 )
  {
    digitalWrite(Solonid1_PIN, RelayHigh);
    digitalWrite(Solonid2_PIN, RelayHigh);
    sol1 = "1";
  }
  else
  {
    digitalWrite(Solonid1_PIN, RelayLow);
    digitalWrite(Solonid2_PIN, RelayLow);
    sol1 = "0";
  }
  // temp>max (30) --> enable tempneg
  // temp < (25) --> enable tempPos
  // between disable all
  if (TEMP > 30)
  {
    digitalWrite(TempNegFan, RelayHigh);
    digitalWrite(TempPosHeat, RelayLow);
    STempNegFan = "1";
    STempPosHeat = "0";
  }
  else if (TEMP < 15)
  {
    digitalWrite(TempNegFan, RelayLow);
    digitalWrite(TempPosHeat, RelayHigh);
    STempNegFan = "0";
    STempPosHeat = "1";
  }
  else
  {
    digitalWrite(TempNegFan, RelayLow);
    digitalWrite(TempPosHeat, RelayLow);
    STempNegFan = "0";
    STempPosHeat = "0";
  }

  //Ultrasonic >4 --> enbale lvlPos
  //Ultrasonic <2 --> enbale lvlNeg

  if (ULTRASONIC >= 5)
  {
    digitalWrite(LVLPos, RelayHigh);
    digitalWrite(LVLNeg, RelayLow);
    SLVLPos = "1";
    SLVLNeg = "0";
  }
  else if (ULTRASONIC <= 3)
  {
    digitalWrite(LVLPos, RelayLow);
    digitalWrite(LVLNeg, RelayHigh);
    SLVLPos = "0";
    SLVLNeg = "1";
  }
  else
  {
    digitalWrite(LVLPos, RelayLow);
    digitalWrite(LVLNeg, RelayLow);
    SLVLPos = "0";
    SLVLNeg = "0";
  }

  //
  //  if ((PH > PH_MaxDangerVal || PH < PH_MinDangerVal)  || NTU_equation > TURB_DangerVal)
  //  {
  //    // Turn ON Solonid
  //    if  (SolonidMode == TimerMode)
  //    {
  //      if (millis() - TimerON < ON_Time)
  //      {
  //        digitalWrite (Solonid1_PIN, RelayHigh);
  //        digitalWrite (Solonid2_PIN, RelayLow);
  //        TimerOFF = millis();
  //      }
  //      else
  //      {
  //        if (millis() - TimerOFF < OFF_Time)
  //        {
  //          digitalWrite (Solonid1_PIN, RelayLow);
  //          digitalWrite (Solonid2_PIN, RelayHigh);
  //          TimerON = millis();
  //        }
  //      }
  //    }
  //    else
  //    {
  //      digitalWrite (Solonid1_PIN, RelayHigh);
  //      digitalWrite (Solonid2_PIN, RelayLow);
  //      string2 = "STOP";
  //      string1 = "WORK";
  //    }
  //  }
  //  else
  //  {
  //    // Turn off solonid
  //    digitalWrite (Solonid1_PIN, RelayLow);
  //    digitalWrite (Solonid2_PIN, RelayHigh);
  //    string1 = "STOP";
  //    string2 = "WORK";
  //  }
  String PrintedLine = "";
  PrintedLine = String(counter) + ")" + "T:" + String(TEMP) + " PH:" + String(PH)  + " TURBIDITY:" + String(NTU_equation) + " Water LVL:" + String(ULTRASONIC) + " Filter:" + sol1 + " PHNEG:" + SPHNEG + " PHPOS:" + SPHPOS + " TempNegFan:" + STempNegFan + " TempPosHeat:" + STempPosHeat + " LVLPos:" + SLVLPos + " LVLNeg:" + SLVLNeg;
  counter ++;
  if (millis() - Timer > (.1 * 60 * 1000))
  {
    //    Serial.println("********************Entered*******************");
    Timer = millis();
    //    digitalWrite (Solonid1_PIN, RelayLow);
    //    digitalWrite (Solonid2_PIN, RelayLow);
    //    digitalWrite (PHNeg, RelayLow);
    //    digitalWrite (PHPos, RelayLow);
    //    digitalWrite (TempNegFan, RelayLow);
    //    digitalWrite (TempPosHeat, RelayLow);
    //    digitalWrite (LVLPos, RelayLow);
    //    digitalWrite (LVLNeg, RelayLow);

    String PrintedLine = "";
    PrintedLine = String(counter) + ")" + "T:" + String(TEMP) + " PH:" + String(PH)  + " TURBIDITY:" + String(NTU_equation) + " Water LVL:" + String(ULTRASONIC) + " Filter:" + sol1 + " PHNEG:" + SPHNEG + " PHPOS:" + SPHPOS + " TempNegFan:" + STempNegFan + " TempPosHeat:" + STempPosHeat + " LVLPos:" + SLVLPos + " LVLNeg:" + SLVLNeg;
    Serial.println(PrintedLine);
    SD.begin(26, 14, 13, 27);
//    delay(100);
    myFile = SD.open("T3.txt", FILE_WRITE);
//    delay(100);
    if (myFile) {
      //      delay(30);
      //  myFile.println(PrintedLine);
      myFile.println("k");
      myFile.close();
//      Serial.println(PrintedLine);
      counter ++;
    }
    else
    {
      myFile.println("k");
      myFile.close();
//      Serial.println("fffff");
//      Serial.println("***************Failed*************************");
    }
  }

  // Connection Part
  WiFiClient client = server.available();
  if (!client) {
    // Serial.println("Not Connected");
    //    Serial.println(client.available());
    //    WiFiClient client = server.available();
    return;
  }
  //  while (!client.available()) {
  //    delay(1);
  //    Serial.println("ssssssssssssssss");
  //  }
  //  else
  //  {
  //Serial.println("Connected");
  //  DisableFlow();
  i = (client.readStringUntil('\r'));
  //  Serial.print("Before:"); Serial.println(i);
  i.remove(0, 5);
  //  Serial.print("first:"); Serial.println(i);

  i.remove(i.length() - 9, 9);
  g = i;
  //  Serial.print("Second:"); Serial.println(i);
  g.remove(1, g.length());
  //  Serial.print("G :"); Serial.println(g);
  if (g == "s")
  {
    i.remove(0, 1);
    Pump = i.toInt();
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    delay(20);
  }
  if (i == "T")
  {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println(TEMP);
    client.println("</html>");
    delay(20);
  }
  if (i == "P")
  {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println(PH);
    client.println("</html>");
    delay(20);
  }
  if (i == "W") {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println(ULTRASONIC);
    client.println("</html>");
    delay(20);
  }
  if (i == "F") {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println(FLOW);
    client.println("</html>");
    delay(20);
  }
  if (i == "Speed") {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println(Pump);
    //Serial.println(analogRead(A0));
    client.println("</html>");
    delay(20);
  }
  if (i == "Tur")
  {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println(NTU_equation);
    //Serial.println(analogRead(A0));
    client.println("</html>");
    delay(20);
  }
//  if (i == "X")
//  {
//    client.println("HTTP/1.1 200 OK");
//    client.println("Content-Type: text/html");
//    client.println("");
//    client.println("<!DOCTYPE HTML>");
//    client.println("<html>");
//    client.println(PrintedLine);
//    //Serial.println(analogRead(A0));
//    client.println("</html>");
//    delay(20);
//  }
  client.flush();
  delay(1);
  // EnableFlow();
  //  }
}
