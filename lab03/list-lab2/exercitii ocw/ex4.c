#include "ex4.h"


int main()
{
    polinom *p1= NULL, *p2= NULL;
    int n1, n2;
    printf("Introduceti gradul polinomului p1: "); scanf("%d", &n1);
    printf("\nIntroduceti gradul polinomului p2: "); scanf("%d", &n2);
    for(int i=0;i<=n1;i++)
    {
        p1= creare_polinom(p1);
    }

    for(int i=0;i<=n2;i++)
    {
        p2= creare_polinom(p2);
    }
    printf("Polinomul p1: ");
    print_polinom(p1);
    printf("\nPolinomul p2: ");
    print_polinom(p2);
    polinom *pr;
    if( n1 > n2 )
        pr= aduna_polinom(p2, p1, n1);
    else pr= aduna_polinom(p1, p2, n2);
    printf("\n\nPolinomul pr: ");
    print_polinom(pr);
    return 0;
}

polinom *creare_polinom(polinom *p)
{
    int i=0;
    polinom *a= p, *c= p;
    polinom *x;
    x= malloc(sizeof(polinom));

    x->coeficient= 1 + rand() % 200 - 100;
    
    while( a != NULL )
    {
        c= a;
        a= a->next;
        i++;
    }
    x->putere= i;
    if( c == NULL )
    {
        x->next= NULL;
        p= x;
    }
    else
    {
        c->next= x;
        x->next= NULL;
    }
    return p;
}

polinom *aduna_polinom(polinom *p1, polinom *p2, int n)
{
    int *v, i=0;
    polinom *pp1= p1, *pp2= p2;
    v= calloc( n+1 , sizeof(int) ); // n este gradul minim
    while ( pp1 != NULL )
    {
        v[i]= pp1->coeficient + pp2->coeficient;
        pp1= pp1->next;
        pp2= pp2->next;
        i++;
    }
    while ( pp2 != NULL )
    {
        v[i]= pp2->coeficient;
        pp2= pp2->next;
        i++;
    }
    polinom *pr= NULL;
    for(int i=0;i<=n;i++)
    {
        int j=0;
        polinom *a= pr, *c= pr;
        polinom *x;
        x= malloc(sizeof(polinom));
        x->coeficient= v[i];
    
        while( a != NULL )
        {
            c= a;
            a= a->next;
            j++;
        }
        x->putere= j;
        if( c == NULL )
        {
            x->next= NULL;
            pr= x;
        }
        else
        {
            c->next= x;
            x->next= NULL;
        }
    }
    return pr;
}

void print_polinom(polinom *p)
{
    polinom *a= p;
    while( a != NULL )
    {
        printf("|  %dX^%d  |", a->coeficient, a->putere);
        a= a->next;
    }
    printf("\n");
}