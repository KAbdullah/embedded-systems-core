#include <stdio.h>

void applyPotion();


int main() {
  //You will get segmentation fault if you intialize these variables as pointers and don't point them to any memory
  //because upon intialization, they point to garbage memory or restricted memory which causes segmentation faults
  int age, strength, weight, wisdom;

  printf("Enter age: ");
  scanf("%d", &age);
  printf("\n");

  printf("Enter strength level: ");
  scanf("%d", &strength);
  printf("\n");

  printf("Enter weight: ");
  scanf("%d", &weight);
  printf("\n");

  printf("Enter wisdom level: ");
  scanf("%d", &wisdom);
  printf("\n");

  applyPotion(&age, &strength, &weight, &wisdom);

  printf("After drinking the Reversal Potion: \n");
  printf("Age: %d\n", age);
  printf("Strength:  %d\n", strength);
  printf("Weight:  %d\n", weight);
  printf("Wisdom:  %d\n", wisdom);


}



void applyPotion(int *age, int *strength, int *weight, int *wisdom) {

  if (*age <= 25) {
    *strength = *strength * 2;
  } else if (25 < *age && *age <= 40) {
    *weight = *weight * 0.90;
  } else {
    *wisdom = *wisdom + 5;
  }

}