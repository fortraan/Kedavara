#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define NUMPIXELS 16
#define NEOPIXEL_PIN 6

Adafruit_NeoPixel leds(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

#include "defines.h"
#include "patterns.h"

extern __struct_pattern patterns[];

uint8_t currentPattern;
uint8_t numPatterns;

void setup() {
  // put your setup code here, to run once:
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif

  leds.begin();
  
  Serial.begin(115200);
  numPatterns = sizeof(patterns) / sizeof(__struct_pattern);
  Serial.print("Found ");
  Serial.print(numPatterns);
  Serial.println(" patterns");

  for (uint8_t i = 0; i < numPatterns; i++) {
    pinMode(patterns[i].pin, INPUT_PULLUP);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  checkButtons();

  patterns[currentPattern].pointer();
}

void checkButtons() {
  for (uint8_t i = 0; i < numPatterns; i++) {
    if (i == currentPattern) continue;
    if (digitalRead(patterns[i].pin) == LOW) {
      Serial.print(i);
      Serial.println(" was pressed");
      currentPattern = i;
      break;
    }
  }
}
