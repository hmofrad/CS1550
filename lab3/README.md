# Walkthrough for lab 3 (PRIORITY SCHEDULING FOR XV61 in xv6)


<p>Download and build XV6 repo on the Linux cluster:</p>
<ul>
  <li>ssh PITT_ID@linux.cs.pitt.edu</li>
  <li>cd private</li>
  <li>mkdir lab2</li>
  <li>cd lab2</li>
  <li>git clone git://github.com/mit-pdos/xv6-public.git</li>
  <li>cd xv6-public</li>
  <li>make qemu-nox</li>
  <li>Use Ctrl + A, and then X to exit</li>
</ul>

<p>Files you might want to have a look for this lab:</p>
<ul>
  <li>proc.c and proc.h for adding the priority queue scheduling algorithm</li>
  <li>user.h, usys.S, syscall.c, sysproc.c for adding the sys_setpriority() syscall</li>
  <li>trap.c, proc.c, proc.h for implementing the bonus part</li>
</ul>

<p>XV6 priority queue pseudocode</p>

    Scheduler() {
        for(;;){
            j=0;
            priority_queue[NPROC];
            processes_to_be_picked ;
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
                            for(k in priority_queue)
                                priority_queue[k] = 0;
                                j = 0;
                                priority_queue[j] = i;
                                j++;
                            }
                        }
                    }
                }
            }
        }
    }