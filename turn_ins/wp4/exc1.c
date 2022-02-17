#include "TimerOne.h"

float temp = 0;
int limits[6] = {0, 10, 30, 60, 100};
int pins[5] = {0, 0, 0, 0, 0};

void which_LEDS_are_on();

void setup()
{
    pinMode(A0, INPUT);
    pinMode(7, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(3, OUTPUT);
    Timer1.initialize(100000);

    Serial.begin(9600);
    Timer1.attachInterrupt( readTemp );
    //int pins[5] = {0, 0, 0, 0, 0};
    //pins_pt = &pins[0];
    // set interrupt using timer calling readTemp as ISR
}

void loop()
{
    for (int i = 7; i > 2; i--)
    {
        digitalWrite(i, LOW);
    }

    which_LEDS_are_on();

    delay(1000);
}

void readTemp()
{
    int temperature = analogRead(A0);
    float voltage = temperature * 5.0;
    voltage /= 1024.0;
    temp = (voltage - 0.55) * 100;
    Serial.print(temp);
    Serial.println("temperature");
}

void which_LEDS_are_on()
{
    int pin = 7;
    int length = sizeof(limits) / sizeof(*limits);
    for (int i = 0; i < 5; i++)
    {
        Serial.print("templim : ");
        Serial.println(limits[i]);
        if (temp >= limits[i])
        {
            digitalWrite(pin, HIGH);
        }
        pin--;
    }
}

