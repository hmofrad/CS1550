/* 
 * Graphics Library header file
 * (c) Mohammad H. Mofrad, 2017
 * (e) mohammad.hmofrad@pitt.edu
 */

#ifndef _LIBRARY_INCLUDED
#define _LIBRARY_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <termios.h>

typedef unsigned short color_t;    // |15 11|10  5|4  0|
                                   // |red  |green|blue|
                                   //   5   + 6   + 5  =  16 bits

void clear_screen();
void init_graphics();
void exit_graphics();
void draw_pixel(int x, int y, color_t color);

#endif
