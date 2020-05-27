#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    for (int i = 1; i <= argc; i++)
    {
        if (argc == 2 && (int)argv[i] >= 48 && (int)argv[i] <= 57)   
        {
            continue;
        }
        else
        {
            printf("Usage: ./caesar key");
            return 1;
        }
    }
    
    int key = atoi(argv[1]);
    
    string pt = get_string("Plaintext: \n");
    
    string ct = "";
    
    for (int i = 0, x = strlen(pt); i < x; i++)
    {
        if ((pt[i] >= 'a' && pt[i] <= 'z') || (pt[i] >= 'A' && pt[i] <= 'Z'))
        {
            char f = pt[i] + key;
            ct[i] = f;
        }
        else
        {
            ct[i] = pt[i];
        }
    }
    
    printf("Ciphertext: %s", ct);
}