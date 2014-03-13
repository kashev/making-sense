/*
 *  |\/| _ | . _  _   (~ _  _  _ _ 
 *  |  |(_||<|| |(_|  _)(/_| |_\(/_
 *                _|               
 *  github.com/kashev/making-sense
 *
 *  Kashev Dalmia :: dalmia3 :: kashev.dalmia@gmail.com
 *  Isaac Dupree  :: dupree2 :: isaac.dupree@gmail.com
 *
 *  sensors.cpp
 */

#include "sensors.h"

/*
 * TEMPERATURE CONVERSIONS
 *     All temperature conversion functions are for the TI LM19 Sensors.
 *     Thanks to Kerry Wong for sample code:
 *     http://www.kerrywong.com/2010/05/09/working-with-lm19-temperature-sensor/
 */

/*
 * d2v
 *     Takes a digital voltage in the range of 0-1023 and converts it to a real
 *     voltage between 0 and 5 volts.
 */
inline float
d2v (int16_t d)
{
    return (5.0 * (float)d / 1024.0);
}

/*
 * v2c
 *     converts a real voltage into a temperature value in degrees Celsius.
 */
inline float
v2c (float v)
{
    return ((1.8663 - v) / 0.01169);
}

/*
 * c2f
 *     converts an input temperature in degrees Celsius and converts it
 *     to degrees Fahrenheit.
 */
inline float
c2f (float c)
{
    return ((1.8 * c) + 32.0); // 9.0/5.0 * tempC + 32.0
}

/*
 * d2f
 *     Combines conversions: given a digital input, convert to degrees Fahrenheit.
 */
inline float
d2f (int16_t d)
{
    return (c2f(v2c(d2v(d))));
}

/*
 * readTempSensor
 *     given a pin, reads it, and returns a value in degrees Fahrenheit.
 */
float
readTempSensor (uint8_t pin)
{
    // return d2f(analogRead(pin));
    /* Spoof Sensor Output */
    return d2f((int16_t)random(0, 1024));
}

/*
 * readPressSensor
 *     given a pin, reads it, and returns a voltage corrosponding to a
 *     read voltage between 0.0 and 5.0.
 */
int16_t
readPressSensor (uint8_t pin)
{
    // return (int16_t)analogRead(pin);
    /* Spoof Sensor Output */
    return ((uint16_t)random(0, 1024));
}
