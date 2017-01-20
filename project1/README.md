# Graphics Library skeleton code
This skeleton code will clear the screen, draw a single line on top of that, waits for 5 seconds, and then agian clear the screen. Compile the code on Qemu VM.
<ol>
<li>library.c contains the Graphics Library implementation.</li>
<li>library.h includes the function signatures  and macros definitions alongside with global variable declaration</li>
<li>square.c is the driver program for the project.</li>
<li>Makefile is the Makefile for compiling the project using gcc</li>
</ol>

## Copy to Qemu VM
  Login to Qemu VM and then run scp:
  <p>scp PITT_ID@thoth.cs.pitt.edu:WORKING_DIR/\\{library.c,library.h,square.c,Makefile\\} .</p>
  <p>\\{...\\} will copy multiple files from a same directory.</p>

## Install on Qemu VM
  make install
## Run on Qemu VM
  ./square
## Uninstall on Qemu VM
  make clean
  
###Don't forget to report bugs to moh18@pitt.edu.
