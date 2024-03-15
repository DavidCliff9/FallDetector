/*
Derived from Yún HTTP Client Sketch

 This example for the Arduino Yún shows how create a basic
 HTTP client that connects to the internet and downloads
 content. In this case, you'll connect to the Arduino
 website and download a version of the logo as ASCII text.

 created by Tom igoe
 May 2013

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/HttpClient

 Additions added by Mary Loftus April 2018 
 - adapted from example by Tom DeBell - August 2017 - http://www.open-sensing.org/evaporometerblog/datalog
 */


  /////////////////
 // MODIFY HERE //
/////////////////

// Add your PushingBox Scenario DeviceID here:
  char devid[] = "v3AD745090CA36D0";
  
  //////////////
 //   End    //
//////////////

char serverName[] = "api.pushingbox.com";
boolean DEBUG = true;
#include "Arduino_SensorKit.h"
#include <Wire.h>
#include <Bridge.h>
#include <HttpClient.h>
#include "rgb_lcd.h"

 bool fallen = false;

 const int buttonPin = A0;  // the number of the pushbutton pin, in case the accel breaks
 int buttonState = 0;
 
 const int buzzerPin = A1;  // Verify the fallen state has gone through
 int buzzernState = 0;

 int colorR = 200;
 const int colorG = 0;
 int colorB = 0;


 rgb_lcd lcd;

void setup() {
  // Bridge takes about two seconds to start up
  // it can be helpful to use the on-board LED
  // as an indicator for when it has initialized
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH); 

  Accelerometer.begin();

  
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.begin(16, 2);
  
  lcd.setRGB(colorR, colorG, colorB);



  Serial.begin(9600);
  while (!Serial); // wait for a serial connection
}

void loop() {
  // Initialize the client library
  HttpClient client;

   Serial.print("x:"); 
  Serial.print(Accelerometer.readX());  // Read the X Value 
  Serial.print("  ");
  Serial.print("y:"); 
  Serial.print(Accelerometer.readY());  // Read the Y Value       
  Serial.print("  ");
  Serial.print("z:"); 
  Serial.println(Accelerometer.readZ());// Read the Z Value

  
  // buttonState = digitalRead(buttonPin);

  //Setup sensorValue to read a value from Analog Port A0
  
  
  //Testing value - when sensor is not connected - comment out when sketch is shown to be working - and take value from A0 instead
// int  sensorValue=1500;

  // Make a HTTP request:  
  String APIRequest;
  APIRequest = String(serverName) + "/pushingbox?devid=" + String(devid)+ "&IDtag=100&TimeStamp=50&TempC="+1;
  client.get (APIRequest); 
  
  // if there are incoming bytes available
  // from the server, read them and print them:

  if (buttonState == HIGH) {
  // Change state to fallen
  fallen = true;
}

if (fallen == true){
  
  lcd.clear();
  lcd.print("Medical Info");
  lcd.setCursor(0, 2);
  lcd.print("Calling 0838201985");
  
   // Make a HTTP request:  
  String APIRequest;
  APIRequest = String(serverName) + "/pushingbox?devid=" + String(devid)+ "&IDtag=100&TimeStamp=50&TempC="+1;
  client.get (APIRequest);

  Serial.print(APIRequest);

  
   tone(A1, 100);
  delay(100);
  noTone(A1);
 
  fallen = false;
} 
  
  while (client.available()) {
    char c = client.read();

     buttonState = digitalRead(buttonPin);


  } 
  Serial.flush();
  String UploadMessage;
  Serial.print("\n Uploaded temp value: ");
  Serial.print(fallen);
  delay(500);

  Serial.print(fallen);
}
