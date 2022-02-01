// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 2
// Exercise 4_1
// Submission code : XXXXXX(provided by your TA - s)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned char byte;

void print_byte_as_bits(char val);

int main(int argc, char const *argv[])
{
  if (argc != 6)
    return 1;
  byte value = 0;
  value += atoi(argv[1]) << 7;
  value += atoi(argv[2]) << 4;
  value += atoi(argv[3]) << 2;
  value += atoi(argv[4]) << 1;
  value += atoi(argv[5]);
  printf("%x\n", value);

  printf("%x\n", value & 0xFF); // 1111 1111
  printf("%x\n", value);
  printf("%02X\n", value);
  printf("%d\n", (int)0x97);
  print_byte_as_bits(value);
  unsigned char c = 255;
  printf("Unsigned char: %hhu\n", c);
  return 0;
}

void print_byte_as_bits(char val)
{
  for (int i = 7; 0 <= i; i--)
  {
    printf("%c", (val & (1 << i)) ? '1' : '0');
  }
}
