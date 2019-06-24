# Vitrual memory implementation with a single level 32-Bit page table and FIFO page replacement algorithm

<p>Install</p>
<ul>make (or make DEBUG=-DDEBUG #To enable debug messages)</ul>

<p>Run</p>
<ul>./vimsim -n &lt;numframes&gt; -a &lt;fifo&gt; &lt;tracefile&gt; </ul>

<p>Trace files</p>
<ul>cd /u/OSLab/PITT_ID</ul>
<ul>cp /u/OSLab/original/gzip.trace.gz . && gunzip bzip.trace.gz</ul>
<ul>cp /u/OSLab/original/swim.trace.gz . && gunzip swim.trace.gz</ul>
<ul>cp /u/OSLab/original/gcc.trace.gz  . && gunzip gcc.trace.gz</ul>

<p>Uninstall</p>
<ul>make clean</ul>


<p>Files</p>
<ul>vmsim.c: Source file for Virtual Memory implementation</ul>
<ul>vmsim.h: Header file for Virtual Memory implementation</ul>
<ul>Makefile: Makefile for building the vmsim program</ul>
