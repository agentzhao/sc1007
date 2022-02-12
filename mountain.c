

#include <stdio.h>
#include <stdlib.h>

typedef struct _dbllistnode {
  int item;
  struct _dbllistnode *next;
  struct _dbllistnode *pre;
  struct _dbllistnode *left;
  struct _dbllistnode *right;
  struct _dbllistnode *dup[5];
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
  newNode->left = NULL;
  newNode->right = NULL;

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

int isRepeated(struct _dbllistnode *first, struct _dbllistnode *second) {
  int i;
  for (i = 0; i < 5; i++) {
    if (first->dup[i] == NULL) {
      break;
    }
    if (first->dup[i] == second)
      return 1;
  }
  for (int j = 0; j < 5; i++) {
    if (second->dup[j] == NULL) {
      break;
    }
    if (second->dup[j] == first)
      return 1;
  }

  first->dup[i] = second;

  return 0;
}

int numMountainPairs(CDblLinkedList CDLL) {
  int pairs = 0;
  CDblListNode *cur = CDLL.head;
  CDblListNode *temp;
  CDblListNode *temp2;
  CDblListNode *temp3;

  if (cur->next == CDLL.head) {
    return 0;
  }
  if (cur->next->next == CDLL.head) {
    return 1;
  }

  // nodes that are adjacent and the same height
  while (1) {
    temp = cur->next;
    if (cur->next == CDLL.head) {
      break;
    }
    if (temp->item > cur->item) {
      // no point finding same height
      cur = cur->next;
      continue;
    } else {
      while (temp != cur) {
        if (cur->item < temp->item) {
          break;
        }
        if (temp->item == cur->item) {
          if (isRepeated(cur, temp)) {
            break;
          } else {
            pairs++;
          }
        }
        temp = temp->next;
      }
      cur = cur->next;
    }
  }

  // reset nodes to NULL
  cur = CDLL.head;
  while (1) {
    cur->left = NULL;
    cur->right = NULL;
    cur = cur->next;
    if (cur->next == CDLL.head) {
      break;
    }
  }

  cur = CDLL.head;

  // adjacent nodes to the right
  while (1) {
    if (cur->right != NULL) {
      cur = cur->next;
      continue;
    }
    temp = cur->next;

    if (cur->item < temp->item) {
      cur->right = temp;
      pairs++;
      cur = cur->next;
    } else {
      // non adjacent nodes to the right
      temp2 = cur->next->next;
      while (temp2 != cur->pre) {
        if (cur->item < temp2->item) {
          cur->right = temp2;
          pairs++;
          break;
        }
        temp2 = temp2->next;
      }
      cur = cur->next;
    }

    if (cur == CDLL.head) {
      break;
    }
  }

  cur = CDLL.head;

  // adjacent nodes to the left
  while (1) {
    if (cur->left != NULL) {
      cur = cur->pre;
      continue;
    }

    temp = cur->pre;

    if (cur->item < temp->item && cur->right != temp) {
      cur->left = temp;
      pairs++;
      cur = cur->pre;
    } else {
      // non adjacent nodes to the left
      temp2 = cur->pre->pre;
      while (temp2 != cur->next) {
        if (cur->item < temp2->item && cur->right != temp2) {
          cur->left = temp2;
          pairs++;
          break;
        }
        temp2 = temp2->pre;
      }
      cur = cur->pre;
    }

    if (cur == CDLL.head) {
      break;
    }
  }

  // cur = CDLL.head;
  // printf("%d: %d %d\n", cur->item, cur->left != NULL, cur->right != NULL);
  // cur = cur->next;
  //
  // while (cur != CDLL.head) {
  //   printf("%d: %d %d\n", cur->item, cur->left != NULL, cur->right != NULL);
  //   cur = cur->next;
  // }

  return pairs;
}
