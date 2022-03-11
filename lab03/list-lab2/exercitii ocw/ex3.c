#include "ex3.h"

int main()
{
    unsigned seed=time(0);
    srand(seed);
    node *head= NULL;
    int n, i;
    printf("Introduceti numarul de elemente al listei: "); scanf("%d", &n);
    for(i=0;i<n;i++)
        head= creare( head, 1 + rand() % 100 );
    printlist(head);
    node *p= head, *c= head;
    while( p != NULL )
    {
        if( p->data % 2 == 0)
        {
            node *a= p;
            printf("%d ", a-> data);
            if( a == head ) head= a->next;
            p= a->next;
            c->next= p;
            free(a);
        }
        else
        {
            c= p;
            p= p->next;
        }
    }
    printf("\n");
    printlist(head);
    return 0;
}

node *creare(node *head, int val)
{
    node *a= head, *c= head;
    node *x;
    x= malloc(sizeof(node));
    x->data= val;
    while( a != NULL )
    {
        c= a;
        a= a->next;
    }
    if( c == NULL )
    {
        x->next= NULL;
        head= x;
    }
    else
    {
        c->next= x;
        x->next= NULL;
    }
    return head;
}

void printlist(node *head)
{
    printf("\n");
    node *p= head;
    while( p != NULL )
    {
        printf("%d ", p->data);
        p= p->next;
    }
    printf("\n");
}
