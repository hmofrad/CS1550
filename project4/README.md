# FUSE: Filesystem in Userspace
<p>1. Connect to thoth.cs.pitt.edu</p>
<ul>ssh PITT_ID@thoth.cs.pitt.edu</ul>
<p>2. Navigate to project4 directory</p>
<ul>cd /u/OSLab/PITT_ID/CS1550/project4</ul>
<p>3. Clone the repo</p>
<ul>git clone https://github.com/hmofrad/CS1550</ul>
<p>4. Copy fuse archive</p>
<ul> cp /u/OSLab/original/fuse-2.7.0.tar.gz</ul>
<p>5. Extract fuse</p>
<ul>tar xzvf fuse-2.7.0.tar.gz</ul>
<p>6. Navigate to fuse directory</p>
<ul>cd fuse-2.7.0</ul>
<p>7. Configure fuse</p>
<ul>./configure</ul>
<p>8. Install fuse</p>
<ul>make</ul>
<p>9. Navigate to the example directory</p>
<ul>cd example</ul>
<p>10. Create the testmount directory</p>
<ul>mkdir testmount</ul>
<p>11. Create the disk</p>
<ul>dd bs=1K count=5K if=/dev/zero of=.disk</ul>
<p>12. Compile fuse examples</p>
<ul>make clean && make</ul>
<p>13. Run hello world example </p>
<ul>./hello </ul>
<p>14. Run cs1550 world example </p>
<ul>./cs1550 </ul>
 
## build.sh: Build script for compiling FUSE on thoth
<p>1. Connect to thoth.cs.pitt.edu</p>
<ul>ssh PITT_ID@thoth.cs.pitt.edu</ul>
<p>2. Navigate to project4 directory</p>
<ul>cd /u/OSLab/PITT_ID/CS1550/project4</ul>
<p>3. Clone the repo</p>
<ul>git clone https://github.com/hmofrad/CS1550</ul>
<p>4. Give execute permission to the script</p>
<ul> chmod +x build.sh</ul>
<p>5. Run the script</p>
<ul>./build.sh &lt;hello|cs1550&gt;</ul>