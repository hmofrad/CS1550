# Steps for compiling and testing aptsim.c
<p>Connect to thoth.cs.pitt.edu</p>
<ul>ssh PITT_ID@thoth.cs.pitt.edu</ul>
<p>Navigate to project 2 directory</p>
<ul>cd /u/OSLab/PITT_ID/CS1550/project2</ul>
<p>Compile aptsim.c by</p>
<ul>gcc -m32 -o aptsim aptsim.c</ul>
<ul>Alternatively, you can use the Makefile and compile it using make</ul>
<p>Now fire up your Qemu virtual machine and </p>
<ul>scp PITT_ID_@thoth.cs.pitt.edu:/u/OSLab/PITT_ID/CS1550/project2/\{bzImage,System.map\} .</ul>
<ul>/bin/cp -rf bzImage /boot/bzImage-devel</ul>
<ul>/bin/cp -rf System.map /boot/System.map-devel</ul>
<ul>lilo</ul>
<p>Reboot your Qemu VM, and then select Linux (devel) from boot loader menu. Note, you only need to perform the above steps to setting up the new kernel only one time</p>
<p>Last, copy aptsim to your Qemu VM and test it</p>
<ul>scp PITT_ID_@thoth.cs.pitt.edu:/u/OSLab/PITT_ID/CS1550/project2/aptsim .</ul>
<ul>./aptsim</ul>
<p>Note that you don't have to reboot the Qemu machine anymore. Just edit and compile aptsim.c on thoth. The copy and test it on Qemu VM using the above commands </p>
