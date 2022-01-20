// (C) Drake Axelrod, group: 07 (2022)
// Work package 1
// Exercise 2
// Submission code : XXXXXX(provided by your TA - s)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// function declarations
// function to rotate one character
char rotchar(char ch, int shifts);
// function to rotate a word (uses rotate)
char *rotword(char *word, int shifts);

/*
 * Main function in the program,
 * @params none
 * @return int (exit code)
 */
int main(int argc, char *argv[])
{
  if (argc > 1 && argc < 3)
  {
    // convert the arg to an int so we know how many characters to shift by
    char first_ch = *argv[1];
    int isNum = isdigit(first_ch) == 2048;
    if (isNum)
    {
      int shifts = atoi(argv[1]);
      // prompt user and provice context for the program
      printf("Type something to have it rotated to exit press ctrl+d (linux) or ctrl+z (Windows)\n");
      // create an array to hold the input (256 is arbitrarly chosen)
      char stdin[256];
      //
      while (scanf("%15s", stdin) == 1)
      {
        char *word = rotword(stdin, shifts);
        printf("%s\n", word);
        free(word);
      }
      return 0;
    }
    else
    {
      printf("argument is not a valid number (only number)\n");
      return 1;
    }
  }
  else
  {
    printf("no argument provided\n");
    return 1;
  }
}

// use type casting to rotate character
// based on a provided number of rotations
// a = 97, z = 122 | A = 65 -> Z = 90 #ref https://www.ascii-code.com/
char rotchar(char ch, int shift)
{
  // cast char to a int and add the number of rotations
  // then cast back to char
  int code = (int)ch;
  int boundary = (int)'z';
  for (int i = 0; i < shift; i++)
  {
    // if the char code is 90 (Z) we need to circle back to 65 (A)
    if (code == 90)
    {
      // set char to 65 (a)
      code = 65;
      // if the char code is 122 (z) we need to circle back to 97 (a)
    }
    else if (code == 122)
    {
      // set char to 97 (A)
      code = 97;
    }
    // don't rotate numbers
    else if (code <= 57 && code >= 48)
    {
      code = code;
    }
    else
    {
      // if we havent hit and end char code for either capital or lowercase
      // we increment to the next char code
      code = code + 1;
    }
  }
  // return the updated char code as a character by casting it back to a char
  return (char)code;
}

// char *rotate_word(char *word, int shift) {
char *rotword(char *word, int shift)
{
  // get the length of the word to rotate
  int len = strlen(word);
  // create a pointer for the new rotated word
  char new_word[len];
  // we set i here so we can use it to place the end character
  int i = 0;
  // loop through the string character by character
  while (i <= len)
  {
    // replace the char at ith index with the rotated version
    new_word[i] = rotchar(word[i], shift);
    i++;
  }
  // add a termination character
  new_word[i] = '\0';
  // create a copy of and return a pointer to the copy (since we know the length we can use strndup instead of strdup)
  return strndup(new_word, len);
}
