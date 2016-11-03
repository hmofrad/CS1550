# Incomplete skeleton code for Virtual Memory

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

##Files
<p>vmsim.c: Source file for Virtual Memory implementation in c</p>
<p>vmsim.h: Header file for Virtual Memory implementation in c</p>
<p>Makefile: Makefile for building the vmsim binary</p>
