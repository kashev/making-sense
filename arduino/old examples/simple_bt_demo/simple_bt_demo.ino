/*
    |\/| _ | . _  _   (~ _  _  _ _ 
    |  |(_||<|| |(_|  _)(/_| |_\(/_
                  _|               
    
    Kashev Dalmia :: dalmia3
    Isaac Dupree  :: dupree2

    simple_bt_demo.ino
*/

// Must include both SoftwareSerial and Bluetooth.h
#include "Bluetooth.h"

#define BAUD_RATE 9600

/*
 * BLUETOOTH
 */
#define pinBT_RX 6
#define pinBT_TX 7
#define BT_NAME "Making Sense Arm"
Bluetooth bt = Bluetooth(pinBT_RX, pinBT_TX, BT_NAME);

static volatile int count = 0;

/*
 * ARDUINO REQUIRED
 */

void
setup (void)
{
    bt.begin();
}

void
loop (void)
{
    char r;
    while (true)
    {
        if (bt.spp.available())
        {
            r = bt.spp.read();

            if (r == 'i')
            {
                count++;
            }
            else if (r == 'd')
            {
                count --;
            }

            bt.spp.print("count : ");
            bt.spp.print(count);
            bt.spp.print("\r\n");

            bt.spp.flush();
        }
    }
}
