/*
 * CS 1550: Header file for Virtual Memory skeleton code
 * with a single level 32-Bit page table
 * (c) Mohammad H. Mofrad, 2016
 * (e) hasanzadeh@cs.pitt.edu
 *
 * Level 1 Page Table   PAGE FRAME
 * 31------------- 12 | 11 ------------- 0
 * |PAGE TABLE ENTRY  | PHYSICAL OFFSET  |
 * -------------------------------------
 * <-------20-------> | <-------12------->
 *
*/


#ifndef _VMSIM_INCLUDED_H
#define _VMSIM_INCLUDED_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Debug levels
#define ALL
#define DEBUG
#define INFO


// 32-Bit page table constants
#define PAGE_SIZE_4KB   4096
#define PT_SIZE_1MB     1048576

#define PAGE_SIZE_BYTES 4
#define PTE_SIZE_BYTES  4

// Macros to extract pte/frame index
#define PTE32_INDEX(x)  (((x) >> 12) & 0xfffff)
#define FRAME_INDEX(x)  ( (x)        &   0x3ff)

// 32-Bit memory frame data structure
struct frame_struct
{
   unsigned int frame_number;
   unsigned int *physical_address;
   unsigned int virtual_address;
   struct pte_32 *pte_pointer;
   struct frame_struct *next;
};

// 32-Bit Root level Page Table Entry (PTE) 
struct pte_32
{
   unsigned int present;
   unsigned int dirty;
   unsigned int *physical_address;
};

// Handle page fault function
struct frame_struct * handle_page_fault(unsigned int);

// Fifo page replacement algorithm
int fifo();

#endif
