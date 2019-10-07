# Walkthrough for lab 3 (Priority Scheduling XV6)


<p>Download and build XV6 repo on the Linux cluster:</p>
<ul>
  <li>ssh PITT_ID@linux.cs.pitt.edu</li>
  <li>cd private</li>
  <li>mkdir lab3</li>
  <li>cd lab3</li>
  <li>git clone git://github.com/mit-pdos/xv6-public.git</li>
  <li>cd xv6-public</li>
  <li>make qemu-nox</li>
  <li>Use Ctrl + A, and then X to exit</li>
</ul>

<p>Files you need to change to implement the priority scheduling algorithm:</p>
<ul>
  <li>proc.h: Add priority filed under struct proc</li>
  <li>proc.c - allocproc(): Initialize the priority filed to 50</li>
  <li>proc.c - scheduler(): Add the priority queue scheduling algorithm</li>
</ul>
    
<p>XV6 priority scheduler pseudocode (with O(p^2) time complexity)</p>

    Scheduler() {
        struct proc* highest_priority_proc_idx;
        struct proc* p1;
        for(;;){
            highest_priority_proc_idx = 0;
            for(p_i in NPROC processes) {
                if(p_i state is RUNNABLE) {
                    highest_priority_proc_idx = p_i;
                    for(p_j in NPROC processes) {
                        if(p_j state is RUNNABLE) {
                            if(highest_priority_proc_idx->priority > p_j->priority) {
                                highest_priority_proc_idx = p_j;
                            }
                        }
                    }
                    schedule highest_priority_proc_idx
                }
            }
        }
    }

<p>XV6 priority scheduler pseudocode (with O(p) time complexity)</p>    

    Scheduler() {
        j = 0;
        declare priority_queue[NPROC];
        declare processes_to_be_picked;
        for(;;){
            j = 0;
            clear priority_queue;
            clear processes_to_be_picked;
            for(p_i in NPROC processes) {
                if(p_i state is RUNNABLE) {
                    if(processes_to_be_picked is empty) {
                        process_to_be_picked = p_i;
                        j = 0;
                        priority_queue[j] = i;
                        j++;
                    } 
                    else{
                        if(p_i priority is equal to process_to_be_picked priority) {
                            priority_queue[j] = i;
                            j++;
                        }
                        else if(p_i priority is less than process_to_be_picked priority){
                            process_to_be_picked = p_i;
                            for(k in priority_queue) {
                                priority_queue[k] = 0;
                            }
                            j = 0;
                            priority_queue[j] = i;
                            j++;
                        }
                    }
                }
            }
            for(k in priority_queue)
                schedule the highest priority task p_k
        }
    }



<p>Files you need to change to add the SYS_setpriority() syscall</p>
<ul>
  <li>syscall.h: Add syscall definition "#define SYS_setpriority 22"</li>
  <li>user.h: Add user-space syscall interface "int setpriority(int);"</li>
  <li>usys.S: Add "SYSCALL(setpriority)"</li>
  <li>syscall.c: Syscall declaration using "extern int sys_setpriority(void);"</li>
  <li>syscall.c: Update syscall table using "[SYS_setpriority] sys_setpriority,"</li>
  <li>sysproc.c: Add syscall implementation "int sys_setpriority(void){return 0; \\ Your code for syscall goes here }"</li>
  <li>(Optional) priority.c: Driver program to test the setpriority() syscall. Make sure to add _priority\ under UPROGS in the Makefile.</li>
</ul>    
    
<p><b>Note</b>: Please visit Courseweb for a detailed version of lab instructions PDF file.</p>    
