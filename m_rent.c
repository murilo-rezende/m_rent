#include "m_rent.h"
#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

//Rounds up to a power of 2 number
#define ALIGN_POW2(n) ((n + sizeof(void*) - 1) & ~(sizeof(void*) - 1))

static char *heap = NULL;
static size_t header_size = 0;
static size_t heap_size = 0;
Block *list_head = NULL;

//Inits the heap of free memory
bool init_heap(size_t size) {
    if (heap) return false;

    //Alignment that the heap's starting address must satisfy
    size_t alignment = alignof(void*);

    //Requested heap size, rounded up to the nearest multiple of alignment
    size_t aligned_heap_size = ALIGN_POW2(size);

    //Reservess aligned_heap_size bytes of memory
    //while makes sure that the returned address is a multiple of alignment
    heap = aligned_alloc(alignment, aligned_heap_size);
    
    if (!heap) return false;

    heap_size = aligned_heap_size;
    header_size = ALIGN_POW2(sizeof(Block));

    Block *head = (Block *)heap;
    head->free = true;
    head->next = NULL;
    head->prev = NULL;
    head->size = heap_size - header_size;
    list_head = head;
    return true;
}

//Creates a new block by splitting the free heap by the size requested by the user
void split_free_heap_block(Block *block, size_t size) {
    //Starts the new block after the end of the current block
    //Adds the size of the requested block to occupy the block's bytes
    Block* new_block = (Block*)((char*)(block + 1) + size);

    new_block->size = block->size - size - header_size;
    new_block->free = true;
    new_block->next = block->next;
    new_block->prev = block;

    //Sets the previous pointer of the next block to point to the new block if it exists
    if (new_block->next) {
        new_block->next->prev = new_block;
    }

    block->size = size;
    block->next = new_block;
}

//Merges the current block with the next and previous blocks if they are free
void merge_free_heap_blocks(Block *block) {
    //Merges the current block with the next block if it's free
    if (block->next && block->next->free) {
        block->size += block->next->size + header_size;
        block->next = block->next->next;
        if (block->next) block->next->prev = block;
    }

    //Merges the current block with the previous block if it's free
    if (block->prev && block->prev->free) {
        block->prev->size += block->size + header_size;
        block->prev->next = block->next;
        if (block->prev->next) block->prev->next->prev = block->prev;
    }
}

//Allocates the memory that the user requested
void *allocate(size_t size) {
    if (size == 0) return NULL;

    //If the free list head is NULL, it initializes the heap
    if (!list_head) return NULL;

    //Makes sure the size is aligned
    size = ALIGN_POW2(size);

    //Makes the current node is the head of the linked list
    Block *current = list_head;

    //Iterates through the linked list to find a free block that is large enough to accommodate the requested size
    while(current) {
        if (current->free == true && current->size >= size) {
            split_free_heap_block(current, size);

            //Marks the block as allocated
            current->free = false;
            return (void *)(current + 1); //Returns the pointer to the memory after the header
        }
        current = current->next;
    }

    return NULL; //No free block found
}

void deallocate(void *ptr) {
    if (!ptr) return;

    //Get the block header from the pointer
    Block *block = (Block *)ptr - 1;

    //Frees the memory within the block
    block->free = true;

    ////Merges the current block with the next and previous blocks if they are free
    merge_free_heap_blocks(block);
}
