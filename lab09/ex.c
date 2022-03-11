#include "ex.h"

int main()
{
    FILE *f, *g;

    if ((f = fopen("_all_files.txt", "rt")) == NULL)
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

    train *t1= malloc(sizeof(train)); // neorientat
    t1->v= 0;
    t1->e= 0;
    while( a != NULL )
    {
        if(verif(v, a->s) == -1 )
        {
            (t1->v)++;
            v = append_node(v, a->s, a->fisier, a->dist, (t1->v)-1);
        }
        a= a->next;
    }
    
    t1->a = calloc(t1->v, sizeof(int *)); //  ALOCAREA DINAMICA A MATRICEI DE ADIACENTA PENTRU t1
    for (int i = 0; i < t1->v; i++)
        t1->a[i] = calloc(t1->v, sizeof(int));

    t1->cost = calloc(t1->v, sizeof(int *)); //  ALOCAREA DINAMICA A MATRICEI DE COSTURI PENTRU t1
    for (int i = 0; i < t1->v; i++)
        t1->cost[i] = calloc(t1->v, sizeof(int));

    train *t2; // t2 este graful orientat
    t2 = malloc(sizeof(train));
    t2->v = t1->v;

    t2->a = calloc(t2->v, sizeof(int *)); //  ALOCAREA DINAMICA A MATRICEI DE ADIACENTA PENTRU t2
    for (int i = 0; i < t2->v; i++)
        t2->a[i] = calloc(t2->v, sizeof(int));

    t2->cost = calloc(t2->v, sizeof(int *)); //  ALOCAREA DINAMICA A MATRICEI DE COSTURI PENTRU t1
    for (int i = 0; i < t2->v; i++)
        t2->cost[i] = calloc(t2->v, sizeof(int));

    int m1, m2;
    a=n;
    while (a->next != NULL)
    {
        m1 = getcode(v, a->s);
        m2 = getcode(v, a->next->s);
        if ( (strcmp(a->fisier, a->next->fisier) ) == 0)
        {
            t1->a[m1][m2] = t1->a[m2][m1] = 1;
            t1->cost[m1][m2]= t1->cost[m2][m1]= get_dist( v, a->next->s );
            t2->a[m1][m2] = 1;
            t2->cost[m1][m2]= get_dist( v, a->next->s );
        }
        a = a->next;
    }

    for (int i = 1; i < t1->v; i++) // NUMARARE MUCHII t1
        for (int k = 0; k < (t1->v) - 1; k++)
            if (i > k && t1->a[i][k] == 1)
                (t1->e)++;

    for (int i = 0; i < t2->v; i++) // NUMARARE MUCHII t2
        for (int k = 0; k < t2->v; k++)
            if (t2->a[i][k] == 1)
                (t2->e)++;

    int min= INT_MAX, max= INT_MIN;

    for(int i=0; i < t1->v ; i++)
        for(int j=0; j < t1->v ; j++)
        {
            if( t1->cost[i][j] < min && t1->cost[i][j] != 0 ) min = t1->cost[i][j];
            if( t1->cost[i][j] > max) max= t1->cost[i][j];
        }

    print_minmax(v, min, max);

    print_total(t1);

    dijkstra(t1, v, 0);

    FW(t1, v);

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

int getcode(node *cop, char *c)
{
    while( cop != NULL )
    {
        if( (strcmp(cop->s, c)) == 0 ) return cop->index;
        cop= cop->next;
    }
    return -1;
}

int get_dist(node *cop, char *c)
{
    while( cop != NULL )
    {
        if( (strcmp(cop->s, c)) == 0 ) return cop->dist;
        cop= cop->next;
    }
    return -1;
}

void print_minmax(node *a, int min, int max)
{
    FILE *f, *g;

    if( ( f= fopen("min.txt", "wt") ) == NULL )
    {
        printf("Fisierul nu a putut fi deschis.");
        exit(1);
    }

    if( ( g= fopen("max.txt", "wt") ) == NULL )
    {
        printf("Fisierul nu a putut fi deschis.");
        exit(1);
    }

    node *aux= a;
    while( a != NULL)
    {
        if( a->dist == min ) fprintf(f, "%s, %s, %d\n", aux->s, a->s, a->dist);
        if( a->dist == max ) fprintf(g, "%s, %s, %d\n", aux->s, a->s, a->dist);
        aux= a;
        a= a->next;
    }
    fclose(f);
    fclose(g);
}

void print_total(train *t)
{
    int s=0;
    for(int i=1; i < t->v ; i++)
        for(int j=0; j< (t->v)-1; j++)
            if( i>j ) s= s + t->cost[i][j];
    FILE *f;

    if( ( f= fopen("total.txt", "wt") ) == NULL )
    {
        printf("Fisierul nu a putut fi deschis.");
        exit(1);
    }
    fprintf(f, "%d", s);
}


 int min_distance(int dist[], int sps[], int v)
 {
     int i, min= INT_MAX, min_index;
     for(i= 0; i< v; i++)
        if(sps[i] == 0 && dist[i] <= min)
        {
            min= dist[i];
            min_index= i;
        }
    return min_index;
 }

void dijkstra(train *t, node *v, int s)
{
    int i, j, u;
    int *dist= malloc((t->v) * sizeof(int));
    int *sps= malloc((t->v) * sizeof(int));
    int *parent= malloc((t->v) * sizeof(int));
    for(i=0; i < t->v ; i++)
    {
        parent[0]= -1;
        dist[i]= INT_MAX;
        sps[i]= 0;
    }
    dist[s]= 0;
    for(j=0; j < (t->v)-1 ; j++)
    {
        u= min_distance(dist, sps, t->v);
        sps[u]= 1;
        for(i=0; i< t->v ; i++)
            if( (sps[i] == 0) && (t->cost[u][i] != 0) && (dist[u] != INT_MAX) && ((dist[u] + t->cost[u][i]) < dist[i]))
            {
                parent[i]= u;
                dist[i]= dist[u] + t->cost[u][i];
            }
    }
    FILE *f;
    if( ( f= fopen("ruta.txt", "wt") ) == NULL )
    {
        printf("Fisierul nu a putut fi deschis.");
        exit(1);
    }
    //prints(dist, t->v);
    printPath(v, parent, getcode(v, "Timisoara Nord"), f);
}

void printPath(node *v, int parent[], int j, FILE *f)
{
    if (parent[j] == -1)
        return;
  
    printPath(v, parent, parent[j], f);
    
    print_station(v, j, f);
}

void print_station(node *a, int i, FILE *f)
{
    while( a != NULL )
    {
        if( i == a->index )
        {
            fprintf(f, "%s\n", a->s);
            break;
        }
        a= a->next; 
    }
}

void FW(train *t, node *v)
{
    int i,j, z, m= INT_MIN;
    int **c= malloc( (t->v) * sizeof(int *) );
    for(i=0;i < t->v ; i++)
        c[i]= malloc( (t->v) *sizeof(int) );
    for(i=0 ; i < t->v ; i++)
        for(j=0 ; j < t->v ; j++)
            if( t->cost[i][j] != 0 ) c[i][j]= t->cost[i][j];
            else c[i][j]= INT_MAX;
    for(z=0 ; z < t->v ; z++)
        for(i=0 ; i < t->v ; i++)
            for(j=0 ; j < t->v ; j++)
                if( c[i][j] > c[i][z] + c[z][i] ) c[i][j]= c[i][z] + c[z][i];
    for(i=0 ; i < t->v ; i++)
        for(j=0 ; j < t->v ; j++)
            if(c[i][j] > m) m= c[i][j];
    FILE *f;
    if( ( f= fopen("drum_lung.txt", "wt"))  ==  NULL) 
    {
        printf("Fisierul nu a putut fi deschis.");
        exit(1);
    }
    for(i=0 ; i < t->v ; i++)
        for(j=0 ; j < t->v ; j++)
            if(c[i][j] == m)
            {
                print_station(v, i, f);
                print_station(v, j, f);
            }
}

void prints(int dist[], int n)
{
    for(int i=0;i<n;i++)
        printf("%d        %d\n", i, dist[i]);
}
