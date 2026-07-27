#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdint.h>

typedef struct {
  double width;
  double height;
} Shape;


double getArea(Shape shape);

Shape make_dimension(double w, double h);

double get_this_area(Shape *shape);


int main() {

  //Learning fputc here

 FILE *fp;

 if((fp = fopen("weekeight1.txt", "w")) == NULL) {
  return 1;
 }
 
 char ans = 'A';

 int whatHappened = fputc(ans, fp);

 if (whatHappened == EOF) {
  printf("Hey man something went wrong, try again!");
  fclose(fp);
  return 1;
 }

 //Then you have putc and putchar

 //This is a macro, and macros are replaced during preprocessing with their underlying definion
 //This means any variable argument placed can have consequences, like fp[i++]
 //Writes to the same open file, and no overwriting since it was opened once
  putc(ans, fp);

  //Writes character straight to the terminal stdout
  putchar(ans);

  fclose(fp);


  FILE *fpt = fopen("weekeight1.txt", "r");

  char theWord[1000];
  
  //this instead of gets, because it got depracated, reason being it didn't accept buffer.
  //When you go beyond the buffer size you cause overflow in the stack
  fgets(theWord, sizeof(theWord), fpt);


  printf("\nThe text in the file was: %s\n", theWord);

  fclose(fpt);

  //Adds to the stream without automatically appending a new line, unlike puts
  fputs("Hello world\n", stdout);

  //Writes it directly to stdout with a new line
  char *strong = "Hello";
  puts(strong);

  //fread() and fwrite() are Block I/O, because they read data in chunks and rather then byte-by-byte
  //useful for efficient data reading and writing on large datasets; i.e. databases and multimedia processing

  int placetoStore[100] = {1,2,3,4,5, 99};

  
  FILE *readFrom = fopen("random.txt", "w+");

  if (readFrom == NULL) {
    printf("Something went wrong.\n");
    return 1;
  }

  //If fwrite doesn't return the same number as 10, then we have an error that occured
  fwrite(placetoStore, sizeof(int), 10, readFrom);

  //If fread doesn't return the same number as 10, then we have an error that occured
  int howmanyelements = fread(placetoStore, sizeof(int), 10, readFrom);

  printf("The 6th value in placetoStore is: %d \n", placetoStore[5]);

  fclose(readFrom);

  //fprintf and fcanf allow for formatted input, but instead of simply inputting or outputting in stdin and stdout
  //they can do write and read into any file, log and/or stream
  
  FILE *stream = fopen("learningfprintf.txt", "w");

  int intnumber = 6;
  float floatnumber = 4.5;
  double doublenumber = 6.66666;

  //result stores the number of characters successfully written. A number returned by fprintf
  int result = fprintf(stream, "Number is %d %0.1f %lf", intnumber, floatnumber, doublenumber);

  printf("%d\n", result);

  //Same thing for scanf as above but it puts the value in those variables, and
  //you must use &

  //The below function checks if we reached the end of that file. 1 for we reached and 0 for we didn't reach
  //Don't use alongside fread(), since it will run even when you reach eof(), use after fread().
  //feof();
  //If feof returns false and there's an error, it means the error wasn't caused by end of file, so you must handle it
  //like so: ferror(FILE *stream); this checks whether an error has occured

  //ferror() returns 0 for no error and 1 for error

  //EOF is defined as -1
  if (result == EOF) {
    if (feof(stream)) {
      printf("Reached the end of the file.\n");
    } else if (ferror(stream)) {
      perror("A write error occured\n");
    }
    //Every letter, number, space and decimal is one character
  } else if (result == 24) {
    printf("Writing was a success\n");
  } else {
    printf("Something else that I don't know went wrong.\n");
  }

  //open() is used for low level I/O operation compared to fopen()
  //found in the <fcntl.h> file
  //This opened a file called file.txt with read only, has third arguement for persmission
  //This || represents bitwise OR and this | represents logical OR
  //Added permission for reading, writing and executing for user, group and other using <sys/stat.h> library
  mode_t file_mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
  open("crazyfile.txt", O_RDONLY | O_CREAT, file_mode);

  //Manipulating the file offset or position using lseek and fseek
  //lseek() returns offset location when successful or -1 otherwise
  //fseek() returns 0 if successful or -1 if error

  //low-level so only accepts file descriptor which is mapped to that specific stream
  //found out using fileno(), offset the pointer at the start (SEEK_SET) and offset by 10
  lseek(fileno(stream), 10, SEEK_SET);

  //high-level so give stream name, then start at the end of the file and offset by 25
  fseek(stream, 25, SEEK_END);

  fclose(stream);

  //If you want random numbers for security and cryptography, you can use the numbers from the file /dev/urandom
  //this file makes these random numbers using noise from various hardware sources

  FILE *ranNum = fopen("/dev/urandom", "r");

  int c = getc(ranNum);

  printf("The random number is: %d\n", c);

  fclose(ranNum);

  //------------------------------------------------------------------------------------------------------------------
  //Memory and Struct

  //The reason we have pointers become a data type, is due to referencing like pt+1, so the pointer knows how mcuh to jump
  //and when you want to read, it knows how many bytes to read at once. 

  //malloc()

  int *intPointer;

  intPointer = (int *) malloc(sizeof(int));

  double *doublePointer;

  doublePointer = (double *) malloc(sizeof(double));

  *intPointer = 5;
  
  *doublePointer = 6.66;

  printf("The malloc pointers hold the values: %d and %lf\n", *intPointer, *doublePointer);

  //free()
  free(intPointer);
  free(doublePointer);

  //Removed the memory that they referenced
  printf("The malloc pointers NOW hold the values: %d and %lf\n", *intPointer, *doublePointer);

  
  //Implementing fucntions using malloc

  int *allocateMemoryArray(int num) {
    int *ptr = (int *) malloc(num * sizeof(int));

    return ptr;
  }

  int *array;
  int num;

  printf("How many grades would you like to input: ");

  scanf("%d", &num);

  array = allocateMemoryArray(num);

  printf("Please enter %d grades: ", num);

  for (int i = 0; i < num; i++) {
    scanf("%d", array+i);
  }

  printf("The grades you inputted are:" );
  for (int i = 0; i < num; i++) {
    printf("%d ", *(array+i));
  }
  printf("\n");

  free(array);

  //calloc()
  //Initializes the allocated memory to zero unlike malloc()
  int *callocPt = calloc(10, sizeof(int)); // allocate 10 elements the size of int, so 40 bytes total

  //realloc()
  //this function also automatically copies your data in your previous memory to the new one, if it moved, otherwise
  //it just grows the memory size and the callocPt sill points to the same place, because the memory didn't move, just grew
  int *temp = realloc(callocPt, 20 * sizeof(int));

  if (temp == NULL) {
    printf("Reallocation failed.");
    free(callocPt);
    return 1;
  }

  callocPt = temp;

  //Only need to free callocPt, because they point to the same address
  //Also free just tells the OS this memory can now be used again, even though the original data is there,
  //you must treat it as corrupted data, because it can be overwritten with the next malloc(), calloc(), etc..
  free(callocPt);

  //always initlize pointers to NULL if you don't plan to initlize them rn because then ptr==NULL works
  //but not inializing it to NULL, leaves it to point to grabage memory which fails the ptr==NULL check

  int *exPtr = NULL;

  if (exPtr == NULL) {
    printf("Failed predictably\n");
  }

  

  //Structures
  //typedef tells the compiler that the variable Student isn't just a variable it's a typedef, meaning a type defintion
  //a.k.a it's a type
  typedef struct {
    char firstname[30];
    char lastname[30];
    int age;
    double grade;

  } Student, cpyStudent;

  Student aleena = {"Aleena", "Khatib", 22, 7.56};

  Student *studPtr = &aleena;

  printf("The pointer values are: %s %s %d %.2lf\n", studPtr->firstname, studPtr->lastname, studPtr->age, studPtr->grade);

  cpyStudent cpyAleena = aleena;

  printf("The copied pointer values are: %s %s %d %.2lf\n", cpyAleena.firstname, cpyAleena.lastname, cpyAleena.age, cpyAleena.grade);  

  //This is an NOT an ANONYMOUS struct (Sunila is wrong, it's variable type), basically it can't be reused again, but because I wan't to use it just once, 
  //I give it the variable Triangle
  //So, of this struct type, only Triangle ever exists in memory. I can also create a pointer triP of the variable type, and it can point to
  //only Triangle, because it's the only one of it's type, if I did a variable Square, then it could point to that too.
  struct {
    double height;
    double base;
  } Triangle, Square, *triP = &Triangle;

  Shape square;
  square.height = 4;
  square.width = 4;

  //Pass by value to functions
  //struct defined at the top of the file, and function at the bottom  

  double shapeAnswer = getArea(square);

  printf("The area of the Square is: %.2lf\n", shapeAnswer);

  //Return struct from function

  Shape rectangle = make_dimension(4, 8);

  printf("My new rectangle dimensions are: %.2lf, %.2lf\n", rectangle.width, rectangle.height);

  //Pass by reference
  //This is feasable for large strcutures with a lot of information, also when you pass pointers you get attribute values as such
  //(*pt).width or much better is pt -> width

  double shapeArea = get_this_area(&square);
  printf("The area of the Square using pass by reference is: %.2lf\n", shapeArea);

  //Array of structures
  typedef struct {
    char firstName[30];
    char lastName[30];
    int age;
    char hobby[100];
  } Person;

  //This is not a 2D array so the 3 here doesn't signify the number of columns, which would otherwise be a program crash
  //it's just an array of structures
  Person pplArray[3] = {
    {"Abdullah", "Khatib", 39, "Play basketball"},
    {"Aleena", "Khatib", 40, "Loves to game"},
    {"Bolo", "Dolo", 101, "Loves to breathe"}
  };

  //Nested structures

  typedef struct {
    int whatever;
    float bruh;
  } Inner;

  typedef struct {
    Inner random1;
    Inner random2;
  } Outer;

  //Unions
  //For unions, only one attribute can be active at a time, and setting one attribute re-writes all the other ones
  //making them inactive, because they share the memory of the biggest type set in the union

  //Enum
  //Basically aliases for number 0... to however many you define
  //You can explicity set them like TYPE_FLOAT = 3, but the next enumerator will be 4, +1 of the previous
  //Enums get 4 bytes
  typedef enum {TYPE_INT, TYPE_FLOAT, TYPE_CHAR} DataType; 

  typedef struct {
    //Reason we have this over here is, because when we create the struct Variant, we want the space reserved for the union to know,
    //what type of data is stored in the variable data, if it's int, float or char. When we create a Variable variable, we will explicitly
    //set type
    DataType type;
    //Names union variable
    union {
      int i_val;
      float f_val;
      char c_val;
      
    } data;
  } Variant;

  //This basically overalys the struct data underneath the attribute value of union type
  typedef union memory {
    uint32_t value;
    struct {
      uint8_t firstByte;
      uint8_t secondByte;
      uint8_t thirdByte;
      uint8_t fourthByte;
    } data;
  } Memory;

  //Little-Endian: Chooses to place the lower part of the memory first
  //Big-Endian: does the opposite

  //The volatile keyword is very important in embedded, because it help avoid the compiler optimization trap
  //baiscally tells the compiler this address changes its value often, so keep checking it, instead of optimizing, and
  //not checking this address often
  volatile keepChanging;
  
}

double getArea(Shape shape) {
  return shape.height * shape.width;
}

Shape make_dimension(double w, double h) {
  Shape returned;

  //If you do this: returned = {w, h}, make sure you know the order defined in the actual structure, because that's
  //how the mapping happens

  returned.width = w;
  returned.height = h;

  return returned;
}

double get_this_area(Shape *shape) {
  return shape->width * shape->height;
}