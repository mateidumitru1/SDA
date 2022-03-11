#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int f1(int n, int *m)
{
    if(n == 0 || n == 1) return n;
    if(m[n] == 0) m[n]= f1(n-1, m) + f1(n-2, m);
    return m[n];
}

int f2(int n)
{
    if(n == 0) return 0;
    if(n == 1) return 1;
    return f2(n-1) + f2(n-2);
}

int main()
{
    int n= 7;
    int *v= calloc(n + 1, sizeof(int));

    clock_t begin= clock();
    int a= f1(n, v);
    clock_t end= clock();
    double t1= (double)(end - begin)/ CLOCKS_PER_SEC;
    printf("%d", a);

    begin= clock();
    a= f2(n);
    end= clock();
    double t2= (double)(end - begin)/ CLOCKS_PER_SEC;
    printf("\n%d\n\n", a);

    printf("Timpul de executie pentru algoritmul cu memorizare este %d, iar pentru cel fara memorizare este %d.\n", t1, t2);
    return 0;
}