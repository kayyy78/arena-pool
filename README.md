# arena-pool

This project implements a virtual-memory-backed arena allocator and a pool allocator built on top of it.

## Features
- Allocates a memory arena an builds a pool on top of it.
- The pool is a set of fixed size blocks that can allocated and freed individually.
- The blocks are stored as a linked list where each block stores the address of the next block.
- The program tracks the amount of free blocks available.

## Notes
This project is inspired by an arena allocator demonstrated by "https://www.youtube.com/@Magicalbat".
