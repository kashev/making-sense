/*
 *  |\/| _ | . _  _   (~ _  _  _ _ 
 *  |  |(_||<|| |(_|  _)(/_| |_\(/_
 *                _|               
 *  github.com/kashev/making-sense
 *
 *  Kashev Dalmia :: dalmia3 :: kashev.dalmia@gmail.com
 *  Isaac Dupree  :: dupree2 :: isaac.dupree@gmail.com
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
inline float d2v(int16_t d);
inline float v2c(float v);
inline float c2f(float c);
inline float d2f(int16_t d);
float readTempSensor  (uint8_t pin);

int readPressSensor (uint8_t pin);

#endif /* _SENSORS_H_ */
