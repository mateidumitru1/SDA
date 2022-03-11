#include <stdio.h>
#include <stdlib.h>

#ifndef ex2_h
#define ex2_h

typedef struct node{
    int data, height;
    struct node *left, *right;
}node;

int max(int a, int b);

void swap(int *a, int *b);

int partition(int v[], int p, int u);

void quicksort(int v[], int p, int u);

// int nodeheight(node *root);

node *rightrotation(node *z);

node *leftrotation(node *z);

node *lrrotation(node *z);

node *rlrotation(node *z);

node *insert(node *node, int data);

void inorder(node *n);

#endif
