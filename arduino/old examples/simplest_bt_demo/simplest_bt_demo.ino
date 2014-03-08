/*
 *  |\/| _ | . _  _   (~ _  _  _ _ 
 *  |  |(_||<|| |(_|  _)(/_| |_\(/_
 *                _|               
 *  github.com/kashev/making-sense
 *
 *  Kashev Dalmia :: dalmia3 :: kashev.dalmia@gmail.com
 *  Isaac Dupree  :: dupree2 :: isaac.dupree@gmail.com
 *
 *  simplest_bt_demo.ino
 */


#include <Arduino.h>
#include <SoftwareSerial.h>

/*
 * PINS
 */
#define pinBT_RX 6
#define pinBT_TX 7

#define HW_BAUD_RATE 9600
#define BT_BAUD_RATE 38400

SoftwareSerial spp = SoftwareSerial(pinBT_RX, pinBT_TX);

void setupBlueToothConnection()
{
    spp.begin(BT_BAUD_RATE);                    // Set BluetoothBee BaudRate to default baud rate 38400
    spp.print("\r\n+STWMOD=0\r\n");             // set the bluetooth work in slave mode
    spp.print("\r\n+STOAUT=1\r\n");             // Permit Paired device to connect me
    spp.print("\r\n+STAUTO=0\r\n");             // Auto-connection should be forbidden here
    spp.print("\r\n+STNA=SeeedBTSlave\r\n");    // set the bluetooth name as "SeeedBTSlave"
    delay(2000);                                // This delay is required.
    spp.print("\r\n+INQ=1\r\n");                // make the slave bluetooth inquirable
    Serial.println("The slave bluetooth is inquirable!");
    delay(2000);                                // This delay is required.
    spp.flush();
}


/*
 * ARDUINO REQUIRED
 */

void
setup (void)
{
    Serial.begin(HW_BAUD_RATE);
    pinMode(pinBT_RX, INPUT);
    pinMode(pinBT_TX, OUTPUT);

    setupBlueToothConnection();

    Serial.println("HW Serial Functional");

    spp.println("BT Serial Functional");
}

void
loop (void)
{
    if (spp.available())
    {
        Serial.write(spp.read());
    }

    if (Serial.available())
    {
        spp.write(Serial.read());
    }
}

