#include <stdio.h>
#include <string.h>

int x[5], n;

int verif(int k)
{
    for(int i=1;i<k;++i)
        if(x[k] == x[i])
            return 0;
    return 1;
}

void permute(int k)
{
    for(int i=1;i<=n;++i)
    {
        x[k]= i;
        if( verif(k) )
            if( k == n )
            {
                for(int j=1;j<=n;j++)
                    printf("%d ", x[j]);
                printf("\n");
            }
            else permute(k+1);
    }
}

int main()
{
    n= 4;
    permute(1);
    return 0;
}