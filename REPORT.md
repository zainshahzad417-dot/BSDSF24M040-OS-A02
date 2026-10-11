#Assignment 02 Report 

##Version v1.0.0:Project Setup

##Implementation

I created the src,bin,obj and man directories.
I copy the instructor starter code into src/ls-v1.0.0.c
I created a Makefile to the compile and link the program


##Build Process
GCC uses -c to compile the source into obj/ls.o
GCC then links the object file into bin/ls
THe -o option specifies the output filename.
make the clean removes the generated object files and the executables.

##Directory Operations
opendir() open a directory
readdir() read entries from stream
closedir() closes stream
The starter skips entries whose names begin with dot.

##Verifies tests
make:Built successfully.
./bin/ls:Listed project entries one per line
./bin/ls/ etc:Listed visible entries in /etc

##Multiple directory test
Record the result of ./bin/ls /etc /tmp here

##Remaining work
Long listing , column display , horizontal display, alphabetical sorting , colors, recursive listing , and the cirresponding report explanation

##Required resources 

Add the mandatory video viewing notes and exact teacher report question

##Test results
- Compilation with -Wall and -Wextra: passed without warnings.
- Basic listing: passed.
- Long listing of the project directory: passed.
- Long listing of /etc: passed.
- Multiple-directory listing: passed.
- File permissions and symbolic-link output: matched Ubuntu ls.


## Version v1.2.0: Column Display

### Implemented Feature
Default listing now displays filenames in aligned columns.
Entries fill down each column before continuing across.

### Implementation Explanation
opendir(), readdir(), and closedir() handle directory entries.
A dynamic array stores copies of the visible filenames.
realloc() expands the array when more space is needed.
strdup() copies each filename because readdir() storage may
be overwritten by later calls.

ioctl() with TIOCGWINSZ reads the terminal width.
If terminal-width detection fails, the program uses 80 columns.

The longest filename determines the column width.
Two spaces separate adjacent columns.
The entry index is calculated as:

index = row + column * rows

The -l option continues using the existing long-listing function.
All allocated filenames and the array are freed after use.

### Complexity
Collecting and printing entries takes linear time in the
number of entries and the total filename length.
Memory usage grows with the number of entries and filename lengths.
Alphabetical sorting has not yet been added.
### Test Results
- Compilation with -Wall and -Wextra: passed without warnings.
- Default column display: passed.
- Listing /etc: passed.
- Narrow-terminal layout: passed.
- Multiple-directory headings: passed.
- Existing -l output: passed.
- Empty-directory handling: passed.
- Invalid-directory error and failure exit status: passed.
