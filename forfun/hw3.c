#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int mode=0, sum=0;
    mode = atoi(argv[1]);
    long long int lli;
    float f;
    double d;
    if(mode==1)
    {
        sum =0;
        for(int i=0; i<32; ++i)
        {
            if(i==0)
            {
                sum += (int)(argv[2][31-i]-'0');
            }
            else
            {
                if((int)(argv[2][31-i]-'0')==1)
                {
                    sum += (int)pow(2, i);
                }
            }
        }
        printf("%d\n", sum);
        printf("%f", *((float *)(&sum)));
    }
    else if(mode==2)
    {
        sum = atoi(argv[2]);
        for(int i=0; i<32; ++i)
        {
            printf("%d", (*(&sum)>>(31-i))&1);
        }
        printf("\n");
    }
    else if(mode==3)
    {
        f = atof(argv[2]);
        for(int i=0; i<32; ++i)
        {
            printf("%d", (*((int *)(&f))>>(31-i))&1);
        }
    }
    else if(mode==4)
    {
        lli = 0;
        for(int i=0; i<64; ++i)
        {
            if(i==0)
            {
                lli += (int)(argv[2][64-i]-'0');
            }
            else
            {
                if((int)(argv[2][64-i]-'0')==1)
                {
                    lli += (int)pow(2, i);
                }
            }
        }
        printf("%lld", lli);
    }
    else if(mode==5)
    {
        lli = atoi(argv[2]);
        for(int i=0; i<64; ++i)
        {
            printf("%lld", (*(&lli)>>(63-i))&1);
        }
        printf("\n");
    }
    else if(mode==6)
    {
        d = atof(argv[2]);
        for(int i=0; i<64; ++i)
        {
            printf("%lld", (*((long long int *)(&d))>>(63-i))&1);
        }
    }
    return 0;
}