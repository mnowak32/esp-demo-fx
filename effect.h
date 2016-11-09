#ifndef Effect_h
#define Effect_h

#include <NeoPixelBus.h>

class Effect {
  public:
    virtual void nextFrame();
    virtual uint16_t delayLength();
};

struct GrbColor {
  uint8_t G, R, B;

  GrbColor(){}
  GrbColor(RgbColor c) : G(c.G), R(c.R), B(c.B) {}
  GrbColor(uint8_t g, uint8_t r, uint8_t b) : G(g), R(r), B(b) {}
};

#endif
