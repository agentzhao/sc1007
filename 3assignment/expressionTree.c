#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200 // The number digit limitation

typedef struct _btnode {
  int item;
  struct _btnode *left;
  struct _btnode *right;
} BTNode; // You should not change the definition of BTNode

typedef struct _node {
  BTNode *item;
  struct _node *next;
} StackNode;

typedef struct _stack {
  int size;
  StackNode *head;
} Stack;

void deleteTree(BTNode **root);

void createExpTree(BTNode **root, char *prefix);
void printTree(BTNode *node);
void printTreePostfix(BTNode *node);
double computeTree(BTNode *node);

void push(Stack *sPtr, BTNode *item);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);

int main() {
  char prefix[SIZE];
  BTNode *root = NULL;

  // printf("Enter an prefix expression:\n");
  gets(prefix);

  createExpTree(&root, prefix);

  // printf("The Infix Expression:\n");
  printTree(root);
  printf("\n");
  // printf("The Postfix (Reverse Polish) Expression:\n");
  printTreePostfix(root);
  printf("\n");
  // printf("Answer ");
  printf("%.2f\n", computeTree(root));
  deleteTree(&root);
  return 0;
}

void push(Stack *sPtr, BTNode *item) {
  StackNode *newNode;
  newNode = malloc(sizeof(StackNode));
  newNode->item = item;
  newNode->next = sPtr->head;
  sPtr->head = newNode;
  sPtr->size++;
}

int pop(Stack *sPtr) {
  if (sPtr == NULL || sPtr->head == NULL) {
    return 0;
  } else {
    StackNode *temp = sPtr->head;
    sPtr->head = sPtr->head->next;
    free(temp);
    sPtr->size--;
    return 1;
  }
}

BTNode *peek(Stack s) { return s.head->item; }

int isEmptyStack(Stack s) {
  if (s.size == 0)
    return 1;
  else
    return 0;
}

void deleteTree(BTNode **root) {
  BTNode *temp;
  if (*root != NULL) {
    temp = (*root)->right;
    deleteTree(&((*root)->left));
    free(*root);
    *root = NULL;
    deleteTree(&temp);
  }
}

// solution
void reverseString(char *infix) {
  // reverse infix expression
  char *infixRev = malloc(sizeof(char) * strlen(infix));
  int length = strlen(infix);
  int j = 0;
  // Traverse character by character from end to start and form a new string
  for (int i = length - 1; i >= 0; i--) {
    if (infix[i] >= '0' && infix[i] <= '9') {
      int k = 0;
      while (infix[i] >= '0' && infix[i] <= '9') {
        j++;
        i--;
        k++;
      }
      i++;
      j--;

      if (k == 1) {
        infixRev[j] = infix[i];
        j++;
      } else if (k == 2) {
        infixRev[j - 1] = infix[i];
        infixRev[j] = infix[i + 1];
        j++;
      } else if (k == 3) {
        infixRev[j - 2] = infix[i];
        infixRev[j - 1] = infix[i + 1];
        infixRev[j] = infix[i + 2];
        j++;
      } else if (k == 4) {
        infixRev[j - 3] = infix[i];
        infixRev[j - 2] = infix[i + 1];
        infixRev[j - 1] = infix[i + 2];
        infixRev[j] = infix[i + 3];
        j++;
      } else if (k == 5) {
        infixRev[j - 4] = infix[i];
        infixRev[j - 3] = infix[i + 1];
        infixRev[j - 2] = infix[i + 2];
        infixRev[j - 1] = infix[i + 3];
        infixRev[j] = infix[i + 4];
        j++;
      } else if (k == 6) {
        infixRev[j - 5] = infix[i];
        infixRev[j - 4] = infix[i + 1];
        infixRev[j - 3] = infix[i + 2];
        infixRev[j - 2] = infix[i + 3];
        infixRev[j - 1] = infix[i + 4];
        infixRev[j] = infix[i + 5];
        j++;
      } else if (k == 7) {
        infixRev[j - 6] = infix[i];
        infixRev[j - 5] = infix[i + 1];
        infixRev[j - 4] = infix[i + 2];
        infixRev[j - 3] = infix[i + 3];
        infixRev[j - 2] = infix[i + 4];
        infixRev[j - 1] = infix[i + 5];
        infixRev[j] = infix[i + 6];
        j++;
      } else if (k == 8) {
        infixRev[j - 7] = infix[i];
        infixRev[j - 6] = infix[i + 1];
        infixRev[j - 5] = infix[i + 2];
        infixRev[j - 4] = infix[i + 3];
        infixRev[j - 3] = infix[i + 4];
        infixRev[j - 2] = infix[i + 5];
        infixRev[j - 1] = infix[i + 6];
        infixRev[j] = infix[i + 7];
        j++;
      } else if (k == 9) {
        infixRev[j - 8] = infix[i];
        infixRev[j - 7] = infix[i + 1];
        infixRev[j - 6] = infix[i + 2];
        infixRev[j - 5] = infix[i + 3];
        infixRev[j - 4] = infix[i + 4];
      } else if (k == 10) {
        infixRev[j - 9] = infix[i];
        infixRev[j - 8] = infix[i + 1];
        infixRev[j - 7] = infix[i + 2];
        infixRev[j - 6] = infix[i + 3];
        infixRev[j - 5] = infix[i + 4];
        infixRev[j - 4] = infix[i + 5];
        infixRev[j - 3] = infix[i + 6];
        infixRev[j - 2] = infix[i + 7];
        infixRev[j - 1] = infix[i + 8];
        infixRev[j] = infix[i + 9];
        j++;
      }

    } else {
      // operator
      infixRev[j] = infix[i];
      j++;
    }
  }

  for (int i = 0; i < length; i++) {

    if (infixRev[i] == '(') {
      infixRev[i] = ')';
    } else if (infixRev[i] == ')') {
      infixRev[i] = '(';
    }
  }

  strcpy(infix, infixRev);
}
// +  99  *  -  88  77  +  /  66  -  55  44  33

