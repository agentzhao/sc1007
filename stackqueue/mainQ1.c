#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _listnode {
  char item;
  struct _listnode *next;
} ListNode;
typedef ListNode StackNode;
typedef ListNode QueueNode;

typedef struct _linkedlist {
  int size;
  ListNode *head;
} Stack;

typedef struct _queue {
  int size;
  ListNode *head;
  ListNode *tail;
} Queue;

// Prototypes of Interface functions for Stack structure
void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);
void deleteStack(Stack *sPtr);

// Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, char item);
int dequeue(Queue *qPtr);
char getFront(Queue q);
int isEmptyQueue(Queue q);
void deleteQueue(Queue *qPtr);

int palindrome(Queue *wordPtr);

int main() {
  char item;
  Queue word;
  word.head = NULL;
  word.tail = NULL;
  word.size = 0;

  printf("Enter a string of characters, terminated by a newline:\n");
  while (1) {
    scanf("%c", &item);
    if (item == '\n')
      break;
    enqueue(&word, item);
  }

  printf("The string is ");
  printf("%s", palindrome(&word) ? "" : "not ");
  printf("a palindrome.\n");

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

void deleteStack(Stack *sPtr) {
  while (pop(sPtr))
    ;
}

void enqueue(Queue *qPtr, char item) {
  QueueNode *newNode;
  newNode = (QueueNode *)malloc(sizeof(QueueNode));
  newNode->item = item;
  newNode->next = NULL;

  if (isEmptyQueue(*qPtr))
    qPtr->head = newNode;
  else
    qPtr->tail->next = newNode;

  qPtr->tail = newNode;
  qPtr->size++;
}

int dequeue(Queue *qPtr) {
  if (qPtr == NULL || qPtr->head == NULL) { // Queue is empty or NULL pointer
    return 0;
  } else {
    QueueNode *temp = qPtr->head;
    qPtr->head = qPtr->head->next;
    if (qPtr->head == NULL) // Queue is emptied
      qPtr->tail = NULL;

    free(temp);
    qPtr->size--;
    return 1;
  }
}

char getFront(Queue q) { return q.head->item; }

int isEmptyQueue(Queue q) {
  if (q.size == 0)
    return 1;
  else
    return 0;
}
void deleteQueue(Queue *qPtr) {
  while (dequeue(qPtr))
    ;
}

int palindrome2(Queue *wordPtr) {
  Stack s_word, s_halfword;
  s_word.head = NULL;
  s_word.size = 0;

  s_halfword.head = NULL;
  s_halfword.size = 0;

  int i, odd;

  while (!isEmptyQueue(*wordPtr)) {
    if (getFront(*wordPtr) != ' ') {
      push(&s_word, toupper(getFront(*wordPtr)));
    }
    dequeue(wordPtr);
  }

  // if the length is odd, the middle char needs to be removed
  odd = s_word.size % 2;

  for (i = s_word.size / 2; i > 0; i--) {
    push(&s_halfword, peek(s_word));
    pop(&s_word);
  }

  if (odd) {
    pop(&s_word);
  }

  while (!isEmptyStack(s_word)) {
    if (peek(s_word) != peek(s_halfword)) {
      deleteStack(&s_word);
      deleteStack(&s_halfword);
      return 0;
    }
    pop(&s_word);
    pop(&s_halfword);
  }

  return 1;
}

// a better soln
int palindrome(Queue *wordPtr) {
  Queue *temp = wordPtr;
  Queue *head = wordPtr;

  Stack s_word;
  s_word.head = NULL;
  s_word.size = 0;

  char string[20] = "";

  while (!isEmptyQueue(*temp)) {
    if (getFront(*temp) != ' ') {
      char upper = toupper(getFront(*temp));
      int len = strlen(string);
      string[len] = upper;
      string[len + 1] = '\0';
      push(&s_word, upper);
    }
    dequeue(temp);
  }

  int size = s_word.size;
  for (int j = 0; j < size - 1; j++) {
    if (string[size - s_word.size] == s_word.head->item) {
      pop(&s_word);
    } else {
      return 0;
    }
  }
  return 1;
}
