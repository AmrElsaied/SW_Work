

/*
   NOTE 1: To EDIT THE SYSTEM TIME CONDITIONS:
   YOU CAN FIND (BREATHE PER MINUETE & INIPIRATION TO EXPIRATION RATIO IN (Ventilator_Config.h) FILE
   NOTE 2: THE NORMAL USER CAN NOT CHANGE ANYTHING RATHER THAN THAT !!!!!!!
   NOTE 3: FOR DEVELOPERS and WHO ARE FAMILIAR WITH CODING YOU CAN CHANGE THE HARDWARE PINS
   YOU WILL FIND THEM IN THE (Ventilator_System_Priv.h) FILE UNDER THE SECTION OF:
   (---Configuration of the SYSTEM HARDWARE---)
   NOTE 4: TRY NOT TO CHANGE IN THE STRUCTURE OR FLOW OF THE CODE UNLESS YOU ARE FAMILIAR WITH THESE KINDS OF SYSTEMS
*/
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <avr/dtostrf.h>
#include "Ventilator_System_Int.h"

#define ITOE_Topic                              "ventelator/ITOE"
#define ITOE_RPI_ACK_Topic                      "ventelator/ITOE/RPI/ACK"
#define Bpm_Topic                               "ventelator/Bpm"
#define Bpm_RPI_ACK_Topic                       "ventelator/Bpm/RPI/ACK"
#define VT_Topic                                "ventelator/VT"
#define VT_RPI_ACK_Topic                        "ventelator/VT/RPI/ACK"
#define Peak_Topic                              "ventelator/Peak"
#define Peak_RPI_ACK_Topic                      "ventelator/Peak/RPI/ACK"
#define Pressure_Present_Reading_ACK_TOPIC      "ventelator/Pressure_present_Reading/RPI/ACK"
#define Pressure_Max_Reading_ACK_TOPIC          "ventelator/Pressure_Max_Reading/RPI/ACK"

double BREATH_PER_MINUETE  = 20;
double INSPIRATION = 1 ;
double EXPIRATION = 2 ;
long now = millis();
long LastReading = 0;
long LastReading_Pressure = 0;
extern float Pressure_Present_Reading;
extern float Pressure_Max_Reading ;
int Pressure_PID_SETPOINT  = 10;
extern bool LOW_FLAG;
bool ff = false;

// Update these with values suitable for your hardware/network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 2, 60);
IPAddress server(192, 168, 2, 16);


EthernetClient ethClient;
PubSubClient client(ethClient);

void callback(char* topic, byte* payload, unsigned int length) {
  String messageTemp;
  for (int i = 0; i < length; i++) {
    messageTemp += (char)payload[i];
  }
  if ((strcmp(topic , ITOE_Topic) == 0))
  {
    EXPIRATION = messageTemp.toFloat();
    static char Temp[7];
    dtostrf(EXPIRATION, 2, 1, Temp);
    client.publish(ITOE_RPI_ACK_Topic , Temp);
    Serial.println(EXPIRATION);
  }
  if ((strcmp(topic , Bpm_Topic) == 0)) {

    BREATH_PER_MINUETE = messageTemp.toInt();
    static char Temp[7];
    dtostrf(BREATH_PER_MINUETE, 2, 0, Temp);
    client.publish(Bpm_RPI_ACK_Topic , Temp);
  }
  if ((strcmp(topic , Peak_Topic) == 0)) {
    Pressure_PID_SETPOINT = messageTemp.toInt();
    static char Temp[7];
    dtostrf(Pressure_PID_SETPOINT, 2, 0, Temp);
    client.publish(Peak_RPI_ACK_Topic , Temp);
  }
 }


long lastReconnectAttempt = 0;

boolean reconnect() {
  if (client.connect("arduinoClient")) {
    {
      static char Temp[7];
      dtostrf(Pressure_Present_Reading, 2, 0, Temp);
      client.publish(Pressure_Present_Reading_ACK_TOPIC , Temp);
    }
    
    {
      static char Temp[7];
      dtostrf(Pressure_Max_Reading, 2, 0, Temp);
      client.publish(Pressure_Max_Reading_ACK_TOPIC , Temp);
    }
    
    {
      static char Temp[7];
      dtostrf(EXPIRATION, 2, 1, Temp);
      client.publish(ITOE_RPI_ACK_Topic , Temp);
    }
    
    {
      static char Temp[7];
      dtostrf(BREATH_PER_MINUETE, 2, 0, Temp);
      client.publish(Bpm_RPI_ACK_Topic , Temp);
    }
    
    {
      static char Temp[7];
      dtostrf(Pressure_PID_SETPOINT, 2, 0, Temp);
      client.publish(Peak_RPI_ACK_Topic , Temp);
    }
      // ... and resubscribe
      client.subscribe("ventelator/#");
  }
  return client.connected();
}

void setup()
{
  Ventilator_Init ();
  client.setServer(server, 1883);
  client.setCallback(callback);

  Ethernet.begin(mac, ip);
  delay(1500);
  lastReconnectAttempt = 0;
}


void loop()
{
  if (!client.connected()) {
    Serial.println("Not Connected !");
    long now = millis();
    if (ff == false)
    {
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
   }
  } else {
    // Client connected
    Serial.println("Connected !");
          now = millis();
  if((now - LastReading_Pressure) >= 500){
    {
      static char Temp[7];
      dtostrf(Pressure_Present_Reading, 2, 0, Temp);
      client.publish(Pressure_Present_Reading_ACK_TOPIC , Temp);
    }
    
    {
      static char Temp[7];
      dtostrf(Pressure_Max_Reading, 2, 0, Temp);
      client.publish(Pressure_Max_Reading_ACK_TOPIC , Temp);
    }
    LastReading_Pressure = now;  
  }
  
  now = millis();
  if((now - LastReading) >= 15000){
    
    {
      static char Temp[7];
      dtostrf(EXPIRATION, 2, 1, Temp);
      client.publish(ITOE_RPI_ACK_Topic , Temp);
    }
    
    {
      static char Temp[7];
      dtostrf(BREATH_PER_MINUETE, 2, 0, Temp);
      client.publish(Bpm_RPI_ACK_Topic , Temp);
    }
    
    {
      static char Temp[7];
      dtostrf(Pressure_PID_SETPOINT, 2, 0, Temp);
      client.publish(Peak_RPI_ACK_Topic , Temp);
    }
    LastReading = now;  
  }
    client.loop();
  }
  Ventilator_Start () ;
  Serial.println(BREATH_PER_MINUETE);
}
