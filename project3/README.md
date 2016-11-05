# Vitrual memory implementation with a single level 32-Bit page table

##Install
make

##Run
<p>./vimsim -n &lt;numframes&gt; -a &lt;fifo&gt; &lt;tracefile&gt; </p>

##Trace files
<p>cd /u/OSLab/PITT_ID</p>
<p>cp /u/OSLab/original/bzip.trace.gz ./ && gunzip bzip.trace.gz</p>
<p>cp /u/OSLab/original/gcc.trace.gz  ./ && gunzip gcc.trace.gz</p>

##Uninstall
make clean

##Log levels
<p>The <b>All</b> log level shows the trace file I/O</p>
<p>The <b>DEBUG</b> log level shows the page walk operations</p>
<p>The <b>INFO</b> log level shows the page fault sequence</p>

##Files
<p>vmsim.c: Source file for Virtual Memory implementation in c</p>
<p>vmsim.h: Header file for Virtual Memory implementation in c</p>
<p>Makefile: Makefile for building the vmsim binary</p>

###Don't forget to report bugs to moh18@pitt.edu.
