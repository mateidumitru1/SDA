#include <stdio.h>
#include <stdlib.h>

int bancnote(int s)
{
    int v[7]={1, 3, 5, 15, 30, 50, 150};
    int nr=0, i=6;
    while( s > 0 )
    {
        while( s - v[i] < 0 ) i--;
        s= s - v[i];
        nr++;
    }
    return nr;
}

int main()
{
    int s;
    s= 90;  // Ar trebui ca rezultatul sa fie 3 (3 bancnote de 30), insa, datorita algoritmului, prima bancnota luata este una de 50, apoi una de 30 si in final
    printf("Numarul de bancnote necesare pentru suma %d este %d.\n", s, bancnote(s));  // doua de 5.
    return 0;   
}
