#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>


int main() {
  int i = 3;
  float f = 3.14;
  int falsey = false;
  char *s = "Hello brotha: ";
  int8_t number3 = 8;
  char greetings[] = "hello";
  long double long_num = 7L;
  double double_num = 7.2;
  unsigned int unsignednumber = 8U;
  #define N 5

  printf("%s i = %d and f = %f!\n", s, i, f);
  printf("%zu\n", sizeof(long_num));

  printf("%5.2Lf\n", long_num);
  printf("%10.8lf\n", double_num);
  printf("%s\n", greetings);

  double varC;

  printf("Here they lies: %d\n", N);

  int varA = 9;
  int varB = 2;

  //Type casting
  varC = varA / (float) varB;
  printf("%f\n", varC);

  // if (!(12 == 123)) {
  //   printf("In the false case statement!\n");
  //   printf("%d\n", 12 == 123);
  //   printf("%f\n", pow(3, 3));
  // }

  // for (int i = 0, j = 10; i < 11 && j < 100; i++, j++)
  //   printf("%d, %d\n", i, j);

  return 1;
}