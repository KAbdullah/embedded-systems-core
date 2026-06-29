#include <stdio.h>
#include <stdlib.h>

void generate_random_numbers(int n);

void read_numbers(int *arr, int n);

double calculate_mean(int *arr, int n);

double calculate_median(int *arr, int n);

int calculate_mode(int *arr, int n);

int main() {

  printf("Enter the number of random integers to generate: ");

  int rndnum;

  scanf("%d", &rndnum);

  if (rndnum <= 0) {
    printf("Please enter a valid number of random integers (1 to 100).\n");
    return 1;
  }

  generate_random_numbers(rndnum);

  int arr[rndnum];

  read_numbers(arr, rndnum);

  double mean = calculate_mean(arr, rndnum);
  printf("Mean: %.0lf\n", mean);

  double median = calculate_median(arr, rndnum);
  printf("Median: %.0lf\n", median);

  double mode = calculate_mode(arr, rndnum);
  printf("Mode: %.0lf\n", mode);

}

void generate_random_numbers(int n) {
  srand(n);
  FILE *fp = fopen("random_numbers.txt", "w");

  if (fp == NULL) {
    perror("An Error occurred. Please try again later.");
    return;
  }

  for (int i = 0; i < n; i++) {
    int rndnum = rand() % 100;
    //Any number lower than 0 indicates an error writing
    if (fprintf(fp, "%d\n", rndnum) < 0) {
      printf("An error occured. Please try again!\n");
    }
  }

  fclose(fp);
}

void read_numbers(int *arr, int n) {
  FILE *fp = fopen("random_numbers.txt", "r");

  if (fp == NULL) {
    //perror automatically writes to stderr instead of stdout.
    //All errors should be redirectd to stderr to keep the channels clean
    // 1> or > redirects stdout output and 2> redirects stderr output
    //./myprogram > data.txt   ||  ./myprogram 2> errors.txt
    perror("An Error occurred. Please try again later.");
    return;
  }

  for (int i = 0; i < n; i++) {
    char nums[20];
    //fgets remembers where it left off, because of the FILE internal pointer
    fgets(nums, sizeof(int), fp);
    arr[i] = atoi(nums);
  }

}

double calculate_mean(int *arr, int n) {
  int total = 0;

  for (int i = 0; i < n; i++) {
    total += *(arr+i);
  }

  double sum = total / n;

  return sum;

}

int comp(const void *a, const void *b) {
  return *(int *)a - *(int *)b;
}

double calculate_median(int *arr, int n) {
  int duplicate[n];

  for(int i = 0; i < n; i++) {
    duplicate[i] = *(arr+i);
  }

  //qsort accepts a function comp that must be defined just the way I did above.
  //negative number means a comes before b
  //0 means do nothing
  //positive number means b comes before a
  qsort(duplicate, n, sizeof(duplicate[0]), comp);

  int result = 0;

  for(int j = 0; j < (n / 2) + 1; j++) {
    result = duplicate[j];
  }

  return result;

}

int calculate_mode(int *arr, int n) {
  int result = 0;

}