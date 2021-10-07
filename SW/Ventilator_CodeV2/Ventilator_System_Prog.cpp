#include "Ventilator_System_Int.h"
#include "Ventilator_System_Priv.h"
#include "Ventilator_PID_Int.h"
#include "Pressure_Int.h"
#include <AccelStepper.h>

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

//IMPORTANT VARIABLES FOR THE SYSTEM SO.... DO NOT TRY TO PLAY with IT
int Speed = Begin_SPEED;
int Speed_1 = Begin_SPEED;
long int Recieved_Time = 0;
long int Start_Loop_Time = 0;
long int LOW_MOTOR_TIME_Start = 0;
long int LOW_MOTOR_TIME = 0;
long int TOTAL_Time = 0;
bool ON_FLAG = TRUE;
bool Valid_Cycle = FALSE;
bool Start_Loop_Lock = FALSE;
bool LOW_MOTOR_TIME_Start_Lock = FALSE ;
bool Present_Reading = HIGH;
bool Last_Reading = HIGH ;
bool System_Homming_Flag = FALSE;
extern double EXPIRATION ;
bool Relay_Flag = false;
extern bool ff;
///------------------PID Variables
double  MOTOR_Kp = .09, MOTOR_Ki = 0, MOTOR_Kd = .0002;
double  Pressure_Kp = 800, Pressure_Ki = 0, Pressure_Kd = 0;
extern double PID_SETPOINT;
extern int Pressure_PID_SETPOINT;
extern PID_Library_var Motor_PID;
extern PID_Library_var Pressure_PID;
double PID_ERROR = 0;
extern double Cycle ;
extern double TIME_I ;
extern double TIME_E ;
extern double  Motor_Time_ON;
extern double Motor_Time_OFF;
float Pressure_Present_Reading = 0;
float Pressure_Max_Reading = 0;
int Pressure_Error = 0;

//-------------------Steper Variable
AccelStepper stepper (1, 7, 6);
extern long int TOTAL_TAKED_STEPS;
bool Pressure_Cycle_Enter = FALSE;
bool Stepper_END = FALSE;
long int STEPPER_STEPS = 0;
long int Reset_EEPROM = 0;
//--------------
extern double BREATH_PER_MINUETE ;
extern double INSPIRATION ;
extern double EXPIRATION ;

