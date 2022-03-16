#include <stdio.h>
#include <stdlib.h>

#define MAX_N 120

typedef struct _btnode {
  char id;
  struct _btnode *left;
  struct _btnode *right;
} BTNode;

void buildTree(BTNode **node, char *preO, char *postO);
void inOrder(BTNode *cur);
void preOrder(BTNode *cur);
void postOrder(BTNode *cur);

int main() {
  char preO[MAX_N];
  char postO[MAX_N];
  scanf("%s", preO);
  scanf("%s", postO);

  BTNode *root = NULL;
  buildTree(&root, preO, postO);
  if (root == NULL)
    printf("error\n");
  preOrder(root);
  printf("\n");
  postOrder(root);
  printf("\n");

  inOrder(root);
  printf("\n");

  return 0;
}
void inOrder(BTNode *cur) {
  if (cur == NULL)
    return;

  inOrder(cur->left);
  printf("%c", cur->id);
  inOrder(cur->right);
}
void preOrder(BTNode *cur) {
  if (cur == NULL)
    return;

  printf("%c", cur->id);
  preOrder(cur->left);
  preOrder(cur->right);
}
void postOrder(BTNode *cur) {
  if (cur == NULL)
    return;

  postOrder(cur->left);
  postOrder(cur->right);
  printf("%c", cur->id);
}

// def constructFromPrePost(self, pre, post):
//         root = TreeNode(pre[self.preIndex])
//         self.preIndex += 1
//         if (root.val != post[self.posIndex]):
//             root.left = self.constructFromPrePost(pre, post)
//         if (root.val != post[self.posIndex]):
//             root.right = self.constructFromPrePost(pre, post)
//         self.posIndex += 1
//         return root
// Solution
int preIndex = 0;
int postIndex = 0;

void buildTree(BTNode **node, char *preO, char *postO) {
  // if (preO[0] == '\0' || postO[0] == '\0') {
  //   *node = NULL;
  //   return;
  // }
  BTNode *root = malloc(sizeof(BTNode));
  root->id = preO[preIndex];
  preIndex++;

  if (root->id != postO[postIndex]) {
    buildTree(&root->left, preO, postO);
  }
  if (root->id != postO[postIndex]) {
    buildTree(&root->right, preO, postO);
  }
  postIndex++;
  *node = root;
}
