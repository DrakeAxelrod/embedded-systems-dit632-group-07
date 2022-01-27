// (C) Drake Axelrod, Sicily Ann Brannen, Vernita Gouws, group: 07 (2022)
// Work package 1
// Exercise 4_2
// Submission code : XXXXXX
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void convert(char *in);
int valid_int(char *str);
/*
 * Main function in the program,
 * @params argc and argv are passed
 * @return int (exit code)
 */
int main(int argc, char *argv[]) {
  char buffer[256], *input;
  if (argc == 1){
  input = fgets(buffer, 256, stdin);
  } else {
    input = argv[1];
  }
  convert(input);
  return 0; // successful execution return code
}

void help() { printf("helpful info\n"); }

void convert(char *in) { // method to convert integer to hex string
  int value = (int)strtol(in, NULL, 2);
  char hex[12]; // create character array for hex representation
  sprintf(hex, "%x\n", value); // 
  printf(hex); // output hex string
}

int valid_int(char *str) {
  while (*str != '\0') { // while string has not ended
    if (!isdigit(*str)) {  // isdigit returns 0 if input is not a number, or 1 if it is a number
      return 0;
    }
    str++;
  }
  return 1;
}
