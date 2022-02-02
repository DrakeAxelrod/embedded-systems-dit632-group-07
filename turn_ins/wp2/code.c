// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 2
// Exercise 4_1
// Submission code : XXXXXX(provided by your TA - s)

#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

typedef unsigned char byte;

/* function declaration */
void print_byte_as_bits(char val);

/* main function */
int main(int argc, char const *argv[])
{
  if (argc != 6)               // if there are not enough arguments
    return 1;                  // exit the program
  byte value = 0;              // set a byte variable and initialise it to 0
  value += atoi(argv[1]) << 7; // bitshift the first argument and create an integer to represent the 7th binary char
  value += atoi(argv[2]) << 4; // bitshift the second argument and create an integer to represent the 4th-6th binary chars
  value += atoi(argv[3]) << 2; // bitshift the third argument and create an integer to represent the 3rd binary char
  value += atoi(argv[4]) << 1; // bitshift the second argument and create an integer to represent the 2nd binary char
  value += atoi(argv[5]);      // create an integer to represent the 1st binary char

  print_byte_as_bits(value); // print the bit representation
  printf("%x\n", value);     // print the value which will be the hex representation of the input
  return 0;                  // exit program
}

/* function to print bits */
void print_byte_as_bits(char val)
{
  for (int i = 7; 0 <= i; i--) // for each bit in the byte
  {
    printf("%c", (val & (1 << i)) ? '1' : '0'); // print the value
  }
}
