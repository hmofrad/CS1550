# Vitrual memory implementation with a single level 32-Bit page table and FIFO page replacement algorithm

## Install
make

## Run

./vimsim -n &lt;numframes&gt; -a &lt;fifo&gt; &lt;tracefile&gt;

## Trace files
* cd /u/OSLab/PITT_ID
* cp /u/OSLab/original/bzip.trace.gz ./ && gunzip bzip.trace.gz
* cp /u/OSLab/original/gcc.trace.gz  ./ && gunzip gcc.trace.gz

## Uninstall

make clean

## Log levels
* The <b>All</b> log level shows the trace file I/O
* The <b>DEBUG</b> log level shows the page walk operations
* The <b>INFO</b> log level shows the page fault sequence

## Files
* vmsim.c: Source file for Virtual Memory implementation in c
* vmsim.h: Header file for Virtual Memory implementation in c
* Makefile: Makefile for building the vmsim binary

## Report bugs
* Report your bugs to moh18@pitt.edu.
