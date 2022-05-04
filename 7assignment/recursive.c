// Input = 5
// Output = 7
// f(n) = f(n - 1) + 2 * f(n-2) - 3 * f(n-3)
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int bottom_up_dp(int n) {
  int *dp = (int *)malloc(sizeof(int) * n + 1);
  dp[0] = 0;
  dp[1] = 1;
  dp[2] = 2;

  for (int i = 3; i <= n; i++) {
    dp[i] = dp[i - 1] + 2 * dp[i - 2] - 3 * dp[i - 3];
  }

  return dp[n];
}

int *dp;

int top_down_dp(int n) {
  dp[0] = 0;
  dp[1] = 1;
  dp[2] = 2;

  if (dp[n] > 0) {
    return dp[n];
  }

  if (dp[n - 1] == -1) {
    dp[n - 1] = top_down_dp(n - 1);
  }
  if (dp[n - 2] == -1) {
    dp[n - 2] = top_down_dp(n - 2);
  }
  if (dp[n - 3] == -1) {
    dp[n - 3] = top_down_dp(n - 3);
  }

  dp[n] = dp[n - 1] + 2 * dp[n - 2] - 3 * dp[n - 3];
  return dp[n];
}

int main() {
  int n;
  int function;
  int i;
  printf("Enter the value of n:\n");
  scanf("%d", &n);

  // initialize dp array
  dp = malloc(sizeof(int) * n + 1);
  for (int i = 0; i <= n; i++) {
    dp[i] = -1;
  }

  printf("The value of F(%d) is: %d \n", n, top_down_dp(n));
}
