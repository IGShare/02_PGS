  // testshapes demo for RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 32x64 RGB LED matrix.

// NOTE THIS CAN ONLY BE USED ON A MEGA! NOT ENOUGH RAM ON UNO!

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define OE   9
#define LAT  10
#define CLK  11
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);
//uint8_t testChar[] = {0x00, 0x00, 0x01, 0x80, 0x03, 0xC0, 0x07, 0xE0, 0x0F, 0xF0, 0x1F, 0xF8, 0x3F, 0xFC, 0x7F, 0xFE, 
//                      0x7F, 0xFE, 0x07, 0xE0, 0x07, 0xE0, 0x07, 0xE0, 0x07, 0xE0, 0x07, 0xE0, 0x07, 0xE0, 0x00, 0x00 };
uint8_t testChar[] = {0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

void setup() {

  //Serial.begin(9600);
  matrix.begin();

int i, j;
  //for(i=0; i<32; i++){
  for(j=0; j<32; j++){
      matrix.drawPixel(0, j, matrix.Color333(0, 7, 0));


      //delay(500);
      //matrix.drawPixel(i+16, j, matrix.Color333(0, 0, 7)); 


     // delay(500);
  }
      
  //}
  
  //bitmapTest
  //matrix.drawBitmap(0,0,testChar,16, 16, matrix.Color333(0, 7, 0));
  //matrix.drawBitmap(8,0,testChar,16, 16, matrix.Color333(7, 0, 0));
  //matrix.drawBitmap(0,16,testChar,16, 16, matrix.Color333(0, 7, 0));
  //matrix.drawBitmap(16,16,testChar,16, 16, matrix.Color333(0, 7, 0));
  //matrix.drawBitmap(32,0,testChar,16, 16, matrix.Color333(0, 7, 0));
  //matrix.drawBitmap(48,0,testChar,16, 16, matrix.Color333(0, 7, 0));
  //matrix.drawBitmap(32,16,testChar,16, 16, matrix.Color333(0, 7, 0));
  //matrix.drawBitmap(48,16,testChar,16, 16, matrix.Color333(0, 7, 0));

  


  // whew!
}

void loop() {
  // do nothing

  

}


// Input a value 0 to 24 to get a color value.
// The colours are a transition r - g - b - back to r.
uint16_t Wheel(byte WheelPos) {
  if(WheelPos < 8) {
   return matrix.Color333(7 - WheelPos, WheelPos, 0);
  } else if(WheelPos < 16) {
   WheelPos -= 8;
   return matrix.Color333(0, 7-WheelPos, WheelPos);
  } else {
   WheelPos -= 16;
   return matrix.Color333(0, WheelPos, 7 - WheelPos);
  }
}
