#include <stdio.h>
#include <cs50.h>
#include <math.h>

float positive(void);

int main(void)
{
    float change = positive();
    float cents = round (change * 100);
    int coins = 0;
    
    while(cents!=0)
    {
        if (cents>25)
        {
            coins++;
            cents = cents - 25;
        }
        else if (cents>10)
        {
            coins++;
            cents -= 10;
        }
        else if (cents>5)
        {
            coins++;
            cents -= 5;
        }
        else
        {
            coins++;
            cents -= 1;
        }
    }
    printf("%i\n",coins);
}


float positive(void)//method to get positive float
{
    float n;
    do
    {
        n = get_float("Change owed: ");//taking input
    }
    while(n<0);
    return n;//returning n
}