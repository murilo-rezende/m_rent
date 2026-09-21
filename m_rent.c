#include "m_rent.h"
#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

//Sets the HEAP_SIZE as 1 MiB
#define HEAP_SIZE (1024 * 1024)

//Rounds up n to the next multiple of bytes
//It guarantees that every block's size is a multiple of the pointer size
static inline size_t align(size_t n) {
    return (n + sizeof(void*) - 1) & ~(sizeof(void*) - 1);
}

//Aligns the memory address that the compiler is gonna use to a multiple of 8
//Creates an array to represent the heap
//Creates a char to represent exactly 1 byte (8 bits)
static alignas(sizeof(void*)) char heap[HEAP_SIZE];

//Keeps track of the size of the header of each block
static size_t HEADER_SIZE;

//Initialize the head of the free memory linked list to NULL
Block *free_list_head = NULL;

//Inits the head of the free memory linked list
Block *init_heap() {
    Block *head = (Block *) heap;

    //Aligns the size of the header to a multiple of 8
    HEADER_SIZE = align(sizeof(Block));

    head->free = true;
    head->next = NULL;
    head->prev = NULL;

    //Sets the free size avaiable on the heap excluding the metadata of the header
    head->size = HEAP_SIZE - HEADER_SIZE; 

    return head;
}

//Creates a new block by splitting the free heap by the size requested by the user
void split_free_heap_block(Block *block, size_t size) {
    //Starts the new block after the end of the current block
    //Adds the size of the requested block to occupy the block's bytes
    Block* new_block = (Block*)((char*)(block + 1) + size);

    new_block->size = block->size - size - HEADER_SIZE;
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
        block->size += block->next->size + HEADER_SIZE;
        block->next = block->next->next;
        if (block->next) block->next->prev = block;
    }

    //Merges the current block with the previous block if it's free
    if (block->prev && block->prev->free) {
        block->prev->size += block->size + HEADER_SIZE;
        block->prev->next = block->next;
        if (block->prev->next) block->prev->next->prev = block->prev;
    }
}

//Allocates the memory that the user requested
void *allocate(size_t size) {
    if (size == 0) return NULL;

    //If the free list head is NULL, it initializes the heap
    if (!free_list_head) free_list_head = init_heap();

    //Makes sure the size is aligned
    size = align(size);

    //Makes the current node is the head of the linked list
    Block *current = free_list_head;

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
