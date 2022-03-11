#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack_node{

	char val;
	struct stack_node *next;
} stack_node;


typedef struct stack{
    struct stack_node *head;
}stack;



typedef struct tree{
    char c;
    struct tree *left, *right;
}tree;


tree *create_tree()
{
    tree *t= NULL;
    t= malloc(sizeof(tree));
    t->left= t->right= NULL;
    return t;
}

tree *create_tree_node(char c)
{
    tree *n= NULL;
    n= malloc(sizeof(tree));
    n->c=c;
    n->left= n->right= NULL;
}

stack *create_stack()
{
    stack *st= NULL;
    st= malloc(sizeof(stack));
    st->head= NULL;
    return st;
}


stack_node *create_stack_node(char val)
{
	stack_node *node = NULL;

	node= malloc(sizeof(stack_node));
	node->next = NULL;
	node->val= val;

	return node;
}

void stack_push(stack *stack, char val)
{
	stack_node *node = NULL;

	node= create_stack_node(val);
	node->next= stack->head;
	stack->head= node;
}

char stack_pop(stack *st)
{
	if( st->head == NULL ) return -1;
	char val;
	stack_node *p= st->head;
	val= (st->head)->val;
	st->head= (st->head)->next;
	free(p);

	return val;
}

void print_tree(tree *root){
     if( root!=NULL){
          print_tree(root->left);
          print_tree(root->right);
          printf("%c ", root->c);
     }
}

int main()
{
    tree *root;
    stack *sr, *so;
    root= create_tree();
    sr= create_stack();
    so= create_stack();
    char s[10];
    scanf("%s", &s);
    for(int i=0;i<strlen(s);i++)
        if(s[i] == '+' || s[i] == '*')
            stack_push(so, s[i]);
        else stack_push(sr, s[i]);
    stack_node *p= so->head;
    tree *r = NULL;
    while(p)
    {
        if(p->val == '*')
        {
            char c1, c2;
            c1= stack_pop(sr);
            c2= stack_pop(sr);
            r= malloc(sizeof(tree));
            r->c= '*';
            r->left= create_tree_node(c1);
            r->right= create_tree_node(c2);
        }
        else if(p->val == '+' )
        {
            r= malloc(sizeof(tree));
            r->left= 
        }
    }
    return 0;
}