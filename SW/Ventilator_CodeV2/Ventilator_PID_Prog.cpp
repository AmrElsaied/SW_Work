#include "Ventilator_PID_Int.h"
#include "Ventilator_PID_Priv.h"
#include <Arduino.h>

//Some USED variables
int SampleTime = 50; //20
bool inAuto = false;
int controllerDirection = DIRECT;
extern double BREATH_PER_MINUETE ;
extern double INSPIRATION ;
extern double EXPIRATION ;
extern double Cycle_PID ;
extern double TIME_I_PID ;
extern double PID_SETPOINT ;
PID_Library_var Motor_PID;
PID_Library_var Pressure_PID;

void Initialize(struct PID_Library_var *Sensor_var)
{
  Sensor_var->lastInput = Sensor_var->Input;
  Sensor_var->ITerm = Sensor_var->Output;
  if (Sensor_var->ITerm > Sensor_var->OutMax) Sensor_var->ITerm = Sensor_var->OutMax;
  else if (Sensor_var->ITerm < Sensor_var->OutMin) Sensor_var->ITerm = Sensor_var->OutMin;
}

void PID_Init(double sensor_Kp, double sensor_Ki, double sensor_Kd, struct PID_Library_var *Sensor_var)
{
  SetMode(AUTOMATIC, &Motor_PID);
  Sensor_var->input_kp = sensor_Kp;
  Sensor_var->input_ki = sensor_Ki;
  Sensor_var->input_kd = sensor_Kd;
  if (Sensor_var->ID == DC_MOTOR_ID)
  {
    SetOutputLimits(-255, 255, Sensor_var);
  }
  else if (Sensor_var->ID == Pressure_ID)
  {
    SetOutputLimits(-5000, 5000, Sensor_var);
  }
}

void SetControllerDirection(int Direction_)
{
  controllerDirection = Direction_;
}

void SetOutputLimits(double Min, double Max, struct PID_Library_var *Sensor_var)
{
  if (Min > Max) return;
  Sensor_var->OutMin = Min;
  Sensor_var->OutMax = Max;

  if (Sensor_var->Output > Sensor_var->OutMax) Sensor_var->Output = Sensor_var->OutMax;
  else if (Sensor_var->Output < Sensor_var->OutMin) Sensor_var->Output = Sensor_var->OutMin;

  if (Sensor_var->ITerm > Sensor_var->OutMax) Sensor_var->ITerm = Sensor_var->OutMax;
  else if (Sensor_var->ITerm < Sensor_var->OutMin) Sensor_var->ITerm = Sensor_var->OutMin;
}
void Compute(struct PID_Library_var *Sensor_var)
{
  if (!inAuto) {
    Sensor_var->Output = 0;
    return;
  }
  unsigned long now = millis();
  long int timeChange = (now - Sensor_var->lastTime);
  if (timeChange >= SampleTime)
  {
    //    Serial.println(Sensor_var->lastTime);
    //    Serial.println("***************************************************************************");
    /*Compute all the working error variables*/
    double error = Sensor_var->Setpoint - Sensor_var->Input;
    Sensor_var->ITerm += (Sensor_var->ki *  error);
    if (Sensor_var->ITerm > Sensor_var->OutMax) Sensor_var->ITerm = Sensor_var->OutMax;
    else if (Sensor_var->ITerm < Sensor_var->OutMin) Sensor_var->ITerm = Sensor_var->OutMin;
    double dInput = (Sensor_var->Input - Sensor_var->lastInput);
    /*Compute PID Output*/

    Sensor_var->Output = Sensor_var->kp * error + Sensor_var->ITerm - Sensor_var->kd * dInput;

    if (Sensor_var->Output > Sensor_var->OutMax) Sensor_var->Output = Sensor_var->OutMax;
    else if (Sensor_var->Output < Sensor_var->OutMin) Sensor_var->Output = Sensor_var->OutMin;
    //Serial.println(Sensor_var->Output);
#if PRINT_LastInput == TRUE
    Serial.print("Last_Input in compute: ");
    Serial.println(Sensor_var->lastInput);
#endif
    /*Remember some variables for next time*/
    Sensor_var->lastInput = Sensor_var->Input;
    Sensor_var->lastTime = now;
    // print lastInput for next time
#if PRINT_LastInput_Next_Time == TRUE
    Serial.print("LastInput_next_step: ");   // equal to Input
    Serial.println(Sensor_var->lastInput);
#endif
    // print K parameters
#if PRINT_K_PARAMETERS == TRUE
    Serial.print("Kp: ");
    Serial.print(Sensor_var->kp);
    Serial.print("\t Ki: ");
    Serial.print(Sensor_var->ki);
    Serial.print("\t Kd: ");
    Serial.println(Sensor_var->kd);
#endif
    // print error without direction
#if PRINT_ERROR_COMPUTE == TRUE
    Serial.print("Error_compute: ");
    Serial.println( error);
#endif
    // print: ITerm, dInput, output
#if PRINT_OUTPUT_PARAMETERS == TRUE
    Serial.print("ITerm:");
    Serial.print(Sensor_var->ITerm);
    Serial.print("\t dInput: ");
    Serial.print(Sensor_var->kd * dInput);
    Serial.print("\t Output:");
    Serial.println(Sensor_var->Output);
#endif
  }
}

void SetTunings(struct PID_Library_var *Sensor_var)
{
  if (Sensor_var->input_kp < 0 || Sensor_var->input_ki < 0 || Sensor_var->input_kd < 0) return;

  double SampleTimeInSec = ((double)SampleTime) / 1000;
  Sensor_var->kp = Sensor_var->input_kp;
  Sensor_var->ki = Sensor_var->input_ki * SampleTimeInSec;
  Sensor_var->kd = Sensor_var->input_kd / SampleTimeInSec;


  if (controllerDirection == REVERSE)
  {
    Sensor_var->kp = (0 - Sensor_var->kp);
    Sensor_var->ki = (0 - Sensor_var->ki);
    Sensor_var->kd = (0 - Sensor_var->kd);
  }
}

void SetMode(int Mode, struct PID_Library_var *Sensor_var)
{
  bool newAuto = (Mode == AUTOMATIC);
  if (newAuto == !inAuto)
  { /*we just went from manual to auto*/
    Initialize(Sensor_var);
  }
  inAuto = newAuto;
}

double GetPIDControlValue(double ControlInput, struct PID_Library_var *Sensor_var) {
  int dirc = 0;
  // If input is negative, corrective output should be positive
  if (ControlInput < 0) {
    SetControllerDirection(DIRECT);
    dirc = 1;
  }
  else
  {
    // If input is positive, corrective output should be negative
    SetControllerDirection(REVERSE);
    dirc = -1;
  }
  SetTunings(Sensor_var);
  Compute(Sensor_var);
  return dirc * (Sensor_var->Output);
}

void Update_Setpoint(double Time_reading, struct PID_Library_var *Sensor_var) {
  if (Sensor_var->Setpoint != Time_reading)
  {
    Sensor_var->Setpoint = Time_reading;
    Sensor_var->Input = Time_reading;
  }
  else;

}

void Get_FeedBack (int Feedback_Time, struct PID_Library_var *Sensor_var)
{
  Sensor_var->Input = Feedback_Time;
}

