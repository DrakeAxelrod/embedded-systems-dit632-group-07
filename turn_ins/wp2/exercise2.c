// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 2
// Exercise 2
// Submission code : XXXXXX(provided by your TA - s)

#include <stdio.h> // functions for standard input/output
#include <stdlib.h> // for standard library functions (malloc, srand)
#include <time.h> // included for the random seed function

//#### Constants #####
#define MAX 5

// ##### typedefs          ####
typedef struct q{
  int number;
  struct q *next;
  struct q *prev;
} REGTYPE;

// ##### Function declarations   #####

REGTYPE *random_list(void);         // declaration of method
REGTYPE *add_first(REGTYPE *, int); // declaration of method

//###### Main program #######
int main(int argc, char *argv[])
{
  int nr = 0;

  REGTYPE *act_post, *head = NULL;

  srand(time(0));               // random seed
  head = random_list();         // call function to create initial list
  head = add_first(head, 1337); // testing add_first
  act_post = head;              // set
  while (act_post != NULL)
  {
    printf("\n Post nr %d : %d", nr++, act_post->number);
    act_post = act_post->next;
  }

  // --- Free the allocated memory  ---

  while ((act_post = head) != NULL)
  {
    head = act_post->next;
    free(act_post);
  }

  return 0;
}

// ==== End of main ======================================

REGTYPE *random_list(void)
{
  int nr;
  int i = 0;

  REGTYPE *top, *old, *item;
  top = NULL;
  while (i < MAX)
  {
    item = (REGTYPE *)malloc(sizeof(REGTYPE));
    item->number = rand() % 100 + 1;
    if (top == NULL)
    {
      item->next = NULL;
      item->prev = NULL;
      top = item;
    }
    else
    {
      old = top;
      while (old->next != NULL)
      {
        old = old->next;
      }
      item->prev = old;
      old->next = item;

      // item->prev = NULL;
      // top->prev = item;
      // old = top;
      // top = item;
      // item->next = old;
      // old->prev = top;
      // old->next = NULL;
      printf("old-prev: %d, old: %d, old-next: %d\n", old->prev, old, old->next);
    }
    i++;
  }
  return (top);
}

//==========================================================

REGTYPE *add_first(REGTYPE *temp, int data)
{
  REGTYPE *item = (REGTYPE *)malloc(sizeof(REGTYPE));
  item->number = data;
  temp->prev = item;
  item->next = temp;
  // struct Node* newNode = GetNewNode(x);
  // if(head == NULL) {
  // 	head = newNode;
  // 	return;
  // }
  // head->prev = newNode;
  // newNode->next = head;
  // head = newNode;
  return item;
}
