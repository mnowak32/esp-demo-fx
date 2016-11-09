#ifndef Matrix_h
#define Matrix_h

#include <Arduino.h>
#include <stdint.h>
#include "effect.h"

class Matrix : public Effect {
  public:
    Matrix(uint8_t *pixels, uint8_t xsize, uint8_t ysize);
    void nextFrame();
    uint16_t delayLength();
  private:
    GrbColor *grbPixels;
    uint8_t xsize, ysize;
    void newDrops();
    void moveDrops();
    void drawDrops();
};
#endif

