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
int rand_int();
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
  create_random(table);
  count_frequency(table, frequency);
  draw_histogram(frequency);
}

int rand_int() {
  // return a random integer between the min and max value
  return (rand() % (MAXNUMBER + 1));
}

/* method to fill the table with random numbers */
void create_random(int *tab) {
  for (int i = 0; i < MAX; i++) { // loop according to the MAX amount specified in the program
    tab[i] = rand_int(); // set the number to a random value using the rand_int() function
  }
}

/* method to count the frequency of occurrences 
of each number in the table of random numbers */
void count_frequency(int *tab, int *freq) {
  for (int i = 0; i < MAXNUMBER; i++) { // loop over each number in the frequency table to initialise the frequency to zero
    freq[i] = 0; // 
  }
  for (int i = 0; i < MAX; i++) { // loop over each number in the table of random numbers to increment the frequency
    int val = tab[i]; // find the value of the number
    freq[val]++; // increment frequency of the number
  }
}

/* method to create the histogram that will be displayed as 
output in the console showing each number and its occurrence. */
void draw_histogram(int *freq) {
  for (int i = 0; i < MAXNUMBER; i++) { // loop through each number that could occur according to the MAXNUMBER value set in the program
    if (freq[i] != 0) { // check if the number occurs in the table of random numbers, if not, continue to next number
      printf("%d ", i); // print the number
      for (int j = 0; j < freq[i]; j++) { // for each occurrence of the number
        printf("x"); // print the number's occurrence
      }
      printf("\n"); // next line
    }
  }
}
