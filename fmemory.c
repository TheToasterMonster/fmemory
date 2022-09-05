#include "fmemory.h"

#include <string.h>

#define HEAP_SIZE 2000
static unsigned char heap[HEAP_SIZE] = {0};
static size_t end = 0;

// index 0 keeps track of start of block of memory
// index 1 keeps track of first cell of next available block of memory
static size_t status[HEAP_SIZE][2] = {0};

#ifdef FMEMORY_DEBUG
static size_t total_allocated = 0;
size_t get_total_allocated() { return total_allocated; }
#endif

int is_block_available(size_t index, size_t size) {
    while (size--) {
        if (index > HEAP_SIZE || status[index++][0]) {
            return 0;
        }
    }
    return 1;
}

void* malloc(size_t size) {
    // get index to block of memory
    size_t index;
    if (end + size <= HEAP_SIZE) {
        index = end;
        end += size;
    } else {
        index = 0;
        while (1) {
            if (status[index][0]) {
                index = status[index][1];
            } else if (!is_block_available(index, size)) {
                index++;
            } else {
                break;
            }

            if (index >= HEAP_SIZE) {
                return NULL;
            }
        }
    }

    // update metadata in status to keep track of allocated memory
    for (size_t i = 0; i < size; i++) {
        status[index + i][0] = index;
        status[index + i][1] = index + size;
    }

#ifdef FMEMORY_DEBUG
    total_allocated += size;
#endif

    return &heap[index];
}

void* calloc(size_t count, size_t size) {
    void* ptr = malloc(count * size);
    memset(ptr, 0, count * size);
    return ptr;
}

void* realloc(void* ptr, size_t size) {
    size_t index = (size_t)ptr - (size_t)heap;
    if (status[index][0] != index) {
        return NULL;
    }

    size_t prev_size = status[index][1] - status[index][0];
    if (size < prev_size) {
        for (size_t i = size; i < prev_size; i++) {
            status[index + i][0] = 0;
            status[index + i][1] = 0;
        }
#ifdef FMEMORY_DEBUG
        total_allocated -= (prev_size - size);
#endif
        return ptr;
    }

    if (is_block_available(status[index][1], size - prev_size)) {
        // update status for already allocated memory
        for (size_t i = 0; i < prev_size; i++) {
            status[index + i][1] = index + size;
        }
        // update status for newly allocated memory
        size_t end = status[index][1];
        for (size_t i = 0; i < size; i++) {
            status[end + i][0] = index;
            status[end + i][1] = index + size;
        }
#ifdef FMEMORY_DEBUG
        total_allocated += (size - prev_size);
#endif
        return ptr;
    } else {
        // old memory not large enough, needs totally new allocation
        void* newPtr = malloc(size);
        memcpy(newPtr, ptr, prev_size);
        free(ptr);
        return newPtr;
    }
}

void free(void* ptr) {
    size_t index = (size_t)ptr - (size_t)heap;
    if (status[index][0] != index) {
        return;
    }

    // update metadata in status to reflect freed memory
    size_t end = status[index][1];
#ifdef FMEMORY_DEBUG
    size_t size = end - index;
#endif
    while (index < end) {
        status[index][0] = 0;
        status[index][1] = 0;
        index++;
    }

#ifdef FMEMORY_DEBUG
    total_allocated -= size;
#endif
}

