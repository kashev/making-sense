/*
    |\/| _ | . _  _   (~ _  _  _ _ 
    |  |(_||<|| |(_|  _)(/_| |_\(/_
                  _|               
    github.com/kashev/making-sense

    Kashev Dalmia :: dalmia3 :: kashev.dalmia@gmail.com
    Isaac Dupree  :: dupree2 :: isaac.dupree@gmail.com

    bluetooth.h
*/

#include <SoftwareSerial.h>

class Bluetooth {
public:
    /* Constructors */
    Bluetooth (uint8_t pinTX, uint8_t pinRX,
               char name[] = "Arduino Bluetooth Shield");

    /* Initializers */
    void begin (int baud = 38400);

private:

    /*
     * Data Members
     */
    /* Pins */
    uint8_t _pinTX, _pinRX;
    /* Bluetooth Name */
    char _name[];
    /* Member Classes */
    SoftwareSerial _spp;
}