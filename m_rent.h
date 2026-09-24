#ifndef M_RENT_H
#define M_RENT_H

#include <stdbool.h>
#include <stddef.h>

typedef uint64_t u64;

#define KiB(x) (u64)((u64)(x) << 10)
#define MiB(x) (u64)((u64)(x) << 20)
#define GiB(x) (u64)((u64)(x) << 30)

//Creates a struct to represent a block of memory in the heap
typedef struct Block {
    bool free;
    size_t size;
    struct Block *next;
    struct Block *prev;
} Block;

extern Block *free_list_head;

//Initiate the heap size by receiving the desired byte size
bool init_heap(size_t heap_size);

//Allocates size bytes from the heap
void *allocate(size_t size);

//Deallocates memory previously requested by allocate() and merge free blocks
void deallocate(void *ptr);

#endif // M_RENT_H