#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// this corresponds to how many pixels there are in the entire neopixel strip
#define NUMPIXELS 16
// this is the pin that the neopixel is connected to
#define NEOPIXEL_PIN 6

Adafruit_NeoPixel leds(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

#include "defines.h"
#include "patterns.h"

// required to access this variable here, since it was declared in patterns.h
extern __struct_pattern patterns[];

uint8_t currentPattern;
uint8_t numPatterns;

void setup() {
  // required for trinket
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif

  leds.begin();
  
  Serial.begin(115200);
  // calculate how many patterns have been registered
  numPatterns = sizeof(patterns) / sizeof(__struct_pattern);
  Serial.print("Found ");
  Serial.print(numPatterns);
  Serial.println(" patterns");

  // configure the pins to INPUT_PULLUP
  for (uint8_t i = 0; i < numPatterns; i++) {
    pinMode(patterns[i].pin, INPUT_PULLUP);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  checkButtons();

  // call the code for the active pattern
  patterns[currentPattern].pointer();
}

// check for new inputs.
// this is a seperate function to allow
// possible usage of external interrupts.
// if interrupts are used, a pattern's code
// can use delay() all it wants without
// inputs being dropped.
void checkButtons() {
  for (uint8_t i = 0; i < numPatterns; i++) {
    if (i == currentPattern) continue;
    // no debouncing is needed, since inputs from the active pattern's button are ignored
    if (digitalRead(patterns[i].pin) == LOW) {
      Serial.print(i);
      Serial.println(" was pressed");
      currentPattern = i;
      // we only want to accept one button press at a time
      // with the current implementation, the pattern that
      // was registered first is given precedence
      break;
    }
  }
}
