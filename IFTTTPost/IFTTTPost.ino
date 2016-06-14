#include <Process.h>

char incomingByte; 

void setup() {
  // Initialize Bridge
  Bridge.begin();

  // Initialize Serial
  Serial.begin(9600);

  // Wait until a Serial Monitor is connected.
  while (!Serial);
  
  Serial.println("type E to send Email"); 
}

void loop() {
  // Do nothing here.
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.println(incomingByte);
    if (incomingByte == 'E') {
      runCurl();
      delay(1000);
    }
  }
}

void runCurl() {
  Process p;
  p.begin("curl");
  p.addParameter("http://maker.ifttt.com/trigger/button_pressed/with/key/{key}?value1={value1}&value2={value2}&value3={value3}");
  p.run();

  // Print arduino logo over the Serial
  // A process output can be read with the stream methods
  while (p.available() > 0) {
    char c = p.read();
    Serial.print(c);
  }
  // Ensure the last bit of data is sent.
  Serial.flush();
}
