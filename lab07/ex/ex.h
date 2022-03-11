#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BYTE 8
#define COUNT_BYTE 256


#ifndef ex_h
#define ex_h

void printv(int v[], int n);

void schimba(int a[],int i,int j);

void cerne(int a[],int n,int k);

void makeHeap(int a[],int n);

void heapSort(int a[],int n);

int obtineOctetul(int n,int byteNr);

void rad(int *a,int *b, int byteNr,int n);

void radixSort(int *a,int n);

#endif
