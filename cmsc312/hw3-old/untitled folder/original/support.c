#include "memory.h"
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


#define META_SIZE sizeof(struct block_meta)



void *global_base = NULL; // head of linked list

struct block_meta *find_free_block(struct block_meta **last, size_t size) {
    struct block_meta *current = global_base;
    while (current && !(current->free && current->size >= size)) {
        *last = current;
        current = current->next;
    }
    current->overhead = current->size - size;
    return current;
}

struct block_meta *request_space(struct block_meta* last, size_t size) {
    struct block_meta *block;
    block = sbrk(0);
    void *request = sbrk(size + META_SIZE);
    assert((void*)block == request); // Not thread safe.
    if (request == (void*) -1) {
        
    }
    if (last) { // NULL on first request.
        
    }
    block->size = size;
    block->next = NULL;
    block->free = 0;
    block->magic = 0x12345678;
    return block;
}

struct block_meta *get_block_ptr(void *ptr) {
    return (struct block_meta*)ptr - 1;
}

void *my_malloc(size_t size) {
    struct block_meta *block;
    // TODO: align size?
    if (size <= 0) {
        return NULL;
    }
    if (!global_base) { // First call.
        block = request_space(NULL, size);
        if (!block) {
            return NULL;
        }
        global_base = block;
    } else {
        struct block_meta *last = global_base;
        block = find_free_block(&last, size);
        if (!block) { // Failed to find free block.
            block = request_space(last, size);
            if (!block) {
                return NULL;
            }
        } else { // Found free block
        // TODO: consider splitting block here.
            block->free = 0;
            block->magic = 0x77777777;
        }
    }
    return(block+1);
}

void my_free(void *ptr) {
    if (!ptr) {
        return;
    }
    // TODO: consider merging blocks once splitting blocks is implemented.
    struct block_meta* block_ptr = get_block_ptr(ptr);
    block_ptr->overhead = META_SIZE;
    assert(block_ptr->free == 0);
    assert(block_ptr->magic == 0x77777777 || block_ptr->magic == 0x12345678);
    block_ptr->free = 1;
    block_ptr->magic = 0x55555555;
}

void *my_realloc(void *ptr, size_t size) {
    if (!ptr) {
        // NULL ptr. realloc should act like malloc.
        return my_malloc(size);
    }
    if (size == 0) {
        // size == 0. realloc should act like free.
        my_free(ptr);
        return NULL;
    }
    struct block_meta* block_ptr = get_block_ptr(ptr);
    if (block_ptr->size >= size) {
        // We have enough space. Could free some once we implement split.
        return ptr;
    }
    // Need to really realloc. Malloc new space and free old space.
    // Then copy old data to new space.
    void *new_ptr;
    new_ptr = my_malloc(size);
    if (!new_ptr) {
        return NULL; // TODO: set errno on failure.
    }
    memcpy(new_ptr, ptr, block_ptr->size);
    my_free(ptr);
    return new_ptr;
}

void *my_calloc(size_t nelem, size_t elsize) {
    size_t size = nelem * elsize; // TODO: check for overflow.
    void *ptr = my_malloc(size);
    memset(ptr, 0, size);
    return ptr;
}

size_t calculateLeak() {
    struct block_meta *current = global_base;
    size_t memoryLeak = 0;
    while(current) {
        memoryLeak += META_SIZE;
        memoryLeak += current->overhead;
        current = current->next;
    }

    return memoryLeak;

}