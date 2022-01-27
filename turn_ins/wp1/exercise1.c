// (C) Vernita Gouws, Sicily Brannen, Drake Axelrod, Group: 7 (2022)
// Work package 1
// Exercise 1
// Submission code: UUHT8LX7
#include <stdio.h> // Header for standard input/output
#include <stdlib.h> // Header for general purpose functions (standard library)

// Dr. Seuss quotes. (store the sentence options in an array for easy access)
char *sentence_array[5] = {
    "You know you're in love when you can't fall asleep because reality is "
    "finally better than your dreams.",
    "I like nonsense, it wakes up the brain cells. Fantasy is a necessary "
    "ingredient in living.",
    "Sometimes the questions are complicated and the answers are simple.",
    "Today you are You, that is truer than true. There is no one alive who is "
    "Youer than You.",
    "A person's a person, no matter how small."};

/*
 * Main function in the program,
 * @params none
 * @return int (exit code)
 */
int main(void)
{
  // initiates a while loop
  while (1)
  {
    // variable to store user input, 256 is arbitrarly chosen
    char option[256];
    // prompt the user to choose a number between 1 and 5
    printf("Please type in a number between 1-5: ");
    // read input from console (safer then scanf)
    fgets(option, sizeof(option), stdin);

    // string/char ptr to int (-1 is to account for 0 indexing)
    int choice = atoi(option) - 1;
    // for valid choices to be between 1 and 5
    if (choice >= 0 && choice <= 4)
    {
      // print the relevant sentences inregards to the chosen option
      printf("%s\n", sentence_array[choice]);
    }
    // else: if choices are outside the valid range
    else
    {
      // provide context for why the program could not run
      printf("\nInvalid option you must choose a number between 1-5\n");
      // exit code to terminate
      return 1;
    }
  }
}
