/*
 * Utilitary functions
 */

#include <avr/pgmspace.h>

#include "a9gdriver.h"

A9Gdriver::A9Gdriver(Stream &serial) : _serial(serial)
{
  _serial.setTimeout(100);
}

void A9Gdriver::init()
{

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
