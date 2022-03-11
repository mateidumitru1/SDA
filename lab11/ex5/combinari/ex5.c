#include <stdio.h>

int x[20], n, k;

int verif(int k)
{
    for(int i=1;i<k;i++)
        if( x[k] == x[i] )
            return 0;
    return 1;
}

int solutie(int p)
{
	return (p==k);
}

void combine(int k)
{
    for(int i= x[k-1]+1;i<=n;++i)
    {
        x[k]= i;
        if( solutie(k) )
        {
            for(int j=1;j<=k;j++)
                printf("%d ", x[j]);
            printf("\n");
        }
        else combine(k+1);
    }
}

int main()
{
    n= 4;
    k= 3;
    combine(1);
    return 0;
}
