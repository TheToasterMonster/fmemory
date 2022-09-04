#include <stdio.h>
#include "fmemory.h"

int main() {
    int* x = malloc(sizeof(int));
    *x = 5;
    printf("%i\n", *x);
    int* y = malloc(sizeof(int));
    *y = 10;
    printf("%i\n", *y);

    return 0;
}
