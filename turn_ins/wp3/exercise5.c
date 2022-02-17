#include <Arduino.h> // header file for Arduino functions
#include <Keypad.h> //header file for keypad functions

const int rowNo = 4; //four rows
const int columnNo = 4; //four columns

char keys[rowNo][columnNo]; = { // list of all the keys with their positions and associated characters
        {'1','2','3', 'A'},
        {'4','5','6', 'B'},
        {'7','8','9', 'C'},
        {'*','0','#', 'D'}
};

byte rows[rownNo] = {9, 8, 7, 6}; // connect to the row keys of the keypad
byte columns[columnNo] = {5, 4, 3, 2}; // connect to the column keys of the keypad

Keypad keymap = Keypad(makeKeymap(keys), rows, columns, rowNo, columnNo); // function to instantiate the keypad

void setup() { //startup function
    Serial.begin(9600); // opens the serial port @ 9600 bits per second
}
void loop() // function that will iterate until the program is ended
{
    char pressed = keymap.getKey(); // sets character to a character from the keymap
    if (pressed) // if the character is pressed
    {
        Serial.println(pressed); //print the pressed character
    }
}

