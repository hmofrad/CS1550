/* 
 * Graphics Library driver file
 * (c) Mohammad H. Mofrad, 2017
 */
 
#include "library.h"

int main(int argc, char** argv)
{
   int i;

   init_graphics();
   clear_screen();

   draw_line(0xFFFF);
   sleep_s(5);
   
   clear_screen();
   exit_graphics();

   return (0);
}
