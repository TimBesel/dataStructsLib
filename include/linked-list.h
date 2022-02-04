#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef uint8_t value_type_t; 

typedef struct node {
    value_type_t *data;
    struct node *nextPrt;
} node_t;

typedef struct llist {
    node_t *head;
    uint8_t size;
    size_t DataSize;
} llist_t;

llist_t *createLinkedList();

bool isEmptyLList(llist_t *llist);

node_t *createNodeLList(size_t dataSize);

node_t *insertLList(llist_t *llist, uint8_t index, value_type_t value);
node_t *insertPtrLList(llist_t *llist, uint8_t index, value_type_t *value);
void __wraped_insertLList(node_t *head, node_t *newElement, int8_t destinationIndex);

node_t *insertHeadLList(llist_t *llist, value_type_t value);
node_t *insertPtrHeadLList(llist_t *llist, value_type_t *value);

node_t *insertEndLList(llist_t *llist, value_type_t value);
node_t *insertPtrEndLList(llist_t *llist, value_type_t *value);
void __warped_insertEndLList(node_t *head, node_t *newElement);

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

#endif //LINKED_LIST_H