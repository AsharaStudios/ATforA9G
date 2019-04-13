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

// Network Settings
const PROGMEM char APN[] = "internet.comcel.com.co";

// MAIN LOGIC
// Based on https://wiki.ai-thinker.com/gprs/examples#mqtt

void setup(){
    Serial.begin(9600);
    SerialA9G.begin(115200); // A9G Baud Rate

    // Cellular Network Settings
    A9G.NET_attach(true);
    delay(5000);
    A9G.NET_setPDP(1,APN);
    delay(1000);
    A9G.NET_activatePDP(1,true);
    delay(5000);

    Serial.println("Setting MQTT up");

    // MQTT Settings
    A9G.MQTT_connect(
        "www.anthinkerwx.com", // Server
        1883,   // Port
        "12345",    // Client ID
        120,    // Alive
        0,      // Clean connection not required
        "Ai-thinker",   // User
        "123456"    // Password
    );
}

void loop(){
    A9G.MQTT_pub("test","1234563",0,0,0);
    delay(5000);
}

// UTILITARY FUNCTIONS
