#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef union address {
  __uint32_t address;
  struct {
    __uint8_t offset;
    __uint8_t pageNumber;
    __uint16_t rightmost;
  } page;
} Address;


int main(int argc, char *argv[]) {

  //Read the file addresses here
  if (argc < 2) {
    fprintf(stderr, "Please enter provide an address file. \n");
    return 1;
  }

  FILE *fp = fopen(argv[1], "r");

  if (fp == NULL) {
    fprintf(stderr, "Came across an error opening the file. Please try again.\n");
    return 1;
  }

  int logicalAddress;


  while (fscanf(fp, "%d", &logicalAddress) == 1) {

    //Turn the address into binary format
    Address logicalAddressBinary;
    
    logicalAddressBinary.address = logicalAddress;

    //Mask the bits here so we only care about the first 16 vinary values
    //No need to do this, since the addresses result and the highest 16 bits to be zero, but I'll do it for practice;

    //0xF represents the binary equivalent of 1111
    //We take 16 0's and shift them to the highest 16 bits, and clear those bits
    logicalAddressBinary.page.rightmost = logicalAddressBinary.page.rightmost & ~(0xFFFF << 16);

    FILE *secondary = fopen("BACKING_STORE.bin", "r");

    if (secondary == NULL) {
      fprintf(stderr, "Couldn't access secondary memory.");
      return 1;
    }

    int pageNumber = logicalAddressBinary.page.pageNumber;

    printf("The page number is: %d\n", pageNumber);

    int offset = logicalAddressBinary.page.offset;

    fseek(secondary, (long)pageNumber*256, SEEK_SET);

    signed char physicalAddress[256];

    fread(&physicalAddress, sizeof(signed char), 256, secondary);

    int final_address = (pageNumber * 256) + offset;

    printf("The physical address is: %d\n", (int)physicalAddress[final_address]);

  }
  
}