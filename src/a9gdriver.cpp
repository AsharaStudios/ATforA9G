/*
 * Ai-Thinker A9(G) Library using AT Commands - Implementation
 */

#include "a9gdriver.h"

A9Gdriver::A9Gdriver(Stream& serial):
  _serial(serial)
{
  _serial.setTimeout(100);
}

// ---------------------- GPS FUNCTIONS ---------------------------

bool A9Gdriver::GPS_setStatus(bool enable){
  sendComm( enable ? F("AT+GPS=1") : F("AT+GPS=0") );
  return catchRx(F("OK"));
}

// -------------------- GENERAL FUNCTIONS -------------------------

void A9Gdriver::init(){}

void A9Gdriver::dropRx() {
  while(_serial.available())
    _serial.read();
}

void A9Gdriver::sendComm(String command) {
  dropRx();
  _serial.print(command);
}

bool A9Gdriver::catchRx(String needle) {
  needle.trim();
  String response = _serial.readStringUntil('\n');
  response.trim();
  return response.equals(needle);
}
