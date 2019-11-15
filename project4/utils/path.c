/*
 * path.c: Extracting tokens from a path
 * Compile: gcc -o path -Wall -Werror path.c
 * Run: ./path /dir/test.txt
 * (c) Mohammad Hasanzadeh Mofrad, 2019
 * (e) m.hasanzadeh.mofrad@gmail.com 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME 8
#define MAX_EXTENSION 3

int main(int argc, char** argv) {
    
    if(argc != 2) {
        fprintf(stderr, "USAGE: %s /DIR/FILE.TXT\n",argv[0]);
        exit(1);
    }
    
    char *path = argv[1];
    
    printf("path = %s\n", path);
    char directory[MAX_FILENAME + 1];
    memset(directory, 0, MAX_FILENAME + 1);
    char filename[MAX_FILENAME + 1];
    memset(filename, 0, MAX_FILENAME + 1);
    char extension[MAX_EXTENSION + 1];
    memset(extension, 0, MAX_EXTENSION + 1);
    int n = sscanf(path, "/%[^/]/%[^.].%s", directory, filename, extension);

    if(n == 0) {
        printf("NoOp\n");
    }
    else if(n == 1) {
        printf("directory = %s\n", directory);
    }
    else if(n == 2) {
        printf("directory = %s\n"
               "filename  = %s\n", directory, filename);
    }
    else if(n == 3) {
        printf("directory = %s\n"
               "filename  = %s\n"
               "extension = %s\n", directory, filename, extension);
    }
    
    return(0);
}