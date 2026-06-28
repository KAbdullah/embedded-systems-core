#include <stdio.h>
#include <stdbool.h>

//If I don't define this here, then when code parses top to bottom, it implicityly assumes that isNonDescending
//return int because we don't define return type there, but when it reads the function definion, it sees it returns
//bool type, so it gives an error. Therefore a heads up here is good to avoid that problem.
bool isNonDescending(int *arr, int m);


int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  // getchar();
  int matrix[n][m];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      //When inputs have space between them, they are counted as seperate inputs so 1 2 3 4, is four different numbers
      //These numbers are placed in the buffer, and scanf then grabs them one by one or how many fromat specifiers there are
      //so if you have "%d %d %d", then it grabs from the buffer three by three
      //Note: If you put in 4 inputs and scanf only accepts one for now, then the remainder three get added to the buffer and
      //get grabbed the next time scanf gets called. 
      scanf("%d", &matrix[i][j]);
    }
  }

  for (int k = 0; k < n; k++) {
    if (isNonDescending(matrix[k], m)) {
      printf("%d\n", k + 1);
    }
  }
  
}


bool isNonDescending(int *arr, int m) {
  for (int i = 1; i < m; i++) {
    if (arr[i - 1] <= arr[i]) {
      continue;
    }
    return false;
  }
  return true;
}