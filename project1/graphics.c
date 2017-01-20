/*
 * CS 1550: Graphics library skeleton code for Qemu VM
 * WARNING: This code is the minimal implementation of the project 1.
 *          It is not intended to serve as a reference implementation.
 *          Following project guidelines, a complete implementation
 *          for this project will contain ~300 lines or more.
 * Compile: gcc -o graphics graphics.c # On Qemu VM
 * Execute: ./graphics # On Qemu VM
 * (C) Mohammad H. Mofrad, 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <sys/mman.h>

typedef unsigned short color_t;    // |15 11|10  5|4  0|
                                   // |red  |green|blue|
                                   //   5   + 6   + 5  =  16
#define BMASK(c) (c & 0x001F) // Blue mask
#define GMASK(c) (c & 0x07E0) // Green mask
#define RMASK(c) (c & 0xF800) // Red mask

int main(int argc, char *argv[])
{
    // Open fb file descriptor
    int fid;
    fid = open("/dev/fb0", O_RDWR);
    if(fid == -1)
    {
        fprintf(stderr, "Error opening /dev/fb0\n");
        exit(1);
    }
    size_t size = 640 * 1; // Horizontal resolution (1 row)
                            // Do not hardcode size in your implementation
    color_t *address;       // Pointer to the shared memory space with fb
    // Add a memory mapping
    address = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fid, 0);
    if(address == (void *) -1)
    {
        fprintf(stderr, "Error mapping memory\n");
        exit(1);
    }

    color_t colorb = 0x001F; // Some blue color
    color_t colorg = 0x07E0; // Some green color
    color_t colorr = 0xF800; // Some red color
    
    color_t off_p = 0;
    // Print 1 white lines
    for(off_p =0; off_p < size; off_p++)
    {
        *(address + off_p) = RMASK(colorr) | GMASK(colorg) | BMASK(colorb);
        //printf("Address(0x%08x), Color(0x%04x) B(0x%04x), G(0x%04x), R(0x%04x) \n", (address + off_p), *(address + off_p), BMASK(colorb), GMASK(colorg), RMASK(colorr));
    }

    // Remove the memory mapping
    if(munmap(address, size) == -1)
    {
        fprintf(stderr, "Error unmapping memory\n");
        exit(1);
    }
    // Close fb file descriptor
    if(!close(fid))
    {
        exit(0);
    }
    else
    {
        fprintf(stderr, "Error closing /dev/fb0\n");
        exit(1);
    }
}
