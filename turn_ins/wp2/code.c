// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 2
// Exercise 4_1
// Submission code : M60HVAJ7

#include <stdlib.h> // for using atoi
#include <stdio.h>  // to print

typedef unsigned char byte;

/* function declaration */
void print_byte_as_bits(char val);
int check_input(char *, int);

/* main function */
int main(int argc, char const *argv[])
{
  if (argc != 6) // if there are too few arguments
  {
    printf("Not enough arguments passed. You should pass 5 arguments with a space between each one. For example: '1 1 1 1 1'.\n"); // error message
    return 1;                                                                                                                      // return                                                                                                               // exit the program
  }
  for (int i = 1; i < 6; i++) // for each argument input
  {
    if (!check_input(argv[i], i)) // calls function to check the user input
    {
      printf("There was an error with your arguments. The minimum value for each argument is 0, and the maximum value is: 1, 4, 3, 1, 1, respectively."); // error message
      exit(0);                                                                                                                                            // exit code
    }
  }
  
  byte value = 0;              // set a byte variable and initialise it to 0
  value += atoi(argv[1]) << 7; // bitshift the first argument and create an integer to represent the 7th binary char
  value += atoi(argv[2]) << 4; // bitshift the second argument and create an integer to represent the 4th-6th binary chars
  value += atoi(argv[3]) << 2; // bitshift the third argument and create an integer to represent the 3rd binary char
  value += atoi(argv[4]) << 1; // bitshift the second argument and create an integer to represent the 2nd binary char
  value += atoi(argv[5]);      // create an integer to represent the 1st binary char
  printf("Hex: %x\n", value);  // print the value which will be the hex representation of the input
  return 0;                    // exit program
}

/*function to check if input is valid*/
int check_input(char *input, int current)
{
  int value = atoi(input);           // first get the int value of the input
  if (value == 0 && input[0] != '0') // if the input is the char 0 it is valid otherwise if atoi returns a 0 it wasnt a valid input
  {
    return 0; // return not valid
  }

  if (current == 1 || current == 4 || current == 5) // if it's the 1st, 4th, or 5th argument
  {
    if (value == 1 || value == 0) // value must be 0 or 1
    {
      return 1; // return success
    }
  }
  else if (current == 2) // if it's the 2nd argument
  {
    if (value >= 0 && value <= 4) // if the value is between 0 and 7
    {
      return 1; // return success
    }
  }
  else if (value >= 0 && value <= 3) // if it's the 3rd argument and the value is between 0 and 3
  {
    return 1; // return success
  }
  return 0; // exit code
}
