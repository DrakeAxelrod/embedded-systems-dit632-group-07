// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 2
// Exercise 4_1
// Submission code : XXXXXX(provided by your TA - s)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
void show_results(char val);

typedef unsigned char byte;

int main(int argc, char *argv[])
{
    if (argc != 2)
        return 1;

    // char buffer[2], *input;
    // input = fgets(buffer, 2, stdin);
    //   printf("%d\n", (int)input);

    byte value = (int)strtol(argv[1], NULL, 16);
    //   printf("%d\n", value);
    //   printf("%d", (int)value & 0xFF);
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
        bits[i] = (char)(val & (1 << i)) ? '1' : '0';
        // printf("%c", (val & (1 << i)) ? '1' : '0');
    }

    char arr[4] = {'1', '1', '1'};
    int i = atoi(arr);
    printf("\n\n%d\n\n", atoi(arr)); //(int)log2(111)+1);
    // printf("gear: %d, key: %d", gear_pos, key_pos);
    printf("\n");
    // printf("Name\t\tValue\n");
    // printf("engine_on\t%c\n", bits[0]);
    // // printf("gear_pos\t%d\n", gear_pos);
    // // printf("key_pos\t\t%c\n", key_pos);
    // printf("brake1\t\t%c\n", bits[6]);
    // printf("brake2\t\t%c\n", bits[7]);
}
