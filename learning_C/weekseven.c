#include <stdio.h>
#include <stdbool.h>
#include <math.h>

//Passing 2D array as a pointer, you MUST type cast it to a singular flat array
//Also, the parameter list is basically accepting a pointer, NOTE: arr size information is decayed.
void printTest(int *arr, int row, int column) {

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < column; j++) {
      //Works because i will be zero for first row so 0*row = 0
      printf("%d\n", *((arr + i*row) + j));
    }
  }
  
}

void main(void) {
  int arr[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
  //Passing 2D array as a pointer, you MUST type cast it to a singular flat array
  printf("%zu, %zu\n", sizeof(arr) / sizeof(arr[0]), sizeof(arr[0]) / sizeof(arr[0][0]));
  printTest((int *) arr,  (int) (sizeof(arr) / sizeof(arr[0])) , (int) (sizeof(arr[0]) / sizeof(arr[0][0])));
  
}