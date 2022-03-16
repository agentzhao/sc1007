#include <stdio.h>
#include <stdlib.h>

typedef struct btNode {
  int item;
  struct btNode *left;
  struct btNode *right;
} btNode;

void insertNode(btNode *root, int item) {
  btNode *newNode = (btNode *)malloc(sizeof(btNode));
  btNode *newnode = malloc(sizeof(btNode));

  newNode->item = item;
  newNode->left = NULL;
  newNode->right = NULL;

  if (root == NULL) {
    root = newNode;
    return;
  }

  while (root != NULL) {
    if (item < root->item) {
      if (root->left == NULL)
        break;
      else
        root = root->left;
    } else if (root->item < item) {
      if (root->right == NULL)
        break;
      else
        root = root->right;
    } else {
      return;
    }
  }

  if (item < root->item) {
    root->left = newNode;
  } else {
    root->right = newNode;
  }
}

void deleteTree(btNode *root) {
  if (root != NULL) {
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
    root = NULL;
  }
}

int oneChild(btNode *root) {
  if (root == NULL)
    return 0;

  int left = oneChild(root->left);
  int right = oneChild(root->right);

  if (root->left != NULL && root->right == NULL)
    left += 1;
  else if (root->left == NULL && root->right != NULL)
    right += 1;

  return left + right;
}

void invertBST(btNode *root) {
  btNode *temp;
  if (root != NULL) {
    invertBST(root->left);
    invertBST(root->right);
    temp = root->left;
    root->left = root->right;
    root->right = temp;
  }
}
