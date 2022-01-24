// (C) Vernita Gouws, Sicily Brannen, Drake Axelrod, Group: 7 (2022)
// Work package 0
// Exercise 1
// Submission code: 39CQFR
#include <stdio.h>

void main()
{
    int ans = 1; // variable for user input, initialised in order to access while loop

    while (ans > 0 && ans < 6) // program runs while these 2 conditions are fulfilled
    {
        printf("Enter any number from 1 to 5 for today's motivational quote.\n"); // string displayed on console to prompt user's input
        scanf("%1d", &ans); // utility function that saves user's input to the variable created in line 9

        switch (ans) // a switch case based on the user's input
        {
        case 1: // If user's input is 1, this string will be displayed in the console
            printf("Today is the first day of the rest of your life.\n\n");
            break; // breaks out of the switch case

        case 2: // If user's input is 2, this string will be displayed in the console
            printf("Need a few days off? Take a few days off. Listen to your body.\n\n");
            break; // breaks out of the switch case

        case 3: // If user's input is 3, this string will be displayed in the console
            printf("All you need is a good bottle of wine, a nice sofa, and great company.\n\n");
            break; // breaks out of the switch case

        case 4: // If user's input is 4, this string will be displayed in the console
            printf("You're one of 8 billion people. You don't have to run around every day - share your load.\n\n");
            break; // breaks out of the switch case

        case 5: // If user's input is 5, this string will be displayed in the console
            printf("Don't like it? Change it.\n");
            break; 

        // operator doesn't match any case (less than 1 or greater than 5)
        default:
            printf("Error: Number is not in range"); // string output to let user know their input is outside of the specified range
            break;// breaks out of the switch case
        }
    } 
}