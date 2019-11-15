/*
 * bitmap.c: Bitmap implementation for disk
 * Compile: gcc -o bitmap -Wall -Werror bitmap.c
 * Run: ./bitmap /dir/test.txt
 *
 * Byte map (MSB <-- LSB)
 * 1536            1280 1279                0
 * |<---    256   ---> | <---   1280    --->|
 * Bit map
 * 12288          10240 10239               0
 * |<---   2048   ---> | <---   10240   --->|
 * Disk map
 * |<---    skip  ---> |10239   Disk   2 1 0| 
 * |///////////////////|x       ....   x x x|
 *
 * MSB is block 10239
 * LSB is block 0
 *
 * (c) Mohammad Hasanzadeh Mofrad, 2019
 * (e) moh18@pitt.edu 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BITS_PER_BYTE     8
#define BLOCK_SIZE        512
#define DISK_SIZE         5242880
#define DISK_NUM_BLOCKS   DISK_SIZE/BLOCK_SIZE
#define BITMAP_COUNT      DISK_NUM_BLOCKS
#define BITMAP_NUM_BLOCKS ((DISK_NUM_BLOCKS/BLOCK_SIZE) + BITS_PER_BYTE - 1)/BITS_PER_BYTE
#define BITMAP_SIZE       BITMAP_NUM_BLOCKS * BLOCK_SIZE * sizeof(unsigned char)
#define BITMAP_START      BITMAP_COUNT - 1
#define BITMAP_END        (BITMAP_SIZE * BITS_PER_BYTE) - BITMAP_COUNT

char* bitmap;

unsigned char get_bit(unsigned int block) {
    unsigned int byte  =  block / BITS_PER_BYTE;
    unsigned int bit   =  block % BITS_PER_BYTE;
    unsigned char mask = 1 << bit;
    return((bitmap[byte] & mask) != 0);
}

void set_bit(unsigned int block) {
    unsigned int byte  =  block / BITS_PER_BYTE;
    unsigned int bit   =  block % BITS_PER_BYTE;
    unsigned char mask = 1 << bit;
    bitmap[byte] |= mask;
}

void toggle_bit(unsigned int block) {
    unsigned int byte  =  block / BITS_PER_BYTE;
    unsigned int bit   =  block % BITS_PER_BYTE;
    unsigned char mask = 1 << bit;
    bitmap[byte] ^= mask;
}

void clear_bit(unsigned int block) {
    unsigned int byte  =  block / BITS_PER_BYTE;
    unsigned int bit   =  block % BITS_PER_BYTE;
    unsigned char mask = ~(1 << bit);
    bitmap[byte] &= mask;
}

void print_bits() {
    unsigned int i = 0;
    unsigned char j = 0;
    for(i = BITMAP_COUNT - 1; i+1 >= 1; i--) {
        j = get_bit(i);
        printf("Block[%5d]=%d\n", i, j);
    }
}

int main(int argc, char** argv) {
    
    printf("Disk size  = %d\n", DISK_SIZE);
    printf("Block size = %d\n", BLOCK_SIZE);
    printf("Total Number of disk blocks      = %d\n", DISK_NUM_BLOCKS);
    printf("Number of disk blocks for bitmap = %d\n", BITMAP_NUM_BLOCKS);
    
    bitmap = (char*) malloc(BITMAP_SIZE);
    memset(bitmap, 0, BITMAP_SIZE);
    
    /*
    // Examples
    unsigned int b = 0;
    printf("%d %d\n", b, get_bit(b));
    set_bit(b);
    printf("%d %d\n", b, get_bit(b));
    clear_bit(b);
    printf("%d %d\n", b, get_bit(b));
    toggle_bit(b);
    printf("%d %d\n", b, get_bit(b));
    //print_bits();
    */
    
    free(bitmap);
    return(0);
}