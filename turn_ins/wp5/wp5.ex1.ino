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

