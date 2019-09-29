/*
 pointer.c: Some pointer arithmetic examples
 (c) Mohammad Hasanzadeh Mofrad, 2019
 (e) moh18@pitt.edu
 Compile: gcc -o pointer pointer.c
 Run: ./pointer
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

void allocate(void** ptr, unsigned long mmap_size) {
    *ptr = mmap(NULL, mmap_size, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0);
    if(*ptr == NULL) {
        fprintf(stderr, "Error on allocating memory of size %lu\n", mmap_size);
        exit(0);
    }
    memset(*ptr, 0, mmap_size);  
}

void deallocate(void** ptr, unsigned long mmap_size) {
    int ret = munmap(*ptr, mmap_size);
    if(ret == -1) {
        fprintf(stderr, "Error on deallocating memory of size %lu\n", mmap_size);
        exit(0);
    }
    *ptr = NULL;
}

void* base_ptr; // Global pointer

void allocate_an_integer() {
    unsigned long sz = sizeof(int);
    allocate(&base_ptr, sz);
    int* a = base_ptr; // Copying a void pointer to an int pointer
    *a = 10;
    printf("       a = %d (value)        a = %p (address)\n", *a, a);
    printf("base_ptr = %d (value) base_ptr = %p (address)\n", *((int*) base_ptr), base_ptr); // Casting a void pointer to int
    deallocate(&base_ptr, sz);    
}

void allocate_an_array() {
    unsigned long sz = sizeof(int) * 3;
    allocate(&base_ptr, sz);
    int* a = base_ptr;
    int* b = a + 1;
    int* c = a + 2;
    *a = 10;
    *b = 15;
    *c = *a + *b;
    
    printf("       a = %d (value)        a = %p (address)\n", *a, a);
    printf("       b = %d (value)        b = %p (address)\n", *b, b);
    printf("       c = %d (value)        c = %p (address)\n", *c, c);
    deallocate(&base_ptr, sz);   
}

void allocate_an_array_in_a_wrong_way() {
    unsigned long sz = sizeof(int) * 3;
    allocate(&base_ptr, sz);
    int* a = base_ptr;
    int* b = base_ptr + 1;
    int* c = base_ptr + 2;
    *a = 10;
    *b = 15;
    *c = *a + *b;
    
    printf("       a = %d (value)        a = %p (address)\n", *a, a);
    printf("       b = %d (value)        b = %p (address)\n", *b, b);
    printf("       c = %d (value)        c = %p (address)\n", *c, c);
    deallocate(&base_ptr, sz);   
}


int main(int argc, char** argv) {
    printf("1st scenario: Allocate an integer\n");
    allocate_an_integer();
    printf("\n2nd scenario: Allocate an array of integer\n");
    allocate_an_array();
    printf("\n3rd scenario: A wrong way of wokring with a pointer to an array of integers\n");
    allocate_an_array_in_a_wrong_way();
    return(0);
}
