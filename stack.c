#include "stack.h"

/*
 * check if full
 *
 * check if empty
 *
 * push (overflow condition)
 *
 * pop
 */

struct Stack* create_stack(unsigned int capacity){
    
    struct Stack* temp_stack = (struct Stack*)malloc(sizeof(struct Stack));
    temp_stack->capacity = capacity;
    temp_stack->top = -1;
    temp_stack->array = (int*)malloc(temp_stack->capacity * sizeof(int));

    return temp_stack;
}

int is_stack_full(struct Stack* stack){
    return (stack->top == stack->capacity - 1); 
}

int is_stack_empty(struct Stack* stack){
    return stack->top == -1;
}

void push(struct Stack* stack, int number){
    stack->array[++stack->top] = number;

    if(is_stack_full(stack) == 1){
        stack->top = 0;
        stack->array[stack->top] = number;
    }
}

int pop(struct Stack* stack){
    if(stack->top == 0)
        stack->top = stack->capacity - 1;
    else stack->top--;

     return stack->array[stack->top];
}
