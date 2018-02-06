/*
 * myLedController.cpp
 *
 * Created: 2017-07-17 오전 11:01:33
 * Author : myeom
 */ 
#include <avr/pgmspace.h>
#include <avr/io.h>
#include "Define.h"
#include "Global.h"

#define CLK 11  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2

uint8_t idx_x = 0, idx_y = 0;

Adafruit_GFX(uint8_t w, uint8_t h)
{
	
}
void init(uint8_t rows, uint8_t a, uint8_t b, uint8_t c,
uint8_t sclk, uint8_t latch, uint8_t oe, bool dbuf, uint8_t width) {

	nRows = rows; // Number of multiplexed rows; actual height is 2X this

	// Allocate and initialize matrix buffer:
	int buffsize  = width * nRows * 3, // x3 = 3 bytes holds 4 planes "packed"
	allocsize = (dbuf == true) ? (buffsize * 2) : buffsize;
	if(NULL == (matrixbuff[0] = (uint8_t *)malloc(allocsize))) return;
	memset(matrixbuff[0], 0, allocsize);
	// If not double-buffered, both buffers then point to the same address:
	matrixbuff[1] = (dbuf == true) ? &matrixbuff[0][buffsize] : matrixbuff[0];

	// Save pin numbers for use by begin() method later.
	_a     = a;
	_b     = b;
	_c     = c;
	_sclk  = sclk;
	_latch = latch;
	_oe    = oe;

	// Look up port registers and pin masks ahead of time,
	// avoids many slow digitalWrite() calls later.
	sclkpin   = digitalPinToBitMask(sclk);
	latport   = portOutputRegister(digitalPinToPort(latch));
	latpin    = digitalPinToBitMask(latch);
	oeport    = portOutputRegister(digitalPinToPort(oe));
	oepin     = digitalPinToBitMask(oe);
	addraport = portOutputRegister(digitalPinToPort(a));
	addrapin  = digitalPinToBitMask(a);
	addrbport = portOutputRegister(digitalPinToPort(b));
	addrbpin  = digitalPinToBitMask(b);
	addrcport = portOutputRegister(digitalPinToPort(c));
	addrcpin  = digitalPinToBitMask(c);
	plane     = nPlanes - 1;
	row       = nRows   - 1;
	swapflag  = false;
	backindex = 0;     // Array index of back buffer
}

void RGBmatrixPanel(
uint8_t a, uint8_t b, uint8_t c,
uint8_t sclk, uint8_t latch, uint8_t oe, bool dbuf) :
Adafruit_GFX(128, 8) {

	init(4, a, b, c, sclk, latch, oe, dbuf, 8);
}
int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

