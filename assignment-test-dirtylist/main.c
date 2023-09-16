#include "./utils/logging.h"
#include "./utils/dirtylist.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

bool UNDER_50000(int *num) {
    // DEBUG("Filtering %d", *num)
    return (*num) > 50000;
}

int main(int argv, char** argc) {

    srand((unsigned int) time(NULL));

    
    DirtyList *dl = new_dirtylist(1, sizeof(int));

    // int find; 
    // for (size_t i = 0; i < 100000; i++)
    // {
    //     // int *r = malloc(sizeof(int));
    //     // *r = rand();
    //     // find = *r;

    //     dl->add(dl, &i);
    //     // free(r);
    //     // DEBUG("added %d", i)

    // }
    // printf("Added range 0 -> 99999 items, fucking around with this.\n");

    // printf("dl->count -> %d\n", dl->count);
    // printf("dl->filter(dl, UNDER_50000) -> %d\n", dl->filter(dl, UNDER_50000));
    // printf("dl->count -> %d\n", dl->count);


    dl = new_dirtylist(10000, sizeof(int));
    for (size_t i = 0; i < 10000; i++) {
        int that = 1;
        // DEBUG("added %d item", i)
        dl->add(dl, &that);
    }
    printf("Added 1 * 10000 items, fucking around with this.\n");

    
    printf("dl->count -> %d\n", dl->count);
    printf("dl->deduplicate_unsafe(dl, sizeof(int)) -> %d\n", dl->deduplicate_unsafe(dl, sizeof(int)) );
    printf("dl->count -> %d\n", dl->count);

    return 0;
}

