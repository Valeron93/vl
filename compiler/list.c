#include "list.h"

void vl_list_grow(void** data, size_t* capacity, size_t length, size_t element_size)
{
    size_t cap = *capacity;
    if (length >= *capacity) {
        *capacity = (cap == 0) ? 32 : (3 * cap / 2);
        *data = realloc(*data, *capacity * element_size);
    }
}