#!/bin/bash
# Fast boot script for rebuilding Linux kernel
# (C) Mohammad H. Mofrad, 2017

if [ $# -ne 1 ]; then
    echo "Usage: ./test.sh PITT_ID"
    exit 1
fi

if [ -f "/boot/bzImage-devel" ]; then
     rm -rf /boot/bzImage-devel
     echo "Cleaning previous bzImage"
fi

if [ -f "/boot/System.map-devel" ]; then
     rm -rf /boot/System.map-devel
     echo "Cleaning previous System.map"
fi

if [ -f "prodcons" ]; then
     rm -rf prodcons
     echo "Cleaning previous prodcons"
fi

# Change the directory based on your working directory on thoth
scp $1@thoth.cs.pitt.edu:/u/OSLab/$1/CS1550/project2/\{bzImage,System.map,prodcons\} ./
# Copy kernel files
/bin/cp -rf bzImage /boot/bzImage-devel
/bin/cp -rf System.map /boot/System.map-devel
# Boot from modified kernel
lilo
