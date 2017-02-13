/* 
 * Skeleton code for prodcons implementation
 * (C) Mohammad H. Mofrad, 2017  
 *
 */
#ifndef PRODCONS_H_INCLUDED
#define PRODCONS_H_INCLUDED


#include <asm/errno.h>
#include <asm/unistd.h>
#include <asm/mman.h>

#define MAP_SIZE 0x00000FFF

struct cs1550_sem
{
   int value;
   //Some process queue of your devising
};

void  cs1550_down(struct cs1550_sem *);
void  cs1550_up  (struct cs1550_sem *);

#endif
