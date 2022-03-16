#include <stdio.h>
#include <stdlib.h>

struct _listNode {
  int item;
  struct _listNode *next;
};
typedef struct _listNode ListNode;

typedef struct _linkedList {
  ListNode *head;
  int size;
} LinkedList;

void printList(LinkedList ll);
void deleteList(LinkedList *llptr);

LinkedList rearrange(LinkedList ll);

int main() {
  LinkedList ll;

  ll.head = NULL;
  ll.size = 0;
  ListNode *temp;

  int i = 0;

  while (scanf("%d", &i)) {
    if (ll.head == NULL) {
      ll.head = (ListNode *)malloc(sizeof(ListNode));
      temp = ll.head;
    } else {
      temp->next = (ListNode *)malloc(sizeof(ListNode));
      temp = temp->next;
    }
    temp->item = i;
    ll.size++;
  }
  temp->next = NULL;

  ll = rearrange(ll);

  printList(ll);
  deleteList(&ll);
  return 0;
}

void printList(LinkedList ll) {
  ListNode *temp = ll.head;

  while (temp != NULL) {
    printf("%d ", temp->item);
    temp = temp->next;
  }
  printf("\n");
}
void deleteList(LinkedList *llptr) {
  ListNode *cur = llptr->head;
  ListNode *temp;
  while (cur != NULL) {
    temp = cur->next;
    free(cur);
    cur = temp;
  }
  llptr->head = NULL;
  llptr->size = 0;
}

LinkedList rearrange(LinkedList ll) {
  if (ll.size == 0 || ll.size == 1) {
    return ll;
  }
  if (ll.size == 2) {
    int tempItem = ll.head->item;
    ll.head->item = ll.head->next->item;
    ll.head->next->item = tempItem;
    return ll;
  }

  ListNode *temp = ll.head;
  int odd = ll.size % 2;
  int array[ll.size / 2];
  int array2[ll.size / 2 + odd];
  int combined[ll.size];

  // first rearrange
  for (int i = 0; i < ll.size - odd; i++) {
    if (i < ll.size / 2) {
      array[i] = temp->item;
    } else {
      array2[i - ll.size / 2] = temp->item;
    }
    temp = temp->next;
  }
  if (odd) {
    array2[ll.size / 2] = temp->item;
  }

  for (int i = 0; i < ll.size / 2; ++i) {
    combined[i * 2 + 1] = array[i];
    combined[i * 2] = array2[i];
  }
  if (odd) {
    combined[ll.size - 1] = array2[ll.size / 2];
  }

  // second rearrange
  for (int i = 0; i < ll.size - odd; i++) {
    if (i < ll.size / 2) {
      array[i] = combined[i];
    } else {
      array2[i - ll.size / 2] = combined[i];
    }
  }
  if (odd) {
    array2[ll.size / 2] = combined[ll.size - 1];
  }

  for (int i = 0; i < ll.size / 2; ++i) {
    combined[i * 2] = array[i];
    combined[i * 2 + 1] = array2[i];
  }
  if (odd) {
    combined[ll.size - 1] = array2[ll.size / 2];
  }

  // for (int i = 0; i < ll.size - 1; ++i) {
  //   printf("%d\n", combined[i]);
  // }

  temp = ll.head;
  for (int i = 0; i < ll.size; ++i) {
    temp->item = combined[i];
    // printf("%d %d\n", combined[i], ll.head->item);

    temp = temp->next;
  }

  return ll;
}
