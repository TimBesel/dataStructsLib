#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "linked-list.h"

//##############################################
//###############   LINKED LIST   ##############
//##############################################

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

node_t *insertHeadLList(llist_t *llist, value_type_t value){
    
    node_t *newElement = createNodeLList(llist->DataSize);
    if(newElement == NULL)
        return NULL;

    newElement->prevPrt = llist->head;
    *(newElement->data) = value;
    llist->head = newElement;
    llist->size++;

    return newElement;
}

node_t *insertPtrHeadLList(llist_t *llist, value_type_t *value){
    
    node_t *newElement = createNodeLList(llist->DataSize);
    if(newElement == NULL)
        return NULL;

    newElement->prevPrt = llist->head;
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
    while(currentElement->prevPrt != NULL)
        currentElement = currentElement->prevPrt;

    newElement->prevPrt = currentElement->prevPrt;
    currentElement->prevPrt = newElement;
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
        currentElement = currentElement->prevPrt;
    }
    newElement->prevPrt = currentElement->prevPrt;
    currentElement->prevPrt = newElement;
}

node_t *getNodeByIndex(llist_t *llist, uint8_t index){
    int8_t destinationIndex = (int8_t)(llist->size - index);

    if(isEmptyLList(llist))
        return NULL;
    if(destinationIndex < 0)
        return llist->head;

    node_t *currentElement = llist->head;
    for(uint8_t i = 0; i < destinationIndex - 1; i++){
        currentElement = currentElement->prevPrt;
    }

    return currentElement;
}

node_t *getNodeByValue(llist_t *llist, uint8_t value){

    node_t *currentElement = llist->head;
    while(currentElement != NULL){
        if(*(currentElement->data) == value)
            return currentElement;
        currentElement = currentElement->prevPrt;
    }
    return NULL;
}

node_t *getNodeByPtrValue(llist_t *llist, uint8_t *value){

    node_t *currentElement = llist->head;
    while(currentElement != NULL){
        if(currentElement->data == value)
            return currentElement;
        currentElement = currentElement->prevPrt;
    }
    return NULL;
}

node_t *deleteLList(llist_t *llist){

    node_t *temp;
    node_t *currentElement = llist->head;

    while(currentElement != NULL){

        if(currentElement->data != NULL)
            free(currentElement->data);
        
        temp = currentElement->prevPrt;
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
        if(currentNode->prevPrt == node)
            return currentNode;
        currentNode = currentNode->prevPrt;
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
        llist->head = node->prevPrt;
        return __free_node(node);
    }

    node_t *prevElement = __get_Prev_Node(llist, node);
    if(prevElement == NULL)
        return node;

    if(prevElement != node)
        prevElement->prevPrt = node->prevPrt;

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
    const char linker[] = "----->";
    
    printf("\n");
    while(currentElement != NULL){
        if(currentElement != llist->head)
            printf(" %s ", linker);

        for(int i = 0; i < elementCount; i++){
            if(i != 0)
                printf(" ");
            printf("%d", *(currentElement->data + i));
        }
        currentElement = currentElement->prevPrt;
    }
}


//##############################################
//###########   DOUBLE LINKED LIST   ###########
//##############################################

dllist_t *createDLList(){
    dllist_t *llist = (dllist_t *)malloc(sizeof(dllist_t));
    llist->head = NULL;
    llist->back = NULL;
    llist->size = 0;
    llist->DataSize = sizeof(value_type_t);
    return llist;
}

bool isEmptyDLList(dllist_t *llist){
    return ((llist->head == NULL) && (llist->size == 0) && llist->back == NULL);
}

dnode_t *createDNodeLList(size_t dataSize){
    dnode_t *newElement = (dnode_t *)malloc(sizeof(dnode_t));
    if(!newElement)
        return NULL;
    
    newElement->data = (value_type_t *)malloc(dataSize);
    if(!newElement->data){
        free(newElement);
        return NULL;
    }
    
    return newElement;
}

dnode_t *insertHeadDLList(dllist_t *llist, value_type_t value){
    dnode_t *newElement = createDNodeLList(llist->DataSize);
    if(newElement == NULL)
        return NULL;

    *(newElement->data) = value;
    newElement->nextPrt = NULL;
    newElement->prevPrt = llist->head;
    if(isEmptyDLList(llist))
        llist->back = newElement;

    llist->head = newElement;
    llist->size++;

    return newElement;
}

