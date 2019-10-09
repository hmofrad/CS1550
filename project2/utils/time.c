/*
 time.c: Program for going to sleep for certain number of seconds
 (c) Mohammad Hasanzadeh Mofrad, 2019
 (e) moh18@pitt.edu
 Compile: gcc -o time time.c
 Run: ./time 3 # Sleep for 3 seconds
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc, char** argv) {
    
    if(argc != 2) {
        fprintf(stderr, "USAGE: %s <sleep_time>\n", argv[0]);
        exit(0);
    }
    
    int sleep_time = atoi(argv[1]);
    printf("The program is going to sleep for %d secodns ...\n", sleep_time);
    struct timeval t0, t1;
    gettimeofday(&t0, 0);
    sleep(sleep_time);
    gettimeofday(&t1, 0);
    long int elapsed = (t1.tv_sec-t0.tv_sec);
    printf("The program sleeped for %ld seconds!!!\n", elapsed);
    
    return(0);
}
