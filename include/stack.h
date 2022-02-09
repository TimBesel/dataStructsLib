#ifndef STACK_H
#define STACK_H

#include <math.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t *stack_value_type_t; 
#define NO_VALUE (stack_value_type_t)NULL

typedef struct stack
{
    uint8_t size;
    uint8_t capacity;
    stack_value_type_t *data;
} stack_t;


stack_t *createStack(uint8_t capacity);
stack_t *reStack(stack_t *stack, uint8_t capacity);
stack_t *deleteStack(stack_t *stack);
bool stackIsFull(stack_t *stack);
bool stackisEmpty(stack_t *stack);
void stackPush(stack_t *stack, stack_value_type_t value);
stack_value_type_t stackPop(stack_t *stack);
stack_value_type_t stackTop(stack_t *stack);
void printStack(stack_t *stack);

#endif //STACK_H