#include "f.h"
#include "f.c" // nu stiu exact de ce, dar nu imi functioneaza codul fara sa includ si fisierul cu functii

int n1,n2;

int main()
{
    int a=-1;
    do
    {

        meniu();
        printf("\nAlegeti o cerinta: "); scanf("%d",&a);
        fflush(stdin);
        switch(a)
        {
        case 1:
            {
                int v1[20], v2[20]; // EX 1
                for(int i=0;i<20;i++)
                {
                    v1[i]=1+rand()%99;
                    v2[i]=v1[i];
                }
                selectionsort(v1,20,&n1);
                afisare(v1,20);
                printf("%d\n",n1);
                quicksort(v2,0,19, &n2);
                afisare(v2,20);
                printf("%d",n2);
                break;
            }
        case 2:
            {
                char **c; // EX 2
                char a[4];
                int n;
                printf("Introduceti numarul de cuvinte: ");
                            scanf("%d", &n);
                c=malloc(n*sizeof(char *));
                printf("\nIntroduceti cuvintele:\n");
                for(int i=0;i<n;i++)
                {
                    fflush(stdin);
                    printf("Cuvantul %d: ", i+1);
                    scanf("%s",&a);
                    c[i]=malloc(strlen(a)*sizeof(char));
                    printf("\n");
                    strcpy(c[i],a);
                }
                selectionsortcuvinte(c,n);
                for(int i=0;i<n;i++)
                    puts(c[i]);
                break;
            }
        case 3:
            {
                timp *v; //EX 3
                printf("Introduceti numarul de momente de timp: ");
                int nr;
                scanf("%d", &nr);
                fflush(stdin);
                v=malloc(nr*sizeof(timp));
                printf("\nIntroduceti momentele de timp");
                for(int i=0;i<nr;i++)
                {
                    printf("\n\nMomentul %d\n", i);
                    printf("Ora: "); scanf("%d",&v[i].ora);
                    printf("Minutul: "); scanf("%d",&v[i].minut);
                    printf("Secunda: "); scanf("%d",&v[i].secunda);
                    printf("\n");
                }
                quicksorttimp(v,0,nr-1);
                for(int i=0;i<nr;i++)
                {
                    printf("Momentul %d de timp este %d:%d:%d\n", i+1, v[i].ora, v[i].minut, v[i].secunda);
                }
                break;
            }
        case 4:
            {
                int *v,nn; // EX 4
                printf("Introduceti numarul de elemente al vectorului: ");
                scanf("%d", &nn);
                v=malloc(nn*sizeof(int));
                sortfrecventa(v,nn);
                printf("Vectorul sortat este: ");
                for(int i=0;i<nn;i++)
                    printf("%d ", v[i]);
                break;
            }
        case 0:
            {
                return 0;
            }
        default:
            {
                printf("Alegeti o optiune valida.");
                break;
            }
        }
        fflush(stdin);
        printf("\n\nTastati ENTER pentru a reveni la meniu.\n\n");
        getchar();
        system("cls");
    }
    while(a!=0);
}
