## 1. Fast Build Script (build.sh)
A script for adding syscalls to Linux (compatible with linux-2.6.23.1). See project details [here](http://people.cs.pitt.edu/~jmisurda/teaching/cs1550/2174/cs1550-2174-project2.htm).

Login to thoth:

* ssh username@thoth.cs.pitt.edu

Navigate to your working directory:

* cd /u/OSLab/username/WORKING_DIR

Give execute permission to the script:

* chmod +x build.sh

Run the script:

* ./build.sh

## 2. Fast Boot Script (boot.sh)
Login to Qemu VM:

* Username: root

* Password: root

Copy fast boot script:

* scp username@thoth.cs.pitt.edu:/u/OSLab/username/WORKING_DIR/boot.sh.

Within boot.sh change the scp target directory based on your working directory on thoth (line #26):

* scp $1@thoth.cs.pitt.edu:/u/OSLab/$1/{CHANGE_ACCORDINGLY}/...

Give execute permission to the script:

* chmod +x boot.sh

Run the script:

* ./boot.sh username (e.g. ./boot.sh moh18)

Reboot Qemu VM

* reboot

Select Linux (devel) from boot loader menu

* Hit Enter

Run prodcons binary:

* ./prodcons

And you will see a semaphore increment followed by a decrement

## Report bugs
* Report your bugs to moh18@pitt.edu.
