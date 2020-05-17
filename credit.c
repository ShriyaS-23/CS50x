#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long n = get_long("Card Number:");
    long x = n;
    long s = 0;
    long k = 0;
    while(n!=0)
    {
        n = n/10;;
        long c = n%10;
        n = n/10;
        if (c/10 == 0)
        {
            s = s + c*2;
        }
        else
        {
            while (c!=0)
            {
                long d = c%10;
                s = s + d;
                c = c/10;
            }
        }
    }
    while(x!=0)
    {
        long c = x%10;
        x = n/100;
        k = k + c;
    }
    long ans = k + s;
    if (ans%10 == 0)
    {
        printf("VISA");
    }
    else
    {
        printf("INVALID");
    }
}