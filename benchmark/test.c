#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../my_vm.h"

#define SIZE 5

int main() {
	srand(time(0));
    printf("Allocating three arrays of 400 bytes\n");
    unsigned int alloc_size = SIZE * SIZE * sizeof(int);
    void *a = myalloc(alloc_size);
    int old_a = (int) a;
    void *b = myalloc(alloc_size);
    void *c = myalloc(alloc_size);
    int x = 1;
    int y, z;
    int i = 0, j = 0;
    int address_a = 0, address_b = 0;
    int address_c = 0;

    printf("Addresses of the allocations: %x, %x, %x\n", (int) a, (int) b, (int) c);

    printf("Storing integers to generate a SIZExSIZE matrix\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            address_a = (unsigned int) a + (i * SIZE * sizeof(int)) + (j * sizeof(int));
            address_b = (unsigned int) b + (i * SIZE * sizeof(int)) + (j * sizeof(int));
            
            x = rand() % 10;
            PutVal((void *) address_a, &x, sizeof(int));
            x = rand() % 10;
            PutVal((void *) address_b, &x, sizeof(int));
        }
    }

    printf("Fetching matrix elements stored in the arrays\n");

	printf("Matrix 1:\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            address_a = (unsigned int) a + (i * SIZE * sizeof(int)) + (j * sizeof(int));
            GetVal((void *) address_a, &y, sizeof(int));
            printf("%d ", y);
        }
        printf("\n");
    }
    
	printf("Matrix 2:\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            address_b = (unsigned int) b + (i * SIZE * sizeof(int)) + (j * sizeof(int));
            GetVal((void *) address_b, &z, sizeof(int));
            printf("%d ", z);
        }
        printf("\n");
    }

    printf("Performing matrix multiplication with itself!\n");
    MatMult(a, b, SIZE, c);

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            address_c = (unsigned int) c + (i * SIZE * sizeof(int)) + (j * sizeof(int));
            GetVal((void *) address_c, &y, sizeof(int));
            printf("%d ", y);
        }
        
        printf("\n");
    }
    
    printf("Freeing the allocations!\n");
    myfree(a, alloc_size);
    myfree(b, alloc_size);
    myfree(c, alloc_size);

    printf("Checking if allocations were freed!\n");
    a = myalloc(alloc_size);
    if ((int) a == old_a)
        printf("free function works\n");
    else
        printf("free function does not work\n");

	print_TLB_missrate();

    return 0;
}
