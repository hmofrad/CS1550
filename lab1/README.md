# Walkthrough for lab 1 (Adding getcount syscall to xv6)
<p>Install Qemu VM on Ubuntu, and download and build XV6 repo:</p>
<ul>
  <li>ssh PITT_ID@linux.cs.pitt.edu</li>
  <li>cd private/</li>
  <li>mkdir lab1</li>
  <li>cd lab1/</li>
  <li>git clone git://github.com/mit-pdos/xv6-public.git</li>
  <li>cd xv6-public</li>
  <li>make qemu-nox</li>
  <li>Use Ctrl + A, and then X to exit</li>
</ul>

<p>Files you might want to have a look for adding the getcount syscall:</p>
<ul>
  <li>syscall.h: #define your syscall here.</li>
  <li>syscall.c: Add syscall signature, update the syscall table, and edit syscall() function</li>
  <li>user.h: Add your syscall signature.</li>
  <li>usys.S: Define your syscall signature.</li>
  <li>proc.h: Edit struct proc.</li>
  <li>proc.c: Edit allocproc() function.</li>
  <li>sysproc.c: Add your syscall implementation here.</li>
  <li>Makefie: Edit UPROGS.</li>
</ul>

<p><b>Note</b>: Please visit Courseweb for a detailed version of lab instructions PDF file.</p>
