#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int sum134(int n) {
  // returns number of ways to express n
  if (n < 0) {
    return -1;
  }

  if (n == 0) {
    return 1;
  }

  int total = 0;
  int temp;

  temp = sum134(n - 1);
  if (temp != -1)
    total += temp;

  temp = sum134(n - 3);
  if (temp != -1)
    total += temp;

  temp = sum134(n - 4);
  if (temp != -1)
    total += temp;

  return total;
}

int sum_dp(int n) {
  int dp[n];

  dp[0] = dp[1] = dp[2] = 1;
  dp[3] = 2;

  for (int i = 4; i <= n; i++) {
    dp[i] = dp[i - 1] + dp[i - 3] + dp[i - 4];
  }

  return dp[n];
}

int main() {
  int n;
  int function;
  int i;
  printf("Expressing n as a sum of 1, 3 and 4\n");
  printf("Enter the value of n:\n");
  scanf("%d", &n);

  // initialize dp array

  printf("The number of ways to express %d is: %d \n", n, sum134(n));
  printf("Using dynamic programming:\n");
  printf("The number of ways to express %d is: %d \n", n, sum_dp(n));
}
