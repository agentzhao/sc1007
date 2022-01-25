#include <stdio.h>
#include <stdlib.h>

struct _listNode {
  float item;
  struct _listNode *next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

ListNode *reverseSegment(ListNode *head, int start, int end);

int main() {
  ListNode *head = NULL, *temp;
  float f = 0.0;
  int S, E;

  scanf("%d %d", &S, &E);

  while (scanf("%f", &f)) {
    if (head == NULL) {
      head = (ListNode *)malloc(sizeof(ListNode));
      temp = head;
    } else {
      temp->next = (ListNode *)malloc(sizeof(ListNode));
      temp = temp->next;
    }
    temp->item = f;
  }
  temp->next = NULL;

  head = reverseSegment(head, S, E);
  printList(head);
  deleteList(&head);
  return 0;
}

void printList(ListNode *head) {
  while (head != NULL) {
    printf("%.2f ", head->item);
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

ListNode *reverseSegment(ListNode *head, int start, int end) {
  if (end < start) {
    return head;
  }
  ListNode *cur = head, *prev = NULL, *temp = head;
  ListNode *segHead, *segTail;

  for (int i = 0; i < end; i++) {
    temp = temp->next;
    if (temp->next == NULL) {
      return head;
    }
  }

  for (int i = 0; i < start; i++) {
    segHead = cur;
    cur = cur->next;
  }

  int i = 0;
  while (cur != NULL && i < end - start + 1) {
    temp = cur->next;
    cur->next = prev;
    prev = cur;
    cur = temp;
    if (i == 0)
      segTail = prev;
    i++;
  }

  if (start == 0) {
    head = prev;
    segTail->next = cur;
  } else {
    segHead->next = prev;
    segTail->next = cur;
  }

  return head;
}
