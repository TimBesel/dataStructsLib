#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "linked-list.h"

llist_t *createLList(){
    llist_t *llist = (llist_t *)malloc(sizeof(llist_t));
    llist->head = NULL;
    llist->size = 0;
    llist->DataSize = sizeof(value_type_t);
    return llist;
}

bool isEmptyLList(llist_t *llist){
    return ((llist->head == NULL) && (llist->size == 0));
}

node_t *createNodeLList(size_t dataSize){
    node_t *newElement = (node_t *)malloc(sizeof(node_t));
    if(!newElement)
        return NULL;
    
    newElement->data = (value_type_t *)malloc(dataSize);
    if(!newElement->data){
        free(newElement);
        return NULL;
    }
    
    return newElement;
}

node_t *insertLList(llist_t *llist, uint8_t index, value_type_t value){

    int8_t destinationIndex = (int8_t) (llist->size - index);
    if(isEmptyLList(llist))
        return insertEndLList(llist, value);
    if(destinationIndex <= 0)
         return insertHeadLList(llist, value);

    node_t *newElement = createNodeLList(llist->DataSize);
    if(newElement == NULL)
        return NULL;

    *(newElement->data) = value;
    __wraped_insertLList(llist->head, newElement, destinationIndex);
    llist->size++;

    return newElement;
}

node_t *insertPtrLList(llist_t *llist, uint8_t index, value_type_t *value){

    int8_t destinationIndex = (int8_t) (llist->size - index);
    if(isEmptyLList(llist))
        return insertPtrEndLList(llist, value);
    if(destinationIndex <= 0)
         return insertPtrHeadLList(llist, value);

    node_t *newElement = createNodeLList(llist->DataSize);
    if(newElement == NULL)
        return NULL;

    newElement->data = value;
    __wraped_insertLList(llist->head, newElement, destinationIndex);
    llist->size++;

    return newElement;
}

void __wraped_insertLList(node_t *head, node_t *newElement, int8_t destinationIndex){
    node_t *currentElement = head;
    for(uint8_t i = 0; i < destinationIndex - 1; i++){
        currentElement = currentElement->nextPrt;
    }
    newElement->nextPrt = currentElement->nextPrt;
    currentElement->nextPrt = newElement;
}

node_t *insertHeadLList(llist_t *llist, value_type_t value){
    
    node_t *newElement = createNodeLList(llist->DataSize);
    if(newElement == NULL)
        return NULL;

    newElement->nextPrt = llist->head;
    *(newElement->data) = value;
    llist->head = newElement;
    llist->size++;

    return newElement;
}

node_t *insertPtrHeadLList(llist_t *llist, value_type_t *value){
    
    node_t *newElement = createNodeLList(llist->DataSize);
    if(newElement == NULL)
        return NULL;

    newElement->nextPrt = llist->head;
    newElement->data = value;
    llist->head = newElement;
    llist->size++;

    return newElement;
}

node_t *insertEndLList(llist_t *llist, value_type_t value){
    node_t *newElement = createNodeLList(llist->DataSize);
    if(newElement == NULL)
        return NULL;

    if(isEmptyLList(llist))
        return insertHeadLList(llist, value);

    *(newElement->data) = value;
    __warped_insertEndLList(llist->head, newElement);
    llist->size++;
    
    return newElement;
}

node_t *insertPtrEndLList(llist_t *llist, value_type_t *value){
    node_t *newElement = createNodeLList(llist->DataSize);
    if(newElement == NULL)
        return NULL;

    if(isEmptyLList(llist))
        return insertPtrHeadLList(llist, value);
    
    newElement->data = value;
    __warped_insertEndLList(llist->head, newElement);
    llist->size++;

    return newElement;
}

void __warped_insertEndLList(node_t *head, node_t *newElement){
    node_t *currentElement = head;
    while(currentElement->nextPrt != NULL)
        currentElement = currentElement->nextPrt;

    newElement->nextPrt = currentElement->nextPrt;
    currentElement->nextPrt = newElement;
}

