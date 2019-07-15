#!/bin/bash
# Build script for FUSE
# Execute permission: chmod +x build.sh  
# Run the script: ./build.sh
# (c) Mohammad Hasanzadeh Mofrad, 2019
# (e) moh18@pitt.edu

BASE=$PWD                    # Current working directory 
FUSE_SRC="fuse-2.7.0.tar.gz" # FUSE source file
FUSE_DIR="fuse-2.7.0"        # FUSE source directory
TEST_MOUNT="testmount"

# Check if you have the FUSE directory in your working directory
# If not, extract fuse directory
# If yes, do nothing
if [ -f "$FUSE_SRC" ]
then
     echo "$FUSE_SRC found."
     echo "You can always remove the current build using \"rm -rf $FUSE_DIR*\""
else
     echo "$FUSE_SRC not found."
     cp /u/OSLab/original/${FUSE_SRC} .
     echo "Extracting ${FUSE_SRC} into ${PWD}"
     tar xzvf ${FUSE_SRC}
     cd ${PWD}/${FUSE_DIR}
     echo "Installing ${FUSE_DIR} into ${PWD}"
     ./configure
     make
     cd -
     echo "Build compeleted!"
fi

# run FUSE cs1550 examples
echo "Running $1 example";
cd ${PWD}/${FUSE_DIR}/example/;
if [ ! -d "${TEST_MOUNT}" ]; 
then
   echo "Creating ${TEST_MOUNT}";
   mkdir ${TEST_MOUNT}
fi
if [ ! -f ".disk" ]; then
   echo
   echo "Creating disk image at \".disk\"";
   dd bs=1K count=5K if=/dev/zero of=.disk
fi   
echo
echo "Unmounting the previous ${TEST_MOUNT}";
fusermount -u ${TEST_MOUNT}
echo
echo "Cleaning the previous build";
make clean
echo
echo "Making the new build";
make
echo
echo "Launching FUSE daemon for \"${EXAMPLE}\"";
./${EXAMPLE} -d ${TEST_MOUNT}