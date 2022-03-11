#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



typedef struct student
{
    char *nume, *prenume;
    char id[6];   //id student
    double note[5]; // aici se salveaza notele obtinute in semestrul anterior
} student;

void meniu()
{
    printf("       Meniu\n");
    printf("1. Afisare studenti.\n");
    printf("2. Creare fisier studenti restantieri.\n");
    printf("3. Stergere studenti restantieri.\n");
    printf("4. Adaugare student.\n");
    printf("5. Modificare student.\n");
    printf("0. Iesire.");
}

void afisare(student *v, int n) // functia de afisare vector studenti
{
    for(int i=0; i<n; i++)
    {
        puts(v[i].nume);
        puts(v[i].prenume);
        puts(v[i].id);
        for(int j=0; j<5; j++)
        {
            printf("%.2lf ", v[i].note[j]);
        }
        printf("\n");
        }
}

void creare_sir_static(char a[4][20], int n) // functia de creare a vectorului de string-uri; am luat din 2 fisiere datele: din fisier1.txt am luat nume
{                                            // si din fisier2.txt am luat prenume; fiecare fisier a fost completat in prealabil de mine
    FILE *f;
    char ch[10];
    for(int i=0; i<n; i++)
    {

        f=fopen("fisier1.txt", "rt"); // fisier1 -> nume
        int ok=0,j=rand()%4; // j este numarul randului din fisier
        char c=fgetc(f); // parcurg fisierul caracter cu caracter
        while(ok<j)
        {
            c=fgetc(f);
            if(c=='\n') // pana gasesc un '\n'
            {
                ok++;
            }
        }
        fscanf(f, "%[^\n]", &a[i]); // cand ok ajunge sa fie egal cu j inseamna ca am ajuns la randul j, deci pot il pot citi
        strcat(a[i]," ");
        fclose(f);
        f=fopen("fisier2.txt", "rt"); // fisier2 -> prenume
        j=rand()%4;
        ok=0;
        c=fgetc(f);
        while(ok<j)
        {
            c=fgetc(f);
            if(c=='\n')
            {
                ok++;
            }
        }
        fscanf(f, "%[^\n]", &ch);
        strcat(a[i],ch);
        fclose(f);
    }
}

void restanta(student *v, int n) // functia de creare a fisierului cu restantieri
{
    FILE *f;
    if((f=fopen("restanta.txt", "wt"))==NULL)
    {
        printf("Deschiderea fisierului a esuat!");
        exit(1);
    }
    for(int i=0; i<n; i++)
    {
        int nr=0;
        for(int j=0; j<5; j++)
            if(v[i].note[j]<5) nr++;
        if(nr>0)
        {
            fputs(v[i].id, f);
            fprintf(f, "\n");
            fputs(v[i].nume, f);
            fprintf(f, "\n");
            fputs(v[i].prenume, f);
            fprintf(f, "\n");
            fprintf(f, "%d\n", nr);
        }
    }
    fclose(f);
}

student *sterge(student *v, int * n) // functia de stergere studenti restantieri
{
    for(int i=0; i<*n; i++)
    {
        int k=0;
        for(int j=0; j<5; j++)
            if(v[i].note[j]<5)
            {
                k++;
                break;
            }
        if(k>0)
        {
            for(int j=i; j<(*n)-2; j++)
                v[j]=v[j+1];
            i--;
            (*n)--;
        }
    }
    v=(student *)realloc(v, (*n) * sizeof(student));
    return v;
}

student *adauga(student *v, int  *n) // functia de adugare studenti
{
    int p;
    printf("Pe ce pozitie doriti sa adaugati studentul?\n");
    scanf("%d", &p);
    fflush(stdin);
    (*n)++;
    v=realloc(v, (*n) * sizeof(student));
    if(v==NULL)
    {
        printf("Alocarea memoriei a esuat.");
        exit(1);
    }
    for(int i=(*n)-1; i>p; i--)
        v[i]=v[i-1];
    printf("Completati detaliile studentului:\n\n");
    printf("Nume: "); gets(v[p].nume);
    printf("Prenume: "); gets(v[p].prenume);
    printf("Id: "); gets(v[p].id);
    printf("Note: "); for(int i=0;i<5;i++) scanf("%lf", &v[p].note[i]);
    return v;
}

student * modificare(student *v,int n) // functia de modificare a unui student
{
    int i;
    char q[6];
    printf("Ce ID doriti sa modificati?\n");
    gets(q);
    fflush(stdin);
    for(i=0;i<n;i++)
        if((strcmp(q,v[i].id))==0) break;
    if(i==n-1) return v;
    printf("Completati detaliile studentului:\n\n");
    printf("Nume: "); gets(v[i].nume);
    printf("Prenume: "); gets(v[i].prenume);
    for(int j=0;j<6;j++)
            v[i].id[j]=(char)(48+rand()%10);
    for(int j=0; j<5; j++)
        {
            v[i].note[j]= 4 + rand()%5 + (double)(rand()%101)/100;
        }
    return v;
}

int main()
{
    unsigned seed=time(0);
    srand(seed);
    student *v;
    int n;
    printf("Introduceti numarul de studenti(nu mai mare de 4): ");
    scanf("%d",&n);
    fflush(stdin);
    v=malloc(n*sizeof(student));
    if(v==NULL)
    {
        printf("Alocarea memoriei a esuat.");
        exit(1);
    }
    char a[4][20];
    creare_sir_static(a,n);
    for(int i=0;i<n;i++)
    {
        int ok=0;
        char *p;
        p=strtok(a[i]," ");
        while(p)
        {
            if(ok==0) // primul cuvant de pe fiecare rand este numele
            {
                v[i].nume=malloc(strlen(p)*sizeof(char));
                strcpy(v[i].nume,p);
                ok++;
            }
            else // al doilea este prenumele
            {
                v[i].prenume=malloc(strlen(p)*sizeof(char));
                strcpy(v[i].prenume,p);
            }
            p=strtok(NULL," ");
        }
        for(int j=0;j<6;j++)
            v[i].id[j]=(char)(48+rand()%10); // am generat random id-uri de 6 cifre
        for(int j=0; j<5; j++)
        {
            v[i].note[j]= 4 + rand()%5 + (double)(rand()%101)/100; // am generat random note
        }
    }

    int k=-1;
    do
    {
        system("cls");
        meniu();
        printf("\n\nAlegeti o optiune: ");
        scanf("%d",&k); fflush(stdin);
        switch(k)
        {
            case 1:
                {
                    afisare(v,n);
                    break;
                }
            case 2:
                {
                    restanta(v,n);
                    break;
                }
            case 3:
                {
                    v=sterge(v,&n);
                    break;
                }
            case 4:
                {
                    v=adauga(v,&n);
                    break;
                }
            case 5:
                {
                    v=modificare(v,n);
                    break;
                }
            case 0: return 0;
            default:
                {
                    printf("Alegeti o optiune valida.");
                    break;
                }
        }
        printf("\n\nTastati ENTER pentru a reveni la meniu.");
        getchar();
    }while(k!=0);
}
