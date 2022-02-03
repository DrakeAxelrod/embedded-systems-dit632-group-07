// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 2
// Exercise 2
// Submission code : XXXXXX(provided by your TA - s)

#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "ex3.bin"
typedef struct
{
  char firstname[20];
  char famname[20];     //PERSON ppost;
  char pers_number[13]; // yyyymmddnnnc
} PERSON;

void menu();
void new_db();
void write();
void create();
void delete ();
void search();
void print_all();
void print_person(PERSON);

// unsigned char buffer[10] = "helloworld"; // 10 byte array
// // WRITE
// FILE *fp;                              // file pointer
// fp = fopen("./ex3.bin", "wb");         // open file with (write byte)
// fwrite(buffer, sizeof(buffer), 1, fp); // write 10 bytes from our buffer
// fclose(fp);                            // close file
// // READ
// FILE *ptr;
// ptr = fopen("./ex3.bin", "rb");        // r for read, b for binary
// fread(buffer, sizeof(buffer), 1, ptr); // read 10 bytes to our buffer
// printf("%s", buffer);
// return 0;

int main(int argc, char const *argv[])
{
  menu();
  //unsigned char buffer[10] = "helloworld"; // 10 byte array
  return 0;
}

void menu()
{
  //char choice = 0;
  printf(
      "1. Create a new and delete the old file.\n"
      "2. Add a new person to the file.\n"
      "3. Search for a person in the file.\n"
      "4. Print out all in the file.\n"
      "5. Exit the program\n");
  printf("> ");
  char choice = getchar();

  // fgets(choice, 1, stdin);
  switch (choice)
  {
  case '1':
    new_db(); // fight me
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
    printf("invalid choice");
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
  char firstname[20];
  char famname[20];
  char pers_number[13];
  printf("What is the firstname?");
  fgets(firstname, 20, stdin);
  printf("What is the lastname?");
  fgets(famname, 20, stdin);
  printf("What is the personnummer?");
  fgets(pers_number, 13, stdin);
  FILE *fp;
}

void print_all()
{
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
  FILE *fp;
  PERSON person;
  char searchterm[20];
  char option[1];
  printf("1. Search by first name\n");
  printf("2. Search by last name\n");
  scanf("\n%c", option);
  //   fgets(option, 1, stdin);
  if (option == '1' || option == '2')
  {
    printf("What is the name? ");
    fgets(searchterm, 20, stdin);
    while (fread(&person, sizeof(person), 1, fp) != 0)
    {
      if (person.firstname == searchterm)
        print_person(person);
    }
  }
  fgets(search, 20, stdin);
  fp = fopen(FILE_NAME, "rb");

  fclose(fp);
}

void write()
{
  FILE *fp;
}

void delete ()
{
  FILE *fp;
}
