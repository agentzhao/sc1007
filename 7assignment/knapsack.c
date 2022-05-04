#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) { return a > b ? a : b; }

int bottom_up_dp(int n, int *s, int *v, int C) {
  // n: number of items
  // s: size of each item
  // v: value of each item
  // C: capacity
  // M[i,j] = max [M[i-1,j], M[i-1,j-s[i]] + v[i]]
  int i, j;

  // building the matrix
  int **dp = (int **)malloc(sizeof(int *) * (n + 1));
  for (i = 0; i <= n; i++) {
    dp[i] = (int *)malloc(sizeof(int) * (C + 1));
  }

  // Initialize with 0
  for (i = 0; i <= n; i++) {
    for (j = 0; j <= C; j++) {
      dp[i][j] = 0;
    }
  }

  // Bottom up DP, filling the matrix. i = items, j = capacity
  // skip 0 because *s and *v starts from index 1
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= C; j++) {
      // if item is included
      if (j >= s[i]) {
        // either include or not
        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - s[i]] + v[i]);
      } else {
        // take the previous value
        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  return dp[n][C];
}

int main() {
  int n, C;
  int function;
  int *s;
  int *v;
  int i, j;
  printf("Enter the number of items n:\n");
  scanf("%d", &n);
  printf("Enter the capacity C:\n");
  scanf("%d", &C);
  s = (int *)malloc(sizeof(int) * (n + 1));
  v = (int *)malloc(sizeof(int) * (n + 1));

  printf("Enter the sizes of items (as a list, separate by spacing:\n");
  for (i = 1; i <= n; i++)
    scanf("%d", &s[i]);

  printf("Enter the values of items (as a list, separate by spacing:\n");
  for (i = 1; i <= n; i++)
    scanf("%d", &v[i]);

  printf("The maximum value is: %d \n", bottom_up_dp(n, s, v, C));
}
