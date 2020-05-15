#include <stdio.h>
#include <cs50.h>

int main(void)//main method
{
    string name = get_string("Enter your name: ");//input from user
    printf("Hello, %s \n", name);
}