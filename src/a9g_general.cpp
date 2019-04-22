/*
 * Only general AT command interface functions
 * (not inner-working functions!!)
 */

#include "a9gdriver.h"

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
