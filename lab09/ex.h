#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#ifndef ex_h
#define ex_h

typedef struct node{
    char *s;
    int dist;
    int index;
    char *fisier;
    struct node *next;
}node;

typedef struct train{
    int v, e; 
    int **a, **cost;
}train;

node *create_node(char *a, char *c);

node *append_node(node *list_head, char *ch, char *i, int dist, int index);

void print_list(node *list_head);

train *create();

int verif(node *v, char *c);

int getcode(node *v, char *c);

int get_dist(node *cop, char *c);

void print_minmax(node *a, int min, int max);

void print_total(train *t);

int print_solution(node *v, int dist[], int n, int parent[], FILE *f);

int min_distance(int dist[], int sps[], int v);

void dijkstra(train *t, node *v, int s);

void printPath(node *v, int parent[], int j, FILE *f);

void print_station(node *a, int i, FILE *f);

void FW(train *t, node *v);

void prints(int dist[], int n);

#endif
