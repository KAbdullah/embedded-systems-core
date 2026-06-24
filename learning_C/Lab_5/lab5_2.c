#include <stdio.h>

void backwardArray();


int main() {
  int arr[6];
  int *pt = arr;
  printf("Pass me 6 intgeters (eg., 1,2,3,4,5,6): ");
  scanf("%d %d %d %d %d %d", pt, pt++, pt++, pt++, pt++, pt++);

  backwardArray(arr);
  
  int *pt2 = arr;
  printf("%d %d %d %d %d %d\n", *pt2, *pt2++, *pt2++, *pt2++, *pt2++, *pt2++);


}

void backwardArray(int arr[6]) {
  for (int i = 0; i < 3; i++) {
    int temp = arr[i];
    arr[i] = arr[5 - i];
    arr[5 - i] = temp;
  }
}