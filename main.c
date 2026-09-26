#include "m_rent.h"
#include <stdio.h>

int main(void) {
    if (!m_rent_init(MiB(32))) {
        printf("Failed to initialize heap\n");
        return 1;
    }

    //Allocation with data type
    int *n = (int *)m_rent_alloc(sizeof(int));
    if(n) {
        *n = 10;
        printf("int: %d, address: %p\n", *n, (void *)n);
    }

    //Allocation with pre-defined size
    //It can be KiB, MiB or GiB
    void* block = m_rent_alloc(MiB(16));
    if(block) {
        printf("16 MiB allocated in the address: %p\n", block);
    }

    //Deallocating
    m_rent_dealloc(n);
    m_rent_dealloc(block);

    return 0;
}