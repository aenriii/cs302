#include "./dirtylist.h"
#include "./logging.h"
#include "./macros.h"
#include <stdlib.h>
#include <string.h>

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
    self->items = malloc(initialCapacity * itemSize);

    return self;
}

int dirtylist_grow(void *_self, int capacity) {
    DirtyList *self = (DirtyList *) _self;

    CHECK_TYPE(self, DIRTYLIST)


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
    DirtyList *self = (DirtyList *) _self;

    CHECK_TYPE(self, DIRTYLIST)

    if (self->count == self->capacity) {
        if (self->grow(self, self->capacity * DIRTYLIST_GROWTH_FACTOR) != 0) {
            ERROR("Failed to grow DirtyList");
            return -1;
        }
    }
    memcpy(self->items + (self->count * self->itemSize), item, self->itemSize);
    self->count++;
    return 0;
}

int dirtylist_remove(void *_self, void* item) {
    DirtyList *self = (DirtyList *) _self;

    CHECK_TYPE(self, DIRTYLIST)
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
    DirtyList *self = (DirtyList *) _self;

    CHECK_TYPE(self, DIRTYLIST)
    for (int i = 0; i < self->count; i++) {
        if (memcmp(self->items + (i * self->itemSize), item, self->itemSize) == 0) {
            return 1;
        }
    }
    return 0;
}

int dirtylist_clear(void *_self) {
    DirtyList *self = (DirtyList *) _self;

    CHECK_TYPE(self, DIRTYLIST)
    self->count = 0;
    memset(self->items, 0, self->capacity * self->itemSize);
    return 0;
}

int dirtylist_destroy(void *_self) {
    DirtyList *self = (DirtyList *) _self;

    CHECK_TYPE(self, DIRTYLIST)
    self->count = 0;
    memset(self->items, 0, self->capacity * self->itemSize);
    free(self->items);
    free(self);
    return 0;
}
