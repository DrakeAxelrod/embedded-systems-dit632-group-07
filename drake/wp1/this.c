#include <stdio.h>

int main()
{
    int binary[8];
int d = 10;
    for (int i = 0; i < 8; i++) { // loop over each number in the array of bits
    int shift = (d >> i) ;
    binary[i] = (char)(d >> i) & 1; // 
    printf("%d %d\n", shift, binary[i]);
  }
//   for (int i = 0; i < 8; i++){
//     printf("%d", binary[i]);
// }
printf("\n");
printf("%d", 250 & 1);
return 0;
}