#include "water.h"

struct Drop {
  uint16_t y; //position (times 16), 
  uint8_t d; // distance (determines speed and brightness)

  Drop() : y(1024), d(0) {}
  Drop(uint8_t d) : y(0), d(d) {}
};

static GrbColor palette[16];
static GrbColor black(0, 0, 0);
//
static Drop *drops;
static uint16_t yLimit;


Water::Water(uint8_t *pixels, uint8_t xsize, uint8_t ysize) : xsize(xsize), ysize(ysize) {
  grbPixels = (GrbColor *)pixels;
  
  for (uint16_t i = 0; i < 16; i++) {
    //initialize palette
    palette[i] = GrbColor(RgbColor(HslColor(0.51f, 1.0f, pow(i / 48.0f, 1.8f))));
  }
  drops = new Drop[xsize];
  yLimit = ysize * 2 * 16;
}

void Water::newDrops() {
  for(uint8_t x = 0; x < xsize; x++) {
    if (drops[x].y >= yLimit) {
      uint8_t dst = random(24);
      if (dst < 16) { //make new, otherwise don't
        drops[x] = Drop(15 - (uint8_t)sqrt(dst * 16));
      }
    }
  }
}

void Water::moveDrops() {
  for(uint8_t x = 0; x < xsize; x++) {
    if (drops[x].y < yLimit) {
      drops[x].y += (16 - drops[x].d);
    }
  }  
}

void Water::drawDrops() {
  for(uint8_t x = 0; x < xsize; x++) {
    uint8_t dy = (drops[x].y / 16);
    uint8_t maxColor = 16 - (drops[x].d / 2);
    
    for(uint8_t y = 0; y < ysize; y++) {
      uint16_t addr = (ysize - y - 1) * xsize + x;
      if (y > dy) { //black
        grbPixels[addr] = black;
      } else if (y == dy) { //bright pix
        grbPixels[addr] = palette[maxColor];
      } else { //y < dy - trail
        int8_t c = (maxColor - 1 - (dy - y));
        grbPixels[addr] = (c < 0) ? black : palette[c];
      }
    }
  }  
}

void Water::nextFrame() {
  newDrops();
  moveDrops();
  drawDrops();
}

uint16_t Water::delayLength() {
  return 80;
}

