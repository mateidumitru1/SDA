#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float lg(int nr, int er)
{
    int a=0;
    int aux= nr;
    while(aux>0)
    {
        aux= aux / 10;
        a++;
    }
    float n= --a;

    float i = 0.1;
    for (int j = 0; j < er; j++)
    {
        while (pow(10, n) <= nr) n= n + i;
        n = n - i;
        i = i / 10;
    }

    return n;
}

int main()
{
    printf("%.3f\n", lg(124, 3));
 
    return 0;
}