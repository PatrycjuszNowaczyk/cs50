// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include <inttypes.h>
#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

char alphabet[N] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\0'};
//char alphabet2[N] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "\'"};

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;
// Number of words in a dictionary
unsigned int dictNrOfWords = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // create index for children array in a trie
    int index = 0;
    // Insert words into trie
    node *trie;
    int nodeNumber;
    while (fscanf(file, "%s", word) != EOF)
    {
        dictNrOfWords++;
        nodeNumber = 0;
        // TODO
        trie = root;

        for (int i = 0; word[i] != '\0'; i++)
        {
        // printf("node number: %i, letter: %c\n", nodeNumber, word[i]);
        nodeNumber++;
            if ((index = tolower(word[i]) % 97) == 39)
            {
                index = 26;
            }
            // printf("index: %i\n", index);
            if (!trie->children[index])
            {
                trie->children[index] = malloc(sizeof(node));
                if (trie->children[index] == NULL)
                {
                    printf("Couldn't create a trie node\n");
                    dictNrOfWords = 0;
                    return false;
                }
                trie->children[index]->is_word = false;
                for (int j = 0; j < N; j++)
                {
                    trie->children[index]->children[j] = NULL;
                }
            }
            if (trie->children[index])
            {
            trie = trie->children[index];
            // printf("memory: %0lx\n", (uintptr_t) trie->children[index]);
            }
            if (word[i+1] == '\0')
            {
                trie->is_word = true;
            }
            // if (word[i+1] == '\0')
            // {
            // printf("end of a word\n");
            // }
        }
        // printf("\n\n\n");
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictNrOfWords;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *trie = root;
    int index = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if ((index = tolower(word[i]) % 97) == 39)
        {
            index = 26;
        }
        if (trie->children[index] && word[i+1])
        {
            trie = trie->children[index];
        }
        else if (!trie->children[index])
        {
            // printf("too long word\n");
            return false;
        }
        else if (!word[i+1])
        {
            if (trie->children[index]->is_word == true)
            {
                return true;
            }
            else
            {
                // printf("too short word\n");
                return false;
            }
        }
        else
        {
            return false;
        } 
    }
    return false;
}

void freeTrie(node *arg)
{
    for (int i = 0; i < N; i++)
    {
        if (arg->children[i])
        {
            freeTrie(arg->children[i]);
        }
    }
    free(arg);
    
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    freeTrie(root);
    return true;
}