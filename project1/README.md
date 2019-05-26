# 1. Files

* **sys.c** contains syscall implementations.
* **syscall_table.S** contains syscall names and numbers.
* **unistd.h** contains syscall numbers for user.
* **sem.h** has cs1550 semaphore implementation
* **test.c** is the test driver.
* **config** is the Linux config file.


# 2. build.sh
<p>Script for adding cs1550 syscalls to Linux (compatible with linux-2.6.23.1).</p>

<p>Login to thoth:</p>
<ul>
  <li>ssh PITT_ID@thoth.cs.pitt.edu</li>
</ul>
<p>Navigate to your dedicated directory:</p>
<ul>
  <li>cd /u/OSLab/PITT_ID</li>
</ul>
<p>Clone the cs1550 repo:</p>
<ul>
  <li>git clone https://github.com/hmofrad/CS1550</li>
</ul>
<p>Navigate to project 1 dir:</p>
<ul>
  <li>cd CS1550/project1</li>
</ul>
<p>Give execute permission to the build.sh script:</p>
<ul>
  <li>chmod +x build.sh</li>
</ul>
<p>Run the script:</p>
<ul>
  <li>./build.sh</li>
</ul>

# 3. boot.sh
<p> Script for booting Qemu VM. Should be executed inisde the Qemu.</p>
<p>Download the qemu emulator from courseweb and launch it</p>
<p>Login to Qemu VM:</p>
<ul>
  <li>Username: root</li>
  <li>Password: root</li>
</ul>
<p>login to the Qemu and copy boot.sh script from thoth:</p>
<ul>
  <li>scp PITT_ID@thoth.cs.pitt.edu:/u/OSLab/PITT_ID/cs1550/project1/boot.sh .</li>
</ul>
<p>In Qemu, change the scp target directory of boot.sh based on your working directory on thoth:</p>
<ul>
  <li>scp $PITT_ID@thoth.cs.pitt.edu:$WORKING_DIR/...</li>
</ul>
<p>Give execute permission to the script:</p>
<ul>
  <li>chmod +x boot.sh</li>
</ul>
<p>Run the script:</p>
<ul>
  <li>./boot.sh PITT_ID WORKING_DIR (e.g. ./boot.sh moh18 /u/OSLab/moh18/cs1550/project1)</li>
</ul>
<p>Reboot Qemu VM</p>
<ul>
  <li>reboot</li>
</ul>
<p>Select Linux (devel) from boot loader menu</p>
<ul>
  <li>Hit enter</li>
</ul>
<p>Run test binary:</p>

<ul>
  <li>./test</li>
  <li>And you will see ...</li>
</ul>
