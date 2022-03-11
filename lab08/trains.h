#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef trains_h
#define trains_h

typedef struct node{
    char *s;
    char *i;
    struct node *next;
}node;

typedef struct train{
    int v, e; 
    int **a;
}train;


node *create_node(char *a, char *c);

node *append_node(node *list_head, char *ch, char *i);

void print_list(node *list_head);

train *create();

int verif(node *v, char *c);

void write_ve(train *t1, train *t2);

void write_max(train *t1, node *a);

void find_grade(train *t1, node *a);

void BFS(train *t, node *v, int i);

void str(node *v, int index, char *s);

int isQueueEmpty();

int removeData();

void insert(int data);

int getAdjUnvisitedVertex(train *t, int vertexIndex, int *v);

void DFS(train *t1, node *v, int i, FILE *f);

#endif
