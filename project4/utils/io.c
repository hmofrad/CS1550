/*
 * io.c: Basic input/output operations
 * Compile: gcc -o io -Wall -Werror io.c
 * Run: ./io FILENAME
 * (c) Mohammad Hasanzadeh Mofrad, 2019
 * (e) m.hasanzadeh.mofrad@gmail.com 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE        512
#define	MAX_DATA_IN_BLOCK (BLOCK_SIZE)

struct cs1550_disk_block {
	char data[MAX_DATA_IN_BLOCK];
};

int main(int argc, char** argv) {
    
    if(argc != 2) {
        fprintf(stderr, "USAGE: %s DISK\n",argv[0]);
        
        exit(1);
    }
    
    char *disk = argv[1];
    FILE *fid = fopen(disk, "rb"); // Open with read pemission 
    
    if(!fid){
		fprintf(stderr,"Error opening %s\n", disk);
        fprintf(stderr,"Create the %s using: dd bs=1K count=5K if=/dev/zero of=.disk\n", disk);
		exit(1);
	}
    
    /* Read first block */
    struct cs1550_disk_block block;
    memset(block.data, 0, sizeof(struct cs1550_disk_block));
    
    int block_size = sizeof(struct cs1550_disk_block);
    int num_blocks = 1;
    long num_read_blocks = fread(&block.data, block_size, num_blocks, fid); // Read 1 block of 512
    if(num_blocks != num_read_blocks) {
        fprintf(stderr, "Error reading %s\n", disk);
        exit(1);
    }
    
    if(fclose(fid)) {
        fprintf(stderr, "Error closing %s\n", disk);
        exit(1);
    }
    
    int i = 0;
    for(i = 0; i < BLOCK_SIZE; i++) {
        block.data[i] = 'a' + (i % 27);
    }
    
    /* Write int first block */
    fid = fopen(disk, "rb+"); // Open with read/write permission
    if(!fid){
		fprintf(stderr,"Error opening %s\n", disk);
        fprintf(stderr,"Create the %s using: dd bs=1K count=5K if=/dev/zero of=.disk\n", disk);
		exit(1);
	}   
    
    int num_write_blocks = fwrite(&block.data, block_size, 1, fid);
    if(num_blocks != num_write_blocks) {
        fprintf(stderr, "Error writing %s\n", disk);
        exit(1);
    }
    
    if(fclose(fid)) {
        fprintf(stderr, "Error closing %s\n", disk);
        exit(1);
    }

    return(0);
}