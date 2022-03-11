#include "ex1.h"

int main()
{
    graph *g= creategraph();
    kruskal(g);
    return 0;
}

void swap(muchie *a, muchie *b)
{
    muchie aux;
    aux= *a;
    *a= *b;
    *b= aux;
}

int partition(muchie *arr, int low, int high)
{
    int j;
    muchie aux;
    muchie pivot= arr[high];
    int i= low - 1;
    for(j= low; j<= high - 1; j++)
        if( arr[j].cost <= pivot.cost ){
            i++;
            swap(&arr[i], &arr[j]);
        }
    swap(&arr[i+1], &arr[high]);
    return (i+1);
}

void quicksort(muchie *arr, int low, int high)
{
    if(low < high)
    {
        int pi= partition(arr, low, high);
        quicksort(arr, low, pi-1);
        quicksort(arr, pi+1, high);
    }
}

graph *creategraph()
{
    int i, j, k, x, y, w;
    graph *g= malloc(sizeof(graph));
    FILE *f;
    if( (f= fopen("date.txt", "rt")) == NULL )
    {
        printf("Fisierul nu a putut fi deschis.");
        exit(1);
    }
    fscanf(f, "%d %d", &i, &j);
    g->V= i;
    g->E= j;

    g->e= malloc( g->E * sizeof(muchie) );

    for(int i=0; i < g->E; i++)
    {
        fscanf(f, "%d %d %d", &x, &y, &w);
        g->e[i].v1= x-1;
        g->e[i].v2= y-1;
        g->e[i].cost= w;
    }
    return g;
}

void kruskal(graph *g)
{
    int i, j, min, max, nr_muchii_selectate= -1;
    int c[g->V];
    for(i=0; i <= g->V; i++)
        c[i]= i;
        
    muchie a[ g->V - 1 ];

    quicksort(g->e, 0, (g->E)-1);

    for(i=0; nr_muchii_selectate < g->V - 1 && i<g->E; i++)
    {
        if( c[g->e[i].v1] != c[g->e[i].v2] )
            a[++nr_muchii_selectate] = g->e[i];

        if( c[g->e[i].v1] < c[g->e[i].v2] )
        {
            min= c[g->e[i].v1];
            max= c[g->e[i].v2];
        }
        else
        {
            max= c[g->e[i].v1];
            min= c[g->e[i].v2];
        }
        for(j=0; j < g->V; j++)
            if( c[j] == max ) c[j]= min;
    }
    int s=0;
    for(i=0; i < g->V - 1;  i++)
    {
        s= s+a[i].cost;
        printf("%d %d %d\n", a[i].v1, a[i].v2, a[i].cost);
    }
    printf("%d\n", s);
}

