/*
 *  |\/| _ | . _  _   (~ _  _  _ _ 
 *  |  |(_||<|| |(_|  _)(/_| |_\(/_
 *                _|               
 *  github.com/kashev/making-sense
 *
 *  Kashev Dalmia :: kashev.dalmia@gmail.com
 *
 *  Bluetooth.h
 */

#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

#include <SoftwareSerial.h>
#include <Arduino.h>

#define _BLUETOOTH_BAUD_RATE_ 38400

class Bluetooth {
public:
    /* Constructors */
    Bluetooth (uint8_t pinTX, uint8_t pinRX,
               String name  = String("BT Arduino Shield"));

    /* Initializers */
    void begin (void);

    /* Member Classes */
    SoftwareSerial spp;

private:

    /*
     * Data Members
     */
    /* Pins */
    uint8_t _pinTX, _pinRX;
    /* Bluetooth Name */
    String _name;
};

#endif /* _BLUETOOTH_H_ */

