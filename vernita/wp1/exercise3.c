// (C) Vernita Gouws, Sicily Brannen, Drake Axelrod, Group: 7 (2022)
// Work package 0
// Exercise 2
// Submission code:

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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
    char input;
    int guess;

    do
    {
        printf("%s", "Guess the number.\n");
        if (scanf("%d", &guess) == 1 && guess >= 1 && guess <= 100)
        {
            count++;
            if (guess == num)
            {
                printf("%s %d %s", "Well done! You guessed", count, "times to get the correct answer.\n");
                break;
            }
            else if (guess < num)
            {
                printf("Your guess is too low.\n");
            }
            else
                printf("Your guess is too high.\n");
        } else {
            scanf("%*[^\n]"); //discard that line up to the newline
            printf("Wrong format. Only numbers between 1-100 (inclusive) accepted.\n");
            // continue;
        }
    } while (guess != num);
}