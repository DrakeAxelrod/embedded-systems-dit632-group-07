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
  char option[265];
  int n = rand_int(1, 100);
  // prompt the user to choose a number between 1 and 5
  printf("Please type in a number between 1-5: ");
  // read input from console (safer then scanf)
  fgets(option, sizeof(option), stdin);
  int guess = atoi(option);
  // string/char ptr to int (-1 is to account for 0 indexing)
  int choice = atoi(option) - 1;
  printf("%d", n);
  // successful execution return code
  return 0;
}

int rand_int(int min, int max) {
  srand(time(0));
  int r = (rand() % (max - min + 1)) + min;
  return r;
}
