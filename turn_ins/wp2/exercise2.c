// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 2
// Exercise 2
// Submission code : XXXXXX(provided by your TA - s)

#include <stdio.h>  // functions for standard input/output
#include <stdlib.h> // for standard library functions (malloc, srand)
#include <time.h>   // included for the random seed function

//#### Constants #####
#define MAX 5

// ##### typedefs  ####
typedef struct q // double linked list node
{
    int number;     // value in this node
    struct q *next; // the next node in the list
    struct q *prev; // the previous node in the list
} REGTYPE;          // so you dont have to use struct q

// ##### Function declarations   #####
REGTYPE *random_list(void);         // declaration of method
REGTYPE *add_first(REGTYPE *, int); // declaration of method

//###### Main program #######
int main(int argc, char *argv[])
{
    int nr = 0; // counter

    REGTYPE *act_post, *head = NULL; // init the head and act_post pointers
// TODO - put while in external function. TEST

    srand(time(0));               // random seed
    head = random_list();         // call function to create initial list
    act_post = head;              // set the current position to head
    while (act_post != NULL)      // while the current position is not null
    {
        printf("\n Post nr %d : %d", nr++, act_post->number); // print the nr and value of correspond node, and increment nr
        act_post = act_post->next;                            // set the position to the next item in list
    }

    head = add_first(head, 1337); // testing add_first
    act_post = head;              // set the current position to head
    while (act_post != 0)      // while the current position is not 0
    {
        printf("\n Post nr %d : %d", nr++, act_post->number); // print the nr and value of correspond node, and increment nr
        act_post = act_post->next;                            // set the position to the next item in list
    }

    // --- Free the allocated memory  ---
    // reset the position of act_post to head since act_post is at the end of list after first while loop
    while ((act_post = head) != 0) //  while current position is not 0
    {
        head = act_post->next; // set to next position as you free each this is to make sure that you free everything
        free(act_post);        // since the head is pointing to next we can free the previous head without losing the list
    }
    printf("\n"); // clean up lines
    return 0; // exit code
}

// ==== End of main ======================================
/* function to create a random list using the MAX amount of list items */
REGTYPE *random_list(void)
{
    int nr;    // set a variable and initialise it to 0
    int i = 0; // set a variable and initialise it to 0

    REGTYPE *top, *old, *item; // create three pointers to the struct type of REGTYPE
    top = NULL;                // set top to null
    while (i < MAX)            // while i is not equal to MAX
    {
        item = (REGTYPE *)malloc(sizeof(REGTYPE)); // create an item struct of type REGTYPE
        item->number = rand() % 100 + 1;           // set the item's number variable to a random integer
        item->next = NULL;                         // initialise item's next variable to null
        if (top == NULL)                           // the first run of the loop
        {
            item->prev = NULL; // initialise item's previous variable to null
            top = item;        // set top to current item
        }
        else // for every run of the loop after the first item has been set to the top
        {
            old = top;                // the old pointer is set as the current top
            while (old->next != NULL) // while there are next items in the list
            {
                old = old->next; // set old to the next item in the list
            }
            item->prev = old; // set the current item's previous variable to the old item
            old->next = item; // set the end of the list's next to the current item
        }
        i++; // increment i
    }
    return (top); // return the top of the list
}

//==========================================================
/* function to append an item to the top of the list */
REGTYPE *add_first(REGTYPE *temp, int data)
{
    REGTYPE *item = (REGTYPE *)malloc(sizeof(REGTYPE)); // create a new struct of type REGTYPE
    item->number = data; // set item's number variable to the data parameter (a random int)
    temp->prev = item; // set temp's previous variable (head passed as parameter) to the current item
    item->next = temp; // set item's next variable to the current head (parameter passed as temp)
    return item; // return item which is now the list's head
}
