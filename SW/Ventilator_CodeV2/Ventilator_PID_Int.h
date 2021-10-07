#ifndef  _PID_
#define _PID_
/*
 * DO NOT Try to change anything in this code as it will lead to a failure in the controlling system
 * if you ar not for dealing with this kind of systems
 */
 //Struct contains all data needed to control the PID of a specific Object
struct PID_Library_var {
  int ID;
  double OutMax;
  double OutMin;
  double Input, Output, Setpoint;
  double ITerm, lastInput;
  double kp, ki, kd;
  double input_kp, input_ki, input_kd;
  unsigned long lastTime;
};
void PID_Init(double sensor_Kp, double sensor_Ki, double sensor_Kd, struct PID_Library_var *Sensor_var); // Initialise the control parameters
void SetOutputLimits(double Min, double Max, struct PID_Library_var *Sensor_var);               // Set the limits of the calculated error
void Initialize(struct PID_Library_var *Sensor_var);                                             // Initialize the object in the system
void SetTunings(struct PID_Library_var *Sensor_var);                                             // incase of want to change the (Kp,Ki,Kd) parameters
void SetMode(int Mode, struct PID_Library_var *Sensor_var);                                      // Set the mode of control (AUTOMATIC,MANUAL)
double GetPIDControlValue(double ControlInput, struct PID_Library_var *Sensor_var);                //calculate the value of the error
void SetControllerDirection(int Direction_);                                                          // The direction to determine the sign of the error
void Update_Setpoint(double Time_reading, struct PID_Library_var *Sensor_var);              //To change the value of the SETPOINT
void Get_FeedBack (int Feedback_Time,struct PID_Library_var *Sensor_var);                               // To save the value of the FEEDBACK
#endif _PID_
