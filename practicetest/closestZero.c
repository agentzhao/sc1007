#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

int Solve(int N, int *A) {
  int closest = A[0];

  for (int i = 0; i < N; ++i) {
    if (abs(A[i]) < abs(closest)) {
      closest = A[i];
    }
    if (abs(A[i] == abs(closest))) {
      closest = A[i] > closest ? A[i] : closest;
    }
  }

  return closest;
}

int main() {
  int N;
  scanf("%d", &N);
  int *A = (int *)malloc(N * sizeof(int));
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }
  int out_ = Solve(N, A);
  printf("%d\n", out_);
}
