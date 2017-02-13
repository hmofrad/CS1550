/* 
 * Skeleton code for prodcons problem
 * (C) Mohammad H. Mofrad, 2017
 *   
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <linux/prodcons.h>

void *BASE_PTR;

void main(int aegc, char *argv[])
{

     BASE_PTR = (void *) mmap(NULL, MAP_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0);
     if(BASE_PTR == (void *) -1) 
     {
          fprintf(stderr, "Error mapping memory\n");
          exit(1);
     }
     
     int *base_ptr = BASE_PTR;
     int *new_ptr;
     int *curr_ptr = BASE_PTR;
     int size = sizeof(struct cs1550_sem);
     curr_ptr = curr_ptr + size;
     if(curr_ptr > base_ptr + MAP_SIZE) 
     {
          fprintf(stderr, "Address out of range\n");
          exit(1);
     }
     else
     {
          new_ptr = curr_ptr - size;
     }
     
     struct cs1550_sem *sem = (struct cs1550_sem *) new_ptr;
     sem->value = 0;
     
     printf("Base pointer (0x%08x), Current pointer (0x%08x), New pointer (0x%08x)\n", base_ptr, curr_ptr, new_ptr);
     printf("Base pointer (%d), Current pointer (%d), New pointer (%d)\n", *base_ptr, *curr_ptr, *new_ptr);
     cs1550_down(sem);
     sleep(5);
     printf("Semaphore value (%d)\n", sem->value);
     printf("Base pointer (%d), Current pointer (%d), New pointer (%d)\n", *base_ptr, *curr_ptr, *new_ptr);
     cs1550_up(sem);
     printf("Semaphore value (%d)\n", sem->value);
     printf("Base pointer (%d), Current pointer (%d), New pointer (%d)\n", *base_ptr, *curr_ptr, *new_ptr);

}

void cs1550_down(struct cs1550_sem *sem) 
{
     syscall(__NR_sys_cs1550_down, sem);
}

void cs1550_up(struct cs1550_sem *sem) 
{
     syscall(__NR_sys_cs1550_up, sem);
}
