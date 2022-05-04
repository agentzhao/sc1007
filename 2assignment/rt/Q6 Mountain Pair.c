#include <stdio.h>
#include <stdlib.h>

typedef struct _dbllistnode
{
    int  item;
	struct _dbllistnode *next;
	struct _dbllistnode *pre;
} CDblListNode;

typedef struct _dbllinkedlist{
   int size;
   CDblListNode *head;
} CDblLinkedList;

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value);
void deleteList(CDblLinkedList *ptrCDLL);
void printList(CDblLinkedList CDLL);

int numMountainPairs(CDblLinkedList CDLL);

int main()
{
    CDblLinkedList himalayas;
    himalayas.head = NULL;
    himalayas.size = 0;

    int item;
    int i,cases;
    int numP;
    scanf("%d",&cases);
    for(i=0; i<cases; i++)
    {
        while(scanf("%d",&item))
            insertNode_AtFront(&himalayas, item);
        scanf("%*s");

        numP = numMountainPairs(himalayas);
        printList(himalayas);
        printf("%d Pairs.\n",numP);

        deleteList(&himalayas);
    }
    return 0;
}

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value){
      //create a new node
      CDblListNode* newNode;
      newNode = (CDblListNode *) malloc(sizeof(CDblListNode));
      newNode->item = value;

      if(ptrCDLL->size==0) //first node
      {
          newNode->next = newNode;
          newNode->pre = newNode;
          ptrCDLL->head = newNode;
      }
      else{
        newNode->next = ptrCDLL->head;
        newNode->pre = ptrCDLL->head->pre;

        newNode->pre->next = newNode; //update last node next link;
        ptrCDLL->head->pre = newNode;

        ptrCDLL->head = newNode;
      }
      ptrCDLL->size++;
}

void printList(CDblLinkedList CDLL){

    if(CDLL.head==NULL) return;

    CDblListNode* temp = CDLL.head;
    printf("Current List: ");

    while (temp->next != CDLL.head){
        printf("%d ", temp->item);
        temp = temp->next;

    }
    printf("%d\n",temp->item);
}

void deleteList(CDblLinkedList *ptrCDLL){
    if(ptrCDLL->head==NULL) return;
    CDblListNode *cur = ptrCDLL->head;
    CDblListNode *temp;

    while (cur->next!= ptrCDLL->head) {
        temp=cur->next;
        free(cur);
        cur=temp;
    }

    free(cur);
    ptrCDLL->head =NULL;
    ptrCDLL->size =0;

}



int numMountainPairs(CDblLinkedList CDLL)
{
// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail


// Write your code here

    int link_Size = CDLL.size;

	// If link size 0 or 1, return and do nothing
    if(link_Size == 0 || link_Size == 1)
    {
        return 0;
    }

 	// If link size 2 return one pair
    else if(link_Size == 2)
    {
        return 1;
    }   

    int pair = 0;
	
    CDblListNode *static_Head = CDLL.head;
    CDblListNode *static_Tail = static_Head->pre;
    CDblListNode *mountain_A = CDLL.head;
    CDblListNode *mountain_B;

    CDblListNode *mountain_B_Left;
    CDblListNode *mountain_B_Right;
	
    int found = 0, min = 0;
    pair += link_Size;

    for(int i = 0;i < link_Size-2;i++)
    {
        // Check current node
        if(i == 0)
        {
			
        }
		
        else
        {
			// Advance next item
            mountain_A = mountain_A->next;
        }
		
        mountain_B = mountain_A->next;
        for(int k = 0;k < link_Size-3; k++)
        {
            found = 0;
            mountain_B = mountain_B->next;
            
			// If mountain B = static head break
			if(mountain_B == static_Head)
            {
                break;
            }
            
			mountain_B_Left = mountain_B_Right = mountain_B;

            // mountain_A with lower height
            if(mountain_A->item > mountain_B->item)
            {
                min = mountain_B->item;
            }
            else
            {
                min = mountain_A->item;
            }
            // Search in anti-clockwise
            while(1)
            {
				// If pair found
                if(mountain_B_Left->pre == mountain_A)
                {
                    found = 1;
                    pair += 1;
                    break;
                }
                else if(mountain_B_Left->pre->item > min)
                {
                    break;
                }
                else
                {
                    mountain_B_Left = mountain_B_Left->pre;
                }
            }
			
            // Search in clockwise
            while(!found)
            {
                if(mountain_B_Right->next == mountain_A)
                {
                    pair += 1;
                    break;
                }
                else if(mountain_B_Right->next->item > min)
                {
                    break;
                }
                else
                {
                    mountain_B_Right = mountain_B_Right->next;
                }
            }
        }

    }
	
    return pair;
}