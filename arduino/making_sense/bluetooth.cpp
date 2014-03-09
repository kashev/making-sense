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
  spp   (pinRX, pinTX),
  _name  (name)
{
    /* Intentionally Empty */
}

void
Bluetooth::begin (void)
{
    pinMode(_pinRX, INPUT);
    pinMode(_pinTX, OUTPUT);

    spp.begin(_BLUETOOTH_BAUD_RATE_);

    /* Initialize BT In Slave Mode */

    spp.print("\r\n+STWMOD=0\r\n");           // slave mode
    spp.print("\r\n+STOAUT=1\r\n");           // allow pairs
    spp.print("\r\n+STAUTO=0\r\n");           // disallow autoconnect
    spp.print(String("\r\n+STNA=") + _name + String("\r\n")); // BT name
    delay(2000);
    spp.print("\r\n+INQ=1\r\n");              // make device inquireable
    delay(2000);
    spp.flush();
}

