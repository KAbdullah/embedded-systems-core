#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

//Passing 2D array as a pointer, you MUST type cast it to a singular flat array
//Also, the parameter list is basically accepting a pointer, NOTE: arr size information is decayed.
void printTest(int *arr, int row, int column) {

  for (int i = 0; i < row-2; i++) {
    for (int j = 0; j < column-2; j++) {
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


int main(int argc, char *argv[]) {
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
  int (*addpt)(int, int);
  
  addpt = add;

  printf("The answer for this is: %d\n", addpt(100, 256));


  //the Seed number in srand directly affects what sequence of numbers show up
  //If srand is the same across re-runs, then the same random numbers will keep showing up
  srand(1);

  //Random numbers
  for (int i = 0; i < 2; i++) {
    
    float j = rand();
    printf("Random number: %lf\n", j);
  }

  //Command line arguments that the main() function gets called with
  printf("Number of command line arguements: %d\n", argc);
  printf("The command line arguments are: ");
  for (int i = 0; i < argc; i++) {
    printf("%s\n", argv[i]);
  }

  //Preprocessor - declaration
  #define ON 0
  //function-macro
  #define power(x) (x * x)
  //file path/name macros
  #define __FILEPATH1__ "/etc/config.conf"
  #define __FILE1__ "config.conf"

  int yellow = power(4);

  printf("%d\n", yellow);

  //Preprocessor - conditional inclusion
  // #defined() is a preprocessor operator
  #if !defined(HDR)
    #define HDR 99

  #elif defined(HDR)
    #define HDR 0

  #endif

  printf("%d\n", HDR);

  #if !defined(HDR)
    #define HDR 99

  #elif defined(HDR)
    #undef HDR
    #define HDR 0

  #endif

  printf("%d\n", HDR);

  //In C if you want to link multiple files together, NOTE: ONLY ONE file can have the MAIN function
  //You use the -c flag to compile into machine code (compiling to assembly is done before turning it into machine code) 
  //but STOP before linking, it creates .o files
  //Then you can gcc file1.o file2.0 -o (flag for renaming) final
  //Then you can run the final file like so ./final


  //STREAMS
  //streams are basically any source of input or destination for output
  //This is how you declare streams aka File pointers more accurately managed by file pointers
  FILE *f1, *f2;
  //Three streams aka file pointers that come by default, they are:
  stdin; stdout; stderr;

  //File descriptors are basically 
  // A File* wraps around a file descriptor and it only becomes in use once we fopen() or open(), we would interact with them directly in systems
  //programming, but because we have OS, we get functions like read() and write() right out of the bag.


  //Now let's get into functions for file reading and writing

  char firstChar, secondChar, thirdChar;

  //READING DATA

  /* printf("Ask me the three chars: \n");
  scanf("%c %c %c", &firstChar, &secondChar, &thirdChar);
  printf("The characters are: %c %c %c \n", firstChar, secondChar, thirdChar); */ 

  char name[50];
  printf("Enter your name: ");
  //I can swap out stdin for a FILE *pointer
  //First argument is the buffer, second is the maximum size to read and third is the file discriptor to map to
  fgets(name, sizeof(name), stdin);

  //Only takes on character, note: getchar() defaults to argument stdin if nothing is passed
  //Additionally, stdin can be replaced with FILE *pointer 
  char choice;
  choice = getc(stdin);
  printf("%c\n", choice);

  //OUTPUTTING DATA
  

}