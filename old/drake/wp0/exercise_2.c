// (C) Drake Axelrod, group: 07 (2022)
// Work package 0
// Exercise 1
// Submission code : 39CQFR
#include <stdio.h>
/**
 *  Main function in the program, one argument supported
 *  No error handling for either no or more then one args
 *  @params int argc. (the number of args)
 *  @params char *argv[].  (array of pointers to the provided args)
 *  @return int. (exit code)
 */
int main(int argc, char *argv[]) {

  // Print a string to the console
  printf("%s - I'm %s!", "Hello World\n",
         argv[1]); // says hello to the 2nd argument provided (first arg is the
                   // filename)
  return 0;
}
