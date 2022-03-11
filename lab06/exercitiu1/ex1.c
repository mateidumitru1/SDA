#include "ex1.h"

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
    //   Creare arbore
    node *root= create_tree(v, 0, n-1);
    inorder(root);

    //   Verificare arbore
    if( ver(root) == 1 ) printf("\nArborele este BST.\n");
    else printf("\nArborele nu este BST.\n");

    //   Cautare valoare random
    int val= 1 + rand() % 100;
    printf("\n\nValoarea generata aleator este %d", val);
    printf("\n");
    node *p= search_tree(root, val);
    if(p != NULL) printf("Valoarea a fost gasita.");
    else printf("Valoarea NU a fost gasita.");


    printf("\n\n");

    //   Inserare valori
    root= insert(root, rand()%100);
    root= insert(root, rand()%40);
    inorder(root);


    printf("\n\n\n");

    //   Stergere valori
    root= delete(root, 17);
    inorder(root);
    printf("\n");
    return 0;
}

node *create_node(int data)
{
    node *a = malloc(sizeof(node));
    a->data = data;
    a->left = a->right = NULL;
    return a;
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

node *create_tree(int *v, int p, int u)
{
    if(p > u) return NULL;
    int m= (p + u)/2;
    node *root = create_node(v[m]);
    root->left = create_tree(v, p, m-1);
    root->right = create_tree(v, m+1, u);
    return root;
}

void inorder(node *n)
{
    if(n == NULL) return;
    
    inorder(n->left);
    printf("%d ", n->data);
    inorder(n->right);
}

void preorder(node *n)
{
    if(n == NULL) return;
    printf("%d ", n->data);
    preorder(n->left);
    preorder(n->right);
}

int ver(node *n)
{
    if( n == NULL )
        return 1;
    if( n->left != NULL && n->data < (n->left)->data) return 0;
    if( n->right != NULL && n->data > (n->right)->data) return 0;
    if( ver(n->left) != 0 || ver(n->right) != 0) return 0;
    return 1;
}

node *search_tree(node *n, int data)
{
    if(n == NULL || n->data == data) return n;
    if(n->data < data ) return search_tree(n->right, data);
    return search_tree(n->left, data);
}

node *insert(node *n, int data)
{
    if(n == NULL) return create_node(data);
    if(data < n->data ) n->left= insert(n->left, data);
    else if(data > n->data) n->right= insert(n->right, data);
    return n;
}

node *delete(node *n, int data)
{
    if(n == NULL) return n;
    if(data < n->data ) n->left= delete(n->left, data);
    else if(data > n->data) n->right= delete(n->right, data);
    else{
        if(n->left == NULL)
        {
            node *aux= n;
            n= n->right;
            free(aux);
            return n;
        }
        else if(n->right == NULL){
            node *aux= n;
            n= n->left;
            free(aux);
            return n;
        }
        node *aux= minvaluenode(n->right);
        n->data= aux->data;
        n->right= delete(n->right, aux->data);
    }
    return n;
}

node *minvaluenode(node *n)
{
    node *a= n;
    while(a->left != NULL)
        a= a->left;
    return a;
}
