/*
 *  |\/| _ | . _  _   (~ _  _  _ _ 
 *  |  |(_||<|| |(_|  _)(/_| |_\(/_
 *                _|               
 *  github.com/kashev/making-sense
 *
 *  Kashev Dalmia :: dalmia3 :: kashev.dalmia@gmail.com
 *  Isaac Dupree  :: dupree2 :: isaac.dupree@gmail.com
 *
 *  making-sense-app.js
 */

/*
 * NOTE: This is a powerful debugging tool:
 * console.log(Object.keys(strangeObject));
 */

/*
 * CONSTANTS
 *   note that 'const' keyword does not work in all javascript settings,
 *   but works in Protocoder (also Chrome, Node.js)
 */
const TITLE          = "Making Sense";
const DEVICE_NAME    = "Making Sense Arm";
const DEVICE_UUID    = "00001101-0000-1000-8000-00805F9B34FB";
const GREEN          = [48,  168, 72];
const WHITE          = [255, 255, 255];
const INPUT_BUF_SIZE = 256;

/*
 * TITLE BAR
 */
function setUpTitleBar (title, text, background) {
  ui.setTitleTextColor (text[0], text[1], text[2]);
  ui.setTitleBgColor   (background[0], background[1], background[2]);
  ui.setTitle          (title);
}
setUpTitleBar(TITLE, WHITE, GREEN);

/*
 * toUTF8Array
 *   for writing to Android Bluetooth out stream. Courtesy of:
 *   http://stackoverflow.com/q/12518830/1473320
 */

function toUTF8Array(str) {
  var utf8 = [];
  for (var i=0; i < str.length; i++) {
    var charcode = str.charCodeAt(i);
    if (charcode < 0x80) utf8.push(charcode);
    else if (charcode < 0x800) {
      utf8.push(0xc0 | (charcode >> 6), 
                0x80 | (charcode & 0x3f));
    }
    else if (charcode < 0xd800 || charcode >= 0xe000) {
      utf8.push(0xe0 | (charcode >> 12), 
                0x80 | ((charcode>>6) & 0x3f), 
                0x80 | (charcode & 0x3f));
    }
    else {
      // let's keep things simple and only handle chars up to U+FFFF...
      utf8.push(0xef, 0xbf, 0xbd); // U+FFFE "replacement character"
    }
  }
  return utf8;
}

/*
 * IMPORT JAVA LIBRARIES
 */
/* ANDROID BLUETOOTH */
var BluetoothAdapter = Packages.android.bluetooth.BluetoothAdapter;
var BluetoothDevice  = Packages.android.bluetooth.BluetoothDevice;
var BluetoothSocket  = Packages.android.bluetooth.BluetoothSocket;
/* OTHER JAVA LIBRARIES */
var BufferedInputStream = Packages.java.io.BufferedInputStream;
var UUID                = Packages.java.util.UUID;

var mBluetoothAdaptder = BluetoothAdapter.getDefaultAdapter();

if (!mBluetoothAdaptder.isEnabled())
{
  ui.toast("Bluetooth Isn't Enabled!")
  // return;
  util.stop();
}

var pairedDevices = mBluetoothAdaptder.getBondedDevices();

var target_id = -1;
var target_device;
for (var i = 0; i < pairedDevices.size(); i++)
{
  // check for target device
  if (pairedDevices.toArray()[i].getName().toString().equals(DEVICE_NAME))
  {
    target_id = i;
    target_device = pairedDevices.toArray()[i];
  }
}

if (target_id < 0)
{
  ui.toast("Target Device Not Found!");
  // return;
  util.stop();
}

var target_uuid = UUID.fromString(DEVICE_UUID);
var mmSocket = target_device.createRfcommSocketToServiceRecord(target_uuid);

try
{
  mmSocket.connect();
}
catch (err)
{
  ui.toast("Something Went Wrong. Reset the Target Device and Try Again");
  // return;
  util.stop();
}
/* Create I/O Streams */
var mmOutputStream = mmSocket.getOutputStream();
var mmInputStream  = BufferedInputStream(mmSocket.getInputStream(), INPUT_BUF_SIZE);

ui.addButton("Increment", 20, 20, 500, 300, function(){
  var msg = "i\n";
  mmOutputStream.write(toUTF8Array(msg)); 
});


// poll for incoming data
var in_packet = "";
var curr_char = "";
var prev_char = "";

util.loop(1, function(){
  var bytesAvailable = mmInputStream.available();
  if (bytesAvailable > 0)
  {
    // console.log(String.fromCharCode(mmInputStream.read()));
    prev_char = curr_char;
    curr_char = String.fromCharCode(mmInputStream.read());
    in_packet = in_packet.concat(curr_char);
    if (prev_char === "\r" && curr_char === "\n")
    {
      // end of string
      console.log(in_packet);
      in_packet = "";
    }
  }
});


// mmSocket.close();
