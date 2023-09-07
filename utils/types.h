#pragma once
#include "./logging.h"
#define CHECK_TYPE(self, type) \
    if (self->__type__ != type) { \
        ERROR("Type mismatch: %d != %d\n", self->__type__, type); \
        return -1; \
    }

// hi :3