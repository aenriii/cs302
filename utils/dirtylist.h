#pragma once
#include <stdbool.h>

typedef struct {
    int __type__;
    int count;
    int capacity;
    int itemSize;

    int   (*grow)(void *_self, int capacity);
    int   (*add)(void *_self, void* item);
    int   (*remove)(void *_self, void* item);
    int   (*contains)(void *_self, void* item);
    int   (*clear)(void *_self);
    int   (*destroy)(void *_self);
    int   (*filter)(void *self, bool (*filter_fn)(void*));
    void  (*for_each)(void *_self, void(*func)(void*));
    // this is really stupid
    int   (*deduplicate_unsafe)(void *_self, int bytes_checked);

    void* items;
} DirtyList;
#define DIRTYLIST_GROWTH_FACTOR 8 // this is 1% faster than 2 in my testing, trust.

DirtyList* new_dirtylist(int initialCapacity, int itemSize);
int  dirtylist_grow(void *_self, int capacity);
int  dirtylist_add(void *_self, void* item);
int  dirtylist_remove(void *_self, void* item);
int  dirtylist_contains(void *_self, void* item);
int  dirtylist_clear(void *_self);
int  dirtylist_destroy(void *_self);
int  dirtylist_filter(void *_self, bool (*filter_fn)(void*));
void dirtylist_for_each(void *_self, void(*func)(void*));
int  dirtylist_deduplicate_unsafe(void *_self, int bytes_checked);
#define DIRTYLIST 0x00000001
