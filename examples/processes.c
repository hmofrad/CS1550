/*
 * CS 1550: Parent & child processes using fork()
 * Compile: gcc -o processes processes.c
 * Execute: ./processes
 * (C) Mohammad H. Mofrad, 2016
 */
#include <stdio.h>
#include <stdlib.h>

void printt(pid_t a)
{
    while(1)
    {
        printf("Hello from process %d - A\n", a);
        printf("Hello from process %d - B\n", a);
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    pid_t p1 = getpid();
    pid_t p2 = 0;
    printf("PID of parent process %d\n", p1);

    if(p1 == getpid())
    {
        p2 = fork();
        if(p2)
        {
             printf("PID of child process %d\n", p2);
        }
    }

    printt(getpid());

    return 0;
}
