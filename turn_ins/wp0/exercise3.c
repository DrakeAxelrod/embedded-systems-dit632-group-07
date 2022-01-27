// (C) Vernita Gouws, Sicily Brannen, Drake Axelrod, Group: 7 (2022) 
// Work package 0 
// Exercise 3
// Submission code: 39CQFR
#include <stdio.h> 
#include <string.h> // This header file allows for us to use 'strcmp' to compare strings in line 11

// Main function in the program, with the argument count and argument values as parameters
void main (int argc, char *argv[]) { 
 
    if (argc == 2) // If the user included one argument the count will be 2. This is the correct use case.
    {
        if (strcmp("-h", argv[1]) == 0) //compares the string to see if user is asking for help (signified by "-h")
        {
            printf("Run the program with your name as an argument, for example: '/exc3 Jerry'. This will display an output message of `Hello World. I'm <name>.'\n"); // Print help message
        } else  
        printf("%s %s %s%s", "Hello World!", "I'm", argv[1], ".\n");  // Output string for the correct use case, with user's input displayed
    }
    if (argc >= 3) // If user included two or more arguments
    {
        printf("Error: You should only pass one argument. Enter -h for help.\n"); // Error message
    }
    if (argc == 1) // If no argument is passed
    {
        printf("Error: Pass one argument. Enter -h for help.\n"); // Error message
    }
}