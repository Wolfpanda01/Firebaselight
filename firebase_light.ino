//all of this set up for the m5stick,wifi and firebase and libaries needed to run it
// malia baker, class csc230,  using google firebase -IOXhop this to get firebase to work, and Arduinojson to make a led light
#include "info.h"
#include <WiFi.h>
#include <M5StickCPlus.h>
#include <IOXhop_FirebaseESP32.h>
#include <IOXhop_FirebaseStream.h>
#include <ArduinoJson.h>
//defines the LED as 10 beacause that is the pin on the M5stickCPlus
# define LED_BUILTIN 10
void setup() {
  //starting the stuff to run the serial monitor, M5stickplus commutation and wifi commutation
 Serial.begin(9600);
 delay(1000);
 pinMode(10,OUTPUT);
 WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
 Serial.print("Connecting to ");
 Serial.print(WIFI_SSID);
 while (WiFi.status()!= WL_CONNECTED){Serial.print(".");
 delay(500); 
 
 }
 M5.begin();
 Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 Firebase.setString("LED_STATUS", "OFF");
}


void loop() {
  //gets the stats of the led from the base and checks it
  String firestatus = Firebase.getString("LED_STATUS");
  
  //if it see the stats say off it will tell it to turn the led off and prints that it is turned off
  if(firestatus == "OFF"){
    Serial.println("LED Turned OFF");
    digitalWrite(LED_BUILTIN,HIGH);
    }
      //if it see the stats say on it will tell it to turn the led on and prints that it is turned on
  else if (firestatus == "ON"){
    Serial.println("LED turned ON");
    digitalWrite(LED_BUILTIN,LOW);
    }
    //if it see the stats say something that is not on or off it will prints that there is something wrong and to print on or off
  else {
    Serial.println("Wrong Credentials! Please send ON/OFF");
  }
}
