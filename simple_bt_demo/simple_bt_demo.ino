/*
    |\/| _ | . _  _   (~ _  _  _ _ 
    |  |(_||<|| |(_|  _)(/_| |_\(/_
                  _|               
    
    Kashev Dalmia :: dalmia3
    Isaac Dupree  :: dupree2

    simple_bt_demo.ino
*/

// Must include both SoftwareSerial and Bluetooth.h
#include <SoftwareSerial.h>
#include "Bluetooth.h"

/*
 * BLUETOOTH
 */
#define pinBT_RX 8
#define pinBT_TX 9
#define BT_NAME "Making Sense Arm"
Bluetooth bt = Bluetooth(pinBT_RX, pinBT_TX, BT_NAME);

static int count = 0;

/*
 * ENERGIA REQUIRED
 */

void
setup (void)
{
    Serial.begin(9600);
    bt.begin();
}

void
loop (void)
{
    char r;
    while (true)
    {
        if (bt.available())
        {
            r = bt.read();

            bt.print(String(r));

            if (r == 'i')
            {
                count++;
            }
            else if (r == 'd')
            {
                count --;
            }

            bt.print(String(count));
            bt.print("\n");
            bt.print("count : ");
        }
    }
}
