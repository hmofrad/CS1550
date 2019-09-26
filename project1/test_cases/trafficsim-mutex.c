/* A simple test program for Project 1 up() and down() syscalls.
 * The output of this program should always be that entering and
 *  exiting the Critical Section is never preempted.
 */
#include <sys/mman.h>
#include <linux/unistd.h>
#include <stdio.h>
#include <math.h> // Need to add -lm flag: "gcc -m32 -lm -o trafficsim ..."
#include "sem.h"

#define LOOPS1 1 // workload for each process
#define LOOPS2 1 // number of iterations


//Add your struct cs1550_sem type declaration below

void down(struct cs1550_sem *sem) {
  syscall(__NR_cs1550_down, sem);
}

void up(struct cs1550_sem *sem) {
  syscall(__NR_cs1550_up, sem);
}



int main()
{
  //Allocate a shared memory region to store one semaphore
  struct cs1550_sem *sem = mmap(NULL,sizeof(struct cs1550_sem),
      PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0);

  //Initialize the semaphore to 1
  sem->value = 1;
  int i, j;
  float m=1.0;

  //Create two child processes
  int pid = fork(); // Create the first child process
  if (pid==0)  { // I am the first child
    for (i=0; i < LOOPS2; i++) {
      down(sem);
      fprintf(stderr, "Child 1 process entering critical section, iteration %i.\n", i);
      fflush(stderr);
      for (j=0; j < LOOPS1; j++) {
        m = m*log(j*i*149384);
        m = exp(m);
      }
      fprintf(stderr, "Child 1 process exiting CS, iteration %i. j=%i\n", i, j);
      fflush(stderr);
      up(sem);
    }
  } else { // I am the parent
    pid = fork(); // Create a second child process
    if(pid == 0) { // I am the second child
      for (i=0; i < LOOPS2; i++) {
        down(sem);
        fprintf(stderr, "Child 2 process entering critical section, iteration %i.\n", i);
        fflush(stderr);
        for (j=0; j < LOOPS1; j++) {
          m = m*log(j*i*149384);
          m = exp(m);
        }
        fprintf(stderr, "Child 2 process exiting CS, iteration %i. j=%i\n", i, j);
        fflush(stderr);
        up(sem);
      }
    } else { // I am the parent
      for (i=0; i < LOOPS2; i++) {
        down(sem);
        fprintf(stderr, "parent process entering critical section, iteration %i.\n", i);
        fflush(stderr);
        for (j=0; j < LOOPS1; j++) {
          m = m*log(j*i*149384);
          m = exp(m);
        }
        fprintf(stderr, "parent process exiting CS, iteration %i. j=%i\n", i, j);
        fflush(stderr);
        up(sem);
      }
      // Release child 1's and child 2's resources to prevent them from being 'orphan'
      wait(NULL);
      wait(NULL);
    }
  }
  return 0;
}
