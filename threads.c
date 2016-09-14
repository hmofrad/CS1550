/*
 * CS 1550: Threading using pthread_create() & pthread_join()
 * Compile: gcc -o threads threads.c -pthread
 * Run: ./threads
 * (C) Mohammad H. Mofrad, 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *printt(void *a)
{
    while(1)
    {
        printf("Hello from thread %d - A\n", *(int *)a);
        printf("Hello from thread %d - B\n", *(int *)a);
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    int i1;
    int a1 = 1;
    pthread_t t1;
    int i2;
    int a2 = 2;
    pthread_t t2;

    i1 = pthread_create(&t1, NULL, printt, (void *)&a1);
    i2 = pthread_create(&t2, NULL, printt, (void *)&a2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);



    return 0;
}
