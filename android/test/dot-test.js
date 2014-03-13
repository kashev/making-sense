/* ANDROID DRAWING */
var Paint = Packages.android.graphics.Paint;
var Color = Packages.android.graphics.Color;

const TITLEBAR_H     = 220;                // determined experimentally
/*
 * SENSOR LOCATIONS
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

const xP0 = 945; const yP0 = 700;
const xP1 = 855; const yP1 = 515;
const xP2 = 725; const yP2 = 400;
const xP3 = 590; const yP3 = 400;
const xP4 = 815; const yP4 = 955;
const xP5 = 710; const yP5 = 855;
const xP6 = 615; const yP6 = 805;
const xP7 = 500; const yP7 = 785;
const xP8 = 150; const yP8 = 770;
const xP9 = 755; const yP9 = 1090;
const xPA = 250; const yPA = 1000;
const xPB = 650; const yPB = 1250;
const xPC = 550; const yPC = 1300;
const xPD = 440; const yPD = 1290;
const xPE = 350; const yPE = 1200;

/*
 * CREATE UI
 */
var c_height = ui.screenHeight - TITLEBAR_H;
var c_width  = ui.screenWidth;

ui.backgroundImage("righthand.png");

var canvas   = ui.addCanvas(0, 0, c_width, c_height);
var paint    = new Paint();

paint.setColor(new Color().argb(255, 255, 0, 0));

canvas.getCanvas().drawCircle(xP0, yP0, smR, paint);
canvas.getCanvas().drawCircle(xP1, yP1, smR, paint);
canvas.getCanvas().drawCircle(xP2, yP2, smR, paint);
canvas.getCanvas().drawCircle(xP3, yP3, smR, paint);

canvas.getCanvas().drawCircle(xP4, yP4, lgR, paint);
canvas.getCanvas().drawCircle(xP5, yP5, lgR, paint);
canvas.getCanvas().drawCircle(xP6, yP6, lgR, paint);
canvas.getCanvas().drawCircle(xP7, yP7, lgR, paint);
canvas.getCanvas().drawCircle(xP8, yP8, lgR, paint);
canvas.getCanvas().drawCircle(xP8, yP8, lgR, paint);
canvas.getCanvas().drawCircle(xP9, yP9, lgR, paint);
canvas.getCanvas().drawCircle(xPA, yPA, lgR, paint);
canvas.getCanvas().drawCircle(xPB, yPB, lgR, paint);
canvas.getCanvas().drawCircle(xPC, yPC, lgR, paint);
canvas.getCanvas().drawCircle(xPD, yPD, lgR, paint);
canvas.getCanvas().drawCircle(xPE, yPE, lgR, paint);