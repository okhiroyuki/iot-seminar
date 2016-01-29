#include <jsonlite.h>
#include <Console.h>
#include <YunClient.h>
#include "M2XStreamClient.h"
#include "DHT.h"

#define DHTPIN 2     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

char deviceId[] = "<device id>"; // Device you want to push to
char streamName[] = "<stream name>"; // Stream you want to push to
char m2xKey[] = "<M2X access key>"; // Your M2X access key

char incomingByte;      // a variable to read incoming Console data into

YunClient client;
M2XStreamClient m2xClient(&client, m2xKey);

void setup() {
  Bridge.begin();   // Initialize Bridge
  Serial.begin(9600);  // Initialize Console

  // Wait for the Serial port to connect
  while(!Serial);

  Serial.println("type T to push temperature data to m2x");
  
  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.println(temperature);

  int response = m2xClient.updateStreamValue(deviceId, streamName, temperature);
  Serial.print("M2x client response code: ");
  Serial.println(response);
  delay(10000);
}
