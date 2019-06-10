# Steps for compiling and testing aptsim.c
<p>Connect to thoth.cs.pitt.edu</p>
<ul>ssh PITT_ID@thoth.cs.pitt.edu</ul>
<p>Navigate to project 2 directory</p>
<ul>cd /u/OSLab/PITT_ID/CS1550/project2</ul>
<p>Compile aptsim.c using</p>
<ul>make clean && make</ul>
<p>Now fire up your Qemu virtual machine, login and </p>
<ul>scp PITT_ID_@thoth.cs.pitt.edu:/u/OSLab/PITT_ID/CS1550/project2/\{bzImage,System.map,aptsim\} ./</ul>
<ul>/bin/cp -rf bzImage /boot/bzImage-devel</ul>
<ul>/bin/cp -rf System.map /boot/System.map-devel</ul>
<ul>lilo</ul>



