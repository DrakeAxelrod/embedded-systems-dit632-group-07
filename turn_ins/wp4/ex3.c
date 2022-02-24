// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 4
// Exercise 3
// Submission code: BJGIKTJU

#include <Arduino.h> // for arduino functionality
#include <Adafruit_NeoPixel.h> // header for the led ring functionality
#include TimerOne.h

const int neoPin = 5; // the pin number of the neopixel strip
const int numLeds = 16; // number of the leds
int tempC; // temperature in celsius

Adafruit_NeoPixel disc = Adafruit_NeoPixel(numLeds, neoPin, NEO_GRB + NEO_KHZ800); // object for led ring

float range[] = {-30.0, -20.0, -10.0, 0.0, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110.0, 120.0};
// array of breakpoints for the temperature

// setup the pin modes, start serial, initial brightness, start Neopixel Disc
void setup()
{
  // put your setup code here, to run once:
  pinMode(neoPin, OUTPUT); // set digital pin 5 to output
  pinMode(A0, INPUT); // set analogue pin 0 to input
  disc.begin(); //to start the led ring
  Serial.begin(9600); // initializes serial
  disc.setBrightness(120); // half brightness
  Timer1.initialize(100000); // initialise the timer with 100 milliseconds
  Timer1.attachInterrupt( checkTemp ); // set an interrupt on the timer, with a callback function that will read the temperature
}

void loop() // function that will iterate until the program ends
{
  setColors(); // call function to set the colors
  delay(100); // delay (100 arbitrarily chosen)
}

void checkTemp() // function to check the temperature
{
  int temperature = analogRead(A0); // to get temp from analogue pin
  float voltage = temperature * (5.0 / 1024); // convert analog to voltage
  tempC = (voltage - 0.5) * 100; // converting from voltage with offset to get the temp
}

void setColors()// function to set the colors on the LED ring
{
  uint16_t i; // unsigned int of 16 bits
  for (i = 0; i < 16; i++) // for loop for range of LEDs on the ring
  {
    if (tempC > range[i]) // if the temperature is in the correct range
    {
      disc.setPixelColor(i, getColor((i * 16) & 255)); // set the color to display on the LED ring
      disc.show(); // re-renders the leds on the ring
    }
    else // else if its in the wrong range
    {
      disc.setPixelColor(i, disc.Color(0, 0, 0)); // turns off the ring's lights (all rgb values 0)
    }
  }
  if (tempC >= 120) // if the temperature is greater than 120 c
  {
    digitalWrite(neoPin, HIGH); // turn on LED
  }
  else // else if the temperature is not >= 120 c
  {
    digitalWrite(neoPin, LOW); // turn off LED
  }
}


uint32_t getColor(byte color) // function for getting getting the colours in hex
{
  /* function to get rainbow colours for the Neopixel ring by mattnupen on codebender. */
  if (color < 85) // if the value is less than 85
  {
    return disc.Color(color * 3, 255 - color * 3, 0); // increase the red, decrease the green, and set blue to 0
  }
  else if (color < 170) // if the value is between 85 and 170
  {
    color -= 85; // decresae the value so that it the equation will stay in range
    return disc.Color(255 - color * 3, 0, color * 3); // decrease the red, set green to 0, and increase the blue
  }
  else // if the value is between 170 and 255
  {
    color -= 170; // decresae the value so that it the equation will stay in range
    return disc.Color(0, color * 3, 255 - color * 3); // set red to 0, increase the green, and decrease the blue
  }
}