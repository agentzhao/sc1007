#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *next;
} ListNode;

void printList(ListNode *curr) {
  printf("%s", "Linked List: ");
  while (curr != NULL) {
    printf("%d ", curr->data);
    curr = curr->next;
  }
  printf("\n");
}

void insert(ListNode **head, int data) {
  ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
  newNode->data = data;
  newNode->next = *head;
  *head = newNode;
}

int main() {
  ListNode *head = NULL, *temp;
  int i = 0;

  while (scanf("%d", &i) != EOF) { // EOF in linux is Ctrl+D
    if (head == NULL) {
      head = malloc(sizeof(ListNode));
      temp = head;
    } else {
      temp->next = (ListNode *)malloc(sizeof(ListNode));
      temp = temp->next;
    }
    temp->data = i;
  }
  temp->next = NULL;

  printList(head);
}
