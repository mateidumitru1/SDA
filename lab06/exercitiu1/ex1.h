#include <stdio.h>
#include <stdlib.h>

#ifndef ex_h
#define ex_h

typedef struct node{
    int data;
    struct node *left, *right;
}node;

node *create_node(int data);

void swap(int *a, int *b);

int partition(int v[], int p, int u);

void quicksort(int v[], int p, int u);

node *create_tree(int *v, int p, int u);

void inorder(node *n);

void preorder(node *n);

int ver(node *n);

node *search_tree(node *n, int data);

node *insert(node *n, int data);

node *delete(node *n, int data);

node *minvaluenode(node *n);

#endif
