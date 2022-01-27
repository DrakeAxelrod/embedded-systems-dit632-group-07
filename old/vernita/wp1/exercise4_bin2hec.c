#include <stdio.h>
#include <math.h>

int convert(int x);

int main(int argc, char *argv[])
{
    int number;
    if (argc > 1)
    {
        convert(argv[1]);
        printf("%s %d", "binary is:", number);
    }
    else
        return 2;
}

int convert(int x)
{
    int current = 1;
    int remainder = 0;
    long long binary = 0;

    while (x > 0)
    {
        remainder = x % 2;
        x /= 2;
        binary = remainder * current;
        current *= 10;
    }
    return binary;
}