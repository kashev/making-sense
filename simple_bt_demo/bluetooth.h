/*
    |\/| _ | . _  _   (~ _  _  _ _ 
    |  |(_||<|| |(_|  _)(/_| |_\(/_
                  _|               
    github.com/kashev/making-sense

    Kashev Dalmia :: dalmia3 :: kashev.dalmia@gmail.com
    Isaac Dupree  :: dupree2 :: isaac.dupree@gmail.com

    Bluetooth.h
*/

#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

#include <SoftwareSerial.h>
#include <Arduino.h>

class Bluetooth {
public:
    /* Constructors */
    Bluetooth (uint8_t pinTX, uint8_t pinRX,
               String name  = String("BT Arduino Shield"));

    /* Initializers */
    void begin (int baud = 38400);

    /* RTX */
    char read (void);
    void print (String buf);
    boolean available (void);

private:

    /*
     * Data Members
     */
    /* Pins */
    uint8_t _pinTX, _pinRX;
    /* Bluetooth Name */
    String _name;
    /* Member Classes */
    SoftwareSerial _spp;
};

#endif /* _BLUETOOTH_H_ */
