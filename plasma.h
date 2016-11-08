#ifndef Plasma_h
#define Plasma_h

#include <Arduino.h>
#include <stdint.h>
#include "effect.h"

class Plasma : public Effect {
  public:
    Plasma(uint8_t a0, uint8_t b0, uint8_t a1, uint8_t b1, uint8_t a2, uint8_t b2,
      uint8_t da0, uint8_t db0, uint8_t da1, uint8_t db1, uint8_t da2, uint8_t db2,
      uint8_t *pixels, uint8_t xsize, uint8_t ysize);
    void nextFrame();
    uint16_t delayLength();
  private:
    uint8_t a0, b0, a1, b1, a2, b2;
    uint8_t da0, db0, da1, db1, da2, db2;
    uint8_t *pixels, xsize, ysize;
    const uint8_t scale = 8;
    void loopColor(uint8_t d, uint8_t a, uint8_t b);
};

#endif
