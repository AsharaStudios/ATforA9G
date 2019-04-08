/*
 * GPS Example using A9G's GPS pins, based on TinyGPS "test_with_gps_device.ino" example
 */

#include <Arduino.h>
#include "a9gdriver.h"
#include <SoftwareSerial.h>

// Connect to HST pins on the A9(G)
#define A9Gtx 4
#define A9Grx 5
SoftwareSerial SerialA9G(A9Gtx,A9Grx);
A9Gdriver A9G(SerialA9G);

// MAIN LOGIC
// Based on https://wiki.ai-thinker.com/gprs/examples#mqtt

void setup(){
    Serial.begin(9600);
    SerialA9G.begin(115200); // A9G Baud Rate

    A9G.NET_attach(true);
    A9G.NET_setPDP();
    A9G.NET_activatePDP();

    A9G.MQTT_connect("www.anthinkerwx.com",1883,"12345",120,0,"Ai-thinker","123456");
}

void loop(){
    A9G.MQTT_pub("test","1234563",0,0,0);
    delay(5000);
}

// UTILITARY FUNCTIONS
