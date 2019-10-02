/*
 aptsim.c: Safe apartment inspection problem skeleton code
 (c) Mohammad Hasanzadeh Mofrad, 2019
 (e) moh18@pitt.edu
*/
#include <sys/mman.h>
#include <linux/unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include "sem.h"

//Add your struct cs1550_sem type declaration below
void down(struct cs1550_sem *sem) {
    syscall(__NR_cs1550_down, sem);
}

void up(struct cs1550_sem *sem) {
    syscall(__NR_cs1550_up, sem);
}

// Structure to store command line arguments
struct options {
	int num_tenants;
	int num_agents;
};

/*
Add your function signatures for
    tenantArrives();
    agentArrives();
    tenantLeaves();
    agentLeaves();
    viewApt();
    openApt();
*/

int main(int argc, char** argv) {
    
    if(argc != 5) {
        printf("Usage: %s -m <number of tenants> -k <number of agents>\n", argv[0]);
        return(1);
    }
    // Read arguments
    struct options opt;
    opt.num_tenants = atoi(argv[2]);
    opt.num_agents = atoi(argv[4]);
    
    
    //Allocate a shared memory region to store one semaphore
    struct cs1550_sem *sem = mmap(NULL, sizeof(struct cs1550_sem), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0);
    memset(sem, sizeof(struct cs1550_sem), 0);
    //Initialize the semaphore to 0
    sem->value = 0;
    int i = 0;
    
    // Allocate an array for storing tenant and agent ids
    pid_t *pids = (void *) mmap(NULL, sizeof(pid_t) * 2, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0);
    memset(pids, sizeof(pid_t) * 2, 0);
    
    //Create two tenant and agent processes
    int pid = fork(); // Create the first child process
    if (pid == 0) { 
        down(sem);
        printf("Parent tenant: I am the first child process with pid=%d.\n", getpid());
        pids[0] = getpid();
        
        // Launch tenant processes
        for(i = 0; i < opt.num_tenants; i++) {
            if(pids[0] == getpid()) {
                pid = fork();
                if(pid == 0) {
                    printf("Child tenant: I am a grandchild process with pid=%d.\n", getpid());
                }
            }
        }
        
        if(pids[0] == getpid()) {
            for(i = 0; i < opt.num_tenants; i++) {
                wait(NULL);
            }
        }
    }
    else {
        pid = fork(); // Create a second child process
        if(pid == 0) {
            sleep(5);
            down(sem);
            printf("Parent agent: I am the second child process with pid=%d.\n", getpid());
            pids[1] = getpid();
            
            // Launch agent processes
            for(i = 0; i < opt.num_agents; i++) {
                if(pids[1] == getpid()) {
                    pid = fork();                
                    if(pid == 0) {
                        printf("Child agent: I am a grandchild process with pid=%d.\n", getpid());
                    }
                }
            }
                        
            if(pids[1] == getpid()) {                
                for(i = 0; i < opt.num_agents; i++) {
                    wait(NULL);
                }
            }
        } 
        else
        {
            sleep(5);
            up(sem);
            sleep(1);
            up(sem);
            
            printf("I am the parent of 2 children and grandparent of %d grandchildren with pid=%d.\n", (opt.num_tenants + opt.num_agents), getpid());
            printf("Now,  My tenant child process pid is %d and my agent child process pid is %d\n", pids[0], pids[1]);
            wait(NULL);
            wait(NULL);
            printf("Then, My tenant child process pid is %d and my agent child process pid is %d\n", pids[0], pids[1]);
        }
    }

  return 0;
}
