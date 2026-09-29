# m_rent

`m_rent` is a memory allocator built in C, it maintains a linked list of memory blocks while keeping track of used and free nodes.

## Features

- **Aligned allocations** — every block size is rounded up to a multiple of `sizeof(void*)` (8 bytes on 64-bit systems), making sure every block is properly aligned.
- **First-fit allocation** — walks the block list and hands out the first free block large enough to satisfy a request.
- **Block merging** — when memory is freed, adjacent free blocks (both forward and backward in the list) are merged back into a single larger block, reducing fragmentation.
- **Doubly linked block list** — each block tracks both `next` and `prev`, enabling merging in both directions.
- 
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

int *a = (int *) m_rent_alloc(sizeof(int));
*a = 42;

m_rent_dealloc(a);
```

## Status

In progress...
