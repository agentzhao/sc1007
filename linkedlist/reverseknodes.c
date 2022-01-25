#include <stdio.h>
#include <stdlib.h>

struct _listNode {
  int item;
  struct _listNode *next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void reverseKNodes(ListNode **head, int K);

int main() {
  ListNode *head = NULL, *temp;
  int i = 0;
  int K = 0;

  scanf("%d", &K);

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

  reverseKNodes(&head, K);
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

void reverseKNodes(ListNode **head, int K) {
  if (K == 0 || K == 1)
    return;
  if (*head == NULL)
    return;

  ListNode *cur = *head, *prev;
  ListNode *temp = *head, *segHead, *segTail, *tempCheck, *prevTail, *test;

  int count = 0;
  while (cur != NULL && count < K) {
    temp = cur->next;
    cur->next = prev;
    prev = cur;
    cur = temp;
    count++;
  }

  if (cur != NULL)
    head->next = reverseKNodes(&cur, K);

  *head = temp;
}
