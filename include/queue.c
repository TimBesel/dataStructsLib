#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

queue_t *createQueue(uint8_t capacity){
    queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
    if(!queue)
        return NULL;
    
    uint8_t data_size = capacity * sizeof(value_type_t);
    value_type_t *data = (value_type_t *)malloc(data_size);

    if(!data){
        free(queue);
        return NULL;
    }

    queue->front_idx = 0u;
    queue->back_idx = 0u;
    queue->size = 0u;
    queue->capacity = capacity;
    queue->data = data;

    return queue;
}

queue_t *reQueue(queue_t *queue, uint8_t capacity){
	if(!queue->data)
        return NULL;
	
    __clean_Queue(queue);

	queue->capacity = capacity;
    size_t data_size = capacity * sizeof(value_type_t);
    queue->data = (value_type_t *)realloc(queue->data, data_size);

    if(queue->back_idx == 0)
        queue->back_idx = queue->capacity - 1;
        
    return queue;
}

void __clean_Queue(queue_t *queue){
    __resort_Queue(queue->data, queue->capacity, queue->front_idx);
    queue->front_idx = 0;
    queue->back_idx = (uint8_t)(queue->front_idx + queue->size) % queue->capacity;
}

void __resort_Queue(value_type_t data[], uint8_t n, uint8_t k){
	int8_t d = -1, i, j;
    value_type_t temp;
	for(i = 0; i < __gcd(n, k); i++){
		j = i;
		temp = data[i];

		while(1){
			d = (int8_t)((j + k) % n);

			if(d == i)
				break;
			
			data[j] = data[d];
			j = d;
		}
		data[j] = temp;
	}
}

uint8_t __gcd(uint8_t a, uint8_t b){
	if(b==0){
		return a;
	} else {
		return __gcd(b, a%b);
	}
}

queue_t *freeQueue(queue_t *queue){
    if(queue){
        if(queue->data)
            free(queue->data);
        free(queue);
    }
    return NULL;
}

bool queueIsFull(queue_t *queue){
    return (queue->size == queue->capacity);
}

bool queueIsEmpty(queue_t *queue){
    return (!queue->size);
}

void queuePush(queue_t *queue, value_type_t value){
    if(queueIsFull(queue))
        return;
    queue->data[queue->back_idx] = value;
    queue->back_idx =(uint8_t)((queue->back_idx + 1) % queue->capacity);
    queue->size++;
}

value_type_t queuePop(queue_t *queue){
    if(queueIsEmpty(queue))
        return NO_VALUE;

    value_type_t temp = queue->data[queue->front_idx];
    queue->data[queue->front_idx] = NO_VALUE;
    queue->front_idx = (uint8_t)((queue->front_idx + 1) % queue->capacity);
    queue->size--;

    return temp;
}

value_type_t queueFront(queue_t *queue){
    if(queueIsEmpty(queue))
        return NO_VALUE;
    return queue->data[queue->front_idx - 1u];
}

value_type_t queueBack(queue_t *queue){
    if(queueIsEmpty(queue))
        return NO_VALUE;
    return queue->data[queue->back_idx - 1u];
}