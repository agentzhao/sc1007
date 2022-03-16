
#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode {
  int nodeV;
  struct _btnode *left;
  struct _btnode *right;
} BTNode;

typedef struct _queuenode {
  BTNode *node;
  struct _queuenode *next;
} QueueNode;

typedef struct _queue {
  int size;
  QueueNode *head;
  QueueNode *tail;
} Queue;

void printBTNode(BTNode *root, int space, int left);
// Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode *node);
int dequeue(Queue *qPtr);
BTNode *getFront(Queue q);
int isEmptyQueue(Queue q);

int twoNodesCost(BTNode *node, int nodeV1, int nodeV2);

int main() {
  BTNode *root = (BTNode *)malloc(sizeof(BTNode));

  Queue q;
  q.head = NULL;
  q.tail = NULL;
  q.size = 0;

  BTNode *node;
  enqueue(&q, root);

  int nodeV;
  char opL, opR;

  while (!isEmptyQueue(q)) {
    scanf("%d %c %c", &nodeV, &opL, &opR);
    node = getFront(q);
    dequeue(&q);
    node->nodeV = nodeV;

    if (opL != '@') {
      node->left = (BTNode *)malloc(sizeof(BTNode));
      enqueue(&q, node->left);
    } else
      node->left = NULL;
    if (opR != '@') {
      node->right = (BTNode *)malloc(sizeof(BTNode));
      enqueue(&q, node->right);
    } else
      node->right = NULL;
  }

  int v1, v2;
  scanf("%d %d", &v1, &v2);
  int cost = twoNodesCost(root, v1, v2);

  printBTNode(root, 0, 0);

  printf("Distance is %d\n", cost);
  return 0;
}

void enqueue(Queue *qPtr, BTNode *node) {
  QueueNode *newNode;
  newNode = malloc(sizeof(QueueNode));
  newNode->node = node;
  newNode->next = NULL;

  if (isEmptyQueue(*qPtr))
    qPtr->head = newNode;
  else
    qPtr->tail->next = newNode;

  qPtr->tail = newNode;
  qPtr->size++;
}

int dequeue(Queue *qPtr) {
  if (qPtr == NULL || qPtr->head == NULL) { // Queue is empty or NULL pointer
    return 0;
  } else {
    QueueNode *temp = qPtr->head;
    qPtr->head = qPtr->head->next;
    if (qPtr->head == NULL) // Queue is emptied
      qPtr->tail = NULL;

    free(temp);
    qPtr->size--;
    return 1;
  }
}

BTNode *getFront(Queue q) { return q.head->node; }

int isEmptyQueue(Queue q) {
  if (q.size == 0)
    return 1;
  else
    return 0;
}
void printBTNode(BTNode *root, int space, int left) {
  if (root != NULL) {

    int i;
    for (i = 0; i < space - 1; i++)
      printf("|\t");

    if (i < space) {
      if (left == 1)
        printf("|---");
      else
        printf("|___");
    }

    printf("%d\n", root->nodeV);

    space++;
    printBTNode(root->left, space, 1);
    printBTNode(root->right, space, 0);
  }
}

// // gives wrong answer
// int meetingCost = 0;
//
// int costTillMeet(BTNode *node, int meetingCost) {
//   if (node == NULL) {
//     return 0;
//   } else if (node->nodeV == meetingCost) {
//     return node->nodeV;
//   } else {
//     int left = costTillMeet(node->left, meetingCost);
//     int right = costTillMeet(node->right, meetingCost);
//
//     if (left) {
//       return left + node->nodeV;
//     } else if (right) {
//       return right + node->nodeV;
//     } else {
//       return 0;
//     }
//   }
// }
//
// int nodesCost(BTNode *node, int nodeV1, int nodeV2) {
//   if (node == NULL)
//     return 0;
//   else if (node->nodeV == nodeV1 || node->nodeV == nodeV2)
//     return node->nodeV;
//   else {
//     int leftCost = nodesCost(node->left, nodeV1, nodeV2);
//     // printf("Current leftCost: %d\n", leftCost);
//     int rightCost = nodesCost(node->right, nodeV1, nodeV2);
//     // printf("Current rightCost: %d\n", rightCost);
//
//     if (leftCost == 0 && rightCost == 0)
//       return 0;
//     else if (leftCost == 0)
//       return rightCost + node->nodeV;
//     else if (rightCost == 0)
//       return leftCost + node->nodeV;
//     else {
//       meetingCost = node->nodeV;
//       return leftCost + rightCost + node->nodeV;
//     }
//   }
// }
//
// int twoNodesCost(BTNode *node, int nodeV1, int nodeV2) {
//
//   int total = nodesCost(node, nodeV1, nodeV2);
//
//   // printf("meetingCost: %d\n", meetingCost);
//   // printf("Cost till meeting: %d\n", costTillMeet(node, meetingCost));
//
//   return total - costTillMeet(node, meetingCost) + meetingCost;
// }

// solution
BTNode *meetingCost;

// Find total cost till meeting node
int costTillMeet(BTNode *node, BTNode *meetingCost) {
  if (node == NULL) {
    return 0;
  } else if (node == meetingCost) {
    return node->nodeV;
  } else {
    int left = costTillMeet(node->left, meetingCost);
    int right = costTillMeet(node->right, meetingCost);

    if (left) {
      return left + node->nodeV;
    } else if (right) {
      return right + node->nodeV;
    } else {
      return 0;
    }
  }
}

// Find total cost to reach both nodes from root
int nodesCost(BTNode *node, int nodeV1, int nodeV2) {
  if (node == NULL)
    return 0;
  else if (node->nodeV == nodeV1 || node->nodeV == nodeV2)
    return node->nodeV;
  else {
    int leftCost = nodesCost(node->left, nodeV1, nodeV2);
    int rightCost = nodesCost(node->right, nodeV1, nodeV2);

    if (leftCost == 0 && rightCost == 0)
      return 0;
    else if (leftCost == 0)
      return rightCost + node->nodeV;
    else if (rightCost == 0)
      return leftCost + node->nodeV;
    else {
      meetingCost = node;
      return leftCost + rightCost + node->nodeV;
    }
  }
}

int twoNodesCost(BTNode *node, int nodeV1, int nodeV2) {
  if (nodeV1 == nodeV2)
    return nodeV1;
  if (node == NULL)
    return 0;
  int total = nodesCost(node, nodeV1, nodeV2);

  // printf("meetingCost: %d\n", meetingCost);
  // printf("Cost till meeting: %d\n", costTillMeet(node, meetingCost));

  return total - costTillMeet(node, meetingCost) + meetingCost->nodeV;
}
