#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct node_def {
    void* data;
    //void (*p_free_node) (void *);
    struct node_def* next;
} Node;

typedef struct linkedlist_def {
    int num_nodes;  // prevents linear time checks for invalid indexes
    void (*p_free_list) (void *);
    int (*p_comp_nodes) (void *, void *);
    Node* head;
} LinkedList;

LinkedList* LinkedList_Create(void* LinkedList_Free, void* LinkedList_CompareNodes);
Node* Node_Create(void* data);
void LinkedList_InsertAtIndex(LinkedList* list, int index, void* data);
void LinkedList_InsertAtFront(LinkedList* list, void* data);    // insert at 0
void LinkedList_InsertAtEnd(LinkedList* list, void* data);      // insert at num_nodes
void LinkedList_PrintList(LinkedList* list);

/*
* These can't be done here?
* doesn't know how big data is
* can't free alloc'd memory
*/
void LinkedList_DeleteByIndex(LinkedList* list, int index);
void LinkedList_DeleteByData(LinkedList* list, void* data);

#endif  // LINKEDLIST_H