/* A simple test program for Project 1 up() and down() syscalls.
 * The output of this program should always be:
 *     This line has to print first
 *     This line has to print second
 *     This line has to print last
 * no matter how long the processes sleep.
 */
#include <sys/mman.h>
#include <linux/unistd.h>
#include <stdio.h>

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
  
  //Initialize the semaphore to 0
  sem->value = 0;

  //Create two child processes
  int pid = fork(); // Create the first child process
  if (pid==0)
  { // I am the first child
    down(sem);
    printf("This line has to print second\n");
  } else { // I am the parent
    pid = fork(); // Create a second child process
    if(pid == 0)
    { // I am the second child
      sleep(1); // Give a chance for the first child to perform down() first
      down(sem);
      printf("This line has to print last\n"); 
    } else
    { // I am the parent
      sleep(3); // Give a chance for the children to run 
      /*
       * Now, both child processes are waiting on sem.
       * The 1st child should be the first entry (head) of queue
       * The 2nd should be the last entry (tail) of queue
       * Parent process keeps going...
       */
      printf("This line has to print first\n");

      up(sem); // Current head of queue (1st child) is waken up 
      sleep(1); // Ensure that the 1st child can finish its printf before the 2nd child is waken up
      up(sem); // Current head of queue (2nd child) is waken up
      
      // Release child 1's and child 2's resources to prevent them from being 'orphan'
      wait(NULL);
      wait(NULL);
    }
  }

  return 0;
}
