#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ex2_h
#define ex2_h

typedef struct node{
    int data;
    struct node *next;
}node;

node *creare(node *head, int val);

void printlist(node *head);

node *sterge(node *head, int n);

#endif