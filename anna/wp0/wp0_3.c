// (C) Drake Axelrod, Sicily Brannen, Vernita Gouws, group: 7 (2022)
// Work package 0
// Exercise 3
// Submission code: XXXXXX (provided by your TA-s)

//Inclusion of header files for standard input/output & string functions
#include <stdio.h>
#include <string.h>

// Parameters: # of args, array for the args
void main (int argc, char *argv[]) {
    // Checks if # of args is exactly 2 (1 is filename, 2nd is passed by user)
    if (argc == 2) {
        // If argument supplied by user is the -h flag, prints the below string to the console
        if (strcmp(argv[1], "-h") == 0) {
            printf("Usage: wp0_3 [NAME]\nPrint the Hello World message with NAME string argument.\nExample:\n\n./wp0_3 tom\nHello World! - I'm tom!\n");
        } else {
            // Prints a string to the console with the supplied arg
            printf("Hello World! - I'm %s! ", argv[1]);
        }
    } else {
        // Prints to the console that the arguments supplied were invalid & further instruction given
        printf("Invalid arguments.\nTry 'wp0_3 -h' for more information.\n");
    }
}