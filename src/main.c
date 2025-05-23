#include <stdio.h>

#include "list.h"

typedef struct {
    int* items;
    size_t capacity;
    size_t length;
} int_list;

int main()
{
    int_list list = { 0 };
    for (int i = 0; i < 100000; i++) {
        vl_list_append(&list, i);
    }

    printf("length: %zu\n", list.length);
    printf("capacity: %zu\n", list.capacity);

    vl_list_free(&list);

    printf("length: %zu\n", list.length);
    printf("capacity: %zu\n", list.capacity);
    printf("items: %p\n", list.items);
}