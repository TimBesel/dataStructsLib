#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef uint8_t value_type_t; 

typedef struct node {
    struct node *prevPrt;
    value_type_t *data;
} node_t;

typedef struct llist {
    node_t *head;
    uint8_t size;
} llist_t;

typedef struct dnode {
    struct dnode *nextPrt;
    struct dnode *prevPrt;
    value_type_t *data;
} dnode_t;

typedef struct dllist {
    dnode_t *head;
    dnode_t *back;
    uint8_t size;
} dllist_t;

//##############################################
//###############   LINKED LIST   ##############
//##############################################

llist_t *createLList();

bool isEmptyLList(llist_t *llist);

node_t *createNode(size_t dataSize);

node_t *insertHeadLList(llist_t *llist, value_type_t value);
node_t *insertPtrHeadLList(llist_t *llist, value_type_t *value);

node_t *insertEndLList(llist_t *llist, value_type_t value);
node_t *insertPtrEndLList(llist_t *llist, value_type_t *value);
void __warped_insertEndLList(node_t *head, node_t *newElement);

node_t *insertLList(llist_t *llist, uint8_t index, value_type_t value);
node_t *insertPtrLList(llist_t *llist, uint8_t index, value_type_t *value);
void __wraped_insertLList(node_t *head, node_t *newElement, int8_t destinationIndex);

node_t *getNodeByIndex(llist_t *llist, uint8_t index);
int8_t getIndexByNode(llist_t *llist, node_t *node);

node_t *getNodeByValue(llist_t *llist, uint8_t value);
node_t *getNodeByPtrValue(llist_t *llist, uint8_t *value);

int8_t getIndexByValueLList(llist_t *llist, value_type_t value);
int8_t getIndexByPtrValueLList(llist_t *llist, value_type_t *value);

llist_t *deleteLList(llist_t *llist);
node_t *deleteNode(llist_t *llist, node_t *node);
node_t *__get_Next_Node(llist_t *llist, node_t *node);
node_t * __free_node(node_t *node);
node_t *deleteIndexNode(llist_t *llist, uint8_t index);
node_t *popHeadLList(llist_t *llist);
node_t *popLList(llist_t *llist);

value_type_t getValueByNode(node_t *node);
value_type_t *getPtrValueByNode(node_t *node);

value_type_t getLListValueByIndex(llist_t *llist, uint8_t index);
value_type_t *getLListPtrValueByIndex(llist_t *llist, uint8_t index);

void printLList(llist_t *llist, uint8_t elementCount);


//##############################################
//###########   DOUBLE LINKED LIST   ###########
//##############################################

dllist_t *createDLList();

bool isEmptyDLList(dllist_t *llist);

dnode_t *createDNode(size_t dataSize);

dnode_t *insertHeadDLList(dllist_t *llist, value_type_t value);
dnode_t *insertPtrHeadDLList(dllist_t *llist, value_type_t *value);

dnode_t *insertBackDLList(dllist_t *llist, value_type_t value);
dnode_t *insertPtrBackDLList(dllist_t *llist, value_type_t *value);

dnode_t *insertDLList(dllist_t *llist, int8_t index, value_type_t value);
dnode_t *insertDPtrLList(dllist_t *llist, int8_t index, value_type_t *value);

dnode_t *getDNodeByIndex(dllist_t *llist, int8_t index);
dnode_t *__head_or_back(dllist_t *llist, int8_t i);
dnode_t *__head_to_back(dnode_t *head, int8_t steps);
dnode_t *__back_to_head(dnode_t *back, int8_t steps);
int8_t getIndexByDNode(dllist_t *llist, dnode_t *node);

dnode_t *getDNodeByValue(dllist_t *llist, uint8_t value);
dnode_t *getDNodeByPtrValue(dllist_t *llist, uint8_t *value);

int8_t getIndexByValueDLList(dllist_t *llist, value_type_t value);
int8_t getIndexByPtrValueDLList(dllist_t *llist, value_type_t *value);

dllist_t *deleteDLList(dllist_t *llist);
dnode_t *deleteDNode(dllist_t *llist, dnode_t *node);
dnode_t * __free_dnode(dnode_t *node);
dnode_t *deleteIndexDNode(dllist_t *llist, int8_t index);
dnode_t *popHeadDLList(dllist_t *llist);
dnode_t *popDLList(dllist_t *llist);

value_type_t getValueByDNode(dnode_t *node);
value_type_t *getPtrValueByDNode(dnode_t *node);

value_type_t getDLListValueByIndex(dllist_t *llist, uint8_t index);
value_type_t *getDLListPtrValueByIndex(dllist_t *llist, uint8_t index);

void printDLList(dllist_t *llist, uint8_t elementCount);

#endif //LINKED_LIST_H