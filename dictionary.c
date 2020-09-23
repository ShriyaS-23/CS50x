#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Number of buckets in hash table
const unsigned int N = 10000;

// Defines struct for a node
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

node *hashtable[N];

//hash function
int hash_index(char *hash_this)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(hash_this); i < n; i++)
    {
        hash = (hash << 2) ^ hash_this[i];
    }
    return hash % N;
}

// Initializes counter for words in dictionary
int word_count = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(dic, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));

        if (new_node == NULL)
        {
            unload();
            return false;
        }

        strcpy(new_node->word, word);

        int h = hash_index(new_node->word);
        node *tmp = hashtable[h];

        if (tmp == NULL)
        {
            hashtable[h] = new_node;
            word_count++;
        }
        else
        {
            new_node->next = hashtable[h];
            hashtable[h] = new_node;
            word_count++;
        }
    }
    fclose(dic);
    return true;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int n = strlen(word);
    char word_copy[LENGTH + 1];
    for (int i = 0; i < n; i++)
    {
        word_copy[i] = tolower(word[i]);
    }

    word_copy[n] = '\0';
    int h = hash_index(word_copy);
    node *cursor = hashtable[h];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word_copy) == 0)
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

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *tmp = NULL;
    node *cursor = tmp;

    while (cursor != NULL)
    {
        node *x = cursor;
        cursor = cursor->next;
        free(x);
    }
    return true;
}