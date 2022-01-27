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

ListNode *reverseSegment(ListNode *head, int start, int end) {
  if (end < start) {
    return head;
  }
  ListNode *cur = head, *prev = NULL, *temp = head;
  ListNode *segHead, *segTail;

  for (int i = 0; i < end; i++) {
    temp = temp->next;
    if (temp == NULL) {
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

void reverseKNodes(ListNode **head, int K) {
  if (K == 0 || K == 1)
    return;
  if (*head == NULL)
    return;

  ListNode *cur = *head, *prev = NULL, *temp = *head;

  int start = 0;
  int end = K - 1;

  while (1) {
    for (int i = 0; i < K - 1; i++) {
      // printf("%d\n", temp->item);

      temp = temp->next;
      if (temp == NULL) {
        return;
      }
      // printf("%d ", temp->item);
    }

    *head = reverseSegment(*head, start, end);
    start += K;
    end += K;
  }
}
