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

bool A9Gdriver::GPS_setStatus(bool enable)
{
  _sendComm( enable ? F("AT+GPS=1") : F("AT+GPS=0") );
  return _catchRx(F("OK"));
}

bool A9Gdriver::GPS_getStatus()
{
  _sendComm(F("AT+GPS?"));
  return true; // TODO: Implement this at all...
}

// ---------------------- GPRS FUNCTIONS --------------------------

void A9Gdriver::NET_attach(bool enable)
{
  _sendComm(F("AT+CGATT=1"));
}

void A9Gdriver::NET_setPDP()
{
  _sendComm(F("AT+CGDCONT=1, \"IP\", \"CMNET\""));
}

void A9Gdriver::NET_activatePDP()
{
  _sendComm(F("AT+CGACT=1,1"));
}

// ---------------------- HTTP FUNCTIONS --------------------------

void A9Gdriver::HTTP_sendGet(String url)
{
  _sendComm("AT+HTTPGET=\"" + url + "\"");
}

void A9Gdriver::HTTP_sendPost(String url,String contentType, String bodyContent){
  // TODO: Verify this...
  _sendComm("AT+HTTPPOST=\"" + url + "\", \"" + contentType + "\", \"" + bodyContent + "\"");
}

// ---------------------- MQTT FUNCTIONS --------------------------

void A9Gdriver::MQTT_connect(String server, uint16_t port, String clientID, uint16_t aliveSeconds, bool cleanSession, String username, String password)
{
  _sendComm(" AT+MQTTCONN=\"" + server + "\"," + String(port) + ",\"" + clientID + "\"," + String(aliveSeconds) + "," + String((uint8_t)cleanSession) + ",\"" + username + "\",\"" + password + "\"");
}

void A9Gdriver::MQTT_pub(String topic, String payload, uint8_t qos, bool dup, bool remain)
{
  _sendComm("AT+MQTTPUB=\"" + topic + "\",\"" + payload + "\"," + String(qos) + "," + String((uint8_t)dup) + "," + String((uint8_t)remain));
}

void A9Gdriver::MQTT_sub(String topic, bool sub, uint8_t qos)
{
  _sendComm("AT+MQTTSUB=\"" + topic + "\"," + String((uint8_t)sub) + "," + String(qos));
}

void A9Gdriver::MQTT_disconnect()
{
  _sendComm(F("AT+MQTTDISCONN"));
}

// -------------------- GENERAL FUNCTIONS -------------------------

void A9Gdriver::init()
{}

void A9Gdriver::sendRst(A9G_shdn_level_t type)
{
  switch (type)
  {
    case RESTART:
      _sendComm(F("AT+RST=1"));
      break;

    case SHUTDOWN:
      _sendComm(F("AT+RST=2"));
      break;

    default:
      break;
  }
}

void A9Gdriver::_dropRx()
{
  while(_serial.available())
    _serial.read();
}

void A9Gdriver::_sendComm(String command)
{
  _dropRx();
  _serial.println(command);
}

bool A9Gdriver::_catchRx(String needle)
{
  needle.trim();
  String response = _serial.readStringUntil('\n');
  response.trim();
  return response.equals(needle);
}
