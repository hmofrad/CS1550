/*
 * CS 1550: Source file for Virtual Memory skeleton code
 * (c) Mohammad H. Mofrad, 2016
 * (e) hasanzadeh@cs.pitt.edu
 */
 
#include "vmsim.h"

#undef ALL

int numframes;
unsigned int *physical_memory;

int main(int argc, char *argv[])
{
  /*
   * Add sanity check for input arguments
   * Open the memory trace file 
   * and store it in an array
   */
   
   FILE *file;
   if((argc == 6) && (!strcmp(argv[1],"-n")) && (!strcmp(argv[3], "-a")) && (!strcmp(argv[4], "fifo")) \
                  && ((!strcmp(argv[5], "gcc.trace")) || (!strcmp(argv[5], "swim.trace"))))
   {
      numframes = atoi(argv[2]);
      file = fopen(argv[5],"rb");
      if(!file)
      {
         fprintf(stderr, "USAGE: %s -n <numframes> -a <fifo> <tracefile>\n", argv[0]);
         fprintf(stderr, "Error on opening the trace file\n");
         exit(1); 
      }
   }
   else
   {
      fprintf(stderr, "USAGE: %s -n <numframes> -a <fifo> <tracefile>\n", argv[0]);
      exit(1); 
   }

   /* 
    * Calculate the trace file's length
    * and read in the trace file
    * and write it into addr_arr and mode_arr arrays 
    */

   unsigned int len = 0;
   unsigned int addr = 0;
   unsigned char mode = NULL;

   // Calculate number of lines in the trace file
   while(fscanf(file, "%x %c", &addr, &mode) == 2)
   {
      len++;
   }
   rewind(file);

   unsigned int addr_arr[len];
   unsigned char mode_arr[len];
   unsigned int i = 0;

   // Store the memory accesses 
   while(fscanf(file, "%x %c", &addr_arr[i], &mode_arr[i]) == 2)
   {
      #ifdef ALL
         printf("\'0x%08x %c\'\n", addr_arr[i], mode_arr[i]);
      #endif
      i++;
   }

   // Initialize the physical memory data structure
   physical_memory = malloc(PAGE_SIZE_4KB * numframes);
   if(!physical_memory)
   {
      fprintf(stderr, "Error on mallocing memory\n");
   }
   memset(physical_memory, 0, PAGE_SIZE_4KB * numframes);

   #ifdef DEBUG
      for(i = 0; i < numframes; i++)
      {
         printf("%10d: New chunk of memory at %ld(0x%08x)\n", i, physical_memory + \
               (i * PAGE_SIZE_4KB)/PAGE_SIZE_BYTES, physical_memory + \
               (i * PAGE_SIZE_4KB)/PAGE_SIZE_BYTES);
      }
   #endif

   // Initialize the page table data structure




   


   if(!fclose(file))
   {
      return(0);
   }
   else
   { 
      fprintf(stderr, "Error on closing the trace file\n");
      exit(1);
   }




   return(0);
}
