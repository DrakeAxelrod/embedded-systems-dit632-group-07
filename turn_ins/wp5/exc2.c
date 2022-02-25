// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 5
// Exercise 2
// Submission code: 2NBFZAGQ
// modified by Drake Axelrod, Vernita Gouws, Silicly Ann Brannen for wp5
// taken from wp3
#include <Arduino.h> // for c files you need to include the arduino lib
#include <TimerOne.h> // interrupt library
#include <math.h> 

float offset = 1.45; // offset of a 500mV base, and taking the resistors in the system into account
float temperature = 0; // temp variable
int range[5] = {0, 10, 20, 30, 40}; // range of values to light up LEDS at
int pins[5] = { 7, 6, 5, 4, 3 }; // representations of pins corresponding to range

void which_LEDS_are_on(); // function declaration

void setup() // prerun configuration
{
  pinMode(A0, INPUT); // temp pin
  pinMode(7, OUTPUT); // led pin
  pinMode(6, OUTPUT); // led pin
  pinMode(5, OUTPUT); // led pin
  pinMode(4, OUTPUT); // led pin
  pinMode(3, OUTPUT); // led pin
  Serial.begin(9600); // start
}

void loop() // iterate until program is ended
{
 syncTemp(); // function call to get the current temperature
 delay(500);
}

// read the temperature and convert to celcius
void syncTemp()
{ int temp = analogRead(A0); // get the analog temperature from the pin
  float voltage = temp * 5.0; //  convert the temperature into voltage
  voltage /= 1024.0; // voltage is converted
  temperature = (voltage - offset) * 100; // use the offset on voltage and 10mV per degree, to get temperature in celsius
  turn_on_LEDS(); // function call to 
}

// power the LED's corresponding to the relevant temperature range
void turn_on_LEDS()
{
  int len = sizeof(range) / sizeof(*range); // length of range (we know its five but for scalability)
  for (int i = 0; i < len; i++) // loop through the range
  {
    if (temperature >= (float)range[i]) { // if the temp is over a certain step in range light LED
      digitalWrite(pins[i], HIGH); // write HIGH to LED correspong to temperature step in range
    } else { // if the pin is not at a temp above the correspond step turn off
      digitalWrite(pins[i], LOW); // write LOW to LED temp is below step
    }
  }
}