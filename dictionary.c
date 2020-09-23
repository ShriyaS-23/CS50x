// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <stdlib.h>

#include <string.h>

#include <stdio.h>

#include <strings.h>

#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

//Word count
int count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    /*int h = hash(word);

    node *cursor = table[h];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    return false;*/
    
    int n = strlen(word);
    char wordCopy[LENGTH + 1];
    for (int i = 0; i < n; i++)
    {
        wordCopy[i] = tolower[word[i]];   
    }
    wordCopy[n] = '\0';
    
    int h = hash_index(wordCopy);
    node *cursor = hashtable[h];
    
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, wordCopy) == 0)
        {
            return true;   
        }
        else
        {
            cursor = cursor->next;   
        }
    }
    
    return false;
}

// Hashes word to a number
/*unsigned int hash(const char *word)
{
    int x = strlen(word);
    char copy[x];

    if (x-1 >= 3)
    {
        unsigned int index = (int)((copy[0] - 65) * 676) + ((copy[1] - 65) * 26) + (copy[2] - 65);
            return index;
    }
    else if (x-1 == 2)
    {
        unsigned int index = (int)((copy[0] - 65) * 26) + (copy[1] - 65);
        return index;
    }
    else
    {
        unsigned int index = (int)copy[0] - 65;
        return index;
    }
}*/

int hash_index(char *hash_this)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(hash_this); i < n; i++)
    {
        hash = (hash << 2) ^ hash_this[i];
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        return false;
    }

    char word [LENGTH+ 1];

    while ((fscanf (dic, "%s", word)) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            //unload; check if to do
            return false;
        }

        strcpy (n->word, word);

        int h = hash(n->word);

        node *tmp = table[h];
        if (tmp == NULL)
        {
            table[h] = n;
            count ++;
        }
        else
        {
            /*node *x = NULL;
            while (tmp != NULL)
            {
                x = tmp;
                tmp = tmp->next;
            }

            n = tmp;
            x->next = n;
            count*/
            
            n->next = table[h];
            table[h] = n;
            count ++;
        }
    }

    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    /*for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }

    return true;*/
    
    node *tmp = NULL;
    node *cursor = tmp;
    
    while(cursor != NULL)
    {
        node *x = cursor;
        cursor = cursor->next;
        free(x);
    }
    return true;
}
