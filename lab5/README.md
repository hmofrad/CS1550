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

<p>This lab is about adding a doubly-indirect block. After implementing this lab, new inode diagram will look like this:</p>

<!--![XV6 new inode Diagram](https://github.com/hmofrad/CS1550/blob/master/lab5/inodeDiagram.jpg) -->



<p>Files you might want to have a look for this lab:</p>
<ul>
  <li>fs.c: <b>static uint bmap(struct inode *ip, uint bn)</b> (inode content) </li>
  <li>fs.h: <b>struct dinode</b> (on-disk inode structure) </li>
  <li>file.h: <b>struct inode</b> definition (in-memory inode structure)</li>
  <li>big.c: Driver program for big files</li>
  <li>Makefile</li>
</ul>

<p><b>Note</b>: Please visit Courseweb for a detailed version of lab instructions PDF file.</p>    
