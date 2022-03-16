
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

// answer
int checkDup(struct _dbllistnode *duparray[10000][2], int filledto,
             struct _dbllistnode *first, struct _dbllistnode *second) {

  for (int i = 0; i < filledto; i++) {
    if (duparray[i][0] == first && duparray[i][1] == second) {
      return 0;
    }
    if (duparray[i][0] == second && duparray[i][1] == first) {
      return 0;
    }
  }
  // printf("inside duparray: %d %d\n", first->item, second->item);

  duparray[filledto][0] = first;
  duparray[filledto][1] = second;
  return 1;
}

int numMountainPairs(CDblLinkedList CDLL) {
  struct _dbllistnode *duparray[10000][2];
  int filledto = 0;

  int pairs = 0;
  CDblListNode *cur = CDLL.head;
  CDblListNode *left;
  CDblListNode *right;

  if (CDLL.size == 0 || CDLL.size == 1) {
    return 0;
  }
  if (CDLL.size == 2) {
    return 1;
  }

  // same height
  while (1) {
    int checkRight = 0;
    int checkLeft = 0;

    if (cur->item >= cur->next->item) {
      checkRight = 1;
    }
    if (cur->item >= cur->pre->item) {
      checkLeft = 1;
    }
    // find adjacent nodes with same height
    if (cur->item == cur->next->item) {
      // if (duparray[0][0] == cur && duparray[0][1] == cur->next) {
      //   pairs++;
      //   cur = cur->next;
      //   continue;
      // }
      // printf("%d %d\n", cur->item, cur->next->item);

      if (checkDup(duparray, filledto, cur, cur->next)) {
        // printf("%d %d\n", cur->item, cur->next->item);
        filledto++;
        pairs++;
      }
    }
    if (cur->item == cur->pre->item) {
      // printf("%d %d\n", cur->item, cur->pre->item);

      if (checkDup(duparray, filledto, cur, cur->pre)) {
        // printf("%d %d\n", cur->item, cur->pre->item);
        filledto++;
        pairs++;
      }
    }

    // find non adjacent nodes with same height
    right = cur->next->next;
    left = cur->pre->pre;
    for (int i = 0; i < CDLL.size - 3; ++i) {
      if (cur->item < left->item) {
        checkLeft = 0;
      }
      if (cur->item < right->item) {
        checkRight = 0;
      }
      if (checkLeft && cur->item == left->item) {
        if (checkDup(duparray, filledto, cur, left)) {
          // printf("%d << %d\n", cur->item, left->item);
          filledto++;
          pairs++;
        }
      }

      left = left->pre;
      if (cur->item == right->item) {
        if (checkRight && checkDup(duparray, filledto, cur, right)) {
          // printf("%d  %d\n", cur->item, right->item);
          filledto++;
          pairs++;
          // checkRight = 0;
        }
      }
      right = right->next;
    }

    // go next node
    cur = cur->pre;
    if (cur == CDLL.head) {
      break;
    }
  }

  // printf("printing duparray:\n");
  // for (int i = 0; i < filledto; i++) {
  //   printf("%d %d\n", duparray[i][0]->item, duparray[i][1]->item);
  //   free(duparray[i][0]);
  //   free(duparray[i][1]);
  // }
  // printf("Pairs after checking same height: %d\n", pairs);

  // different height left to right
  while (1) {
    right = cur->next->next;
    left = cur->pre->pre;

    // flag to check if adj pair is found
    int leftadj = 0;
    int rightadj = 0;
    int nonadjcheck = 0;

    // check left adj node
    if (cur->item < cur->pre->item) {
      if (checkDup(duparray, filledto, cur, cur->pre)) {
        filledto++;
        pairs++;
        // printf("%d < %d\n", cur->item, cur->pre->item);
        leftadj = 1;
      }
    }
    // check right adj nodes
    if (cur->item < cur->next->item) {
      if (checkDup(duparray, filledto, cur, cur->next)) {
        filledto++;
        pairs++;
        // printf("%d < %d\n", cur->item, cur->next->item);
        rightadj = 1;
      }
    }

    for (int i = 0; i < CDLL.size - 3; ++i) {
      if (leftadj == 0) {
        if (cur->item < left->item) {
          if (checkDup(duparray, filledto, cur, left)) {
            filledto++;
            pairs++;
            // printf("%d << %d\n", cur->item, left->item);
            leftadj = 1;
          }
        }
        left = left->pre;
      }
      if (rightadj == 0) {
        if (cur->item < right->item) {
          if (checkDup(duparray, filledto, cur, right)) {
            filledto++;
            pairs++;
            // printf("%d << %d\n", cur->item, right->item);
            rightadj = 1;
          }
        }
        right = right->next;
      }
      // if (leftadj == 1 && rightadj == 1) {
      //   if (left->next == right->pre || left->next == cur->next ||
      //       right->pre == cur->pre) {
      //     printf("minus\n");
      //
      //     pairs--;
      //   };
      //   // if (left->next == cur->next) {
      //   //   printf("minus\n");
      //   //   pairs--;
      //   // }
      //   // if (right->pre == cur->pre) {
      //   //   printf("minus\n");
      //   //   pairs--;
      //   // }
      // }
    }
    // if (cur->pre == right) {
    //   printf("this: %d << %d\n", cur->item, left->item);
    //   pairs--;
    // }

    // go next node
    cur = cur->pre;
    if (cur == CDLL.head) {
      break;
    }
  }

  return pairs;
}
