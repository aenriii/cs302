#include "./utils/dirtylist.h"
#include "./utils/logging.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argv, char** argc) {
    // stress test

    printf("Hello, world!\n");
    return 0;
    // for (size_t k = 0; k < 10; k++)
    // {
    //     DirtyList *list = new_dirtylist(1, sizeof(long long int));

    //     for (long long int i = 0; i < 10000000; i++)
    //     {
    //         list->add(list, &i);
    //     }

    //     list->destroy(list);
    // }
}