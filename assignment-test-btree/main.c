#include "./utils/logging.h"
#include "./utils/btree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argv, char** argc) {

    srand((unsigned int) time(NULL));

    BSTree *tree = newBSTree();
    
    int find = 0;
    for (size_t i = 0; i < 100000; i++)
    {
        int r = rand();

        find = r;

        tree->vtable->insert(tree, r);
    }
    printf("Added all items, fucking around with this.\n");

    
    printf("tree->vtable->contains(tree, find) -> %d\n", tree->vtable->contains(tree, find));
    printf("tree->vtable->sorted(tree) -> %d\n", tree->vtable->sorted(tree));
    printf("tree->vtable->size(tree) -> %d\n", tree->vtable->size(tree));
    


    return 0;
}