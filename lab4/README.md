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

<p>Files you might want to have a look for this lab:</p>
<ul>
  <li>proc.h: Add memeber **int old_sz;** inside **struct proc**</li>
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
      
  <li></li>
  <li></li>
  <li></li>
  <li></li>
</ul>
