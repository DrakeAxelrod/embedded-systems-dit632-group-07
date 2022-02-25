// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 5
// Exercise 1
// Submission code: 2NBFZAGQ
// modified by Drake Axelrod, Vernita Gouws, Silicly Ann Brannen for wp5
// base code reused from WP3 of our group's hand-in

static int state = 0;

void blink(); // function declaration

void setup() // initialize the program
{
  pinMode(0, INPUT); // set the pin 5 to input
  pinMode(7, OUTPUT); // set the pin 7 to output
  pinMode(3, OUTPUT); // set the pin 3 to output
  attachInterrupt(digitalPinToInterrupt(7), blink, CHANGE); // set the interrupt to call blink every time the LED is changed (which happens every time blink runs)
}

// function that iterates until the program is ended
void loop() {
  digitalWrite(3, digitalRead(0) == LOW ? HIGH : LOW); // set the pin to high if the button is pressed, and to low if button is released
  blink(); // function call to blink an LED with 1 second intervals
}

// function that blinks the LED
void blink() {
  delay(1000); // delay of 1 second before the LED is turned on or off
  digitalWrite(7, state); // change the voltage to high for pin 13
  state = !state; // change the state between 1 and 0
}