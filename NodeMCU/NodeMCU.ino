/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on NodeMCU.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right NodeMCU module
  in the Tools -> Board menu!

  For advanced settings please follow ESP examples :
   - ESP8266_Standalone_Manual_IP.ino
   - ESP8266_Standalone_SmartConfig.ino
   - ESP8266_Standalone_SSL.ino

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <Blynk_SimpleEsp8266.h>
#include <SoftwareSerial.h>
SoftwareSerial s(D6,D5);

char auth[]="fs_2O0lgBtA9jfmxlUtZcta4HVwogPmW";

// Your WiFi credentials.
char ssid[]="vivo 1901";
char pass[]="5ff35479ef37";

void setup()
{
  // Debug console
  s.begin(9600);
  Serial.begin(9600);

  Blynk.begin(auth,ssid,pass);
  while (!Serial) 
  {
   ; 
  }
}


void loop()
{
  if(s.available()) 
  {
   Serial.println(s.read());
  }
  String Data=String (s.write(s.read()));
  int p = 0;
  for(int i=0;i<Data.length();i++)
  {
    if(Data[i] == ',')
    {
      p = i;
      break;
    }
  }
  String str1, str2;
  str1 = "";
  str2 = "";
  for (int i=0;i<p;i++)
  {
    str1 += Data[i];
  }
  for(int i=p;i<Data.length();i++)
  {
    str2 += Data[i];
  }
  int BPM = str1.toInt();
  int Temp = str2.toInt();
  Blynk.virtualWrite(V5, BPM);
  Blynk.virtualWrite(V6, Temp);     
  Blynk.run();
}
