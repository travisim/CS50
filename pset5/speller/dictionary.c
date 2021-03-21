// Implements a dictionary's functionality
#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
int counter = 0;
// Number of buckets in hash

const unsigned int N = 65536;
//46 * 122;
// initialise positive hash value using unsigned int 

unsigned int word_count;


// Hash table
node *table[N];


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    
    node *cursor = table[index];
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
    // TODO
    
    int hash = 5381;

    int c = (*word);

    while (c == *word++)
    {
        hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */
    }
    /*   int hash = 0;
        for(int i = 0; i < strlen(word); i++)
        {
        hash += tolower(word[i]);
        }
        */
    return hash % N;
    
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dict 
    FILE *fp = fopen(dictionary, "r");// If file is not opened, return false
    if (fp == NULL)
    {
        return false;
    }
    // storage space for word + /0
    char word[LENGTH + 1];// Scan dict for strings that are not the end of the file
    while (fscanf(fp, "%s", word) != EOF)
    {
        // Allocate memory for new node
        node *n = malloc(sizeof(node));// If malloc returns NULL, return false
        if (n == NULL)
        {
            return false;
        }
        // Pointer to next node and word itself
        strcpy(n->word, word);
        n->next = NULL;
        //get hash value
        int index = hash(word);
       
       
        // Set new pointer
        n->next = table[index];
        // Set head to new pointer
        table[index] = n;
        
        /*
        if (table[index] == NULL)
        {
            table[index] = n;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }*/
        /*  if index null, node.next = null than at index = node*/
        // Increment word count
        counter++;
    }// Close file
    fclose(fp);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false

bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
