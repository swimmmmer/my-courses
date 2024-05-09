#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

struct block_meta {
    size_t size;
    size_t overhead;
    struct block_meta *next;
    struct block_meta *prev;
    int free;
    int magic; // For debugging only. TODO: remove this in non-debug mode.
};

struct block_meta *find_free_block(struct block_meta **last, size_t size);
struct block_meta *request_space(struct block_meta* last, size_t size);
struct block_meta *get_block_ptr(void *ptr);
void *my_malloc(size_t size);
void my_free(void *ptr) ;
void *my_realloc(void *ptr, size_t size);
void *my_calloc(size_t nelem, size_t elsize);
size_t calculateLeak();


