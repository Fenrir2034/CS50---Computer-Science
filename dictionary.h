#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
#define LENGTH 45
#define HASH_SIZE 2000

// Define the node structure
typedef struct node
{
    char* word;
    struct node* next;
} node;

// Function prototypes
bool check(const char* word);
bool load(const char* dictionary);
unsigned int size(void);
bool unload(void);

#endif // DICTIONARY_H
