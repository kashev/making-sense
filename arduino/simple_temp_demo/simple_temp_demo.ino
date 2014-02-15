/*
	|\/| _ | . _  _   (~ _  _  _ _ 
	|  |(_||<|| |(_|  _)(/_| |_\(/_
				  _|               
	
	Kashev Dalmia :: dalmia3
	Isaac Dupree  :: dupree2

	simple_temp_demo.ino
*/

/*
 * Thanks to Kerry Wong:
 *     http://www.kerrywong.com/2010/05/09/working-with-lm19-temperature-sensor/
 */

#define BAUD_RATE 9600

/*
 * PINS
 */
// LM19 V_out pin on Analog Pin 0
#define pinLM19 0

/*
 *  ARDUINO REQUIRED - VOID & MAIN
 */
void
setup (void)
{
	Serial.begin(BAUD_RATE);    
}

/* GLOBAL VARIABLES */
// globals are used so locals don't have to be reallocated every loop()
float vin, tempC, tempF;
 
void
loop (void)
{
    // sensor realing
    vin = 5.0 * analogRead(pinLM19) / 1024.0;
    tempC = (1.8663 - vin) / 0.01169;
    tempF = 1.8 * tempC + 32.0; // 9.0/5.0 * tempC + 32.0
    
    // printing
    Serial.print("V: ");
    Serial.print(vin);
    Serial.print(",  ");
    Serial.print("C: ");
    Serial.print(tempC);
    Serial.print(",  ");
    Serial.print("F: ");
    Serial.println(tempF);
    
    // to reduce jitter
    delay(100);
}
