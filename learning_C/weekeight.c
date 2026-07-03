#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>


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

}