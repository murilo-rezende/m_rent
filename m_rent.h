#ifndef M_RENT_H
#define M_RENT_H

#include <stdbool.h>
#include <stddef.h>

//Creates a struct to represent a block of memory in the heap
typedef struct Block {
    bool free;
    size_t size;
    struct Block *next;
    struct Block *prev;
} Block;

extern Block *free_list_head;

//Allocates size bytes from the heap
void *allocate(size_t size);

//Deallocates memory previously requested by allocate() and merge free blocks
void deallocate(void *ptr);

#endif // M_RENT_H