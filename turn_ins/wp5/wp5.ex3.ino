// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 5
// Exercise 3
// Submission code :
// modified by Drake Axelrod, Vernita Gouws, Silicly Ann Brannen for wp5
// taken from wp3
#include <stdio.h>   // standard lib
#include <Arduino.h> // header file for Arduino functions

int calculate_light_intensity(int); // define function
int determine_light(float, int, int); // define function
int lightV = 0; // variable for light intensity
float tempC = 0; // variable for temperature
float offset = 0.55;  // 500 mV offset + 50mV offset for resistor over temp guage and ground
int pin = 0; // set global variable to hold the value of the lit LED

void setup() // initialize the program
{
    pinMode(A0, INPUT); // sets analog pin A0 to input mode
    Serial.begin(9600); // opens the serial port
    pinMode(A3, INPUT); // sets analog pin A3 to input mode
    pinMode(4, OUTPUT); // sets pin 2 to output mode for the blue LED
    pinMode(5, OUTPUT); // sets pin 3 to output mode for the green LED
    pinMode(6, OUTPUT); // sets pin 4 to output mode for the red LED
}

void loop() // function that will iterate while the program is running
{ 
  int temperature = analogRead(A0); // reads temperature from analog pin A0
  int light = analogRead(A3); // reads temperature from analog pin A3
  Serial.print("light ");
  Serial.println(light);
  float voltage = temperature * (5.0 / 1024); // convert analog to voltage
  tempC = (voltage - 1.45) * 100 ;  // remove offset, then convert using 10mV per degree               
 
  lightV = calculate_light_intensity(light); // set lightV to the return of the function
  //consider the floats in the temperature
   
    digitalWrite(pin, LOW); // reset the pin previously lit up
    if (lightV == 0) // if light is 0
    {
        pin = determine_light(tempC, -40, -13); // call function to determine which pin to light and set to variable pin
    }
    else if (lightV <= 20) // if light is 0 and 20
    {
        pin = determine_light(tempC, -12, 0); // call function to determine which pin to light and set to variable pin
    }
    else if (lightV <= 60) // if light is between 20 and 60
    {
        pin = determine_light(tempC, 0, 20); // call function to determine which pin to light and set to variable pin
    }
    else // if lightV is between 60 and max
    {
        pin = determine_light(tempC, 21, 50); // call function to determine which pin to light and set to variable pin
    }
    // Delay a little bit to improve simulation performance
    digitalWrite(pin, HIGH); // turn on the correct LED
    Serial.print("tempC ");
    Serial.println(tempC);
    Serial.print("lightV ");
    Serial.println(lightV);
    Serial.print("pin ");
    Serial.println(pin);
    delay(500); // wait 0.5 seconds in between loops
}

int calculate_light_intensity(int reading) // function to convert the light reading to a value between 0 and 100
{

    return map(reading, 14, 250, 0, 100); // returns the converted value
}

int determine_light(float value, int min, int max) { // function to determine which LED will be lit
    if (value <= min) // if the temperature is below min
        return 4; // return pin 2 (blue LED)
    else if (value >= max) // if the temperature is above max
        return 6; // return pin 4 (red LED)
    else // if the temperature is in the correct range
        return 5; // return pin 3 (green LED)
}


/* Table to show the correct ranges 
< -12 °C     0%
-12 °C - 0 °C   1% - 20%
0 °C - 20 °C  21% - 60%
>= 21 °C    61% - 100% */