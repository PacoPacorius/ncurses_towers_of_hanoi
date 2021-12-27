#include "stack.h"

struct Stack* create_stack(unsigned int capacity){
    
    struct Stack* temp_stack = (struct Stack*)malloc(sizeof(struct Stack));     // allocate memory for the stack struct object
    temp_stack->capacity = capacity;
    temp_stack->top = -1;
    temp_stack->array = (int*)malloc(temp_stack->capacity * sizeof(int));       // allocate memory for the int array inside the stack 

    int i;
    for(i = 0; i < capacity + 1; i++) temp_stack->array[i] = -1;
    return temp_stack;
}

int is_stack_full(struct Stack* stack){
    return (stack->top == stack->capacity); 
}

int is_stack_empty(struct Stack* stack){
    return stack->top == -1;
}

void push(struct Stack* stack, int number){

    if(is_stack_full(stack) == 0){          // overflow condition, wrap back at the beginning of the int array and continue, fuck the overflow condition, fuck all this fancy shit
        stack->top++;
        stack->array[stack->top] = number;
    }
}

int pop(struct Stack* stack){               
    if(is_stack_empty(stack) == 1) return -1;   // catch this before pushing it to another stack

    int previous_top;

    previous_top = stack->array[stack->top];
    stack->array[stack->top] = -1;

//    if(stack->top == 0)                     // underflow condition, wrap at the end of the array and continue
//        stack->top = stack->capacity;
//    else stack->top--;
    stack->top--;                             // fuck the underflow condition this is probably what fucked me up
    return previous_top;
    
}

int number_of_items(struct Stack* stack){
    int i, counter;

    for(i = 0, counter = 0; i < stack->capacity; i++)
        if(stack->array[i] != -1) counter++;
    
    return counter;
}
