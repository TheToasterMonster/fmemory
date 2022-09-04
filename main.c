#include <assert.h>
#include <stdio.h>

#include "fmemory.h"

int main() {
    int* x = malloc(sizeof(int));
    *x = 5;
    assert(*x == 5);

    int* y = malloc(sizeof(int));
    *y = 10;
    assert(*y == 10);
    assert(get_total_allocated() == 2 * sizeof(int));

    free(y);
    assert(get_total_allocated() == 1 * sizeof(int));

    int* arr = malloc(50 * sizeof(int));
    for (int i = 0; i < 50; i++) {
        arr[i] = i + 1;
    }
    for (int i = 0; i < 50; i++) {
        assert(arr[i] == i + 1);
    }
    assert(get_total_allocated() == 51 * sizeof(int));

    int* z = malloc(sizeof(int));
    *z = 15;
    assert(*z == 15);

    arr = realloc(arr, 100 * sizeof(int));
    for (int i = 50; i < 100; i++) {
        arr[i] = i + 1;
    }
    for (int i = 0; i < 100; i++) {
        assert(arr[i] == i + 1);
    }
    assert(get_total_allocated() == 102 * sizeof(int));

    printf("All tests passed!\n");

    return 0;
}
