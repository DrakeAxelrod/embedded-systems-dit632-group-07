#include <stdio.h>
#include <Arduino.h>

int calculate_light_intensity(int);
int lightV = 0;
float tempC = 0;
float offset = 0.55;
int pin = 0;
void setup()
{
    pinMode(A0, INPUT);
    Serial.begin(9600);
    pinMode(A3, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
}

void loop()
{
    // read from A0
    int readingTemp = analogRead(A0);
    int readingLight = analogRead(A3);
    Serial.println(readingLight);

    float voltage = readingTemp * 5.0;
    voltage /= 1024.0;

    tempC = (voltage - offset) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
    //to degrees ((voltage - 500mV) times 100)
    Serial.print(tempC); Serial.println(" degrees C");

    lightV = calculate_light_intensity(readingLight);
    Serial.println(lightV);

    digitalWrite(pin, LOW);
    if (lightV == 0)
    {
        pin = determine_light(tempC, -40, -13);
    }
    else if (lightV <= 20)
    {
        pin = determine_light(tempC, -12, 0);
    }
    else if (lightV <= 60)
    {
        pin = determine_light(tempC, 0, 20);
    }
    else //if (lightV <= 100)
    {
        pin = determine_light(tempC, 21, 50);
    }
    // Delay a little bit to improve simulation performance
    digitalWrite(pin, HIGH);
    delay(100);
}

int calculate_light_intensity(int reading)
{
    return map(reading, 6, 679, 0, 100);
}

int determine_light(int value, int min, int max) {
    if (value <= min)
        return 2;
    else if (value >= max)
        return 4;
    else
        return 3;
}

