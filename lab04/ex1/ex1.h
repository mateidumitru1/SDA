#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ex1_c
#define ex1_c

typedef struct stack_node{
    char *cuv;
    struct stack_node *next;
} stack_node;

typedef struct stack{
    struct stack_node *head;
    unsigned int length;
} stack;

stack *stack_create();

stack_node *stack_node_create(char c[]);

void stack_push(stack *stack, char c[]);

char *stack_pop(stack *stack);

void stack_print(stack *stack);

#endif
