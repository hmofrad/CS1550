# Walkthrough for lab 1 (Adding getcount syscall to xv6)
<p>Install Qemu VM on Ubuntu, and download and build XV6 repo:</p>
<ul>
  <li>sudo apt-get update</li>
  <li>sudo apt-get install qemu-kvm qemu virt-manager virt-viewer libvirt-bin</li>
  <li>mkdir lab2</li>
  <li>cd lab2</li>
  <li>git clone git://github.com/mit-pdos/xv6-public.git</li>
  <li>cd xv6-public</li>
  <li>make qemu-nox</li>
  <li>Use Ctrl + A, and then X to exit</li>
</ul>

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
