#include "ex2.h"

int main()
{
    FILE *f;
    char c[15];
    printf("Introduceti numele fisierului: "); fgets(c, 16, stdin);
    while( ( strcmp(c, "ex2.in\n") ) != 0 )
    {
        printf("\nIntroduceti numele unui fisier valid: "); fgets(c, 16, stdin);   // am folosit fgets() la toata tema pentru ca imi dadea warning compilatorul la gets()
    }
    strcpy( c + strlen(c)-1, c + strlen(c) );
    if( (f=fopen(c, "rt")) == NULL )
    {
        printf("Fisierul nu a putut fi deschis.");
        exit(1);
    }

    node *head= NULL;
    int val;
    fscanf(f, "%d", &val);
    while( fscanf(f, "%d", &val) != EOF )
    {
        head= creare(head, val);
    }

    printlist(head);

    int x;
    printf("\n\nIntroduceti valoarea pe care doriti sa o stergeti: "); scanf("%d", &x);

    head= sterge(head, x);

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
        c=a;
        a=a->next;
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

node *sterge(node *head, int n)
{
    node *p= head, *a= head;
    while( a != NULL)
    {
        if( a->data == n )
        {
            p->next= a->next;
            free(a);
            printf("\nValoarea a fost stearsa cu succes.\n");
            return head;
        }
        p=a;
        a=a->next;
    }
    printf("\nValoarea nu a fost gasita.\n");
    return head;
}