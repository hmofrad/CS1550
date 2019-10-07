// priority.c 
#include "types.h"
#include "user.h"
#include "syscall.h"
int main(int argc, char *argv[])
{
    printf(1, "New priority is %d\n", setpriority(0));
    exit();
}