//#include <Adafruit_NeoPixel.h>
#include <Adafruit_DotStar.h>
#include <Bounce2.h>

#define PIN_ON        3
#define PIN_COLOR     4
//#define PIN_NEOPIXEL  4
#define PIN_CLOCK     13  // use hardware SPI pins
#define PIN_DATA      11  // use hardware SPI pins
#define PIN_LED        1

#define NUMPIXELS     2

#define END           0x0000000 // end of colors flag

static Bounce colorchange = Bounce();
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(
//    1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
//static Adafruit_DotStar rgbled = Adafruit_DotStar(
//  NUMPIXELS, PIN_DATA, PIN_CLOCK, DOTSTAR_BRG);
static Adafruit_DotStar rgbled = Adafruit_DotStar(
  NUMPIXELS, DOTSTAR_BGR);

static uint32_t  sequence[] = {
  0xff00ff, // purple (peace)
  0xff0000, // red (love)
  0xffffff, // white (&)
  0x00ff00, // green (kale)
  0xffff00, // yellow (banana)
  END       // end of sequence
};

static uint32_t  tsequence[] = {
  0x00000001,
  0x00000010,
  0x00000100,
  0x00001000,
  0x00010000,
  0x00100000,
  0x01000000,
  0x10000000,
  0x04040404,
  0x04040400,
  0x00040404,
  END       // end of sequence
};

static boolean  last;
static int      index;
static uint32_t curcolor;

void
setup()
{
  pinMode(PIN_ON, INPUT_PULLUP);
  pinMode(PIN_COLOR, INPUT_PULLUP);
  //pinMode(PIN_LED, OUTPUT);

  colorchange.attach(PIN_COLOR);
  colorchange.interval(5);  // debounce time in milliseconds

  //digitalWrite(PIN_LED, LOW);

  rgbled.begin(); // initialize pins for output
  rgbled.show();  // turn off LEDs

  rgbled.setPixelColor(0, 0xff00ff);
  rgbled.setPixelColor(1, 0x00ff00);
  rgbled.show();

  delay(300);
  //digitalWrite(PIN_LED, HIGH);

  rgbled.setPixelColor(0, 0x040404);
  rgbled.setPixelColor(1, 0x040408);
  rgbled.show();

  delay(300);
  //digitalWrite(PIN_LED, LOW);

  index    = 0;
  curcolor = sequence[index];
  last     = true;
}

void
loop()
{
  boolean   state;
  uint32_t  setcolor;
  colorchange.update();
  //state = colorchange.read();
  //change = colorchange.fallingEdge();

  state = colorchange.read();

  if (state != last) {
    if (state) {
      if (curcolor != END) {
        ++index;
        curcolor = sequence[index];
      }
    }
    last = state;
  }

  setcolor = digitalRead(PIN_ON) ? 0x000000 : curcolor;

  rgbled.setPixelColor(0, setcolor);
  rgbled.setPixelColor(1, setcolor);
  rgbled.show();
}
