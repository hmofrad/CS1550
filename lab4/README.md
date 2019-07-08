# Walkthrough for lab 4 (XV6 Lazy Page Allocation)


<p>Download and build XV6 repo on the Linux cluster:</p>
<ul>
  <li>ssh PITT_ID@linux.cs.pitt.edu</li>
  <li>cd private</li>
  <li>mkdir lab4</li>
  <li>cd lab4</li>
  <li>git clone git://github.com/mit-pdos/xv6-public.git</li>
  <li>cd xv6-public</li>
  <li>make qemu-nox</li>
  <li>Use Ctrl + A, and then X to exit</li>
</ul>

<p>What's this lab about? This lab is about lazy page allocation which postpone the allocation of a page until the time a program wants to access that memory. So, we do not allocate memory in advance and wait for a page fault to happen. Later, we intercept the fault address and allocate memory for it. </p>

<p>Interesting methods and macros for this lab: </p>
<ul>
<li><b>sys_sbrk()</b> under sysproc.c</li>
<li><b>allocuvm()</b> under vm.c</li>
<li><b>mappages()</b> under vm.c</li>
<li><b>PGROUNDDOWN</b> under mmu.h</li>
<li><b>trap()</b> under trap.c</li>
<li><b>T_PGFLT</b> under trap.h</li>
</ul>

<p>Files you might want to have a look for this lab:</p>
<ul>
  <li>proc.h: Add memeber <b>int old_sz;</b> inside <b>struct proc</b></li>
  <li>sysproc.c: </li>
  
      int sys_sbrk(void)
      {
          int addr;
          int n;
          if(argint(0, &n) < 0)
              return -1;
          myproc()->old_sz = myproc()->sz;
          addr = myproc()->sz;
          myproc()->sz += n;
          return addr;
      }
      
  <li>trap.c</li>
  
    void trap(struct trapframe *tf) {
        // Some codes are here
        switch(tf->trapno){
        // Some code are here
            default:
                if(myproc() == 0 || (tf->cs&3) == 0){
                // In kernel, it must be our mistake.
                    cprintf("unexpected trap %d from cpu %d eip %x (cr2=0x%x)\n",
                             tf->trapno, cpuid(), tf->eip, rcr2());
                    panic("trap");
                }
                /* Start of partial implementation */
                if(tf->trapno == T_PGFLT) {       
                    pde_t *pgdir = myproc()->pgdir;       
                    uint oldsz = myproc()->old_sz;
                    uint newsz = myproc()->sz;
                    allocuvm(pgdir, oldsz, newsz);
                    return;
                }
                /* End of partial implementation */
                // In user space, assume process misbehaved.
                cprintf("pid %d %s: trap %d err %d on cpu %d "
                        "eip 0x%x addr 0x%x--kill proc\n",
                        myproc()->pid, myproc()->name, tf->trapno,
                        tf->err, cpuid(), tf->eip, rcr2());
                        myproc()->killed = 1;
        }
  
  <p><b>Notes</b>: This is a working partial implementation of the lab which shows how to trap the page fault and handle it. In trap.c, you should put your implementation inside the part marked with a <b>start</b> and <b>end</b>. Also, when you want to use <b>mappages</b> directly, put <b>extern int mappages(pde_t *pgdir, void *va, uint size, uint pa, int perm)</b> (implemented in vm.c) in the beginning of trap.c </p>