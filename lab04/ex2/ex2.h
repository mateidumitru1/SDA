#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#ifndef ex2_h
#define ex2_h

typedef struct stack_node{
	int val;
	struct stack_node *next;
} stack_node;

typedef struct stack{
	struct stack_node *head;
	unsigned int length;
} stack;

stack *stack_create();

stack_node *stack_node_create(int val);

void stack_push(stack *stack, int val);

void stack_print(stack *stack);

int stack_pop(stack *stack);

#endif