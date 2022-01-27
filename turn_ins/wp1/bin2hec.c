// (C) Drake Axelrod, Sicily Ann Brannen, Vernita Gouws, group: 07 (2022)
// Work package 1
// Exercise 4_2
// Submission code : UUHT8LX7
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// function declarations
void convert(char *in); // convert binary to hexidecimal
int valid_bin(char *str); // check if input is a valid binary
/*
 * Main function in the program,
 * @params argc and argv are passed
 * @return int (exit code)
 */
int main(int argc, char *argv[])
{
  char buffer[40], *input; // create buffer array to support input for piping. create input pointer for use in convert() function
  if (argc == 1)           // if there is no argument
  {
    input = fgets(buffer, 40, stdin); // get input from stdin (command line)
  }
  else
  {                  // if there is an argument
    input = argv[1]; // get input from argument
  }
  if (valid_bin(input))
  {                 // if to check if input is valid binary
    convert(input); // if valid call convert function
  }
  else
  {                                     // if not valid binary input
    printf("Invalid binary number.\n"); // error message
    return 1;                           // exit program
  }                                     // call function to convert binary to hexadecimal
  return 0;                             // successful execution return code
}

// method to convert binary number to hex string
void convert(char *in)
{
  int value = (int)strtol(in, NULL, 2); // convert input from a string to an integer to a base 2 to represent binary
  char hex[12];                         // create character array for hex representation
  sprintf(hex, "%x\n", value);          // writes values to the hex array
  printf(hex);                          // output hex string to console
}

/* function to check if input is a valid binary representation */
int valid_bin(char *str)
{
  while (*str != '\n' && *str != '\0')
  { // while string hasn't ended (taking fgets into account, as well as arguments)
    if (*str != '0' && *str != '1')
    {           // checks if the character is not 1 and not 0
      return 0; // returns 0 if input is not a 1 or 0
    }
    str++; // increments to next character in string
  }
  return 1; // returns when input is a valid number
}