// insert each operator into the tree as internal node and operand as leaf node
void createExpTree(BTNode **root, char *prefix) {
  Stack s;
  BTNode *newNode;

  reverseString(prefix);
  char *token;
  char *delim = " ";
  char *temp = malloc(sizeof(char) * strlen(prefix));
  strcpy(temp, prefix);
  token = strtok(temp, delim);
  while (token != NULL) {
    // operator
    if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
        strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
      newNode = malloc(sizeof(BTNode));
      newNode->item = token[0];
      newNode->left = peek(s);
      pop(&s);
      newNode->right = peek(s);
      pop(&s);

      push(&s, newNode);
    } else { // operand
      newNode = malloc(sizeof(BTNode));
      newNode->item = atoi(token);
      newNode->right = NULL;
      newNode->left = NULL;

      push(&s, newNode);
    }
    token = strtok(NULL, delim);
  }
  free(temp);

  *root = peek(s);
  pop(&s);
}

int checkOperand(BTNode item) {
  if (item.item == '+' || item.item == '-' || item.item == '*' ||
      item.item == '/') {
    if (item.left == NULL || item.right == NULL) {
      // must be an operand
      return 1;
    }
    return 0;
  }
  return 1;
}

// in order traversal
void printTree(BTNode *node) {
  if (node == NULL)
    return;
  printTree(node->left);
  if (node->item == '+' || node->item == '-' || node->item == '*' ||
      node->item == '/') {
    if (checkOperand(*node)) {
      printf("%d ", node->item);
    } else {
      printf("%c ", node->item);
    }
  } else {
    printf("%d ", node->item);
  }
  printTree(node->right);
}

// post order traversal
void printTreePostfix(BTNode *node) {
  if (node == NULL)
    return;
  printTreePostfix(node->left);
  printTreePostfix(node->right);
  if (node->item == '+' || node->item == '-' || node->item == '*' ||
      node->item == '/') {
    if (checkOperand(*node)) {
      printf("%d ", node->item);
    } else {
      printf("%c ", node->item);
    }

  } else {
    printf("%d ", node->item);
  }
}

double computeTree(BTNode *node) {
  if (node == NULL)
    return 0;
  double left = computeTree(node->left);
  double right = computeTree(node->right);
  if (checkOperand(*node)) {
    return node->item;
  }

  if (node->item == '+') {
    return left + right;
  } else if (node->item == '-') {
    return left - right;
  } else if (node->item == '*') {
    return left * right;
  } else if (node->item == '/') {
    return left / right;
  } else {
    return node->item;
  }
}
