// (C) Drake Axelrod, Vernita Gouws, Sicily Ann Brannen group: 07 (2022)
// Work package 2
// Exercise 2
// Submission code : XXXXXX(provided by your TA - s)

#include <stdio.h>


int main(int argc, char const *argv[])
{
  unsigned char buffer[10]; // 10 byte array
  // WRITE
  FILE *fp; // file pointer
  fp = fopen("./ex3.bin", "wb"); // open file with (write byte)
  fprintf("hello world");
  //fwrite(buffer, sizeof(buffer), 1, fp); // write 10 bytes from our buffer
  fclose(fp); // close file
  // READ
  FILE *ptr;
  ptr = fopen("./ex3.bin", "rb"); // r for read, b for binary
  fread(buffer, sizeof(buffer), 1, ptr); // read 10 bytes to our buffer
  for (int i = 0; i < 10; i++)
    printf("%u ", buffer[i]); // prints a series of bytes
  return 0;
}
