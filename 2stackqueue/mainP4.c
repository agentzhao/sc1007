#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000 // The limit of expression length

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

void in2Pre(char *, char *);

int main() {
  char infix[SIZE];
  char prefix[SIZE];

  printf("Enter an infix expression:\n");
  scanf("%[^\n]%*c", infix);

  in2Pre(infix, prefix);
  printf("The prefix expression is \n");
  printf("%s\n", prefix);

  return 0;
}

void push(Stack *sPtr, char item) {
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
  if (s.size == 0)
    return 1;
  else
    return 0;
}

int precedence(char op) {
  if (op == '*' || op == '/')
    return 1;
  else
    return 0;
}

void in2Pre(char *infix, char *prefix) {
  int length = strlen(infix);
  int j = 0;
  Stack s;

  for (int i = length - 1; i != -1; --i) {
    char temp = infix[i];
    switch (temp) {
    case ')':
      push(&s, temp);
      break;
    case '(':
      while (!isEmptyStack(s) && peek(s) != ')') {
        prefix[j] = peek(s);
        j++;
        pop(&s);
      }
      pop(&s); // pop the '('
      break;
    case '+':
    case '-':
    case '*':
    case '/':
      while (!isEmptyStack(s) && peek(s) != ')' &&
             precedence(peek(s) > precedence(temp))) {
        prefix[j] = peek(s);
        j++;
        pop(&s);
      }
      push(&s, temp);
      break;
    default:
      prefix[j] = temp;
      j++;
    }
  }

  // why does this not work
  // while (!isEmptyStack(s)) {
  //   prefix[j] = peek(s);
  //   j++;
  //   pop(&s);
  // }
  prefix[j] = peek(s);
  j++;

  prefix[j] = '\0';
}
