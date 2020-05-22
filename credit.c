#include <stdio.h>
#include <cs50.h>

long number(void);

int main(void)//main method
{
    long n = number();
    long x = n;
    long q = n;
    long t = n;
    long y = 0;
    
    //luhn's algorithm
    while (x != 0)
    {
        long b = (x % 100 - x % 10) / 10 ;
        x = x / 100;
        long c = b * 2;
        if (c / 10 == 0)
        {
            y = y + c;
        }
        else
        {
            while (c != 0)
            {
                long f = c % 10;
                y = y + f;
                c = c / 10;
            }
        }
    }
    
    long s2 = 0;
    while (q != 0)
    {
        s2 = s2 + q % 10;
        q = q / 100;
    }
    
    long s = y + s2;
    
    //checking for type of card
    if (s % 10 == 0 && (t / 10000000000000 == 34 || t / 10000000000000 == 37))
    {
        printf("AMEX\n");
    }
    else if (s % 10 == 0 && (t / 100000000000000 == 51 || t / 100000000000000 == 52 || t / 100000000000000 == 53 
                             || t / 100000000000000 == 54 || t / 100000000000000 == 55))
    {
        printf("MASTERCARD\n");
    }
    else if (s % 10 == 0 && (t / 1000000000000 == 4 || t / 1000000000000000 == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
    
}

long number(void)//method to get positive long
{
    long n = 0;
    do
    {
        n = get_long("Card Number: ");
    }
    while (n < 0);
    return n;
}
