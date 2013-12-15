/*
    |\/| _ | . _  _   (~ _  _  _ _ 
    |  |(_||<|| |(_|  _)(/_| |_\(/_
                  _|               
    
    Kashev Dalmia :: dalmia3
    Isaac Dupree  :: dupree2

    simple_bt_demo.ino
*/

#include "Bluetooth.h"

/*
 * BLUETOOTH
 */
#define pinBT_RX 8
#define pinBT_TX 9
Bluetooth bt = Bluetooth(pinBT_RX, pinBT_TX);

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

            bt.print(r);

            if (r == 'i')
            {
                count++;
            }
            else if (r == 'd')
            {
                count --;
            }

            bt.print(count);
            bt.print("\n");
            bt.print("count : ");
        }
    }
}
