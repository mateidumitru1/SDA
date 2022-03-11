#include "trains.h"

int main()
{
    FILE *f, *g;

    if( (f= fopen("_all_files.txt", "rt")) == NULL )
    {
        printf("Fisierul nu a putut fi deschis.\n");
        exit(1);
    }

    char c[15];
    node *n= NULL;
    while ( (fscanf(f, "%[^\n]\n", c)) == 1 ) // CITIRE
     {
        if( (g= fopen(c, "rt") ) == NULL )
        {
            printf("Fisierul nu a putut fi deschis.\n", c);
            exit(1);
        }
        char a[30];
        while( (fscanf(g, "%[^\n]", a)) == 1 )
        {
            fgetc(g);
            n= append_node(n, a, c); 
        }
    }
    fclose(f);
    fclose(g);

    node *v= NULL;  // LISTA IN CARE APAR O SINGURA DATA STATIILE
    node *a= n;     // LISTA IN CARE SE REPETA STATIILE

    train *t1;  // t1 este graful neorientat
    t1= malloc( sizeof(train) );
    t1->v= 0;
    t1->e= 0;

    while( a != NULL )  // CREAREA LISTEI v
    {
        if( verif(v, a->s) == -1 )
        {
            v= append_node(v, a->s, a->i);
            (t1->v)++;
        }
        a= a->next;
    }

    t1->a= calloc( t1->v, sizeof(int*) );  //  ALOCAREA DINAMICA A MATRICEI DE ADIACENTA PENTRU t1
    for(int i=0; i<t1->v; i++) t1->a[i]= calloc( t1->v, sizeof(int) );

    train *t2;  // t2 este graful orientat
    t2= malloc( sizeof(train) );
    t2->v= t1->v;

    t2->a= calloc( t2->v, sizeof(int*) );  //  ALOCAREA DINAMICA A MATRICEI DE ADIACENTA PENTRU t2
    for(int i=0; i<t2->v; i++) t2->a[i]= calloc( t2->v, sizeof(int) );

    a= n;  // COPIE PENTRU PARCURGERE
    int m1, m2, nr=0, k=0;
    printf("%s", v->s);
    while( a->next != NULL )
    {
        m1= verif(v, a->s);
        m2= verif(v, a->next->s);
        if( (strcmp(a->i, a->next->i) ) == 0 )
        {
            t1->a[m1][m2]= t1->a[m2][m1]= 1;
            t2->a[m1][m2]= 1;
        }
        a= a->next;
    }
    
    for(int i=1; i<t1->v; i++)  // NUMARARE MUCHII t1
        for(int k=0; k<(t1->v)-1; k++)
            if( i>k && t1->a[i][k] == 1) (t1->e)++;

    for(int i=0; i<t2->v; i++)  // NUMARARE MUCHII t2
        for(int k=0; k<t2->v; k++)
            if(t2->a[i][k] == 1) (t2->e)++;

    write_ve(t1, t2);

    write_max(t1, v);

    find_grade(t1, v);

    BFS(t1, v, 0);


    if( ( f= fopen("DFS.txt", "wt")) == NULL  )
    {
        printf("Fisierul nu a putut fi deschis.");
        exit(1);
    }

    DFS(t1, v, 0, f);

    return 0;
}


node *create_node(char *a, char *c)
{
    node *n= NULL;
    n= malloc(sizeof(node));
    n->s= strdup(a);
    n->i= strdup(c);
    n->next= NULL;
    return n;
}

node *append_node(node *list_head, char *ch, char *i)
{
	node *a= list_head, *c= list_head;
	node *n;
	n= malloc(sizeof(node));
	n->s= strdup(ch);
    n->i= strdup(i);
	while(c!= NULL)
	{
		a=c;
		c=c->next;
	}
	if(a==NULL)
	{
		n->next= NULL;
		list_head= n;
	}
	else
	{
		a->next=n;
		n->next=NULL;
	}
	return list_head;
}

void print_list(node *list_head)
{
    FILE *f;
    f= fopen("a.txt", "wt");
	node *p= list_head;
	while( p != NULL )
	{
		fputs(p->s,f);
        puts(p->i);
		p= p->next;
	}
	printf("\n");
}

int verif(node *v, char *c)
{
    node *a= v;
    int i=0;
    while( a != NULL )
    {
        if( ( strcmp(a->s, c) ) == 0  ) return i;
        i++;
        a= a->next;
    }
    return -1;
}

