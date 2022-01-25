#include <stdio.h>
#include <stdlib.h>

struct _listNode {
  int item;
  struct _listNode *next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void triPartition(ListNode **head, int pivot);

int main() {
  ListNode *head = NULL, *temp;
  int i = 0;
  int pivot = 0;

  scanf("%d", &pivot);

  while (scanf("%d", &i)) {
    if (head == NULL) {
      head = (ListNode *)malloc(sizeof(ListNode));
      temp = head;
    } else {
      temp->next = (ListNode *)malloc(sizeof(ListNode));
      temp = temp->next;
    }
    temp->item = i;
  }
  temp->next = NULL;

  triPartition(&head, pivot);
  printList(head);
  deleteList(&head);

  return 0;
}

void printList(ListNode *head) {
  while (head != NULL) {
    printf("%d ", head->item);
    head = head->next;
  }
  printf("\n");
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

void triPartition(ListNode **head, int pivot) {
  if (*head == NULL)
    return;

  ListNode *newHead = (ListNode *)malloc(sizeof(ListNode));
  ListNode *temp = newHead;
  ListNode *test;

  ListNode *cur = *head;
  while (cur != NULL) {
    if (cur->item < pivot) {
      newHead->item = cur->item;
      newHead->next = (ListNode *)malloc(sizeof(ListNode));
      newHead = newHead->next;
    }
    cur = cur->next;
  }

  cur = *head;
  while (cur != NULL) {
    if (cur->item == pivot) {
      newHead->item = cur->item;
      newHead->next = (ListNode *)malloc(sizeof(ListNode));
      newHead = newHead->next;
    }
    cur = cur->next;
  }

  cur = *head;
  while (cur != NULL) {
    if (cur->item > pivot) {
      newHead->item = cur->item;
      test = newHead;
      newHead->next = (ListNode *)malloc(sizeof(ListNode));
      newHead = newHead->next;
    }
    cur = cur->next;
  }

  test->next = NULL;
  *head = temp;
}
