/*
 * Only HTTP related AT command interface functions
 */

#include "a9gdriver.h"

void A9Gdriver::HTTP_sendGet(String url)
{
  _sendComm(F("AT+HTTPGET=\""));
  _sendComm(url);
  _sendCommEnd(F("\""));
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
  _sendCommEnd(F("\""));
}
