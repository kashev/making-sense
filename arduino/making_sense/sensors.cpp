/*
 *  |\/| _ | . _  _   (~ _  _  _ _ 
 *  |  |(_||<|| |(_|  _)(/_| |_\(/_
 *                _|               
 *  github.com/kashev/making-sense
 *
 *  Kashev Dalmia :: kashev.dalmia@gmail.com
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
float
d2v (int16_t d)
{
    return (5.0 * (float)d / 1023.0);
}

/*
 * v2c
 *     converts a real voltage into a temperature value in degrees Celsius.
 */
float
v2c (float v)
{
    return ((1.8663 - v) / 0.01169);
}

/*
 * c2f
 *     converts an input temperature in degrees Celsius and converts it
 *     to degrees Fahrenheit.
 */
float
c2f (float c)
{
    return ((1.8 * c) + 32.0); // 9.0/5.0 * tempC + 32.0
}

/*
 * d2f
 *     Combines conversions: given a digital input, convert to degrees Fahrenheit.
 */
float
d2f (int16_t d)
{
    return (c2f(v2c(d2v(d))));
}

/*
 * d2c
 *     Combines conversions: given a digital input, convert to degrees Celsius
 */

float
d2c (int16_t d)
{
    return (v2c(d2v(d)));
}

/*
 * readTempSensor
 *     given a pin, reads it, and returns a value in degrees Fahrenheit.
 */
float
readTempSensor (uint8_t pin)
{
    delay(10);
    analogRead(pin);
    delay(10);
    return d2f(analogRead(pin));
    /* Spoof Sensor Output */
    // return d2c((int16_t)random(0, 1024));
}

/*
 * readPressSensor
 *     given a pin, reads it, and returns a digital voltage between
 *     1023. This value is returned as an int for convenience of use
 *     with the aJSON library. This voltage is only used as a
 *     relative difference;
 */
int
readPressSensor (uint8_t pin)
{
    delay(10);
    analogRead(pin);
    delay(10);
    return (int)analogRead(pin);
    /* Spoof Sensor Output */
    // return ((int)random(0, 1024));
}
