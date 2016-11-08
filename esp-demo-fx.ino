#include <NeoPixelBus.h>
#include "effect.h"
#include "plasma.h"

const uint16_t PixelCount = 100;
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount);

Effect *effect;

void SetRandomSeed()
{
    uint32_t seed = 0;

    // random works best with a seed that can use 31 bits
    // analogRead on a unconnected pin tends toward less than four bits
    for (int shifts = 0; shifts < 31; shifts += 3) {
        seed ^= (analogRead(0) & 0b111) << shifts;
        delay(1);
    }
    randomSeed(seed);
}

void setup() {
  SetRandomSeed();
  
//  Serial.begin(115200);

  strip.Begin();
  strip.Show();
  uint8_t *pixels = strip.Pixels(); //100 pixels of 3 bytes each
  effect = new Plasma(random(255), random(255), random(255), random(255), random(255), random(255),
    random(8), random(8), random(8), random(8), random(8), random(8),
    pixels, 10, 10);
  
//  Serial.println("GO");
}

void loop() {
  delay(64);
  effect->nextFrame();
  
  strip.Dirty();
  strip.Show();
}
