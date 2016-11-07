#include <NeoPixelBus.h>

const uint16_t PixelCount = 100;
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount);

uint8_t cosTable[128] = {
  255, 255, 255, 255, 254, 254, 254, 253, 253, 252, 251, 250, 250, 249, 248, 246,
  245, 244, 243, 241, 240, 238, 237, 235, 234, 232, 230, 228, 226, 224, 222, 220,
  218, 215, 213, 211, 208, 206, 203, 201, 198, 196, 193, 190, 188, 185, 182, 179,
  176, 173, 170, 167, 165, 162, 158, 155, 152, 149, 146, 143, 140, 137, 134, 131,
  128, 124, 121, 118, 115, 112, 109, 106, 103, 100,  97,  93,  90,  88,  85,  82,
   79,  76,  73,  70,  67,  65,  62,  59,  57,  54,  52,  49,  47,  44,  42,  40,
   37,  35,  33,  31,  29,  27,  25,  23,  21,  20,  18,  17,  15,  14,  12,  11,
   10,   9,   7,   6,   5,   5,   4,   3,   2,   2,   1,   1,   1,   0,   0,   0
};

uint8_t a0, b0, a1, b1, a2, b2;
uint8_t da0, db0, da1, db1, da2, db2;
uint8_t* pixels;
uint8_t scale = 8;

uint8_t cVal(uint8_t x) {
  return cosTable[(x > 127) ? 255 - x : x];
}

void loopColor(uint8_t d, uint8_t a, uint8_t b) {
  uint8_t x, y, aa, bb, c;
  uint16_t dy;
  
  for (y = 0; y < 10; y++) {
    aa = cVal(y * scale + a);
    bb = cVal(b + 64);
    dy = 30 * y;
    for (x = 0; x < 10; x++) {
      c = cVal(x * scale + aa) + cVal(y * scale + bb + 64);
      pixels[ dy + (3 * x) + d ] = map(c, 0, 255, 0, 80);
    }
  }
}

void SetRandomSeed()
{
    uint32_t seed;

    // random works best with a seed that can use 31 bits
    // analogRead on a unconnected pin tends toward less than four bits
    seed = analogRead(0);
    delay(1);

    for (int shifts = 3; shifts < 31; shifts += 3)
    {
        seed ^= analogRead(0) << shifts;
        delay(1);
    }

    // Serial.println(seed);
    randomSeed(seed);
}

void setup() {
  SetRandomSeed();
  a0 = random(255);
  b0 = random(255);
  a1 = random(255);
  b1 = random(255);
  a2 = random(255);
  b2 = random(255);
  da0 = random(8);
  db0 = random(8);
  da1 = random(8);
  db1 = random(8);
  da2 = random(8);
  db2 = random(8);
  
  Serial.begin(115200);

  strip.Begin();
  strip.Show();
  
  pixels = strip.Pixels(); //100 pixels of 3 bytes each
  Serial.println("GO");
  
  Serial.print("PixelsSize() = ");
  Serial.println(strip.PixelsSize());
  
  Serial.print("PixelSize() = ");
  Serial.println(strip.PixelSize());
  
  Serial.print("PixelCount() = ");
  Serial.println(strip.PixelCount());
  
}

void loop() {
  delay(64);
  loopColor(0, a0, b0);
  a0 += da0 - 4; b0 += db0 - 4;
  loopColor(1, a1, b1);
  a1 += da1 - 4; b1 += db1 - 4;
  loopColor(2, a2, b2);
  a2 += da2 - 4; b2 += db2 - 4;
  
  strip.Dirty();
  strip.Show();
}
