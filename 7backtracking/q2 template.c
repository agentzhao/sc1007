#include <stdio.h>
#include <stdlib.h>

int nQueens(int **board, int N, int col);
int isSafe(int **board, int N, int row, int col);
void printSolution(int **board, int N);

int main() {
  int **board;
  int BSize;

  int i, j;

  printf("Enter the size of chessBoard:\n");
  scanf("%d", &BSize);

  board = (int **)malloc(BSize * sizeof(int *));
  for (i = 0; i < BSize; i++)
    board[i] = (int *)malloc(BSize * sizeof(int));

  for (i = 0; i < BSize; i++)
    for (j = 0; j < BSize; j++)
      board[i][j] = 0;

  if (!nQueens(board, BSize, 0))
    printf("Solution does not exist");

  return 0;
}

// print one possible soln for nQueens
int nQueens(int **board, int BSize, int col) {
  if (col == BSize) {
    printSolution(board, BSize);
    return 1;
  }

  int found;
  for (int i = 0; i < BSize; i++) {
    if (isSafe(board, BSize, i, col)) {
      // place queen
      board[i][col] = 1;
      // recur for remaining cols
      found = nQueens(board, BSize, col + 1);
      if (found)
        return 1;
      // delete queen
      board[i][col] = 0;
    }
  }

  return 0;
}

/* A utility function to check if a queen can
   be placed on board[row][col]. Note that this
   function is called when "col" queens are
   already placed in columns from 0 to col -1.
   So we need to check only left side for
   attacking queens */
int isSafe(int **board, int BSize, int row, int col) {
  int i, j;

  // Horizontal check
  for (i = 0; i < col; i++)
    if (board[row][i])
      return 0;

  // Upper left diagonal check
  for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
    if (board[i][j])
      return 0;

  // Lower left diagonal check
  for (i = row, j = col; i < BSize && j >= 0; i++, j--)
    if (board[i][j])
      return 0;

  return 1;
}

void printSolution(int **board, int BSize) {
  int i, j;
  for (i = 0; i < BSize; i++) {
    for (j = 0; j < BSize; j++) {
      if (board[i][j] == 1)
        printf(" Q ");
      else
        printf(" + ");
    }
    printf("\n");
  }
  printf("\n");
}
