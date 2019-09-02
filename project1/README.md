# 1. Files
* **P1.pdf** Project description.
* **sys.c** contains syscall implementations.
* **syscall_table.S** contains syscall names and numbers.
* **unistd.h** contains syscall numbers for user.
* **sem.h** has cs1550 semaphore implementation
* **test.c** is the test driver.
* **config** is the Linux config file.

# 2. Adding cs1550 syscalls
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
<p>Copy the linux-2.6.23.1.tar.bz file to your local space under /u/OSLab/PITT_ID:</p>
<ul>
  <li>cp /u/OSLab/original/linux-2.6.23.1.tar.bz2 .</li>
</ul>
<p>Extract</p>
<ul>
  <li>tar xfj linux-2.6.23.1.tar.bz2</li>
</ul>
<p>Copy the .config file</p>
<ul>
  <li>cp /u/OSLab/original/.config linux-2.6.23.1/</li>
</ul>
<p>Copy sys.c that contains the cs1550_up and cs1550_down implementations</p>
<ul>
  <li>cp sys.c linux-2.6.23.1/kernel/sys.c </li>
</ul>
<p>Copy system call table</p>
<ul>
  <li>cp syscall_table.S linux-2.6.23.1/arch/i386/kernel/syscall_table.S</li>
</ul>
<p>Copy unistd.h that contains syscall names along with syscall number</p>
<ul>
  <li>cp unistd.h linux-2.6.23.1/include/asm/unistd.h</li>
</ul>
<p>Change into linux-2.6.23.1/ directory</p>
<ul>
  <li>cd linux-2.6.23.1</li>
</ul>
<p>Build</p>
<ul>
  <li>make ARCH=i386 bzImage</li>
</ul>
<p></p>
<p>Building the test program</p>
<ul>
  <li>gcc -m32 -o test -I linux-2.6.23.1/include/ test.c</li>
</ul>

# 3. Testing cs1550 syscalls
<p>Download the Qemu emulator:</p>
<ul>
  <li>Windows: https://github.com/hmofrad/CS1550/blob/master/project1/qemu_win.zip</li>
  <li>Mac os: https://github.com/hmofrad/CS1550/blob/master/project1/qemu_mac.zip</li>
</ul>
<p>Extract and launch Qemu VM:</p>
<ul>
  <li>Windows: qemu/qemu-win.bat</li>
  <li>Mac OS: qemu-test/start.sh</li>
</ul>
<p>Login to Qemu VM:</p>
<ul>
  <li>Username: root</li>
  <li>Password: root</li>
</ul>
<p>Use scp to download the kernel to a home directory:</p>
<ul>
  <li>scp PITT_ID@thoth.cs.pitt.edu:/u/OSLab/PITT_ID/CS1550/project1/linux-2.6.23.1/arch/i386/boot/bzImage .</li>
  <li>scp PITT_ID@thoth.cs.pitt.edu:/u/OSLab/PITT_ID/CS1550/project1/linux-2.6.23.1/System.map .</li>
</ul>
<p>Copy kernel files</p>
<ul>
  <li>cp bzImage /boot/bzImage-devel</li>
  <li>cp System.map /boot/System.map-devel</li>
</ul>

<p>Boot from modified kernel</p>
<ul>
  <li>lilo</li>
</ul>
<p>Reboot Qemu VM:</p>
<ul>
  <li>reboot</li>
</ul>
<p>Select Linux (devel) from boot loader menu</p>
<ul>
  <li>Hit enter</li>
</ul>
<p>Download the test binary:</p>
<ul>
  <li>scp PITT_ID@thoth.cs.pitt.edu:/u/OSLab/PITT_ID/CS1550/project1/test .</li>
</ul>
<p>Run the test binary:</p>
<ul>
  <li>./test</li>
</ul>

<p>Windows users can use Ctrl + Alt to exit the Qemu VM</p>




<!--
# 4. build.sh
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

# 5. boot.sh
<p> Script for booting Qemu VM. Should be executed inisde the Qemu.</p>
<p>Download the Qemu emulator:</p>
<ul>
  <li>Windows: https://github.com/hmofrad/CS1550/blob/master/project1/qemu_win.zip</li>
  <li>Mac os: https://github.com/hmofrad/CS1550/blob/master/project1/qemu_mac.zip</li>
</ul>
<p>Extract and launch Qemu VM:</p>
<ul>
  <li>Windows: qemu/qemu-win.bat</li>
  <li>Mac OS: qemu-test/start.sh</li>
</ul>
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
<p>Reboot Qemu VM:</p>
<ul>
  <li>reboot</li>
</ul>
<p>Select Linux (devel) from boot loader menu:</p>
<ul>
  <li>Hit enter</li>
</ul>
<p>Run test binary:</p>

<ul>
  <li>./test</li>
</ul>
-->
