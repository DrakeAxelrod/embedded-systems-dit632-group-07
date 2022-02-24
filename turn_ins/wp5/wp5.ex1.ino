// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 5
// Exercise 1
// Submission code :
// modified by Drake Axelrod, Vernita Gouws, Silicly Ann Brannen for wp5
// taken from wp3
const byte LED = 5;
const byte BUTTON = 7;

// Interrupt Service Routine (ISR)
void switchPressed ()
{
  if (digitalRead (BUTTON) == HIGH)
    digitalWrite (LED, LOW);
  else
    digitalWrite (LED, HIGH);
}  // end of switchPressed

void setup ()
{
  pinMode (LED, OUTPUT);  // so we can update the LED
  digitalWrite (BUTTON, HIGH);  // internal pull-up resistor
  attachInterrupt (digitalPinToInterrupt (BUTTON), switchPressed, CHANGE);  // attach interrupt handler
}  // end of setup

void loop ()
{
  if (digitalRead (BUTTON) == HIGH)
    digitalWrite (LED, LOW);
  else
    digitalWrite (LED, HIGH);
  // loop doing nothing 
}
