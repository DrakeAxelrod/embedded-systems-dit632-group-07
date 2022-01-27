// (C) Vernita Gouws, Sicily Brannen, Drake Axelrod, Group: 7 (2022)
// Work package 0
// Exercise 2
// Submission code: 
#include <stdio.h>
#include <stdlib.h>         // for atoi
void encrypt(int, char **); // define the function to encrypt

void main(int argc, char *argv[]) // main function
{
    while (1)
    {                        // loop continues until user ends the program via the command line
        encrypt(argc, argv); // function to encrypt is executed
    }
}

void encrypt(int argc, char *argv[]) // function to encrypt
{
    int i = 0;                                // initialising i to use in while loop
    char str[100];                            // initialisation of string that user wants to encrypt
    printf("Enter the string to encrypt.\n"); // print to console to ask for user input
    scanf("%s", str);                         // save user input string to char array

    char *a = argv[1];                        // create pointer to command line argument for encryption amount
    int amount = atoi(a);                     // get the integer from the character pointer
    if (amount == *a){
        printf("heyy well done");
    }

    while (str[i] != '\0') // while loop continues until end of the user's input string
    {
        if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) // checks if character is valid alphabet letters
        {
            if (str[i] < 'a' && str[i] > 'Z' - amount || str[i] <= 'z' && str[i] > 'z' - amount) // checks if character's will fall outside of alphabet ASCII numbers after encryption
            {
                str[i] -= 26 - amount; // equation to ensure encryption stays in the lowercase of uppercase alphabet range respectively
            }
            else
            {
                str[i] += amount; // equation for simple encryption using user's argument
            }
        }
        i++; // increment i to check next character in while loop
    }
    printf("\nThe encrypted str is: %s\n\n", str); // print string after encryption
}