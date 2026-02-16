#include <stdio.h>
#include "arena.h"

typedef struct {
    mem_arena* arena_source;
    void* mem_start;
    size_t block_size;
    size_t capacity;
    size_t free_count;
    void* free_list;
} arena_pool;

arena_pool *arena_pool_make(mem_arena *arena, size_t block_size, size_t capacity);
void* arena_pool_alloc(arena_pool *pool);
void arena_pool_free(arena_pool *pool, void *block);
size_t arena_pool_available_blocks(arena_pool *pool);
