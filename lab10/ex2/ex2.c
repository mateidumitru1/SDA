#include "ex2.h"

int main()
{
    FILE *f, *g;

    if( (f= fopen("_all_files.txt", "rt")) == NULL )
    {
        printf("Fisierul nu a putut fi deschis.\n");
        exit(1);
    }
    int dist, dist1=0, d;
    char c[15];
    node *n = NULL;
    node *aux= NULL;
    while ((fscanf(f, "%[^\n]\n", c)) == 1) // CITIRE
    {
        if ((g = fopen(c, "rt")) == NULL)
        {
            printf("Fisierul nu a putut fi deschis.\n", c);
            exit(1);
        }
        char a[30];
        while ((fscanf(g, "%[^,]", a)) == 1)
        {
            fgetc(g);
            fscanf(g, "%d", &dist);
            fgetc(g);
            if( dist == 0 ) d= 0;
            else d= dist - dist1;
            n = append_node(n, a, c, d, 0);
            dist1= dist;
        }
    }
    fclose(f);
    fclose(g);

    node *a= n;
    node *v= NULL;

    train *t= malloc(sizeof(train)); // neorientat
    t->v= 0;
    t->e= 0;
    while( a != NULL )
    {
        if(verif(v, a->s) == -1 )
        {
            (t->v)++;
            v = append_node(v, a->s, a->fisier, a->dist, (t->v)-1);
        }
        a= a->next;
    }

    //print_list(v);
    
    t->cost= calloc(t->v, sizeof(int *));
    for(int i=0;i < t->v; i++)
        t->cost[i]= calloc(t->v, sizeof(int));

    int m1=0, m2=0;
    a= n;

    while (a->next != NULL)
    {
        m1 = getCode(v, a->s);
        m2 = getCode(v, a->next->s);
        if ( (strcmp(a->fisier, a->next->fisier) ) == 0 )
        {
            t->cost[m1][m2]= t->cost[m2][m1]= a->next->dist;
        }
        a = a->next;
    }

    for(int i=0; i < t->v; i++)
        for(int j=i+1; j < t->v; j++)
            if( t->cost[i][j] != 0 ) (t->e)++;

    if( ( f= fopen("date.txt", "wt") ) == NULL )
    {
        printf("Fisierul nu a putut fi deschis.");
        exit(1);
    }

    fprintf(f,"%d %d\n", t->v, t->e);

    for(int i=0; i < t->v; i++)
        for(int j=i+1; j < t->v; j++)
            if(t->cost[i][j] != 0 )
            {
                fprintf(f, "%d %d %d\n", i, j, t->cost[i][j]);
            }
    fclose(f);

    graph *gr= creategraph();
    kruskal(gr);
    return 0;
}

node *create_node(char *a, char *c)
{
    node *n = NULL;
    n = malloc(sizeof(node));
    n->s = strdup(a);
    n->fisier = strdup(c);
    n->next = NULL;
    return n;
}

node *append_node(node *list_head, char *ch, char *i, int dist, int index)
{
    node *a = list_head, *c = list_head;
    node *n;
    n = malloc(sizeof(node));
    n->s = strdup(ch);
    n->fisier = strdup(i);
    n->dist= dist;
    n->index= index;
    while (c != NULL)
    {
        a = c;
        c = c->next;
    }
    if (a == NULL)
    {
        n->next = NULL;
        list_head = n;
    }
    else
    {
        a->next = n;
        n->next = NULL;
    }
    return list_head;
}

void print_list(node *list_head)
{
    FILE *f;
    f = fopen("a.txt", "wt");
    node *p = list_head;
    while (p != NULL)
    {
        fputs(p->s, f);
        fprintf(f,", %d, %d\n", p->dist, p->index);
        p = p->next;
    }
}

int verif(node *v, char *c)
{
    node *a= v;
    while( a != NULL )
    {
        if( (strcmp(a->s, c)) == 0 ) return 1;
        a= a->next;
    }
    return -1;
}

int getCode(node *head, char *valStatie)
{
    while(head!=NULL)
    {
        if((strcmp(head->s, valStatie)) == 0)
        {
            return head->index;
        }
        head=head->next;
    }
    return -1;
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
        g->e[i].v1= x;
        g->e[i].v2= y;
        g->e[i].cost= w;
    }
    return g;
}

void kruskal(graph *g)
{
    int i, j, min, max, nr_muchii_selectate= -1;
    int c[g->V];
    for(i=0; i < g->V; i++)
        c[i]= i;
        
    muchie a[ g->V - 1 ];

    quicksort(g->e, 0, (g->E)-1);
    
    for(i=0; nr_muchii_selectate < g->V - 2; i++)
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

    FILE *f;

    if( ( f= fopen("out.txt", "wt") ) == NULL )
    {
        printf("Fisierul nu a putut fi deschis.");
        exit(1);
    }
    int sum=0;
    for(i=0; i < g->V - 1;  i++)
    {
        sum= sum+a[i].cost;
        fprintf(f, "%d %d %d\n", a[i].v1, a[i].v2, a[i].cost);
    }
    fprintf(f,"%d", sum);
}
