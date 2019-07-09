// patterns are comprised of two parts:
// the callback and the registry.
// the callback is made with the ON_RUN_PATTERN macro, as follows:
//
// ON_RUN_PATTERN([name of pattern],
// {
//   [code]
// })
//
// the name of the pattern must not contain spaces.
// whatever code you want to run the pattern goes in the code
// block. keep in mind that this code is executed repeatedly,
// at a rate of roughly 100 thousand times per second. thus,
// try to keep the time to execute the code block under 100ms.
// as long as there are no delay()s, the code should always
// take less than 100ms.
//
// the second part of a pattern is the registry, which is at the bottom of the file.
//
// the neopixel api is exposed through an object called "leds". it's an instance of
// Adafruit_NeoPixel, which is from the Adafruit NeoPixel library: https://github.com/adafruit/Adafruit_NeoPixel
//
// The configuration for the NeoPixel is under the file called Kedavara.
// If you want to change the number of LEDs on the strip, it's defined by #define NUMPIXELS.
// To change the pin the NeoPixel is connected to, change #define NEOPIXEL_PIN.

ON_RUN_PATTERN(one,
{
  // clear the display
  leds.clear();
  delay(10);
})

ON_RUN_PATTERN(two,
{
  delay(10);
})

ON_RUN_PATTERN(three,
{
  delay(10);
})

ON_RUN_PATTERN(four,
{
  delay(10);
})

ON_RUN_PATTERN(five,
{
  delay(10);
})

ON_RUN_PATTERN(six,
{
  delay(10);
})

ON_RUN_PATTERN(seven,
{
  delay(10);
})

ON_RUN_PATTERN(eight,
{
  delay(10);
})

ON_RUN_PATTERN(nine,
{
  delay(10);
})

ON_RUN_PATTERN(zero,
{
  delay(10);
})

// this is the registry. every pattern must be registered.
// if a pattern is missing a callback, the code won't compile.
// if a pattern is missing a registry, it will fail silently -
// that is, the underlying software won't recognize the pattern
// correctly.
//
// registry calls are made using the REGISTER_PATTERN macro.
// the first argument is the name of the pattern. the second
// argument is the physical pin the pattern corresponds to.
// whenever this pin is shorted to ground, the corresponding
// pattern is started. if the pattern is already the active
// pattern, the input is ignored.
//
// registry calls should be placed between "REGISTRY START"
// and "REGISTRY END"
__struct_pattern patterns[] = {
  // REGISTRY START
  REGISTER_PATTERN(1, 3)
  REGISTER_PATTERN(two, 4)
  REGISTER_PATTERN(three, 5)
  REGISTER_PATTERN(four, 6)
  REGISTER_PATTERN(five, 7)
  REGISTER_PATTERN(six, 8)
  REGISTER_PATTERN(seven, 9)
  REGISTER_PATTERN(eight, 10)
  REGISTER_PATTERN(nine, 11)
  REGISTER_PATTERN(zero, 12)
  // REGISTRY END
};
