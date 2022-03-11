#include <stdio.h>

int x[10], n;

int prodcart(int k)
{
    if( k == n+1 )
    {
        for(int i=1;i<=n;i++) printf("%d", x[i]);
        printf("\n");
    }
    else
        for(int i=1;i<=n;i++)
        {
            x[k]= i;
            prodcart(k+1);
        }
}

int main()
{
    n= 4;
    prodcart(1);
    return 0;
}
