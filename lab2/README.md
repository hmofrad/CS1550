# Walkthrough for lab 2 (Process Synchronization in xv6)


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

<p>Follow lab1 walkthrough to add signal and wait system calls.</p>
<p>Files you might want to have a look for this lab:</p>
<ul>
  <li>race.c (copied from the lab instructions)</li>
  <li>usys.S</li>
  <li>syscall.h</li>
  <li>syscall.c</li>
  <li>condvar.h</li>
  <li>ulib.c</li>
  <li>user.h</li>
  <li>proc.c</li>
  <li>defs.h</li>
  <li>sysproc.c</li>
  <li>Makefie</li>
</ul>