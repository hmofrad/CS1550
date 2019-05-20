#!/bin/bash
# boot.sh: Boot script for Qemu VM
# (c) Mohammad Hasanzadeh Mofrad, 2019
# (e) moh18@pitt.edu
# Run: To be executed on Qemu VM
#      First give execute permission to the script by
#      chmod +x boot.sh 
#      Then run the script by
#      ./bott.sh

if [ $# -ne 1 ]; then
    echo "Usage: ./boot.sh PITT_ID"
    exit 1
fi


FILES="test /boot/bzImage-devel /boot/System.map-devel"
echo "INFO: Cleaning ${FILES}"
for FILE in ${FILES};
do
    if [ -a "$FILE" ];
    then
         echo $FILE
         rm -rf $FILE;
    fi
done

# Change the directory based on your working directory on thoth
scp $1@thoth.cs.pitt.edu:/u/OSLab/$1/project2/demo/\{bzImage,System.map,test\} ./
# Copy kernel files
/bin/cp -rf bzImage /boot/bzImage-devel
/bin/cp -rf System.map /boot/System.map-devel
# Boot from modified kernel
lilo
