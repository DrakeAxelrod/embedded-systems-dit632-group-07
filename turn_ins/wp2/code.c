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
int check_input(char *input, int value)

/* main function */
int main(int argc, char const *argv[])
{
  if (argc != 6) // if there are too few arguments
  {
    printf("Not enough arguments passed. You should pass 5 arguments with a space between each one. For example: '1 1 1 1 1'.\n"); // error message
    return 1;                                                                                                                      // exit the program
  }
  for (int i = 1; i < 6; i++)
  {
    if (!check_input(argv[i], i))
    {
      printf("There was an error with your arguments. The minimum value for each argument is 0, and the maximum value is: 1, 7, 3, 1, 1, respectively."); // error mes
      exit(0);
    }
  }

  byte value = 0;              // set a byte variable and initialise it to 0
  value += atoi(argv[1]) << 7; // bitshift the first argument and create an integer to represent the 7th binary char
  value += atoi(argv[2]) << 4; // bitshift the second argument and create an integer to represent the 4th-6th binary chars
  value += atoi(argv[3]) << 2; // bitshift the third argument and create an integer to represent the 3rd binary char
  value += atoi(argv[4]) << 1; // bitshift the second argument and create an integer to represent the 2nd binary char
  value += atoi(argv[5]);      // create an integer to represent the 1st binary char
  printf("%x\n", value);       // print the value which will be the hex representation of the input
  return 0;                    // exit program
}

/*function to check if input is valid*/
int check_input(char *input, int value)
{
  if (current == 1 || current == 4 || current == 5)
  {
    if (input == '1' || input == '0')
    {
      return 1;
    }
  }
  else if (current == 2)
  {
    if (input >= '0' && input <= '7')
    {
      return 1;
    }
  }
  else if (input >= '0' && input <= '3')
  {
    return 1;
  }
  return 0;
}
