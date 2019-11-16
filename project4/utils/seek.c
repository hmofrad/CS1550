/*
 * seek.c: Basic file position commands
 * Compile: gcc -o seek -Wall -Werror seek.c
 * Run: ./seek FILENAME
 * (c) Mohammad Hasanzadeh Mofrad, 2019
 * (e) m.hasanzadeh.mofrad@gmail.com 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE        512
#define	MAX_DATA_IN_BLOCK (BLOCK_SIZE)

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
     
     
     
    fseek(fid, 0L, SEEK_END);    // Move to the end of disk
    long disk_size = ftell(fid); // Get the file position == disk size
    fseek(fid, 0L, SEEK_SET);    // Move to the beginning of disk (alternatively do rewind(fid);)
    printf("Disk size = %lu\n", disk_size);

    
    
    int nth = 3;
    long offset = nth * BLOCK_SIZE;
	int ret = fseek(fid, offset, SEEK_SET); // Move to an offset from the beginning of disk
    if(ret) {
        fprintf(stderr, "Error seeking %s\n", disk);
        exit(1);
    }
    long current_position = ftell(fid);
    printf("First seek  from the beginning: offset = %ld, current fid position from the beginning = %ld\n", offset, current_position); 
    
    
    
	ret = fseek(fid, -offset, SEEK_END); // Move to an offset from the end of disk
    if(ret) {
        fprintf(stderr, "Error seeking %s\n", disk);
        exit(1);
    }
    current_position = ftell(fid);
    printf("Second seek from the end:       offset = %ld, current fid position from the end       = %ld\n", offset, disk_size - current_position); 
    
    
    
    long previous_position = current_position;
    offset = 1;
    ret = fseek(fid, offset, SEEK_CUR); // Move to an offset from the current position
    if(ret) {
        fprintf(stderr, "Error seeking %s\n", disk);
        exit(1);
    }
    current_position = ftell(fid);
    printf("Third seek from the end: previous fid position = %ld, current fid position = %ld\n", previous_position, current_position); 
    
    
    
    if(fclose(fid)) {
        fprintf(stderr, "Error closing %s\n", disk);
        exit(1);
    }


    return(0);
}