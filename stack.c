
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000 // The limit of expression length

typedef struct _stackNode {
  int item;
  struct _stackNode *next;
} StackNode;

typedef struct _stack {
  int size;
  StackNode *head;
} Stack;

void push(Stack *sPtr, int item);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);

int main() {
  printf("Enter numbers to add to stack, enter 0 to quit: ");
  char input[SIZE];
  scanf("%s", input);
  Stack s;
  s.size = 0;
  s.head = NULL;
  while (input[0] != '0') {
    push(&s, atoi(input));
    scanf("%s", input);
  }

  return 0;
}

void push(Stack *sPtr, int item) {
  StackNode *newNode;
  newNode = (StackNode *)malloc(sizeof(StackNode));
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

int peek(Stack s) { return s.head->item; }

int isEmptyStack(Stack s) {
  if (s.size == 0)
    return 1;
  else
    return 0;
}
