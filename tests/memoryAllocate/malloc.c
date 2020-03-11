#include <stdio.h>
#include <stdlib.h>

    typedef struct node
    {
        int value;
        struct node *child[3];
    }node;

int main(const int argc, const char *argv[])
{

    node *element1 = malloc(sizeof(node));
    element1->child[0] = malloc(sizeof(node));
    

    printf("%p\n", element1);
    printf("%p\n", element1->child[0]);
    printf("%p\n", element1->child[0]->child[0]);
    element1->child[0]->child[0] = malloc(sizeof(node));
    printf("%p\n", element1->child[0]->child[0]);


    return 0;
}