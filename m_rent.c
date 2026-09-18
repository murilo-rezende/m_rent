#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

//Sets the HEAP_SIZE as 1 MiB
static const size_t HEAP_SIZE = 1024 * 1024;

//Rounds up n to the next multiple of bytes
//It guarantees that every block's size is a multiple of the pointer size
static inline size_t align(size_t n) {
    return (n + sizeof(void*) - 1) & ~(sizeof(void*) - 1);
}

//Aligns the memory address that the compiler is gonna use to a multiple of 8
//Creates an array to represent the heap
//Creates a char to represent exactly 1 byte (8 bits)
static alignas(sizeof(void*)) char heap[HEAP_SIZE];

typedef struct Block {
    bool free;
    size_t size;
    struct Block *next;
    struct Block *prev;
} Block;

//Inits the head of the free memory linked list
void init_heap() {
    Block *head = (Block *) heap;

    head->free = true;
    head->next = NULL;
    head->prev = NULL;
    head->size = HEAP_SIZE - sizeof(Block);
}

void allocate(size_t size, Block* head) {
    if (size == 0) return NULL;

    if (!head) init_heap();

    //Makes sure the size is aligned
    size = align(size);



    


}

void deallocate(void *ptr) {

}