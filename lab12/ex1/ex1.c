#include <stdio.h>
#include <stdlib.h>

float err= 1e-6, n;

float rad(float st, float dr)
{
    if(dr - st < err) return dr;

    double m = (st + dr) / 2;

    if(m * m < n) return rad(m, dr);

    return rad(st, m);
    
}

int main()
{
    n= 9.02;
    printf("%.6f\n", rad(0, n));
 
    return 0;
}