volatile int LOW_FLAG = FALSE;
bool Ended_LOOP = FALSE;
// Configure the PINS in the (Ventilator_System_Priv.h) File
void Ventilator_Init (void) // Initialize the Pins of the Motor and other needed PINS
{
  myservo.attach(20);  // attaches the servo on pin 9 to the servo object
  Motor_PID.ID = DC_MOTOR_ID;
  Pressure_PID.ID = Pressure_ID;
  Serial.begin(9600);
  //   pinMode (MOTOR_FEEDBACK_PIN, INPUT_PULLUP);
  pinMode (MOTOR_FEEDBACK_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(MOTOR_FEEDBACK_PIN), FIRE_FLAG, FALLING);
  pinMode (MOTOR_DIR_PIN, OUTPUT);
  pinMode (MOTOR_PWM_PIN, OUTPUT);
  pinMode(RELAY_PIN, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite (RELAY_PIN, LOW);
  digitalWrite (MOTOR_DIR_PIN, LOW);
  analogWrite(MOTOR_PWM_PIN, STOP);
  PID_Init(MOTOR_Kp, MOTOR_Ki, MOTOR_Kd, &Motor_PID);
  PID_Init(Pressure_Kp, Pressure_Ki, Pressure_Kd, &Pressure_PID);
  Stepper_Init();
  Pressure_Init();
  //EEPROM.put(0, Reset_EEPROM);
  //EEPROM.get(0, TOTAL_TAKED_STEPS);
  // Serial.print("Total taked Steps AT START : ");Serial.println(TOTAL_TAKED_STEPS);
}

void Ventilator_Start (void)
{
  Cycle = (60 / BREATH_PER_MINUETE);
  TIME_I = ((Cycle / (INSPIRATION + EXPIRATION)) * INSPIRATION);
  TIME_E = (Cycle / (INSPIRATION + EXPIRATION)) * EXPIRATION;
  Motor_Time_ON = (TIME_I * 2) * 1000;
  Motor_Time_OFF = (TIME_E - TIME_I) * 1000;
  Update_Setpoint (Motor_Time_ON, &Motor_PID);
  Update_Setpoint (Pressure_PID_SETPOINT, &Pressure_PID);

  //  Serial.print("ITOE_SETPOINT: "); Serial.println (Motor_PID. Setpoint );
  //  Serial.print("PRESSURE SETPOINT: "); Serial.println (Pressure_PID. Setpoint );
  static int Work_STATE = WORK_STATE_ON;
  Motor_Time_NOW = millis();
  if ((((((Motor_Time_NOW - Motor_Last_Time_OFF) ) >= Motor_Time_ON) && Work_STATE == WORK_STATE_ON) || ON_FLAG == FALSE) && (Valid_Cycle == TRUE))
  {
    Work_STATE = WORK_STATE_OFF;
    Motor_Last_Time_ON = Motor_Time_NOW;
    ON_FLAG = TRUE;
    Start_Loop_Lock = FALSE;
    LOW_MOTOR_TIME_Start_Lock = FALSE;
  }

  else if (((((Motor_Time_NOW - Motor_Last_Time_ON) ) >= Motor_Time_OFF) && Work_STATE == WORK_STATE_OFF) && Valid_Cycle == TRUE && Pressure_Cycle_Enter == TRUE)
  {
    Work_STATE = WORK_STATE_ON;
    Motor_Last_Time_OFF = Motor_Time_NOW;
    Valid_Cycle = FALSE;
    Pressure_Cycle_Enter = FALSE;
    Relay_Flag  = false;
    //Stepper_END = FALSE;
  }
  else
  {}
  if (Stepper_END)
  {
    Stepper_END = FALSE;
  }
  Determine_STATE (Work_STATE);
}
void Determine_STATE (int state)
{
  switch (state)
  {
    case WORK_STATE_ON:
      Ventilator_ON();
      break;
    case WORK_STATE_OFF:
      Ventilator_OFF ();
      break;
    default:
      Serial.println("ERROR !!");
      break;
  }
}

void Ventilator_OFF (void)
{

  if (Relay_Flag == false)
  {
    digitalWrite (RELAY_PIN, HIGH);
    myservo.write(90);
    Relay_Flag = true;
  }

#if (ON_OFF_SIGNAL == TRUE)
  Serial.println("IAM IN OFF STATE !!");
#endif
  //Turn off the motor
  if (EXPIRATION > 1)
  {
    analogWrite(MOTOR_PWM_PIN, STOP);
  }
  else {}
  // Measure the error of pressure
  if (!Pressure_Cycle_Enter)
  {
    Get_FeedBack(Pressure_Max_Reading, &Pressure_PID);
    Pressure_Error = GetPIDControlValue(POSITIVE_DIR, &Pressure_PID);
    STEPPER_STEPS = (-Pressure_Error);// Pressure_Error;


    if (TOTAL_TAKED_STEPS >= MAX_STEPS || TOTAL_TAKED_STEPS <= MIN_STEPS)
    {
      //TOTAL_TAKED_STEPS -= STEPPER_STEPS;
      STEPPER_STEPS = 0;
    }

#if (STEPPER_STEPS_SIGNAL == TRUE)
    Serial.print("STEPPER_STEPS: "); Serial.println(STEPPER_STEPS);
    Serial.print("TOTAL_STEPS: "); Serial.println(TOTAL_TAKED_STEPS);
#endif
    //EEPROM.put(0, TOTAL_TAKED_STEPS);
    Pressure_Cycle_Enter = TRUE;
  }

  //Stepper_END = TRUE;
  Stepper_Move (STEPPER_STEPS, 40000);
  // Move the motor till its new position
  //must wait till it finished and wait till the time of OFF_Cycle end
}

void Stepper_Init(void)
{
  stepper.setMaxSpeed(32000);
}

void Stepper_Move (int Place , int iteration)
{
  int Current_Position;
  if (!Stepper_END)
  {

    for (long int i = 0; i < 20000 ; i++)
    {
      stepper.moveTo(Place);
      stepper.setSpeed(Stepper_Speed);
      stepper.runSpeedToPosition();
    }
    //    Serial.println("kkkkkkkkkkkkkkkkkkkkkkkkkkkkk");
    Current_Position = stepper.currentPosition();

    //  Serial.print("Stepper_Position: "); Serial.println(Current_Position);
    //    Serial.println("kkkkkkkkkkkkkkkkkkkkkkkkkkkkk");

    if (Place >= 0)
    {
      if (Current_Position >= Place)
      {
        TOTAL_TAKED_STEPS += Current_Position;
        stepper.stop();
        stepper.setCurrentPosition(0);
        Stepper_END = TRUE;
      }
    }
    else if (Place <= 0)
    {
      if (Current_Position <= Place)
      {
        TOTAL_TAKED_STEPS += Current_Position;
        stepper.stop();
        stepper.setCurrentPosition(0);
        Stepper_END = TRUE;
      }
    }
    else {};
  }
}

void Ventilator_Homming (void)
{
  static bool Homming_Switch = TRUE;
  static bool Valid_Homming = FALSE;
  static bool RuntoPosition = FALSE;
  static bool Valid_BacktoPostion = FALSE;
  //Homming_Switch = digitalRead() //switch pin
  if (! Valid_Homming )
  {
    if (Homming_Switch)
    {
      // Move to home
    }
    else if (!Homming_Switch)  //Active LOW
    {
      //Stop the stepper
      Valid_Homming = TRUE;
      RuntoPosition = TRUE;
    }
  }

  if (! Valid_BacktoPostion )
  {

    if (Valid_BacktoPostion)
    {
      // Run to the last position "Total_Steps"
      if (Valid_BacktoPostion) // backed to the last position again
      {
        Valid_BacktoPostion = TRUE;
        System_Homming_Flag = TRUE;
      }
    }
  }
}

void Ventilator_ON (void)
{

  if (ON_FLAG == TRUE)
  {
    if (Relay_Flag == false)
    {
      digitalWrite (RELAY_PIN, LOW);
      Relay_Flag = true;
    }
#if (ON_OFF_SIGNAL == TRUE)
    Serial.println("IAM IN ON STATE !!");
#endif
    // To make sure that the system didn't get overlimits
    if (Speed >= 250) Speed = 250;
    else if (Speed <= 80) Speed = 80;
    analogWrite(MOTOR_PWM_PIN, Speed);
#if (SPEED_SIGNAL == TRUE)
    Serial.print("Speed 1: "); Serial.println(Speed_1);
    Serial.print("Speed 2: "); Serial.println(Speed);
#endif
    if (Start_Loop_Lock == FALSE)
    {
      myservo.write(90);
      Start_Loop_Time = millis();
      Pressure_Max_Reading = 0;
      Pressure_Present_Reading = 0;
      Start_Loop_Lock = TRUE;
      ff = true;
    }
    //Take the Reading of pressure sensor "The highest value"

    Pressure_Present_Reading = Pressure_Reading ();//map (analogRead(A0),0,1023,0,40); // CAll the function of the pressure sensor
    if (Pressure_Present_Reading > Pressure_Max_Reading)
    {
      Pressure_Max_Reading = Pressure_Present_Reading;
    }
    //Pressure_Max_Reading = Pressure_Present_Reading;
#if (Pressure_SIGNAL == TRUE)
    Serial.print("Current Pressure Read: "); Serial.println(Pressure_Present_Reading);
    Serial.print("MAX Pressure Read: "); Serial.println(Pressure_Max_Reading);
#endif
    //Present_Reading = digitalRead(MOTOR_FEEDBACK_PIN);
    if ( LOW_FLAG == TRUE && !digitalRead(MOTOR_FEEDBACK_PIN) && Recieved_Time > 500)
    {
      LOW_FLAG = FALSE;
      Ended_LOOP = TRUE;
    }
    else
    {
      Recieved_Time = (millis () - Start_Loop_Time);
    }
    //    Recieved_Time = (millis () - Start_Loop_Time);
    //    if (Recieved_Time > 1600)
    //    {
    //      if ( LOW_FLAG == TRUE)
    //      {
    //        LOW_FLAG = FALSE;
    //        Ended_LOOP = TRUE;
    //      }
    //      else {}
    //    }
    if ( (Ended_LOOP == TRUE) && Recieved_Time > 200)
    {
      Serial.println("-----------------------------------------");
      Serial.print("Recieved Time: "); Serial.println(Recieved_Time);
      Serial.println("-----------------------------------------");
      LOW_MOTOR_TIME_Start_Lock = FALSE;
      LOW_FLAG = FALSE;
      Ended_LOOP = FALSE;
      if (EXPIRATION <= 2)
      {
        TOTAL_Time = Recieved_Time + 300;
      }
      else
      {
        TOTAL_Time = Recieved_Time + 500;
      }
      Last_Reading = HIGH ;
      ON_FLAG = FALSE;
      Valid_Cycle = TRUE;
      Get_FeedBack(TOTAL_Time, &Motor_PID);
      PID_ERROR = GetPIDControlValue(POSITIVE_DIR, &Motor_PID);
      Relay_Flag = false;
      Speed_1 = Speed;
      Speed = Speed - PID_ERROR;
      ff = false;
      if (Recieved_Time >= Valid_Cycle_Threshold)
      {
        Serial.println("******************************************");

      }
#if (RECIEVED_TIME_SIGNAL == TRUE)
      Serial.println("-----------------------------------------");
      Serial.print("TOTAL Recieved Time: "); Serial.println(TOTAL_Time);
      Serial.println("-----------------------------------------");
#endif
#if (PID_ERROR_SIGNAL == TRUE)
      Serial.print("ERROR: "); Serial.println(PID_ERROR);
#endif
      Recieved_Time = 0;
    }
  }
}

void FIRE_FLAG (void)
{
  LOW_FLAG = TRUE;

}
