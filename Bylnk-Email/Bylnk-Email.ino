/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * Simple e-mail example
 *
 * App dashboard setup:
 *   E-mail Widget
 *
 * Connect a button to digital pin 2 and GND
 * Pressing this button will send an e-mail
 *  
 * WARNING: You are limited to send ONLY ONE E-MAIL PER MINUTE!
 *
 **************************************************************/
#define BLYNK_PRINT Serial
#include <Bridge.h>
#include <BlynkSimpleYun.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

int flg = 0;

void setup()
{
  Serial.begin(9600);
  // Wait for the Serial port to connect
  while(!Serial);
  
  Blynk.begin(auth);

  while (Blynk.connect() == false) {
    // Wait until connected
  }
  
  // Setting the button
  pinMode(3, INPUT_PULLUP);
  // Attach pin 3 interrupt to our handler
  attachInterrupt(digitalPinToInterrupt(3), emailOnButtonPress, FALLING);
}

void emailOnButtonPress()
{
  // *** WARNING: You are limited to send ONLY ONE E-MAIL PER MINUTE! ***
  
  // Let's send an e-mail when you press the button 
  // connected to digital pin 3 on your Arduino
  
  int isButtonPressed = !digitalRead(3); // Invert state, since button is "Active LOW"
  
  if (isButtonPressed) // You can write any condition to trigger e-mail sending
  {
    Serial.println("Button is pressed."); // This can be seen in the Serial Monitor
    if(flg == 0){
      flg = 1;
    }
  }
}

void loop()
{
  Blynk.run();
  if(flg == 1){
    Blynk.email("<your email>", "Subject: Button Logger", "You just pushed the button...");
    delay(1000);
    flg = 0;
  }
}

