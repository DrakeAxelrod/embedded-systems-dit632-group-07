// (C) Drake Axelrod, group: 07 (2022)
// Work package
// Exercise
// Submission code : XXXXXX(provided by your TA - s)
#include <stdio.h>
#include <string.h>

// function declaration
void help();
/*
 * Main function in the program,
 * @params argc (the amount of arguments provided to the program)
 * @params *argv[] (a pointer to the arguments provided to the program)
 * @return int (exit code)
 */
int main(int argc, char *argv[]) {
  // argv[0] is the filename so no arg was provided if argc less than 2
  // if argc is greater than 1 arguments were provided
  // the program only accepts 1 argument
  if (argc == 2) {
    // checks if the argument provided is -h or --help
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
      help();
      return 0; // exit code
    } else {
      // one argument has been provided and it is not the either of the help
      // flags
      printf("Hello World! - I'm %s", argv[1]);
      return 0; // exit code
    }
  } else {
    // let the user know that the failed to provide and argument
    fprintf(stderr, "No arguments where provided");
    help();
    return 1; // exit code
  }
}

// help message for incorrect input or if the flag -h or --help is passed
void help() {
  printf("Program that takes one argument and prints out 'Hello World! - I'm "
         "<argument>'");
  printf("\nFlags:");
  printf("\n     -h, --help         display this help message.");
  printf("\nExample:");
  printf("\n     exercise_3 <argument>");
}
