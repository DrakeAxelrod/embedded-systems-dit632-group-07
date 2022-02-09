#include <stdio.h>
#include <Arduino.h>

define handle_keypad_input();
define is_low(int);
define handle_pin(int, char);
define handle_row(char *);

void setup() // setup function - runs once on startup
{
  Serial.begin(9600); // opens the serial port
  pinMode(11,OUTPUT); // sets pin 11 to output mode
  pinMode(10,OUTPUT); // sets pin 10 to output mode
  pinMode(9,OUTPUT); // sets pin 9 to output mode
  pinMode(8,OUTPUT); // sets pin 8 to output mode
  pinMode(7,INPUT); // sets pin 7 to input mode
  pinMode(6,INPUT); // sets pin 6 to input mode
  pinMode(5,INPUT); // sets pin 5 to input mode
  pinMode(4,INPUT); // sets pin 4 to input mode
}

void loop(){ // function that loops until program is ended
  handle_keypad_input(); // calls function
  delay(1000); // delay of 1 second as given in exercise (this delay is too long for good usability of the program)
}

void handle_keypad_input(){ // function that checks key presses and repeats delay of 1 sec
  digitalWrite(11,LOW); // row 1 is set to LOW
  handle_row("A321"); // function call with row 1 characters
  digitalWrite(11,HIGH); // row 1 is set to HIGH 
  digitalWrite(10,LOW); // row 2 is set to LOW
  handle_row("B654"); // function call with row 2 characters
  digitalWrite(10,HIGH); // row 2 is set to HIGH
  digitalWrite(9,LOW); // row 3 is set to LOW
  handle_row("C987"); // function call with row 3 characters
  digitalWrite(9,HIGH); // row 3 is set to HIGH
  digitalWrite(8,LOW); // row 4 is set to LOW
  handle_row("D#0*"); // function call with row 4 characters
  digitalWrite(8,HIGH); // row 4 is set to HIGH
}

int is_low(int pin) // function to check if key is pressed
{
  return (digitalRead(pin) == LOW); // returns 1 if the pin is low (pressed), otherwise it returns 0
}

void handle_pin(int pin, char ch) // function to handle each key
{
  is_low(pin) ? Serial.println(ch) : NULL; // if the is_low function returns 1 (true), character is printed. Otherwise, nothing happens
}

void handle_row(char *keys) // function to check for each key in a row
{
  for (int i = 4; i < 8; i++) // for each key in a row (four)
  {
  	handle_pin(i, keys[i-4]); // function call to check if key is pressed
  }
}