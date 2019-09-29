/*
 rabd.c: Program for generating random number and checking against a probability
 (c) Mohammad Hasanzadeh Mofrad, 2019
 (e) moh18@pitt.edu
 Compile: gcc -o rand rand.c
 Run: ./rand 20 # Generate a random number and check it against 20% probability
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int rand_gen(int min, int max) {
    return((rand() % (max + 1 - min)) + min);
}

int main(int argc, char** argv) {
    
    if(argc != 2) {
        fprintf(stderr, "USAGE: %s <probability (of 100)>\n", argv[0]);
        exit(0);
    }
    
    int probability = atoi(argv[1]);
    time_t seeder = 10;
    srand(time(&seeder));
    int random_number = rand_gen(0, 100);
    printf("probability = %d (of 100), random_number = %d\n", probability, random_number);
    if(random_number < probability) {
        printf("Do something immediatly (random_number < probability)\n");
    }
    else {
        printf("Go to sleep for certain amount of time (random_number > probability)\n");
    }
    
    return(0);
}
