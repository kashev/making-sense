/*
 *  |\/| _ | . _  _   (~ _  _  _ _ 
 *  |  |(_||<|| |(_|  _)(/_| |_\(/_
 *                _|               
 *  
 *  Kashev Dalmia :: dalmia3
 *  Isaac Dupree  :: dupree2
 *
 *  making_sense.ino
 */

/*
 * INCLUDES
 */
#include <SoftwareSerial.h>
#include <Serial.h>

#include "Bluetooth.h"
#include "aJSON.h"
#include "sensors.h"


int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

/*
 * BLUETOOTH
 */
#define BAUD_RATE 9600
#define pinBT_RX 6
#define pinBT_TX 7
#define BT_NAME "Making Sense Arm"
Bluetooth bt = Bluetooth(pinBT_RX, pinBT_TX, BT_NAME);

/*
 * SENSORS
 */
void
configureSensorPins (void)
{
    /* Set Input/Output Modes */
}
/*
 * readAllSensors
 *     Returns a stringified JSON Object containing sensor values.
 */
char *
readAllSensors (void)
{
    aJsonObject * root = aJson.createObject();
    aJsonObject * temp = aJson.createObject();
    aJsonObject * pres = aJson.createObject();
    aJson.addItemToObject(root, "temp",  temp);
    aJson.addItemToObject(root, "press", pres);
    /* FAKE SENSOR DATA */
    /*
     * Read Temperature Sensors
     */
    aJson.addNumberToObject(temp, "1", readTempSensor(A0));
    aJson.addNumberToObject(temp, "2", readTempSensor(A1));
    aJson.addNumberToObject(temp, "3", readTempSensor(A2));

    /*
     * Read Pressure Sensors
     */    
    aJson.addNumberToObject(pres, "1", readPressSensor(A0));
    aJson.addNumberToObject(pres, "2", readPressSensor(A1));
    aJson.addNumberToObject(pres, "3", readPressSensor(A2));

    /* return as String */
    char * r = aJson.print(root);
    aJson.deleteItem(root);
    return r;
}

/*
 * ARDUINO REQUIRED
 */

void
setup (void)
{
    configureSensorPins();
    Serial.begin(BAUD_RATE);
    bt.begin();
}

void
loop (void)
{   
    Serial.println(freeRam());
    char * t = readAllSensors();
    Serial.print("Sent : ");
    Serial.println(t);
    bt.spp.print(t);
    bt.spp.print("\r\n");
    bt.spp.flush();
    /* Required so that the Arduino doesn't run out of Memory */
    free(t);

    delay(1000);
}

