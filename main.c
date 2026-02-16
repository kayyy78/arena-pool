#include <stdio.h>
#include "arena.h"
#include "poolArena.h"

int main()
{
    // Create arena
    mem_arena *arena = arena_create(MB(16), KB(64));
    if (!arena) {
        printf("Arena creation failed\n");
        return 1;
    }

    // Create pool inside arena
    size_t block_size = 64;
    size_t capacity   = 10;

    arena_pool *pool = arena_pool_make(arena, block_size, capacity);
    if (!pool) {
        printf("Pool creation failed\n");
        return 1;
    }

    printf("Pool created with %zu blocks\n", capacity);

    // Allocate some blocks
    void *a = arena_pool_alloc(pool);
    void *b = arena_pool_alloc(pool);
    void *c = arena_pool_alloc(pool);

    printf("Allocated:\n");
    printf("a: %p\n", a);
    printf("b: %p\n", b);
    printf("c: %p\n", c);

    printf("Free blocks left: %zu\n", arena_pool_available_blocks(pool));

    // Free one block
    arena_pool_free(pool, b);
    printf("Freed block b\n");

    printf("Free blocks now: %zu\n", arena_pool_available_blocks(pool));

    // Allocate again
    void *d = arena_pool_alloc(pool);
    printf("Allocated d (should match b): %p\n", d);
    printf("Free blocks left: %zu\n", arena_pool_available_blocks(pool));

    //frees everything
    arena_destroy(arena);

    return 0;
}
