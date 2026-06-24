#include <stdio.h>


int main () {
  int s, m;
  //This is a VLA that get's set with m which currently has garbage data because it isn't set yet by the user.
  //It could cause segmentation faults
  char a[m];

  printf("Please enter the number of spaces you'd like and the number of rows (e.g., 5, 6): ");
  //Scanf returns the number of successful variables that were set
  if (scanf("%d, %d", &s, &m) != 2) {
    printf("Invalid input. \n");
    //Anything besides return 1 indicates an Error
    return 1;
  }
  

  for (int i = 0; i < m; i++) {
    for (int j = i; j < s; j++) {
      printf(" ");
    }
    
    for (int k = 0; k <= i; k++) {
      printf("*");
    }
    printf("\n");
  }
}