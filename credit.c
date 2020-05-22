#include <stdio.h>
#include <cs50.h>

long number(void);

int main (void)
{
    long n = number();
    long x = n;
    long q = n;
    long t = n;
    long y = 0;
    while (x != 0)
    {
        long b = (x%100 - x%10)/10 ;
        x = x/100;
        long c = b*2;
        if (c/10 == 0)
        {
            y = y + c;
        }
        else
        {
            while(c != 0)
            {
                long f = c%10;
                y = y + f;
                c = c/10;
            }
        }
    }
    /*long s1 = 0;
    while (y != 0)
    {
        s1 = s1 + y%10;
        y = y/10;
    }*/
    
    long s2 = 0;
    while (q != 0)
    {
        s2 = s2 + q%10;
        q = q/100;
    }
    
    long s = y + s2;
    long h = t/1000000000000;
    long z = t/1000000000000000;
    printf("%ld\n", h);
    printf("%ld\n", z);
    
    
    if (s%10 == 0 && (t/10000000000000 == 34 || t/10000000000000 == 37))
    {
        printf("AMEX");
    }
    else if (s%10 == 0 && (t/1000000000000000 == 51 || t/1000000000000000 == 52 || t/1000000000000000 == 53 || t/1000000000000000 == 54 || t/1000000000000000 == 55))
    {
        printf("MASTERCARD");
    }
    else if (s%10 == 0 && (t/1000000000000 == 4 || t/1000000000000000 == 4))
    {
        printf("VISA");
    }
    else
    {
        printf("INVALID");
    }
    
}

long number(void)
{
    long n = 0;
    do
    {
        n = get_long("Card Number: ");
    }
    while(n<0);
    return n;
}
