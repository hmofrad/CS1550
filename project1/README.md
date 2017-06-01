# Graphics library code skeleton
This code skeleton clears the screen, draws a single line, waits for 5 seconds, and then agian clears the screen.

**ALERT** : Compile and run this code only on Qemu VM.

* **library.c** contains the Graphics Library implementation.
* **library.h** includes the function signatures  and macros definitions alongside global variable declaration.
* **driver.c** is the driver program for the project.
* **Makefile** is the Makefile for compiling the project using gcc.


## Prerequisites
After running devtools.sh, execute "tce-load -wi make-locale.tcz" command to install "make"

## Copy to Qemu VM
Login to Qemu VM and then scp:
* scp username@thoth.cs.pitt.edu:YOUR_WORKING_DIR_ON_THOTH/\\{library.c,library.h,square.c,Makefile\\} .
* Using scp's \\{...\\} trick, we can copy multiple files from a same directory.

## Install on Qemu VM
make install
## Run on Qemu VM
./driver
## Uninstall on Qemu VM
make clean
  
### Report bugs
Report your bugs to mohammad.hmofrad@pitt.edu.
