#include <Arduino.h>
#include "a9gdriver.h"

//Assume A9G is connected to Serial
A9Gdriver A9G(Serial);

void setup(){
    Serial.begin(115200); // A9G Baud Rate
    A9G.init();
    while (!A9G.GPS_setStatus(1))
        delay(2000);
}

void loop(){

    delay(5000);
}
