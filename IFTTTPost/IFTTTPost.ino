/*
  Running process using Process class.

 This sketch demonstrate how to run linux processes
 using an Arduino Yún.

 created 5 Jun 2013
 by Cristian Maglie

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Process

 */

#include <Process.h>

void setup() {
  // Initialize Bridge
  Bridge.begin();

  // Initialize Serial
  Serial.begin(9600);

  // Wait until a Serial Monitor is connected.
  while (!Serial);

  pinMode(3,INPUT_PULLUP);
}

void loop() {
  // Do nothing here.
  if(digitalRead(3) == LOW){
    runCurl();
    delay(1000);
  }
}

void runCurl() {
  // Launch "curl" command and get Arduino ascii art logo from the network
  // curl is command line program for transferring data using different internet protocols
  Process p;		// Create a process and call it "p"
  p.begin("curl");	// Process that launch the "curl" command
  p.addParameter("<ifttt url>"); // Add the URL parameter to "curl"
  p.run();		// Run the process and wait for its termination

  // Print arduino logo over the Serial
  // A process output can be read with the stream methods
  while (p.available() > 0) {
    char c = p.read();
    Serial.print(c);
  }
  // Ensure the last bit of data is sent.
  Serial.flush();
}