dnode_t *insertPtrHeadDLList(dllist_t *llist, value_type_t *value){
    dnode_t *newElement = createDNodeLList(llist->DataSize);
    if(newElement == NULL)
        return NULL;

    newElement->data = value;
    newElement->nextPrt = NULL;
    newElement->prevPrt = llist->head;
    if(isEmptyDLList(llist))
        llist->back = newElement;

    llist->head = newElement;
    llist->size++;

    return newElement;
}

dnode_t *insertBackDLList(dllist_t *llist, value_type_t value){
    dnode_t *newElement = createDNodeLList(llist->DataSize);
    if(newElement == NULL)
        return NULL;

    *(newElement->data) = value;
    newElement->nextPrt = llist->back;
    newElement->prevPrt = NULL;

    if(!isEmptyDLList(llist))
        llist->back->prevPrt = newElement;
    else
        llist->head = newElement;
    
    llist->back = newElement;
    llist->size++;

    return newElement;
}

dnode_t *insertPtrBackDLList(dllist_t *llist, value_type_t *value){
    dnode_t *newElement = createDNodeLList(llist->DataSize);
    if(newElement == NULL)
        return NULL;

    newElement->data = value;
    newElement->nextPrt = llist->back;
    newElement->prevPrt = NULL;

    if(!isEmptyDLList(llist))
        llist->back->prevPrt = newElement;
    else
        llist->head = newElement;
    
    llist->back = newElement;
    llist->size++;

    return newElement;
}

dnode_t *insertDLList(dllist_t *llist, int8_t index, value_type_t value){

    if(llist == NULL)
        return NULL;

    if(isEmptyDLList(llist))
        return insertHeadDLList(llist, value);
    if(index <= 0)
        return insertBackDLList(llist, value);
    if(index >= (llist->size - 1))
        return insertHeadDLList(llist, value);

    dnode_t *replacingElement = __get_index_element(llist, index);
    dnode_t *newElement = createDNodeLList(llist->DataSize);

    *(newElement->data) = value;

    newElement->prevPrt = replacingElement->prevPrt;
    newElement->nextPrt = replacingElement;
    replacingElement->prevPrt = newElement;
    replacingElement->prevPrt->nextPrt = newElement;

    return newElement;
}

dnode_t *insertDPtrLList(dllist_t *llist, int8_t index, value_type_t *value){
    if(llist == NULL)
        return NULL;

    if(isEmptyDLList(llist))
        return insertPtrHeadDLList(llist, value);
    if(index <= 0)
        return insertPtrBackDLList(llist, value);
    if(index >= (llist->size - 1))
        return insertPtrHeadDLList(llist, value);

    dnode_t *replacingElement = __get_index_element(llist, index);
    dnode_t *newElement = createDNodeLList(llist->DataSize);

    newElement->data = value;

    newElement->prevPrt = replacingElement->prevPrt;
    newElement->nextPrt = replacingElement;
    replacingElement->prevPrt = newElement;
    replacingElement->prevPrt->nextPrt = newElement;

    return newElement;
}

dnode_t * __get_index_element(dllist_t *llist, int8_t i){

    if(isEmptyDLList(llist))
        return NULL;

    dnode_t *usedNode = __head_or_back(llist, i);
    if(usedNode == llist->head){
        int8_t destinationI = (int8_t)(llist->size - 1- i);
        if(destinationI <= 0)
            return usedNode;
        return __head_to_back(usedNode, destinationI);
    } else {
        if(i == 0)
            return usedNode;
        return __back_to_head(usedNode, i);
    }
}

dnode_t *__head_or_back(dllist_t *llist, int8_t i){
    if((llist->size/2) <= (i + 1))
        return llist->head;
    else 
        return llist->back;
}

dnode_t *__head_to_back(dnode_t *head, int8_t steps){
    dnode_t *cE = head;
    for(uint8_t i = 0; i < steps; i++){
        if(cE->prevPrt != NULL)
            cE = cE->prevPrt;
    }
    return cE;
}

dnode_t *__back_to_head(dnode_t *back, int8_t steps){
    dnode_t *cE = back;
    for(uint8_t i = 0; i < steps; i++){
        if(cE->nextPrt != NULL)
            cE = cE->nextPrt;
    }
    return cE;
}

void printDLList(dllist_t *llist, uint8_t elementCount){

    dnode_t *currentElement = llist->head;
    const char linker[] = "<---->";
    
    printf("\n");
    while(currentElement != NULL){
        if(currentElement != llist->head)
            printf(" %s ", linker);

        for(int i = 0; i < elementCount; i++){
            if(i != 0)
                printf(" ");
            printf("%d", *(currentElement->data + i));
        }
        currentElement = currentElement->prevPrt;
    }
}
