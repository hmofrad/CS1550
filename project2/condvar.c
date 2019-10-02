#include "condvar.h"
#include "unistd.h"
#include <stdio.h>

void down(struct cs1550_sem *sem) {
  syscall(__NR_cs1550_down, sem);
}

void up(struct cs1550_sem *sem) {
  syscall(__NR_cs1550_up, sem);
}

void cs1550_init_lock(struct cs1550_lock *l) {
  l->nextCount = 0;
  l->mutex.value = 1;
  l->next.value = 0;
}

void cs1550_acquire(struct cs1550_lock *l){
  down(&(l->mutex));
  // printf("%d: acquiring lock\n", getpid());
}

void cs1550_release(struct cs1550_lock *l) {
  if (l->nextCount > 0)
    up(&(l->next));
  else
    up(&(l->mutex));
  // printf("%d: releasing lock\n", getpid());
}

void cs1550_init_condition(struct cs1550_condition *cond, struct cs1550_lock *l){
  cond->semCount = 0;
  cond->condSem.value = 0;
  cond->l = l;
}

void cs1550_wait(struct cs1550_condition *cond){
  cond->semCount += 1;
  if (cond->l->nextCount > 0)
    up(&(cond->l->next));
  else
    up(&(cond->l->mutex));
  down(&(cond->condSem));
  // printf("%d: waking up\n", getpid());
  cond->semCount -= 1;
}

void cs1550_signal(struct cs1550_condition *cond){
  if (cond->semCount > 0) {
    cond->l->nextCount += 1;
    up(&(cond->condSem));
    down(&(cond->l->next));
    cond->l->nextCount -= 1;
    // printf("%d: resuming\n", getpid());
  }
}

void cs1550_broadcast(struct cs1550_condition *cond){
  while (cond->semCount > 0) {
    cond->l->nextCount += 1;
    up(&(cond->condSem));
    down(&(cond->l->next));
    cond->l->nextCount -= 1;
  }
}