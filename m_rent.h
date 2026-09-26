#ifndef M_RENT_H
#define M_RENT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef uint64_t u64;

#define KiB(x) (u64)((u64)(x) << 10)
#define MiB(x) (u64)((u64)(x) << 20)
#define GiB(x) (u64)((u64)(x) << 30)

typedef struct MemBlock {
    bool free;
    size_t size;
    struct MemBlock *next;
    struct MemBlock *prev;
} MemBlock;

bool m_rent_init(size_t size);
void *m_rent_alloc(size_t size);
void m_rent_dealloc(void *ptr);

#endif