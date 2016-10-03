#!/bin/bash
# Fast build script for Linux kernel
# login to thoth:
#     ssh PITT_ID@thoth.cs.pitt.edu
# Navigate to your working directory:
#      cd /u/OSLab/PITT_ID/WORK_DIR
# Give execute permission to the script:
#      chmod +x build.sh 
# Run the script:
#      ./build.sh
# (C) Mohammad H. Mofrad, 2016

BASE=$PWD # Current working directory 
KERNEL_SRC="linux-2.6.23.1.tar.bz2"; # Kernel source file
KERNEL_DIR="linux-2.6.23.1" # Kernel source directory

# Check if you are at /u/OSLab/PITT_ID
# If yes, continue
# If not,  exit
if [[ "$BASE" =~ ^/u/OSLab/[a-zA-Z]{3}[0-9]{1,2,3}/.*$ ]];
then
     echo "$BASE OK.";
     if [[ "$BASE" =~ (/u/OSLab/)([a-zA-Z]{3}[0-9]{2,3}) ]];
     then 
          PITT_ID=${BASH_REMATCH[2]}
          echo "Your PITT_ID $PITT_ID";
     fi
else
     echo "Must change $BASE to /u/OSLab/";
     exit;
fi;

# Check if you have the kernel directory in your working directory
# If not, extract kernel directory
# If yes, do nothing
if [ -f "$KERNEL_SRC" ];
then
     echo "$KERNEL_SRC found.";
else
     echo "$KERNEL_SRC not found.";
     cp /u/OSLab/original/$KERNEL_SRC .;
     tar xjvf $KERNEL_SRC;
fi

# prodcons library
cp ./src/prodcons.h      $KERNEL_DIR/include/linux/prodcons.h;
# The file that should contain sys_cs1550_up and sys_cs1550_down implementation
cp ./src/sys.c           $KERNEL_DIR/kernel/sys.c;             
# The file that should contain: sys_cs1550_up and sys_cs1550_down signatures 
#                            && #include <linux/prodcons.h>
#                            && struct cs1550_sem;
cp ./src/syscalls.h      $KERNEL_DIR/include/linux/syscalls.h;
# You should put syscall names along with syscall number here
cp ./src/syscall_table.S $KERNEL_DIR/arch/i386/kernel/syscall_table.S
# Define your syscall names and number here
cp ./src/unistd.h        $KERNEL_DIR/include/asm/unistd.h

# If exists, clear previous build
FILES="System.map bzImage $KERNEL_DIR/System.map $KERNEL_DIR/arch/i386/boot/bzImage"
echo "${P}"
for FILE in ${FILES};
do
if [ -a "$FILE" ];
then
     echo $FILE
     rm -rf $FILE;
fi
done

# Compile kernel
cd $KERNEL_DIR;
make ARCH=i386 bzImage; 
cd ..; 

if [ -a "$KERNEL_DIR/System.map" ] && [ -a "$KERNEL_DIR/arch/i386/boot/bzImage" ];
then
     # Copy kernel image to your working directory
     cp $KERNEL_DIR/arch/i386/boot/bzImage .; 
     # Copy kernel symbole table
     cp $KERNEL_DIR/System.map .;

     # Compile prodcons program statistically using kernel source directory
     gcc -m32 -o prodcons -I $KERNEL_DIR/include/ ./src/prodcons.c;
else
     echo "Error: Kernel compilation error"
fi

exit;
