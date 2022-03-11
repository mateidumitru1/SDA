#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ex1_h
#define ex1_h

typedef struct muchie{
    int v1, v2, cost;
}muchie;

typedef struct graph{
    int V, E;
    muchie *e;
}graph;

void swap(muchie *a, muchie *b);

int partition(muchie *arr, int low, int high);

void quicksort(muchie *arr, int low, int high);

graph *creategraph();

void kruskal(graph *g);

#endif