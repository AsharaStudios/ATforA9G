/*
 * Only MQTT related AT command interface functions
 */

#include "a9gdriver.h"

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
  _sendCommEnd(F("\""));
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
  _sendCommEnd(String((uint8_t)remain));
}

void A9Gdriver::MQTT_sub(String topic, bool sub, uint8_t qos)
{
  _sendComm(F("AT+MQTTSUB=\""));
  _sendComm(topic);
  _sendComm(F("\","));
  _sendComm(String((uint8_t)sub));
  _sendComm(F(","));
  _sendCommEnd(String(qos));
}

void A9Gdriver::MQTT_disconnect()
{
  _sendCommEnd(F("AT+MQTTDISCONN"));
}
