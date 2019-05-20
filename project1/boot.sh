#!/bin/bash
# boot.sh: Boot script for Qemu VM
# (c) Mohammad Hasanzadeh Mofrad, 2019
# (e) moh18@pitt.edu
# Run: To be executed on Qemu VM
#      First give execute permission to the script by
#      chmod +x boot.sh 
#      Then run the script by
#      ./bott.sh

if [ -z $1 ]; then
    echo "WARN: PITT_ID is not set!" 
else
    PITT_ID=$1
    echo "INFO: Your PITT_ID is $PITT_ID"
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
if [ -z "$PITT_ID" ]
then
    echo "ERROR: Edit the following line" 
    WORKING_DIR=""
    PITT_ID=""
    scp $PITT_ID@thoth.cs.pitt.edu:/$WORKING_DIR/\{bzImage,System.map,test\} ./ 
else
    scp PITT_ID@thoth.cs.pitt.edu:WORKING_DIR/\{bzImage,System.map,test\} ./ 
fi
# Copy kernel files
/bin/cp -rf bzImage /boot/bzImage-devel
/bin/cp -rf System.map /boot/System.map-devel
# Boot from modified kernel
lilo
