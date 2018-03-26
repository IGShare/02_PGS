/*
 * Global.h
 *
 * Created: 2017-07-17 오전 11:36:02
 *  Author: myeom
 */ 


#ifndef GLOBAL_H_
#define GLOBAL_H_


  uint8_t         *matrixbuff[2];
  uint8_t          nRows;

  // PORT register pointers, pin bitmasks, pin numbers:
  volatile uint8_t  *latport, *oeport, *addraport, *addrbport, *addrcport, *addrdport;
  uint8_t  sclkpin, latpin, oepin, addrapin, addrbpin, addrcpin, addrdpin, _sclk, _latch, _oe, _a, _b, _c, _d;

  // Counters/pointers for interrupt handler:
  volatile uint8_t row, plane;
  volatile uint8_t *buffptr;
  
  volatile uint8_t backindex;
  volatile bool swapflag;
  
  
  
  
#endif /* GLOBAL_H_ */