#pragma once
#include "./dirtylist.h"
#include "./macros.h"

int INT_COMPARATOR(void* int1, void* int2) {
    int i1 = * ((int *) int1);
    int i2 = * ((int *) int2);

    if (i1 < i2) {
        return -1;
    } else if (i1 == i2) {
        return 0;
    } else {
        return 1;
    }
}

