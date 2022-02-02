// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 2
// Exercise 4_2
// Submission code : XXXXXX(provided by your TA - s)

#include <stdlib.h> // strtol
#include <stdio.h>  // printf

// byte type declaration unsigned char = 8 bits
typedef unsigned char byte;

// function declaration
void show_results(byte val);

// Main function
int main(int argc, char *argv[])
{
    if (argc != 2)                               // the program should only accept 1 user provided argument otherwise exist the program with an error code
        return 1;                                // error exit code
    byte value = (int)strtol(argv[1], NULL, 16); // convert hex to decimal (in the form of a unsigned char byte)
    show_results(value);                         // display the result
}
// function to display the arguments that were provided to code
void show_results(byte val)
{
    char bits[8];                // array to hold the bits of the dec value
    for (int i = 7; 0 <= i; i--) // decrement so the order is correct
    {
        // shift based on the position in the byte, ternary for 1 or 0
        // cast to char so the ternary works
        bits[i] = (char)(val & (1 << i)) ? '1' : '0';
    }

    int gear_pos = 0;           // init gear_pos
    int key_pos = 0;            // init key_pos
    int bin_rep_gear = 1;       // init bin_rep_gear
    int bin_rep_key = 1;        // init bin_rep_key
    for (int i = 3; i > 0; i--) // check the 0 _ _ _ 0000 positions in the byte
    {
        if (bits[i] == '1')           // check if this index is 1
            gear_pos += bin_rep_gear; // if it is increment by bin_rep_gear
        bin_rep_gear *= 2;            // increment the binary value to represent the current value
    }
    for (int i = 6; i > 4; i--) // check the 0000 _ _ 00 positions in the byte
    {
        if (bits[i] == '1')         // check if this index is 1
            key_pos += bin_rep_key; // if it is increment by bin_rep_key
        bin_rep_key *= 2;           // increment the binary value to represent the current value
    }
    printf("Name\t\tValue\n");          // Print the headings for the output
    printf("engine_on\t%c\n", bits[0]); // print the engine's current state
    printf("gear_pos\t%d\n", gear_pos); // print the gear's current state
    printf("key_pos\t\t%d\n", key_pos); // print the key's current state
    printf("brake1\t\t%c\n", bits[6]);  // print the 1st brake's current state
    printf("brake2\t\t%c\n", bits[7]);  // print the 2nd brake's current state
}
