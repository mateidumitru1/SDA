#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * TASK 1.
 *
 * Completati structura din fisierul header.
 */

int main()
{	
	printf("Lab 2 - Liste inlantuite.\n\n");
	
	/**************************************************************************
	 * Test Task 2.
	 * Creati un nod cu o anumita valoare.
	 * Afisati valoarea la stdout.
	 */
	node_t *node= NULL;

	/* ... your code comes here ... */
	int val= 1+ rand() % 100;
	node= create(val);

	printf("%d\n\n", node->val);



	/**************************************************************************
	 * Test Task 3.
	 *
	 * Creati o variabila de tip 'node_t' cu numele 'head'.
	 * Ea va reprezenta capul listei cu care veti lucra mai jos.
	 *
	 * Adaugati 5-6 noduri cu valori diferite la final listei.
	 * Aveti un exemplu.
	 */

	/* ... some cool code... */
	node_t *head= NULL;

	head = append_node(head, 42); /* Raspunsul universal :). */
	/* ... more badass code ... */
	for(int i=0;i<6;i++)
		head = append_node(head, 1+ rand() % 30);

	/**************************************************************************
	 * Test Task 4.
	 */
	print_list(head);
	
	/**************************************************************************
	 * Test Task 5.
	 */

	int v= 1+ rand() % 150;
	head= prepend_node(head, v);
	print_list(head);

	/* ... in a galaxy far far away ... */

	/**************************************************************************
	 * Test Task 6.
	 */

	node_t *t;
	t=get_node(head, v);

	if(t != NULL) printf("%d\n", t->val);
	else printf("Nu a fost gasit.\n");

	/**************************************************************************
	 * Test Task 7.
	 */

	int new= 1+ rand() % 60;
	node_t *a;
	a= modify_node(head, v, new);

	if(t != NULL) print_list(head);
	else printf("Nu a fost gasit. Lista a ramas neschimbata.\n");

	/**************************************************************************
	 * Test Task 8.
	 */

	int after_val= 1+ rand() % 1000;
	node_t *q= insert_node(head, 24, after_val);
	print_list(head);


	/**************************************************************************
	 * Test Task 9.
	 */

	head = remove_node(head, 24);
	print_list(head);

	return 0;
}

/**
 * TASK 2.
 *
 * Functia primeste o valoare, creeaza un nou nod cu aceasta
 * valoare si returneaza un pointer catre nodul creat.
 */
node_t *create(int val)
{
	node_t *node=NULL;
	node=malloc(sizeof(node_t));
	node->val=val;
	node->next=NULL;
	return node;
}


/**
 * TASK 3.
 *
 * Functia creaza un nou nod cu valoarea 'val' 
 * si il adauga la finalul listei.
 *
 * Functia returneaza noul cap al listei (daca e cazul), sau vechiul.
 */
node_t *append_node(node_t *list_head, int val)
{
	node_t *a= list_head, *c= list_head;
	node_t *n;
	n=malloc(sizeof(node_t));
	n->val= val;
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

/**
 * TASK 4.
 *
 * Functia afiseaza la stdout continutul listei.
 * Valorile sunt separate prin virgula.
 */
void print_list(node_t *list_head)
{
	node_t *p= list_head;
	while(p!=NULL)
	{
		printf("%d ", p->val);
		p=p->next;
	}
	printf("\n");
}

/**
 * TASK 5.
 *
 * Functia creaza un nou nod cu valoarea 'val' 
 * si il adauga la inceputul listei.
 *
 * Functia returneaza noul cap al listei.
 */
node_t *prepend_node(node_t *list_head, int val)
{
	node_t *n;
	n=malloc(sizeof(node_t)); 
	n->val= val;
	n->next= list_head;
	return n;
}

/**
 * TASK 6.
 *
 * Functia primeste un numar intreg si cauta in lista acest numar.
 * Daca gaseste numarul in lista, returneaza nodul care il contine.
 * Daca nu il gaseste returneaza NULL.
 * Daca elementul apare de mai multe ori, se returneaza prima aparitie.
 */
node_t *get_node(node_t *list_head, int val)
{
	node_t *a= list_head;
	while(a != NULL)
	{
		if(a->val == val) return a;
		a=a->next;
	}
	return NULL;
}

/**
 * TASK 7.
 *
 * Functia cauta valoarea 'val' in lista si daca gaseste un element
 * cu aceasta valoare o schimba cu 'new_val'.
 *
 * Functia returneaza un pointer catre acest element, sau
 * NULL daca nodul nu exista.
 */
node_t *modify_node(node_t *list_head, int val, int new_val)
{
	node_t *t=get_node(list_head, val);
	if(t != NULL)
	{
		t->val = new_val;
		return t;
	}
	return NULL;
}

/**
 * TASK 8.
 *
 * Functia creaza un nod nou cu valoarea 'after_val' si il 
 * insereaza dupa nodul cu valoarea 'val'. 
 * Se returneaza un pointer catre nodul nou creat.
 *
 * Daca nodul cu valoarea 'val' nu exista in lista, lista
 * ramane nemodificata si se returneaza capul listei.
 */
node_t *insert_node(node_t *list_head, int val, int after_val)
{
	node_t *a;
	a= get_node(list_head, val);
	while(a != NULL)
	{
		node_t *p;
		p=malloc(sizeof(node_t));
		p->next= a->next;
		a->next= p;
		p->val= after_val;
		return p;
	}
	return list_head;
}


/**
 * TASK 9.
 *
 * Functia cauta nodul cu valoarea 'val' si il sterge din lista.
 * Functia returneaza noul cap al listei (daca e cazul), sau vechiul.
 *
 * Daca nodul cu valoarea 'val' nu exista in lista, lista
 * ramane nemodificata si se returneaza capul listei.
 */
node_t *remove_node(node_t *list_head, int val)
{
	if(list_head == NULL) return NULL;
	if(list_head->val == val)
	{
		node_t *s= list_head;
		list_head= list_head->next;
		free(s);
		return list_head;
	}
	node_t *a= list_head, *c= list_head;
	while(a != NULL)
	{
		if(a->val != val)
		{
			c= a;
			a= a->next;
		}
		else
		{
			c->next = a->next;
			free(a);
			return list_head;
		}
	}
}
