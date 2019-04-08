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
  _sendComm( enable ? F("AT+GPS=1") : F("AT+GPS=0") );
  return _catchRx(F("OK"));
}

bool A9Gdriver::GPS_getStatus(){
  _sendComm(F("AT+GPS?"));
}

// -------------------- GENERAL FUNCTIONS -------------------------

void A9Gdriver::init(){}

void A9Gdriver::_dropRx() {
  while(_serial.available())
    _serial.read();
}

void A9Gdriver::_sendComm(String command) {
  _dropRx();
  _serial.print(command.concat("\r\n"));
}

bool A9Gdriver::_catchRx(String needle) {
  needle.trim();
  String response = _serial.readStringUntil('\n');
  response.trim();
  return response.equals(needle);
}
