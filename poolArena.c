#include "poolArena.h"


arena_pool *arena_pool_make(mem_arena *arena, size_t block_size, size_t capacity) {
    if(!arena || block_size == 0 || capacity == 0) {
        return NULL;
    }

    size_t align = sizeof(void *);
    block_size = ALIGN_UP_POW2(block_size, align);
    if(block_size < align) {
        block_size = align;
    }

    arena_pool *pool = PUSH_STRUCT(arena, arena_pool);
    if(!pool) return NULL;

    void* memory = arena_push(arena, block_size * capacity, 0);
    if(!memory) return NULL;

    pool->arena_source = arena;
    pool->mem_start = memory;
    pool->capacity = capacity;
    pool->block_size = block_size;
    pool->free_count = capacity;

    unsigned char *current = (unsigned char*)memory;
    for(size_t i = 0; i < capacity - 1; i++) {
        void* next = current + block_size;
        *(void **)current = next;
        current += block_size;
    }

    *(void**)current = NULL;
    pool->free_list = memory;

    return pool;
}

void* arena_pool_alloc(arena_pool *pool) {
    if (!pool || pool->free_list == NULL) {
        return NULL;
    }

    void *block = pool->free_list;
    pool->free_list = *(void**)block;

    pool->free_count--;

    return block;
}

void arena_pool_free(arena_pool *pool, void *block) {
    if(!pool || !block) {
        return;
    }

    *(void**)block = pool->free_list;
    pool->free_list = block;

    pool->free_count++;
}

size_t arena_pool_available_blocks(arena_pool *pool) {
    return pool->free_count;
}