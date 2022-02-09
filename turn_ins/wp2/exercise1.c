// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 2
// Exercise 1
// Submission code : M60HVAJ7

#include <ctype.h>  // for use in isDigit() method
#include <stdio.h>  // for input/output handling
#include <string.h> // for use of strlen() method
#include <stdlib.h> // for use with atoi() method

enum DIRECTION // ENUM constants for cardinal directions
{
  N,
  E,
  S,
  W
};

typedef struct // structure for ROBOT for use in the program
{
  int xpos;           // definition of the x-position of the robot
  int ypos;           // definition of the y-position of the robot
  enum DIRECTION dir; // the direction - N/W/S/E - of the robot
} ROBOT;

void move(ROBOT *); // declaration of a method
void turn(ROBOT *); // declaration of a method

int is_valid_input(char *);     // declaration of a method
void input_loop(ROBOT *);       // declaration of a method
void movement(ROBOT *, char *); // declaration of a method
/*
 * Main function in the program,
 * @params none
 * @return int (exit code)
 */
int main(void)
{
  int x;
  ROBOT robot;   // initialise a struct of type ROBOT
  char str[256]; // variable to store user input, 256 is arbitrarly chosen
  while (1)      // loop based on exit character not being input
  {
    input_loop(&robot);                                            // function call with the robot struct passed as a parameter
    printf("\nPress 'Enter' to move the robot, or 'q' to exit\n"); // prints user prompt for input to console
    int x = getchar();                                             // to read a single char from user input
    if (x == 'Q' || x == 'q')                                      // if the user's input is Q or q
    {
      break; // end loop
    }
  }
  return 0; // return exit code
}

/* function to adapt robot's position (coordinates) based on the input from the user*/
void move(ROBOT *robot)
{
  if (robot->dir == 'N') // if robot's direction is N
  {
    robot->ypos++; // increments robot's position on y axis
  }
  else if (robot->dir == 'E') // if robot's direction is E
  {
    robot->xpos++; // increments robot's position on x axis
  }
  else if (robot->dir == 'S') // if robot's direction is S
  {
    robot->ypos--; // decrements robot's position on y axis
  }
  else if (robot->dir == 'W') // if robot's direction is W
  {
    robot->xpos--; // decrements robot's position on x axis
  }
}

/* function to adapt robot's direction based on the input from the user */
void turn(ROBOT *robot)
{
  if (robot->dir == 'N') // if robot's direction is N
  {
    robot->dir = 'E'; // turns robot clockwise to E
  }
  else if (robot->dir == 'E') // if robot's direction is E
  {
    robot->dir = 'S'; // turns robot clockwise to S
  }
  else if (robot->dir == 'S') // if robot's direction is S
  {
    robot->dir = 'W'; // turns robot clockwise to W
  }
  else if (robot->dir == 'W') // if robot's direction is W
  {
    robot->dir = 'N'; // turns robot clockwise to N
  }
}

/* checks whether the coordinates of the user's input are as expected for the program to run successfully */
int is_valid_input(char *input)
{
  while (*input != '\n') // while input is not a newline character
  {
    if (!isdigit(*input))
    { // isdigit returns 0 if input is not a number, or 1
      // if it is a number
      fflush(stdin); // discards unconsumed buffered data
      return 0;      // return when not a number
    }
    input++; // increment to next character
  }
  fflush(stdin); // discards unconsumed buffered data
  return 1;      // return when input is a valid number
}

/* function to check whether the user's input for the robot's movement is valid */
int is_valid_movement(char *input)
{
  while (*input != '\n') // while input is not a newline character
  {
    if (!(*input == 'M' || *input == 'm' || *input == 'T' || *input == 't')) // check each character to see if it is the expected characters
    {
      printf("Invalid input for movement.\nInput can only consist of 'm' for move, or 't' for turn. (With no spaces separating characters)"); // print error message to console with help for the user
      return 0;                                                                                                                               // return when input is not M/m or T/t
    }
    input++; // iterate over string array by incrementing pointer
  }
  return 1; // return when input is valid for movement or turning (M/m T/t)
}

/* function to ask for input from the user for the robot's coordinates and its movement */
void input_loop(ROBOT *robot)
{
  char coords[8];                                  // create variable to hold the robot's coordinates
  char movestring[256];                            // create variable tohold he robot's movement string
  printf("\nWhat is the starting x coordinate: "); // print to console asking for user input
  fgets(coords, 8, stdin);                         // read input to coords variable
  if (is_valid_input(coords))                      // check if the input is valid by calling function
  {
    robot->xpos = atoi(coords); // convert coords to integer and set robot's x coordinate
  }
  printf("\nWhat is the starting y coordinate: "); // print to console asking for user input
  fgets(coords, 8, stdin);                         // read input to coords variable
  if (is_valid_input(coords))                      // check if the input is valid by calling function
  {
    robot->ypos = atoi(coords); // convert coords to integer and set robot's y coordinate
  }
  robot->dir = 'N';                                                                // set Robot's starting direction to 'N'
  printf("\nWhat is the movement of the robot?\n");                                // print to console asking for user input
  fgets(movestring, 256, stdin);                                                   // read the input to the movestring character array
  if (is_valid_movement(movestring))                                               // checks if the input is relevant for succesful functionality
  {                                                                                // read input to coords variable
    movement(robot, movestring);                                                   // call function to move the robot
    printf("\nx: %d y: %d direction: %c\n", robot->xpos, robot->ypos, robot->dir); // print the robot's current coordinates and direction on the console
  }
}

/* function to read the user's input and call the respective functions necessary to apply the change */
void movement(ROBOT *robot, char *movement)
{
  int len = strlen(movement);   // get the length of the string
  for (int i = 0; i < len - 1; i++) // for each character in the string, minus the newline character
  {
    if (movement[i] == 't' || movement[i] == 'T') // if the input is 'T' or 't'
    {
      turn(robot); // call function to turn robot direction 90 degrees
    }
    else if (movement[i] == 'm' || movement[i] == 'M') // if the input is 'M' or 'm'
    {
      move(robot); // call function to move robot once in the direction it is currently facing
    }
    else // if the above conditions are not met
    {
      printf("\nInvalid input. Try again.\n"); // prints that message to console if input is invalid
      continue;                                // continues the loop
    }
  }
}
