// (C) Drake Axelrod, group: 07 (2022)
// Work package
// Exercise
// Submission code : XXXXXX(provided by your TA - s)
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;

void help();
void convert(char *in);
int valid_int(char *str);
/*
 * Main function in the program,
 * @params none
 * @return int (exit code)
 */
int main(int argc, char *argv[])
{
  char *buffer, *input;
  input = fgets(buffer, 256, stdin);
  int n = sizeof(input) / sizeof(input[0]);
  printf("size of input: %d\n", n);
  //printf("a%s\n", stdin);
  convert(input);
  //   int result = valid_int(argv[1]);
  //   // check if number is float also
  //   if (argc > 1 && argc < 3) {
  //     if (result) {
  //       convert(argv[1]);
  //     } else {
  //       printf("failed at result if check\n");
  //     }
  //     // if (input == *argv[1]) {
  //     // } else {
  //     //   printf("failed on equality");
  //     // }
  //   } else {
  //     printf("must provide one arg\n");
  //   }
  // successful execution return code
  return 0;
}

void help() { printf("helpful info\n"); }

void convert(char *in)
{
  //char *CHARS = "0123456789ABCDEF";
  //int value = strtol(in, NULL, 2);
  // char *one = { in[0], in[1], in[2], in[3] };
  // char *one = { in[5], in[6], in[7], in[8] };
  int value = (int)strtol(in, NULL, 2);

  // convert integer to hex string
  char hexString[12]; // long enough for any 32-bit value, 4-byte aligned
  sprintf(hexString, "0x%x\n", value);

  // output hex string
  printf(hexString);
  // while (value != 0)
  // {
  //   value >>= 4;
  //   printf("%c", CHARS[ value & 0xF ]);
  // }
  // printf("%d", value);
  // for (int i = 0; i < 8; i+1) {
  //   tmp += ();
  // }
}

int valid_int(char *str)
{
  while (*str != '\0')
  {
    // isdigit return 0 or 1 depending on if char is an int which you check with
    // 0 if 0 true else 1 false
    if (!isdigit(*str))
    {
      return 0;
    }
    str++;
  }
  return 1;
}
