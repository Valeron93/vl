#ifndef VL_LIST_H_
#define VL_LIST_H_

#include <assert.h>
#include <stdlib.h>

#define vl_list_append(list, item)                                                                       \
    do {                                                                                                 \
        vl_list_grow((void**)&(list)->items, &(list)->capacity, (list)->length, sizeof(*(list)->items)); \
        (list)->items[(list)->length++] = (item);                                                        \
    } while (0)

#define vl_list_free(list)    \
    do {                      \
        free((list)->items);  \
        (list)->items = NULL; \
        (list)->length = 0;   \
        (list)->capacity = 0; \
    } while (0)

void vl_list_grow(void** data, size_t* capacity, size_t length, size_t element_size);

#endif // VL_LIST_H_
