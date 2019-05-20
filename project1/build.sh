#!/bin/bash
# build.sh: Build script for Linux kernel
# (c) Mohammad Hasanzadeh Mofrad, 2019
# (e) moh18@pitt.edu
# Run: First give execute permission to the script by
#      chmod +x build.sh 
#      Then run the script by
#      ./build.sh

BASE=$PWD # Current working directory 
KERNEL_SRC="linux-2.6.23.1.tar.bz2"; # Kernel source file
KERNEL_DIR="linux-2.6.23.1" # Kernel source directory


if [ -z $1 ]; then
    PITT_ID="PITT_ID"
    echo "WARN: PITT_ID is not set!"; 
else
    PITT_ID=$1
    echo "INFO: Your PITT_ID is $PITT_ID";
fi

if [[ "$BASE" =~ ^/u/OSLab/.*$ ]];
then
     echo "INFO: $BASE is oaky.";
else
     echo "WARN: For proper use, navigate to /u/OSLab/$PITT_ID and then clone the repo.";
fi;

# Check if you have the kernel directory in your working directory
# If not, extract kernel directory
# If yes, do nothing
if [ -f "$KERNEL_SRC" ]; then
    echo "INFO: $KERNEL_SRC found."
else
    echo "INFO: $KERNEL_SRC not found."
    if [ -f "/u/OSLab/original/$KERNEL_SRC" ]; then
        cp /u/OSLab/original/$KERNEL_SRC .
    else
        wget http://cs.pitt.edu/~moh18/files/pages/$KERNEL_SRC
    fi;
fi
  
if [ ! -d "$KERNEL_DIR" ]; then
    echo "INFO: Extracting $KERNEL_SRC ..." 
    tar xjf $KERNEL_SRC
fi

echo "INFO: Coppying sys.c, syscall_table.S, unistd.h,  ..." 
# Project 1 (Please upload sys.c, syscall_table.S, unitstd.h, and sem.h)

# This file is the kernel config file
cp config $KERNEL_DIR/.config
# This file contains sys_cs1550_up and sys_cs1550_down implementations
cp sys.c           $KERNEL_DIR/kernel/sys.c;             
# This file contains sys_cs1550_up and sys_cs1550_down signatures 
#                            && #include <linux/prodcons.h>
#                            && struct cs1550_sem;
#cp syscalls.h      $KERNEL_DIR/include/linux/syscalls.h;
# You should put syscall names along with syscall number here
cp syscall_table.S $KERNEL_DIR/arch/i386/kernel/syscall_table.S
# Define your syscall names and number here
cp unistd.h        $KERNEL_DIR/include/asm/unistd.h
# prodcons library
#cp sem.h      $KERNEL_DIR/include/linux/sem.h;


# If exists, clear previous build
FILES="System.map bzImage $KERNEL_DIR/System.map $KERNEL_DIR/arch/i386/boot/bzImage"
echo "INFO: Cleaning ${FILES}"
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
make ARCH=i386 bzImage
cd ..



if [ -a "$KERNEL_DIR/System.map" ] && [ -a "$KERNEL_DIR/arch/i386/boot/bzImage" ];
then
     # Copy kernel image to your working directory
     cp $KERNEL_DIR/arch/i386/boot/bzImage .
     # Copy kernel symbole table
     cp $KERNEL_DIR/System.map .

     # Compile prodcons program statistically using kernel source directory
     gcc -m32 -o test -I $KERNEL_DIR/include/ ./test.c
else
     echo "Error: Kernel compilation error"
fi

exit
