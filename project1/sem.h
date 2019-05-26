/*
 sem.h: CS1550 semaphore helper library 
 (c) Mohammad Hasanzadeh Mofrad, 2019
 (e) moh18@pitt.edu
*/

#ifndef SEM_H_INCLUDED
#define SEM_H_INCLUDED
struct cs1550_sem {
    int value;
    struct cs1550_queue *head;
};

struct cs1550_queue {
    struct cs1550_queue *next;
    struct task_struct *task;
};
#endif
