#ifndef STACK_H
#define STACK_H

/*
 *  JQR Task 8.5
 */

typedef enum {
  FALSE = 0,
  TRUE = 1
} Bool;

typedef struct node_def {
    void* data;
    void (*p_destroy_node) (void *);   // pointer to function
    struct node_def* next;  // points to Node "below"
} Node;

typedef struct stack_def {
    void (*p_destroy_stack) (void *);  // pointer to function
    void (*p_destroy_node) (void *);   // pointer to function
    Node* head;     // "top" of Stack
} Stack;

Node* Node_Create(void* data, void* Node_Free);
Stack* Stack_Create(void* Stack_Free, void* Node_Free);

Bool Stack_isEmpty(Stack* stack);

void Stack_Push(Stack* stack, void* data);  // adds data (stored in Node) to "top" of Stack
void* Stack_Pop(Stack* stack);   // removes Node from "top" of Stack
void* Stack_Pop_Multi(Stack* stack, int n);  // removes n Nodes from Stack
void* Stack_Pop_All(Stack* stack);   // removes all Nodes from Stack
//void Stack_Destroy(Stack* stack);   // destroys Stack

#endif  // STACK_H