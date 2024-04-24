/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL4xRAoL_mD"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "kD4DgVsILdwhfyKb1mncZwyK5VKXKlao"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

  char devid[] = "v3AD745090CA36D0";

  char serverName[] = "api.pushingbox.com";
boolean DEBUG = true;
#include "Arduino_SensorKit.h"
#include <Wire.h>
// #include <Bridge.h>
#include <HttpClient.h>
#include "rgb_lcd.h"


#include <Bridge.h>
#include <BlynkSimpleYun.h>


BlynkTimer timer;

int velocity = 20;
int velocityHolder[5];
int counter = 0;

 int colorR = 200;
 const int colorG = 0;
 int colorB = 0;

   HttpClient client;


 rgb_lcd lcd;

int speedThreshold = 15;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
  if (value==1) {
    digitalWrite(13,HIGH);
  }

if (value==0){
  digitalWrite(13,LOW);
  
  }

  
}

BLYNK_WRITE(V4){
  velocity = param.asInt();

    // Update state
  Blynk.virtualWrite(V4, velocity);

  // Serial.print(velocity);

  // Serial.print(counter);

  velocityHolder[counter] = velocity;

  counter++;

  if (counter == 6){
    counter = 0;
  }
  
  dataReading(velocity);
}

// BLYNK_WRITE(V5)


// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup()
{

  for(int i = 0; i < 5; i++){
    velocityHolder[i] = 5;
  }
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);

   lcd.begin(16, 2);
  
  lcd.setRGB(colorR, colorG, colorB);
}

void loop()
{
  Blynk.run();
  timer.run();




  /*if (velocity == 0){
    Serial.print("Bro died");
  } */
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!

    while (client.available()) {
    char c = client.read();

     //buttonState = digitalRead(buttonPin);


  } 
  Serial.flush();
  String UploadMessage;
  //Serial.print("\n Uploaded temp value: ");
 // Serial.print(fallen);
 // delay(500);
}

  static void UpdateSpreadSheet(){
    String APIRequest;
  APIRequest = String(serverName) + "/pushingbox?devid=" + String(devid)+ "&IDtag=100&TimeStamp=50&TempC="+"1";
  client.get (APIRequest); 
  }



static void dataReading(int data){


  int temp = 0;
  int phase = 0;
  int tempPhase1 = 0;

  for(int i = 0; i < 5; i++){

  temp = velocityHolder[i];
  Serial.print(temp);

  if (temp > speedThreshold){ // Phase 1, Possible Fall
    phase = 1;
        Serial.print("Phase 1");
       tempPhase1 = temp;
       
  }

  if (phase == 1 && data < speedThreshold - 14) {
    phase = 0;
    UpdateSpreadSheet();
    Serial.print("Fall Detected");

    lcd.clear();
  lcd.print("Medical Info");
  lcd.setCursor(0, 2);
  lcd.print("Calling 0838201985");

    
    
    
  }

  }

}

  
 /* else if (phase == 1 && temp > speedThreshold - 5){
    phase = 0;s
  }

  if (phase == 2 && temp < 1) {
    Serial.print("bro died");
    phase = 0;
  }
  else if (phase == 2 && temp > 1){
    phase = 0;
  } */
  


  
// }
