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
 * This is an Android application written in Protocoder Javascript.
 * More information on the Protocoder website: 
 *   http://protocoder.org/
 */
/*
 * NOTE: This is a powerful debugging tool for Protocoder:
 * console.log(Object.keys(aStrangeObject));
 */

/*
 * CONSTANTS
 *   note that 'const' keyword does not work in all Javascript
 *   settings (Internet Explorer), but works in Protocoder, as
 *   well as Chrome, Node.js.
 */
const TITLE          = "Making Sense";     // App Title
const DEVICE_NAME    = "Making Sense Arm"; // Target Device Name
/* UUIDs are advertised by the device. This one just happens to be known in advance */
const DEVICE_UUID    = "00001101-0000-1000-8000-00805F9B34FB";
const INPUT_BUF_SIZE = 256;                // Buffered Input Stream; max packet size
const GREEN          = [48,  168, 72];     // courtesy of http://bitelabs.org/
const WHITE          = [255, 255, 255];
const TITLEBAR_H     = 220;                // determined experimentally

const NUM_P_SENSORS  = 15;
const NUM_T_SENSORS  = 5;

/*
 * TITLE BAR
 */
function setUpTitleBar (title, text, background) {
  ui.setTitleTextColor (text[0], text[1], text[2]);
  ui.setTitleBgColor   (background[0], background[1], background[2]);
  ui.setTitle          (title);
}
/* Initialization */
setUpTitleBar(TITLE, WHITE, GREEN);
device.screenAlwaysOn();

/*
 * toUTF8Array
 *   for writing to Android Bluetooth out stream. Courtesy of:
 *   http://stackoverflow.com/q/12518830/1473320
 */
