#!/bin/bash
# build.sh: Build script for Linux kernel
# (c) Mohammad Hasanzadeh Mofrad, 2019
# (e) moh18@pitt.edu
# Run: To be executed on thoth
#      First give execute permission to the script by
#      chmod +x build.sh 
#      Then run the script by
#      ./build.sh

BASE=$PWD # Current working directory 
KERNEL_SRC="linux-2.6.23.1.tar.bz2" # Kernel source file
KERNEL_DIR="linux-2.6.23.1" # Kernel source directory

if [ -z $1 ]; then
    echo "WARN: PITT_ID is not set!" 
else
    PITT_ID=$1
    echo "INFO: Your PITT_ID is $PITT_ID"
fi

if [[ "$BASE" =~ ^/u/OSLab/.*$ ]];
then
     echo "INFO: $BASE is oaky."
else
     echo "WARN: For proper use, navigate to /u/OSLab/$PITT_ID and then clone the repo."
fi

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
    fi
fi
  
if [ ! -d "$KERNEL_DIR" ]; then
    echo "INFO: Extracting $KERNEL_SRC ..." 
    tar xjf $KERNEL_SRC
fi

# Project 1 (Please upload sys.c, syscall_table.S, unitstd.h, and sem.h)
echo "INFO: Copying sys.c syscall_table.S unistd.h" 
# This file is the kernel config file
cp config $KERNEL_DIR/.config

# This file contains sys_cs1550_up and sys_cs1550_down implementations
cp sys.c           $KERNEL_DIR/kernel/sys.c             

# System call table
cp syscall_table.S $KERNEL_DIR/arch/i386/kernel/syscall_table.S

# This file contains syscall names along with syscall number
cp unistd.h        $KERNEL_DIR/include/asm/unistd.h


# If exists, clear the old build
FILES="test System.map bzImage $KERNEL_DIR/System.map $KERNEL_DIR/arch/i386/boot/bzImage"
echo "INFO: Cleaning ${FILES}"
for FILE in ${FILES};
do
    if [ -a "$FILE" ];
    then
         echo $FILE
         rm -rf $FILE
    fi
done

# Compile kernel
cd $KERNEL_DIR
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
     echo "ERROR: Kernel compilation error"
     exit
fi

#Update boot.sh
if [ -z "$PITT_ID" ];
then
    echo "WARN: You should update boot.sh manually"
else
    echo "Updating boot.sh for you"
    sed -i  "s/PITT_ID/$PITT_ID/g" "boot.sh"
    sed -i  "s|WORKING_DIR|$BASE|g" "boot.sh"
    
fi

