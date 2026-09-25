#include "m_rent.h"
#include <stdio.h>

int main(void) {
    if (!init_heap(MiB(32))) {
        printf("Failed to initialize heap\n");
        return 1;
    }

    //Allocation with data type
    int *n = (int *)allocate(sizeof(int));
    if(n) {
        *n = 10;
        printf("int: %d, address: %p\n", *n, (void *)n);
    }

    //Allocation with pre-defined size
    //It can be KiB, MiB or GiB
    void* block = allocate(MiB(16));
    if(block) {
        printf("16 MiB allocated in the address: %p\n", block);
    }

    //Deallocating
    deallocate(n);
    deallocate(block);

    return 0;
}