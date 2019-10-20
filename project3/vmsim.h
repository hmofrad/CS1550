/*
 * vmsim.h: Virtual memory header file
 * (c) Mohammad Hasanzadeh Mofrad, 2019
 * (e) moh18@pitt.edu
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

// 32-Bit Root level Page Table Entry (PTE) 
struct pte_32 {
   char present;
   unsigned int* physical_address;
};

// Macros to extract pte/frame index
#define FRAME_INDEX(x)  ( (x)        &   0xfff)
#define PTE32_INDEX(x)  (((x) >> 12) & 0xfffff)

// 4KB (2^12) page size
#define PAGE_SIZE_4KB   4096    
// Smallest addressable unit in a page
#define PAGE_SIZE_UNITS 4       
// Page table size = Maximum size of the 32-bit memory (4GB)
// divided by page size (4kB): 2^32 / 2^12 = 2^20 (1MB)
#define PT_SIZE_1MB     1048576 
// Page table entry size
#define PTE_SIZE_BYTES sizeof(struct pte_32*)

// 32-Bit memory frame data structure
struct frame_struct {
   unsigned int frame_number;
   unsigned int* physical_address;
   unsigned int virtual_address;
   struct pte_32* pte_pointer;
   struct frame_struct* next;
};

// Number of physical frames
uint32_t numframes;
// Physical memory
unsigned int* physical_frames = NULL;
// Page Table
struct pte_32** page_table = NULL;
// Page Table Entry
struct pte_32* pte = NULL;
// Handle page fault function
struct frame_struct* handle_page_fault(unsigned int);

// Fifo page replacement algorithm
int fifo();
// Fifo page replacement current index
int current_index = -1;

// Allocate dynamic memory
void* allocate(unsigned long int size);

// Deallocate dynamic memory
void* deallocate(void** ptr, unsigned long int size);

#endif
