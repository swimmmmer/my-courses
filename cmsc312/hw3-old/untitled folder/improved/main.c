// main file
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include "memory.h"

#define SIZE 20

void print_leaks() {
    printf("Memory leaks detected!\n");
}



int main() {
    // program1
    char *p1 = (char *)my_malloc(ALLOC_SIZE);
    char *p2 = (char *)my_calloc(ALLOC_SIZE, sizeof(char));
    char *p3 = (char *)my_realloc(p1, ALLOC_SIZE*2);
    my_free(p3);
    my_free(p2);
    my_free(p1);

    char *p4 = (char *)my_malloc(ALLOC_SIZE*3);
    char *p5 = (char *)my_malloc(ALLOC_SIZE);
    char *p6 = (char *)my_malloc(ALLOC_SIZE*4);
    char *p7 = (char *)my_realloc(p5, ALLOC_SIZE*2);
    my_free(p4);
    my_free(p7);
    my_free(p6);
    my_free(p5);

    char *p8 = (char *)my_malloc(ALLOC_SIZE*3);
    char *p9 = (char *)my_malloc(ALLOC_SIZE*2);
    char *p10 = (char *)my_realloc(p8, ALLOC_SIZE*6);
    char *p11 = (char *)my_calloc(ALLOC_SIZE*2, sizeof(char));
    my_free(p11);
    my_free(p10);
    my_free(p9);
    my_free(p8);

    size_t leak = calculateLeak();
    printf("Memory leak for program1: %ld bytes\n", leak);

    // program2
    char *p12 = (char *)my_malloc(ALLOC_SIZE*5);
    char *p13 = (char *)my_calloc(ALLOC_SIZE*2, sizeof(char));
    char *p14 = (char *)my_realloc(p12, ALLOC_SIZE*3);
    my_free(p13);
    my_free(p14);
    my_free(p12);

    char *p15 = (char *)my_malloc(ALLOC_SIZE*6);
    char *p16 = (char *)my_malloc(ALLOC_SIZE);
    char *p17 = (char *)my_malloc(ALLOC_SIZE*4);
    char *p18 = (char *)my_realloc(p15, ALLOC_SIZE*3);
    my_free(p18);
    my_free(p17);
    my_free(p16);
    my_free(p15);

    char *p19 = (char *)my_malloc(ALLOC_SIZE*4);
    char *p20 = (char *)my_malloc(ALLOC_SIZE*2);
    char *p21 = (char *)my_realloc(p19, ALLOC_SIZE*5);
    char *p22 = (char *)my_calloc(ALLOC_SIZE*3, sizeof(char));
    my_free(p22);
    my_free(p21);
    my_free(p20);
    my_free(p19);

    leak = calculateLeak();
    printf("Memory leak for program2: %ld bytes\n", leak);

    return 0;
    
}
