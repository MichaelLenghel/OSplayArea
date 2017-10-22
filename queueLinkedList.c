/*Implementation of a queue*/

#include <stdio.h>
#include <stdlib.h>

// self-referential structure
struct listNode {
   char data; // each listNode contains a character
   struct listNode *nextPtr; // pointer to next node
};

typedef struct listNode ListNode; // synonym for struct listNode
//typedef ListNode* ListNode*; // synonym for ListNode*

// prototypes
void insert(ListNode* *sPtr, ListNode* *tail, char value);
char delete(ListNode* *sPtr, ListNode* *tail);
void printList(ListNode* currentPtr);
void menu(void);

int main(void)
{
	ListNode *sPtr = NULL;
	ListNode *tail = NULL;
	unsigned int choice; // user's choice
	char value, c;

   // loop while user does not choose 3
   while (choice != 3)
   {
   		menu();
		printf("%s", "? ");
	    scanf("%u", &choice);
        //Clear buffer for new line characters, otherwise it skips the scanf
        while((c = getchar()) != '\n' && c != EOF);
   		switch(choice)
   		{
   			case 1:
   			{
   				puts("Enter a value to insert");
   				scanf("%c", &value);

   				insert(&sPtr, &tail, value);
   				printList(sPtr);
   				break;
   			}//end case 1

   			case 2:
   			{
            if (sPtr != NULL)
            {
                value = delete(&sPtr, &tail);
                printf("%c deleted\n", value);
                printList(sPtr);

            }//end if

   				else
   				{
   					puts("List is empty");
   				}//end else

   				break;
   			}//end case 2

   			case 3:
   			{
   				puts("Program has terminated");
   				break;
   			}//end case 3

   			default:
   			{
   				puts("Invalid input detected");
   			}
   		}//end switch
   }//end while
	return(0);
}//end main

void insert(ListNode **sPtr, ListNode **tailPtr, char value)
{
    ListNode *newPtr = malloc(sizeof(ListNode));

    if (newPtr != NULL)
    {
        newPtr->data = value; // place value in node
        newPtr->nextPtr = NULL; // node does not link to another node

        //At least one element already exists in the list
        if(*sPtr != NULL)
        {
            //Let new pointer point to the head
            newPtr->nextPtr = *sPtr;
            //Let the head point to the newPtr
            *sPtr = newPtr;
        }//end inner if

        else
        {//Set both as the first element if nothing else is in the list

            //newPtr->nextPtr holds the value of the startPtr which at the start is NULL
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
            *tailPtr = newPtr;
        }
    }//end outer if

    else
    {
        puts("Failed to allocate memory");
    }//end else

}//end insert

char delete(ListNode* *sPtr, ListNode* *tailPtr)
{
  char value = (*tailPtr)->data;
  int check = 0;

  ListNode *previous2Ptr = *sPtr;
  ListNode *previousPtr = *sPtr;
  ListNode *currentPtr = (*sPtr)->nextPtr;

  //If there is only one element in the list then we dont need to do all that other stuff to assign the tail to the previous elements address
  if ((*sPtr)->nextPtr == NULL)
  {
    *tailPtr = NULL;
    *sPtr = NULL;
  }//end if

  else
  {
    //Walk through the list until you reach the last element
    while (currentPtr != NULL)
    {
        //We need 3 ptrs as currentPtr will be NULL at the end

        //previous2Ptr holds the value of the element before the element we are deleting
        previous2Ptr = previousPtr;
        //PreviousPtr holds the value of the element we are deleting
        previousPtr = currentPtr;
        //currentPtr will be NULL
        currentPtr = currentPtr->nextPtr;
    }//end while

    //Assign the first element entered at tailPtr to a tempPtr for safety
    ListNode *tempPtr = previousPtr;
    //Force the tail pointer to point to the element before it
    *tailPtr = previous2Ptr;
    previous2Ptr->nextPtr = NULL;
    free(tempPtr);
  }//end outer else

  return(value);
}//end delete

// print the list
void printList(ListNode* currentPtr)
{
   // if list is empty
   if (currentPtr == NULL) {
      puts("List is empty.-\n");
   }
   else {
      puts("The list is:");

      // while not the end of the list
      while (currentPtr != NULL) {
         printf("%c --> ", currentPtr->data);
         currentPtr = currentPtr->nextPtr;
      }

      puts("NULL\n");
   }
}

// display program instructions to user
void menu(void)
{
   puts("Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end.");
}//end menu
