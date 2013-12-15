/*
    |\/| _ | . _  _   (~ _  _  _ _ 
    |  |(_||<|| |(_|  _)(/_| |_\(/_
                  _|               
    github.com/kashev/making-sense

    Kashev Dalmia :: dalmia3 :: kashev.dalmia@gmail.com
    Isaac Dupree  :: dupree2 :: isaac.dupree@gmail.com

    bluetooth.cpp
*/

#include "Bluetooth.h"

Bluetooth::Bluetooth (uint8_t pinRX, uint8_t pinTX, char name[])
: _pinRX (pinRX),
  _pinTX (pinTX),
  _name  (name),
  _spp   (pinRX, _pinTX)
{
    /* Intentionally Empty */
}

void
Bluetooth::begin (int baud)
{
    pinMode(_pinRX, INPUT);
    pinMode(_pinTX, OUTPUT);

    _spp.begin(baud)

    /* Initialize BT In Slave Mode */

    _spp.print("\r\n+STWMOD=0\r\n");
    _spp.print("\r\n+STNA=" + _name + "\r\n");
    _spp.print("\r\n+STOAUT=1\r\n")
}