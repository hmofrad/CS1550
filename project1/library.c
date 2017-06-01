/*
 * CS 1550: Graphics library code skeleton for Qemu VM
 * WARNING: This code is the minimal implementation of the project 1.
 *          It is not intended to serve as a reference implementation.
 *          Following project guidelines, a complete implementation
 *          for this project will contain ~300 lines or more.
 * (c) Mohammad H. Mofrad, 2017
 * (e) mohammad.hmofrad@pitt.edu
 */

#include "library.h"

int fid;
/* http://www.ummon.eu/Linux/API/Devices/framebuffer.html */
struct fb_var_screeninfo var_info;
struct fb_fix_screeninfo fixed_info;

/* http://man7.org/linux/man-pages/man3/termios.3.html */
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
    
    /* Determine virtual resolution */
    if(ioctl(fid, FBIOGET_VSCREENINFO, &var_info) == -1)
    {
        perror("Error using ioctl");
        exit(1);
    }
    
    /* Determine bit depth */
    if(ioctl(fid, FBIOGET_FSCREENINFO, &fixed_info) == -1)
    {
        perror("Error using ioctl");
        exit(1);
    }
    
    size = var_info.yres_virtual * fixed_info.line_length; // 614400 = 480 * 1280
    
    /* Total size of the mmap()’ed region */
    address = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fid, 0);
    if(address == (void *) -1)
    {
        perror("Error mapping memory");
        exit(1);
    }
    
    //  disable keypress echo and buffering the keypresses
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

void draw_pixel(int x, int y, color_t color)
{
    if (y >= 480)  // Invalid coordinate
    {
        return;
    }
    int coordinate = (y * fixed_info.line_length / sizeof(color_t)) + x;
    *(address + coordinate) = color;
}

void sleep_s(unsigned seconds)
{
   sleep(seconds); // This is in seconds
}

void clear_screen() 
{
    const char cmd[] = "\033[2J"; // ANSI escape code
    write(STDOUT_FILENO, cmd, sizeof(cmd));  // This will do the trick
}

void exit_graphics() 
{
    // Reseting the terminal settings
    terminal_settings.c_lflag |= (ICANON | ECHO);

    if(ioctl(STDIN_FILENO, TCSETS, &terminal_settings) == -1) {
        perror("Error using ioctl");
        exit(1);
    }
    
    // Remove the memory mapping
    if(munmap(address, size) == -1)
    {
        perror("Error unmapping memory");
        exit(1);
    }
    
    // close fb file desriptor
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
