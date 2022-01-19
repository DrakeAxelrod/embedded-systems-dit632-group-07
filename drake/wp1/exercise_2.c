// (C) Drake Axelrod, group: 07 (2022)
// Work package 1
// Exercise 2
// Submission code : XXXXXX(provided by your TA - s)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// function declarations
char rotate(char ch, int rotations);

char *rotate_word(char *word, int rotations);
/*
 * Main function in the program,
 * @params none
 * @return int (exit code)
 */
int main(int argc, char *argv[]) {
  // char *word = rotate_word(argv[1], atoi(argv[2]));
  // printf("%s", word);
  char *alphabet = "abcdefghijklmnopqrstuvwxyz";
  for (int i = 0; i < strlen(alphabet); i++) {
    printf("%s", rotate(alphabet[i], 1));
  }
  return 0;
  // char option[265];
  // int n = rand_int(1, 100);
  // prompt the user to choose a number between 1 and 5
  // printf("Please type in a number between 1-5: ");
  // read input from console (safer then scanf)
  // fgets(option, sizeof(option), stdin);
  // int guess = atoi(option);
  // string/char ptr to int (-1 is to account for 0 indexing)
  // int choice = atoi(option) - 1;
  // printf("%d", n);
  // successful execution return code
  // return 0;
}

// use type casting to rotate character
// based on a provided number of rotations
char rotate(char ch, int rotations) {
  // cast char to a int and add the number of rotations
  // then cast back to char
  int code = (int)ch;
  int boundary_code = (int)"z";
  if (code >= boundary_code) {
  }
  char c = (char)(code + rotations);
  return c;
}

char *rotate_word(char *word, int rotations) {
  // loop through the string
  int len = strlen(word);
  char *new_word;
  for (int i = 0; i < len; i++) {
    word[i] = rotate(word[i], rotations);
  }
  return word;
}
