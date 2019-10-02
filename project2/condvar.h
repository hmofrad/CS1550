#ifndef _CONDVAR_H_
#define _CONDVAR_H_

#include "sem.h"

struct cs1550_lock {
  struct cs1550_sem mutex;
  struct cs1550_sem next;
  int nextCount;
};

struct cs1550_condition {
  struct cs1550_lock *l;
  struct cs1550_sem condSem;
  int semCount;
};

void cs1550_init_lock(struct cs1550_lock *l);
void cs1550_acquire(struct cs1550_lock *l);
void cs1550_release(struct cs1550_lock *l);
void cs1550_init_condition(struct cs1550_condition *cond, struct cs1550_lock *l);
void cs1550_wait(struct cs1550_condition *cond);
void cs1550_signal(struct cs1550_condition *cond);
void cs1550_broadcast(struct cs1550_condition *cond);

#endif
