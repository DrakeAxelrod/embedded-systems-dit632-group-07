// (C) Drake Axelrod, group: 07 (2022)
// Work package 1
// Exercise 3
// Submission code : XXXXXX(provided by your TA - s)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand_int(int min, int max);
/*
 * Main function in the program,
 * @params none
 * @return int (exit code)
 */
int main(void) {
  // start the random seed so that we actually generate a random int
  srand(time(0));
  // int to count the rounds
  int count = 0;
  // max number of guesses per round
  const int MAX_NUMBER = 10;
  // holder for user input 256 is an arbitrarly chosen value
  char input[256];
  // basically a bool to run the while loop
  int correct = 1;
  // the number to guess
  int n = rand_int(1, 100);
  // prompt the user to choose a number between 1 and 5
  while (correct != 0) {
    // prompt the user to type a number
    printf("Please guess a number between 1-100: ");
    // read input from console (safer then scanf)
    fgets(input, sizeof(input), stdin);
    // convert the input to a int
    int g = atoi(input);
    // make sure the input is between 1-100
    if (g <= 100 && g >= 1) {
      // handle the input if it is valid
      // check is guess is greater than random number
      if (g > n) {
        // let the user know the number is less
        printf("the number is less than %d\n", g);
        // check is guess is less than random numer
      } else if (g < n) {
        // let the user know the number is greater
        printf("the number is greater than %d\n", g);
        // if it is not greater or less than the number and it is between 1-100
        // then it is the number
      } else {
        // let the user know that they guessed correct
        printf("You have guessed %d times and your guess is correct\n", count);
        printf("would you like to play another round? Y/N: ");
        char ans;
        scanf("%c", &ans);
        if (0) {
          // reset values and start again
        } else {
          // exit
          correct = 0;
        }
      }
      // if the input is not a int or between 1-100 let the user know the rules.
    } else {
      // Inform the user of the rules
      printf("Invalid input, must be an integer between 1-100\n");
    }
    count++;
  }
  // successful execution return code
  return 0;
}

int rand_int(int min, int max) {
  // return a random integer between the min and max value
  return (rand() % (max - min + 1)) + min;
}
