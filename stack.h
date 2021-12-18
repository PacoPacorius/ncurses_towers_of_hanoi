#ifndef _STACK
#define _STACK

#include <stdlib.h>

struct Stack {
    int top;
    unsigned int capacity;
    int* array;
};

struct Stack* create_stack(unsigned int capacity);

int is_stack_full(struct Stack* stack);

int is_stack_empty(struct Stack* stack);

void push(struct Stack* stack, int number);

int pop(struct Stack* stack);

int number_of_items(struct Stack* stack);

#endif
