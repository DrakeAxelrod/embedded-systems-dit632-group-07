// (C) Vernita Gouws, Sicily Brannen, Drake Axelrod, Group: 7 (2022)
// Work package 1
// Exercise 2
// Submission code: UUHT8LX7
#include <stdio.h> // for standard input/output functions
#include <stdlib.h> // for atoi
void encrypt(int, char **, char* str); // define the function to encrypt

int main(int argc, char *argv[]) // main function
{
  // exit if no argument or too many args were provided
  if (argc !=2) { // check if we dont have 2 args
    printf("Must provide one argument, which is the amount of shifts for the characters"); // error message
    return 1; // exit code (error)
  }
  // arbitrary size array to hold input
  char str[256]; // variable to store user input, 256 is arbitrarly chosen
  printf("Enter the string to encrypt.\n"); // print to console to ask for user input
  while (scanf("%s", str) != EOF) // loop continues until user ends the program via the command line
  {
    encrypt(argc, argv, str); // function to encrypt is executed
    printf("Enter the string to encrypt.\n"); // print to console to ask for user input
  }
}

void encrypt(int argc, char *argv[], char *str) // function to encrypt
{
    int i = 0; // initialising i to use in while loop
    char *a = argv[1]; // create pointer to command line argument for encryption amount
    int amount = atoi(a); // get the integer from the character pointer

    //while (scanf("%s", input) != EOF)
      while (str[i] != '\0') // while loop continues until end of the user's input string
      {
        if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) // checks if character is valid alphabet letters
        {
            if (str[i] < 'a' && str[i] > 'Z' - amount || str[i] <= 'z' && str[i] > 'z' - amount) // checks if character's will fall outside of alphabet ASCII numbers after encryption
            {
                str[i] -= 26 - amount; // equation to ensure encryption stays in the lowercase of uppercase alphabet range respectively
            }
            else // else condition
            {
                str[i] += amount; // equation for simple encryption using user's argument
            }
        }
        i++; // increment i to check next character in while loop
    }
    printf("\nThe encrypted str is: %s\n", str); // print string after encryption
}
