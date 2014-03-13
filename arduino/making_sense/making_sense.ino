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

/*
 * FOR DEBUGGING
 */
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
 * PINS
 */
/* SENSOR PINS */
#define pinS0 A0
#define pinS1 A1
#define pinS2 A2
/* MUX PINS */
#define pinM0 2
#define pinM1 3
#define pinM2 4

void
configurePins (void)
{
    /* MUX is CD74HC4051E and has 3 selects */
    pinMode(pinM0, OUTPUT);
    pinMode(pinM1, OUTPUT);
    pinMode(pinM2, OUTPUT);
    /* analog pins do not need further configuration */
}

void
changeMux (uint8_t path)
{
    /* for an 8 way mux, only use te bottom three bits */
    digitalWrite(pinM0, 0x01 & (path));
    digitalWrite(pinM1, 0x01 & (path >> 1));
    digitalWrite(pinM2, 0x01 & (path >> 2));
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
    aJson.addItemToObject(root, "T", temp);
    aJson.addItemToObject(root, "P", pres);
    /* FAKE SENSOR DATA */
    /*
     * Read Temperature Sensors
     */
    aJson.addNumberToObject(temp, "0", readTempSensor(A0));
    aJson.addNumberToObject(temp, "1", readTempSensor(A1));
    aJson.addNumberToObject(temp, "2", readTempSensor(A2));

    /*
     * Read Pressure Sensors
     */
    /* FIRST MUX */
    changeMux(0);
    aJson.addNumberToObject(pres, "0", readPressSensor(A0));
    aJson.addNumberToObject(pres, "1", readPressSensor(A1));
    aJson.addNumberToObject(pres, "2", readPressSensor(A2));
    changeMux(1);
    aJson.addNumberToObject(pres, "3", readPressSensor(A0));
    aJson.addNumberToObject(pres, "4", readPressSensor(A1));
    aJson.addNumberToObject(pres, "5", readPressSensor(A2));
    changeMux(2);
    aJson.addNumberToObject(pres, "6", readPressSensor(A0));
    aJson.addNumberToObject(pres, "7", readPressSensor(A1));
    aJson.addNumberToObject(pres, "8", readPressSensor(A2));
    changeMux(3);
    aJson.addNumberToObject(pres, "9", readPressSensor(A0));
    aJson.addNumberToObject(pres, "A", readPressSensor(A1));
    aJson.addNumberToObject(pres, "B", readPressSensor(A2));
    changeMux(4);
    aJson.addNumberToObject(pres, "C", readPressSensor(A0));
    aJson.addNumberToObject(pres, "D", readPressSensor(A1));
    aJson.addNumberToObject(pres, "E", readPressSensor(A2));

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
    configurePins();
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

