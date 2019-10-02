/* A simple test program for Project 2 locks and condition variables.
 * The output of this program should always be:
 *     This line has to print first
 *     This line has to print second
 *     This line has to print last
 * no matter how long the processes sleep.
 */
#include <sys/mman.h>
#include <linux/unistd.h>
#include <stdio.h>
#include "condvar.h"
#include <stdbool.h>

int main()
{

  //Allocate a shared memory region to store one lock, two condition variables
  // and two booleans
  struct cs1550_lock *lock = mmap(NULL,
      sizeof(struct cs1550_lock)+2*sizeof(struct cs1550_condition)+2*sizeof(bool),
      PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0);
  //pointer arithmetic
  struct cs1550_condition *cond1 = (struct cs1550_condition *)(lock + 1);
  struct cs1550_condition *cond2 = cond1 + 1;
  bool *done1 = (bool *)(cond2 + 1);
  bool *done2 = done1 + 1;

  // Initialize the lock, the condition variables, and the booleans
  cs1550_init_lock(lock);
  cs1550_init_condition(cond1, lock);
  cs1550_init_condition(cond2, lock);

  *done1 = false;
  *done2 = false;

  //Create two child processes
  int pid = fork(); // Create the first child process
  if (pid==0)
  { // I am the first child
    cs1550_acquire(lock);
    while(!(*done1)) cs1550_wait(cond1);
    printf("%d: This line has to print second\n", getpid());
    fflush(stdout);
    *done2 = true;
    cs1550_signal(cond2);
    cs1550_release(lock);
  } else { // I am the parent
    pid = fork(); // Create a second child process
    if(pid == 0) {
      // I am the second child
      cs1550_acquire(lock);
      while(!(*done2)) cs1550_wait(cond2);
      printf("%d: This line has to print last\n", getpid());
      fflush(stdout);
      cs1550_release(lock);
    } else {
      // I am the parent
      /*
       * Now, both child processes maybe waiting on condition variables.
       * Parent process keeps going...
       */
      printf("%d: This line has to print first\n", getpid());
      fflush(stdout);

      //Wake up the first child
      cs1550_acquire(lock);
      *done1 = true;
      cs1550_signal(cond1);
      cs1550_release(lock);

      // Release child 1's and child 2's resources to prevent them from being 'orphan'
      wait(NULL);
      wait(NULL);
    }
  }

  return 0;
}