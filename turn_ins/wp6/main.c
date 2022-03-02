#include <Arduino.h>
#include <Keypad.h>
#include <Adafruit_NeoPixel.h>
#include <string.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

// function declarations
void keyEv(KeypadEvent key);
void interdimensional_warp_activated(char key);
void err();
void red();
void reset();
void lockpos(int pos);
uint32_t Wheel(byte WheelPos);
void rainbow();

const byte ROWS = 4; // four rows
const byte COLS = 4; // three columns
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'B'}
};
byte rowPins[ROWS] = {7, 6, 5, 4}; // connect to the row pinouts of the kpd
byte colPins[COLS] = {11, 10, 9, 8};    // connect to the column pinouts of the kpd

Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int NEOPIN = 2;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, NEOPIN, NEO_GRB + NEO_KHZ800);
uint8_t offset = 0;        // Position of spinny eyes
uint32_t color = 0xFF0000; // Start red

int numPresses = 0;

int locked[7] = { 0, 0, 0, 0, 0, 0, 0 };
int locks[7][2] = { {1,2}, {4,5}, {7,8}, {13,14}, {16,17}, {19,20}, {22,23} };
int lockColors[7][3] = { {255, 0, 0}, {255, 127, 0}, {255, 255, 0}, {0, 255, 0}, {0, 0, 255}, {75, 0, 130}, {143, 0, 255} };
char presses[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
char valid[7][9] = {
    "13654329",
    "A4D21439",
    "C21A32B9",
    "98765439",
    "12345699",
    "B42A3C39",
    "DABCACB9"};


void printPresses()
{
  for (int i = 0; i < 8; i++)
  {
    Serial.print(presses[i]);
  }
  Serial.println("");
}
void setup()
{
  // kpd.begin(makeKeymap(keys));
  // keypad
  kpd.addEventListener(keyEv); // Add an event listener for this keypad
  // neopixel ring setup
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
}

void loop() {
  kpd.getKey();
}

// Taking care of some special events.
void keyEv(KeypadEvent key)
{
  switch (kpd.getState())
  {
    case PRESSED:
      locked[numPresses] = 1;
      presses[numPresses] = key;
      lockpos(numPresses);
      numPresses++;
      if (numPresses == 8) {
        int accepted = 1;
        for (int i = 0; i < 8; i++) {
          accepted = strcmp(presses, valid[i]);
          if (accepted == 0) {
            break;
          }
        }
        printPresses();
        if (accepted == 0)
        {
          interdimensional_warp_activated(key);
        }
        else
        {
          err();
        }
      }
      // Serial.print("pressed key -> ");
      // Serial.println(key);
      break;
    case RELEASED:
      // Serial.print("released key -> ");
      // Serial.println(key);
      break;
    case HOLD:
      // Serial.print("holding -> ");
      // Serial.println(key);
      break;
    case IDLE:
      break;
  }
}

void interdimensional_warp_activated(char key) {
  Serial.print("last pressed: ");
  Serial.println(key);
  for (int i = 0; i < 3; i++) {
    rainbow();
  }
  reset();
  numPresses = 0;
  for (int i = 0; i < 7; i++)
  {
    locked[i] = 0;
  }
}

void dial(int pos) {
  for (int i = 0; i < 4; i++)
  {
    int on = i % 2;
    for (int j = 0; j < 24; j++)
    {
      if (!on) {
        strip.setPixelColor(j, lockColors[pos][0], lockColors[pos][1], lockColors[pos][2]);
      }
      else
      {
        strip.setPixelColor(j, 0, 0, 0);
      }
    }
    strip.show();
    delay(200);
  }
  delay(200);
}

void lockpos(int pos) {
  dial(pos);
  locked[numPresses] = 1;
  for (int i = 0; i < 7; i++) {
    if (locked[i] == 1) {
      strip.setPixelColor(locks[i][0], lockColors[i][0], lockColors[i][1], lockColors[i][2]);
      strip.setPixelColor(locks[i][1], lockColors[i][0], lockColors[i][1], lockColors[i][2]);
    }
  }
  strip.show();
}

void err() {
  red();
  delay(100);
  reset();
  delay(100);
  red();
  delay(100);
  numPresses = 0;
  for (int i = 0; i < 7; i++)
  {
    locked[i] = 0;
  }
  reset();
}

void red() {
  for (int i = 0; i < 24; i++)
  {
    strip.setPixelColor(i, 255, 0, 0);
  }
  strip.show();
}

void reset() {
  for (int i = 0; i < 24; i++)
  {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85)
  {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if (WheelPos < 170)
  {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else
  {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void rainbow()
{
  uint16_t i, j;
  for (j = 0; j < 256; j++)
  {
    for (i = 0; i < strip.numPixels(); i++)
    {
      strip.setPixelColor(i, Wheel((i * 2 + j) & 255));
    }
    strip.show();
    delay(1);
  }
}
