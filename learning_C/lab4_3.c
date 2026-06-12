#include <stdio.h>
#include <stdbool.h>

int powTo(int base, int exp) {
  int result = 1;
  while (exp > 0) {
    result *= base;
    exp --;
  }
  return result;
}


void main(void) {
  int numberArray;
  int i;
  int j;

  scanf("%d %d %d", &numberArray, &i, &j);

  int removeBack = numberArray / powTo(10, i);

  int removeFront = removeBack % powTo(10, j);
  
  printf("%d\n", removeFront);

}