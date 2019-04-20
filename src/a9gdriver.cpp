/*
 * Ai-Thinker A9(G) Library using AT Commands - Implementation
 */

#include <avr/pgmspace.h>
#include <CayenneLPP.h>

#include "a9gdriver.h"

A9Gdriver::A9Gdriver(Stream &serial) : _serial(serial)
{
  _serial.setTimeout(100);
}

// ---------------------- GPS FUNCTIONS ---------------------------

bool A9Gdriver::GPS_setStatus(bool enable)
{
  _sendCommln(enable ? F("AT+GPS=1") : F("AT+GPS=0"));
  return _catchRx(F("OK"));
}

bool A9Gdriver::GPS_getStatus()
{
  _sendCommln(F("AT+GPS?"));
  return true; // TODO: Implement this at all...
}

// ---------------------- GPRS FUNCTIONS --------------------------

void A9Gdriver::NET_attach(bool enable)
{
  _sendCommln(F("AT+CGATT=1"));
}

void A9Gdriver::NET_setPDP(int profile, const char *APN)
{
  _sendComm(F("AT+CGDCONT="));
  _sendComm(String(profile));
  _sendComm(F(", \"IP\", \""));
  _sendLongString(APN);
  _sendCommln(F("\""));
}

void A9Gdriver::NET_activatePDP(int profile, bool activate)
{
  _sendComm(F("AT+CGACT="));
  _sendComm(String(1));
  _sendComm(F(","));
  _sendCommln(activate ? "1" : "0");
}

// ---------------------- HTTP FUNCTIONS --------------------------

void A9Gdriver::HTTP_sendGet(String url)
{
  _sendComm(F("AT+HTTPGET=\""));
  _sendComm(url);
  _sendCommln(F("\""));
}

void A9Gdriver::HTTP_sendPost(String url, String contentType, String bodyContent)
{
  // TODO: Verify this...
  _sendComm(F("AT+HTTPPOST=\""));
  _sendComm(url);
  _sendComm(F("\", \""));
  _sendComm(contentType);
  _sendComm(F("\", \""));
  _sendComm(bodyContent);
  _sendCommln(F("\""));
}

// ---------------------- MQTT FUNCTIONS --------------------------

void A9Gdriver::MQTT_connect(const char *server, uint16_t port, String clientID, uint16_t aliveSeconds, bool cleanSession, const char *username, const char *password)
{
  _sendComm(F("AT+MQTTCONN=\""));
  _sendLongString(server);
  _sendComm(F("\","));
  _sendComm(String(port));
  _sendComm(F(",\""));
  _sendComm(clientID);
  _sendComm(F("\","));
  _sendComm(String(aliveSeconds));
  _sendComm(F(","));
  _sendComm(String((uint8_t)cleanSession));
  _sendComm(F(",\""));
  _sendLongString(username);
  _sendComm(F("\",\""));
  _sendLongString(password);
  _sendCommln(F("\""));
}

void A9Gdriver::MQTT_pub(const char *topic, String payload, uint8_t qos, bool dup, bool remain)
{
  _sendComm(F("AT+MQTTPUB=\""));
  _sendLongString(topic);
  _sendComm(F("\",\""));
  _sendComm(payload);
  _sendComm(F("\","));
  _sendComm(String(qos));
  _sendComm(F(","));
  _sendComm(String((uint8_t)dup));
  _sendComm(F(","));
  _sendCommln(String((uint8_t)remain));
}

void A9Gdriver::MQTT_sub(String topic, bool sub, uint8_t qos)
{
  _sendComm(F("AT+MQTTSUB=\""));
  _sendComm(topic);
  _sendComm(F("\","));
  _sendComm(String((uint8_t)sub));
  _sendComm(F(","));
  _sendCommln(String(qos));
}

void A9Gdriver::MQTT_disconnect()
{
  _sendCommln(F("AT+MQTTDISCONN"));
}

// -------------------- GENERAL FUNCTIONS -------------------------

void A9Gdriver::init()
{

}

void A9Gdriver::sendRst(A9G_shdn_level_t type)
{
  switch (type)
  {
  case RESTART:
    _sendCommln(F("AT+RST=1"));
    break;

  case SHUTDOWN:
    _sendCommln(F("AT+RST=2"));
    break;

  default:
    break;
  }
}

void A9Gdriver::_dropRx()
{
  while (_serial.available())
    _serial.read();
}

void A9Gdriver::_flushTx()
{
  _serial.flush();
}

void A9Gdriver::_sendComm(String command)
{
  _dropRx();
  _serial.print(command);
  _flushTx();
}

void A9Gdriver::_sendCommln(String command)
{
  _dropRx();
  _serial.println(command);
}

void A9Gdriver::_sendBuffer(const char *buffer, size_t size)
{
  char *out = (char *)buffer;

  for (char *it = out; it < buffer + size; it += 4)
    *out++ = "0123456789abcdef"[(it[0] != '0') * 8 +
                                (it[1] != '0') * 4 +
                                (it[2] != '0') * 2 +
                                (it[3] != '0') * 1];

  _serial.write(out, size / 4);
  _serial.flush();
}

bool A9Gdriver::_catchRx(String needle)
{
  needle.trim();
  String response = _serial.readStringUntil('\n');
  response.trim();
  return response.equals(needle);
}

char tmpChar = 0;
int k = 0;

void A9Gdriver::_sendLongString(const char *str)
{
  for (k = 0; k < strlen_P(str); k++)
  {
    tmpChar = pgm_read_byte_near(str + k);
    _serial.print(tmpChar);
  }
}
