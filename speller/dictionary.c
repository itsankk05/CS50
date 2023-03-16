// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include<stdio.h>
#include<strings.h>
#include<string.h>
#include<stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
int countword = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *cursor = table[index];
    while(cursor != NULL){
        if(strcasecmp(cursor->word, word) == 0){
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char str[LENGTH + 1];
    int index;

    FILE *file = fopen(dictionary , "r");
    if(!file){
        return 1;
    }
    while(fscanf(file, "%s" , str) != EOF){
        node *n = malloc(sizeof(node));
        if(n == NULL){
            return false;
        }
        strcpy(n->word, str);
        index = hash(str);
        n->next = table[index];
        table[index] = n;
        countword += 1;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return countword;
}

void freenode(node *n)
{
    if(n->next != NULL){
        freenode(n->next);
    }
    free(n);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++){
        if(table[i] != NULL){
            freenode(table[i]);
        }
    }
    return true;
}
