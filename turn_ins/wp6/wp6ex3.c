// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 6
// Exercise 3
// Submission code: MYESOG6S

#include <Arduino.h>
#include <Keypad.h>
#include <Adafruit_NeoPixel.h>
#include <string.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

// function declarations
void keyEv(KeypadEvent);                // declare function to process the keypad events
void interdimensional_warp_activated(); // runs the accepted sequence
void err();                             // runs the error sequence
void red();                             // collors all neopixels red
void reset();                           // turns off all pixels on the neopixel ring
void lockpos(int);                      // runs the lock position animations and logic
uint32_t getColor(byte);

const byte ROWS = 4; // four rows
const byte COLS = 4; // three columns
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'B'}};
byte rowPins[ROWS] = {7, 6, 5, 4};   // connect to the row pinouts of the kpd
byte colPins[COLS] = {11, 10, 9, 8}; // connect to the column pinouts of the kpd

Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int NEOPIN = 2;

// Parameter 1 = number of pixels in disc
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel disc = Adafruit_NeoPixel(60, NEOPIN, NEO_GRB + NEO_KHZ800);
uint8_t offset = 0;        // Position of spinny eyes
uint32_t color = 0xFF0000; // Start red

int numPresses = 0;

int locked[7] = {0, 0, 0, 0, 0, 0, 0}; // representation of locked positions
int locks[7][2] = {{1, 2}, {4, 5}, {7, 8}, {13, 14}, {16, 17}, {19, 20}, {22, 23}}; // pixels to be locked corresponding to sequence
// colors corrensponfing to sequence (r,g,b)
int lockColors[7][3] = {{255, 0, 0}, {255, 127, 0}, {255, 255, 0}, {0, 255, 0}, {0, 0, 255}, {75, 0, 130}, {143, 0, 255}};
// array to hold the pressed keys init as all 0
char presses[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
// all the valid sequences to compare against
char valid[7][9] = {
    "13654329",
    "A4D21439",
    "C21A32B9",
    "98765439",
    "12345699",
    "B42A3C39",
    "DABCACB9"};

// debugging function
void printPresses()
{
  for (int i = 0; i < 8; i++) // runs through the presses
  {
    Serial.print(presses[i]); // prints the char
  }
  Serial.print("\n"); // new line
}

// setup function before we enter loop
void setup()
{
  // kpd.begin(makeKeymap(keys));
  // keypad
  kpd.addEventListener(keyEv); // Add an event listener for this keypad
  // neopixel ring setup
  disc.begin();           // start the neopixel
  disc.setBrightness(50); // set the brightness of the ring to 50%
  disc.show();            // Initialize all pixels to 'off'
  Serial.begin(9600);     // allow for serial printing
}

// main loop of the program
void loop()
{
  kpd.getKey(); // gets the key presses (and triggers keyEv on change)
}

// event handler for keypad events
void keyEv(KeypadEvent key)
{
  switch (kpd.getState()) // gets the state of the key and switch off it
  {
  case PRESSED:                // key was pressed
    locked[numPresses] = 1;    // set the position to locked
    presses[numPresses] = key; // set the array at the current pressed position to the key
    lockpos(numPresses);       // call the function to turn on the disc's lights on entry of the code
    numPresses++;              // increment the amount of presses that have occurred
    if (numPresses == 8)       // if the max amount of presses are reached
    {
      int accepted = 1;           // i
      for (int i = 0; i < 8; i++) // check against all accepted sequences
      {
        accepted = strcmp(presses, valid[i]); // compare the pressed keys to the accepted sequences
        if (accepted == 0)                    // if we hit an accepted sequence we can leave the loop
        {
          break; // leave the loop
        }
      }
      if (accepted == 0) // we matched an accepted sequence
      {
        interdimensional_warp_activated(key); // accepted sequence run the accepted function
      }
      else // pressed keys did not match any of the accepted sequences.
      {
        err(); // not an accepted sequence run the error function
      }
    }
    break;
  case RELEASED: // key was released
    break;
  case HOLD: // key was held
    break;
  case IDLE: // nothing
    break;
  }
}

/* accepted sequence animation function */
void interdimensional_warp_activated()
{
  for (int i = 0; i < 3; i++) // inner loop runs for approxiamtely 1s (atleast during testing) so loop 3 times
  {
    uint16_t i, j;            // i and j interator variabnles
    for (j = 0; j < 256; j++) // run through all the color values (255 is max for rgb)
    {
      for (i = 0; i < disc.numPixels(); i++) // loop through all the pixels in the ring
      {
        disc.setPixelColor(i, getColor((i * 2 + j) & 255)); // color the pixel on a scale
      }
      disc.show(); // update the neopixel
      delay(1); // wait 1ms
    }
  }
  reset();                    // reset the ring too all off
  numPresses = 0;             // reset number of presses
  for (int i = 0; i < 7; i++) // loop through locked and reset to 0
  {
    locked[i] = 0; // reset locked positions
  }
}

/* run the dial / lock in animation */
void dial(int pos)
{
  for (int i = 0; i < 4; i++) // flash on and off the corresponding color for this lock position
  {
    int on = i % 2;              // if even then we can set colors else turn off
    for (int j = 0; j < 24; j++) // run through all pixels
    {
      // honestly shouldn't matter if you color on (!on or on) you just want it to switch between states so you get the double flash
      if (!on) // if not on color
      {
        disc.setPixelColor(j, lockColors[pos][0], lockColors[pos][1], lockColors[pos][2]); // use the correspond position to color the relevant pixels
      }
      else // set lights to off
      {
        disc.setPixelColor(j, 0, 0, 0); // set the pixel to not show
      }
    }
    disc.show(); // update the ring
    delay(200);  // 200ms delay
  }
  delay(200); // 200ms delay
}

/* handles the locking of a position in the sequence and running the corresponding animation */
void lockpos(int pos)
{
  dial(pos);                  // run the dial sequence
  locked[numPresses] = 1;     // lock our current position
  for (int i = 0; i < 7; i++) // loop through 7 times for the locked positions
  {
    if (locked[i] == 1)
    { // if a position has been locked paint it
      // using the arrays to reference the relevant positions and colors according to the
      // step in the sequence.
      //                 pixel             Red              Green                    Blue
      disc.setPixelColor(locks[i][0], lockColors[i][0], lockColors[i][1], lockColors[i][2]);
      //                 pixel             Red              Green                    Blue
      disc.setPixelColor(locks[i][1], lockColors[i][0], lockColors[i][1], lockColors[i][2]);
    }
  }
  disc.show(); // update the neopixel ring
}

/* function that is fired when a wrong code is entered. The light flashes red, and resets*/
void err()
{
  red();                      // call function to set disc color to red
  delay(100);                 // 100ms delay
  reset();                    // call function to reset disc color
  delay(100);                 // 100ms delay
  red();                      // call function to set disc color to red
  delay(100);                 // 100ms delay
  numPresses = 0;             // reset the variable storing amount of presses
  for (int i = 0; i < 7; i++) // loop 7 times
  {
    locked[i] = 0; // set element in array to 0
  }
  reset(); // call function to reset disc color
}

/* function to change the dics's color to red (fired when code is incorrect) */
void red()
{
  for (int i = 0; i < 24; i++) // for each led in the ring (24)
  {
    disc.setPixelColor(i, 255, 0, 0); // set the pixels to red
  }
  disc.show(); // sends the data above to the disc
}

/* function to reset the dics's color */
void reset()
{
  for (int i = 0; i < 24; i++) // for each led in the ring
  {
    disc.setPixelColor(i, 0, 0, 0); // set the pixels to no color
  }
  disc.show(); // send the data to the disc
}

// ===== https://codebender.cc/sketch:80438#Neopixel%20Rainbow.ino ===== //
uint32_t getColor(byte color) // function for getting getting the colours in hex
{
  /* function to get rainbow colours for the Neopixel ring by mattnupen on codebender. */
  if (color < 85) // if the value is less than 85
  {
    return disc.Color(color * 3, 255 - color * 3, 0); // increase the red, decrease the green, and set blue to 0
  }
  else if (color < 170) // if the value is between 85 and 170
  {
    color -= 85;                                      // decresae the value so that the equation will stay in range
    return disc.Color(255 - color * 3, 0, color * 3); // decrease the red, set green to 0, and increase the blue
  }
  else // if the value is between 170 and 255
  {
    color -= 170;                                     // decresae the value so that it the equation will stay in range
    return disc.Color(0, color * 3, 255 - color * 3); // set red to 0, increase the green, and decrease the blue
  }
}
// ==================================================================== //
