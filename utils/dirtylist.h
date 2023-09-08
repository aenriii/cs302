#pragma once

typedef struct {
    int __type__;
    int count;
    int capacity;
    int itemSize;

    int (*grow)(void* self, int capacity);
    int (*add)(void* self, void* item);
    int (*remove)(void* self, void* item);
    int (*contains)(void* self, void* item);
    int (*clear)(void* self);
    int (*destroy)(void* self);

    void* items;
} DirtyList;
#define DIRTYLIST_GROWTH_FACTOR 8 // this is 1% faster than 2 in my testing, trust.

DirtyList* new_dirtylist(int initialCapacity, int itemSize);
int dirtylist_grow(void* self, int capacity);
int dirtylist_add(void* self, void* item);
int dirtylist_remove(void* self, void* item);
int dirtylist_contains(void* self, void* item);
int dirtylist_clear(void* self);
int dirtylist_destroy(void* self);

#define DIRTYLIST 0x00000001
