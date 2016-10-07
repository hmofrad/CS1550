/* 
 * Multiple files development example using strcpy and strcat
 * (C) Mohammad H. Mofrad, 2016
 *   
 */

#include "lib.h"

int main(int argc, char *argv[]) {

    char dest[100];
    char src[] = "Hello World!";

    my_strcpy(dest, src);
    printf ("COPY: %s\n", dest);

    my_strcat(dest, src);
    printf ("CAT : %s\n", dest);

    return 0;
}
