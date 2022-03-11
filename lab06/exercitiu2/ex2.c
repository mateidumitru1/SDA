#include "ex2.h"

int main()
{
    int n;
    int *v;
    printf("Introduceti numarul de elemente: ");
    scanf("%d", &n);
    v= malloc(n * sizeof(int));
    FILE *f;
    if( (f= fopen("input.txt", "rt")) == NULL )
    {
        printf("Fisierul nu a putut fi deschis.");
        exit(1);
    }
    for(int i=0; i<n; i++)
        fscanf(f, "%d", &v[i]);
    fclose(f);
    quicksort(v, 0, n-1);
    node *root;
    for(int i=0; i<n;i++)
        root= insert(root, v[i]);
    inorder(root);
    return 0;
}

void swap(int *a, int *b)
{
    int aux= *a;
    *a= *b;
    *b= aux;
}

int partition(int v[], int p, int u)
{
    int q=v[u];
    int i=p-1;
    for(int j=p; j<u; j++)
    {
        if(v[j]<q)
        {
            i++;
            swap(&v[i],&v[j]);
        }
    }
    swap(&v[i+1], &v[u]);
    return (i+1);
}

void quicksort(int v[], int p, int u)
{
    if(p<u)
    {
        int m=partition(v,p,u);
        quicksort(v,p,m-1);
        quicksort(v,m+1,u);
    }
}

int max(int a, int b)
{
    if(a > b) return a;
    else return b;
}

node *rightrotation(node *z)
{
    node *y= z->left;
    node *t= y->right;
    y->right= z;
    z->left= t;
    // z->height= max((z->left)->height, (z->right)->height)+1;  IMI DA SEGMENTATION FAULT LA (z->left)->height si nu stiu de ce
    z->height= max((y->left)->height, (y->left)->height)+1;
    return y;
}

node *leftrotation(node *z)
{
    node *y= z->right;
    node *t= y->left;
    y->left= z;
    z->right= t;
    z->height= max((z->left)->height, (z->right)->height)+1;
    z->height= max((y->left)->height, (y->right)->height)+1;
    return y;
}

node *lrrotation(node *z)
{
    z->left= leftrotation(z->left);
    return rightrotation(z);
}

node *rlrotation(node *z)
{
    z->right= rightrotation(z->right);
    return leftrotation(z);
}

node *create_node(int data)
{
    node *a = malloc(sizeof(node));
    a->data = data;
    a->height= 0;
    a->left = a->right = NULL;
    return a;
}

node *insert(node *n, int data)
{
    if(n == NULL)
    {
        n= malloc(sizeof(node));
        n->data = data;
        n->height= 0;
        n->left = n->right = NULL;
        return n;
    }
    if(data < n->data) n->left= insert(n->left, data);
    else if(data > n->data) n->right= insert(n->right, data);
    else return n;

    n->height= 1+ max((n->left)->height, (n->right)->height);
    int k= ((n->left)->height - (n->right)->height);

    if(k > 1 && data < (n->left)->data) return rightrotation(n);
    if(k < -1 && data > (n->right)->data) return leftrotation(n);
    if(k < -1 && data < (n->right)->data) return lrrotation(n);
    return n;
}

void inorder(node *n)
{
    if(n == NULL) return;
    
    inorder(n->left);
    printf("%d ", n->data);
    inorder(n->right);
}
