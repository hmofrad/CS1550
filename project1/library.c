/*
 * CS 1550: Graphics library skeleton code for Qemu VM
 * WARNING: This code is the minimal implementation of the project 1.
 *          It is not intended to serve as a reference implementation.
 *          Following project guidelines, a complete implementation
 *          for this project will contain ~300 lines or more.
 * (c) Mohammad H. Mofrad, 2017
 * (e) mohammad.hmofrad@pitt.edu
 */

#include "library.h"

int fid;
struct fb_var_screeninfo var_info;
struct fb_fix_screeninfo fixed_info;
struct termios terminal_settings;
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

    if(ioctl(fid, FBIOGET_VSCREENINFO, &var_info) == -1)
    {
        perror("Error using ioctl");
        exit(1);
    }
    
    if(ioctl(fid, FBIOGET_VSCREENINFO, &fixed_info) == -1)
    {
        perror("Error using ioctl");
        exit(1);
    }
    
    size = var_info.yres_virtual * fixed_info.line_length;
    printf("%d\n", size);
    
    address = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fid, 0);
    if(address == (void *) -1)
    {
        perror("Error mapping memory");
        exit(1);
    }
    
    if(ioctl(STDIN_FILENO, TCGETS, &terminal_settings) == -1)
    {
        perror("Error using ioctl");
        exit(1);
    }

    terminal_settings.c_lflag &= ~(ICANON | ECHO);
    if(ioctl(STDIN_FILENO, TCSETS, &terminal_settings) == -1)
    {
        perror("Error using ioctl");
        exit(1);
    }
}

void draw_pixel(int x, int y, color_t color) {
	if (y >= 480) return; // invalid coordinate
	int coordinate = (y * fixed_info.line_length / sizeof(color_t)) + x;
	*(address + coordinate) = color;
}

//void draw_line(color_t color)
//{
    /* Print a single line */
//    color_t off_p = 0;
//    for(off_p =0; off_p < size; off_p++)
//    {
//        *(address + off_p) = RMASK(c) | GMASK(c) | BMASK(c);
        /* 
          printf("Address(0x%08x), Color(0x%04x) B(0x%04x), G(0x%04x), R(0x%04x) \n",
                (address + off_p), *(address + off_p), BMASK(c), GMASK(c), RMASK(c));
        */      
//    }
//}

void sleep_s(unsigned seconds)
{
   sleep(seconds); /* This is in seconds and not milliseconds */
}

void clear_screen() 
{
    const char cmd[] = "\033[2J";
    write(STDOUT_FILENO, cmd, sizeof(cmd));  /* This will do the trick for fid1*/
}

void exit_graphics() 
{
    /* 
     * Skipping ioctl for reseting the terminal setting for fid1
     * Remove the memory mapping
     * Finally, close fb file desriptor
     */
    
    terminal_settings.c_lflag |= (ICANON | ECHO);

    if(ioctl(STDIN_FILENO, TCSETS, &terminal_settings) == -1) {
        perror("Error using ioctl");
        exit(1);
    }

    if(munmap(address, size) == -1)
    {
        perror("Error unmapping memory");
        exit(1);
    }

    if(!close(fid))
    {
        exit(0);
    }
    else
    {
        perror("Error closing /dev/fb0");
        exit(1);
    }
}
