// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 2
// Exercise 3
// Submission code : XXXXXX(provided by your TA - s)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "ex3.bin"
typedef struct
{
  char firstname[20];
  char famname[20];     //PERSON ppost;
  char pers_number[14]; // yyyymmddnnnnc
} PERSON;

void menu();
void new_db();
void create();
void search();
void print_all();
void print_person(PERSON);
void file_exists();

int main(int argc, char const *argv[])
{
  while (1)
  {
    menu();
  }
  return 0;
}

void menu()
{
  printf(
      "1. Create a new and delete the old file.\n"
      "2. Add a new person to the file.\n"
      "3. Search for a person in the file.\n"
      "4. Print out all in the file.\n"
      "5. Exit the program\n");
  printf("> ");
  char choice = getchar();
  getchar(); //handle the 'Enter' (\n)
  int return_code;
  switch (choice)
  {
  case '1':
    new_db();
    break;
  case '2':
    create();
    break;
  case '3':
    search();
    break;
  case '4':
    print_all();
    break;
  case '5':
    exit(0); // exit the program
    break;
  default:
    printf("invalid choice\n");
    menu();
    break;
  }
}

void new_db()
{
  FILE *fp;
  fp = fopen(FILE_NAME, "wb+");
  PERSON dummy = {"Jane", "Doe", "199909091111"};
  fwrite(&dummy, sizeof(dummy), 1, fp);
  PERSON dummy2 = {"Jack", "Doe", "199909091112"};
  fwrite(&dummy2, sizeof(dummy2), 1, fp);
  fclose(fp);
}

void create()
{
  ensure_db_initialized();
  FILE *fp;
  char firstname[20];
  char famname[20];
  char pers_number[13];
  PERSON person = {NULL, NULL, NULL};
  fflush(stdin);
  fflush(stdout);
  printf("What is the firstname? ");
  fgets(person.firstname, sizeof(person.firstname), stdin);
  person.firstname[strlen(person.firstname) - 1] = '\0';
  printf("What is the lastname? ");
  fgets(person.famname, sizeof(person.famname), stdin);
  person.famname[strlen(person.famname) - 1] = '\0';
  printf("What is the personnummer? ");
  fgets(person.pers_number, sizeof(person.pers_number), stdin);
  person.pers_number[strlen(person.pers_number) - 1] = '\0';
  print_person(person);
  fp = fopen(FILE_NAME, "ab");
  fwrite(&person, sizeof(person), 1, fp);
  fclose(fp);
}

void print_all()
{
  ensure_db_initialized();
  FILE *fp;
  PERSON person;
  fp = fopen(FILE_NAME, "rb");
  while (fread(&person, sizeof(person), 1, fp) != 0)
  {
    print_person(person);
  }
  fclose(fp);
}

void print_person(PERSON person)
{
  printf("first name: %s\n", person.firstname);
  printf("last name: %s\n", person.famname);
  printf("personal number: %s\n", person.pers_number);
}

void search()
{
  ensure_db_initialized();
  FILE *fp;
  PERSON person;
  char searchterm[20];
  char ch = '\0';
  fp = fopen(FILE_NAME, "rb");
  printf("1. Search by first name\n");
  printf("2. Search by last name\n");
  ch = getchar();
  printf("What is the name: ");
  scanf("%s", searchterm);
  while (fread(&person, sizeof(person), 1, fp) != 0)
  {
    if (strcmp(person.firstname, searchterm) == 0 && ch == '1')
    {
      print_person(person);
    }
    if (strcmp(person.famname, searchterm) == 0 && ch == '2')
    {
      print_person(person);
    }
  }
  getchar(); //handle the 'Enter' (\n)
  fclose(fp);
}

void ensure_db_initialised()
{
  if (fopen(FILE_NAME, "rb") != NULL)
  {
    new_db();
  }
}
