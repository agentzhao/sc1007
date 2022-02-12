
#include <stdio.h>
#include <stdlib.h>

typedef struct _dbllistnode {
  int item;
  struct _dbllistnode *next;
  struct _dbllistnode *pre;
} CDblListNode;

typedef struct _dbllinkedlist {
  int size;
  CDblListNode *head;
} CDblLinkedList;

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value);
void deleteList(CDblLinkedList *ptrCDLL);
void printList(CDblLinkedList CDLL);

int numMountainPairs(CDblLinkedList COLL);

int main() {
  CDblLinkedList himalayas;
  himalayas.head = NULL;
  himalayas.size = 0;

  int item;
  int i, cases;
  int num;
  int pairs;
  scanf("%d", &cases);
  for (i = 0; i < cases; i++) {
    while (scanf("%d", &item))
      insertNode_AtFront(&himalayas, item);
    scanf("%*s");

    pairs = numMountainPairs(himalayas);
    printList(himalayas);
    printf("%d Pairs.\n", pairs);

    deleteList(&himalayas);
  }

  return 0;
}

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value) {
  // create a new node
  CDblListNode *newNode;
  newNode = (CDblListNode *)malloc(sizeof(CDblListNode));

  newNode->item = value;

  // first node
  if (ptrCDLL->size == 0) {
    newNode->next = newNode;
    newNode->pre = newNode;
    ptrCDLL->head = newNode;
  } else {
    newNode->next = ptrCDLL->head;
    newNode->pre = ptrCDLL->head->pre;

    newNode->pre->next = newNode; // update last node's next link
    ptrCDLL->head->pre = newNode;

    ptrCDLL->head = newNode;
  }

  ptrCDLL->size++;
}

void printList(CDblLinkedList CDLL) {
  if (CDLL.head == NULL)
    return;

  CDblListNode *temp = CDLL.head;
  printf("Current List: ");

  while (temp->next != CDLL.head) {
    printf("%d ", temp->item);
    temp = temp->next;
  }
  printf("%d\n", temp->item);
}

void deleteList(CDblLinkedList *ptrCDLL) {
  if (ptrCDLL->head == NULL)
    return;
  CDblListNode *cur = ptrCDLL->head;
  CDblListNode *temp;

  while (cur->next != ptrCDLL->head) {
    temp = cur->next;
    free(cur);

    cur = temp;
  }

  free(cur);
  ptrCDLL->head = NULL;
  ptrCDLL->size = 0;
}

int numMountainPairs(CDblLinkedList CDLL) {
  int pairs = 0;
  CDblListNode *cur = CDLL.head;
  CDblListNode *temp;
  CDblListNode *temp2;

  if (cur->next == CDLL.head) {
    return 0;
  }
  if (cur->next->next == CDLL.head) {
    return 1;
  }

  return pairs;
}
