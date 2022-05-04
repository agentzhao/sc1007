#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int  item;
    enum ExpType type;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);


void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int main()
{
    char infix[SIZE];

    //printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c",infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
}

void push(Stack *sPtr, char item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}


void in2PreLL(char* infix, LinkedList *inExpLL)
{
    //Write your code here
    Stack new_Stack;
    new_Stack.head=NULL;
    new_Stack.size=0;
  
    Stack Op;
    Op.head=NULL;
    Op.size=0;

    char top;

    while(*infix)
    {
        if(*infix == '(') // Open->Close
        {
            push(&new_Stack, ')');
        }
        else if(*infix == ')') // Close->Open
        {
            push(&new_Stack, '(');
        }
        else
        {
		    push(&new_Stack, *infix);
        }
        infix++;
    }
  
    char temp, tempNum[SIZE]; // Note: SIZE is 1k
    int count = 0, num = 0;
	
    while(new_Stack.size)
    {
        temp = peek(new_Stack);
        pop(&new_Stack);
		
        // If temp is an operand
        if(temp >= '0' && temp <= '9')
        {
            tempNum[count] = temp;
			// If num consist of double digits
            while(new_Stack.size) 
            {
                if(peek(new_Stack) >= '0' && peek(new_Stack) <= '9')
                {
                    count++;
                    tempNum[count] = peek(new_Stack);
                    pop(&new_Stack);
                }
                else
                    break;
            }
            if(count) // Multi
            {
                count++;
            }
            for(int k = 0; k < count/2;k++)
            {
				// Swap
                char first = tempNum[k];
                tempNum[k] = tempNum[count-k-1];
                tempNum[count-k-1] = first;
            }
            num = atoi(tempNum);
            for(int k = 0;k < count;k++)
            {
                tempNum[k] = 0;
            }
            count = 0;
            insertNode(inExpLL, num, OPERAND);
        }
		
        else if(temp == '(') // Opening bracket
        {
            push(&Op, temp);
        }
        
        else if(temp == ')') // Closing bracket
        {
            while(peek(Op) != '(')
            {
                switch(peek(Op)){
                    case '*':
                        insertNode(inExpLL, 42, OPT);
                        break;
                    case '+':
                        insertNode(inExpLL, 43, OPT);
                        break;
                    case '-':
                        insertNode(inExpLL, 45, OPT);
                        break;
                    case '/':
                        insertNode(inExpLL, 47, OPT);
                        break;
                }
                pop(&Op);
            }
            pop(&Op);
        }
        
		// Note to self double check and fix this error
        else if(temp == '+' || temp == '-')
        {
            while(1)
            {
				// If empty end it
                if(isEmptyStack(Op))
                {
                    push(&Op, temp);
                    break;
                }
				// Top precedence higher = continue
                else
                {
                    top = peek(Op);
                    if(top == '*' || top == '/')
                    {
                        pop(&Op);
                        switch(top)
                        {
                            case '*':
                            insertNode(inExpLL, 42, OPT);
                            break;
                            case '/':
                            insertNode(inExpLL, 47, OPT);
                            break;
                        }
                    }
                    else
                    {
                        push(&Op, temp);
                        break;
                    }
                }
            }
        }
		
		else if(temp == '*' || temp == '/')
        {
            push(&Op, temp);            
        }
        
    }

    while(!isEmptyStack(Op))
    {
        switch(peek(Op))
        {
            case '*':
                insertNode(inExpLL, 42, OPT);
                break;
            case '+':
                insertNode(inExpLL, 43, OPT);
                break;
            case '-':
                insertNode(inExpLL, 45, OPT);
                break;
            case '/':
                insertNode(inExpLL, 47, OPT);
                break;
        }
        pop(&Op);
    }
}
