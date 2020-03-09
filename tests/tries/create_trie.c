#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
    int value;
    struct node *children[2];
}node;

void trieAdd(node *trie, int value);
void triePrint(node *trie);
int main(int argc, const char *argv[])
{

node *trie = malloc(sizeof(node));
trieAdd(trie, 50);
trieAdd(trie, 11);
trieAdd(trie, 12);
trieAdd(trie, 12);
trieAdd(trie, 14);
trieAdd(trie, 55);
trieAdd(trie, 122);
trieAdd(trie, 43);
trieAdd(trie, 35);
trieAdd(trie, 156);
trieAdd(trie, 1);
trieAdd(trie, 5);
trieAdd(trie, 87);
trieAdd(trie, 15);
trieAdd(trie, 16);
trieAdd(trie, 1);
trieAdd(trie, 87);
trieAdd(trie, 5);
trieAdd(trie, 156);
trieAdd(trie, 15);

triePrint(trie);
printf("\n");

free(trie);

return 0;
}

void trieAdd(node *trie, int value)
{
    if (!trie->value) 
    {
        trie->value = value;
        trie->children[0] = '\0';
        trie->children[1] = '\0';
    }
    else if (trie->value > value && trie->children[0])
    {
        trieAdd(trie->children[0], value);
    }
    else if (trie->value < value && trie->children[1])
    {
        trieAdd(trie->children[1], value);
    }
    else if (trie->value > value)
    {
        trie->children[0] = malloc(sizeof(node));
        trieAdd(trie->children[0], value);
    }
    else if (trie->value < value)
    {
        trie->children[1] = malloc(sizeof(node));
        trieAdd(trie->children[1], value);
    }
    return;
}

void triePrint(node *trie)
{
    if (trie->value)
    {
        printf("%i, ", trie->value);
    }
    
    if (trie->children[0])
    {
        triePrint(trie->children[0]);
    }
   
    if (trie->children[1])
    {
        triePrint(trie->children[1]);
    }
    return;
}