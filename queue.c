#include <stdio.h>
#include <stdlib.h>

typedef struct queueNode {
  int item;
  struct queueNode *next;
} queueNode;

typedef struct Queue {
  int size;
  struct queueNode *head;
  struct queueNode *tail;
} Queue;

queueNode *getFront(Queue *qPtr) { return qPtr->head; }
int isEmptyQueue(Queue q) { return q.size; }

void enqueue(Queue *qPtr, int item) {
  queueNode *newNode = (queueNode *)malloc(sizeof(queueNode));
  newNode->item = item;
  newNode->next = NULL;

  if (isEmptyQueue(*qPtr)) {
    qPtr->head = newNode;
  } else {
    qPtr->tail->next = newNode;
  }

  qPtr->tail = newNode;
  qPtr->size++;
}

int dequeue(Queue *qPtr) {
  if (isEmptyQueue(*qPtr)) {
    return 0;
  }

  queueNode *removed = qPtr->head;
  qPtr->head = qPtr->head->next;
  qPtr->size--;

  if (qPtr->head == NULL) {
    qPtr->tail = NULL;
  }

  free(removed);
  return 1;
}
