#include "plasma.h"

static uint8_t cosTable[128] = {
  255, 255, 255, 255, 254, 254, 254, 253, 253, 252, 251, 250, 250, 249, 248, 246,
  245, 244, 243, 241, 240, 238, 237, 235, 234, 232, 230, 228, 226, 224, 222, 220,
  218, 215, 213, 211, 208, 206, 203, 201, 198, 196, 193, 190, 188, 185, 182, 179,
  176, 173, 170, 167, 165, 162, 158, 155, 152, 149, 146, 143, 140, 137, 134, 131,
  128, 124, 121, 118, 115, 112, 109, 106, 103, 100,  97,  93,  90,  88,  85,  82,
   79,  76,  73,  70,  67,  65,  62,  59,  57,  54,  52,  49,  47,  44,  42,  40,
   37,  35,  33,  31,  29,  27,  25,  23,  21,  20,  18,  17,  15,  14,  12,  11,
   10,   9,   7,   6,   5,   5,   4,   3,   2,   2,   1,   1,   1,   0,   0,   0
};


static uint8_t cVal(uint8_t x) {
  return cosTable[((x > 127) ? 255 - x : x) & 127];
}

Plasma::Plasma(uint8_t a0, uint8_t b0, uint8_t a1, uint8_t b1, uint8_t a2, uint8_t b2,
      uint8_t da0, uint8_t db0, uint8_t da1, uint8_t db1, uint8_t da2, uint8_t db2,
      uint8_t *pixels, uint8_t xsize, uint8_t ysize) :
        a0(a0), b0(b0), a1(a1), b1(b1), a2(a2), b2(b2), da0(da0), db0(db0), da1(da1), db1(db1), da2(da2), db2(db2),
        pixels(pixels), xsize(xsize), ysize(ysize) {
  
}

void Plasma::loopColor(uint8_t d, uint8_t a, uint8_t b) {
  uint8_t x, y, aa, bb, c;
  uint16_t dy;
  
  for (y = 0; y < ysize; y++) {
    aa = cVal(y * scale + a);
    bb = cVal(b + 64);
    dy = 3 * xsize * y;
    for (x = 0; x < xsize; x++) {
      c = cVal(x * scale + aa) + cVal(y * scale + bb + 64);
      pixels[ dy + (3 * x) + d ] = map(c, 0, 255, 0, 80);
    }
  }
}

void Plasma::nextFrame() {
  loopColor(0, a0, b0);
  a0 += da0 - 4; b0 += db0 - 4;
  loopColor(1, a1, b1);
  a1 += da1 - 4; b1 += db1 - 4;
  loopColor(2, a2, b2);
  a2 += da2 - 4; b2 += db2 - 4;
}

