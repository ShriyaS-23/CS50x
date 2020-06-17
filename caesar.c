#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    for (int i = 1; i <= argc; i++)
    {
        if (argc == 2)   
        {
                break;
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    
    int j = strlen(argv[1]);
    for (int i = 0; i < j; i++)
    {
        char c = argv[1][i];
        if ( c >= 48 && c <= 57 )
        {
            continue;
        }
        else
        {
            printf("Usage: ./caesar key \n");
        }
    }
    
    int key = atoi(argv[1]);
    
    string pt = get_string("plaintext: ");
    
    int z = strlen(pt);
    
    int ct[z];
    
    for (int i = 0; i<z ; i++)
    {
        if ((pt[i] >= 'a' && pt[i] <= 'z') )
        {
            ct[i] = (((pt[i] -'a') + key) % 26) + 'a';
        }
        else if ((pt[i] >= 'A' && pt[i] <= 'Z'))
        {
            ct[i] = (((pt[i] -'A') + key) % 26) + 'A';
        }
        else
        {
            ct[i] = pt[i];
        }
    }
    
    printf("ciphertext: ");
    
    for (int i = 0; i<z; i++)
    {
        printf("%c", (char)ct[i]);   
    }
    printf("\n");
    
}