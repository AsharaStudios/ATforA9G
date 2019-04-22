/*
 * Only general and mixed AT command interface functions
 * (not inner-working functions!!)
 */

#include "a9gdriver.h"

void A9Gdriver::A_attention()
{
  _sendCommEnd(F("AT"));
}

void A9Gdriver::A_setEchoMode(bool enabled)
{
  _sendComm(F("ATE"));
  _sendCommEnd(String((uint8_t)enabled));
  _echo = enabled;
}

void A9Gdriver::sendRst(A9G_shdn_level_t type)
{
  switch (type)
  {
  case RESTART:
    _sendCommEnd(F("AT+RST=1"));
    break;

  case SHUTDOWN:
    _sendCommEnd(F("AT+RST=2"));
    break;

  default:
    break;
  }
}

void A9Gdriver::ATmode(bool enabled) {
  delay(3050);
  _sendCommEnd( enabled ? F("+++") : F("ATO") );
  delay(3050);
}