node_t *getNodeByIndex(llist_t *llist, uint8_t index){
    int8_t destinationIndex = (int8_t)(llist->size - index);

    if(isEmptyLList(llist))
        return NULL;
    if(destinationIndex < 0)
        return llist->head;

    node_t *currentElement = llist->head;
    for(uint8_t i = 0; i < destinationIndex - 1; i++){
        currentElement = currentElement->nextPrt;
    }

    return currentElement;
}

node_t *getNodeByValue(llist_t *llist, uint8_t value){

    node_t *currentElement = llist->head;
    while(currentElement != NULL){
        if(*(currentElement->data) == value)
            return currentElement;
        currentElement = currentElement->nextPrt;
    }
    return NULL;
}

node_t *getNodeByPtrValue(llist_t *llist, uint8_t *value){

    node_t *currentElement = llist->head;
    while(currentElement != NULL){
        if(currentElement->data == value)
            return currentElement;
        currentElement = currentElement->nextPrt;
    }
    return NULL;
}

node_t *deleteLList(llist_t *llist){

    node_t *temp;
    node_t *currentElement = llist->head;

    while(currentElement != NULL){

        if(currentElement->data != NULL)
            free(currentElement->data);
        
        temp = currentElement->nextPrt;
        free(currentElement);
        currentElement = temp;
    }
    free(llist);

    return NULL;
}

node_t *__get_Prev_Node(llist_t *llist, node_t *node){

    node_t *currentNode = llist->head;
    if(currentNode == node)
        return node;

    while(currentNode != NULL){
        if(currentNode->nextPrt == node)
            return currentNode;
        currentNode = currentNode->nextPrt;
    }

    return NULL;
}

node_t * __free_node(node_t *node){
    if(node->data != NULL)
        free(node->data);
    if(node != NULL)
        free(node);
    return NULL;
}

node_t *deleteNode(llist_t *llist, node_t *node){

    if(node == NULL)
        return NULL;
    
    if(isEmptyLList(llist))
        return NULL;

    if(node == llist->head){
        llist->size--;
        llist->head = node->nextPrt;
        return __free_node(node);
    }

    node_t *prevElement = __get_Prev_Node(llist, node);
    if(prevElement == NULL)
        return node;

    if(prevElement != node)
        prevElement->nextPrt = node->nextPrt;

    llist->size--;
    return __free_node(node);
}

node_t *deleteIndexNode(llist_t *llist, uint8_t index){
    if(llist->head == NULL)
        return NULL;

    if(isEmptyLList(llist))
        return NULL;
        
    node_t *node = getNodeByIndex(llist, index);
    return deleteNode(llist, node);
}

node_t *popHeadLList(llist_t *llist){
    if(llist->head == NULL)
        return NULL;

    if(isEmptyLList(llist))
        return NULL;

    return deleteNode(llist, llist->head);
}

node_t *popLList(llist_t *llist){
    if(llist->head == NULL)
        return NULL;

    if(isEmptyLList(llist))
        return NULL;
    
    return deleteIndexNode(llist, 0);
}

value_type_t getValueByNode(node_t *node){
    if(node == NULL)
        return (value_type_t)INFINITY;
    return *(node->data);
}

value_type_t *getPtrValueByNode(node_t *node){
    if(node == NULL)
        return NULL;
    return node->data;
}

value_type_t getValueByIndex(llist_t *llist, uint8_t index){
    node_t *node = getNodeByIndex(llist, index);
    return getValueByNode(node);
}

value_type_t *getPtrValueByIndex(llist_t *llist, uint8_t index){
    node_t *node = getNodeByIndex(llist, index);
    return getPtrValueByNode(node);
}

void printLList(llist_t *llist, uint8_t elementCount){

    node_t *currentElement = llist->head;
    const char linker[] = "-->";
    
    printf("\n");
    while(currentElement != NULL){
        if(currentElement != llist->head)
            printf(" %s ", linker);

        for(int i = 0; i < elementCount; i++){
            if(i != 0)
                printf(" ");
            printf("%d", *(currentElement->data + i));
        }
        currentElement = currentElement->nextPrt;
    }
}