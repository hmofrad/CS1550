/*
 sem.h: CS1550 semaphore helper library 
 (c) Mohammad Hasanzadeh Mofrad, 2019
 (e) moh18@pitt.edu
*/

#ifndef SEM_H_INCLUDED
#define SEM_H_INCLUDED

#include <asm/errno.h>
#include <asm/unistd.h>
// Your implementation goes here ...
struct cs1550_sem {
   int value;
   //Some process queue of your devising
};

void  down(struct cs1550_sem *);
void  up  (struct cs1550_sem *);

/*
void down(struct cs1550_sem *sem) {
  syscall(__NR_cs1550_down, sem);
}

void up(struct cs1550_sem *sem) {
  syscall(__NR_cs1550_up, sem);
}
*/


#endif
