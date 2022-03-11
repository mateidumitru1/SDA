#include "ex2.h"


int main()
{
    int n;
    stack *stackp;
    stackp= stack_create();
    printf("\nIntroduceti dimensiunea sirului: "); scanf("%d", &n);
    for(int i=0;i<n;i++)
        stack_push(stackp, rand() % 200 - 100 );
    printf("\nElementele stivei initiale sunt: ");
    stack_print(stackp);
    stack *poz, *neg;
    poz= stack_create();
    neg= stack_create();
    for(int i=0;i<n;i++)
    {
        int val= stack_pop(stackp);
        if( val < 0 )
            stack_push( neg, val );
        else stack_push( poz, val );
    }
    printf("\nElementele pozitive sunt: ");
    stack_print(poz);
    printf("\nElementele negative sunt: ");
    stack_print(neg);
    printf("\n");
    return 0;
}

stack *stack_create()
{
    stack *stack;
    stack= malloc(sizeof(stack));
	if( stack == NULL ) return NULL;
	stack->length= 0;
	stack->head= NULL;
    return stack;
}

stack_node *stack_node_create(int val)
{
    stack_node *node = NULL;
	node= malloc(sizeof(stack_node));
	node->next = NULL;
	node->val= val;

	return node;
}

void stack_push(stack *stack, int val)
{
    stack_node *node = NULL;
	(stack->length)++;
	node= stack_node_create(val);
	node->next= stack->head;
	stack->head= node;
}

void stack_print(stack *stack)
{
    stack_node *p= stack->head;
	while( p != NULL )
	{
		printf("%d ", p->val);
		p= p->next;
	}
	printf("\n");
}

int stack_pop(stack *stack)
{
	if( stack->head == NULL ) return INT_MIN;
	int val = 0;
	stack_node *p= stack->head;
	val= (stack->head)->val;
	stack->head= (stack->head)->next;
	free(p);
	(stack->length)--;

	return val;
}
