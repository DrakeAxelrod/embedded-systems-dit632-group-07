// WP 6 Exercise 1 Template DIT 632
// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 6
// Exercise 1
// Submission code: MYESOG6S

#include <Arduino.h>

#define ENCA 2
#define ENCB 3
#define PWM1 5
#define PWM2 6

int pos = 0; // Position in ticks
int deg = 0; // Position in degrees

int degtarget = 0; // Target position in degrees

int speed = 0; // Desired motor speed

int kp = 100;  // Proportional constant for controller (tuning parameter)
int u_out = 0; // output of controller

int e = 0; // error
int a = 0; // a-encoder signal
int b = 0; // b-encoder signal


/* function to initialise the program - is executed once */
void setup()
{

  Serial.begin(9600); // initialise the serial monitor
  pinMode(ENCA, INPUT_PULLUP);
  pinMode(ENCB, INPUT_PULLUP);
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  // ========== Added ========== //
  attachInterrupt(digitalPinToInterrupt(ENCB), ISR_readEncoder, RISING); // Attach interrupt to ISR function on rising on channel B
  // =========================== //
  // attachInterrupt(digitalPinToInterrupt(5), ISR_readEncoder, CHANGE);
  //  Start the motor, just a tiny little bit because otherwise TinkerCad dies....
  analogWrite(PWM2, 10);
  delay(1000); // TinkerCad bug
  analogWrite(PWM1, 10);
}

/* function that iterates until program is terminated*/
void loop()
{
  // Stop the motor, but not to zero because then TinkerCad dies....
  analogWrite(PWM1, 10);
  delay(1000); // TinkerCad...bug
  analogWrite(PWM2, 10);

  // Check if motor rotated all the way around, and reset counter
  if (pos > 2299)
  {
    deg = deg - 359;
    pos = pos - 2299;
  }
  if (pos < 0)
  {
    deg = 359 + deg;
    pos = 2299 + pos;
  }

  // Print current position
  Serial.print("The current position is: ");
  Serial.print(deg);
  Serial.print("\n");
  // Get input
  degtarget = getInput();

  // Calculate initial error
  e = degtarget - deg;
  // ========== Added ========== //
  Serial.print("The current error: ");     // print the error
  Serial.print(e);                            // print the error
  Serial.print("\n");                         // print the error
  // =========================== //
  // Loop until error is zero
  while (e)
  {

    // Map current position into degrees
    deg = map(pos, 0, 2299, 0, 359);
    // ========== Added ========== //
    Serial.print("The current degrees: "); // print the degrees
    Serial.print(e);                          // print the degrees
    Serial.print("\n");                       // print the degrees
    // =========================== //
    // Get necessary speed signal
    speed = getAction(e);

    // Send speed signal to motor
    // Rotating clockwise
    if (speed >= 0)
    {
      if (speed < 100)
      { // motor does not react with too low inputs
        speed = 100;
      }
      analogWrite(PWM2, 0);
      analogWrite(PWM1, speed);
    }

    // Rotating counter-clockwise
    else
    {
      if (-speed < 100)
      { // motor does not react with too low inputs
        speed = -100;
      }
      analogWrite(PWM1, 0);
      analogWrite(PWM2, -speed);
    }

    // Calculate new error
    e = degtarget - deg;
  }
}

int getInput()
{

  int ready = 0;
  char buf[3];
  int input = -1;

  Serial.print("Please enter the desired position: \n");

  while (!ready)
  {
    ready = Serial.readBytes(buf, 3);
    input = atoi(&buf[0]);
  }
  return input;
}

int getAction(int error)
{
  // ========== Added ========== //
  u_out = kp * e; // given algorithm from wp6ex1
  // =========================== //
  if (u_out > 254)
  { // u_out cannot be more than 255...
    return 255;
  }
  else if (u_out < -254)
  { // ...or less than -254
    return -255;
  }
  else
    return u_out;
}

void ISR_readEncoder()
{
  // ========== Added ========== //
  digitalRead(ENCA) != LOW ? pos++ : pos--; // we read a since we attach to chanB then we inc or dec depending on low or high
  // =========================== //
}
