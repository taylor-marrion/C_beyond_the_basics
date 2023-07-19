#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

/*
 *  JQR Task 8.5
 */

Node* Node_Create(void* data, void* Node_Destroy) {
    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error allocating memory for Node.\n");
    } else {
        newNode->data = data;
        newNode->p_destroy_node = Node_Destroy;
        newNode->next = NULL;
    }
    
    return newNode;
}   // end Node_Create

Stack* Stack_Create(void* Stack_Destroy, void* Node_Destroy)
{
    Stack* stack = malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Error allocating memory for Node.\n");
    } else {
        stack->p_destroy_stack = Stack_Destroy;
        stack->p_destroy_node = Node_Destroy;
        stack->head = NULL;
    }
    
    return stack;
}   // end Stack_Create

Bool Stack_isEmpty(Stack* stack)
{
    if (stack->head == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}   // end Stack_isEmpty

void Stack_Push(Stack* stack, void* data)  // adds data (stored in Node) to "top" of Stack
{
    Node* newNode = Node_Create(data, stack->p_destroy_node);
    newNode->next = stack->head;    // points to "top" of stack
    stack->head = newNode;  // head now points to newNode

    return;
}   //end Stack_Push

void* Stack_Pop(Stack* stack)   // removes and returns Node from "top" of Stack
{
    Node * popped = stack->head;
    if (popped == NULL) {
        printf("The stack is empty, there's nothing to pop.\n");
    } else {
        //
        stack->head = stack->head->next;
        //free(popped);
    }

    return popped;
}   //end Stack_Pop

void* Stack_Pop_Multi(Stack* stack, int n)  // removes n Nodes from Stack
{
    // TODO: safely handle n larger than number of Nodes
    // try using Stack_isEmpty ???
    Node* popped = stack->head;
    //for (int i = 0; i < n && popped != NULL; i++) {
    while (Stack_isEmpty(stack)) {
        // TODO: fix memory leak, destroy Nodes other than returned
        popped = (Node*)Stack_Pop(stack);
    }

    return popped;
}   //end Stack_Pop_Multi

void* Stack_Pop_All(Stack* stack)   // removes all Nodes from Stack
{
    Node* popped = stack->head;
    while (popped->next != NULL) {
        // TODO: fix memory leaks, destroy all Nodes
        popped = (Node*)Stack_Pop(stack);
    }

    return popped;
}   //end Stack_Pop_All

/*void Stack_Destroy(Stack* stack)   // destroys Stack
{
    //
}   //end Stack_Destroy*/
