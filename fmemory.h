#ifndef FMEMORY_H
#define FMEMORY_H

#include <stddef.h>

void* malloc(size_t size);
void* calloc(size_t count, size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);

#ifdef FMEMORY_DEBUG
size_t get_total_allocated();
#endif

#endif
