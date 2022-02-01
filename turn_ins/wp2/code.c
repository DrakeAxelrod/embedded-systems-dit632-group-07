// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 2
// Exercise 4_1
// Submission code : XXXXXX(provided by your TA - s)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
Name         Range    Bits   Info    
engine_on    0..1     1     Is engine on or off . This is bit no 7  
(MSB == Most Significant Bit, the one that carries the value 128 in decimal) 
gear_pos      0..4     3      The position of the gear. Three bits means that we can have 23 == 7 positions    
key_pos       0..2     2       Position of the key – 0 == stop, 1 == on, 2 == engine starter on     
brake1         0..1     1        Position of the front brakes   
brake2         0..1     1        Position of the rear brakes. Bit no 0 (LSB) 
*/
// We should store them in a byte like this :
// [engine_on][gear_pos][key_pos][brake1][brake2]
//   1 bit      3 bits   2 bits   1 bit   1 bit

typedef unsigned char byte;

int main(int argc, char const *argv[])
{
  if (argc != 6)
    return 1;
  int value = 0;

  value += atoi(argv[1]) << 7;
  value += atoi(argv[2]) << 4;
  value += atoi(argv[3]) << 2;
  value += atoi(argv[4]) << 1;
  value += atoi(argv[5]);
  printf("value: %d", value);
  byte packed = value;
  convert(packed);
  return 0;
}

char convert(char *bin)
{
  int value = (int)strtol(bin, NULL, 2); // convert input from a string to an integer to a base 2 to represent binary
  char hex[12];                          // create character array for hex representation
  sprintf(hex, "%x\n", value);           // writes values to the hex array
}
Step 1: Divide the original decimal number by 16
Step 2: Divide the quotient by 16
Step 3: Repeat the step 2 until we get quotient equal to zero.
