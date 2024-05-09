// main file
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include "memory.h"

#define SIZE 100

void print_leaks() {
    printf("Memory leaks detected!\n");
}

int main() {
    // program1
    double *p1 = (double *)my_malloc(4 * sizeof(double));
    char *p2 = (char *)my_malloc(4 * sizeof(char));

    my_free(p1);
    my_free(p2);

    char *p3 = (char *)my_malloc(4 * sizeof(char));
    double *p4 = (double *)my_malloc(4 * sizeof(double));

    double *p5 = (double *)my_malloc(5 * sizeof(double));

    double *p6 = (double *)my_malloc(sizeof(double));

    my_free(p5);
    my_free(p6);

    double *p7 = (double *)my_malloc(sizeof(double));

    double *p8 = (double *)my_malloc(5 * sizeof(double));
    double *p9 = (double *)my_malloc(5 * sizeof(double));

    my_free(p7);

    double *p10 = (double *)my_malloc(sizeof(double));

    int *p11 = (int *)my_calloc(3, sizeof(int));

    my_free(p9);
    my_free(p11);

    int *p12 = (int *)my_calloc(3, sizeof(int));

    int *p13 = (int *)my_calloc(10, sizeof(int));

    int *p14 = (int *)my_calloc(10, sizeof(int));

    int *p15 = (int *)my_calloc(4, sizeof(int));

    my_free(p14);
    my_free(p15);

    int *p16 = (int *)my_calloc(4, sizeof(int));

    int *p17 = (int *)my_calloc(8, sizeof(int));

    my_free(p16);
    my_free(p17);

    int *p18 = (int *)my_calloc(4, sizeof(int));

    int *p19 = (int *)my_calloc(10, sizeof(int));

    int *p20 = (int *)my_calloc(10, sizeof(int));

    my_free(p3);

    char *p21 = (char *)my_malloc(2 * sizeof(char));

    char *p22 = (char *)my_realloc(p21, 4 * sizeof(char));

    my_free(p4);

    int *p23 = (int *)my_malloc(2 * sizeof(int));

    int *p24 = (int *)my_realloc(p23, 8 * sizeof(int));

    my_free(p8);

    int *p25 = (int *)my_malloc(2 * sizeof(int));

    int *p26 = (int *)my_realloc(p25, 10 * sizeof(int));

    my_free(p10);

    int *p27 = (int *)my_malloc(sizeof(int));

    int *p28 = (int *)my_realloc(p27, 2 * sizeof(int));

    my_free(p12);

    int *p29 = (int *)my_malloc(2 * sizeof(int));

    int *p30 = (int *)my_realloc(p29, 3 * sizeof(int));

    my_free(p13);

    int *p31 = (int *)my_malloc(2 * sizeof(int));

    int *p32 = (int *)my_realloc(p31, 10 * sizeof(int));

    my_free(p18);

    int *p33 = (int *)my_malloc(sizeof(int));

    int *p34 = (int *)my_realloc(p33, 4 * sizeof(int));

    my_free(p19);

    int *p35 = (int *)my_malloc(3 * sizeof(int));

    int *p36 = (int *)my_realloc(p35, 10 * sizeof(int));


    my_free(p20);

    int *p37 = (int *)my_malloc(2 * sizeof(int));

    int *p38 = (int *)my_realloc(p37, 10 * sizeof(int));

    int *p39 = (int *)my_realloc(p22, sizeof(int));






    










    
    size_t leak = calculateLeak();
    printf("Memory leak for program2: %zu bytes\n", leak);

    return 0;
    
}


