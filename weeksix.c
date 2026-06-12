#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

//Defining the Array in 3 different ways
void passingArrays1(int *b ) {

}

void passingArrays2(int b[10]) {

}

void passingArrays3(int b[]) {

}


void main(void) {
  /*Because the stack goes from high memory to lower memory
    pushing onto a stack is:
    p++*
    Poping from a stack is:
    *--p

    Note: The pointer automatically moves to the next lower memory empty space after pushing,
    therefore it must go pack first before popping.
  
  */

  int yoloArray[5] = {};

  //Few ways of passing arrays
  passingArrays1(yoloArray);

  //Arrays of arrays
  int twoDArray[][4] = {{1,2,3,4}};

  //Specifying row is optional, but specifying columns is mandatory
  //This is invalid: [row][column]
  // int twoDArray1[2][] = {{1,2,3,4}, {1,2,3,4}};

  //Indexing two day arrays via pointers
  // *(*(twoDArray+2)+1) is the same as twoDArray[2][1]

  //Printf evaluates it's arguments from right to left, LIFO
  //This means, depending on if you increment the pointer itself or just add to the pointer
  //You can get some cheeky results
  int *pf = twoDArray[0];
  //This prints out in order
  printf("%d %d %d\n", *pf, *(pf + 1), *(pf + 2));
  //This prints out in reverse, because of the cheeky LIFO rule that printf uses for evaluating
  //Right most pf evaluates to 3, the second right most evaluates to 2, then finally 1.
  printf("%d %d %d\n", *pf, *pf++, *pf++);

  //Array of pointers
  //This is basically an array of pointers that points to an element
  //so words[0] is a pointer, pointing to apple and vice versa
  char *words[] ={"apple", "cherry", "orange"};
  printf("%s\n", words[1]);

  char *words2[][3] ={{"apple", "cherry", "orange"}, {"Jello", "Jam", "Marmalade"}};
  printf("%s\n", words2[1][2]);

  //Pointers to whole arrays
  //Basically you say, this is a pointer and it indexes 3 spaces each time you get it's address.
  //Officially called Stride Contract, basically a two way promise saying that I will use this pointer to only look at
  //Arrays of columns with size 3, in turn you must calculate index * 3 spaces for me (math scaling done for me by compiler).
  //This works, because in RAM, the arrays are flattened and set side by side.
  int (*pt)[3];
  int arrayed[2][3] = {{1,2,3}, {4,5,6}};

  pt = arrayed;
  //First *(pt+1) returns address of second row, then you must * again to get value 
  printf("%d\n", **(pt+1));

  //int arr[M][N] is the same as int (*arr)[3]

}

//Passing 2D Arrays
//COLUMNS must always be defined
//you can do it 3 ways:

void loss1(int arr[][3]) {

}
void loss2(int arr[2][3]) {

}
void loss3(int (*arr)[3]) {

}


