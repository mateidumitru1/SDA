#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#ifndef ex3_h
#define ex3_h

typedef struct queue_node{
	int val;
	unsigned int prio;
	struct queue_node *next;
} queue_node;

typedef struct queue{
	queue_node *front, *rear;
	unsigned int length;
} queue;

queue *queue_create();

queue_node *queue_node_create(int val, int v[]);

void queue_print(queue *q);

void queue_push(queue *q, int val);

int queue_pop(queue *queue, int v[]);

#endif