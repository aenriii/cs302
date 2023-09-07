#include "./btree.h"
#include "./logging.h"
#include <stdlib.h>
BTree* newBTree() {
    BTree* self = malloc(sizeof(BTree));
    self->__type__ = BTREE;
    self->root = NULL;
    // self->vtable = &{
        
    // };
    return self;
}

void btree_insert(void *self, int value) {
    
}