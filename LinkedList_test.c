#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

//void Node_Free(Node* node);
//void LinkedList_Free(LinkedList* list);
void LinkedList_Free(void* list);   // doesn't need to be void, only used in main so can be casted as specific struct type
int LinkedList_CompareNodes(void* n1, void* n2);
void LinkedList_PrintList(LinkedList* list);

int main(int argc, char* argv[]) {
    printf("Playing with generic Linked List implementation.\n");
    
    /*int num1 = 10;
    Node* myNode = Node_Create((int*)&num1);

    LinkedList* numbers = LinkedList_Create();
    numbers->head = myNode;

    printf("%d\n", *(int*)myNode->data);
    printf("%d\n", *(int*)numbers->head->data);

    char str[] = ("This is generic.\n");
    Node* myNode2 = Node_Create((char*)&str);

    LinkedList* strings = LinkedList_Create();
    strings->head = myNode2;
    printf("%s\n", (char*)myNode2->data);
    printf("%s\n", (char*)strings->head->data);

    num1 = 20;
    Node* myNode3 = Node_Create((int*)&num1);
    numbers->head->next = myNode3;

    LinkedList_PrintList(numbers);*/

    LinkedList* myList = LinkedList_Create(&LinkedList_Free, &LinkedList_CompareNodes);

    LinkedList_PrintList(myList);   // should be empty right now

    /*int a = 1;
    Node* myNode = Node_Create((int*)&a);
    myList->head = myNode;
    myList->num_nodes++;

    int b = 2;
    Node* myNode2 = Node_Create((int*)&b);
    myList->head->next = myNode2;
    myList->num_nodes++;

    int c = 4;
    Node* myNode3 = Node_Create((int*)&c);
    myList->head->next->next = myNode3;
    myList->num_nodes++;

    int d = 8;
    Node* myNode4 = Node_Create((int*)&d);
    myList->head->next->next->next = myNode4;
    myList->num_nodes++;

    int e = 16;
    LinkedList_InsertAtIndex(myList, 0, (int*) &e);

    int f = 32;
    LinkedList_InsertAtFront(myList, (int*) &f);

    int g = 64;
    LinkedList_InsertAtEnd(myList, (int*) &g);*/

    int a = 1;
    int * ap = &a;

    // doing it this way to test LinkedList_Free
    int b = 2;
    int * b_ptr = (int*)malloc(sizeof(int));
    memcpy(b_ptr, &b, sizeof(int));

    int c = 4;
    int * cp = &c;
    int d = 8;
    int * dp = &d;
    int e = 16;
    int * ep = &e;
    int f = 32;
    int * fp = &f;
    int g = 64;
    int * gp = &g;

    LinkedList_InsertAtEnd(myList, ap);
    LinkedList_InsertAtEnd(myList, b_ptr);
    LinkedList_InsertAtEnd(myList, (int*) &c);
    LinkedList_InsertAtEnd(myList, (int*) &d);
    LinkedList_InsertAtEnd(myList, ep);
    LinkedList_InsertAtEnd(myList, (int*) &f);
    LinkedList_InsertAtEnd(myList, gp);

    LinkedList_PrintList(myList);
    printf("numNodes: %d\n", myList->num_nodes);

    LinkedList_CompareNodes(myList->head, myList->head->next);
    LinkedList_CompareNodes(myList->head->next, myList->head->next);
    LinkedList_CompareNodes(myList->head->next->next, myList->head->next);

    LinkedList_DeleteByIndex(myList, 1);
    LinkedList_PrintList(myList);
    printf("numNodes: %d\n", myList->num_nodes);

    LinkedList_DeleteByIndex(myList, 0);
    LinkedList_PrintList(myList);
    printf("numNodes: %d\n", myList->num_nodes);

    LinkedList_DeleteByIndex(myList, 0);
    LinkedList_PrintList(myList);
    printf("numNodes: %d\n", myList->num_nodes);

    //free list
    myList->p_free_list((void*) myList);

    // print to verify list is emptied
    LinkedList_PrintList(myList);

    return 0;
}   // end main

/*
 * discard individual Node
 */
/*
void Node_Free(Node* node) {
    free(node->data);
    node->data = NULL;
    free(node);
    node = NULL;
}   // end Node_Free
*/

/*
 * This only works because I'm using ints above.
 * If I used malloc to allocate space for structs, this would cause memory leaks
 */
void LinkedList_Free(void* list) {

    LinkedList * p_temp = ((LinkedList *)list);

    while (p_temp->head != NULL) {
        // loop through list
        // node temp = head
        // head = head->next
        // Node_Free(temp) -or- temp->p_free_node
        LinkedList_DeleteByIndex(p_temp, 0);
    }

    free(list);
    list = NULL;
}   // end LinkedList_Free

int LinkedList_CompareNodes(void* n1, void* n2) {
    Node * node1 = (Node*) n1;
    Node * node2 = (Node*) n2;
    if (*(int*)node1->data < *(int*)node2->data) {
        printf("%d is less than %d\n", *(int*)node1->data, *(int*)node2->data);
        return -1;
    } else if (*(int*)node1->data > *(int*)node2->data) {
        printf("%d is greater than %d\n", *(int*)node1->data, *(int*)node2->data);
        return 1;
    }
    printf("%d is equal to %d\n", *(int*)node1->data, *(int*)node2->data);
    return 0;
}   // end LinkedList_CompareNodes

void LinkedList_PrintList(LinkedList* list) {
    if (list->head == NULL) {   // valgrind: "Invalid read of size 8"
        printf("Empty list!\n");
        return;
    }

    Node* temp = list->head;
    while (temp != NULL) {
        printf("%d   ", *(int*)temp->data);
        temp = temp->next;
    }
    printf("\n");
}   // end LinkedList_PrintList
