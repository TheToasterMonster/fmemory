#include "fmemory.h"
#include <stdio.h>
#include <string.h>

#define HEAP_SIZE 2000
static unsigned char heap[HEAP_SIZE] = {0};
static size_t end = 0;

void* malloc(size_t size) {
    void* ptr = &heap[end];
    end += size;
    return ptr;
}

void* calloc(size_t count, size_t size) {
    void* ptr = malloc(count * size);
    memset(ptr, 0, count * size);
    return ptr;
}
