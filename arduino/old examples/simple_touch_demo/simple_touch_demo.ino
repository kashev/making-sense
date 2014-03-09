/*
    |\/| _ | . _  _   (~ _  _  _ _ 
    |  |(_||<|| |(_|  _)(/_| |_\(/_
                  _|               
    
    Kashev Dalmia :: dalmia3
    Isaac Dupree  :: dupree2

    simple_touch_demo.ino
*/

#define BAUD_RATE 9600

/*
 * PINS
 */
// Touch Sensor V_out pin on Analog Pin 0
#define pinTouch 0

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
float vin;
 
void
loop (void)
{
    // sensor reading
    vin = 5.0 * analogRead(pinTouch) / 1024.0;
    
    // printing
    Serial.print("V: ");
    Serial.println(vin);
    
    // to reduce jitter
    delay(100);
}
