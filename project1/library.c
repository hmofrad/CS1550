/*
 * CS 1550: Graphics library skeleton code for Qemu VM
 * WARNING: This code is the minimal implementation of the project 1.
 *          It is not intended to serve as a reference implementation.
 *          Following project guidelines, a complete implementation
 *          for this project will contain ~300 lines or more.
 * (c) Mohammad H. Mofrad, 2017
 */

#include "library.h"

int fid;
int fid1 = 1;
size_t size;
color_t *address;

void init_graphics()
{
    /* Open fb file descriptor */
    fid = open("/dev/fb0", O_RDWR);
    if(fid == -1)
    {
        perror("Error opening /dev/fb0");
        exit(1);
    }

    /* 
     * Horizontal resolution (1 row)
     * Do not hardcode size in your implementation
     * We skip some ioctls here
     * Then add the memory mapping using
     * "address" which is the pointer to the shared memory space with frame buffer (fb)
     */
    size = 640 * 1; 
    address = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fid, 0);
    if(address == (void *) -1)
    {
        fprintf(stderr, "Error mapping memory\n");
        exit(1);
    }
    /* Skipping ioctls for teminal settings for fid1 */
}

void draw_line(color_t c)
{
    /* Print a single line */
    color_t off_p = 0;
    for(off_p =0; off_p < size; off_p++)
    {
        *(address + off_p) = RMASK(c) | GMASK(c) | BMASK(c);
        /* 
          printf("Address(0x%08x), Color(0x%04x) B(0x%04x), G(0x%04x), R(0x%04x) \n",
                (address + off_p), *(address + off_p), BMASK(c), GMASK(c), RMASK(c));
        */      
    }
}

void sleep_s(unsigned seconds)
{
   sleep(seconds); /* This is in seconds and not milliseconds */
}

void clear_screen() 
{
    write(fid1, "\033[2J", 4);  /* This will do the trick for fid1*/
}

void exit_graphics() 
{
    /* 
     * Skipping ioctl for reseting the terminal setting for fid1
     * Remove the memory mapping
     * Finally, close fb file desriptor
     */

    if(munmap(address, size) == -1)
    {
        fprintf(stderr, "Error unmapping memory\n");
        exit(1);
    }

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
