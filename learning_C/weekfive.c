#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

long int andOp = 0b1011 & 0b1001;

float longArrayVal[] = {2.33, 5.33, 6.99};

//Will disappear after pre-processing is done
#define N_COL 200

#define N_ROW 100
//Note VLAs (varaible length arrays) are only allowed inside fucntions, meaning
//if it's not a direct number of define placeholder name inside [], then it's a VLA.
long int TwoDArray[N_COL][N_ROW] = {{2,3}, {4,5}, {9,11}};

//These two things below are the same thing
char *fullString = "Hello world";
char greetings[] = "Hello world";



void main(void) {
  printf("%ld\n", andOp);
  printf("%f\n", longArrayVal[0]);
  printf("%ld\n", TwoDArray[0][0]);

  //string.h functions
  printf("%lu\n", strlen(fullString));

  char *p = strchr(fullString, 'H');

  if (*p == 'H') {
    printf("The magical character %c has been hit!\n", *p);
  } else if (p != NULL) {
    printf("%c\n", *p);
  } else {
    printf("Character not found.\n");
  }

  switch (*p) {
    case 'e': {
      printf("It's e.\n");
    }

    case 'H': {
      printf("It's H.\n");
    }

    default: {
      printf("I don't know.\n");
    }    
  }

  int xxx = 0;
  int yyy = 0;

  while (xxx > 0) {
    printf("While loop values.\n");
    xxx--;
  }

  do {
    printf("Do While loop\n");
    yyy--;
  } while (yyy > 0);

  for (int i = 5; i > 0; i--) {
    printf("Hello for loop!\n");
    continue; // Skips the break for every iteration.
    break;
  }
  
}