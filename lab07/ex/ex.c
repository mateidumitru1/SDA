#include "ex.h"

int c;

int main()
{
    //  EXERCITIUL 1
    int *v1, *v2, n=1e6;
    v1= malloc(n * sizeof(int));
    v2= malloc(n * sizeof(int));

    for(int i=0;i<n;i++)
    {
        v1[i]= rand()%1000000;
        v2[i]= v1[i];
    }

    /*printf("v1: ");
    printv(v1, n);
    printf("\n");

    printf("v2: ");
    printv(v2, n);
    printf("\n");*/

    clock_t begin= clock();
    heapSort(v1, n);
    clock_t end= clock();
    double t1= (double)(end- begin)/ CLOCKS_PER_SEC;
    printf("Numarul de apelari necesare pentru tot algoritmul ale functiei \"cerne\" este %d.\n\n", c); //  EXERCITIUL 2
    /*printf("v1: ");
    printv(v1, n);
    printf("\n");*/

    begin= clock();
    radixSort(v2, n);
    end= clock();
    double t2= (double)(end- begin)/ CLOCKS_PER_SEC;

    /*printf("v2: ");
    printv(v2, n);*/

    printf("\nTimpul de executie pentru heapsort este %f secunde, iar pentru radixsort este %f secunde.\n", t1, t2);
    printf("\n\n");




//  EXERCITIUL 3
    srand(time(NULL));
    int *v;
    v= malloc(20 * sizeof(int));
    for(int i=0;i<20;i++)
        v[i]= rand()%1500 - 750;
    printf("v: ");
    printv(v, 20);
    printf("\n");
    int m= v[0];
    for(int i=1;i<20;i++)
        if(v[i] < m) m= v[i];
    if(m < 0) for(int i=0;i<20;i++) v[i]= v[i] - m;
    radixSort(v, 20);
    if(m < 0) for(int i=0;i<20;i++) v[i]= v[i] + m;
    printf("v: ");
    printv(v, 20);

    return 0;
}

void printv(int v[], int n)
{
    for(int i=0;i<n;i++) printf("%d ", v[i]);
    printf("\n");
}

void schimba(int a[],int i,int j)
{
    int aux;
    aux = a[i];
    a[i] = a[j];
    a[j] = aux;
}

void cerne(int a[],int n,int k)
{
    c++;
    int fiuStanga = 2 * k + 1, fiuDreapta = 2 * k + 2, pozMax = fiuStanga;
    if(fiuStanga >= n)
        return;
    if(fiuDreapta < n) {
        if(a[fiuDreapta] > a[fiuStanga] ) {
            pozMax = fiuDreapta;
        }
    }
    if(a[k] < a[pozMax]) {
        schimba(a,k,pozMax);
        cerne(a,n,pozMax);
    }
}

void makeHeap(int a[],int n)
{
    for(int i = n / 2;i >= 0;i--) {
        cerne(a,n,i);
    }
    printf("Numarul de apelari al functiei makeHeap este %d.\n", c);
}

void heapSort(int a[],int n)
{
    makeHeap(a,n);
    while(n > 1) {
        schimba(a,0,n-1);
        n--;
        cerne(a,n,0);
    }
 
}

int obtineOctetul(int n,int byteNr)
{
    int bitsNr =  BYTE * byteNr;
    int mask = COUNT_BYTE - 1;
    return (n >> bitsNr) & mask;
}

void rad(int *a,int *b, int byteNr,int n)
{
    int i,
        count[COUNT_BYTE] = {0},
        index[COUNT_BYTE] = {0};
    for(i = 0; i < n;i++) {
        int car = obtineOctetul(a[i],byteNr);
        count[car]++;
    }
    for(i = 1;i < COUNT_BYTE;i++)
        index[i] = index[i-1] + count[i-1];
    for(i = 0; i < n; i++) {
        int car = obtineOctetul(a[i],byteNr);
        b[index[car]++] = a[i];
    }
}

void radixSort(int *a,int n)
{
    int *b = malloc(n*sizeof(int)), byteNr, k = sizeof(a[0]);
    for(byteNr = 0; byteNr < k; byteNr += 2) {
        rad(a, b, byteNr, n);
        rad(b, a, byteNr + 1, n);
    }
    free(b);
}
