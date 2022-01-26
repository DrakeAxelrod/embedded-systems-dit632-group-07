// (C) Drake Axelrod, Sicily Ann Brannen, Vernita Gouws, group: 07 (2022)
// Work package 1
// Exercise 5
// Submission code : XXXXXX
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;

void help();
void convert(int d);
int valid_int(char *str);
int get_byte(int arg);
/*
 * Main function in the program,
 * @params none
 * @return int (exit code)
 */
int main(int argc, char *argv[]) {
  int result = valid_int(argv[1]);
  // check if number is float also
  if (argc > 1 && argc < 3) {
    if (result) {
      int input = atoi(argv[1]);
      convert(input);
    } else {
      printf("failed at result if check\n");
    }
    // if (input == *argv[1]) {
    // } else {
    //   printf("failed on equality");
    // }
  } else {
    printf("must provide one arg\n");
  }
  // successful execution return code
  return 0;
}

void help() { printf("helpful info\n"); }

void convert(int d) {
  int size = get_byte(d);
  int binary[size];
  for (int i = 0; i < size; i++) {
    binary[i] = (char)(d >> i) & 1;
  }
  for (int i = size - 1; i >= 0; i--) {
    printf("%d", binary[i]);
  }
  printf("\n");
}

int valid_int(char *str) {
  while (*str != '\0') {
    // isdigit return 0 or 1 depending on if char is an int which you check with
    // 0 if 0 true else 1 false
    if (!isdigit(*str)) {
      return 0;
    }
    str++;
  }
  return 1;
}

int get_byte(int arg) {
  int n = 0;
  while (arg != 0) {
    arg >>= 8;
    n++;
  }
  return n * 8;
}
// 2^32-1
// 9,223,372,036,854,775,807 - 64bitsystem
