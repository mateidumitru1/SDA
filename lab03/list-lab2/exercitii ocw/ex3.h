#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef ex3_h
#define ex3_h

typedef struct node{
    int data;
    struct node *next;
}node;

node *creare(node *head, int val);

void printlist(node *head);

#endif