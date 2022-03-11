#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ex1_h
#define ex1_h

typedef struct angajati{
    char nume[30], nrtel[11], post[10];
    struct angajati *next, *prev;
}angajati;

angajati *creare(angajati *head);

void printlist(angajati *head);

angajati *adauga3(angajati *head);

angajati *adauga_dupa_mecanic(angajati *head);

angajati *sterge_nrtel(angajati *head);

#endif