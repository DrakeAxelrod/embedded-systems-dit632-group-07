// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 2
// Exercise 4_1
// Submission code : XXXXXX(provided by your TA - s)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void show_results(char val);

typedef unsigned char byte;

void main(int argc, char *argv[])
{
  if (argc != 2)
    return 1;

  // char buffer[2], *input;
  // input = fgets(buffer, 2, stdin);
  //   printf("%d\n", (int)input);

  byte value = (int)strtol(argv[1], NULL, 16);
  printf("%d\n", value);
  printf("%d", (int)value & 0xFF);
  show_results(value);
  // value += atoi(argv[2]) >> 4;
  // value += atoi(argv[3]) >> 2;
  // value += atoi(argv[4]) << 1;
  // value += atoi(argv[5]);
}
void show_results(char val)
{
  char bits[8];
  for (int i = 7; 0 <= i; i--)
  {
    bits[i] = (val & (1 << i)) ? '1' : '0';
    // printf("%c", (val & (1 << i)) ? '1' : '0');
  }
  char a = val ^ 128; // 0111 0000 -> 0000 0111 -> 7
  char arg2[8] = { '0', '0', '0', '0', '0', bits[7], bits[6], bits[5]};
  int lo = 0;
  int hi = 7;
  int top = (val >> lo) & ((1 << hi) - 1);
  int bottom = val & ((1 << lo) - 1);
  printf("\n");
  printf("Name\t\tValue\n");
  printf("engine_on\t%c\n", bits[0]);
  printf("gear_pos\t%c\n", 0);
  printf("key_pos\t\t%c\n", 0);
  printf("brake1\t\t%c\n", 0);
  printf("brake2\t\t%c\n", 0);
}