void write_ve(train *t1, train *t2)
{
    FILE *f;
    if( ( f= fopen("noduri.txt","wt") ) == NULL )
    {
        printf("Fisierul nu a putut fi deschis.");
        exit(1);
    }

    fprintf(f, "%d", t1->v);  // SCRIERE NODURI
    fclose(f);

    if( ( f= fopen("muchii.txt","wt") ) == NULL )
    {
        printf("Fisierul nu a putut fi deschis.");
        exit(1);
    }

    fprintf(f, "%d %d", t1->e, t2->e);  // SCRIERE MUCHII t1 SI t2
    fclose(f);
}

void write_max(train *t1, node *a)
{
    FILE *f;
    int *v;
    int *s, m1= -999999998, m2= -999999999;
    s= calloc(t1->v, sizeof(int));
    for(int i=0; i<t1->v; i++)
    {
        for(int j=0; j<t1->v; j++) s[i]= s[i] + t1->a[i][j];
    }
    for(int i=0; i<t1->v; i++)
        if( m1 < s[i] )
        {
            m2= m1;
            m1= s[i];
        }
        else if( m2 < s[i] ) m2= s[i];
    
    for(int i=0; i<t1->v; i++)
    {
        if( s[i] == m1 )
        {
            m1= i;
        }
        if( m2 == s[i] )
        {
            m2= i;
        }
    }
    f= fopen("primul.txt", "wt");
    fclose(f);
    f= fopen("doilea.txt", "wt");
    fclose(f);
    str(a, m1, "primul.txt");
    str(a, m2, "doilea.txt");
    free(s);   
}

void find_grade(train *t, node *a)
{
    node *aux= a;
    int j=0;
    while( aux != NULL )
    {
        if( ( strstr(aux->s, "Cluj Napoca") ) ) break;
        j++;
        aux= aux->next;
    }
    int s=0;
    for(int i=0; i<t->v; i++)
        s= s+ t->a[j][i];
    
    FILE *f;

    if( (f= fopen("orasul_meu.txt", "wt")) == NULL )
    {
        printf("Fisierul nu a putut fi deschis.");
        exit(1);
    }
    fprintf(f, "%d", s);
    fclose(f);
}

void str(node *v, int index, char *s)  // printeaza numele statiei care corespunde index-ului 
{                                      // introdus ca parametru
    FILE *f;
    if( ( f= fopen(s, "at")) == NULL  )
    {
        printf("Fisierul nu a putut fi deschis.");
        exit(1);
    }
    node *a= v;
    while( a != NULL )
    {
        if( index == 0 )
        {
            fputs(a->s, f);
            break;
        }
        index--;
        a= a->next;
    }
    fclose(f);
}

int rear= -1, *q, front=0, nr= 0;

void insert(int data)
{
    rear++;
    q[rear]= data;
    nr++;
}

int removeData()
{
    nr--;
   return q[front++]; 
}

int isQueueEmpty()
{
    if(nr == 0) return 1;
    return 0;
}

int getAdjUnvisitedVertex(train *t, int vertexIndex, int *v)
{
   int i;
	
   for(i = 0; i<t->v; i++) {
      if( t->a[vertexIndex][i] == 1 && v[i] == 0)
         return i;
   }
	
   return -1;
}

void BFS(train *t, node *v, int i)
{
    FILE *f;
    if( ( f= fopen("BFS.txt", "wt")) == NULL  )
    {
        printf("Fisierul nu a putut fi deschis.");
        exit(1);
    }
    fclose(f);
    q= malloc((t->v) * sizeof(int));
    int *viz= calloc( t->v, sizeof(int) );
    viz[i]= 1;  // varful 0 e Bucuresti
    str(v, i, "BFS.txt");
    insert(i);
    int notviz;
    while( !isQueueEmpty() )
    {
        int aux= removeData();
        while( ( notviz = getAdjUnvisitedVertex(t, aux, viz) ) != -1 )
        {
            viz[notviz]= 1;
            str(v, notviz, "BFS.txt");
            insert(notviz);
        }
    }
    free(q);
    free(viz);
}

int viz[600];

void DFS(train *t1, node *v, int i, FILE *f)
{
    viz[i]= 1;
    node *aux= v;
    int k=i;
    while( aux != NULL )
    {
        if(k==0)
        {
            fputs(aux->s, f);
            break;
        }
        k--;
        aux= aux->next;
    }
    for(int j=0; j<t1->v; j++)
        if( viz[j]==0 && t1->a[i][j] == 1 )
            DFS(t1, v, j, f);
}
