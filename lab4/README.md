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

<p><b>Note</b>: Please visit Courseweb for a detailed version of lab instructions PDF file.</p>    