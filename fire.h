#ifndef Fire_h
#define Fire_h

#include <Arduino.h>
#include <stdint.h>
#include "effect.h"


class Fire : public Effect {
  public:
    Fire(uint8_t *pixels, uint8_t xsize, uint8_t ysize);
    void nextFrame();
    uint16_t delayLength();
  private:
    GrbColor *grbPixels;
    uint8_t xsize, ysize;
    void randomize();
    uint8_t getPixel(uint8_t x, uint8_t y);
    void calculate();
    void paint();
};
#endif

