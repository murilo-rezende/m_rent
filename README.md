# m_rent

`m_rent` is a free-list memory allocator built from scratch in C. Similarly to malloc() and free(), m_rent features allocate() and deallocate().


## Overview

`m_rent` is a free-list memory allocator that keeps track of free blocks in the heap using a **linked list of blocks**.

## Features

- **Word-aligned allocations** — every block size is rounded up to a multiple of `sizeof(void*)` (8 bytes on 64-bit systems), keeping every block's start address properly aligned.
- **First-fit allocation** — walks the block list and hands out the first free block large enough to satisfy a request.
- **Block merging (coalescing)** — when memory is freed, adjacent free blocks (both forward and backward in the list) are merged back into a single larger block, reducing fragmentation.
- **Doubly linked block list** — each block tracks both `next` and `prev`, enabling merging in both directions.

## How it works

Each block of memory is preceded by a small header:

```c
typedef struct Block {
    bool free;
    size_t size;
    struct Block *next;
    struct Block *prev;
} Block;
```

Memory is laid out as a chain of these blocks across the simulated heap:

```
[header][data][header][data][header][data]...
```

- `allocate(size)` rounds `size` up to a word boundary, searches the block list for a free block big enough, splits it if there's meaningful space left over, and returns a pointer to the usable data region (just past the header).
- `deallocate(ptr)` recovers the block header from `ptr` (it sits immediately before the data), marks the block free, and attempts to merge it with its free neighbors.

## Files

| File | Purpose |
|---|---|
| `m_rent.h` | Public interface — the `Block` type and `allocate`/`deallocate` declarations |
| `m_rent.c` | Allocator implementation (heap setup, splitting, merging, allocation logic) |
| `main.c` | Example/test usage |

## Building

```sh
gcc m_rent.c main.c -o m_rent_test
./m_rent_test
```

## Usage

```c
#include "m_rent.h"

int *a = (int *) allocate(sizeof(int));
*a = 42;

deallocate(a);
```

## Status

Work in progress — a learning project for understanding how memory allocators work under the hood (alignment, header/metadata layout, free-list management, splitting, and coalescing).

### Current limitations

- Fixed heap size (1 MiB) — does not grow via `sbrk`/`mmap` if exhausted.
- First-fit strategy only — no best-fit or other allocation strategies implemented.
- Not thread-safe.
