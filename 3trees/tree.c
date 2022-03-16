#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode {
  int data;
  struct _btnode *left;
  struct _btnode *right;
} BTNode;

BTNode *insertNode(BTNode *root, int data) {
  if (root == NULL) {
    root = (BTNode *)malloc(sizeof(BTNode));
    root->data = data;
    root->left = NULL;
    root->right = NULL;
  } else if (data < root->data) {
    root->left = insertNode(root->left, data);
  } else {
    root->right = insertNode(root->right, data);
  }
  return root;
}

BTNode *findNode(BTNode *root, int data) {
  if (root == NULL) {
    printf("Not found\n");
    return 0;
  } else if (data == root->data) {
    printf("Found\n");
    return root;
  } else if (data < root->data) {
    return findNode(root->left, data);
  } else {
    return findNode(root->right, data);
  }
}

// used to create copy of tree, get prefix expression
void preorder(BTNode *cur) {
  if (cur == NULL)
    return;
  printf("%c ", cur->data);
  preorder(cur->left);
  preorder(cur->right);
}

void inorder(BTNode *cur) {
  if (cur == NULL)
    return;
  inorder(cur->left);
  printf("%c ", cur->data);
  inorder(cur->right);
}

// iterative use stack
// postorder usually used to delete tree, get postfix expression
void postorder(BTNode *cur) {
  if (cur == NULL)
    return;
  postorder(cur->left);
  postorder(cur->right);
  printf("%c ", cur->data);
}

int size(BTNode *cur) {
  if (cur == NULL)
    return 0;
  return size(cur->left) + size(cur->right) + 1;
}
