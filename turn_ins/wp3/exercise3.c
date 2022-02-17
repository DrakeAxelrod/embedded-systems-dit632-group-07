#include <stdlib.h>
#include <Arduino.h> // header file for Arduino functions

float tempC = 0; // set variable for temperature
float offset = 0.55; // 500mV offset + 50mV from the 1kohm resistor into account

void setup() // initialize the program
{
    pinMode(A0, INPUT); // set analog pin A0 to input mode
    Serial.begin(9600); // opens the serial port
}

void loop() // function that will iterate while the program is running
{
    // read from A0
    int temperature = analogRead(A0);           // reads temperature from analog pin A0
    float voltage = temperature * (5.0 / 1024); // convert analog to voltage

    tempC = (voltage - offset) * 100; // converting from 10 mv per degree wit
    // to degrees ((voltage - 500mV) times 100)
    Serial.print(tempC); // print temperature
    Serial.println(" degrees C"); // print degrees string
    delay(500); // wait half a second in between loops
}
