
/*  Getting_BPM_to_Monitor prints the BPM to the Serial Monitor, using the least lines of code and PulseSensor Library.
 *  Tutorial Webpage: https://pulsesensor.com/pages/getting-advanced
 *
--------Use This Sketch To------------------------------------------
1) Displays user's live and changing BPM, Beats Per Minute, in Arduino's native Serial Monitor.
2) Print: "♥  A HeartBeat Happened !" when a beat is detected, live.
2) Learn about using a PulseSensor Library "Object".
4) Blinks LED on PIN 13 with user's Heartbeat.
--------------------------------------------------------------------*/

#define USE_ARDUINO_INTERRUPTS true    
#include <PulseSensorPlayground.h>    

// First we include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

#define ONE_WIRE_BUS 7 

OneWire oneWire(ONE_WIRE_BUS); 

DallasTemperature sensors(&oneWire);


//  Variables
const int PulseWire = 0;       
const int LED13 = 13;          
int Threshold = 550;           
String BPM = "" ;
String Temp = "" ;                               
                               
PulseSensorPlayground pulseSensor;  
SoftwareSerial NodeMCU(5,6);

void setup() {   

  Serial.begin(9600);         
  NodeMCU.begin(9600);
 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);      
  pulseSensor.setThreshold(Threshold);   


   if (pulseSensor.begin()) {
    Serial.println("Object created !");   
  }
  
  sensors.begin(); 
}



void loop() {

 int myBPM = pulseSensor.getBeatsPerMinute();  
                                               
 Current_BPM = String(myBPM);                                               

if (pulseSensor.sawStartOfBeat()) {            
 Serial.println("Value_BPM , Value_temp"); 
 Serial.print("BPM: ");                         
 Serial.println(myBPM);                       
}

  delay(20);                    
 Serial.print("Requesting temp."); 
 sensors.requestTemperatures(); 
 Serial.println("DONE"); 

 Serial.print("Temperature : "); 
 Serial.print(sensors.getTempCByIndex(0));  
 int T =  sensors.getTempCByIndex(0)
 Current_Temp = String(T);
 NodeMCU.println(BPM + "," + Temp);   
   delay(1000);
}

  
