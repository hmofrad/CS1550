# Vitrual memory implementation with a single level 32-Bit page table and FIFO page replacement algorithm

# 1. Files
<ul>vmsim.c: Source file for Virtual Memory implementation</ul>
<ul>vmsim.h: Header file for Virtual Memory implementation</ul>
<ul>Makefile: Makefile for building the vmsim program</ul>

# 2. Compilation and run
<p>1. Connect to thoth.cs.pitt.edu</p>
<ul>ssh PITT_ID@thoth.cs.pitt.edu</ul>
<p>2. Navigate to your dedicated directory:</p>
<ul> cd /u/OSLab/PITT_ID</ul>
<p>3. Clone the cs1550 repo:</p>
<ul> git clone https://github.com/hmofrad/CS1550</ul>
<p>Navigate to project 3 directory:</p>
<ul>cd CS1550/project3</ul>
<p>4. Extract a trace file (simple, gcc, gzip, mcf, and swim traces)</p>
<ul>gunzip traces/gcc.trace.gz</ul>
<p>5. Install</p>
<ul>make (or "make DEBUG=-DDEBUG" to enable debug messages)</ul>
<p>6. Run</p>
<ul>./vmsim -n &lt;numframes&gt; -a &lt;fifo&gt; &lt;tracefile&gt;</ul>
<ul>./vmsim -n 4 -a fifo traces/gcc.trace </ul>
<p>7. Uninstall</p>
<ul>make clean</ul>


<p><b>Note</b>: Please visit Courseweb for a detailed version of project instructions PDF file.</p>