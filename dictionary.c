// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Hashtable size 2^17
#define HT_LENGTH 131072


typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

node *hashtable[HT_LENGTH];


// Dummy hash function - returns first character as int from 0-25 for testing purposes
/*unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}*/

// Modified djb2 hash function from http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(const char *str)
{
    unsigned long hash = 5381;
    int c;
    while ((c = tolower(*str++)))
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *head = hashtable[hash(word) % HT_LENGTH];
    node *cursor = head;
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

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Dictionary is passed in as a string (char*)
    FILE *dict = fopen(dictionary, "r");
    char word[LENGTH];

    // Scan through file word by word until EOF
    while (fscanf(dict, "%s", word) != EOF)
    {
        // Hash word
        node *head = hashtable[hash(word) % HT_LENGTH];

        // Insertion into linked list
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        strcpy(new_node->word, word);
        new_node->next = head;
        head = new_node;
        hashtable[hash(word) % HT_LENGTH] = head;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int total_words = 0;
    for (int i = 0; i < HT_LENGTH; i++)
    {
        // Traverse each linked list and add count to total_words
        node *head = hashtable[i];
        node *cursor = head;
        while (cursor != NULL)
        {
            total_words++;
            cursor = cursor->next;
        }
    }
    return total_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < HT_LENGTH; i++)
    {
        // Traverse each linked list and free memory for each node
        node *head = hashtable[i];
        node *cursor = head;
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
