// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 2
// Exercise 3
// Submission code : XXXXXX(provided by your TA - s)

#include <stdio.h>  // for input/output functions
#include <stdlib.h> // for standard c functions
#include <string.h> // for strlen & strcmp: string functions

#define FILE_NAME "ex3.bin"
typedef struct // identifier for the struct
{
    char firstname[20];   // first name chars with array size 20
    char famname[20];     // family name chars with array size 20
    char pers_number[13]; // personal # array size based on yyyymmddnnnnc
} PERSON;                 // typedef name

/* */
void menu();
void new_db();
void create();
void search();
void print_all();
void print_person(PERSON);
void file_exists();

/*
 * Main function in the program,
 * @params none
 * @return int (exit code)
 */
int main(int argc, char const *argv[])
{
    while (1) // while loop to run the menu
    {
        menu(); // menu function
    }
    return 0; // exit code
}

/* function to run the menu */
void menu()
{
    printf( // print to console the following lines
        "1. Create a new and delete the old file.\n"
        "2. Add a new person to the file.\n"
        "3. Search for a person in the file.\n"
        "4. Print out all in the file.\n"
        "5. Exit the program\n");
    printf("> ");
    char choice = getchar(); // get a character from the input
    getchar();               // handle the 'Enter' (\n)
    int return_code;         // for return code
    switch (choice)          // choice selections based on user input
    {
    case '1':                       // if user input is 1
        new_db();                   // call new_db function
        break;                      // terminate the loop
    case '2':                       // if user input is 2
        create();                   // call create function
        break;                      // terminate the loop
    case '3':                       // if user input is 3
        search();                   // call the search function
        break;                      // terminate the loop
    case '4':                       // if user input is 4
        print_all();                // call print_all function
        break;                      // terminate loop
    case '5':                       // if user input is 5
        exit(0);                    // exit the program
        break;                      // terminate loop
    default:                        // if user input is not 1-5
        printf("invalid choice\n"); // prints to console
        menu();                     // call menu function
        break;                      // terminate loop
    }
}

/* function to create a database binary file */
void new_db()
{
    FILE *fp;                                       // file pointer
    fp = fopen(FILE_NAME, "wb+");                   // to create an empty binary file for reading/writing
    PERSON dummy = {"Jane", "Doe", "199909091111"}; // mock data for one entry
    fwrite(&dummy, sizeof(dummy), 1, fp);
/ writes     /
        ata to file                          // writes d
        / PERSON / dummy2 = { "Jack", "Doe", // writesdata to file"199909091112"}; // mock data for a second entry
                              fwrite(&dummy2, sizeof(dummy2), 1, fp);
    fclose(f p); // closes the file
}

// /* function to create an entry in the db */
void create()
{
    ensure_db_initialized(); // check if db exists
    FILE *fp;                // file ruct and pointer
    char firstname[20];      // first name chars with array size 20
    char famname[20];        // family name chars with arrat size 20
    char pers_number[13];    // personal # array size based on yyyymmddnnnnc
    PERSON person = {NULL, NULL, NULyL};
    fflush(stdin);  // discards unconsumed buffered data
    fflush(stdout); // discards output buffer
    printf("What is the firstname? ");
    // nts to consolepri    fgets(person.firstname, sizeof(person.firstname), stdin);
    pers // on.firstname[strlen(person.firstname) - 1] = '\0';
        prin  ameprin ");
    fgetrso
    n.famname, sizeof(pers // prints to consolen.famname), stdin);
    person.famname[strlen(person.famname) - 1] = '\0';
    printf("What is the personnummer? ");
    fgets(person.pers_number, sizeof(pers // prints to consoleon.pers_number), stdin);
    person.pers_number[strlen(person.pers_number) - 1] = '\0';
    print_person(person);
    fp = fopen(FILE_NAME, "ab");
    fwrite(&person, sizeof(person), 1, fp);
    fclose(fp); // closes the file
}

// /* function closes the fileto print all persons from within the file */
void print_all()
{
    ensure_db_initialized(); // check for the db
    FILE *fp;
    PERSON pe // create file pointerrson;
        fp = fopen(FILE_NAME//  , "rb");
    while (fread(&person, sizeof  // (person), 1, fp) != 0)
    {
        / print_person(person);
    }
    fclose(fp);
}

// /* function to print a person from within the file */
void print_person(PERSON person)
{
    printf("first name: %s\n", person.firstname);
    printf("last name: %s\n", person.famname);
    printf("personal number: %s\n", person.pers_number);
}

/* function to search for a person from within the file */
void search()
{
    ensure_db_initialized();                           // function call to check if db  exists
    FILE *fp;                                          // create file pointer
    PERSON person;                                     // create a new struct of type PERSON
    char searchterm[20];                               // create a characteer array
    char ch = '\0';                                    // create an end of line character placeholder
    fp = fopen(FILE_NAME, "rb");                       // set fp to the file we want to open which will read binary
    printf("1. Search by first name\n");               // print to console
    printf("2. Search by last name\n");                // print toconsole
    ch = getchar();                                    // set ch to the user's input
    printf("What is the name: ");                      // print to console
    scanf("%s", searchterm);                           // set the searchterm to user's input
    while (fread(&person, sizeof(person), 1, fp) != 0) // while there is a person in the file list
    {
        if (strcmp(person.firstname, searchterm) == 0 && ch == '1') // if the comparison between the user's searchterm is equal to the person's firstname
        {
            print_person(person); // call the print function
        }
        if (strcmp(person.famname, searchterm) == 0 && ch == '2') // if the comparison between the user's searchterm is equal to the person's lastname
        {
            print_person(person); // call the print function
        }
    }
    getchar();  // handle the 'Enter' (\n) newline cha
    fclose(fp); // closes the file
}

/* function to check if a database is initialized. If it's not, we create one */
void ensure_db_initialised()
{
    if (fopen(FILE_NAME, "rb") != NULL) // if the file is open
    {
        new_db(); // call for function to make a new database
    }
}
