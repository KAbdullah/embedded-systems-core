#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

void swap(int* swapx, int* swapy);


//Variable declared outside of main stay invisible to other files
static int winner;
//Variable can be used in other files, but those files must have the same variable name
//winner2 and have extern before it too, to connect the occurences.
extern int winner2;


void main(void) {
  int ordintvar = 4;

  //Pointer variable that contains the address of an ordinary variable
  //&gives the address, * means pointers followed by identifier *identifier
  int *pointintvar = &ordintvar;
  //Now the address that pointintvar points to has the value 20, which means so does ordintvar
  *pointintvar = 20;

  int p1, p2;
  int *p3, *p4;
  //P1 now references the memory object of p2
  // p1 = p2;
  // //The address p3 has access to now changes it's value to the dereferenced value of p4
  // *p3 = *p4;

  int l = 3;
  //Pointer that points to a variable
  int* m = &l;
  //Pointer that points a pointer that points to a variable
  int** n = &m;

  //To get the value stored in l, we must do
  printf("%p\n", *n);

  //Generic pointer, meaning it can point to any data type it wants
  void* jello;
  int jollaf = 9;
  jello = &jollaf;

  /*Pointer Arithmetic

  If a pointer x is added like x++ and x+4, then we bascially increment by the byte size of the type that the
  pointer refers to. So x++ is basically x = x + sizeof(type) * 1, x+4 is x = x + sizeof(type) * 4
  */ 

  /*Pointers and arrays
  
  int* p = &a[0], for a[0], we can just simply p = a, since a refers to an address already.

  a[1] same as *(p+1); a[i] same as *(p+i).
  Under the hood, array indexing is defined as pointer arithmetic
  */


  void random() {
    extern int varriability;
    //Value is retained between subsequent calls in memory
    static int staysInMemory;
  }


  /*Functions are usually pass by valie, by you can make them pass by reference if you use pointers
  or arrays, mind you arrays get treated the same as pointers, so referencing an array is basically &a[0] 
  NOTE: ALL functions must be defined outside of other functions
  */

  /*

  Standard C file structure: 
  
  +---------------------------------------+
|  #include files & Macros              |
+---------------------------------------+
|  Global / Static Variables            |
+---------------------------------------+
|  Function Prototypes (Declarations)   |
|  - void swap(int* x, int* y);         |
+---------------------------------------+
|  int main(void) {                     |
|      // Code execution starts here    |
|      swap(&a, &b);                    |
|  }                                    |
+---------------------------------------+
|  void swap(int* x, int* y) {          |
|      // Actual logic lives here       |
|  }                                    |
+---------------------------------------+
  
  */

  int allet = 3;
  int batt = 2;

  swap(&allet, &batt);
  

  int *ip, x;



  //We simply get the address it references which is the int address
  printf("%p, %p, Do the addressess match: %s \n", &x, ip, (&x == ip) ? "true" : "false");

  ip = &x;

  //References different memory address pointing to x
  printf("%p, %p, Do the addressess match: %s \n", &x, ip, (&x == ip) ? "true" : "false");


}

void swap(int* swapx, int *swapy) {
    int temp;
    temp = *swapx;
    *swapx = *swapy;
    *swapy = temp;
  }