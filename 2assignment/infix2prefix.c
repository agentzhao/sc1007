#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

enum ExpType { OPT, OPERAND };

typedef struct _stackNode {
  char item;
  struct _stackNode *next;
} StackNode;

typedef struct _stack {
  int size;
  StackNode *head;
} Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode {
  int item;
  enum ExpType type;
  struct _listnode *next;
} ListNode;

typedef struct _linkedlist {
  int size;
  ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item, enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList(LinkedList ll);

void in2PreLL(char *infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int main() {
  char infix[SIZE];

  // printf("Enter an infix expression: \n");
  scanf("%[^\n]%*c", infix);

  LinkedList inExpLL;
  inExpLL.head = NULL;
  inExpLL.size = 0;

  in2PreLL(infix, &inExpLL);

  printExpLL(inExpLL);

  removeAllNodes(&inExpLL);

  return 0;
}

void printExpLL(LinkedList inExpLL) {
  ListNode *temp = NULL;
  temp = inExpLL.head;
  while (temp != NULL) {
    if (temp->type == OPERAND) {
      printf(" %d ", temp->item);
    } else {
      printf(" %c ", (char)(temp->item));
    }
    temp = temp->next;
  }
  printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
  ListNode *newNode;
  newNode = malloc(sizeof(ListNode));
  if (newNode == NULL)
    exit(0);

  newNode->item = item;
  newNode->type = type;
  newNode->next = LLPtr->head;
  LLPtr->head = newNode;
  LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
  if (LLPtr == NULL || LLPtr->size == 0) {
    return 0;
  } else {
    ListNode *temp = LLPtr->head;
    LLPtr->head = LLPtr->head->next;

    free(temp);
    LLPtr->size--;
    return 1;
  }
}

int isEmptyLinkedList(LinkedList ll) {
  if (ll.size == 0) {
    return 1;
  } else {
    return 0;
  }
}

void removeAllNodes(LinkedList *LLPtr) {
  while (deleteNode(LLPtr))
    ;
}

void push(Stack *sPtr, char item) {
  // printf("push %c\n", item);
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

char peek(Stack s) { return s.head->item; }

int isEmptyStack(Stack s) {
  if (s.size == 0) {
    return 1;
  } else {
    return 0;
  }
}

// start
#include <string.h>

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

int getPriority(char C) {
  if (C == '-' || C == '+')
    return 1;
  else if (C == '*' || C == '/')
    return 2;
  else if (C == '^')
    return 3;
  return 0;
}

// convert infix expression in char *infix to a prefix expression in LinkedList
// *inExpLL

void in2PreLL(char *infix, LinkedList *inExpLL) {
  // reverse infix expression
  reverseString(infix);
  // printf("reversed: %s\n", infix);

  Stack s;
  s.head = NULL;
  s.size = 0;

  int i = 0;

  // for (int k = strlen(infix) - 1; k >= 0; k--) {
  while (infix[i] != '\0') {
    if (infix[i] >= '0' && infix[i] <= '9') {
      int operand = 0;
      char temp[10];
      int j = 0;
      while (infix[i] >= '0' && infix[i] <= '9') {
        temp[j] = infix[i];
        j++;
        i++;
      }
      // k -= strlen(temp) - 1;

      temp[j] = '\0';
      operand = atoi(temp);
      // printf("%d\n", operand);
      insertNode(inExpLL, operand, OPERAND);
      i--;
    } else if (infix[i] == '(') {
      push(&s, infix[i]);
    } else if (infix[i] == ')') {
      while (isEmptyStack(s) == 0) {
        if (peek(s) != '(') {
          // printf("poped from stack: %c\n", peek(s));
          insertNode(inExpLL, peek(s), OPT);
          pop(&s);
        } else if (peek(s) == '(') {
          pop(&s);
          break;
        }
      }
    } else if (isEmptyStack(s)) {
      push(&s, infix[i]);
    } else {
      while ((isEmptyStack(s) == 0) &&
             getPriority(peek(s)) > getPriority(infix[i])) {
        insertNode(inExpLL, peek(s), OPT);
        pop(&s);
      }
      push(&s, infix[i]);
    }
    i++;
  }

  while (!isEmptyStack(s)) {
    insertNode(inExpLL, peek(s), OPT);
    pop(&s);
  }
}
