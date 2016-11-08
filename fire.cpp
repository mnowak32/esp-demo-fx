#include "fire.h"

static RgbColor palette[256];
//
static uint8_t *field;

Fire::Fire(uint8_t *pixels, uint8_t xsize, uint8_t ysize) : pixels(pixels), xsize(xsize), ysize(ysize) {
  for (uint16_t i = 0; i < 256; i++) {
    //initialize palette
    palette[i] = RgbColor(HslColor(i / 1024.0, 1.0f, (i > 127) ? 0.25f : i / 512.0));
  }
  field = new uint8_t[xsize * (ysize + 1)];
}

void Fire::randomize() {
  for (uint8_t i = 0; i < xsize; i++) {
    field[i] = random(256);
  }
}

uint8_t Fire::getPixel(uint8_t x, uint8_t y) {
  return field[(y % ysize) * xsize + (x % xsize)];
}

void Fire::calculate() {
  for (uint8_t y = ysize; y > 0; y--) {
    for (uint8_t x = 0; x < xsize; x++) {
      uint8_t c = (
        getPixel(x - 1, y - 1) +
        getPixel(x, y - 1) +
        getPixel(x + 1, y - 1) +
        getPixel(x, y - 2)
      ) * 32 / 129;
      field[y * xsize + x] = c;
    }
  }
}

void Fire::paint() {
  uint8_t dy;
  for (uint8_t y = 0; y < ysize; y++) {
    dy = 3 * xsize * y;
    for (uint8_t x = 0; x < xsize; x++) {
      RgbColor c = palette[getPixel(x, y)];
      pixels[dy + x + 0] = c.R;
      pixels[dy + x + 1] = c.G;
      pixels[dy + x + 2] = c.B;
    }
  }
}

void Fire::nextFrame() {
  randomize();
  calculate();
  paint();
}

