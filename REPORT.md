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

## Version v1.3.0: Horizontal Display

### Implemented Feature
Added the -x option to display filenames from left to right
across each row before continuing on the next row.

### Implementation Explanation
getopt() accepts both -l and -x.
The last display option selects the output mode.

The same dynamic filename array and terminal-width detection
are used for both column layouts.

Default vertical layout:
index = row + column * rows

Horizontal layout:
index = row * columns + column

The longest filename determines column width.
Two spaces separate adjacent columns.
Allocated filenames and the array are freed after listing.

### Complexity
Both display layouts take linear time in the number of entries
and the total filename length.
Changing the layout does not require another filename array.

### Test Results
- Compilation with -Wall and -Wextra: passed without warnings.
- Default vertical display: passed.
- Horizontal display with -x: passed.
- Existing long listing with -l: passed.
- Narrow-terminal layouts: passed.
- Multiple-directory headings: passed.
- Last-option precedence for -lx and -xl: passed.


## Version v1.4.0: Alphabetical Sorting

### Implemented Feature
All directory listings now sort filenames before displaying them.
Sorting applies to default columns, horizontal display with -x,
and long listing with -l.

### Implementation Explanation
qsort() sorts the dynamic array of filename pointers.
The compare_names() callback receives pointers to array elements.
It dereferences them to obtain the filenames.
strcmp() compares the two filenames.

A negative result places the first filename before the second.
Zero means the filenames compare equally.
A positive result places the first filename after the second.

Sorting occurs after collecting directory entries and before
selecting the display mode. Each directory is sorted separately.

### Sorting Behavior
Comparison is case-sensitive and follows strcmp() byte ordering.
It does not use locale-aware dictionary ordering.
The C standard does not prescribe qsort()'s internal algorithm.
### Test Results
- Compilation with -Wall and -Wextra: passed without warnings.
- Default listing of test files: sorted correctly.
- Horizontal listing of test files: sorted correctly.
- Long listing of test files: sorted correctly.
- Larger-directory listings: passed.


## Version v1.5.0: Colorized Output

### Implemented Feature
Filenames are colorized by file type in all display modes.

Directories: blue.
Executable regular files: green.
Archives ending in .tar, .gz, or .zip: red.
Symbolic links: pink.
Devices, sockets, and FIFOs: reverse video.

### Implementation Explanation
lstat() identifies file types without following symbolic links.
S_ISDIR(), S_ISLNK(), S_ISREG(), and the special-file macros
classify entries.

Bitwise AND checks executable permission bits.
Filename suffix comparison identifies archive extensions.
Archive color takes priority over executable color.

ANSI escape sequences select colors and reverse video.
The reset sequence restores normal terminal formatting.

isatty() enables colors only for terminal output.
Piped and redirected output remains plain text.
Column padding uses filename lengths without color sequences.
Sorting continues to compare plain filenames.

### Test Results
- Compilation with -Wall and -Wextra: passed without warnings.
- Directory, executable, archive, and symbolic-link colors: passed.
- FIFO reverse-video formatting: passed.
- Colors in default, horizontal, and long layouts: passed.
- Alphabetical ordering and column alignment: preserved.
- Piped output: plain text.


## Version v1.6.0: Recursive Listing

### Implemented Feature
Added -R to list a directory and its visible subdirectories.
Recursion works with default columns, -x, and -l.

### Implementation Explanation
getopt() accepts -R independently of the display options.
The recursive flag is passed to do_ls().

Each directory's filenames are collected and sorted.
The current directory is displayed first.
The program then visits its subdirectories in sorted order.

A full child path is allocated and constructed.
lstat() checks whether the child is a real directory.
do_ls() calls itself for that directory.

Directory headings separate recursive listings.
Hidden entries, including "." and "..", are skipped.
Symbolic links are displayed but are not followed recursively.

Directory streams are closed before descending.
Child-path buffers and filename arrays are freed.

### Error Handling
Directory and metadata errors are reported to standard error.
A failed child listing does not prevent visiting other children.
The program returns failure if any listing operation fails.

### Memory Usage
Recursive calls use stack space according to directory depth.
Each active call retains its filename array until its children
have been processed.


### Test Results
- Compilation with -Wall and -Wextra: passed without warnings.
- Nested-directory traversal with -R: passed.
- Long recursive listing with -lR: passed.
- Horizontal recursive listing with -xR: passed.
- Directory headings and sorted traversal: passed.
- Parent-directory symbolic link: displayed without traversal.
- Existing nonrecursive display modes: passed.
