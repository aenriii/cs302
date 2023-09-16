#include "./dirtylist.h"
#include "./logging.h"
#include "./macros.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

DirtyList* new_dirtylist(int initialCapacity, int itemSize) {
    DirtyList *self = malloc(sizeof(DirtyList));
    self->__type__ = DIRTYLIST;
    self->count = 0;
    self->capacity = initialCapacity;
    self->itemSize = itemSize;
    self->grow = dirtylist_grow;
    self->add = dirtylist_add;
    self->remove = dirtylist_remove;
    self->contains = dirtylist_contains;
    self->clear = dirtylist_clear;
    self->destroy = dirtylist_destroy;
    self->filter = dirtylist_filter;
    self->for_each = dirtylist_for_each;
    self->deduplicate_unsafe = dirtylist_deduplicate_unsafe;
    self->items = malloc(initialCapacity * itemSize);

    return self;
}

int dirtylist_grow(void *_self, int capacity) {
    FLASH(_self, self, DirtyList, DIRTYLIST)
    if (capacity <= self->capacity) {
        WARN("Cannot grow to capacity %d, which is less than or equal to current capacity %d\n", capacity, self->capacity);
        return -1;
    }
    DEBUG("Growing from %d to %d", self->capacity, capacity);
    void* newItems = malloc(capacity * self->itemSize);
    memcpy(newItems, self->items, self->count * self->itemSize);
    free(self->items);
    self->items = newItems;
    self->capacity = capacity;
    return 0;
}

int dirtylist_add(void *_self, void* item) {
    FLASH(_self, self, DirtyList, DIRTYLIST)

    if (self->count == self->capacity) {
        if (self->grow(self, self->capacity * DIRTYLIST_GROWTH_FACTOR) != 0) {
            ERROR("Failed to grow DirtyList");
            return -1;
        }
    }
    memcpy((self->items) + (self->count * self->itemSize), item, self->itemSize);
    self->count++;
    return 0;
}

int dirtylist_remove(void *_self, void* item) {
    FLASH(_self, self, DirtyList, DIRTYLIST)
    int index = -1;
    for (int i = 0; i < self->count; i++) {
        if (memcmp(self->items + (i * self->itemSize), item, self->itemSize) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        WARN("Item not found in DirtyList");
        return -1;
    }
    for (int i = index; i < self->count - 1; i++) {
        memcpy(self->items + (i * self->itemSize), self->items + ((i + 1) * self->itemSize), self->itemSize);
    }
    self->count--;
    return 0;
}

int dirtylist_contains(void *_self, void* item) {
    FLASH(_self, self, DirtyList, DIRTYLIST)
    for (int i = 0; i < self->count; i++) {
        if (!memcmp(self->items + (i * self->itemSize), item, self->itemSize) == 0) {
            return 1;
        }
    }
    return 0;
}

int dirtylist_clear(void *_self) {
    FLASH(_self, self, DirtyList, DIRTYLIST)
    self->count = 0;
    memset(self->items, 0, self->capacity * self->itemSize);
    return 0;
}

int dirtylist_destroy(void *_self) {
    FLASH(_self, self, DirtyList, DIRTYLIST)
    self->count = 0;
    memset(self->items, 0, self->capacity * self->itemSize);
    free(self->items);
    free(self);
    return 0;
}


int dirtylist_filter(void *_self, bool (*filter_func)(void*)) {
    FLASH(_self, self, DirtyList, DIRTYLIST)
    int removed = 0;
    int i = 0;
    while (i < self->count) {
        if (!filter_func(self->items + (i * self->itemSize))) {
            self->remove(self, self->items + (i * self->itemSize));
            removed++;
        } else {
            i++;
        }
    }
    return removed;    
}
void dirtylist_for_each(void *_self, void(*func)(void*)) {
    FLASH_V(_self, self, DirtyList, DIRTYLIST)

    for (int i = 0; i < self->count; i++) {

        func(self->items + (i * self->itemSize));

    }
}

int dirtylist_deduplicate_unsafe(void *_self, int bytes_checked) {
    FLASH(_self, self, DirtyList, DIRTYLIST)
    int removed = 0;
    int index = 0;
    while ( index < self->count ) {
        void *ptr = self->items + (index * self->itemSize);
        int i2 = index + 1;
        int doNextPtr = 1; 
        while (i2 < self->count) {
            void *optr = self->items + (self->itemSize * i2);
            if (memcmp(ptr, optr, bytes_checked) == 0) {
                self->remove(self, ptr);
                removed++;
                doNextPtr = 0;
                break;
            }
            i2++;
        }
        index += doNextPtr;
    }
    return removed;
}