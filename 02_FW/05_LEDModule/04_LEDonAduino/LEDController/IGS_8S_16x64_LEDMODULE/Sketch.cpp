/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 16x32 RGB LED matrix:
// http://www.adafruit.com/products/420

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include "Adafruit-GFX-Library-master\Adafruit_GFX.h"   // Core graphics library
#include "RGB-matrix-Panel-master\RGBmatrixPanel.h" // Hardware-specific library
//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio



#define CLK 11  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2

uint8_t idx_x = 0, idx_y = 0;
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

void setup() {

  matrix.begin();
  
  // draw a pixel in solid white
//  for(idx_y = 0; idx_y<8; idx_y++){
//  for(idx_x = 0; idx_x<64; idx_x ++)
//  {
//       matrix.drawPixel(idx_x, idx_y, matrix.Color333(0, 7, 0)); 
//       delay(50);
//  }
//  }
//
//  for(idx_y = 0; idx_y<8; idx_y++){
//  for(idx_x = 64; idx_x<128; idx_x ++)
//  {
//       matrix.drawPixel(idx_x, idx_y, matrix.Color333(7, 0, 0)); 
//       delay(50);
//  }
//  }
//    matrix.drawPixel(0, 0, matrix.Color333(7, 0, 0)); 
//  delay(500);
//
//  // fix the screen with green
//  matrix.fillRect(0, 0, 32, 16, matrix.Color333(0, 7, 0));
//  delay(500);
//
//  // draw a box in yellow
//  matrix.drawRect(0, 0, 32, 16, matrix.Color333(7, 7, 0));
//  delay(500);
//  
//  // draw an 'X' in red
//  matrix.drawLine(0, 0, 31, 15, matrix.Color333(7, 0, 0));
//  matrix.drawLine(31, 0, 0, 15, matrix.Color333(7, 0, 0));
//  delay(500);
//  
//  // draw a blue circle
//  matrix.drawCircle(7, 7, 7, matrix.Color333(0, 0, 7));
//  delay(500);
//  
//  // fill a violet circle
//  matrix.fillCircle(23, 7, 7, matrix.Color333(7, 0, 7));
//  delay(500);
//  
//  // fill the screen with 'black'
//  matrix.fillScreen(matrix.Color333(0, 0, 0));
//  
//  // draw some text!
//  matrix.setCursor(1, 0);   // start at top left, with one pixel of spacing
//  matrix.setTextSize(1);    // size 1 == 8 pixels high
//  
//  // print each letter with a rainbow color
//  matrix.setTextColor(matrix.Color333(7,0,0));
//  matrix.print('1');
//  matrix.setTextColor(matrix.Color333(7,4,0)); 
//  matrix.print('6');
//  matrix.setTextColor(matrix.Color333(7,7,0));
//  matrix.print('x');
//  matrix.setTextColor(matrix.Color333(4,7,0)); 
//  matrix.print('3');
//  matrix.setTextColor(matrix.Color333(0,7,0));  
//  matrix.print('2');
//  
//  matrix.setCursor(1, 9);   // next line
//  matrix.setTextColor(matrix.Color333(0,7,7)); 
//  matrix.print('*');
//  matrix.setTextColor(matrix.Color333(0,4,7)); 
//  matrix.print('R');
//  matrix.setTextColor(matrix.Color333(0,0,7));
//  matrix.print('G');
//  matrix.setTextColor(matrix.Color333(4,0,7)); 
//  matrix.print("B");
//  matrix.setTextColor(matrix.Color333(7,0,4)); 
//  matrix.print("*");

  // whew!
}

uint8_t cidx = 0;
void loop() {
  // do nothing
  switch(cidx){
    case 0 : matrix.drawPixel(idx_x, idx_y, matrix.Color333(7, 0, 0)); break;
    case 1 : matrix.drawPixel(idx_x, idx_y, matrix.Color333(0, 7, 0)); break;
    case 2 : matrix.drawPixel(idx_x, idx_y, matrix.Color333(0, 0, 7)); break;
    case 3 : matrix.drawPixel(idx_x, idx_y, matrix.Color333(0, 7, 7)); break;
    case 4 : matrix.drawPixel(idx_x, idx_y, matrix.Color333(7, 7, 0)); break;
    case 5 : matrix.drawPixel(idx_x, idx_y, matrix.Color333(7, 0, 7)); break;
    case 6 : matrix.drawPixel(idx_x, idx_y, matrix.Color333(7, 7, 7)); break;
    case 7 : matrix.drawPixel(idx_x, idx_y, matrix.Color333(0, 0, 0)); break;
    }
  
  //delay(100);

  idx_x++;
  if(idx_x ==128){
    idx_x = 0;
    idx_y++;
    //matrix.drawPixel(idx_x, idx_y, matrix.Color333(0, 0, 0)); 
    if(idx_y == 8){
      idx_y = 0;
      cidx++;
      delay(100);
      if(cidx == 8) cidx = 0;
    }
  }
}
