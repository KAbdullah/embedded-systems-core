#include <stdio.h>


int main () {
  int s, m;
  char a[m];

  printf("Please enter the number of spaces you'd like and the number of rows: ");
  scanf("%d, %d", &s, &m);
  

  for (int i = 0; i < m; i++) {
    for (int j = i; j < s; j++) {
      printf(" ");
    }
    a[i] = '*';
    printf("%s\n", a);
  }
}