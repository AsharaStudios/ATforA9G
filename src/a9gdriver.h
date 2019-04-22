/*
 * Ai-Thinker A9(G) Library using AT Commands
 */

#ifndef A9G_AT_COMMANDS_H
#define A9G_AT_COMMANDS_H

#include <Arduino.h>
#include <stdbool.h>
#include "a9g-codes.h" // Check this header for error/status codes

class A9Gdriver
{
    public:

        /**
         * Passes the Serial (software or hardware) connected to the A9(G)
         * to be driven directly by the library. The Serial MUST had been
         * initialized externally at 115200 baud, prior to pass the serial
         * to this function
         */
        A9Gdriver(Stream& serial);

        // GENERAL FUNCTIONS

        void init();
        void sendRst(A9G_shdn_level_t type);

        // GPS FUNCTIONS

        bool GPS_setStatus(bool enable); // GPS
        bool GPS_getStatus();   // GPS?

        // GPRS FUNCTIONS

        void NET_attach(bool enable); // CGATT
        void NET_setPDP(int profile, const char * APN);  // CGDCONT
        void NET_activatePDP(int profile, bool activate); // CGACT

        // HTTP FUNCTIONS

        void HTTP_sendGet(String url); // HTTPGET
        void HTTP_sendPost(String url,String contentType, String bodyContent); // HTTPPOST

        // MQTT FUNCTIONS

        void MQTT_connect(const char * server, uint16_t port, String clientID, uint16_t aliveSeconds, bool cleanSession, const char * username, const char * password);    // MQTTCONN
        void MQTT_pub(const char * topic, String payload, uint8_t qos, bool dup, bool remain);    // MQTTPUB
        void MQTT_sub(String topic, bool sub, uint8_t qos);    // MQTTSUB
        void MQTT_disconnect(); // MQTTDISCONN

    protected:
        Stream& _serial;
        void _dropRx();
        void _flushTx();
        void _sendComm(String command);
        void _sendCommln(String command);
        void _sendLongString(const char * str);
        void _sendBuffer(const char * buffer, size_t size);
        bool _catchRx(String needle);
};

#endif // A9G_AT_COMMANDS_H !def
