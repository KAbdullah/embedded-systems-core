#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

long int andOp = 0b1011 & 0b1001;

float longArrayVal[] = {2.33, 5.33, 6.99};

//Will disappear after pre-processing is done
#define N_COL 200

#define N_ROW 100
//Note VLAs (varaible length arrays) are only allowed inside fucntions, meaning
//if it's not a direct number of define placeholder name inside [], then it's a VLA.
long int TwoDArray[N_COL][N_ROW] = {{2,3}, {4,5}, {9,11}};

void main(void) {
  printf("%ld\n", andOp);
  printf("%f\n", longArrayVal[0]);
  printf("%ld\n", TwoDArray[0][0]);
}