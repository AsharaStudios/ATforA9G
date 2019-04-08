/*
 * Ai-Thinker A9(G) Library using AT Commands
 */

#ifndef A9G_AT_COMMANDS_H
#define A9G_AT_COMMANDS_H

#include <Arduino.h>
#include <stdbool.h>

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
        void init();

        bool GPS_setStatus(bool enable);
        bool GPS_getStatus();
    
    private:
        Stream& _serial;
        void dropRx();
        void sendComm(String command);
        bool catchRx(String needle);
};

#endif // A9G_AT_COMMANDS_H !def
