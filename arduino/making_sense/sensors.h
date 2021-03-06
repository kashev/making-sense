/*
 *  |\/| _ | . _  _   (~ _  _  _ _ 
 *  |  |(_||<|| |(_|  _)(/_| |_\(/_
 *                _|               
 *  github.com/kashev/making-sense
 *
 *  Kashev Dalmia :: kashev.dalmia@gmail.com
 *
 *  sensors.h
 */
/*
 * Thanks to Kerry Wong for Temperature Sensor sample code:
 *     http://www.kerrywong.com/2010/05/09/working-with-lm19-temperature-sensor/
 */

#ifndef _SENSORS_H_
#define _SENSORS_H_

#include <Arduino.h>

/*
 * CONVERSION FUNCTIONS
 */
float d2v (int16_t d);
float v2c (float v);
float c2f (float c);

float d2f (int16_t d);
float d2c (int16_t d);

float readTempSensor (uint8_t pin);

int readPressSensor (uint8_t pin);

#endif /* _SENSORS_H_ */
