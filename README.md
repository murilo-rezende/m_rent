# m_rent

`m_rent` is a memory allocator built from scratch in C.


## Overview

`m_rent` is a free memory list allocator that keeps track of free blocks in the heap using a **linked list of blocks**.

## Features

- **Aligned allocations** — every block size is rounded up to a multiple of `sizeof(void*)` (8 bytes on 64-bit systems), making sure every block is properly aligned.
- **First-fit allocation** — walks the block list and hands out the first free block large enough to satisfy a request.
- **Block merging (coalescing)** — when memory is freed, adjacent free blocks (both forward and backward in the list) are merged back into a single larger block, reducing fragmentation.
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

int *a = (int *) allocate(sizeof(int));
*a = 42;

deallocate(a);
```

## Status

Work in progress...

### Current limitations

- Fixed heap size (1 MiB) — does not grow via `sbrk`/`mmap` if exhausted.
- First-fit strategy only — no best-fit or other allocation strategies implemented.
- Not thread-safe.
