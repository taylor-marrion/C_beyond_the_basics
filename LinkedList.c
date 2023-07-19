#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

Node* Node_Create(void* data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    //newNode->p_free_node = &Node_Free;
    newNode->next = NULL;

    return newNode;
}   // end Node_Create

LinkedList* LinkedList_Create(void* LinkedList_Free, void* LinkedList_CompareNodes) {
    LinkedList* ll = malloc(sizeof(LinkedList));
    ll->num_nodes = 0;
    ll->p_free_list = LinkedList_Free;
    ll->p_comp_nodes = LinkedList_CompareNodes;
    ll->head = NULL;
    return ll;
}   // end LinkedList_Create

void LinkedList_InsertAtIndex(LinkedList* list, int index, void* data) {
    if (index > list->num_nodes || index < 0) {
        printf("Error: Invalid index!\n");
    } else if (index == 0) {
        Node* newNode = Node_Create(data);
        newNode->next = list->head;
        list->head = newNode;
        list->num_nodes++;
    } else {
        Node* newNode = Node_Create(data);
        Node* temp = list->head;
        for (int i = 1; i<index; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        list->num_nodes++;
    }
}   // end LinkedList_InsertAtIndex

void LinkedList_InsertAtFront(LinkedList* list, void* data) {
    LinkedList_InsertAtIndex(list, 0, data);
}   // end LinkedList_InsertAtFront

void LinkedList_InsertAtEnd(LinkedList* list, void* data) {
    LinkedList_InsertAtIndex(list, list->num_nodes, data);
}   // end LinkedList_InsertAtEnd

/*
 * This only works because main uses ints as data.
 * Need to re-write in main to handle malloc'd data.
 * Can I use Node->p_free_node to free nodes in list here?
 */
void LinkedList_DeleteByIndex(LinkedList* list, int index) {
    if (list->head == NULL) {
        printf("Empty list!\n");
        return;
    }

    if (index == 0) {
        Node * deleteMe = list->head;
        list->head = list->head->next;
        //free(deleteMe->data); // this library doesn't know how big data is
        free(deleteMe);
        deleteMe = NULL;
        list->num_nodes--;
    } else {
        Node * temp = list->head;

        for (int i = 0; i < index-1; i++) {
            temp = temp->next;
        }

        Node * deleteMe = temp->next;
        temp->next = temp->next->next;
        free(deleteMe);
        deleteMe = NULL;
        list->num_nodes--;
    }
}   // end LinkedList_DeleteByIndex

/*
 * Cannot implement with void pointer for data
 */
void LinkedList_DeleteByData(LinkedList* list, void* data) {
    // 
}   // end LinkedList_DeleteByData
