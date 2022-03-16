#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode {
  int item;
  struct _listnode *next;
} ListNode;

int moveMaxToFront(ListNode **ptrHead);

void printList(ListNode *cur);
ListNode *findNode(ListNode *cur, int index);
int insertNode(ListNode **ptrHead, int index, int item);
void deleteList(ListNode **ptrHead);

int main() {
  ListNode *head = NULL;
  int size = 0;
  int item;
  int index;

  printf("Enter a list of numbers, terminated by any non-digit character: \n");
  while (scanf("%d", &item))
    if (insertNode(&head, size, item))
      size++;
  scanf("%*s");

  printf("Before moveMaxToFront() is called:\n");
  printList(head);

  index = moveMaxToFront(&head);

  printf("After moveMaxToFront() was called:\n");
  printf("The original index of the node with the largest value: %d.\n", index);
  printList(head);

  deleteList(&head);
  return 0;
}

void printList(ListNode *cur) {
  printf("Current List: ");
  while (cur != NULL) {
    printf("%d ", cur->item);
    cur = cur->next;
  }
  printf("\n");
}

ListNode *findNode(ListNode *cur, int index) {
  if (cur == NULL || index < 0)
    return NULL;
  while (index > 0) {
    cur = cur->next;
    if (cur == NULL)
      return NULL;
    index--;
  }
  return cur;
}

int insertNode(ListNode **ptrHead, int index, int item) {
  ListNode *pre, *newNode;
  // If empty list or inserting first node, update head pointer
  if (index == 0) {
    newNode = malloc(sizeof(ListNode));
    newNode->item = item;
    newNode->next = *ptrHead;
    *ptrHead = newNode;
    return 1;
  }
  // Find the nodes before and at the target position
  // Create a new node and reconnect the links
  else if ((pre = findNode(*ptrHead, index - 1)) != NULL) {
    newNode = malloc(sizeof(ListNode));
    newNode->item = item;
    newNode->next = pre->next;
    pre->next = newNode;
    return 1;
  }
  return 0;
}

void deleteList(ListNode **ptrHead) {
  ListNode *cur = *ptrHead;
  ListNode *temp;
  while (cur != NULL) {
    temp = cur->next;
    free(cur);
    cur = temp;
  }
  *ptrHead = NULL;
}

int moveMaxToFront(ListNode **ptrHead) {
  int index = 0;
  ListNode *cur = *ptrHead;
  cur = cur->next;
  ListNode *prev = *ptrHead;
  ListNode *maxNode;
  if (cur->item > prev->item) {
    maxNode = cur;
    index = 1;
  } else {
    maxNode = prev;
  }

  while (1) {
    index++;
    if (cur->item > maxNode->item) {
      maxNode = cur;
    }

    if (cur->next == NULL)
      break;
    else {
      cur = cur->next;
      prev = prev->next;
    }
  }
  // delete maxNode
  prev->next = maxNode->next;
  insertNode(ptrHead, 0, maxNode->item);
  free(maxNode);
  return index;
}
