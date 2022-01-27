// (C) Drake Axelrod, Sicily Ann Brannen, Vernita Gouws, group: 07 (2022)
// Work package 1
// Exercise 4_1
// Submission code : XXXXXX
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help();
void convert(int d);
int valid_int(char *str);
int get_byte(int arg);
/*
 * Main function in the program,
 * @params argc and argv passed
 * @return int (exit code)
 */
int main(int argc, char *argv[])
{
  if (argc == 2)
  { // if one argument was provided
    if (strcmp("-h", argv[1]) == 0)
    {           // check if help flag is passed as argument
      help();   // call function to display help to user
      return 0; // exit program
    }
    int result = valid_int(argv[1]); // result calls valid_int() method and 1 is returned if true, 0 if false
    if (result)
    {                            // if number is valid
      int input = atoi(argv[1]); // convert argument to an integer
      convert(input);            // call function to convert the decimal input
    }
    else
    {                                                                           // if not a valid number
      printf("Argument is not a valid decimal number. Enter '-h' for help.\n"); // print error message
    }
  }
  else
  {
    printf("Please provide one arg. Enter '-h' for help.\n"); // print error message
  }
  // successful execution return code
  return 0;
}

/* function to display help to the user when required */
void help()
{
  printf("Program to convert decimal to binary, and binary to hexadecimal. Enter one argument - a positive decimal number.\nExample: dec2bin 250 | bin2hec \n"); // helpful information when user requires it
}

/* function to convert the decimal value to a binary representation */
void convert(int d)
{
  int size = get_byte(d); // set size to the number of bits returned from get_byte()
  int binary[size];       // create an array of integers the size of the required bits
  for (int i = 0; i < size; i++)
  {                                 // loop over each number in the array of bits
    binary[i] = (char)(d >> i) & 1; // we shift the decimal down based on the ith digit of the binary representation and check whether that digit should be a 1 or a 0
  }
  for (int i = size - 1; i >= 0; i--)
  {                          // for each number in the array in reverse order
    printf("%d", binary[i]); // print every element
  }
  printf("\n"); // next line
}

/* function to check whether the input is a valid positive number. Also fails if number is a floating point number */
int valid_int(char *str)
{
  while (*str != '\0')
  {
    if (!isdigit(*str))
    {           // isdigit returns 0 if input is not a number, or 1 if it is a number
      return 0; // return when not a number
    }
    str++; // increment to next character
  }
  return 1; // return when input is a valid number
}

/* function to check the input number in order to find how many bytes are required. */
int get_byte(int arg)
{
  int n = 0; // number of bytes
  while (arg != 0)
  {            // when a number still exists
    arg >>= 8; // bitshift 8 to the right
    n++;       // increment the number of bytes required
  }
  return n * 8; // return the amount of bits
}
