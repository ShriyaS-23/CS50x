#include <stdio.h>
#include <cs50.h>

int positive(void);

int main(void)//main method
{
    int h = positive();
    for (int i = 1 ; i<=h ; i++)
    {
        for ( int c = i ; c <= (h-1) ; c++)
        {
            printf(" ");
            
        }
        for (int c = 1 ; c <= i ; c++)
        {
            printf("#");
        }
        
        printf("\n");
    }
}

int positive(void)//method to store positive integer between 1 to 8
{
    int n;
    do
    {
        n = get_int("Height:");//taking input
    }
    while (n < 1 || n > 8);
    return n;
}