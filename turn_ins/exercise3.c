// (C) Vernita Gouws, Sicily Brannen, Drake Axelrod, Group: 7 (2022)
// Work package 0
// Exercise 3
// Submission code:
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int rand(void);
void guessing();
/*
 * Main function in the program,
 * @params argc and argv passed
 * @return int (exit code)
 */
int main(int argc, char *argv[]) {
  srand(time(0));    // create a random seed
  char answer = 'y'; // initialize the answer string
  do {          // continue loop until while condition is false
    guessing(); // run the guessing function
    printf("Would you like to play again? y/n\n"); // print to console
    scanf("%s", &answer);                          // get the answer
  } while (answer == 'y'); // continue loop while answer is 'y'
  return 0; // exit program
}
/* function to initiate the guessing game */
void guessing() {
  int count = 0; // initialize the count of the amount of guesses
  int num =
      rand() % 100 + 1; // get a random number from the random number generator
  char input;           // create variable to store user input
  int guess;            // create variable to store the guess
  do {
    printf("%s", "Guess the number.\n"); // print to console
    if (scanf("%d", &guess) == 1 && guess >= 1 &&
        guess <= 100) {   // check whether input is valid
      count++; // increment count of guesses
      if (guess ==
          num) { // check whether user guess is equal to the random number
        printf(
            "%s %d %s", "Well done! You guessed", count,
            "times to get the correct answer.\n"); // print success to console
        break;                                     // end
      } else if (guess < num) { // if guess is lower than the random number
        printf("Your guess is too low.\n"); // print to console
      } else // if guess is higher than the random number
        printf("Your guess is too high.\n"); // print to console
    } else {                                 // if input is not valid
      scanf("%*[^\n]"); // discard that line up to the newline
      printf("Wrong format. Only numbers between 1-100 (inclusive) "
             "accepted.\n"); // print helpful advice to console
      // continue;
    }
  } while (guess != num); // loop until guess is equal to random number
}
