#include "ex1.h"

int main()
{
    angajati *head= NULL;
    head= creare(head);
    for(int i=0;i<5;i++)
        head= creare(head);

    head= adauga3(head);

    head= adauga_dupa_mecanic(head);

    head= sterge_nrtel(head);
    printlist(head);
    return 0;
}

angajati *creare(angajati *head)    //              **** CREARE LISTA ****
{
    angajati *a= head;
    angajati *x;
    x= malloc(sizeof(angajati));
    printf("\nIntroduceti numele angajatului: "); fgets(x->nume, 31, stdin);
    printf("Introduceti numarul de telefon: "); fgets(x->nrtel, 11, stdin);
    printf("Introduceti postul angajatului: "); fgets(x->post, 21, stdin);
    fflush(stdin);
    if(head == NULL)
    {
        x->next= x;
        x->prev= x;
        head= x;
    }
    else
    {
        a= head->prev;
        x->next= head;
        x->prev= a;
        head->prev= x;
        a->next= x;
    }
    return head;
}

void printlist(angajati *head)
{
    int i=0;
    angajati *p= head;
    while(p->next != head)
	{
        printf("Angajatul %d: \n", i+1);
		printf("Nume: "); puts(p->nume);
        printf("Numar de telefon: "); puts(p->nrtel);
        printf("Post: "); puts(p->post);
		p=p->next;
        i++;
    }
    printf("Angajatul %d: \n", i+1);
	printf("Nume: "); puts(p->nume);
    printf("Numar de telefon: "); puts(p->nrtel);
    printf("Post: "); puts(p->post);
    /*while(p->prev != head)                **** AFISARE in directie inversa pt verificare ****
	{
        printf("Angajatul %d: \n", i+1);
		printf("Nume: "); puts(p->nume);
        printf("Numar de telefon: "); puts(p->nrtel);
        printf("Post: "); puts(p->post);
		p=p->prev;
        i++;
    }
    printf("Angajatul %d: \n", i+1);
	printf("Nume: "); puts(p->nume);
    printf("Numar de telefon: "); puts(p->nrtel);
    printf("Post: "); puts(p->post);*/
}

angajati *adauga3(angajati *head)                        // **** CERINTA 1 ****
{
    angajati *a= head, *c= head;
    angajati *x;
    x=malloc(sizeof(angajati));
    printf("\nIntroduceti numele noului angajat: "); fgets(x->nume, 31, stdin);
    printf("Introduceti numarul de telefon: "); fgets(x->nrtel, 11, stdin);
    printf("Introduceti postul noului angajat: "); fgets(x->post, 21, stdin);
    fflush(stdin);
    int i=0;
    while(i<3)     // Parcurg lista pentru a gasi al treilea angajat
    {
        c= a;
        a= a->next;
        i++;
    }
    x->prev= c;    // Adaug noul angajat dupa cel de-al treilea din lista
    x->next= a;
    c->next= x;
    a->prev= x;
    return head;
}

angajati *adauga_dupa_mecanic(angajati *head)             // **** CERINTA 2 ****
{
    angajati *a= head, *c= head->prev;
    angajati *x;
    x=malloc(sizeof(angajati));
    printf("\nIntroduceti numele noului angajat: "); fgets(x->nume, 31, stdin);
    printf("Introduceti numarul de telefon: "); fgets(x->nrtel, 11, stdin);
    printf("Introduceti postul noului angajat: "); fgets(x->post, 21, stdin);
    fflush(stdin);
    while( a->next != head)
    {
        if( ( strcmp(a->post, "mecanic\n") ) == 0 ) break; //  Daca gaseste vreun mecanic iese din while
        c= a;                                              //  Daca nu gaseste, atunci cand se termina while-ul a are valoarea ultimului angajat din lista
        a= a->next;                                       
    }
    if( ( strcmp(a->post, "mecanic\n") ) != 0)             // Daca nici aici nu gaseste vreun mecanic, adaug noul angajat la finalul listei
    {
        printf("\nNu a fost gasit niciun mecanic. Noul angajat a fost adaugat la final.\n");
        a= head->prev;
        x->next= head;
        x->prev= a;
        head->prev= x;
        a->next= x;
    }
    else
    {
        printf("\nNoul angajat a fost adaugat cu succes.\n");// Altfel(a gasit mecanic) adaug noul angajat inainte de mecanic
        c->next= x;
        x->prev= c;
        a->prev= x;
        x->next= a;
    }
    return head;
}


angajati *sterge_nrtel(angajati *head)                     // **** CERINTA 3 ****
{
    char nrtel[11];
    printf("\nIntroduceti numarul de telefon al angajatului pe care doriti sa il stergeti din lista: "); fgets(nrtel, 11, stdin);
    angajati *a= head, *c= head->prev;
    while( a->next != head )
    {
        if( (strcmp(a->nrtel, nrtel) ) == 0 ) break;        // Daca gaseste nr de telefon iese din while
        c= a;                                               // Daca nu il gaseste, dupa ce iese din while verifica si pt ultimul angajat
        a= a->next;
    }
    if( (strcmp(a->nrtel, nrtel) ) == 0 )                   // Daca il gaseste, il sterge
    {
        c->next= a->next;
        a->next->prev= c;
        if(a == head) head= c->next;                        // Daca angajatul care trebuie sters este head, schimb head-ul
        free(a); 
        printf("\nAngajatul a fost sters cu succes.\n\n");
    }
    else printf("\nAngajatul nu a fost gasit.\n\n");        // Daca nu il gaseste nu se intampla nimic.
    return head;
}