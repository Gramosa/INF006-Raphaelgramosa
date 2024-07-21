#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MIN_SIZE 10

typedef struct Stack{
    int *S;
    int top;
    int size;
} Stack;

Stack* create_stack(){
    Stack *stack = malloc(sizeof(Stack));
    stack->S = malloc(MIN_SIZE * sizeof(int));
    stack->size = MIN_SIZE;
    stack->top = -1;
    return stack;
}

void delete_stack(Stack *stack){
    if(stack != NULL){
        if(stack->S != NULL){
            free(stack->S);
        }
        free(stack);
    }
}

bool is_full(Stack *stack){
    return stack->top == stack->size - 1;
}

bool is_empty(Stack *stack){
    return stack->top == -1;
}

void push(Stack *stack, int item){
    if(!is_full(stack)){
        stack->S[++stack->top] = item;
    }
    else{
        printf("Cannot push, since stack is full");
    }
}

int pop(Stack *stack){
    if(!is_empty(stack)){
        return stack->S[stack->top--];
    }
    else{
        printf("Cannot pop since the stack is empty");
        return INT_MIN;
    }
}

int main(){
    Stack *nb = create_stack();
    push(nb, 40);
    push(nb, 23);
    push(nb, 112);
    push(nb, -15);
    while(!is_empty(nb)){
        printf("%d\n", pop(nb));
    }

    delete_stack(nb);
    return 0;
}
