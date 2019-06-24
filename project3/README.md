# Vitrual memory implementation with a single level 32-Bit page table and FIFO page replacement algorithm


<p>Connect to thoth.cs.pitt.edu</p>
<ul>ssh PITT_ID@thoth.cs.pitt.edu</ul>
<p>Navigate to project3 directory</p>
<ul>cd /u/OSLab/PITT_ID/CS1550/project3</ul>
<p>Copy a trace file (gzip, gcc, and swim traces)</p>
<ul>cp /u/OSLab/original/gzip.trace.gz . && gunzip bzip.trace.gz</ul>

<p>Install</p>
<ul>make (or "make DEBUG=-DDEBUG" to enable debug messages)</ul>

<p>Run</p>
<ul>./vimsim -n &lt;numframes&gt; -a &lt;fifo&gt; &lt;tracefile&gt;</ul>
<ul>./vimsim -n 4 fifo gzip </ul>

<p>Uninstall</p>
<ul>make clean</ul>

<p>Files</p>
<ul>vmsim.c: Source file for Virtual Memory implementation</ul>
<ul>vmsim.h: Header file for Virtual Memory implementation</ul>
<ul>Makefile: Makefile for building the vmsim program</ul>
