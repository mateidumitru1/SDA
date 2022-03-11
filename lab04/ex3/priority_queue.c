#include "ex3.h"

int v[11];

int main()
{
    queue *q;
    q= queue_create();
    int n;
    printf("Introduceti numarul de elemente: "); scanf("%d", &n);
    for(int i=0;i<n;i++)
        queue_push(q, rand() % 200 - 101);
    queue_print(q);
	printf("Valoarea stearsa a fost: %d", queue_pop(q, v) );
	printf("\n");
    return 0;
}

queue *queue_create()
{
	queue *queue = NULL;
	queue= malloc(sizeof(queue));
	if( queue == NULL ) return NULL;
	queue->length= 0;
	queue->front= queue->rear= NULL;
	return queue;
}

queue_node *queue_node_create(int val, int v[])
{
	queue_node *node = NULL;
	node= malloc(sizeof(queue_node));
	node->next = NULL;
	node->val= val;
	node->prio= rand() % 11;
	v[node->prio]++;
	return node;
}

void queue_push(queue *q, int val)
{
	queue_node *node = NULL;
	(q->length)++;
	node= queue_node_create(val, v);
	if( q->rear == NULL )
	{
		q->rear= node;
	}
	else
	{
		(q->rear)->next= node;
		q->rear= node;
	}
	if( q->front == NULL) q->front= q->rear;
}

void queue_print(queue *q)
{
	queue_node *p= q->front;
	printf("\nElementele cozii sunt: ");
	while( p != NULL )
	{
		printf("%d ", p->val );
		p= p->next;
	}
	printf("\n");
}

int queue_pop(queue *queue, int v[])
{
	if( queue->front == NULL ) return INT_MIN;
	int val= 0;
	queue_node *p= queue->front, *a= queue->front;
	while( p!= NULL )
	{
		int m;
		for(int i=10;i>=0;i--)
			if( v[i] != 0 )
			{
				m= i;
				v[i]--;
			}
		if( p->prio == m ) break;
		a= p;
		p= p->next;
	}
	val= p->val;
	if( p == queue->front )
		queue->front= (queue->front)->next;
	else
		a->next= p->next;
	free(p);
	(queue->length)--;
	return val;
}
