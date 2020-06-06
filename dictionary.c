// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table = 2^14
const unsigned int HASH_TABLE_SIZE = 16384;

// Hash table
node *hash_table[HASH_TABLE_SIZE];

// Count for number of words in dictionary
unsigned int word_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Lowercase word before hashing
    char lower[strlen(word) + 1];
    for (int i = 0; i < strlen(word) + 1; i++)
    {
        lower[i] = tolower(word[i]);
    }

    // Calculate hash key for lowercase word
    unsigned int hash_key = hash(lower);

    // Get pointer to first node in linked list
    node *cursor = hash_table[hash_key];

    // Traverse linked list
    while (cursor != NULL)
    {
        // If word at cursor matches word (lowercase)
        if (strcasecmp(cursor->word, lower) == 0)
        {
            return true;
        }

        // Otherwise go to next node in the linked list
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    const char *str = word;

    // djb2 Hash Function - http://www.cse.yorku.ca/~oz/hash.html
    unsigned int hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash % HASH_TABLE_SIZE;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");

    // Check if dictionary was opened correctly
    if (file == NULL)
    {
        printf("Could not open dictionary\n");
        return false;
    }

    // Set all values in hash table to NULL
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }

    // Initialise word variable to read from file into memory
    char word[LENGTH];

    // Read strings from dictionary one at a time
    while (fscanf(file, "%s", word) != EOF)
    {
        // Increment word count
        word_count++;

        // Allocate memory for new node
        node *n = malloc(sizeof(node));

        // Check if memory could be allocated for new node
        if (n == NULL)
        {
            printf("Memory could not be allocated for new node\n");
            return false;
        }

        // Copy word into node
        strcpy(n->word, word);

        // Get hash key value
        unsigned int hash_key = hash(word);

        // Set new node next to be equal to current value in hash table e.g. start of linked list or NULL
        n->next = hash_table[hash_key];

        // Point hash table to new node
        hash_table[hash_key] = n;
    }

    // Close dictionary
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Loop over each element in the hash table
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        // Initialise cursor as pointer to first node in linked list
        node *cursor = hash_table[i];

        // Traverse linked list
        while (cursor != NULL)
        {
            // Initialise tmp variable and set to cursor
            node *tmp = cursor;

            // Move cursor to next node
            cursor = cursor->next;

            // Free node pointed to by tmp
            free(tmp);
        }
    }

    return true;
}
