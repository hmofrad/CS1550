# FUSE: Filesystem in Userspace
## build.sh: Build script for compiling FUSE on thoth
<p>1. Connect to thoth.cs.pitt.edu</p>
<ul>ssh PITT_ID@thoth.cs.pitt.edu</ul>
<p>2. Navigate to project4 directory</p>
<ul>cd /u/OSLab/PITT_ID/CS1550/project4</ul>
<p>3. Give execute permission to the script</p>
<ul> chmod +x build.sh</ul>
<p>4; Run the script</p>
<ul>./build.sh &lt;hello|cs1550&gt;</ul>
<p>5. Files info</p>
<ul>build.sh: Script for building fuse</ul>

<p>6. A useful snippet code for cs1550_getattr method <p>

    printf("cs1550_getattr: path = %s\n", path);
    char directory[MAX_FILENAME + 1];
    memset(directory, 0, MAX_FILENAME + 1);
    char filename[MAX_FILENAME + 1];
    memset(filename, 0, MAX_FILENAME + 1);
    char extension[MAX_EXTENSION + 1];
    memset(extension, 0, MAX_EXTENSION + 1);
    int n = sscanf(path, "/%[^/]/%[^.].%s", directory, filename, extension);
    if(n == 1)
        printf("cs1550_getattr: directory = %s\n", directory);
    else ;
