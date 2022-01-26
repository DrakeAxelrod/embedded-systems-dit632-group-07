#include <stdio.h>
#include <math.h>
#include <stdlib.h>   

int convert(int x);

    int main(int argc, char *argv[])
{
    char *a = argv[1]; // create pointer to command line argument for encryption amount
    int number = atoi(a); 
    if (argc > 1)
    {
        int binary = convert(number);
        printf("%s %d\n","binary is:",  binary);
        return 0;
    }
    else
        return 2;
}

int convert(int x)
{
    int current = 1;
    int remainder = 0;
    long long binary = 0;
    long long binaryFormat = 00000000;
    int i = 0;

    while (i < 8) 
    {
        remainder = x % 2;
        x /= 2;
        binary += remainder * current;
        current *= 10;
        i++;
    }
    return binary | binaryFormat;
}