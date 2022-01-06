#include "stack.h"

struct Stack* create_stack(unsigned int capacity){
    
    struct Stack* temp_stack = (struct Stack*)malloc(sizeof(struct Stack));     // allocate memory for the stack struct object
    temp_stack->capacity = capacity;
    temp_stack->top = -1;                                                       // pointer location for empty stack
    temp_stack->array = (int*)malloc((temp_stack->capacity - 1) * sizeof(int));       // allocate memory for the int array inside the stack 

    int i;
    for(i = 0; i < capacity; i++) temp_stack->array[i] = -1;                    // initialise the array (-1 is empty)
    return temp_stack;
}

int is_stack_full(struct Stack* stack){
    return (stack->top == stack->capacity); 
}

int is_stack_empty(struct Stack* stack){
    return stack->top == -1;
}

void push(struct Stack* stack, int number){

    if(is_stack_full(stack) == 0 && number > -1){          // if the stack is not full and the number is positive or 0, push
        stack->top++;
        stack->array[stack->top] = number;
    }
}

int pop(struct Stack* stack){               
    if(is_stack_empty(stack) == 1) return -1;   // catch this before pushing it to another stack, this is quite dangerous and might fuck things up but I have to return some value here

    int previous_top;

    previous_top = stack->array[stack->top];
    stack->array[stack->top] = -1;                  // replace the old value with -1

    stack->top--;                             
    return previous_top;
    
}

int number_of_items(struct Stack* stack){
    int i, counter;

    for(i = 0, counter = 0; i < stack->capacity; i++)
        if(stack->array[i] != -1) counter++;                // number of items is how many numbers in the stack aren't -1
    
    return counter;
}
