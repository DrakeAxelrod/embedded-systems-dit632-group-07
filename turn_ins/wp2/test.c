#include <stdio.h>

int main(int argc, char const *argv[])
{
  int i = 1;
  // 64 32 16 = 112
  int y = 6 << 2 << 1 << 1;
  int x = 6 << 1;
  int a = 1 << 6;
  int b = 1 << 5;
  int c = 1 << 4;
  int d = a + b + c;
  printf("%d\n", 0 << 7);
  printf("%d\n", 7 << 4); 
  printf("%d\n", 2 << 2);
  printf("%d\n", 1 << 1);
  printf("%d", 1);

  return 0;
}
// i = 7
// convert number to bits
// 1 << 7;
// while (bit !\0) {
//     bit << i
// }
