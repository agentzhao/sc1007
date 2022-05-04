#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *M;

int fib_recursive(int n) {
  if (n == 0) {
    return 0;
  } else if (n == 1) {
    return 1;
  } else {
    return fib_recursive(n - 1) + fib_recursive(n - 2);
  }
}

int fib[50];
int top_down_dp2(int n) {
  if (fib[n] < 0) {
    if (n == 0) {
      fib[0] = 0;
    } else if (n == 1) {
      fib[1] = 1;
    } else {
      fib[n] = fib[n - 1] + fib[n - 2];
    }
  }
  return fib[n];
}

int top_down_dp(int n) {
  M[0] = 0;
  M[1] = 1;

  if (M[n] > 0) {
    return M[n];
  }
  if (M[n - 1] == -1) {
    M[n - 1] = top_down_dp(n - 1);
  }
  if (M[n - 2] == -1) {
    M[n - 2] = top_down_dp(n - 2);
  }
  M[n] = M[n - 1] + M[n - 2];
  return M[n];
}

int bottom_up_dp(int n) {
  int *fib = (int *)malloc(sizeof(int) * (n + 1));
  fib[0] = 0;
  fib[1] = 1;
  for (int i = 2; i <= n; i++) {
    fib[i] = fib[i 
- 1] + fib[i - 2];
  }
  return fib[n];
}

void main() {
  int n;
  int function;
  int i;
  printf("Enter the value of n:\n");
  scanf("%d", &n);

  // allocate the memory array
  M = malloc(sizeof(int) * (n + 1));

  printf("Choose a function (1 for recursive, 2 for top-down DP, 3 for "
         "bottom-up DP, 0 to stop): \n");
  scanf("%d", &function);
  while (function != 0) {
    if (function == 1) {
      clock_t begin = clock();
      printf("The result of Fib(%d) is: %d \n", n, fib_recursive(n));
      clock_t end = clock();
      double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
      printf("Running time is: %f seconds \n", time_spent);
    } else if (function == 2) {
      // set all memory elements to -1
      for (i = 0; i <= n; i++)
        M[i] = -1;

      clock_t begin = clock();
      printf("The result of Fib(%d) is: %d \n", n, top_down_dp(n));
      clock_t end = clock();
      double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
      printf("Running time is: %f seconds \n", time_spent);
    } else if (function == 3) {
      // set all memory elements to -1
      for (i = 0; i <= n; i++)
        M[i] = -1;

      clock_t begin = clock();
      printf("The result of Fib(%d) is: %d \n", n, bottom_up_dp(n));
      clock_t end = clock();
      double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
      printf("Running time is: %f seconds \n", time_spent);
    }
    printf("Choose a function (1 for recursive, 2 for top-down DP, 3 for "
           "bottom-up DP, 0 to stop): \n");
    scanf("%d", &function);
  }
}
