#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Simulate a dictionaries functionality
#include "dictionary.h"

int counter = 0;
int hash_index = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    hash_index = hash(word);
    node *cursor = table[hash_index];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    if (strlen(word) > 2)
    {
        return ((toupper(word[0]) - 'A') + (toupper(word[1]) - 'A'));
    }

    else
    {
        return (toupper(word[0]) - 'A');
    }

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        printf("Could not open dictionary\n");
        return false;

    }

    char dict_word[LENGTH + 1];

    while (fscanf(source, "%s", dict_word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Could not allocate memory\n");
            return false;
        }
        strcpy(n->word, dict_word);
        hash_index = hash(dict_word);
        n->next = table[hash_index];
        table[hash_index] = n;

        counter++;
    }

    fclose(source);

    printf("The size of the dictionary is: %u\n", size());

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }

    return true;
}
