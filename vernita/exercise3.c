// (C) __Your names here, group: 7 __ (2022) 
// Work package 0 
// Exercise 1 
// Submission code: XXXXXX (provided by your TA-s) 
#include <stdio.h> 
#include <string.h> // This library allows for us to use 'strcmp' to compare strings in line 11

  // Main function in the program, no program arguments supported 
void main (int argc, char *argv[]) { 
 
    if (strcmp("-h",argv[1]) ==0) //compares the string to see if user is asking for help
    {
        printf("Run the program with your name as an argument. This will display an output message of `Hello World. I'm <name>.'\n"); // Help message
    }
    else // If the user is not asking for help.
    {   if (argc == 2) // If the user included one argument. This is the correct use case.
        {
            // Print a string to the console 
            printf("%s %s %s%s", "Hello World!", "I'm", argv[1], ".\n");  // Output line for the correct use case
        }
        
        if (argc == 3) // If user included two arguments
        {
            printf("Error: Only pass one argument\n"); // Error message
        }
        if (argc == 1) // If no argument is passed
        {
            printf("Error: Pass an argument\n"); // Error message
        }
    }
} 