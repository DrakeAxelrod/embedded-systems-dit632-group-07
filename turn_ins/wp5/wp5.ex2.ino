// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 5
// Exercise 2
// Submission code: 2NBFZAGQ
// modified by Drake Axelrod, Vernita Gouws, Silicly Ann Brannen for wp5
// taken from wp3
#include <TimerOne.h> // interrupt library

float temperature = 0; // temp variable
int range[5] = {0, 10, 20, 30, 40}; // range of values to light up LEDS at
int pins[5] = { 7, 6, 5, 4, 3 }; // representations of pins corresponding to range

void which_LEDS_are_on(); // function declaration

// init basically
void setup()
{
  pinMode(A0, INPUT); // temp pin
  pinMode(7, OUTPUT); // led pin
  pinMode(6, OUTPUT); // led pin
  pinMode(5, OUTPUT); // led pin
  pinMode(4, OUTPUT); // led pin
  pinMode(3, OUTPUT); // led pin
  Serial.begin(9600); // start
  // set interrupt using timer calling syncTemp as ISR
  Timer1.initialize(500000);         // initialize timer1, and set a 1/2 second period
  Timer1.pwm(A0, 512);                // setup pwm on pin 9, 50% duty cycle
  Timer1.attachInterrupt(syncTemp); // attach callback
}

// basically just chill out bro (main loop although we dont use it since we are demonstrating interrupts)
void loop()
{
 // huge delay to prove interrupt works
}

// read the temperature and convert to celcius
void syncTemp()
{
  // lines 36-38 are from https://docs.wokwi.com/parts/wokwi-ntc-temperature-sensor
//  float beta = 3950; // should match the Beta Coefficient of the thermistor
//  int val = analogRead(A0); // read the analog pin values
//  temperature = 1 / (log(1 / (1023.0 / val - 1)) / beta + 1.0 / 298.15) - 273.15; // convert to celcius
//  temperature = temperature /100;
  int temp = analogRead(A0); // get the analog temperature from the pin
  float voltage = temp * 5.0; //  convert the temperature into voltage
  voltage /= 1024.0; // voltage is converted
  temperature = (voltage - 1.45) * 100; // use the offset on voltage and 10mV per degree, to get temperature in celsius
  Serial.println(temperature);
  which_LEDS_are_on(); // turn on lights depending on temp
}

// power the LED's corresponding to the relevant temperature range
void which_LEDS_are_on()
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