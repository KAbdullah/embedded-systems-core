#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>


void main(void) {
  int ordintvar = 4;

  //Pointer variable that contains the address of an ordinary variable
  //&gives the address, * means pointers followed by identifier *identifier
  int *pointintvar = &ordintvar;


  int *ip, x;

  x = 0;

  //We simply get the address it references which is the int address
  printf("%p, %p, Do the addressess match: %s \n", &x, ip, (&x == ip) ? "true" : "false");

  ip = &x;

  //References different memory address pointing to x
  printf("%p, %p, Do the addressess match: %s \n", &x, ip, (&x == ip) ? "true" : "false");
}