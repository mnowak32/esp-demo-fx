#include "fire.h"

static GrbColor palette[256];
//
static uint8_t *field, *seed;
static uint16_t fSize;


Fire::Fire(uint8_t *pixels, uint8_t xsize, uint8_t ysize) : xsize(xsize), ysize(ysize) {
  grbPixels = (GrbColor *)pixels;
  
  for (uint16_t i = 0; i < 256; i++) {
    //initialize palette
//    palette[i] = GrbColor(RgbColor(HslColor(i / 1600.0, 1.0f, (i > 127) ? 0.33f : i / 384.0)));
    palette[i] = GrbColor(RgbColor(HslColor(i / 1600.0, 1.0f, pow(i / 256.0, 1.6f))));
  }
  fSize = xsize * ysize;
  field = new uint8_t[xsize * (ysize + 1)];
  seed = new uint8_t[xsize];
}

void Fire::randomize() {
  for (uint8_t i = 0; i < xsize; i++) {
    seed[i] = random(256);
  }
  //average it
  for (uint8_t i = 1; i < xsize - 1; i++) {
    field[i] = (seed[i - 1] + seed[i] + seed[i + 1]) / 3;
  }
  //add some sparx
  for (uint8_t i = 0; i < 5; i++) {
    uint8_t c = random(32);
    if (c > 24) {
      field[random(fSize / 2) + xsize] = c + 192;
    }
  }
}

uint8_t Fire::getPixel(uint8_t x, uint8_t y) {
  return field[(y % (ysize + 1)) * xsize + (x % xsize)];
}

void Fire::calculate() {
  for (uint8_t y = ysize; y > 0; y--) {
    for (uint8_t x = 0; x < xsize; x++) {
      uint16_t c = (
        getPixel(x - 1, y - 1) +
        getPixel(x, y - 1) +
        getPixel(x + 1, y - 1) +
        getPixel(x, y - 2)
      ) * 28 / 172;
      field[y * xsize + x] = (c & 0xff);
    }
  }
}

void Fire::paint() {
  uint16_t dy;
  for (uint8_t y = 0; y < ysize; y++) {
    dy = xsize * y;
    for (uint8_t x = 0; x < xsize; x++) {
      GrbColor c = palette[getPixel(x, y + 1)];
      grbPixels[dy + x] = c;
    }
  }
}

void Fire::nextFrame() {
  randomize();
  calculate();
  paint();
}

uint16_t Fire::delayLength() {
  return 80;
}

