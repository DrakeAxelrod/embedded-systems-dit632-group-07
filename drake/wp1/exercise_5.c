#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100      // Defines the maximum number of the values in the table
#define MAXNUMBER 20 // Defines the maximum value of random numbers
// ------ Function declarations ----------
// This function generates a set of random numbers
// and fills the table *tab with these numbers
void create_random(int *tab);
// This function takes the *tab of random numbers
// and creates a table with the frequency counts for these numbers
void count_frequency(int *tab, int *freq);
// This function takes the frequency count table
// and draws a histogram of the values in that frequency table
void draw_histogram(int *freq);
// ------ Function definitions ----------
int rand_int(int max);
// ------ Main --------------------------
// The main entry point for the program
//
// If you choose to go for the optional part
// Please modify it accordingly
int main(void) {
  // random seed init
  srand(time(0));
  int table[MAX], n;
  int frequency[MAXNUMBER];
}

int rand_int(int max) {
  // return a random integer between the min and max value
  return (rand() % (max - 0 + 1)) + 0;
}
