#ifndef QUEUE_H
#define QUEUE_H

#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef uint8_t *queue_value_type_t;
#define QUEUE_NO_VALUE (queue_value_type_t)NULL

typedef struct queue
{
    uint8_t front_idx;
    uint8_t back_idx;
    uint8_t size;
    uint8_t capacity;
    queue_value_type_t *data;
} queue_t;


queue_t *createQueue(uint8_t capacity);

queue_t *reQueue(queue_t *queue, uint8_t capacity);
void reOrderQueue(queue_t *queue);
void __clean_Queue(queue_t *queue);
void __resort_Queue(queue_value_type_t data[], uint8_t n, uint8_t k);
uint8_t __gcd(uint8_t a, uint8_t b);

queue_t *freeQueue(queue_t *queue);

bool queueIsFull(queue_t *queue);
bool queueIsEmpty(queue_t *queue);

void queuePush(queue_t *queue, queue_value_type_t value);
queue_value_type_t queuePop(queue_t *queue);
queue_value_type_t queueFront(queue_t *queue);
queue_value_type_t queueBack(queue_t *queue);

#endif //QUEUE_H