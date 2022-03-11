#ifndef f_h
#define f_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct timp
{
    int ora,minut,secunda;
}timp;

void meniu();
void selectionsort(int v[], int n, int *n1);
int partition(int v[], int p, int u, int *n2);
void quicksort(int v[], int p, int u, int *n2);
void swap(int *a, int *b);
void afisare(int v[], int n);
void *selectionsortcuvinte(char **v, int n);
void swapcuv(char *v1, char *v2);
int partitiontimp(timp *v, int p, int u);
void quicksorttimp(timp *v, int p, int u);
void sortfrecventa(int *v, int n);


#endif
