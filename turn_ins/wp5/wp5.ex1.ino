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


// sudo chmod a+rw /dev/ttyACM0 - permission to upload the sketch
static int state = 0;
void setup() // initialize the program
{
  pinMode(0, INPUT); // set the pin 5 to input
  pinMode(7, OUTPUT); // set the pin 7 to output
  pinMode(3, OUTPUT); // set the pin 3 to output
  attachInterrupt(digitalPinToInterrupt(7), blink, CHANGE);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(3, digitalRead(0) == LOW ? HIGH : LOW);
  blink();
}

void blink() {
  delay(1000);
  digitalWrite(7, state); // change the voltage to high for pin 13
  state = !state;
}