/*
 * CS 1550: Header file for Virtual Memory skeleton code
 * (C) Mohammad H. Mofrad, 2016
 */

#ifndef _VMSIM_INCLUDED_H
#define _VMSIM_INCLUDED_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define DEBUG
#define ALL

#define PAGE_SIZE_4KB   4096
#define PAGE_SIZE_BYTES 4

struct frame_struct
{
   int frame_number;
   unsigned int *physical_address;
   unsigned int *virtual_address;
   struct pte_32 *pte_pointer;
   struct frame_struct *next;
};

struct page_struct
{
   int page_number;
};

// 32-Bit Root level Page Table Entry (PTE) 
struct pte_32
{
   unsigned int present;
   unsigned int *address;
};


#endif
