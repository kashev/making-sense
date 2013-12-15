/*
    |\/| _ | . _  _   (~ _  _  _ _ 
    |  |(_||<|| |(_|  _)(/_| |_\(/_
                  _|               
    github.com/kashev/making-sense

    Kashev Dalmia :: dalmia3 :: kashev.dalmia@gmail.com
    Isaac Dupree  :: dupree2 :: isaac.dupree@gmail.com

    Bluetooth.cpp
*/

#include "Bluetooth.h"

Bluetooth::Bluetooth (uint8_t pinRX, uint8_t pinTX, String name)
: _pinRX (pinRX),
  _pinTX (pinTX),
  _spp   (pinRX, pinTX),
  _name  (name)
{
    /* Intentionally Empty */
}

void
Bluetooth::begin (int baud)
{
    pinMode(_pinRX, INPUT);
    pinMode(_pinTX, OUTPUT);

    _spp.begin(baud);

    /* Initialize BT In Slave Mode */

    _spp.print("\r\n+STWMOD=0\r\n");           // slave mode
    _spp.print(String("\r\n+STNA=") + _name + String("\r\n")); // BT name
    _spp.print("\r\n+STOAUT=1\r\n");           // allow pairs
    _spp.print("\r\n+STAUTO=0\r\n");           // disallow autoconnect
    delay(2000);
    _spp.print("\r\n+INQ=1\r\n");              // make device inquireable
    delay(2000);
    _spp.flush();
}

char
Bluetooth::read (void)
{
    return _spp.read();
}

void
Bluetooth::print (String buf)
{
    _spp.print(buf);
}

boolean
Bluetooth::available (void)
{
    return _spp.available();
}
