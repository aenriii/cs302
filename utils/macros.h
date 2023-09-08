#pragma once
#include "./logging.h"
#define CHECK_TYPE(self, type) \
    if (self->__type__ != type) { \
        ERROR("Type mismatch: %d != %d\n", self->__type__, type); \
        return -1; \
    }

#define FLASH(varFrom, varTo, type, typeId) \
    type *varTo = (type *) varFrom; \
    \
    CHECK_TYPE(self, typeId);

#define CHECK_TYPE_V(self, type) \
    if (self->__type__ != type) { \
        ERROR("Type mismatch: %d != %d\n", self->__type__, type); \
        return; \
    }
#define FLASH_V(varFrom, varTo, type, typeId) \
    type *varTo = (type *) varFrom; \
    \
    CHECK_TYPE_V(self, typeId);
