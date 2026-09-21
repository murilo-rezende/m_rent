#include "m_rent.h"
#include <stdio.h>

static void print_blocks(void) {
    Block *cur = free_list_head;
    int i = 0;
    while (cur) {
        printf("  Block %d: addr=%p size=%zu free=%s\n",
               i++, (void *)cur, cur->size, cur->free ? "true" : "false");
        cur = cur->next;
    }
}

int main(void) {
    printf("=== Allocator test ===\n\n");

    int *a = (int *) allocate(sizeof(int));
    double *b = (double *) allocate(sizeof(double));
    char *c = (char *) allocate(64);

    printf("a = %p\nb = %p\nc = %p\n\n", (void *)a, (void *)b, (void *)c);

    if (!a || !b || !c) {
        printf("ERROR: allocation returned NULL\n");
        return 1;
    }

    *a = 42;
    *b = 3.14;
    for (int i = 0; i < 63; i++) c[i] = 'x';
    c[63] = '\0';

    printf("*a = %d\n*b = %f\nc  = %s\n\n", *a, *b, c);

    printf("=== After 3 allocations ===\n");
    print_blocks();

    printf("\n=== Freeing b ===\n");
    deallocate(b);
    print_blocks();

    printf("\n=== Freeing a and c ===\n");
    deallocate(a);
    deallocate(c);
    print_blocks();

    return 0;
}