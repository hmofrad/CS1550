# Graphics Library skeleton code
## Copy to Qemu VM
Login to Qemu VM and then run scp:
scp PITT_ID@thoth.cs.pitt.edu:WORKING_DIR/\{library.c,library.h,square.c,Makefile} .

## Install on Qemu VM
  make install
## Run on Qemu VM
  ./square # It will clear the screen, draw a line on top of that, waits for 5', and clean the screen agin.
## Uninstall on Qemu VM
  make clean
