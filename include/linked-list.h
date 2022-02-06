#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef uint8_t value_type_t; 

typedef struct node {
    value_type_t *data;
    struct node *prevPrt;
} node_t;

typedef struct llist {
    node_t *head;
    uint8_t size;
    size_t DataSize;
} llist_t;

typedef struct dnode {
    value_type_t *data;
    struct dnode *nextPrt;
    struct dnode *prevPrt;
} dnode_t;

typedef struct dllist {
    dnode_t *head;
    dnode_t *back;
    uint8_t size;
    size_t DataSize;
} dllist_t;



//##############################################
//###############   LINKED LIST   ##############
//##############################################

llist_t *createLList();

bool isEmptyLList(llist_t *llist);

node_t *createNodeLList(size_t dataSize);

node_t *insertHeadLList(llist_t *llist, value_type_t value);
node_t *insertPtrHeadLList(llist_t *llist, value_type_t *value);

node_t *insertEndLList(llist_t *llist, value_type_t value);
node_t *insertPtrEndLList(llist_t *llist, value_type_t *value);
void __warped_insertEndLList(node_t *head, node_t *newElement);

node_t *insertLList(llist_t *llist, uint8_t index, value_type_t value);
node_t *insertPtrLList(llist_t *llist, uint8_t index, value_type_t *value);
void __wraped_insertLList(node_t *head, node_t *newElement, int8_t destinationIndex);

node_t *getNodeByIndex(llist_t *llist, uint8_t index);
node_t *getNodeByValue(llist_t *llist, uint8_t value);
node_t *getNodeByPtrValue(llist_t *llist, uint8_t *value);

node_t *deleteLList(llist_t *llist);
node_t *deleteNode(llist_t *llist, node_t *node);
node_t *__get_Prev_Node(llist_t *llist, node_t *node);
node_t * __free_node(node_t *node);
node_t *deleteIndexNode(llist_t *llist, uint8_t index);
node_t *popHeadLList(llist_t *llist);
node_t *popLList(llist_t *llist);

value_type_t getValueByNode(node_t *node);
value_type_t *getPtrValueByNode(node_t *node);

value_type_t getValueByIndex(llist_t *llist, uint8_t index);
value_type_t *getPtrValueByIndex(llist_t *llist, uint8_t index);

void printLList(llist_t *llist, uint8_t elementCount);


//##############################################
//###########   DOUBLE LINKED LIST   ###########
//##############################################

dllist_t *createDLList();

bool isEmptyDLList(dllist_t *llist);

dnode_t *createDNodeLList(size_t dataSize);

dnode_t *insertHeadDLList(dllist_t *llist, value_type_t value);
dnode_t *insertPtrHeadDLList(dllist_t *llist, value_type_t *value);

dnode_t *insertBackDLList(dllist_t *llist, value_type_t value);
dnode_t *insertPtrBackDLList(dllist_t *llist, value_type_t *value);

dnode_t *insertDLList(dllist_t *llist, uint8_t index, value_type_t value);
dnode_t *__head_or_back(dllist_t *llist, uint8_t index);
dnode_t *insertDPtrLList(dllist_t *llist, uint8_t index, value_type_t *value);
void __wraped_insertDLList(dnode_t *head, dnode_t *back, dnode_t *newElement, int8_t destinationIndex);
void printDLList(dllist_t *llist, uint8_t elementCount);

#endif //LINKED_LIST_H