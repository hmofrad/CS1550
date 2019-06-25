# Vitrual memory implementation with a single level 32-Bit page table and FIFO page replacement algorithm

<p>1. Connect to thoth.cs.pitt.edu</p>
<ul>ssh PITT_ID@thoth.cs.pitt.edu</ul>
<p>2. Navigate to project3 directory</p>
<ul>cd /u/OSLab/PITT_ID/CS1550/project3</ul>
<p>3. Extract a trace file (gcc, gzip, mcf, and swim traces)</p>
<ul>gunzip traces/gcc.trace.gz</ul>

<p>4. Install</p>
<ul>make (or "make DEBUG=-DDEBUG" to enable debug messages)</ul>

<p>5. Run</p>
<ul>./vimsim -n &lt;numframes&gt; -a &lt;fifo&gt; &lt;tracefile&gt;</ul>
<ul>./vimsim -n 4 fifo gzip </ul>

<p>6. Uninstall</p>
<ul>make clean</ul>

<p>7. Files info</p>
<ul>vmsim.c: Source file for Virtual Memory implementation</ul>
<ul>vmsim.h: Header file for Virtual Memory implementation</ul>
<ul>Makefile: Makefile for building the vmsim program</ul>
