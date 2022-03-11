#include "f.h"

void meniu()
{
    printf("                               MENIU\n");
    printf("\n1. Alegeti un algoritm A (am ales Selection) si un algoritm B (am ales\n");
    printf("Quicksort). Introduceti niste variabile globale cu care sa contorizati\n");
    printf("numarul de comparatii pentru algoritmii A si B. Comparati rezultatele\n");
    printf("pentru un vector de intregi de lungime 20.\n");
    printf("\n2. Implementati un algoritm(am ales Selection) pentru sortarea unui vector\n");
    printf("cu n cuvinte de maxim 4 litere fiecare.\n");
    printf("\n3. Implementati un algoritm(am ales Quicksort) pentru sortarea unui vector\n");
    printf("de structuri, unde fiecare structura reprezinta un moment de timp(ora, min, sec).\n");
    printf("\n4. Se da un vector de n intregi, iar toate valorile din vector sunt intre 0 si\n");
    printf("1000. Sortati vectorul in timp O(n).\n");
    printf("\n0. Iesire.\n\n\n");
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void selectionsort(int v[], int n, int *n1)
{
    int i, j, min, minPoz;
    for(i =0; i<n-1; i++)
    {
        minPoz = i;
        min = v[i];
        for(j =i+1; j<n; j++)
        {
            (*n1)++;
            if(min > v[j])
            {
                minPoz = j;
                min = v[j];
            }
        }
        swap(&v[i],&v[minPoz]);
    }
}

int partition(int v[], int p, int u, int *n2)
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

void quicksort(int v[], int p, int u, int *n2)
{
    (*n2)++;
    if(p<u)
    {
        int m=partition(v,p,u,n2);
        quicksort(v,p,m-1,n2);
        quicksort(v,m+1,u,n2);
    }
}

void afisare(int v[], int n)
{
    for(int i=0; i<n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void swapcuv(char *v1, char *v2)
{
    char *aux;
    aux=malloc(strlen(v1)*sizeof(char));
    strcpy(aux, v1);
    strcpy(v1, v2);
    strcpy(v2, aux);
}

void *selectionsortcuvinte(char **v, int n)
{
    int i, j, minPoz;
    char min[4];
    for(i=0; i<n-1; i++)
    {
        minPoz = i;
        strcpy(min, v[i]);
        for(j =i+1; j<n; j++)
        {
            if((strcmp(min, v[j]))>0)
            {
                minPoz = j;
                strcpy(min, v[j]);
            }
        }
        swapcuv(v[i],v[minPoz]);
    }
}

void swaptimp(timp *v1, timp *v2)
{
    timp aux;
    aux=*v1;
    *v1=*v2;
    *v2=aux;
}

int partitiontimp(timp *v, int p, int u)
{
    timp q=v[u];
    int i=p-1;
    for(int j=p; j<u; j++)
        if(v[j].ora<q.ora)
        {
            i++;
            swaptimp(&v[i],&v[j]);
        }
        else if(v[j].ora==q.ora && v[j].minut<q.minut)
        {
            i++;
            swaptimp(&v[i],&v[j]);
        }
        else if(v[j].ora==q.ora && v[j].minut==q.minut && v[j].secunda<q.secunda)
        {
            i++;
            swaptimp(&v[i],&v[j]);
        }
    swaptimp(&v[i+1], &v[u]);
    return (i+1);
}

void quicksorttimp(timp *v, int p, int u)
{
    if(p<u)
    {
        int m=partitiontimp(v,p,u);
        quicksorttimp(v,p,m-1);
        quicksorttimp(v,m+1,u);
    }
}

void sortfrecventa(int *v, int n)
{
    int vf[1001]={0};
    printf("Introduceti elementele vectorului: ");
    for(int i=0; i<n; i++)
    {
        scanf("%d",&v[i]);
        vf[v[i]]++;
    }
    int i=0,j=0;
    while(i<n)
    {
        while(vf[j]!=0)
        {
            v[i]=j;
            i++;
            vf[j]--;
        }
        j++;
    }
}
