# 1. Steps for compiling and testing sem_test.c and condvar_test.c
<p>1. Connect to thoth.cs.pitt.edu</p>
<ul>ssh PITT_ID@thoth.cs.pitt.edu</ul>
<p>2. Navigate to project 2 directory</p>
<ul>cd /u/OSLab/PITT_ID/CS1550/project2</ul>
<p>3. Copy and extract the kernel archive</p>
<ul>cp /u/OSLab/original/linux-2.6.23.1.tar.bz2 . </ul>
<ul>tar xjf linux-2.6.23.1.tar.bz2</ul>
<p>4. Copy <b>unistd.h</b> into include directory of the kernel</p>
<ul>cp unistd.h linux-2.6.23.1/include/asm/unistd.h</ul>
<p>5. Compile sem_test.c and condvar_test.c</p>
<ul>gcc -m32 -o sem_test -I linux-2.6.23.1/include sem_test.c # sem_test.c</ul>
<ul> gcc -m32 -o condvar_test  -I linux-2.6.23.1/include condvar_test.c condvar.c # condvar_test.c</ul>
<ul>Alternatively, you can use the Makefile and just type <b>make</b></ul>
<p>6. Now fire up your Qemu virtual machine on your laptop, then login and use the following commands to copy the kernel image with cs1550 semaphore implementation to Qemu and add it to the Linux boot loader</p>
<ul>scp PITT_ID_@thoth.cs.pitt.edu:/u/OSLab/PITT_ID/CS1550/project2/\{bzImage,System.map\} .</ul>
<ul>/bin/cp -rf bzImage /boot/bzImage-devel</ul>
<ul>/bin/cp -rf System.map /boot/System.map-devel</ul>
<ul>lilo</ul>
<p>7. Reboot your Qemu VM, and then select Linux (devel) from boot loader menu. Note, you need to perform the above steps only one time to set up the new kernel</p>
<p>8. Last, copy sem_test and condvar_test to your Qemu VM and test it</p>
<ul>scp PITT_ID_@thoth.cs.pitt.edu:/u/OSLab/PITT_ID/CS1550/project2/sem_test . # sem_test</ul>
<ul>./sem_test # sem_test</ul>
<ul>scp PITT_ID_@thoth.cs.pitt.edu:/u/OSLab/PITT_ID/CS1550/project2/condvar_test . # condvar_test</ul>
<ul>./condvar_test # condvar_test</ul>
<p><b>Note</b>: You do not have to reboot the Qemu machine anymore. Just edit sem_test.c or condvar_test.c on thoth and then compile it using make. Next copy and test it on Qemu VM using the above commands </p>
<p><b>Note</b>: Please visit Courseweb for a detailed version of project instructions PDF file.</p>

# 2. Have a look at utils folder for some utility implementations
