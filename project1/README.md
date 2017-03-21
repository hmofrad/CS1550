# Graphics library skeleton code
This skeleton code will clear the screen, draw a single line on top of that, wait for 5 seconds, and then agian clear the screen.

**ALERT** : Compile and run this code only on Qemu VM.

* **library.c** contains the Graphics Library implementation.
* **library.h** includes the function signatures  and macros definitions alongside with global variable declaration.
* **square.c** is the driver program for the project.
* **Makefile** is the Makefile for compiling the project using gcc.


## Prerequisites
After running devtools.sh, execute "tce-load -wi make-locale.tcz" command to install "make"

## Copy to Qemu VM
Login to Qemu VM and then scp:
* scp username@thoth.cs.pitt.edu:WORKING_DIR/\\{library.c,library.h,square.c,Makefile\\} .
* Using \\{...\\} trick, we can copy multiple files from a same directory.

## Install on Qemu VM
make install
## Run on Qemu VM
./square
## Uninstall on Qemu VM
make clean
  
### Report bugs
Report your bugs to moh18@pitt.edu.
