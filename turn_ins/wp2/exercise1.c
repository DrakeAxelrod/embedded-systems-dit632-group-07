// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 2
// Exercise 1
// Submission code : XXXXXX(provided by your TA - s)

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

enum DIRECTION { N, E, S, W };

typedef struct {
  int xpos;
  int ypos;
  enum DIRECTION dir;
} ROBOT;

void move(int *);
void turn(int *);

int is_valid_input(char *);
int input_loop(char *);
/*
 * Main function in the program,
 * @params none
 * @return int (exit code)
 */
int main(void) {
  ROBOT robot;
  char coords[8];
  char movement[256];
  // printf("%d", robot.xpos);
  printf("\nWhat is the starting x coordinate: ");
  fgets(coords, 8, stdin);
  if (is_valid_input(coords)) {
    printf("im in ");
    robot.xpos = atoi(coords);
  }
  printf("\nWhat is the starting y coordinate: ");
  fgets(coords, 8, stdin);
  if (is_valid_input(coords)) {
    robot.ypos = atoi(coords);
  }
  printf("x: %d, y: %d\n", robot.xpos, robot.ypos);
  printf("\nWhat is the movement of the robot?\n");
  fgets(movement, 256, stdin);
  return 0;
}

void move(int *robot) {}

void turn(int *robot) {}

int is_valid_input(char *input) {
  while (*input != '\n') {
    if (!isdigit(*input)) { // isdigit returns 0 if input is not a number, or 1
                            // if it is a number
      fflush(stdin);
      return 0; // return when not a number
    }
    input++; // increment to next character
  }
  fflush(stdin);
  return 1; // return when input is a valid number
}

int input_loop(char *input) { return 0; }
