# 1. Fast Build Script (build.sh)
<p>A script for adding syscalls to Linux (compatible with linux-2.6.23.1).</p>
<p>See project details at http://people.cs.pitt.edu/~jmisurda/teaching/cs1550/2174/cs1550-2174-project2.htm</p>
<p>Login to thoth:</p>
<ul>
  <li>ssh username@thoth.cs.pitt.edu</li>
</ul>
<p>Navigate to your working directory:</p>
<ul>
  <li>cd /u/OSLab/username/WORKING_DIR</li>
</ul>
<p>Give execute permission to the script:</p>
<ul>
  <li>chmod +x build.sh</li>
</ul>
<p>Run the script:</p>
<ul>
  <li>./build.sh</li>
</ul>



# 2. Fast Boot Script (boot.sh)
<p>Login to Qemu VM:</p>
<ul>
  <li>Username: root</li>
  <li>Password: root</li>
</ul>
<p>Copy fast boot script:</p>
<ul>
  <li>scp PITT_ID@thoth.cs.pitt.edu:/u/OSLab/username/WORKING_DIR/boot.sh .</li>
</ul>
<p>Within boot.sh change the scp target directory based on your working directory on thoth:</p>
<ul>
  <li>scp $1@thoth.cs.pitt.edu:/u/OSLab/$1/{CHANGE_ACCORDINGLY}/...</li>
</ul>
<p>Give execute permission to the script:</p>
<ul>
  <li>chmod +x boot.sh</li>
</ul>
<p>Run the script:</p>
<ul>
  <li>./boot.sh username (e.g. ./boot.sh moh18)</li>
</ul>
<p>Reboot Qemu VM</p>
<ul>
  <li>reboot</li>
</ul>
<p>Select Linux (devel) from boot loader menu</p>
<ul>
  <li>Hit enter</li>
</ul>
<p>Run prodcons binary:</p>

<ul>
  <li>./prodcons</li>
  <li>And you will see a semaphore increment followed by a decrement</li>
</ul>


###Don't forget to report bugs to moh18@pitt.edu.
