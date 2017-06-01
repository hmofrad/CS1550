/* 
 * Graphics Library driver file
 * (c) Mohammad H. Mofrad, 2017
 * (e) mohammad.hmofrad@pitt.edu
 */
 
#include "library.h"

int main(int argc, char** argv)
{
   int i;

   init_graphics();
   clear_screen();
   for(i = 0; i < 640; i++)
       draw_pixel(i, 100, 255);
   sleep_s(5);
   
   clear_screen();
   exit_graphics();

   return (0);
}
