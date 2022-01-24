// (C) Vernita Gouws, Sicily Brannen, Drake Axelrod, Group: 7 (2022)
// Work package 0
// Exercise 2
// Submission code: 

#include <stdio.h>
#include <stdlib.h>
int rand(void);
void guessing();

int main(int argc, char *argv[])
{
    char answer = 'y';

    do
    {
        guessing();
        printf("Would you like to play again? y/n\n");
        scanf("%s", &answer);
    } while (answer == 'y');

    return 0;
}

void guessing()
{
    int count = 0;
    int num = rand() % 100 + 1;
    int guess;

    do
    {
        printf("%s %d %s", "Guess the number. (You have guessed", count, "times)\n");
        scanf("%d", &guess);
        if (guess == num)
        {
            printf("Well done! You have guessed correctly.\n");
            break;
        }
        else if (guess < num)
        {
            printf("Your guess is too low.\n");
        }
        else
            printf("Your guess is too high.\n");
        count++;
    } while (guess != num);
}