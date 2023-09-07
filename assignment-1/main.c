#include "./utils/dirtylist.h"
#include "./utils/logging.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argv, char** argc) {
    DirtyList* permutations = new_dirtylist(1, sizeof(int));
    int *ptr = malloc(sizeof(int));
    *ptr = 1;
    permutations->add(permutations, ptr);

    printf("hii\n");

}