function toUTF8Array(str) {
  var utf8 = [];
  for (var i=0; i < str.length; i++) {
    var charcode = str.charCodeAt(i);
    if (charcode < 0x80)
    {
      utf8.push(charcode);
    }
    else if (charcode < 0x800)
    {
      utf8.push(0xc0 | (charcode >> 6), 
                0x80 | (charcode & 0x3f));
    }
    else if (charcode < 0xd800 || charcode >= 0xe000)
    {
      utf8.push(0xe0 | (charcode >> 12), 
                0x80 | ((charcode>>6) & 0x3f), 
                0x80 | (charcode & 0x3f));
    }
    else
    {
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
/* ANDROID DRAWING */
var Paint = Packages.android.graphics.Paint;
var Color = Packages.android.graphics.Color;
/* OTHER JAVA LIBRARIES */
var BufferedInputStream = Packages.java.io.BufferedInputStream;
var UUID                = Packages.java.util.UUID;

/*
 * color() - a simple linear RYGCB colormap
 *     thanks to Roger Serwy & the UIUC ECE 420 course staff
 *     of ages past for this color mapping.
 */
// simple linear RYGCB colormap
function color (val) {
  var r, g, b = 0;

  if (val <= 0.25)
  {
    r = 0;
    b = 255;
    g = Math.round(4*val*255);
  }
  else if (val <= 0.5)
  {
    r = 0;
    g = 255;
    b = Math.round((1-4*(val-0.25))*255);
  }
  else if(val <= 0.75)
  {
    g = 255;
    b = 0;
    r = Math.round(4*(val-0.5)*255);
  }
  else
  {
    r = 255;
    b = 0;
    g = Math.round((1-4*(val-0.75))*255);
  }

  var RGB =  {
    R:r, 
    G:g,
    B:b
  };

  return RGB;
}


/*
 * SENSOR LOCATIONS
 */

/*
 * PRESSURE
 */
/*
       PALM           BACK 
     pressure       pressure
       _.-._        _.-._
     _|1|2|3|      |3|2|1|_
    |0| | | |      | | | |0|
    | | | | |      | | | | |
    |4_5-6 7| _  _ |7 6 5 4|
    ; .-'.-'/8/  \8\       ;
    |9  '   A/    \A      9|
     \B CD E/      \E DC B/
      |    |        |    |
*/

const smR = 30;
const lgR = 45;
/* [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E] */
const xP = [
  945, 855,  725,  590,  815,  710,  615,  500,
  150, 755,  250,  650,  550,  440,  350
];
const yP = [
  700, 515,  400,  400,  955,  855,  805,  785,
  770, 1090, 1000, 1250, 1300, 1290, 1200
];

/*
 * CREATE UI
 */
/*
 * UI CONSTANTS
 */
const C_HEIGHT = ui.screenHeight - TITLEBAR_H;
const C_WIDTH  = ui.screenWidth;
const PRESSURE_LABEL     = "Pressure Map (Right Hand)";
const TEMPERATURE_LABEL  = "Temperature Map (Left Hand)";
const PRESSURE_BUTTON    = "Show Pressure";
const TEMPERATURE_BUTTON = "Show Temperature";
const RIGHTHAND_IMG = "righthand.png";
const LEFTHAND_IMG  = "lefthand.png";
const TEXT_SIZE     = 25;
const BUTTON_SIZE   = 200;

/*
 * UI GLOBALS
 */
var canvas   = ui.addCanvas(0, 0, C_WIDTH, C_HEIGHT);
var paint    = new Paint();

/*
 * GLOBAL SWITCH VARS
 */
var label = ui.addLabel(PRESSURE_LABEL, 20, 20, C_WIDTH, TITLEBAR_H);
/* INITIALIZE */
label.textSize = TEXT_SIZE;
ui.backgroundImage(RIGHTHAND_IMG);

/*
 * CREATE SWITCHING TOGGLE
 */
var sbutton = ui.addToggle(
  TEMPERATURE_BUTTON,
  0,
  C_HEIGHT - BUTTON_SIZE,
  C_WIDTH,
  BUTTON_SIZE,
  false,
  function(checked){
    if (checked)
    {
      /* TEMPERATURE */
      ui.backgroundImage(LEFTHAND_IMG);
      label.text = TEMPERATURE_LABEL;
    }
    else
    {
      /* PRESSURE */
      ui.backgroundImage(RIGHTHAND_IMG);
      label.text = PRESSURE_LABEL;
    }
  });
/* CONFIGURE TOGGLE */
sbutton.textOn  = PRESSURE_BUTTON;
sbutton.textOff = TEMPERATURE_BUTTON;



/*
 * drawPSensor()
 *   given a sensor string and a value, paint the 'heat' dot on the appropriate location.
 */
function drawPSensor (sensor, val) {
  var idx = parseInt(sensor, 16);
  var RGB = color(val / 1023);
  paint.setColor(new Color().argb(255, RGB.R, RGB.G, RGB.B));
  var r;
  if (idx > 3)
  {
    r = lgR;
  }
  else
  {
    r = smR;
  }

  if (idx < NUM_P_SENSORS)
  {
    /* do drawing */
    canvas.getCanvas().drawCircle(xP[idx], yP[idx], r, paint);
  }
}
/*
 * drawPSensors()
 *   given a JSON object with keys 0-E,
 */
function drawPSensors (sensors) {
  for (var key in sensors)
  {
    drawPSensor(key, sensors[key]);
    canvas.invalidate();
  }
}
/*
 * TEST PSENSORS
 */
// var cur = 0;
// util.loop(0, function(){
//   for(var i = 0; i < NUM_P_SENSORS; i++)
//   {
//     drawPSensor(i.toString(16), cur);
//   }
//   cur = (cur + 5) % 1024;
//   canvas.invalidate();
// });

/*
 * BLUETOOTH GLOBALS
 */
var mmOutputStream, mmInputStream;
/*
 * bluetoothConnect()
 *  connect to the target device.
 */
function bluetoothConnect () {
  var mBluetoothAdaptder = BluetoothAdapter.getDefaultAdapter();
  
  if (!mBluetoothAdaptder.isEnabled())
  {
    ui.toast("Bluetooth Isn't Enabled!")
    return false;
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
    return false;
  }
  
  var target_uuid = UUID.fromString(DEVICE_UUID);
  var mmSocket = target_device.createRfcommSocketToServiceRecord(target_uuid);
  
  try
  {
    mmSocket.connect();
  }
  catch (err)
  {
    console.log(err.message);
    ui.toast("Something went wrong during connecting.\n" +
             "Reset the Target Device and Try Again");
    return false;
  }
  /* Create I/O Streams */
  var mmOutputStream = mmSocket.getOutputStream();
  var mmInputStream  = BufferedInputStream(mmSocket.getInputStream(), INPUT_BUF_SIZE);

  /* success */
  return {
    result    : true,
    outstream : mmOutputStream,
    instream  : mmInputStream
  };
}


/*
 * POLL FOR INCOMING DATA
 */
var streams = bluetoothConnect()
if (streams.result)
{
  var mmInputStream  = streams.instream;
  var mmOutputStream = streams.outstream;
  var in_packet = "";
  var curr_char = "";
  var prev_char = "";
  util.loop(1, function(){ // 1 ms for stability
    while (mmInputStream.available() > 0)
    {
      prev_char = curr_char;
      curr_char = String.fromCharCode(mmInputStream.read());
      in_packet = in_packet.concat(curr_char);
      if (prev_char === "\r" && curr_char === "\n")
      {
        // end of packet! update UI.
        try
        {
          var obj = JSON.parse(in_packet);
          console.log(JSON.stringify(obj));
          drawPSensors(obj["P"]);
        }
        catch (err)
        {
          console.log(err.message);
        }
        // reset packet
        in_packet = "";
        prev_char = "";
        curr_char = "";
      }
    }
  });
}

