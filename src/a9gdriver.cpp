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
  _sendCommln( enable ? F("AT+GPS=1") : F("AT+GPS=0") );
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

void A9Gdriver::NET_setPDP(int profile, String APN)
{
  _sendCommln("AT+CGDCONT=" + String(profile) +", \"IP\", \"" + APN + "\"");
}

void A9Gdriver::NET_activatePDP(int profile, bool activate)
{
  _sendCommln("AT+CGACT=" + String(activate) + "," + String(profile));
}

// ---------------------- HTTP FUNCTIONS --------------------------

void A9Gdriver::HTTP_sendGet(String url)
{
  _sendCommln("AT+HTTPGET=\"" + url + "\"");
}

void A9Gdriver::HTTP_sendPost(String url,String contentType, String bodyContent){
  // TODO: Verify this...
  _sendCommln("AT+HTTPPOST=\"" + url + "\", \"" + contentType + "\", \"" + bodyContent + "\"");
}

// ---------------------- MQTT FUNCTIONS --------------------------

void A9Gdriver::MQTT_connect(char * server, uint16_t port, char * clientID, uint16_t aliveSeconds, bool cleanSession, char * username, char * password)
{
  _sendComm("AT+MQTTCONN=\"");
  _sendComm(server);
  _sendComm("\",");
  _sendComm(String(port));
  _sendComm(",\"");
  _sendComm(clientID);
  _sendComm("\",");
  _sendComm(String(aliveSeconds));
  _sendComm(",");
  _sendComm(String((uint8_t)cleanSession));
  _sendComm(",\"");
  _sendComm(username);
  _sendComm("\",\"");
  _sendComm(password);
  _sendCommln("\"");
  }

void A9Gdriver::MQTT_pub(char * topic, String payload, uint8_t qos, bool dup, bool remain)
{
  _sendComm("AT+MQTTPUB=\"");
  _sendComm(topic);
  _sendComm("\",\"");
  _sendComm(payload);
  _sendComm("\",");
  _sendComm(String(qos));
  _sendComm(",");
  _sendComm(String((uint8_t)dup));
  _sendComm(",");
  _sendCommln(String((uint8_t)remain));
}

void A9Gdriver::MQTT_sub(String topic, bool sub, uint8_t qos)
{
  _sendCommln("AT+MQTTSUB=\"" + topic + "\"," + String((uint8_t)sub) + "," + String(qos));
}

void A9Gdriver::MQTT_disconnect()
{
  _sendCommln(F("AT+MQTTDISCONN"));
}

// -------------------- GENERAL FUNCTIONS -------------------------

void A9Gdriver::init()
{}

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
  while(_serial.available())
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
  _flushTx();
}

bool A9Gdriver::_catchRx(String needle)
{
  needle.trim();
  String response = _serial.readStringUntil('\n');
  response.trim();
  return response.equals(needle);
}
