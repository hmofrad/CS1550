/*
 * CS 1550: Source file for Virtual Memory skeleton code
 * (c) Mohammad H. Mofrad, 2016
 * (e) hasanzadeh@cs.pitt.edu
 */
 
#include "vmsim.h"

#undef ALL

int numframes;
unsigned int *physical_frames;

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

   unsigned int address_array[len];
   unsigned char mode_array[len];
   unsigned int i = 0;

   // Store the memory accesses 
   while(fscanf(file, "%x %c", &address_array[i], &mode_array[i]) == 2)
   {
      #ifdef ALL
         printf("\'0x%08x %c\'\n", address_array[i], mode_array[i]);
      #endif
      i++;
   }

   if(!fclose(file))
   {
      ; // Noop
   }
   else
   {
      fprintf(stderr, "Error on closing the trace file\n");
      exit(1);
   }




   // Initialize the physical memory address space
   physical_frames = malloc(PAGE_SIZE_4KB * numframes);
   if(!physical_frames)
   {
      fprintf(stderr, "Error on mallocing physical frames\n");
      exit(1);
   }
   memset(physical_frames, 0, PAGE_SIZE_4KB * numframes);

   // Create the first frame of the frames linked list
   struct frame_struct *frame = malloc(sizeof(struct frame_struct));
   if(!frame)
   {
      fprintf(stderr, "Error on mallocing frame struct\n");
      exit(1);
   }
   memset(frame, 0, sizeof(struct frame_struct));

   // Store the head of frames linked list
   struct frame_struct *head = frame;

   // Initialize the frames linked list
   for(i = 0; i < numframes; i++)
   {
      frame->frame_number = i;
      frame->physical_address = physical_frames + (i * PAGE_SIZE_4KB) / PAGE_SIZE_BYTES;
      frame->virtual_address = NULL;
      frame->pte_pointer = NULL;
      #ifdef DEBUG
         printf("Frame#%d: Adding a new frame at memory address %ld(0x%08x)\n", i, frame->physical_address, frame->physical_address);
      #endif
      frame->next = malloc(sizeof(struct frame_struct));
      frame = frame->next;
      memset(frame, 0, sizeof(struct frame_struct));

   }
   
   unsigned int fault_address = 0;
   unsigned char mode_type = NULL;
   
   // Main loop for processing memory Accesses

   return(0);
}
