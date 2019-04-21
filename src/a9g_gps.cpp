/*
 * Only GPS related AT command interface functions
 */

#include "a9gdriver.h"

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
