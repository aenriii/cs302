#pragma once
#include "./dirtylist.h"
// TODO
typedef struct {
    int length;
    int capacity;
    char *buffer;
} DirtyString;
 
 // string methods are based on JS's String class

char string_at(void *_self, int pos);

void string_concat(void *_self, DirtyString *other);
void string_concat_n(void *_self, DirtyList *others);
