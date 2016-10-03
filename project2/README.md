# 1. Fast Build Script (build.sh)
<p>A script for adding syscalls to Linux (compatible with linux-2.6.23.1).</p>
<p>See project detials at http://people.cs.pitt.edu/~jmisurda/teaching/cs1550/2171/cs1550-2171-project2.htm</p>
<p>login to thoth:</p>
<ul>
  <li>ssh PITT_ID@thoth.cs.pitt.edu</li>
</ul>
<p>Navigate to your working directory:</p>
<ul>
  <li>cd /u/OSLab/PITT_ID/WORK_DIR</li>
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
<p>login to Qemu VM:</p>
<ul>
  <li>Username: root</li>
  <li>Password: root</li>
</ul>
<p>Copy fast boot script:</p>
<ul>
  <li>scp PITT_ID@thoth.cs.pitt.edu:/u/OSLab/PITT_ID/WORK_DIR/boot.sh .</li>
</ul>
<p>Within boot.sh change the scp target directory:</p>
<ul>
  <li>scp $1@thoth.cs.pitt.edu:/u/OSLab/$1/{WORK_DIR}/...</li>
</ul>
<p>Give execute permission to the script:</p>
<ul>
  <li>chmod +x boot.sh</li>
</ul>
<p>Run the script:</p>
<ul>
  <li>./boot.sh PITT_ID (e.g. moh18)</li>
</ul>


