#include <stdio.h>
#include <stdlib.h>

int bancnote(int s)
{
    int v[5]={1, 5, 10, 50, 100};
    int nr=0, i=4;
    for(int i=4;i>=0;i--)
    {
        nr= nr + (s / v[i]);
        s= s % v[i];
    }
    return nr;
}

int main()
{
    int s;
    s= 78;
    printf("Numarul de bancnote necesare pentru suma %d este %d.\n", s, bancnote(s));
    return 0;   
}
