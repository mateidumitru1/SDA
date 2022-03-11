#include "ex1.h"


int main()
{
    stack *stack;
    FILE *f;
    if( ( f= fopen("input.txt", "rt") ) == NULL )
    {
        printf("Fisierul nu a putut fi deschis.");
        exit(1);
    }
    stack= stack_create();
    char c[16];
    while( fscanf(f, "%s", c) == 1 )
    {
        stack_push(stack, c);
    }
    fclose(f);
    stack_print(stack);
    /*if( ( f= fopen("output.txt", "wt") ) == NULL )
    {
        printf("Fisierul nu a putut fi deschis.");
        exit(1);
    }
    stack_print(stack);
    stack_node *p= stack->head;
    while ( p != NULL )
    {
        fprintf(f, "%s ", stack_pop(stack) );
        p= p->next;
        stack_print(stack);
    }
    fclose(f);*/
    return 0;
}

stack *stack_create()
{
	stack *stack = NULL;
	stack= malloc(sizeof(stack));
	if( stack == NULL ) return NULL;
	stack->length= 0;
	stack->head= NULL;
	return stack;
}

stack_node *stack_node_create(char c[])
{
    stack_node *node= NULL;
    node= (stack_node *)malloc(sizeof(stack_node *));
    node->next= NULL;
    node->cuv= malloc(strlen(c));
    strcpy( node->cuv, c );
    return node;
}

void stack_push(stack *stack, char c[])
{
    stack_node *node= NULL;
    (stack->length)++;
    node= stack_node_create(c);
    node->next= stack->head;
    stack->head= node;
}

char *stack_pop(stack *stack)
{
    stack_node *p= stack->head;
    char *cuv;
    cuv= malloc( strlen(p->cuv) );
    strcpy( cuv, p->cuv );
    stack->head= p->next;
    free(p);
    (stack->length)--;
    return cuv;
}

void stack_print(stack *stack)
{
    FILE *f;
    if( ( f= fopen("output.txt", "wt") ) == NULL )
    {
        printf("Fisierul nu a putut fi deschis.");
        exit(1);
    }
	stack_node *p= stack->head;
	while( p != NULL )
	{
		fprintf(f, "%s ", p->cuv);
		p= p->next;
	}
    fclose(f);
	fprintf(f,"\n");

}
