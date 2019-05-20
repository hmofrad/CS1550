#!/bin/bash
# boot.sh: Boot script for Qemu VM
# (c) Mohammad Hasanzadeh Mofrad, 2019
# (e) moh18@pitt.edu
# Run: To be executed on Qemu VM
#      First give execute permission to the script by
#      chmod +x boot.sh 
#      Then run the script by
#      ./bott.sh

if [ "$#" -eq 2 ]; then
    PITT_ID=$1
    WORKING_DIR=$2
    echo "INFO: Your PITT_ID is $PITT_ID and WORKING_DIR is $WORKING_DIR"
else
    echo "WARN: PITT_ID and WORKING_DIR are not set!" 
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
    echo "INFO: Copy using pre-populated information from build.sh."
    scp PITT_ID_@thoth.cs.pitt.edu:WORKING_DIR_/\{bzImage,System.map,test\} ./ 
else
    echo "INFO: Copy using the given arguments." 
    scp $PITT_ID@thoth.cs.pitt.edu:$WORKING_DIR/\{bzImage,System.map,test\} ./ 
fi
# Copy kernel files
/bin/cp -rf bzImage /boot/bzImage-devel
/bin/cp -rf System.map /boot/System.map-devel
# Boot from modified kernel
lilo
