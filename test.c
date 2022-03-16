#include <stdio.h>
#include <stdlib.h>

typedef struct stackNode {
  int item;
  struct stackNode *next;
} stackNode;

typedef struct stack {
  int size;
  stackNode *head;
} Stack;

void push(Stack *sPtr, int item) {
  stackNode *newNode = (stackNode *)malloc(sizeof(stackNode));
  newNode->item = item;

  newNode->next = sPtr->head;
  sPtr->head = newNode;
  sPtr->size++;
}

int isEmptyStack(Stack *sPtr) { return sPtr->size == 0; }

stackNode *peek(Stack *sPtr) { return sPtr->head; }

int pop(Stack *sPtr) {
  if (isEmptyStack(sPtr))
    return 0;
  else {
    stackNode *removed = peek(sPtr);
    sPtr->head = removed->next;
    sPtr->size--;
    free(removed);
    return 1;
  }
}
