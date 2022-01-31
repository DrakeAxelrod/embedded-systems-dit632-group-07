// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 2
// Exercise 2
// Submission code : XXXXXX(provided by your TA - s)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#### Constants #####
#define MAX 5

// ##### typedefs          ####
typedef struct q
{
  int number;
  struct q *next;
  struct q *prev;
} REGTYPE;

// ##### Function declarations   #####

REGTYPE *random_list(void);
REGTYPE *add_first(REGTYPE *temp, int data);

//###### Main program #######
int main(int argc, char *argv[])
{
  int nr = 0;

  REGTYPE *act_post, *head = NULL;

  srand(time(0)); //   Random seed
  head = random_list();
  act_post = head;
  while (act_post != NULL)
  {
    printf("\n Post nr %d : %d", nr++, act_post->number);
    act_post = act_post->next;
    break;
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
  item = (REGTYPE *)malloc(sizeof(REGTYPE));
  while (i < MAX)
  {
    item->next = NULL;
    item->prev = NULL;
    item->number = rand() % 100 + 1;
    // printf("%d", MAX);
    // printf("i=%d", i);
    if (i == 0)
    {
      top = item;
    }
    else
    {
      top->next = item;
      printf("now: %d, prev: %d", top->number, top->next->number);
      break;
    }
    i++;
  }

  // item top = null top = item
  // item old = top top = item
  // top - #1 - prev - #2 next - #1
  // top - #2 - prev - null next - old
  // top - #3 -

  // top->prev = old;
  // top->next = item;
  // top->number = rand() % 100 + 1; // get a random number from the random number generator
  return (top);
}

//==========================================================

REGTYPE *add_first(REGTYPE *temp, int data)
{
  // struct Node* newNode = GetNewNode(x);
  // if(head == NULL) {
  // 	head = newNode;
  // 	return;
  // }
  // head->prev = newNode;
  // newNode->next = head;
  // head = newNode;
}
