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

int add(int x, int y) {
  return x + y;
}

int multiply(int x, int y) {
  return x * y;
}

int calculate(int (*operation)(int, int), int x, int y) {

  return operation(x, y);
}


int main(void) {
  int arr[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
  //Passing 2D array as a pointer, you MUST type cast it to a singular flat array
  printf("%zu, %zu, %zu\n", sizeof(arr), sizeof(arr) / sizeof(arr[0]), sizeof(arr[0]) / sizeof(arr[0][0]));
  printTest((int *) arr,  (int) (sizeof(arr) / sizeof(arr[0])) , (int) (sizeof(arr[0]) / sizeof(arr[0][0])));

  //Pointers to functions
  //You need this when you want to store functions in arrays, when you want pass functions to functions, etc..
  //It's when you choose functions during run time not compilation time
  
  //This is passing a function to a function
  int ans;
  ans = calculate(add, 4, 5);
  int ans1 = calculate(multiply, 5, 5);

  printf("This is the answer: %d\n", ans);
  printf("This is the answer: %d\n", ans1);

  //Pointer referencing a function
  int (*addpt)(int, int) = add;

  printf("The answer for this is: %d\n", addpt(100, 256));
}