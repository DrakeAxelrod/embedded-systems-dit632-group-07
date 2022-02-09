#include <Arduino.h> // header file for Arduino functions
#include <Keypad.h> //header file for keypad functions

const int rn = 4; //four rows
const int cn = 4; //four columns

char keys[rn][cn] = { // list of all the keys with their positions and associated characters
        {'1','2','3', 'A'},
        {'4','5','6', 'B'},
        {'7','8','9', 'C'},
        {'*','0','#', 'D'}
};

byte rows[rn] = {9, 8, 7, 6}; // connect to the row keys of the keypad
byte columns[cn] = {5, 4, 3, 2}; // connect to the column keys of the keypad

Keypad keymap = Keypad(makeKeymap(keys), rows, columns, rn, cn); // function to instantiate the keypad

void setup() { //startup function
    Serial.begin(9600); // opens the serial port @ 9600 bits per second
}
void loop() // function for instantiating the program and loop
{
    char pressed = keymap.getKey(); // sets character to a character from the keymap
    if (pressed) // if the character is pressed
    {
        Serial.println(pressed); //print the pressed character
    }
}

