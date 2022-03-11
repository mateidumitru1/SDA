#include <stdio.h>
#include <stdlib.h>

#ifndef ex4_h
#define ex4_h

typedef struct polinom{
    unsigned int putere;
    int coeficient;
    struct polinom *next;
}polinom;

polinom *creare_polinom(polinom *p);

polinom *aduna_polinom(polinom *p1, polinom *p2, int n);

void print_polinom(polinom *p);

#endif