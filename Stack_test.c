#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

#define LENGTH 16

/*
 *  JQR Task 8.5
 */

/* my data to be held in each Node in the Stack */
typedef struct thing_def {
    int serial;
    char desc[LENGTH];
} Thing;

void Node_Destroy(void* node); // tells header how to free Node
void Stack_Destroy(void* stack);    // tells header how to free Stack
void Stack_Print(Stack* stack); // prints Stack
Thing* Thing_Create(int num, char str[]);
void Thing_Destroy(Thing* thing);

int main(int argc, char* argv[]) {
    printf("Playing with generic Stack implementation.\n");

    /* Create Stack */
    Stack * myStack = Stack_Create(&Stack_Destroy, &Node_Destroy);
    Stack_Print(myStack);   // should be empty right now

    // create Things
    Thing * myThing0 = Thing_Create(0, "zero");
    printf("myThing0: %d, %s\n", myThing0->serial, myThing0->desc);
    Thing * myThing1 = Thing_Create(1, "one");
    printf("myThing1: %d, %s\n", myThing1->serial, myThing1->desc);
    Thing * myThing2 = Thing_Create(2, "two");
    printf("myThing2: %d, %s\n", myThing2->serial, myThing2->desc);
    Thing * myThing3 = Thing_Create(3, "three");
    printf("myThing3: %d, %s\n", myThing3->serial, myThing3->desc);
    Thing * myThing4 = Thing_Create(4, "four");
    printf("myThing4: %d, %s\n", myThing4->serial, myThing4->desc);
    Thing * myThing5 = Thing_Create(5, "five");
    printf("myThing5: %d, %s\n", myThing5->serial, myThing5->desc);

   // push Things to Stack
    Stack_Push(myStack, myThing0);
    Stack_Push(myStack, myThing1);
    Stack_Push(myStack, myThing2);
    Stack_Push(myStack, myThing3);
    Stack_Push(myStack, myThing4);
    Stack_Push(myStack, myThing5);

    // print to verify pushing
    Stack_Print(myStack);

    // pop 1 Node
    Node* popped = (Node*)Stack_Pop(myStack);
    Thing* burnt = (Thing*)popped->data;
    printf("Stack_Pop: %d, %s\n", burnt->serial, burnt->desc);

    // print to verify single pop
    Stack_Print(myStack);

    Node* multi = (Node*)Stack_Pop_Multi(myStack, 7);
    Thing* dos = (Thing*)multi->data;
    printf("Stack_Pop_Multi(2): %d, %s\n", dos->serial, dos->desc);

    // print to verify multi-pop (2)
    Stack_Print(myStack);

    Node* done = (Node*)Stack_Pop_All(myStack);
    Thing* zilch = (Thing*)done->data;
    printf("Stack_Pop_All: %d, %s\n", zilch->serial, zilch->desc);

    // print to verify list is emptied
    Stack_Print(myStack);

    Node* last = (Node*)Stack_Pop(myStack);

    /* Destroy Stack */

    //free stack
    //myStack->p_Destroy_stack((void*) myStack);

    //free(myStack);
    //free(myThing0);

    return 0;
}   // end main

Thing* Thing_Create(int num, char str[])
{
    Thing* newThing = malloc(sizeof(Thing));

    if (newThing == NULL) {
        printf("Error allocating memory to Thing.\n");
    } else {
        newThing->serial = num;
        strncpy(newThing->desc, str, LENGTH-1);
    }

    return newThing;

}   // end Thing_Create

void Thing_Destroy(Thing* thing)
{
    free(thing);
}   // end Thing_Destroy

void Node_Destroy(void* node)
{
    Node* deleteMe = (Node*)node;
    Thing_Destroy((Thing*)deleteMe->data);
    free(deleteMe);
}   // end Node_Destroy

void Stack_Destroy(void* stack)
{
    //
}   // end Stack_Destroy

void Stack_Print(Stack* stack)
{
    printf("Stack_Print: ");

    if (Stack_isEmpty(stack)) {
        printf("empty stack!\n");
    } else {
        Node * temp_Node = stack->head; //

        while (temp_Node != NULL) {
            Thing * temp_Thing = (Thing*)temp_Node->data;
            printf("%d  ", temp_Thing->serial); //
            temp_Node = temp_Node->next;
        }
        printf("\n");
    }
    
}   // end Stack_Print
