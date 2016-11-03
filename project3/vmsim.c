/*
 * CS 1550: Source file for Virtual Memory skeleton code
 * (c) Mohammad H. Mofrad, 2016
 * (e) hasanzadeh@cs.pitt.edu
 */
 
#include "vmsim.h"

int numframes;

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

   printf("%d\n", numframes);

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
