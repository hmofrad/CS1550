/* 
 * Graphics Library header file
 * (c) Mohammad H. Mofrad, 2017
 */

#ifndef _LIBRARY_INCLUDED_H
#define _LIBRARY_INCLUDED_H

#include <stdlib.h>
#include <stdio.h>

#include <linux/fb.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <termios.h>

typedef unsigned short color_t;    // |15 11|10  5|4  0|
                                   // |red  |green|blue|
                                   //   5   + 6   + 5  =  16 bits
// Macros to extract RGB colors 
#define BMASK(c) (c & 0x001F) // Blue mask
#define GMASK(c) (c & 0x07E0) // Green mask
#define RMASK(c) (c & 0xF800) // Red mask

void clear_screen();
void init_graphics();
void exit_graphics();
void draw_line(color_t c);

#endif
