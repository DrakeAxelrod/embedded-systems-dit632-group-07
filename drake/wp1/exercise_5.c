// (C) Drake Axelrod, Sicily Ann Brannen, Vernita Gouws, group: 07 (2022)
// Work package 1
// Exercise 5
// Submission code : XXXXXX
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100      // defines the maximum number of the values in the table
#define MAXNUMBER 20 // defines the maximum value of random numbers

// function declarations
void create_random(int *tab);
void count_frequency(int *tab, int *freq);
void draw_histogram(int *freq);
int rand_int();
/**
 * main function of program. entry point for the program which calls the other
 * functions.
 * @return int which is the exit code
 */
int main(void) {
  // random seed init
  srand(time(0));
  // initialize a table to fill with random numbers
  int table[MAX];
  // initialize a frequency array to count the occurances within table
  int frequency[MAXNUMBER];
  create_random(table);
  // counts the frequency of occurances of each number in table
  count_frequency(table, frequency);
  // draw a histogram to represent the frequency of the numbers within table
  draw_histogram(frequency);
  // exit code
  return 0;
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
    freq[i] = 0;
  }
  for (int i = 0; i < MAX; i++) { // loop over each number in the table of random numbers to increment the frequency
    int val = tab[i]; // find the value of the number
    freq[val]++; // increment frequency of the number
  }
}

/* method to create the histogram that will be displayed as 
output in the console showing each number and its occurrence. */
void draw_histogram(int *freq) {
  for (int i = 0; i < MAXNUMBER; i++) { 
    if (freq[i] != 0) { // check if the number occurs in the table of random numbers, if not, continue to next number
      printf("%d ", i); // print the number
      for (int j = 0; j < freq[i]; j++) { // for each occurrence of the number
        printf("x"); // print the number's occurrence
      }
      printf("\n"); // next line
    }
  }
}
