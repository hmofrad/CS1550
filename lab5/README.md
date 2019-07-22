# Walkthrough for lab 5 (Bigger files for XV6)


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
  <li>fs.c: static uint bmap(struct inode *ip, uint bn) (inode content) </li>
  <li>fs.h: struct dinode (on-disk inode structure) </li>
  <li>file.h: struct inode definition (in-memory inode structure)</li>
  <li>big.c:Driver program for big files</li>
  <li>Makefile</li>
</ul>