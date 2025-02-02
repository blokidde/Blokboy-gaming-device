/*
 * Description: Using this sketch you can get your Arduino mac address through Serial Monitor.
 *              The mac address can be used for connection to the IoT-network.
 *              Prints the mac address every 5 seconds in the Serial Monitor.
 *              Serial speed: 9600
 * Author:  Mats Otten
 * Date:    8 sep 2021
 */
#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("MAC-address of your WeMoS: ");
  Serial.println(WiFi.macAddress());
  delay(5000);
}
