# Graphics Library skeleton code
This skeleton code will clear the screen, draw a single line on top of that, wait for 5 seconds, and then agian clear the screen.
<p><b>ALERT</b>: Compile and run this code only on Qemu VM.</p>
  <ul>
  <li><b>library.c</b> contains the Graphics Library implementation.</li>
  <li><b>library.h</b> includes the function signatures  and macros definitions alongside with global variable declaration</li>
  <li><b>square.c</b> is the driver program for the project.</li>
  <li><b>Makefile</b> is the Makefile for compiling the project using gcc</li>
</ul>

## Copy to Qemu VM
  Login to Qemu VM and then run scp:
  <p>scp PITT_ID@thoth.cs.pitt.edu:WORKING_DIR/\\{library.c,library.h,square.c,Makefile\\} .</p>
  <p>Using \\{...\\} trick, we can copy multiple files from a same directory.</p>

## Install on Qemu VM
  make install
## Run on Qemu VM
  ./square
## Uninstall on Qemu VM
  make clean
  
###Don't forget to report bugs to moh18@pitt.edu.
