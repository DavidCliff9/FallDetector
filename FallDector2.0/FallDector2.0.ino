#include "Arduino_SensorKit.h"
#include <Wire.h>
#include <Bridge.h>
#include <HttpClient.h>
#include "rgb_lcd.h"
 
 bool fallen = false;
 
 char devid[] = "v3AD745090CA36D0";
 
 const int buttonPin = A0;  // the number of the pushbutton pin, in case the accel breaks
 int buttonState = 0;
 
 const int buzzerPin = A1;  // Verify the fallen state has gone through
 int buzzernState = 0;

   // const int AccelPin = I2C

 int delaytimer = 500;

 rgb_lcd lcd;

  int colorR = 200;
  const int colorG = 0;
  int colorB = 0;

  String bloodType = "21";

  char serverName[] = "api.pushingbox.com";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  
  Accelerometer.begin();

  
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.begin(16, 2);
  
  lcd.setRGB(colorR, colorG, colorB);

  

// char serverName[] = "api.pushingbox.com";
  boolean DEBUG = true;


  

}
 
void loop() {
  
   // Initialize the client library
  HttpClient client;

  while (client.available()) {
    char c = client.read();

    

  } 


  
  
  // put your main code here, to run repeatedly:
  // 3 axis
  Serial.print("x:"); 
  Serial.print(Accelerometer.readX());  // Read the X Value 
  Serial.print("  ");
  Serial.print("y:"); 
  Serial.print(Accelerometer.readY());  // Read the Y Value       
  Serial.print("  ");
  Serial.print("z:"); 
  Serial.println(Accelerometer.readZ());// Read the Z Value

  // API Request
  
  String APIRequest;
  APIRequest = String(serverName) + "/pushingbox?devid=" + String(devid)+ "&IDtag=100&TimeStamp=50&TempC="+1;
  client.get (APIRequest);

 
  delay(500);

  buttonState = digitalRead(buttonPin);

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

  
  // tone(A1, 100);
  delay(100);
  noTone(A1);
 
  fallen = false;

  // delaytimer = 100000; // Pause the function of the device

  // Text repeats, have a look at the loop
 
}

  Serial.flush();
  String UploadMessage;
  Serial.print("\n Uploaded temp value: ");
  Serial.print(fallen);
  
}
